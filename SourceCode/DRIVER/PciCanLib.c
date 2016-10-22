/********************************************************************
文件名称:   PciCanLib.c

文件功能:   板卡驱动源文件

文件说明:   实现PCI板卡CAN总线通讯功能

当前版本:   V1.6

修改记录:   2014-06-25  V1.0    李世杰  创建
            2014-09-04  V1.1    李世杰  升级    重新设计驱动结构
            2014-11-06  V1.2    李世杰  升级    解决一个文件描述符bug
            2015-10-20  V1.3    徐佳谋  升级    统一函数名，解决5.5无法使用问题
            2016-04-21  V1.4    徐佳谋  升级    解决接收丢帧问题，修改发送函数
            2016-06-17  V1.5    徐佳谋  增加    增加版本显示函数
            2016-08-02  V1.6    徐佳谋  升级    修改为持续发送，同时解决复位不成功问题   
********************************************************************/

#ifndef _WRS_CONFIG_SMP
#define _WRS_CONFIG_SMP /* 双核模式 */
#endif

#include "stdio.h"
#include "string.h"
#include "vmLib.h"
#include "drv\pci\pciConfigLib.h"
#include "arch\I86\ivI86.h"
#include "semLib.h"
#include "rngLib.h"
#include "msgQLib.h"
#include "logLib.h"
#include "drv\pci\pciIntLib.h"
#include "taskLib.h"

#include "PciCanLib.h"

/* 调试宏 */
#define DEBUG                   0

#ifdef _WRS_CONFIG_SMP
IMPORT UINT8 *sysInumTbl;
#undef INT_NUM_GET
#define INT_NUM_GET(irq) sysInumTbl[irq]
#else
#define INT_NUM_IRQ0            0x20
#undef INT_NUM_GET
#define INT_NUM_GET(irq)        ((int)irq + INT_NUM_IRQ0)
#endif

#define VM_STATE_MASK_FOR_ALL   VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE
#define VM_STATE_FOR_PCI        VM_STATE_VALID | VM_STATE_WRITABLE | VM_STATE_CACHEABLE_NOT
#define VM_PAGE_SIZE            4096
#define PCI_DEV_MMU_MSK         (~(VM_PAGE_SIZE - 1))

/* 寄存器访问宏 */
#define READ_REGISTER_UCHAR(x)      (*(volatile unsigned char *)(x))
#define READ_REGISTER_USHORT(x)     (*(volatile unsigned short *)(x))
#define READ_REGISTER_ULONG(x)      (*(volatile unsigned long *)(x))

#define WRITE_REGISTER_UCHAR(x, y)  (*(volatile unsigned char *)(x) = (unsigned char)((y) & 0xFF))
#define WRITE_REGISTER_USHORT(x, y) (*(volatile unsigned short *)(x) = (unsigned short)((y) & 0xFFFF))
#define WRITE_REGISTER_ULONG(x, y)  (*(volatile unsigned long *)(x) = (unsigned long)(y))

typedef struct pcican_device_s
{
    unsigned long ulBase0;  /* 映射基地址 */
    unsigned long ulBase2;  /* 映射基地址 */
    unsigned long ulSize;   /* 映射地址大小 */
    int irq;                /* 是否注册中断标志 */
    int tid;                /* 驱动使用任务 */
    int isr;                /* 驱动中断注册标志 */
    int fpga;               /* FPGA版本 */
    SEM_ID sem;             /* 驱动程序使用信号量 */
} pcican_device_t;

/* SJA1000芯片初始化结构体 注意结构体内存对齐问题 */
typedef struct pcican_sja1000_s
{
    unsigned long base;
    RING_ID ring;   /* 驱动程序使用的软件FIFO */
    RING_ID ring2;  /* 驱动程序使用的发送FIFO */
    SEM_ID sem2;    /* 应用程序使用信号量 */
    SEM_ID mutex;   /* 驱动使用互斥体 */
    SEM_ID sem3;    /* 发送使用信号量 */
    SEM_ID sem4;    /* 发送完成使用信号量 */
    int tid2;       /* 发送任务tid */
    MSG_Q_ID msg;   /* 驱动程序使用消息 */
} pcican_sja1000_t;

