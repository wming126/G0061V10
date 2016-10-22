/********************************************************************
文件名称:   TestIoCt.c

文件功能:   测试基于PCI总线的IO口驱动

文件说明:   IO板外设寄存器映射到PCI设备IO空间

当前版本:   V1.0

修改记录:   2016-07-07  V1.0    王 明 创建
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
#include "ioLib.h"
#include "selectLib.h"
#include "tickLib.h"
#include "rngLib.h"
#include "PciIoCntLib.h"
#include "wdLib.h"

#pragma pack(1)

static int s_tid = 0;
static unsigned int g_IntCnt = 0;   /* 中断计数 */
static WDOG_ID s_wdId = NULL;  /* 看门狗ID */
static int s_stop = 0;
static FILE *g_fp = NULL;
static MSG_Q_ID g_MsgQId;

typedef struct TestCntQmsg_s
{
    unsigned short cnt1;
    unsigned short cnt2;
    unsigned short delta1;
    unsigned short delta2;
} TestCntQmsg_t;

/* defines */
#define MAX_MSGS (10)
#define MAX_MSG_LEN (100)


static int tIoReceive2(void);
static void watch_dog_callback(int tick);
static int TestCt(void);
static int GetKeyInput(int radix);
static int TestIoInput(void);
static int InitCom(int comNum, int BaudRate);
static int TestIoOutput(void);
static int tCtFile(void);

