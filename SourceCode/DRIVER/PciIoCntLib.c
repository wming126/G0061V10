/********************************************************************
文件名称:   IoCntLib.c

文件功能:   GAD64655板卡驱动程序源文件(在源板卡基础上添加了计数器)

文件说明:   GAD64655板卡驱动程序,IO板外设寄存器映射到PCI设备IO空间
            所以不需要vxworks不需要对其进行内存映射，直接访问其IO空
            间即可。该板卡在原有逻辑上升级在IN1-IN5上复用了5路计数器

当前版本:   V1.0

修改记录:   2016-07-07  V1.0    王 明 创建
            2016-08-10  V1.1    王 明 添加  添加io中断支持
********************************************************************/
#ifndef _WRS_CONFIG_SMP
#undef _WRS_CONFIG_SMP /* 双核模式 */
#endif

#include "vxWorks.h"
#include "stdio.h"
#include "ioLib.h"
#include "fcntl.h"
#include "vmLib.h"
#include "arch\I86\ivI86.h"
#include "drv\pci\pciIntLib.h"
#include "drv\pci\pciConfigLib.h"
#include "taskLib.h"
#include "sysLib.h"

#include "PciIoCntLib.h"

#define DEBUG                   0
#define PCI_IO_CNT_DEBUG        0
#define PCI_CFG_BASE_ADDRESS_0  0x10
#define CNT_READ_MODE           0       /* 0:8位读 1:16位读 */

#define IO_OUT_OFFSET           0x00
#define IO_IN_OFFSET            0x02
#define CNT_OFFSET              0x10

#define CNT_DATA_REG_OFFSET     0
#define CNT_CTRL_REG_OFFSET     2
#define CNT_STATE_REG_OFFSET    3       /* 目前逻辑未定义状态 */

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

static unsigned char s_uch;     /* 记录中断状态 */

extern void logMsg( const char *fmt, ... );

/* 保存映射的MEM地址 */
typedef struct pciio_device_s
{
    int OpenFlag;                           /* 驱动打开标志 */
    unsigned long ulBase0;                  /* PCI 映射基地址BAR0 */
    unsigned long ulSize;                   /* PCI映射地址大小BARO size */
    unsigned short IoInAddr[MAX_IN_PORT];   /* IO输入基地址，映射到IO空间 */
    unsigned short IoOutAddr[MAX_OUT_PORT]; /* IO输出基地址，映射到IO空间 */
    unsigned short CntBase[MAX_CNT_NUM];    /* 计数器基地址，映射到IO空间 */
    int irq;                                /* 中断号 */
    int tid;                                /* 中断任务ID */
    int isr;                                /* 驱动中断注册标志 */
    SEM_ID sem;                             /* 中断服务程序中使用的信号量 */
    SEM_ID sem2;               /* 应用程序使用信号量 */
} pciiocnt_device_t;

/* 全局设备结构 */
static pciiocnt_device_t s_devices[MAX_GAD64655_NUM];

int RemovePciIoCnt(int index);
int ClosePciIoCnt(int fd);
void iPciIo(void *para);
int tPciIo(void *para);


