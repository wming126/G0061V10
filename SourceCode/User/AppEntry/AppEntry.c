/********************************************************************
文件名称:   AppEntry.c

文件功能:   应用层入口源文件

文件说明:   该文件包含入口函数，入口函数为AppEntry，程序固化时在usrAp
            pInit.c usrAppInit函数调用

当前版本:   V1.0

修改记录:   2016-07-05  V1.0    王  明  创建
********************************************************************/
#include "stdio.h"
#include "string.h"
#include "semLib.h"
#include "taskLib.h"
#include "vmLib.h"
#include "logLib.h"
#include "sysLib.h"
#include "usrFsLib.h"
#include "stat.h"

#include "..\SRC\User\AppEntry\AppEntry.h"

/* 函数声明 */
int AppDelete(void);

/********************************************************************
函数名称:   AppEntry

函数功能:   应用程序入口

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   应用程序入口，函数调用各个模块的创建函数。注意模块创建函数
            的顺序。

修改记录:   2016-07-05  V1.0    王  明  创建
********************************************************************/
int AppEntry(void)
{
    int ret = 0;

    /* 初始化系统时间 */
    InitSystemTime();

    /* 设置系统时间片为1ms */
    sysClkRateSet(1000);

    /* 添加延时等待硬盘设备创建好，否则无法进行文件操作 */
    taskDelay(1000);

    /* 打印程序版本号 */
    printf("\n________________________________________________________________\n");
    printf("%s\n", VEHICLE_PRGRAM_VERSION);
    printf("usage:if you want to exit this program please input AppDelete");
    printf("\n________________________________________________________________\n");

  
    /* 改变当前路径 */
    ret = cd(ALL_FILE_PATA);
    /* 如果进入文件夹失败以ALL_FILE_PATA为路径创建文件夹 */
    if(ret == ERROR)
    {
        printf("Can not find this %s path!\n", ALL_FILE_PATA);
        mkdir(ALL_FILE_PATA);
        printf("Now creat %s path!\n", ALL_FILE_PATA);
        ret = cd(ALL_FILE_PATA);
        if(ret == ERROR)
        {
            printf("Creat %s path faild! Please check the hard disk!\n", ALL_FILE_PATA);
            return -1;
        }
    }
    printf("Enter directory succeed!\n");

  
    /* 创建CAN功能模块 */
    ret = CreatCanModule();
    if(ret < 0)
    {
        printf("CreatCanModule faild! Plese check the can board. Now exit the program!\n");
        goto Exit;
    }
    printf("CAN module init succeed!\n");

    /* 串口模块要在IOCNT模块之前创建，因为incnt模块调用了串口的读函数 */
    ret = CreatComModule();
    if(ret < 0)
    {
        printf("CreatComModule faild! Plese check the cpu board. Now exit the program!\n");
        goto Exit;
    }
    printf("COM module init succeed!\n");
    
    /* 创建IO定时器功能模块，必须在ComModule之后创建 */
    CreatIoCntModule();
    if(ret < 0)
    {
        printf("CreatIoCntModule faild! Plese check the IOCNT board. Now exit the program!\n\n");
        goto Exit;
    }
    printf("IOCNT module init succeed!\n");
    

    /* 创建USB管理模块 */
    ret = CreatMangeUsbModule();
    if(ret < 0)
    {
        printf("CreatMangeUsbModule faild! Plese check the usb componet. Now exit the program!\n");
        goto Exit;
    }
    printf("FILE module init succeed!\n");


    /* 创建文件管理功能模块，该模块应该最后被创建 */
    ret = CreatMangeFileModule();
    if(ret < 0)
    {
        printf("CreatMangeFileModule faild! There may be some eerror\n");
        goto Exit;
    }
    printf("USB module init succeed!\n");

    return ret;
Exit:
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("AppEntry run error!");
    printf("Please check the board!");
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    AppDelete();
    return -1;
}

/********************************************************************
函数名称:   AppDelete

函数功能:   应用程序出口

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   应用程序出口，函数调用各个模块的移除函数。

修改记录:   2016-07-05  V1.0    王  明  创建
********************************************************************/
int AppDelete(void)
{
	/* 必须先移除MangeFileModule */
	RemoveMangeFileModule();
	RemoveCanModule();
    RemoveIoCntModule();
    RemoveComModule();
    RemoveMangeUsbModule();

    return 0;
}
