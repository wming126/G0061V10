/********************************************************************
文件名称:   ReadCan.h

文件功能:   CAN功能模块源文件

文件说明:   该功能模块完成CAN口数据读取，然后解析数据并封装为CanQmsg_t
            结构，通过vxworks的消息机制发送给文件管理模块

当前版本:   V1.0

修改记录:   2016-06-20  V1.0    王  明  创建
********************************************************************/
#include "semLib.h"
#include "drv\pci\pciIntLib.h"
#include "taskLib.h"
#include "stdio.h"
#include "string.h"
#include "vmLib.h"
#include "drv\pci\pciConfigLib.h"
#include "arch\I86\ivI86.h"
#include "logLib.h"
#include "sysLib.h"
#include "PciCanLib.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "CanModule.h"



/* 宏定义 */
#define CAN_MODULE_DEBUG    0

static int s_CanTid[MAX_CAN];
MSG_Q_ID g_CanMsgID[MAX_CAN];

/* 局部函数声明 */
static int InitPciCan(int fd, int BaudRate);
static int tCanReceive(int fd);
static unsigned int ConvertBufferToID(sja1000_frame_t* pframe);

/********************************************************************
函数名称:   InitPciCan

函数功能:   CAN口初始化

参数名称        类型            输入/输出           含义
fd              int             input               设备描述符(对应CAN口)
BaudRate        int             input               波特率

返回值  :   0:成功 非0:失败

函数说明:   完成CAN口初始化，在驱动基础上封装一层。

修改记录:   2016-06-20  王  明    创建
********************************************************************/
int InitPciCan(int fd, int BaudRate)
{
    sja1000_config_t config;
    int ret = 0;

    /* 防止参数错误 */
    fd = fd % 2;

    CreatePciCan2(fd);

    /* 打开设备 */
    ret = OpenPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d OpenPciCan failed!%d\n", fd, ret);
        return -1;
    }

    /* 初始化SJA1000芯片 */
    config.uchMOD    = 0x08;    /* 单滤波 */
    config.uchCDR    = 0xC4;    /* 不清楚含义时不需要修改 */
    config.uchOCR    = 0xDA;    /* 不清楚含义时不需要修改 */
    config.uchBTR0   = BaudRate >> 8;
    config.uchBTR1   = BaudRate;   /* 波特率 */
    if(fd == 0)
    {
        config.uchACR[0] = CAN0_ACR0;
        config.uchACR[1] = CAN0_ACR1;
        config.uchACR[2] = CAN0_ACR2;
        config.uchACR[3] = CAN0_ACR3;
        config.uchAMR[0] = CAN0_AMR0;
        config.uchAMR[1] = CAN0_AMR1;
        config.uchAMR[2] = CAN0_AMR2;
        config.uchAMR[3] = CAN0_AMR3;
    }
    else
    {
        config.uchACR[0] = CAN1_ACR0;
        config.uchACR[1] = CAN1_ACR1;
        config.uchACR[2] = CAN1_ACR2;
        config.uchACR[3] = CAN1_ACR3;
        config.uchAMR[0] = CAN1_AMR0;
        config.uchAMR[1] = CAN1_AMR1;
        config.uchAMR[2] = CAN1_AMR2;
        config.uchAMR[3] = CAN1_AMR3;
    }
    config.uchIER = 0x83;       /* 使能总线错误 接收数据 发送完成 必须设置为0x83 */
    config.uchRXERR = 0;
    config.uchTXERR = 0;
    config.uchEWLR = 0x60;

    /* 初始化芯片 */
    ret = IoctlPciCan(fd, IOCTL_INIT_SJA, &config);
    if (ret != 0)
    {
        printf("channel %d IoctlPciCan failed(IOCTL_INIT_SJA)!%d\n", fd, ret);
    }

    /* 清除FIFO */
    ret = FlushPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d FlushPciCan failed!%d\n", fd, ret);
    }

    return ret;
}

/********************************************************************
函数名称:   RemoveCanModule

函数功能:   移除can功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   函数删除can功能模块创建的任务和消息

修改记录:   2016-06-20  王  明    创建
********************************************************************/
int RemoveCanModule(void)
{
    int fd = 0;

    for(fd = 0; fd < MAX_CAN; fd++)
    {
        if(s_CanTid[fd] > 0)
        {
            taskDelete(s_CanTid[fd]);
        }

        if(g_CanMsgID[fd] > 0)
        {
            msgQDelete(g_CanMsgID[fd]);
        }
    }

    /* 回收第一路can创建的资源 */
    
    ClosePciCan(0);
    /* RemovePciCan(0); */
    RemovePciCan2(0);
    

    /* 回收第二路can创建的资源 */
    ClosePciCan(1);
    /* RemovePciCan(1); */
    RemovePciCan2(1);
    

    return 0;
}

