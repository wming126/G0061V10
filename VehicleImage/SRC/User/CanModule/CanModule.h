/********************************************************************
文件名称:   ReadCan.h

文件功能:   CAN功能模块头文件

文件说明:   向文件管理模块发送消息。对外可见的只有消息结构、消息ID、
            模块创建函数、模块移除函数。

当前版本:   V1.0

修改记录:   2016-06-20  V1.0    王  明  创建
********************************************************************/
#ifndef _READCAN_H_
#define _READCAN_H_

#pragma pack(1)

#define MAX_CAN                 2
#define CAN_TASK_PRIORITY       110 /* 任务优先级 */

#define CAN_MAX_QMSG            1000    /* 消息队列长度 */
#define CAN_MODULE_STACK_SIZE   (1024 * 100)

#define CAN_BAUD_RATE           BAUDRATE_250K

/* CAN0接收滤波器 */
#define CAN0_ACR0           0x70
#define CAN0_ACR1           0x60
#define CAN0_ACR2           0x00
#define CAN0_ACR3           0x00
/* #define CAN0_AMR0           0x00 */
#define CAN0_AMR0           0xE0
#define CAN0_AMR1           0x1f
#define CAN0_AMR2           0xff
#define CAN0_AMR3           0xff

/* CAN1接收滤波器 */
#define CAN1_ACR0           0x90
#define CAN1_ACR1           0x60
#define CAN1_ACR2           0x00
#define CAN1_ACR3           0x00
/* #define CAN1_AMR0           0x00 */
#define CAN1_AMR0           0xE0
#define CAN1_AMR1           0x1f
#define CAN1_AMR2           0xff
#define CAN1_AMR3           0xff

typedef struct CanQmsg_s
{
    char time[24];
    unsigned short counter;
    unsigned short CBIO_ID;
} CanQmsg_t;

/* 发送给文件管理模块的消息ID */
extern MSG_Q_ID g_CanMsgID[MAX_CAN];

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatCanModule();        /* can模块初始化函数 */
extern int RemoveCanModule(void);   /* 移除Can功能模块 */

#ifdef __cplusplus
}
#endif


#endif
