/* usrAppInit.c - stub application initialization routine */

/* Copyright (c) 1998,2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,16mar06,jmt  Add header file to find USER_APPL_INIT define
01a,02jun98,ms   written
*/

/*
DESCRIPTION
Initialize user application code.
*/ 

#include <vxWorks.h>
#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif /* defined PRJ_BUILD */

#include "..\SRC\User\AppEntry\AppEntry.h"
#include "stdio.h"
#include "ioLib.h"
#include "taskLib.h"
#include <usb2/usb2Helper.h>
#include "dirent.h"
#include "stat.h"

#define INCLUDE_APP_ENTRY   1

extern int sysIchAtaWait();

/******************************************************************************
*
* usrAppInit - initialize the users application
*/ 

void usrAppInit (void)
    {
#if INCLUDE_APP_ENTRY
    int ret = 0;
#endif
    
#ifdef  USER_APPL_INIT
    USER_APPL_INIT;     /* for backwards compatibility */
#endif
    /* add application specific code here */
    
    /* 必须在这里调用，等待硬盘设备初始化完成 */
    sysIchAtaWait();

#if INCLUDE_APP_ENTRY

    
    /* 应用层入口函数 */
    ret = AppEntry();
    
    if(ret < 0) 
    {
        printf("Can not run AppEntry ret = %d\n", ret);
    }
    
#endif
    
    }