/********************************************************************
函数名称:   CreatCanModule

函数功能:   初始化Can功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   初始化Can功能模块，函数在AppEntry文件的AppEntry函数调用。

修改记录:   2016-06-20  王  明    创建
********************************************************************/
int CreatCanModule(void)
{
    int fd = 0;
    int ret = 0;

    /* 初始化两CAN,并创建程序需要的资源（任务、消息）*/
    for(fd = 0; fd < MAX_CAN; fd++)
    {
        /* 初始化CAN */
        ret = InitPciCan(fd, BAUDRATE_250K);
        if(ret < 0)
        {
            goto Exit;  /* 初始化失败回收资源 */
        }

        /* 创建CAN接收任务 */
        s_CanTid[fd] = taskSpawn("tCanReceive", CAN_TASK_PRIORITY, 0, CAN_MODULE_STACK_SIZE, tCanReceive, fd, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        if(s_CanTid[fd] == ERROR)
        {
            goto Exit;  /* 创建失败回收资源 */
        }

        /* 创建消息 */
        g_CanMsgID[fd] = msgQCreate(CAN_MAX_QMSG, sizeof(CanQmsg_t), MSG_Q_FIFO);
        if(g_CanMsgID[fd] == NULL)
        {
            goto Exit;  /* 创建失败回收资源 */
        }
    }

    return 0;   /* 成功返回0 */

Exit:
    RemoveCanModule();
    return ERROR;
}

#if 0
/********************************************************************
函数名称:   ConvertIDtoBuffer

函数功能:   将int型ID转化成帧格式ID

参数名称        类型            输入/输出           含义
ID              unsigned int    input               需要转换的int型ID
pframe          sja1000_frame_t output              帧指针

返回值  :   0代表成功 非0代表失败

函数说明:   将int型ID转化成帧格式ID，并保存到发送帧结构当中

修改记录:   2016-04-29  王  明    创建
********************************************************************/
static int ConvertIDtoBuffer(unsigned int ID, sja1000_frame_t* pframe)
{
    if((pframe->header & 0x80) == 0x80) /* 扩展帧 */
    {
        /* 判断id有效性 */
        if(ID > 0x1fffffff)
        {
            printf("Id format error!\n");
            return -1;
        }
        
        ID = ID << 3;
        
        pframe->buffer[3] = (ID & 0xf8); /* 高5位有效 */
        pframe->buffer[2] = ((ID >> 8) & 0xff);
        pframe->buffer[1] = ((ID >> 16) & 0xff);
        pframe->buffer[0] = ((ID << 24) & 0xff);
    }
    else /* 标准帧 */
    {
        /* 判断id有效性 */
        if(ID > 0x7ff)
        {
            printf("Id format error!\n");
            return -1;
        }

        ID = ID << 5;
        
        pframe->buffer[1] = (ID & 0xe0);/* 高3位有效 */
        
        pframe->buffer[0] = ((ID >> 8) & 0xff);
    }
    
    return 0;
}
#endif

/********************************************************************
函数名称:   ConvertBufferToID

函数功能:   从接收的帧中提取int型ID

参数名称        类型            输入/输出           含义
pframe          sja1000_frame_t input               帧指针

返回值  :   RetID(int型ID)

函数说明:   从接收的帧中提取int型ID

修改记录:   2016-04-29  王  明    创建
********************************************************************/
static unsigned int ConvertBufferToID(sja1000_frame_t* pframe)
{
    unsigned int RetID = 0;

    if((pframe->header & 0x80) == 0x80) /* 扩展帧 */
    {
        /* 将数据直接转换到pframe数组中 */
        RetID = ((pframe->buffer[0] << 24) | (pframe->buffer[1] << 16)
                    | (pframe->buffer[2] << 8) | ((pframe->buffer[3]) & 0xf8) ) >> 3;
    }
    else /* 标准帧 */
    {
        RetID = ((pframe->buffer[0] << 8) | ((pframe->buffer[1]) & 0xe0) ) >> 5;
    }   
    
    return RetID;
}

#if 0
/********************************************************************
函数名称:   AnalyzeCanFrame

函数功能:   解析can帧中的数据并生成消息

参数名称        类型            输入/输出           含义
fd              int             input               can设备描述符
sja1000_frame_t*frame           input               can数据帧
CanQmsg_t *     msg             output              返回消息结构

返回值  :   0:成功 非0:失败

函数说明:   解析can帧中的数据并生成消息

修改记录:   2016-06-20  王  明    创建
********************************************************************/
static int AnalyzeCanFrame(int fd, sja1000_frame_t *frame, CanQmsg_t *msg)
{
    char time[24] = {'\0'};
    char length = 0;
    int CbioId = 0;

#if 0
    CbioId = ConvertBufferToID(frame);
    
    /* 软件滤除总线上的其他数据 */
    if(CbioId != 0x383 && CbioId != 0x483)
    {
        return -1;
    }


    /* 左齿轮计数 */
    if(CbioId = 0x383)
    {
        /* 将数据封装到Qmsg结构体中  */
        msg->Lnum = ((frame->buffer[5] << 8) + frame->buffer[4]);
    }


    /* 右齿轮计数 */
    if(CbioId = 0x483)
    {
        /* 将数据封装到Qmsg结构体中  */
        msg->Rnum = ((frame->buffer[5] << 8) + frame->buffer[4]);
    }


    /* 获取当前系统时间 */
    length = GetTime(time, 3);

    /* 将时间封装到Qmsg结构当中 */
    /* strncpy(msg->time, time, length + 1); */

    sprintf(msg->time, "%s", time);

    /* 将数据封装到Qmsg结构体中  */
    msg->counter = ((frame->buffer[5] << 8) + frame->buffer[4]);

    /* 保留参数 */
    msg->CBIO_ID = 0x55;

#if CAN_MODULE_DEBUG
    printf("\n------------Can module send mesg--------------\n");
    printf("msg->time:%s\n", msg->time);
    printf("msg->counter:%d\n", msg->counter);
    printf("\n----------------------------------------------\n");
#endif
#endif
    return 0;
}
#endif

/********************************************************************
函数名称:   tCanReceive

函数功能:   数据接收任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   任务等待驱动触发事件(接收到数据)

修改记录:   2016-06-20  王  明    创建
********************************************************************/
static int tCanReceive(int fd)
{
    int ret = 0;
    sja1000_frame_t frame;
    CanQmsg_t msg;
    char time[24] = {'\0'};
    int CbioId = 0;

    memset(&frame, 0x00, sizeof(frame));
    memset(&msg, 0x00, sizeof(CanQmsg_t));
    
    for(;;)
    {
        ret = ReadPciCan(fd, &frame, 10);

        if(ret <= 0)
        {
            /* 如果没有接收到数据清0结构 */
            memset(&frame, 0x00, sizeof(frame));
            continue;
        }
        else if(ret > 0)
        {
#if CAN_MODULE_DEBUG
            printf("\n------------------CAN FRAME-------------------\n");
            printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
                   fd, frame.header,
                   frame.buffer[0], frame.buffer[1], frame.buffer[2], frame.buffer[3],
                   frame.buffer[4], frame.buffer[5], frame.buffer[6], frame.buffer[7],
                   frame.buffer[8], frame.buffer[9], frame.buffer[10], frame.buffer[11]);
            printf("\n----------------------------------------------\n");
#endif

            CbioId = ConvertBufferToID(&frame);

            /* 软件滤除总线上的其他数据 */
            if(CbioId != 0x383 && CbioId != 0x483)
            {
                /* 如果没有接收到数据清0结构 */
                memset(&frame, 0x00, sizeof(frame));
                continue;
            }

            /* 左齿轮计数 */
            if(CbioId == 0x383)
            {
#if 0
                printf("CbioId = 0x383\n");
#endif
                GetTime(time, 3);
				sprintf(msg.time, "%s", time);

                /* 将数据封装到Qmsg结构体中  */
                msg.counter = ((frame.buffer[4] << 8) + frame.buffer[3]);
                msg.CBIO_ID = 0x383;

                /* 将msg消息发送给文件管理模块 */
                msgQSend(g_CanMsgID[fd], (char *)&msg, sizeof(CanQmsg_t), NO_WAIT, 0);
                
                memset(&msg, 0x00, sizeof(CanQmsg_t));
            }

            /* 右齿轮计数 */
            if(CbioId == 0x483)
            {
                GetTime(time, 3);
                sprintf(msg.time, "%s", time);
#if 0
                printf("CbioId = 0x483\n");
#endif
                
                /* 将数据封装到Qmsg结构体中  */
                msg.counter = ((frame.buffer[4] << 8) + frame.buffer[3]);
                msg.CBIO_ID = 0x483;

                /* 将msg消息发送给文件管理模块 */
                msgQSend(g_CanMsgID[fd], (char *)&msg, sizeof(CanQmsg_t), NO_WAIT, 0);

                memset(&msg, 0x00, sizeof(CanQmsg_t));
            }
        }
    } /* end for */
}