/********************************************************************
函数名称:   TestPciIoCnt

函数功能:   测试IOCNT驱动

参数名称            类型            输入/输出       含义

返回值  :   0代表成功 非0代表失败

函数说明:   测试IOCNT驱动,测试程序入口

修改记录:   2016-07-08  王 明     创建
********************************************************************/
int TestPciIoCnt(void)
{
    int input = 0;
    int i = 0;
    int ComFd = 0;
    int ret = 0;
    unsigned char TxBuffer[2] = {0xF0,0xF0};
    unsigned int IntCnt = 0;
    unsigned int com = 0;
    int file_tid = 0;
    
    s_stop = 0;

    CreatePciIoCnt(0);

    OpenPciIoCnt(0);

    for(;; input = 0)
    {
        printf("\n"
               "1.  Test IO input \n"
               "2.  Test IO outpit \n"
               "3.  Test CNT\n"
               "4.  IO INT\n"
               "99. Exit \n");

        /* 用户输入 */
        printf("Your choice: %d\n", input = GetKeyInput(10));


        switch (input)
        {
        case 1:
            TestIoInput();
            break;

        case 2:
            TestIoOutput();
            break;

        case 3:
            /* create message queue */
            if ((g_MsgQId = msgQCreate (500, sizeof(TestCntQmsg_t), MSG_Q_PRIORITY)) == NULL)
                return (ERROR);

            g_fp = fopen("/ata0a/CT.txt", "w+");
            if (g_fp == NULL)
            {
                printf("fopen failed!\n");
                return 0;
            }
            
            file_tid = taskSpawn("tCtFile", 100, 0, 8192, tCtFile, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            
            ret = TestCt();
            
            printf("return = %d\n", ret);
            
            if(ret == 0)
            {
                printf("The cnt data is record to /ata0a/CT.TXT\n");
            }
            break;

        case 4:
            printf("Please input using witch COM to test.(0:COM1 1:COM2 2:COM3 3:COM4)\n");
            com = GetKeyInput(10) % 4;
        
            ComFd = InitCom(com, 300);
            
            /* 创建输入IO中断响应任务 */
            s_tid = taskSpawn("tIoReceive2", 100, 0, 8192, tIoReceive2,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

            printf("Please input test times (1-10000)\n");
            IntCnt = GetKeyInput(10) % 10000;

            for(i = 0; i < IntCnt; i++)
            {
                write(ComFd, (char *)TxBuffer, 1);
                taskDelay(sysClkRateGet()/1000*83);
            }
            
            taskDelay(sysClkRateGet());

            if(g_IntCnt == IntCnt)
            {
                printf("*******OK*******\n");
                printf("g_IntCnt = %u\n", g_IntCnt);
                printf("****************\n");
                
                g_IntCnt = 0;
            }
            else
            {
                printf("------ERROR-----\n");
                printf("g_IntCnt = %u\n", g_IntCnt);
                printf("----------------\n");
                
                g_IntCnt = 0;
            }

            close(ComFd);
            break;

        case 99:
            s_stop = 1;
            goto Exit;
            break;

        default:
            printf("Invalid input, retry!\n");
            break;
        }
    }

Exit:
    if(s_tid > 0)
    {
        taskDelete(s_tid);
    }

    if(file_tid > 0)
    {
        taskDelete(file_tid);
    }

    if(g_fp != NULL)
    {
        fclose(g_fp);
    }

    /* 删除创建的消息 */
    if(g_MsgQId != NULL)
    {
        msgQDelete(g_MsgQId);
    }

    ClosePciIoCnt(0);
    RemovePciIoCnt(0);


    return 0;
}

/********************************************************************
函数名称:   GetKeyInput

函数功能:   获取键盘输入

参数名称        类型            输入/输出           含义
radix           int             input               输入数据进制(10:十进制 16:十六进制)

返回值  :   键盘输入字符转换后的十进制值或十六进制值。

函数说明:   理论上可以用scanf获取用户输入
            但是scanf函数当用户输入错误的数据时会出现异常，进而导致程序异常
            不利于程序健壮性，所以写一个函数替换。函数可应用于VxWorks和Linux

修改记录:   2010-10-27  徐佳谋  创建
            2015-07-10  王明    修改    修改16进制计算问题
********************************************************************/
static int GetKeyInput(int radix)
{
    char input = 0;
    int value = 0;

    if (radix == 10)
    {
        while((input = getchar()) != 0x0a)
        {
            value = value * 10 + (input - 0x30);  /* 转换成十进制数 */
        }
    }
    else
    {
        while((input = getchar()) != 0x0a)
        {
            if (input <= 0x39)
            {
                input -= 48;
            }
            else if (input <= 0x46)
            {
                input -= 55;
            }
            else
            {
                input -= 87;
            }
            value = (value << 4) + input;  /* 转换成十六进制数 */
        }
    }

    return value;
}

/********************************************************************
函数名称:   TestIoInput

函数功能:   测试IO输入

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   测试IO输入

修改记录:   2016-07-08  王 明     创建
********************************************************************/
static int TestIoInput(void)
{
    int i = 0;
    unsigned char uch = 0;

    printf("\n");
    for(i = 0; i < MAX_IN_PORT; i++)
    {
        uch = ReadPciIo(0, (InPort1 + i));

        printf("IN_PORT%d:%-4#x", i, uch);
    }
    printf("\n");

    return 0;
}

/********************************************************************
函数名称:   InitCom

函数功能:   COM口初始化

参数名称        类型            输入/输出           含义
comNum          int             input               对应串口(1-8)
BaudRate        int             input               波特率

返回值  :   0:成功 非0:失败

函数说明:   完成串口初始化，在驱动基础上封装一层。数据位8位 停止位1位
            无校验 本地模式

修改记录:   2016-07-14  王  明    创建
********************************************************************/
static int InitCom(int comNum, int BaudRate)
{
    int ret = 0;
    int fd = 0;
    
    /* 串口名称 板载串口1-8 */
    char *ComName[] =
    {
        "/tyCo/0", "/tyCo/1", "/tyCo/2", "/tyCo/3"
    };

    fd = open(ComName[comNum % 8], O_RDWR, 0);

    if(fd == ERROR)
    {
        printf("%s open faild!\n", ComName[comNum % 8]);
        return -1;
    }

    /* 数据位8位 停止位1位 奇校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CREAD | CS8);
    ret += ioctl(fd, FIOBAUDRATE, BaudRate);    /* 波特率 */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOFLUSH, 0);              /* 清空缓冲区 */

    return fd;
}

/********************************************************************
函数名称:   TestIoOutput

函数功能:   测试IO输出

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   测试IO输出

修改记录:   2016-07-08  王 明     创建
********************************************************************/
static int TestIoOutput(void)
{
    static unsigned char io_out = 0xff;

    io_out = ~io_out;

    WritePciIo(0, OutPort2, io_out);

    return 0;
}

/********************************************************************
函数名称:   tIoReceive2

函数功能:   数据接收任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   任务等待驱动触发事件(接收到数据)，接收数据，检查并计数

修改记录:   2016-05-03  李世杰  创建
********************************************************************/
static int tIoReceive2(void)
{
    for (;;)
    {
        /* 必须进行判断 */
        if (WaitPciIo(0, WAIT_FOREVER) < 0)
        {
            logMsg("tCntComSync run error WaitPciIo!\n", 0 , 0, 0, 0, 0, 0);
            break; 
        }

        g_IntCnt++;
    } /* end for;; */

    return 0;
}

/********************************************************************
函数名称:   tCtFile

函数功能:   功能测试函数2

参数名称            类型            输入/输出       含义
tick                int             input           看门狗周期tick数

返回值  :   0代表成功 非0代表失败

函数说明:   单次外部产生脉冲，然后驱动技术值。

修改记录:   2016-06-13      徐佳谋  创建
********************************************************************/
static int tCtFile(void)
{
    TestCntQmsg_t CntQmsg;

    for(;;)
    {
        msgQReceive(g_MsgQId, (char *)&CntQmsg, sizeof(TestCntQmsg_t), WAIT_FOREVER);

        fprintf(g_fp, "CNT1 = %08d delta1 = %08d CNT2 = %08d delta2 = %08d\n", 
            CntQmsg.cnt1, CntQmsg.delta1, CntQmsg.cnt2, CntQmsg.delta2);
    }
}

/********************************************************************
函数名称:   TestCt

函数功能:   功能测试函数2

参数名称            类型            输入/输出       含义
tick                int             input           看门狗周期tick数

返回值  :   0代表成功 非0代表失败

函数说明:   单次外部产生脉冲，然后驱动技术值。

修改记录:   2016-06-13      徐佳谋  创建
********************************************************************/
static int TestCt(void)
{
    int tick = 0;
    
    /* 创建看门狗定时器 */
    s_wdId = wdCreate();
    if (s_wdId == NULL)
    {
        printf("wdCreate failed!\n");
        return -1;
    }

    printf("Input counter read cycle(1 - 999 ms) default 5ms\n");
    tick = GetKeyInput(10) % 1000;
    if (tick == 0)
    {
        tick = 5;
    }

    /* 清零计数器 */
    ClearPciCnt(0, 0);
    ClearPciCnt(0, 1);
    
    /* 启动计数器 */
    StartPciCnt(0, 0);
    StartPciCnt(0, 1);
    
    /* 启动看门狗 */
    wdStart(s_wdId, tick, (FUNCPTR)watch_dog_callback, tick);

    return 0;
}

/********************************************************************
函数名称:   watch_dog_callback

函数功能:   看门狗回调函数

参数名称            类型            输入/输出       含义
tick                int             input           看门狗周期tick数

返回值  :   0代表成功 非0代表失败

函数说明:   周期读取计数值，比较有无大的差值

修改记录:   2016-06-13      徐佳谋  创建
********************************************************************/
static void watch_dog_callback(int tick)
{
    int i = 0;
    TestCntQmsg_t CntQmsg;
    unsigned short cnt[2];
    unsigned short delta[2];
    static unsigned short s_cnt[2];

    if (s_stop == 0)
    {
        /* 重复触发看门狗 */
        wdStart(s_wdId, tick, (FUNCPTR)watch_dog_callback, tick);
    }
    else
    {
        /* 删除看门狗 */
        wdDelete(s_wdId);
    }

    for(i = 0; i < 2; i++)
    {
        /* 读脉冲 */
        cnt[i] = ReadPciCnt(0, i);

        /* 处理翻转 */
        if (cnt[i] >= s_cnt[i])
        {
            delta[i] = cnt[i] - s_cnt[i];
        }
        else
        {
            delta[i] = 0xFFFF - s_cnt[i] + cnt[i] + 1;
        }
        s_cnt[i] = cnt[i];
        
        if(i == 0)
        {
            CntQmsg.cnt1 = cnt[i];
            CntQmsg.delta1 = delta[i];
        }
        else
        {
            CntQmsg.cnt2 = cnt[i];
            CntQmsg.delta2 = delta[i];
        }
    }

    msgQSend(g_MsgQId, (char*)&CntQmsg, sizeof(TestCntQmsg_t), NO_WAIT, MSG_PRI_NORMAL);

    return ;
}

