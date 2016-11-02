/********************************************************************
文件名称:   ComModule.h

文件功能:   串口功能模块源文件

文件说明:   该功能模块完成串口口数据读取，然后解析数据并封装为ComQmsg_t
            结构，通过vxworks的消息机制发送给文件管理模块。该模块协议解析
            函数需要在IoCntModule模块中调用（超时模式下）。

当前版本:   V1.0

修改记录:   2016-07-14  V1.0    王  明  创建
            2016-08-14  V1.1    周绍兴  修改 完善串口协议解析使其健壮
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
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "ComModule.h"
#include "tickLib.h"
#include "rngLib.h"

/* 宏定义 */
#define COM_MODULE_DEBUG    0

#if (COM_FRAME_ANALYZE_MODE == 0)
static int s_ComTid = 0;
#endif

MSG_Q_ID g_ComMsgID = NULL;
static int s_ComFd = 0;

/* 串口名称 板载串口1-8 */
char *s_ComName[] =
{
    "/tyCo/0", "/tyCo/1", "/tyCo/2", "/tyCo/3"
};


/* 局部函数声明 */
static int InitCom(int comNum, int BaudRate);
BOOL RecvAnalyzeComData(int fd);
#if (COM_FRAME_ANALYZE_MODE == 0)
static int tComRecv(int fd);
#endif

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
int InitCom(int comNum, int BaudRate)
{
    int ret = 0;
    int fd = 0;

    fd = open(s_ComName[comNum % 8], O_RDWR, 0);

    if(fd == ERROR)
    {
        printf("%s open faild!\n", s_ComName[comNum % 8]);
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
函数名称:   RemoveComModule

函数功能:   移除串口功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   函数删除串口功能模块创建的任务和消息

修改记录:  2016-07-14  王  明    创建
********************************************************************/
int RemoveComModule(void)
{
#if (COM_FRAME_ANALYZE_MODE == 0)
    if(s_ComTid > 0)
    {
        taskDelete(s_ComTid);
    }
#endif

    if(g_ComMsgID != NULL)
    {
        msgQDelete(g_ComMsgID);
    }

        if(s_ComFd > 0)
    {
        close(s_ComFd);
    }

    return 0;
}

/********************************************************************
函数名称:   CreatComModule

函数功能:   初始化Com功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   初始化Com功能模块，函数在AppEntry文件的AppEntry函数调用。

修改记录:   2016-07-14  王  明    创建
********************************************************************/
int CreatComModule(void)
{
    /* 初始化串口*/
    s_ComFd = InitCom(TYCO_COM0, COM_BAUD_RATE);
    if(s_ComFd < 0)
    {
        goto Exit;
    }

#if (COM_FRAME_ANALYZE_MODE == 0)
    /* 创建串口接收任务 */
    s_ComTid = taskSpawn("tComRecv", COM_TASK_PRIORITY, 0, COM_MODULE_STACK_SIZE,
                         (FUNCPTR)tComRecv, s_ComFd, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_ComTid == ERROR)
    {
        printf("tComRecv creat faild!\n");
        goto Exit;
    }
#endif

    /* 创建串口模块使用的消息 */
    g_ComMsgID = msgQCreate(COM_MAX_QMSG, sizeof(ComQmsg_t), MSG_Q_FIFO);
    if(g_ComMsgID == NULL)
    {
        goto Exit;
    }

    return 0;   /* 成功返回0 */

Exit:
    RemoveComModule();
    return ERROR;
}

/********************************************************************
函数名称:   ReadComEx

函数功能:   串口读取超时返回函数

参数名称        类型            输入/输出           含义
fd              int             input               串口文件描述符
buffer          char*           input               读取缓冲区指针
maxbytes        size_t          input               读取最大字节数
pTimeOut        struct timeval* input               超时信息结构体

返回值  :   -1:操作失败 0:超时 1-maxbytes:返回的数据

函数说明:   使用select为read函数添加超时，在徐佳谋ReadComEx函数基础上移植

修改记录:   2016-08-12  周绍兴 修改  使用select为read函数添加超时
********************************************************************/
int ReadComEx(int fd, char *buffer, size_t maxbytes, struct timeval *pTimeOut)
{
    int ret = 0;
    fd_set fdset;

    /* 设置文件描述符集合 */
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);

    /* 使用select函数判断串口状态 */
    ret = select(fd + 1, &fdset, NULL, NULL, pTimeOut);
    if (ret <= 0)
        return ret;
    /* 判断当前串口是否有数据可读 */
    if (FD_ISSET(fd, &fdset))
    {
        ret = read(fd, buffer, maxbytes);
        return ret;
    }

    return -1;
}

/********************************************************************
函数名称:   CheckComSum

函数功能:   计算校验和

参数名称        类型            输入/输出           含义
pBuffer         const char *    input               需要计算校验和的数据
size            unsigned int    input               计算校验和数据个数

返回值  :   0:成功 非0:失败

函数说明:   计算8bit校验，该函数从ipmb程序移植，具体校验和还要和客户
            使用方式一致。

修改记录:   2016-07-14  王  明    创建
            2016-08-14  周绍兴    修改  结合用户协议修改校验和程序
********************************************************************/
unsigned char CheckComSum(const char *pBuffer, unsigned int size)
{
    int i = 0;
    unsigned int sum = 0;

    for(i = 0; i < size; i++)
    {
        sum += *(pBuffer + i);
    }

    return (char)sum;
}


#if (COM_FRAME_ANALYZE_MODE == 1)
/********************************************************************
函数名称:   AnalyzeComFrame

函数功能:   解析串帧中的数据并生成消息

参数名称        类型            输入/输出           含义
buffer          char *          input               BUFFER
ComQmsg_t *     msg             output              返回消息结构

返回值  :   0:成功 非0:失败(-2:校验和错误，-1：未找到一个帧)

函数说明:   解析串帧中的数据并生成消息，移植注意处理器大小端问题
            unsigned int num    数据包计数
            unsigned int ax     X陀螺仪数据
            unsigned int ay     y陀螺仪数据
            unsigned int az     z陀螺仪数据
            unsigned int wx     x加表仪数据
            unsigned int wy     y加表数据
            unsigned int wz     z加表数据
            unsigned short temp 温度

修改记录:   2016-07-14  王  明    创建
            2016-08-12  周绍兴    修改  函数解析接收的串口帧
            2016-10-22  王  明    修改  客户协议修改增加mems陀螺数据
********************************************************************/
static int AnalyzeComFrame(unsigned char *buffer, unsigned int buffersize, ComQmsg_t *msg)
{
    unsigned char *pHeader = NULL;
    unsigned int header = 0;
    unsigned char checkSum = 0;
    int ret = -1;

#if 0
    printf("\n--------------AnalyzeComFrame-----------------\n");
    printf("AnalyzeComFrame run \n");
    printf("\n----------------------------------------------\n");
#endif

    /* 移植注意处理器大小端问题 */
    pHeader = buffer;
    while(buffersize - (pHeader - buffer) >= COM_MAX_FRAME_SIZE)
    {
        header = *((unsigned int *) pHeader);

        /* 判断帧头帧帧尾 */
        if(header == 0x55555555)
        {
            /* 计算校验和 */
            checkSum = CheckComSum((const char *)pHeader, (COM_MAX_FRAME_SIZE - 1));

            if(checkSum != pHeader[COM_MAX_FRAME_SIZE - 1])
            {
                /* 和校验错误 */
                msg->num = -1;
                msg->fog_gx = -1;
                msg->fog_gy = -1;
                msg->fog_gz = -1;
                
                msg->mems_gx = -1;
                msg->mems_gy = -1;
                msg->mems_gz = -1;
                
                msg->ax = -1;
                msg->ay = -1;
                msg->az = -1;

                msg->temp = -1;
                ret = -2;

                pHeader++;
            }
            else
            {
                /* 具体数据解析按客户协议,目前只是简单的赋值 */
                msg->num = *(int *)(pHeader + 4);
                msg->fog_gx =  *(int *)(pHeader + 8);
                msg->fog_gy = *(int *)(pHeader + 12);
                msg->fog_gz = *(int *)(pHeader + 16);
                
                msg->mems_gx = *(int *)(pHeader + 20);
                msg->mems_gy = *(int *)(pHeader + 24);
                msg->mems_gz = *(int *)(pHeader + 28);
                
                msg->ax = *(int *)(pHeader + 32);
                msg->ay = *(int *)(pHeader + 36);
                msg->az = *(int *)(pHeader + 40);
                
                msg->temp = *(short *)(pHeader + 44);
                ret = 0;
                break;
            }
        }
        else
        {
#if 0
            printf("Data header Error!\n");
#endif
            pHeader++;
        }
    }
    if (-1 == ret)
    {
        /* 找不到帧 */
        msg->num = -2;
        msg->fog_gx = -2;
        msg->fog_gy = -2;
        msg->fog_gz = -2;
        
        msg->mems_gx = -2;
        msg->mems_gy = -2;
        msg->mems_gz = -2;
        
        msg->ax = -2;
        msg->ay = -2;
        msg->az = -2;

        msg->temp = -2;
    }

    return ret;
}


/********************************************************************
函数名称:   RecvCom

函数功能:   超时接收串口数据

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   超时接收串口数据，该函数应该在IO中断产生时调用。目前串口协议
            解析采用两种方式该。第一种方式为在IO中断产生时通过超时读取
            串口数据，该方式的好处是可以实现与计数器时间的同步。第二种
            方式为创建一个任务一直查询接收数据，该方式优点是稳定移植性
            高。两种方式各有利弊，使用结合实际情况。本函数为第一种方式
            的核心函数。

修改记录:   2016-08-12  周绍兴    创建   函数解析接收的串口帧
            2016-10-22  王  明    修改  客户协议修改增加mems陀螺数据
********************************************************************/
BOOL RecvCom(void)
{
    int ret;
    int Received = 0;
    unsigned char RxBuffer[4096] = {0};
    ComQmsg_t ComQmsg;
    struct timeval timeout;
    char time[24];
    int flag = 99;

    /* 设置超时时间 */
    timeout.tv_sec = 0;         /* 0 单位s */
    timeout.tv_usec =  3000;   /* 单位us */

    long starttime = tickGet();
    long lefttime = 3;

    unsigned char *pData =  RxBuffer;
    BOOL errFlag = FALSE;

#if 0
    printf("\n------------------ComRecv---------------------\n");
    printf("ComRecv func run!\n");
    printf("\n----------------------------------------------\n");
#endif

    /* 获取当前系统时间 */
    GetTime(time, 3);
    sprintf(ComQmsg.time, "%s", time);

    taskDelay(4);

    /* 打印接收数据 */
    do
    {
        /* read函数为阻塞性函数 */
        timeout.tv_sec = 0;         /* 0 单位s */
        timeout.tv_usec = lefttime  * 1000;
        if (pData - RxBuffer + COM_MAX_FRAME_SIZE >= sizeof(RxBuffer))
        {
#if COM_MODULE_DEBUG
            printf("ERROR: (pData - RxBuffer + COM_MAX_FRAME_SIZE >= sizeof(RxBuffer) \n");
#endif
            break;
        }

        Received = ReadComEx(s_ComFd, (char *)pData, COM_MAX_FRAME_SIZE, &timeout);

        /* 超时 */
        if(Received >= COM_MAX_FRAME_SIZE)
        {
            pData += Received;
            errFlag = FALSE;
#if 0
            printf("Received == COM_MAX_FRAME_SIZE\n");
#endif
            break;
        }
        else if(Received == 0)
        {
            flag = Received;
#if 0
            printf("timeout: ReadComEx \n");
#endif
            break;
        }
        else if(Received < 0)
        {
            flag = Received;
            errFlag = TRUE;
#if COM_MODULE_DEBUG
            printf("ERROR: ReadComEx \n");
#endif
            break;
        }

        pData += Received;
        lefttime = 3 - (tickGet() - starttime);
    }
    while (lefttime <= 3);

#if 0
    /* 打印原始数据 */
    printf("\n------------------ComRecv--------------------\n");
    int i;
    for(i = 0; i < (pData - RxBuffer); i++)
    {
        printf("%-#4x ", RxBuffer[i]);
        if(i % 17 == 16)
        {
            printf("\n");
        }
    }
    printf("\n----------------------------------------------\n");
#endif

    /* 解析数据 */
    if ((pData - RxBuffer) >= COM_MAX_FRAME_SIZE)
    {
        ret = AnalyzeComFrame(RxBuffer, (pData - RxBuffer), &ComQmsg);
    }
    else
    {
        /* 接收失败 */
        ComQmsg.num = -3;
        ComQmsg.fog_gx = -3;
        ComQmsg.fog_gy = -3;
        ComQmsg.fog_gz = -3;
        
        ComQmsg.mems_gx = -3;
        ComQmsg.mems_gy = -3;
        ComQmsg.mems_gz = -3;
        
        ComQmsg.ax = -3;
        ComQmsg.ay = -3;
        ComQmsg.az = -3;

        ComQmsg.temp = -3;
    }

    /* 发送消息 */
    msgQSend(g_ComMsgID, (char *)&ComQmsg, sizeof(ComQmsg_t), NO_WAIT, MSG_PRI_NORMAL);

    /* todo 存串口原始数据 */

    return errFlag;
}
#endif

#if (COM_FRAME_ANALYZE_MODE == 0)
/********************************************************************
函数名称:   RecvAnalyzeComData

函数功能:   查询接受数据并解析数据

参数名称        类型            输入/输出           含义
fd              int             input               串口fd

返回值  :   0:成功 非0:失败

函数说明:   查询接受数据并解析数据，该函数应该创建一个任务循调用。目前
            串口协议解析采用两种方式该。第一种方式为在IO中断产生时通过
            超时读取串口数据，该方式的好处是可以实现与计数器时间的同步。
            第二种方式为创建一个任务一直查询接收数据，该方式优点是稳定
            移植性高。两种方式各有利弊，使用结合实际情况。本函数为第二
            种方式的核心函数。

修改记录:   2016-08-11  王  明    创建
            2016-08-12  周绍兴    修改
            2016-10-22  王  明    修改  客户协议修改增加mems陀螺数据
********************************************************************/
BOOL RecvAnalyzeComData(int fd)
{
    int i = 0;
    int ret = 0;
    int Received = 0;
    unsigned char RxBuffer[COM_MAX_FRAME_SIZE * 10] = {0}; /* 防止越界设置10帧大小 */
    unsigned char *pBuffer = RxBuffer;

    int datalen = 0;
    char time[24] = {'\0'};
    char length = 0;

    unsigned char *pHeader = NULL;
    unsigned int header = 0;
    unsigned char checkSum = 0;

    ComQmsg_t ComQmsg;
    struct timeval timeout;

    /* 设置超时时间 */
    timeout.tv_sec = 0;         /* 0 单位s */
    timeout.tv_usec =  4000;    /* 单位us */

    while(1)
    {
        /* Received = ReadComEx(fd, (char*)pBuffer, COM_MAX_FRAME_SIZE, &timeout); */
        Received = read(fd, (char *)pBuffer, COM_MAX_FRAME_SIZE);

        if(Received > 0)
        {
            pBuffer += Received;
            datalen = pBuffer - RxBuffer;
            if (datalen > 4)
            {
                for(i = 0; i < datalen - 4; i++)
                {
                    /* datalen-4是考虑了帧头未接收完的情况 */
                    /* 找帧头 */
                    if((*((int *)&RxBuffer[i]) == 0x55555555))
                        break;
                }

                if(i > 0)
                {
                    /* 丢弃不是帧头的数据 */
                    datalen -= i;
                    memmove(RxBuffer, RxBuffer + i, datalen);
                    pBuffer = RxBuffer + datalen;
                }
            }
            /* 开始处理帧数据 */
            if (datalen >= COM_MAX_FRAME_SIZE)
            {
                /* 获取当前系统时间 */
                length = GetTime(time, 3);
                sprintf(ComQmsg.time, "%s", time);

                pHeader = RxBuffer;
                ret = -1;
                while(datalen - (pHeader - RxBuffer) >= COM_MAX_FRAME_SIZE)
                {
                    header = *((unsigned int *) pHeader);

                    /* 判断帧头帧帧尾 */
                    if(header == 0x55555555)
                    {
                        /* 计算校验和 */
                        checkSum = CheckComSum((const char *)pHeader, (COM_MAX_FRAME_SIZE - 1));

                        ComQmsg.num = *(int *)(pHeader + 4);
                        ComQmsg.fog_gx =  *(int *)(pHeader + 8);
                        ComQmsg.fog_gy = *(int *)(pHeader + 12);
                        ComQmsg.fog_gz = *(int *)(pHeader + 16);
                        
                        ComQmsg.mems_gx = *(int *)(pHeader + 20);
                        ComQmsg.mems_gy = *(int *)(pHeader + 24);
                        ComQmsg.mems_gz = *(int *)(pHeader + 28);
                        
                        ComQmsg.ax = *(int *)(pHeader + 32);
                        ComQmsg.ay = *(int *)(pHeader + 36);
                        ComQmsg.az = *(int *)(pHeader + 40);
                        
                        ComQmsg.temp = *(short *)(pHeader + 44);

                        if(checkSum != pHeader[COM_MAX_FRAME_SIZE - 1])
                        {
                            /* 和校验错误 */
                            printf("Check sum Error:(calc=%x,src =%x)!\n", checkSum, pHeader[COM_MAX_FRAME_SIZE - 1]);

                            /* 和校验错误 */
                            ComQmsg.num = -1;
                            ComQmsg.fog_gx = -1;
                            ComQmsg.fog_gy = -1;
                            ComQmsg.fog_gz = -1;
                            
                            ComQmsg.mems_gx = -1;
                            ComQmsg.mems_gy = -1;
                            ComQmsg.mems_gz = -1;
                            
                            ComQmsg.ax = -1;
                            ComQmsg.ay = -1;
                            ComQmsg.az = -1;

                            ComQmsg.temp = -1;

                            ret = -2;
                            /* 尝试校验下一个帧头,会重新更新 pLeftdata_Pos */
                            pHeader++;
                        }
                        else
                        {
                            ret = 0;
                            pHeader += COM_MAX_FRAME_SIZE;
                            /* 继续找下一个帧 */
                        }
                    }
                    else
                    {
                        pHeader++;
                    }
                }
                if (ret == -1)
                {
                    printf("[no frame：%d] ", datalen);

                    /* 接收失败 */
                    ComQmsg.num = -3;
                    ComQmsg.fog_gx = -3;
                    ComQmsg.fog_gy = -3;
                    ComQmsg.fog_gz = -3;
                    
                    ComQmsg.mems_gx = -3;
                    ComQmsg.mems_gy = -3;
                    ComQmsg.mems_gz = -3;
                    
                    ComQmsg.ax = -3;
                    ComQmsg.ay = -3;
                    ComQmsg.az = -3;

                    ComQmsg.temp = -3;
                }

                /* 解帧后，移除已经处理的数据 */
                datalen -= (pHeader - RxBuffer);
                memmove(RxBuffer, pHeader, datalen);
                pBuffer = RxBuffer + datalen;
                /* 发送消息 */
                msgQSend(g_ComMsgID, (char *)&ComQmsg, sizeof(ComQmsg_t), NO_WAIT, MSG_PRI_NORMAL);
            }
        }
    }
}

/********************************************************************
函数名称:   tComRecv

函数功能:   数据接收任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   任务等待驱动触发事件(接收到数据)，接收数据，串口查询接收
            任务。

修改记录:   2016-07-14  王  明    创建
********************************************************************/
static int tComRecv(int fd)
{
    /* 打印接收数据 */
    for (;;)
    {
        RecvAnalyzeComData(s_ComFd);
    }

    return 0;
}
#endif