/* 全局设备结构 */
pcican_device_t g_devices[MAX_DEVICE_NUM];
pcican_sja1000_t g_sja1000s[MAX_CAN_NUM];
static char s_versions[64];

/* 内部函数声明 */
void iPciCan(void *para);
int tPciCan(void *para);
int tPciCan2(MSG_Q_ID msg);
int DrainFifo(int fd);

int InitSja(pcican_sja1000_t *pCan, sja1000_config_t *pConfig);

extern STATUS sysIntEnablePIC(int intLevel);
extern STATUS sysMmuMapAdd(void *address, UINT len, UINT initialStateMask, UINT initialState);

/********************************************************************
函数名称:   CreatePciCan

函数功能:   第一阶段初始化函数。

参数名称        类型            输入/输出           含义
index           int             input               设备索引

返回值  :   0:成功 非0:失败

函数说明:   在使用驱动前，需要先创建板卡设备。函数初始化全局设备变量。

修改记录:   2014-06-25  李世杰  创建
********************************************************************/
int CreatePciCan(int index)
{
    int ret = 0;
    int BusNo;
    int DeviceNo;
    int FuncNo;
    unsigned int ul;
    pcican_device_t *pDevice = NULL;

    /* 防止参数错误 获取设备结构体指针 */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* 判断是否已经映射地址 */
    if(pDevice->ulBase2 != 0)
    {
        return 0;
    }

    /* 搜索PCI总线查找PLX9056设备 */
    ret = pciFindDevice(PLX9056_VENDOR_ID, PLX9056_DEVICE_ID, index, &BusNo, &DeviceNo, &FuncNo);
    if (ret == -1)
    {
        ret = -1;
        goto Exit;
    }

    /* 读取设备映射空间地址0 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &ul);
    if (ret == -1)
    {
        ret = -2;
        goto Exit;
    }

    pDevice->ulBase0 = ul;

    /* 映射内存访问 */
    ret = sysMmuMapAdd((void *)(pDevice->ulBase0 & PCI_DEV_MMU_MSK), 4096, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_PCI);
    if (ret == -1)
    {
        /*ret = -3;
        goto Exit; 在应用层调用时 无法测试 */
    }

    /* 读取设备映射空间地址2 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, &ul);
    if (ret == -1)
    {
        ret = -4;
        goto Exit;
    }

    pDevice->ulBase2 = ul;

    /* 读取设备映射空间长度 */
    pciConfigOutLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, 0xFFFFFFFF);
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, &ul);
    if (ret == -1)
    {
        ret = -5;
        goto Exit;
    }

    pDevice->ulSize = (~ul | 0x0F) + 1;  /* 已经确定是内存映射 */

    /* 映射内存访问 */
    ret = sysMmuMapAdd((void *)(pDevice->ulBase2 & PCI_DEV_MMU_MSK), pDevice->ulSize, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_PCI);
    if (ret == -1)
    {
        /*ret = -6;
        goto Exit; 在应用层调用时 无法测试 */
    }

    /* 必须回写地址 */
    pciConfigOutLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, pDevice->ulBase2);

    /* 读取设备中断号 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &ul);
    if (ret == -1)
    {
        ret = -7;
        goto Exit;
    }

    pDevice->irq = ul & 0xFF;

    return ret;

Exit:
    RemovePciCan(index);

    return ret;
}

/********************************************************************
函数名称:   RemovePciCan

函数功能:   删除板卡驱动

参数名称        类型            输入/输出           含义
index           int             input               板卡索引(0-1)

返回值  :   0:成功 非0:失败

函数说明:   清除第一阶段初始化变量。

修改记录:   2014-06-25  李世杰  创建
********************************************************************/
int RemovePciCan(int index)
{
    int ret = 0;
    pcican_device_t *pDevice = NULL;

    /* 防止参数错误 */
    index %= MAX_DEVICE_NUM;

    /* 判断是否已经映射地址 */
    pDevice = &g_devices[index];
    if (pDevice->ulBase2 == 0)
    {
        return -1;
    }

    /* 先删除第二阶段 */
    RemovePciCan2(index);

    pDevice->ulBase2 = 0;

    return ret;
}