/********************************************************************
函数名称:   CreatePciIoCnt

函数功能:   创建驱动

参数名称            类型            输入/输出       含义
index               int             input           板卡索引(0,1)

返回值  :   0代表成功 非0代表失败

函数说明:   查找PCI设备，读取配置空间找到映射地址。

修改记录:   2016-07-08  王 明     创建
********************************************************************/
int CreatePciIoCnt(int index)
{
    int i = 0;
    int j = 0;
    int ret = 0;
    int BusNo;
    int DeviceNo;
    int FuncNo;
    unsigned int ul;
    pciiocnt_device_t *pDevice = NULL;

    /* 防止参数错误 获取设备结构体指针 */
    index %= MAX_GAD64655_NUM;
    pDevice = &s_devices[index];

    /* 搜索PCI设备 */
    ret = pciFindDevice(VENDOR_ID, DEVICE_ID, index, &BusNo, &DeviceNo, &FuncNo);
    if (ret == ERROR)
    {
        goto Exit;
    }

    /* 读取设备映射空间地址0 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &ul);
    if (ret == ERROR)
    {
        ret = -2;
        goto Exit;
    }

    /* 板卡映射到IO空间，PCI规范规定地址后两位（bit0 bit1）无效基地址为ul & 0xFC */
    pDevice->ulBase0 = (ul & 0xFFFFFFFC);


    /* 从dos下ru中读出，正规应该可读不可写的位决定映射空间的大小 */
    pDevice->ulSize = 0x100;

    /* 将IO计数器基地址写入设备结构中 */
    for(i = 0; i < MAX_GAD64655_NUM; i++)
    {
        for(j = 0; j < MAX_IN_PORT; j++)
        {
            pDevice->IoInAddr[j] = (pDevice->ulBase0 + IO_IN_OFFSET + j);
        }

        for(j = 0; j < MAX_OUT_PORT; j++)
        {
            pDevice->IoOutAddr[j] = (pDevice->ulBase0 + IO_OUT_OFFSET + j);
        }

        for(j = 0; j < MAX_CNT_NUM; j++)
        {
            pDevice->CntBase[j] = (pDevice->ulBase0 + CNT_OFFSET + j * 4);
        }
    }

    /* 读取设备中断号 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &ul);
    if (ret == -1)
    {
        ret = -6;
        goto Exit;
    }

    pDevice->irq = ul & 0xFF;

    /* 判断是否已经注册中断 */
    if (pDevice->isr == 1)
    {
        return 0;
    }

    /* 创建信号量 */
    pDevice->sem = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pDevice->sem == NULL)
    {
        ret = -2;
        goto Exit;
    }
    /* 创建任务 */
    pDevice->tid = taskSpawn("tPciIo", 0, (VX_SUPERVISOR_MODE | VX_UNBREAKABLE), 8192, tPciIo, (int)pDevice, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pDevice->tid == -1)
    {
        ret = -3;
        goto Exit;
    }

    /* 注册中断前要先清除中断，否则程序会进一次中断 */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) | 0x01);
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) & 0xFE);
    
    /* 注册中断服务程序 */
    ret = pciIntConnect(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciIo, (int)pDevice);
    if (ret == -1)
    {
        ret = -4;
        goto Exit;
    }
    pDevice->isr = 1;

    /* 使能中断 */
    sysIntEnablePIC(pDevice->irq);

    /* 使能中断FPGA中断 */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) | 0x01);

#if IO_INT_MODE
    /* 配置同步信号触发方式 */
    sysOutByte(pDevice -> ulBase0 + FPGA_IO_INT_MODE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_MODE) | 0x01);
#else
    sysOutByte(pDevice -> ulBase0 + FPGA_IO_INT_MODE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_MODE) & 0xFE);
#endif

    return ret;

Exit:
    RemovePciIoCnt(index);
    return ret;
}

/********************************************************************
函数名称:   RemovePciIoCnt

函数功能:   移除板卡设备驱动

参数名称            类型            输入/输出       含义
index               int             input           板卡索引(0,1)

返回值  :   0代表成功 非0代表失败

函数说明:   清除第一阶段初始化变量。

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int RemovePciIoCnt(int index)
{
    int ret = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 防止参数错误 */
    index %= MAX_GAD64655_NUM;

    /* 判断是否已经映射地址 */
    pDevice = &s_devices[index];
    if (pDevice->ulBase0 == 0)
    {
        return -1;
    }

    /* 关闭FPGA中断 */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, (sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) & 0xfe));

    if (pDevice->isr != 0)
    {
        pciIntDisconnect2(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciIo, (int)pDevice);
        pDevice->isr = 0;
    }

    if (pDevice->sem != NULL)
    {
        semDelete(pDevice->sem);
        pDevice->sem = 0;
    }

    /* 最后清零数据结构 */
    memset(&s_devices[index], 0, sizeof(pciiocnt_device_t));

    return ret;
}

