/********************************************************************
文件名称:   ReadCan.h

文件功能:   文件管理模块头文件

文件说明:   该功能模块接收其他模块（can口、串口、IO、计数器）发来的消息
            并将发来的消息写入文件。

当前版本:   V1.0

修改记录:   2016-06-23  V1.0    王  明    创建
********************************************************************/
#ifndef _MANGEFILE_H_
#define _MANGEFILE_H_

#include "..\SRC\User\CanModule\CanModule.h"
#include "..\SRC\User\IoCtModule\IoCntModule.h"
#include "..\SRC\User\ComModule\ComModule.h"

#pragma pack(1)

/* #define QMSG_TIME_OUT               (1 * sysClkRateGet()) */
#define QMSG_TIME_OUT                  (WAIT_FOREVER)

#define CAN_QMSG_TASK_PRIORITY          111         /* 任务优先级 */

#define IO_QMSG_TASK_PRIORITY           111         /* 任务优先级 */

#define CNT_QMSG_TASK_PRIORITY          111         /* 任务优先级 */

#define COM_QMSG_TASK_PRIORITY          111         /* 任务优先级 */

#define CAN_TASK_STACK_SIZE             (1024 * 100) /* 任务堆栈 */

#define IO_TASK_STACK_SIZE              (1024 * 100) /* 任务堆栈 */

#define CNT_TASK_STACK_SIZE             (1024 * 100) /* 任务堆栈 */

#define COM_TASK_STACK_SIZE             (1024 * 100) /* 任务堆栈 */

/* #define CAN_FILE_PATH                "/ata0a/VehicleLog/can/" */
#define ALL_FILE_PATA                   "/ata0a/DATA"   /* 临时调试 */
#define CAN_FILE_PATH                   "/ata0a/DATA"   /* 临时调试 */
#define IO_FILE_PATH                    "/ata0a/DATA"   /* 临时调试 */
#define CNT_FILE_PATH                   "/ata0a/DATA"   /* 临时调试 */
#define COM_FILE_PATH                   "/ata0a/DATA"   /* 临时调试 */

#define SIGAL_FILE_MAX_SIZE             2147483647      /* 文件大小最大为2147483647 (1024 * 1024 * 1024 * 2 - 1 = 2147483647) */

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatMangeFileModule(void);
extern int RemoveMangeFileModule(void);

#ifdef __cplusplus
}
#endif


#endif