/********************************************************************
函数名称:   CreatePciCan2

函数功能:   第二阶段初始化驱动

参数名称        类型            输入/输出           含义
index           int             input               设备索引

返回值  :   0:成功 非0:失败

函数说明:   驱动在调用CreatePciCan函数后，还需要调用此函数继续初始化。

修改记录:   2015-10-20  徐佳谋  创建
********************************************************************/
int CreatePciCan2(int index)
{
    int ret = 0;
    int i = 0;
    pcican_device_t *pDevice = NULL;

    /* 防止参数错误 获取设备结构体指针 */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* 判断是否已经映射地址 */
    if(pDevice->ulBase2 == 0)
    {
        return -1;
    }

    /* 判断是否已经注册中断 */
    if (pDevice->isr == 1)
    {
        return 0;
    }

    /* 记录CAN口基地址 */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        g_sja1000s[i].base = pDevice->ulBase2 + i * CAN_CHANNEL_STRIDE;
    }

    /* 创建信号量 */
    pDevice->sem = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pDevice->sem == NULL)
    {
        ret = -2;
        goto Exit;
    }

    /* 创建任务 */
    pDevice->tid = taskSpawn("tPciCan", 0, (VX_SUPERVISOR_MODE | VX_UNBREAKABLE), 8192, tPciCan, (int)pDevice, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pDevice->tid == -1)
    {
        ret = -3;
        goto Exit;
    }

    /* 注册中断服务程序 */
    ret = pciIntConnect(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciCan, (int)pDevice);
    if (ret == -1)
    {
        ret = -4;
        goto Exit;
    }
    pDevice->isr = 1;

    /* 使能中断 */
    sysIntEnablePIC(pDevice->irq);

    /* 打开Local Bus 中断 */
    WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68) | (0x01 << 11));

    return ret;

Exit:
    RemovePciCan2(index);

    return ret;
}

/********************************************************************
函数名称:   RemovePciCan2

函数功能:   删除板卡驱动2

参数名称        类型            输入/输出           含义
index           int             input               板卡索引(0-1)

返回值  :   0:成功 非0:失败

函数说明:   关闭中断，清除第二阶段初始化变量。

修改记录:   2015-10-20  徐佳谋  创建
********************************************************************/
int RemovePciCan2(int index)
{
    int i = 0;
    pcican_device_t *pDevice = NULL;

    /* 先关闭所有通道 */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        ClosePciCan(i);
    }

    /* 防止参数错误 获取设备结构体指针 */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* 关闭FPGA中断 */
    WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, (READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68) & ~(0x01 << 11)));

    if (pDevice->isr != 0)
    {
        pciIntDisconnect2(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciCan, (int)pDevice);
        pDevice->isr = 0;
    }

    if (pDevice->tid != 0)
    {
        taskDelete(pDevice->tid);
        pDevice->tid = 0;
    }

    if (pDevice->sem != NULL)
    {
        semDelete(pDevice->sem);
        pDevice->sem = 0;
    }

    return 0;
}

/********************************************************************
函数名称:   OpenPciCan

函数功能:   打开设备

参数名称        类型            输入/输出           含义
fd              int             input               设备描述符

返回值  :   0:成功 非0:失败

函数说明:   函数创建驱动需要使用的信号量、任务、队列、注册中断服务程序等。

修改记录:   2013-07-22  徐佳谋  创建
********************************************************************/
int OpenPciCan(int fd)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* 参数检查 */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->base == 0)
    {
        return -1;
    }

    /* 创建互斥体 */
    pCan->mutex = semMCreate(SEM_Q_FIFO | SEM_DELETE_SAFE);
    if (pCan->mutex == NULL)
    {
        ret = -2;
        goto Exit;
    }

    /* 创建FIFO */
    pCan->ring = rngCreate(CAN_FIFO_SIZE);
    if (pCan->ring == NULL)
    {
        ret = -3;
        goto Exit;
    }

    pCan->ring2 = rngCreate(CAN_TX_FIFO_SIZE);
    if (pCan->ring2 == NULL)
    {
        ret = -3;
        goto Exit;
    }

    /* 创建信号量 */
    pCan->sem2 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pCan->sem2 == NULL)
    {
        ret = -4;
        goto Exit;
    }

    pCan->sem3 = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
    if (pCan->sem3 == NULL)
    {
        ret = -5;
        goto Exit;
    }

    pCan->sem4 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pCan->sem4 == NULL)
    {
        ret = -5;
        goto Exit;
    }

    /* 创建消息队列 */
    pCan->msg = msgQCreate(100, 32, MSG_Q_PRIORITY);
    if (pCan->msg == NULL)
    {
        ret = -6;
        goto Exit;
    }

    /* 创建发送任务 */
    pCan->tid2 = taskSpawn("tPciCan2", 100, (VX_SUPERVISOR_MODE | VX_UNBREAKABLE), 8192, tPciCan2, (int)pCan->msg, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pCan->tid2 == -1)
    {
        ret = -7;
        goto Exit;
    }

    return ret;