/********************************************************************
函数名称:   OpenPciIoCnt

函数功能:   打开驱动

参数名称            类型            输入/输出       含义
fd                  int             input           设备索引,用于多板卡支持

返回值  :   0代表成功 非0代表失败

函数说明:   函数将驱动打开标志设置为1

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int OpenPciIoCnt(int fd)
{
    int ret = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if (pDevice->ulBase0 == 0)
    {
        printf("Pleae creat iocnt first\n");

        ret = -1;
        goto Exit;
    }


    pDevice->sem2 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pDevice->sem2 == NULL)
    {
        ret = -2;
        goto Exit;
    }

    pDevice->OpenFlag = 1;

#if PCI_IO_CNT_DEBUG
    printf("pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
#endif

    return ret;

Exit:
#if PCI_IO_CNT_DEBUG
    printf("pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
#endif
    ClosePciIoCnt(fd);

    return ret;
}

/********************************************************************
函数名称:   ClosePciIoCnt

函数功能:   关闭驱动

参数名称            类型            输入/输出       含义
fd                  int             input           IO索引

返回值  :   0代表成功 非0代表失败

函数说明:   函数将驱动打开标志设置为0

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int ClosePciIoCnt(int fd)
{
    int ret = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if (pDevice->ulBase0 == 0)
    {
        return -1;
    }


    if (pDevice->sem2 != 0)
    {
        semDelete(pDevice->sem2);
        pDevice->sem2 = 0;
    }


    pDevice->OpenFlag = 0;

    return ret;
}

/********************************************************************
函数名称:   WritePciIo

函数功能:   写IO口

参数名称            类型            输入/输出       含义
fd                  int             input           板卡索引，用于多板卡支持
port                OutPort_t       input           8bit写入数据
ch                  unsigned char   input           8bit写入数据

返回值  :   0代表成功 非0代表失败

函数说明:   向输出IO寄存器写入值。GAD64655有16路IO输出软件将其分为2个port，每个
            prot 8路IO。对应关系如下图所示。
            ------------------------------------------------------------------------
            |        bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0  |
            |PORT_1  OUT08   OUT07   OUT06   OUT05   OUT04   OUT03   OUT02   OUT01 |
            |PORT_2  OUT16   OUT15   OUT14   OUT13   OUT12   OUT11   OUT10   OUT09 |
            ------------------------------------------------------------------------

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int WritePciIo(int fd, OutPort_t port, unsigned char ch)
{
    unsigned short OutAddr = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!, pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
        return -1;
    }

    OutAddr = pDevice->IoOutAddr[port];

    sysOutByte(OutAddr, ch);

    return 0;
}

/********************************************************************
函数名称:   ReadPciIo

函数功能:   写IO口

参数名称            类型            输入/输出       含义
fd                  int             input           板卡索引，用于多板卡支持
port                InPort_t        input           GAD64655有48路IO软件将其分为6个port，每个prot 8路IO

返回值  :   8bit IO返回值

函数说明:   从输入IO寄存器读取值。GAD64655有48路IO软件将其分为6个port，每个
            prot 8路IO。对应关系如下图所示。
            ---------------------------------------------------------------------
            |        bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0|
            |PORT_0  IN08    IN07    IN06    IN05    IN04    IN03    IN02   IN01 |
            |PORT_1  IN16    IN15    IN14    IN13    IN12    IN11    IN10   IN09 |
            |PORT_2  IN24    IN23    IN22    IN21    IN20    IN19    IN18   IN17 |
            |PORT_3  IN32    IN31    IN30    IN29    IN28    IN27    IN26   IN25 |
            |PORT_4  IN40    IN39    IN38    IN37    IN36    IN35    IN34   IN33 |
            |PORT_5  IN48    IN47    IN46    IN45    IN44    IN43    IN42   IN41 |
            ---------------------------------------------------------------------

修改记录:   2016-07-08  王 明   创建
********************************************************************/
unsigned char ReadPciIo(int fd, InPort_t port)
{
    unsigned short InAddr = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!, pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
        return -1;
    }

    InAddr = pDevice->IoInAddr[port];

    return sysInByte(InAddr);
}

/********************************************************************
函数名称:   StartPciCnt

函数功能:   使能计数器开始计数

参数名称            类型            输入/输出       含义
fd                  int             input           板卡索引(0,1)
cnt_num             int             input           计数器号

返回值  :   0代表成功 非0代表失败

函数说明:   使能计数器开始计数

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int StartPciCnt(int fd, int cnt_num)
{
    unsigned char uch = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

    /* 读CNT base + 2 */
    uch = sysInByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET));

    /* CNT base + 2 为控制寄存器bit0为1时计数器开始计数为0时计数器停止计数  */
    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch | 0x01));

    return 0;
}

/********************************************************************
函数名称:   StopPciCnt

函数功能:   失能计数器，停止计数

参数名称        类型            输入/输出           含义
fd                  int             input           板卡索引(0,1)
cnt_num             int             input           计数器号

返回值  :   0:成功 非0:失败

函数说明:   失能计数器，停止计数

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int StopPciCnt(int fd, int cnt_num)
{
    unsigned char uch = 0;

    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

    /* 读CNT base + 2 */
    uch = sysInByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET));

    /* CNT base + 2 为控制寄存器bit0为1时计数器开始计数为0时计数器停止计数  */
    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch & 0xFE));

    return 0;
}

