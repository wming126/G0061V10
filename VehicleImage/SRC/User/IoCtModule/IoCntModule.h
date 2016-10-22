/********************************************************************
文件名称:   IoCtModule.h

文件功能:   IOCNT功能模块头文件

文件说明:   该功能模块完成IO口定时器数据读取，然后解析数据并封装为IoCtQmsg_t
            结构，通过vxworks的消息机制发送给文件管理模块

当前版本:   V1.0

修改记录:   2016-07-06  V1.0    王  明  创建
********************************************************************/
#ifndef _IOCNT_MODULE_H_
#define _IOCNT_MODULE_H_

#pragma pack(1)

#define IO_CNT_MODULE_DEBUG          0

#define IO_INT_RECV_TASK_PRIORITY           60          /* 任务优先级 */
#define IO_INT_RECV_TASK_STACK_SIZE         (1024 * 100) /* 任务堆栈 */

#define CNT_MODULE_QMSG_TASK_PRIORITY       101         /* 任务优先级 */
#define CNT_MODULE_TASK_STACK_SIZE          (1024 * 100) /* 任务堆栈 */

#define IOCNT_MAX_QMSG                      100

typedef struct CntQmsg_s
{
    char time[24];
    unsigned short cnt1;
    unsigned short cnt2;
    unsigned short delta1;
    unsigned short delta2;
    int io1;
    int io2;
} IoCntQmsg_t;

/* 发送给文件管理模块的消息ID */
extern MSG_Q_ID g_IoCntMsgID;

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatIoCntModule(void);      /* can模块初始化函数 */
extern int RemoveIoCntModule(void);     /* 移除Can功能模块 */

#ifdef __cplusplus
}
#endif

#endif