Exit:
    ClosePciCan(fd);

    return ret;
}

/********************************************************************
函数名称:   ClosePciCan

函数功能:   关闭PCICAN板卡驱动

参数名称        类型            输入/输出           含义
fd              int             input               设备描述符

返回值  :   0:成功 非0:失败

函数说明:   函数关闭创建的信号量、任务、队列、中断注册。

修改记录:   2014-06-25  李世杰  创建
********************************************************************/
int ClosePciCan(int fd)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* 参数检查 */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->tid2 == 0)
    {
        return -1;
    }

    /* 禁止CAN口芯片中断 */
    WRITE_REGISTER_UCHAR(pCan->base + 4, 0x00);

    /* 删除变量 */
    if (pCan->ring != NULL)
    {
        rngDelete(pCan->ring);
        pCan->ring  = 0;
    }

    if (pCan->ring2 != NULL)
    {
        rngDelete(pCan->ring2);
        pCan->ring2 = 0;
    }

    if (pCan->sem2 != NULL)
    {
        semDelete(pCan->sem2);
        pCan->sem2 = 0;
    }

    if (pCan->sem3 != NULL)
    {
        semDelete(pCan->sem3);
        pCan->sem3 = 0;
    }

    if (pCan->sem4 != NULL)
    {
        semDelete(pCan->sem4);
        pCan->sem4 = 0;
    }

    if (pCan->mutex != NULL)
    {
        semDelete(pCan->mutex);
        pCan->mutex = 0;
    }

    if (pCan->tid2 != 0)
    {
        taskDelete(pCan->tid2);
        pCan->tid2 = 0;
    }

    if (pCan->msg != NULL)
    {
        msgQDelete(pCan->msg);
        pCan->msg = 0;
    }

    return ret;
}

/********************************************************************
函数名称:   IoctlPciCan

函数功能:   实现不同功能的命令字

参数名称        类型            输入/输出           含义
fd              int             input               设备描述符
cmd             int             input               命令字
p               void*           input/output        命令字对应参数

返回值  :   0:成功 非0:失败

函数说明:   函数通过不同的命令字与参数，实现不同的功能。
            IOCTL_INIT_SJA初始化芯片。

修改记录:   2014-06-25  李世杰  创建
********************************************************************/
int IoctlPciCan(int fd, int cmd, void *p)
{
    pcican_sja1000_t *pCan = NULL;
    int ret = 0;

    /* 确认设备有效 */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];

    /* 根据命令字 */
    switch(cmd & 0x00FF)
    {
    case IOCTL_INIT_SJA:            /* 初始化SJA控制器 */
        InitSja(pCan, p);

        break;

    default:
        ;
    }

    return ret;
}