/********************************************************************
函数名称:   ReadPciCnt

函数功能:   读取计数器计数值

参数名称        类型            输入/输出           含义
fd                  int             input           板卡索引(0,1)
cnt_num             int             input           计数器号

返回值  :   0:成功 非0:失败

函数说明:   读取计数器计数值

修改记录:   2016-07-08  王 明   创建
********************************************************************/
unsigned short ReadPciCnt(int fd, int cnt_num)
{
    unsigned short cnt;

    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

#if (CNT_READ_MODE == 1)
    cnt = sysInWord((pDevice->CntBase[cnt_num] + CNT_DATA_REG_OFFSET));
#else

    /* 逻辑不完善，读计数器前要先读一下该寄存器。不知怎么想的，脑袋被门夹了 */
    sysInByte(pDevice->CntBase[cnt_num] + CNT_STATE_REG_OFFSET);
    
    cnt = (sysInByte((pDevice->CntBase[cnt_num] + CNT_DATA_REG_OFFSET) + 1) << 8) + (sysInByte((pDevice->CntBase[cnt_num] + CNT_DATA_REG_OFFSET)));

#endif

    return cnt;
}

/********************************************************************
函数名称:   ClearPciCnt

函数功能:   清除计数器计数值

参数名称        类型            输入/输出           含义
fd                  int             input           板卡索引(0,1)
cnt_num             int             input           计数器号

返回值  :   0:成功 非0:失败

函数说明:   清除计数器计数值

修改记录:   2016-07-08  王 明   创建
********************************************************************/
int ClearPciCnt(int fd, int cnt_num)
{
    unsigned char uch = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

    /* 读CNT base + 2 */
    uch = sysInByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET));

    /* CNT base + 2 为控制寄存器bit1为1时清零计数器，清零后需要软件把bit1清零才能继续计数  */
    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch | 0x02));

    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch & 0xFD));

    return 0;
}

/********************************************************************
函数名称:   WaitPciIo

函数功能:   等待PCI IO产生中断

参数名称            类型            输入/输出       含义
index               int             input           板卡索引(0,1)
timeout             int             input           信号量超时参数

返回值  :   0代表成功 非0代表失败

函数说明:   函数等待内部的一个由中断触发的信号量。

修改记录:   2016-05-03      徐佳谋  创建
********************************************************************/
int WaitPciIo(int fd, int timeout)
{
    pciiocnt_device_t *pDevice = NULL;

    /* 参数检查 */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    /* 等待信号量 */
    if (semTake(pDevice->sem2, timeout) == -1)
    {
        return -2;
    }

    return s_uch;
}

/********************************************************************
函数名称:   iPciIo

函数功能:   PCIIO板卡中断服务程序

参数名称        类型            输入/输出           含义
*para           void            input               板卡信息传递参数

返回值  :   0:成功 非0:失败

函数说明:   中断服务程序判断中断源、屏蔽中断、触发中断。
            后续的操作在后处理任务中实现。

修改记录:   2016-05-03      徐佳谋  创建
********************************************************************/
void iPciIo(void *para)
{
    unsigned char uch = 0x00;
    pciiocnt_device_t *pDevice = para;

    /* 判断是否是IO中断 */
    uch = sysInByte(pDevice->ulBase0 + FPGA_IO_INT_STATE);

    if((uch & 0X01) != 0X01)
    {
        return ;
    }

    /* 屏蔽中断 */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, (sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) & 0xfe));

    /* 触发信号量  */
    if (pDevice->sem != NULL)
    {
        semGive(pDevice->sem);
    }

    return ;
}

/********************************************************************
函数名称:   tPciIo

函数功能:   中断后处理任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   为了防止中断服务程序运行时间过长，对板卡的数据操作放在后处理
            任务中实现。

修改记录:   2016-05-03      徐佳谋  创建
********************************************************************/
int tPciIo(void *para)
{
    unsigned char uch = 0x00;
    pciiocnt_device_t *pDevice = para;

    for (;;)
    {
        if (semTake(pDevice->sem, WAIT_FOREVER) == -1)
        {
            break;
        }

        for(;;)
        {
            /* 读取中断源 */
            uch = sysInByte(pDevice->ulBase0 + FPGA_IO_INT_STATE);

#if DEBUG
            logMsg("uch = 0x%02X\n", uch, 2, 3, 4, 5, 6);
#endif
            if ((uch & 0X01) != 0X01)
            {
                break;
            }

            s_uch = uch;

            /* 清除中断 */
            sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) | 0x01);
            sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) & 0xFE);

            if (pDevice->sem2 != 0)
            {
                semGive(pDevice->sem2);
            }
        } /* end for */

        /* 恢复中断 */
        sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) | 0x01);
    }

    return 0;
}
