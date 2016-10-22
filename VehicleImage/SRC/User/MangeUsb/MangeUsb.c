/********************************************************************
文件名称:   MangeFile.c

文件功能:   USB文件拷贝源文件

文件说明:   当U盘插入当板卡usb口时，msc驱动会发送一个消息，这部分功为自
            己添加。需要注意消息的格式必须为长度为10的数组，否则曾在问题。

当前版本:   V1.0

修改记录:   2016-06-23  V1.0    王  明    创建
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
#include "rngLib.h"
#include "semLib.h"
#include "sysLib.h"
#include "usrFsLib.h"
#include "stat.h"
#include "ioLib.h"
#include "..\SRC\User\ManageFile\MangeFile.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "..\SRC\Driver\iocnt\PciIoCntLib.h"
#include "MangeUsb.h"


/* 宏定义 */
#define USB_MODULE_DEBUG               1

typedef struct MangeIoCnt_s
{
    int tid;                     /* 任务ID */
    int reserve;
} MangeUsb_t;

/* 全局变量定义 */
static MangeUsb_t s_MangeUsb;

/* 外部变量声明 */
extern MSG_Q_ID g_MscHaveMountedMsgID;

/* 局部函数声明 */
int CreatUsbPath(char *usbDevsName, char *str);
int CreatMangeUsbModule(void);
int RemoveMangeFileModule(void);
static int tUsbQmsgReceive(void);
int CreatUsbPath(char *usbDevsName, char path[50]);

/********************************************************************
函数名称:   CreatUsbPath

函数功能:   在U盘中创建一个以时间为名称的文件夹

参数名称        类型            输入/输出           含义
usbDevsName     char *          input               U盘设备名称
path[]          char            output              保存创建的路径

返回值  :   0:成功 非0:失败

函数说明:   U盘插入时会以当前时间在U盘中创建一个文件夹，函数第二个
            参数返回创建的文件夹路径。

修改记录:   2016-07-06  王 明 创建
********************************************************************/
int CreatUsbPath(char *usbDevsName, char path[50])
{
    int ret = 0;
    char time[50] = {'\0'};
    char pathName[50] = {'\0'};

    /* 参数检查 */
    if(path == NULL || usbDevsName == NULL)
    {
        printf("Parameter error!\n");
        return -1;
    }

    /* 获取固定字符串格式的时间 */
    GetTime(time, 4);
    sprintf(pathName, "%s/DATA%s", usbDevsName, time);

#if USB_MODULE_DEBUG
    printf("%s\n", pathName);
#endif

    ret = mkdir(pathName);
    if(ret < 0)
    {
        return ret;
        printf("mkdir run error!\n");
    }

    sprintf(path, "%s", pathName);

    return ret;
}

/********************************************************************
函数名称:   CreatMangeUsbModule

函数功能:   初始化USB功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   初始化USB功能模块

修改记录:   2016-06-23  王  明    创建
********************************************************************/
int CreatMangeUsbModule(void)
{
    /* 清零消息结构 */
    memset((char *)&s_MangeUsb, 0x00, sizeof(MangeUsb_t));

    s_MangeUsb.tid = taskSpawn("tUsbQmsgReceive", USB_QMSG_TASK_PRIORITY, 0,
                               USB_TASK_STACK_SIZE, tUsbQmsgReceive, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_MangeUsb.tid == ERROR)
    {
        printf("tFlushAllModuleFile creat faild!\n");
        goto Exit;  /* 创建失败回收资源 */
    }

    return 0;   /* 成功返回0 */

Exit:
    /* 回收创建的资源 */
    RemoveMangeFileModule();
    return ERROR;
}

/********************************************************************
函数名称:   RemoveMangeUsbModule

函数功能:   移除USB功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   函数删除USB功能模块创建的任务

修改记录:   2016-06-23  王  明    创建
********************************************************************/
int RemoveMangeUsbModule(void)
{
    /* 删除文件刷新任务 */
    if(s_MangeUsb.tid > 0)
    {
        taskDelete(s_MangeUsb.tid);
    }

    return 0;
}

/********************************************************************
函数名称:   tUsbQmsgReceive

函数功能:   接受从Msc驱动(Mass storage)发送过来的消息

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   接受从Msc驱动(Mass storage)发送过来的消息，当U盘插入当板卡
            usb口时，msc驱动会发送一个消息，这部分功能为自己添加。需要
            注意消息的格式必须为长度为10的数组，否则曾在问题。

修改记录:   2016-06-23  王  明    创建
********************************************************************/
static int tUsbQmsgReceive(void)
{
    int i = 0;
    int nByte = 0;
    int ret = 0;

    char usbDevsName[10] = {'\0'};  /* 注意数组大小必须为10，因为usb驱动中发送的消息长度为10 */
    char usbPath[50] = {'\0'};

    for(;;)
    {
        /* 接收can功能模块发来的消息 */
        nByte = msgQReceive(g_MscHaveMountedMsgID, usbDevsName, sizeof(usbDevsName), WAIT_FOREVER);

#if USB_MODULE_DEBUG
        printf("msgQReceive ok! \n");
#endif

        CreatUsbPath(usbDevsName, usbPath);

        printf("******************************************************\n");
        printf("src:%s\n", ALL_FILE_PATA);
        printf("dest:%s\n", usbPath);
        printf("******************************************************\n");

        /* IMPORT STATUS xcopy (const char * src, const char *dest); */
        ret = xcopy(ALL_FILE_PATA, usbPath);
        if(ret == ERROR)
        {
            printf("File xcopy faild!\n");
            
            /* 数据拷贝成功亮5s会 */
            WritePciIo(0, OutPort2, 0xff);
            taskDelay(sysClkRateGet()/2);
            WritePciIo(0, OutPort2, 0x00);
            taskDelay(sysClkRateGet()/2);
            WritePciIo(0, OutPort2, 0xff);
            taskDelay(sysClkRateGet()/2);
            WritePciIo(0, OutPort2, 0x00);
            continue;
        }

        /* 拷贝完成后要延时一段时间等待U盘数据写入 */
        for(i = 0; i < XCOPY_DELAY_TIME; i++)
        {
            taskDelay(1000);
        }

        printf("******************************************************\n");
        printf("xcopy cmd run finish!\n");
        printf("Now you can remove your Mass stoarge!\n");
        printf("******************************************************\n");

        /* 数据拷贝成功亮5s会 */
        WritePciIo(0, OutPort2, 0xff);
        taskDelay(sysClkRateGet() * 5);
        WritePciIo(0, OutPort2, 0x00);

    } /* end for */
}