/********************************************************************
函数名称:   WritePciCan

函数功能:   通过FIFO发送CAN总线帧(1帧)

参数名称        类型             输入/输出           含义
fd              int              input               设备描述符
pFrame          sja1000_frame_t* input               发送数据指针

返回值  :   0:成功 非0:失败

函数说明:   通过任务发送数据，直接写SJA1000发送寄存器，属于查询发送。

修改记录:   2014-06-25  李世杰  创建
            2016-04-22  徐佳谋  升级    修改为中断发送
********************************************************************/
int WritePciCan(int fd, sja1000_frame_t *pFrame)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* 参数检查 */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->tid2 == 0)
    {
        return -1;
    }

    /* 等待缓冲有空余 */
    semTake(pCan->sem3, WAIT_FOREVER);

    /* 保证访问互斥 */
    semTake(pCan->mutex, WAIT_FOREVER);

    /* 发送数据放入FIFO */
    rngBufPut(pCan->ring2, (char *)pFrame, sizeof(sja1000_frame_t));

    /* 触发发送任务 */
    msgQSend(pCan->msg, (char *)&pCan, sizeof(pCan), NO_WAIT, MSG_PRI_URGENT);

    /* 判断缓冲区是否有空余 */
    if (rngFreeBytes(pCan->ring2) >= sizeof(sja1000_frame_t))
    {
        /* 使能发送 */
        semGive(pCan->sem3);
    }

    /* 释放互斥 */
    semGive(pCan->mutex);

    return ret;
}

/********************************************************************
函数名称:   ReadPciCan

函数功能:   读取FIFO中的CAN总线帧(1帧)

参数名称        类型            输入/输出           含义
fd              int             input               设备描述符
pFrame          sja1000_frame_t*output              接收数据指针
timeout         int             output              读取阻塞延时(-1:无限 n:毫秒)

返回值  :   0:缓冲区为空 13:返回一帧数据 其他:失败

函数说明:   函数从驱动FIFO中读取接收到的数据，每次一帧。

修改记录:   2014-06-25  李世杰   创建
********************************************************************/
int ReadPciCan(int fd, sja1000_frame_t *pFrame, int timeout)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* 参数检查 */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->tid2 == 0)
    {
        return -1;
    }

    /* 保证一次读空数据 */
    if (rngIsEmpty(pCan->ring))
    {
        /* 等待信号量 */
        if (semTake(pCan->sem2, timeout) == -1)
        {
            return -2;
        }
    }

    /* 从软件缓冲区 */
    ret = rngBufGet(pCan->ring, (char *)pFrame, sizeof(sja1000_frame_t));
    if ((ret == 0) && (timeout == -1))
    {
        /* 通过递归解决多信号量返回0的问题 */
        ret = ReadPciCan(fd, pFrame, timeout);
    }

    return ret;
}

/********************************************************************
函数名称:   FlushPciCan

函数功能:   清除驱动缓冲

参数名称        类型            输入/输出           含义
*pCan           pcican_sja1000_t  input               设备结构体

返回值  :   0:成功 非0:失败

函数说明:   复位SJA1000芯片，清空软件缓冲区。

修改记录:   2014-6-26  李世杰  创建
********************************************************************/
int FlushPciCan(int fd)
{
    int ret = 0;
    unsigned long base;
    pcican_sja1000_t *pCan = NULL;

    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];

    /* 判断CAN口是否已经打开 */
    if (pCan->sem2 == NULL)
    {
        return -1;
    }

    base = pCan->base;

    /* 释放SJA1000接收缓存 */
    while (READ_REGISTER_UCHAR(base + CAN_STATE_REG) & 0x01)
    {
        WRITE_REGISTER_UCHAR(base + CAN_CTRL_REG, 0x04);
    }

    /* 清空软件缓冲区 */
    rngFlush(pCan->ring);
    rngFlush(pCan->ring2);

    /* 使能发送 */
    semGive(pCan->sem3);

    return ret;
}

/********************************************************************
函数名称:   iPciCan

函数功能:   板卡中断服务程序

参数名称        类型            输入/输出           含义
*para           void            input               板卡信息传递参数

返回值  :   0:成功 非0:失败

函数说明:   中断服务程序判断中断源、屏蔽中断、触发中断。
            后续的操作在后处理任务中实现。

修改记录:   2013-07-22  李世杰  创建
********************************************************************/
void iPciCan(void *para)
{
    unsigned long ul = 0x00;
    unsigned char uch = 0x00;
    pcican_device_t *pDevice = para;

    /* 判断是否是Local中断 */
    ul = READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68);
    if (!((ul & (0x01 << 15)) && (ul & (0x01 << 8))))
    {
        return ;
    }

