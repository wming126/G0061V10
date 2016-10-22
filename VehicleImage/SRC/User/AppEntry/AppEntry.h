/********************************************************************
文件名称:   AppEntry.h

文件功能:   应用层入口头文件

文件说明:   该文件包含入口函数，入口函数为AppEntry，程序固化时在usrAp
            pInit.c usrAppInit函数调用

当前版本:   V1.0

修改记录:   2016-07-05  V1.0    王  明  创建
********************************************************************/
#ifndef _APP_ENTRY_H_
#define _APP_ENTRY_H_

#include "..\SRC\Driver\rtc\RtcLib.h"
#include "..\SRC\User\CanModule\CanModule.h"
#include "..\SRC\User\ManageFile\MangeFile.h"
#include "..\SRC\User\IoCtModule\IoCntModule.h"
#include "..\SRC\User\MangeUsb\MangeUsb.h"

#define VEHICLE_PRGRAM_VERSION      "Vehicle data collection V1.0"

#ifdef __cplusplus
extern "C" {
#endif

extern int AppEntry(void);
extern int AppDelete(void);

#ifdef __cplusplus
}
#endif


#endif
