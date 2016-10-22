/********************************************************************
文件名称:   IoCtModule.c

文件功能:   IO口定时器模块

文件说明:   该功能模块完成IO口定时器数据读取，然后解析数据并封装为IoCtQmsg_t
            结构，通过vxworks的消息机制发送给文件管理模块。当串口协议解析
            使用超时模式时会在tCntComSync函数中调用RecvCom()函数。

当前版本:   V1.0

修改记录:   2016-07-06  V1.0    王  明  创建
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
#include "wdLib.h"
#include "PciCanLib.h"
#include "..\SRC\Driver\iocnt\PciIoCntLib.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "IoCntModule.h"
#include "..\SRC\User\ComModule\ComModule.h"

#define IO_CNT_DEBUG        0

int s_IoCntTid = 0;

MSG_Q_ID g_IoCntMsgID;


/* 局部函数声明 */
static int ReadIoCntCallBack(int fd);
int tCntComSync(void *para);

/********************************************************************
函数名称:   RemoveIoCntModule

函数功能:   移除IOCNT功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   移除IOCNT功能模块

修改记录:   2016-06-20  王  明    创建
********************************************************************/
int RemoveIoCntModule(void)
{
    int ret = 0;

    /* 删除创建的任务 */
    if(s_IoCntTid > 0)
    {
        taskDelete(s_IoCntTid);
    }
    
    /* 删除创建的消息 */
    if(g_IoCntMsgID != NULL)
    {
        msgQDelete(g_IoCntMsgID);
    }
    
    ret = ClosePciIoCnt(0);
    if(ret != 0)
    {
        return ret;
    }
    
    ret = RemovePciIoCnt(0);
    if(ret != 0)
    {
        return ret;
    }

    return ret;   /* 成功返回0 */
}

/********************************************************************
函数名称:   CreatIoCntModule

函数功能:   创建IOCNT功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   创建IOCNT功能模块

修改记录:   2016-06-20  王  明    创建
********************************************************************/
int CreatIoCntModule(void)
{
    int ret = 0;

    ret = CreatePciIoCnt(0);
    if(ret != 0)
    {
        goto Exit;
    }

    ret = OpenPciIoCnt(0);
    if(ret != 0)
    {
        goto Exit;
    }

    g_IoCntMsgID = msgQCreate(IOCNT_MAX_QMSG, sizeof(IoCntQmsg_t), MSG_Q_FIFO);
    if(g_IoCntMsgID == NULL)
    {
        goto Exit;  /* 创建失败回收资源 */
    }

    /* 创建CAN接收任务 */
    s_IoCntTid = taskSpawn("tCntComSync", IO_INT_RECV_TASK_PRIORITY, 0, IO_INT_RECV_TASK_STACK_SIZE, tCntComSync, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_IoCntTid == ERROR)
    {
        goto Exit;  /* 创建失败回收资源 */
    }

    return 0;   /* 成功返回0 */

Exit:
    RemoveIoCntModule();
    return ERROR;
}

/********************************************************************
函数名称:   ReadIoCntCallBack

函数功能:   计数器口数据读取任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   计数器口数据读取任务
并计数
修改记录:   2016-06-20  王  明    创建
********************************************************************/
static int ReadIoCntCallBack(int fd)
{
    char time[50] = {'\0'};
    IoCntQmsg_t IoCntMsg;
    unsigned char uch;
    unsigned short cnt;
    unsigned short cnt2;
    unsigned short delta1;
    unsigned short delta2;
    static unsigned short s_cnt = 0;
    static unsigned short s_cnt2 = 0;

    memset(&IoCntMsg, 0, sizeof(IoCntQmsg_t));

    /* 获取当前系统时间 */
    GetTime(time, 3);

    sprintf(IoCntMsg.time, "%s", time);

    /* 读脉冲 */
    cnt = ReadPciCnt(0, 0);

    /* 处理翻转 */
    if (cnt >= s_cnt)
    {
        delta1 = cnt - s_cnt;
    }
    else
    {
        delta1 = 0xFFFF - s_cnt + cnt + 1;
    }
    s_cnt = cnt;
    
    /* IoCntMsg.cnt1 = delta1; */
    IoCntMsg.delta1 = delta1;
    IoCntMsg.cnt1 = cnt;


    /* 读脉冲 */
    cnt2 = ReadPciCnt(0, 1);
    
    /* 处理翻转 */
    if (cnt2 >= s_cnt2)
    {
        delta2 = cnt2 - s_cnt2;
    }
    else
    {
        delta2 = 0xFFFF - s_cnt2 + cnt2 + 1;
    }
    s_cnt2 = cnt2;

    IoCntMsg.delta2 = delta2;
    IoCntMsg.cnt2 = cnt2;


    uch = ReadPciIo(0, InPort2);

    /* bit0 为 io1 */
    IoCntMsg.io1 = uch & 0x01;
    /* bit1 为 io2 */
    IoCntMsg.io2 = (uch >> 1) & 0x01;

#if 0
    printf("IoCntMsg.io1 = %d IoCntMsg.io2 = %d ch = %d\n", IoCntMsg.io1, IoCntMsg.io2, uch);
#endif
    
    msgQSend(g_IoCntMsgID, (char *)&IoCntMsg, sizeof(IoCntQmsg_t), NO_WAIT, 0);

    return 0;
}

/********************************************************************
函数名称:   tCntComSync

函数功能:   中断等待任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   任务等待驱动触发事件(接收到数据)，接收数据，检查并计数

修改记录:   2016-05-03  李世杰  创建
********************************************************************/
int tCntComSync(void *para)
{
    int ret = 0;
    int startFlag = 0;

    for (;;)
    {
        /* 等待同步信号触发中断，必须判断<0的情况 */
        if (WaitPciIo(0, WAIT_FOREVER) < 0)
        {
            logMsg("tCntComSync run error WaitPciIo!\n", 0 , 0, 0, 0, 0, 0);
            break;
        }

        if(startFlag != 1)
        {
            ret += StartPciCnt(0, 0);
            ret += StartPciCnt(0, 1);
            if(ret >= 0)
            {
                startFlag = 1;
            }
        }

        /* 同步信号到来，开始读取计数器数据 */
        ReadIoCntCallBack(0);

#if (COM_FRAME_ANALYZE_MODE == 1)
        RecvCom();
#endif
    } /* end for;; */

    return 0;
}