#if DEBUG
    logMsg("ul = 0x%08X\n", ul, 0, 0, 0, 0, 0);   /* 会影响接收 */
#endif

    /* 判断是否有CAN中断 */
    uch = READ_REGISTER_UCHAR(pDevice->ulBase2 + FPGA_CAN_INT_STATE) & INT_MASK;
    if (uch == 0x00)
    {
        return ;
    }

    /* 屏蔽中断 */
    WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, ul & ~(0x01 << 8));

    /* 触发信号量  */
    if (pDevice->sem != NULL)
    {
        semGive(pDevice->sem);
    }

    return ;
}

/********************************************************************
函数名称:   tPciCan

函数功能:   中断后处理任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   为了防止中断服务程序运行时间过长，对板卡的数据操作放在后处理
            任务中实现。

修改记录:   2014-06-25  李世杰  创建
********************************************************************/
int tPciCan(void *para)
{
    int i = 0;
    unsigned char uch;
    pcican_device_t *pDevice = para;
    int states[MAX_CAN_NUM];
    pcican_sja1000_t *pCan = NULL;

    for (;;)
    {
        memset(states, 0x00, sizeof(states));

        if (semTake(pDevice->sem, WAIT_FOREVER) == -1)
        {
            break;
        }

        for(;;)
        {
            uch = READ_REGISTER_UCHAR(pDevice->ulBase2 + FPGA_CAN_INT_STATE) & INT_MASK;
            if (uch == 0x00)
            {
                break;
            }

            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                if (uch & (0x01 << i))
                {
                    states[i] = DrainFifo(i);
                }
            }
        } /* end for */

        /* 恢复中断 */
        WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, (READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68) | (0x01 << 8)));

        /* 触发应用层事件 */
        for (i = 0; i < MAX_CAN_NUM; i++)
        {
            pCan = &g_sja1000s[i];
            if (pCan->sem2 != NULL && states[i])
            {
                semGive(pCan->sem2);
            }
        }
    }

    return 0;
}

/********************************************************************
函数名称:   tPciCan2

函数功能:   数据发送任务

参数名称        类型            输入/输出           含义
msg             MSG_Q_ID        input               串口使用的消息队列

返回值  :   0:成功 非0:失败

函数说明:   使用任务发送数据，可以防止出现发送优先级过高问题。

修改记录:   2014-08-19  徐佳谋  创建
********************************************************************/
int tPciCan2(MSG_Q_ID msg)
{
    int i = 0;
    pcican_sja1000_t *pCan = NULL;
    unsigned long base = 0;
    sja1000_frame_t frame;

    for (;;)
    {
        /* 使用消息队列 */
        if (msgQReceive(msg, (char *)&pCan, sizeof(pCan), WAIT_FOREVER) == -1)
        {
            break;
        }
        base = pCan->base;

        for (;;)
        {
            if (rngIsEmpty(pCan->ring2))
            {
                break;
            }

            rngBufGet(pCan->ring2, (char *)&frame, sizeof(sja1000_frame_t));

            /* 向缓冲区写入数据 */
            WRITE_REGISTER_UCHAR(base + CAN_TRAN_FIFO_OFFSET, frame.header);

            for(i = 0; i < 12; i++)
            {
                WRITE_REGISTER_UCHAR(base + CAN_TRAN_FIFO_OFFSET + 1 + i, frame.buffer[i]);
            }

            /* 发送数据 使用持续发送 */
            WRITE_REGISTER_UCHAR(base + CAN_CTRL_REG, 0x01);

            /* 判断缓冲区可用 查询的方法
            while((READ_REGISTER_UCHAR(pCan->base + CAN_STATE_REG) & 0x04) == 0x00);*/

            /* 等待缓冲区可用 中断的方法 */
            semTake(pCan->sem4, WAIT_FOREVER);
        }

        /* 使能发送 */
        semGive(pCan->sem3);
    }

    return 0;
}

/********************************************************************
函数名称:   DrainFifo

函数功能:   读空板卡所有CAN通道中FIFO的数据

参数名称        类型                输入/输出           含义
fd              int                 input               设备通道号

返回值  :   0:成功 非0:失败

函数说明:   把硬件FIFO数据放入软件FIFO。

修改记录:   2013-07-22  徐佳谋  创建
********************************************************************/
int DrainFifo(int fd)
{
    int ret = 0;
    int i = 0;
    unsigned long base;
    unsigned char buffer[13];
    pcican_sja1000_t *pCan = &g_sja1000s[fd];
    unsigned char uch;
    unsigned char uch2;

    base = pCan->base;

    /* 读取中断状态 */
    uch = READ_REGISTER_UCHAR(base + CAN_IRQ_REG);
    if (uch & 0x80) /* 总线错误 */
    {
        /* 复位芯片 */
        uch2 = READ_REGISTER_UCHAR(base + CAN_MODE_REG);
        WRITE_REGISTER_UCHAR(base + CAN_MODE_REG, uch2 | 0x01);
        WRITE_REGISTER_UCHAR(base + CAN_MODE_REG, uch2 & 0xfe);

        /* 解决发送失败阻塞问题 */
        semGive(pCan->sem4);
        semGive(pCan->sem3);

        logMsg("fd = %d bus off reset!\n", fd, 2, 3, 4, 5, 6);

        ret = 0;
    }

    if (uch & 0x02) /* 发送完成 */
    {
        semGive(pCan->sem4);

        ret = 0;
    }

    if(uch & 0x01)
    {
        /* 读取数据拼装成一般帧格式 */
        for(i = 0; i < 13; i++)
        {
            buffer[i] = READ_REGISTER_UCHAR(base + CAN_RECV_FIFO_OFFSET + i);
        }

#if DEBUG
        logMsg("channel %d number = %d - %02X \n",
               fd, i, buffer[0], 0, 0, 0);

        logMsg("%02X %02X %02X %02X %02X %02X\n",
               buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]);

        logMsg("%02X %02X %02X %02X %02X %02X\n",
               buffer[7], buffer[8], buffer[9], buffer[10], buffer[11], buffer[12]);
#endif

        if (rngIsFull(pCan->ring))
        {
            logMsg("channel %d 's soft fifo is full. Now flush.\n", fd, 0, 0, 0, 0, 0);
            rngFlush(pCan->ring);
        }

        /* 放入软件FIFO */
        ret = rngBufPut(pCan->ring, (char *)buffer, sizeof(buffer));

        /* 释放SJA1000接收缓存 */
        WRITE_REGISTER_UCHAR(base + CAN_CTRL_REG, 0x04);
    }

    return ret;
}

/********************************************************************
函数名称:   InitSja

函数功能:   初始化SJA1000芯片

参数名称        类型                输入/输出           含义
*pCan           pcican_sja1000_t    input               设备结构体
pConfig         sja1000_config_t*   input               配置信息结构体

返回值  :   0:成功 非0:失败

函数说明:   can芯片初始化函数，通过ioctl_pcican调用

修改记录:   2014-06-25  李世杰  创建
            2015-11-25  徐佳谋  升级    增加参数
********************************************************************/
int InitSja(pcican_sja1000_t *pCan, sja1000_config_t *pConfig)
{
    int ret = 0;
    unsigned long base;

    /* 保证访问互斥 */
    semTake(pCan->mutex, WAIT_FOREVER);

    /* 获取基地址 */
    base = pCan->base;

    /* 开始进入reset模式配置 */
    WRITE_REGISTER_UCHAR(base + CAN_MODE_REG, 0x01);

    if ((READ_REGISTER_UCHAR(base + CAN_MODE_REG) & 0x01) == 0x00)
    {
        return -1;
    }

    WRITE_REGISTER_UCHAR(base + 31, pConfig->uchCDR);    /* 0xc4 set clock divider PELICAN MODE */
    WRITE_REGISTER_UCHAR(base + 8, pConfig->uchOCR);     /* 0xda set output control */

    /* 设置波特率 */
    WRITE_REGISTER_UCHAR(base + 6, pConfig->uchBTR0);
    WRITE_REGISTER_UCHAR(base + 7, pConfig->uchBTR1);

    /* 设置错误门限 */
    WRITE_REGISTER_UCHAR(base + 13, pConfig->uchEWLR);

    /*清除错误计数器*/
    WRITE_REGISTER_UCHAR(base + 14, 0);
    WRITE_REGISTER_UCHAR(base + 15, 0);

    /*以下code 和 mask 设置是在扩展的can的reset模式下的设置值，在operat模式下无效*/
    WRITE_REGISTER_UCHAR(base + 16, pConfig->uchACR[0]);
    WRITE_REGISTER_UCHAR(base + 17, pConfig->uchACR[1]);
    WRITE_REGISTER_UCHAR(base + 18, pConfig->uchACR[2]);
    WRITE_REGISTER_UCHAR(base + 19, pConfig->uchACR[3]);
    WRITE_REGISTER_UCHAR(base + 20, pConfig->uchAMR[0]);
    WRITE_REGISTER_UCHAR(base + 21, pConfig->uchAMR[1]);
    WRITE_REGISTER_UCHAR(base + 22, pConfig->uchAMR[2]);
    WRITE_REGISTER_UCHAR(base + 23, pConfig->uchAMR[3]);

    /* 使能需求的中断 */
    WRITE_REGISTER_UCHAR(base + 4, pConfig->uchIER);

    /* 进入正常模式 */
    WRITE_REGISTER_UCHAR(base + 0, pConfig->uchMOD & 0xfe);

    if ((READ_REGISTER_UCHAR(base + 0) & 0x01) == 0x01)
    {
        ret = -2;
    }

    /* 释放互斥 */
    semGive(pCan->mutex);

    return ret;
}

/********************************************************************
函数名称:   ShowPciCan

函数功能:   显示驱动信息

参数名称        类型            输入/输出           含义
index           int             input               设备描述符

返回值  :   0:成功 非0:失败

函数说明:   函数显示驱动当前寄存器值，调试时使用。

修改记录:   2014-06-26  李世杰  创建
********************************************************************/
int ShowPciCan(int index)
{
    int i = 0;
    unsigned long base = 0;
    pcican_device_t *pDevice = NULL;
    pcican_sja1000_t *pCan = NULL;

    if (index >= MAX_DEVICE_NUM)
    {
        return -1;
    }

    /* 确认设备有效 */
    pDevice = &g_devices[index];

    printf("PCICAN Device information: index = %d\n", index);

    printf("ulBase0 = 0x%08X, ulBase2 = 0x%08X, ulSize = 0x%08X\n", pDevice->ulBase0, pDevice->ulBase2, pDevice->ulSize);

    printf("irq = %d, version = %s\n", pDevice->irq, GetPciCan(index));

    /* 读取2个通道的中断状态与FIFO状态 */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        pCan = &g_sja1000s[i];
        base = pCan->base;

        WRITE_REGISTER_UCHAR(base + 0, 0x00);

        printf("base = 0x%08X, mod = 0x%02X, sr = 0x%02X, ir = 0x%02X, ier = 0x%02X\n", base,
               READ_REGISTER_UCHAR(base + 0) & 0x1F, READ_REGISTER_UCHAR(base + 2), READ_REGISTER_UCHAR(base + 3), READ_REGISTER_UCHAR(base + 4));
    }

    return 0;
}

/********************************************************************
函数名称:   GetPciCan

函数功能:   获取软件和FPGA版本号

参数名称        类型                输入/输出           含义
index           int                 input               设备描述符

返回值  :   软件和FPGA版本信息字符串。

函数说明:   为了区分各种软件和FPGA版本，增加版本信息函数。

修改记录:   2016-06-17  徐佳谋  创建
********************************************************************/
char *GetPciCan(int index)
{
    pcican_device_t *pDevice = NULL;

    /* 防止参数错误 获取设备结构体指针 */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* 判断是否已经映射地址 */
    if(pDevice->ulBase2 == 0)
    {
        return 0;
    }

    sprintf(s_versions, "CD6020 VxWorks 6.8.3 SMP G0044V12 PLX9056 FPGA = 0x%02X", READ_REGISTER_UCHAR(pDevice->ulBase0 + 0x32F));

    return s_versions;
}
