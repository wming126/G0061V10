/********************************************************************
文件名称:   ComModule.h

文件功能:   串口功能模块头文件

文件说明:   向文件管理模块发送消息。对外可见的只有消息结构、消息ID、
            模块创建函数、模块移除函数。

当前版本:   V1.0

修改记录:   2016-07-14  V1.0    王  明  创建
            2016-08-14  V1.1    周绍星  修改 完善串口协议解析使其健壮
********************************************************************/
#ifndef _COMMODULE_H_
#define _COMMODULE_H_

#pragma pack(1)

#define COM_FRAME_ANALYZE_MODE  1               /*1:超时接收 0：查询接收 */

#define MAX_COM                 1
#define TYCO_COM0               0
#define TYCO_COM1               1
#define COM_TASK_PRIORITY       90              /* 任务优先级 */
#define COM_MODULE_STACK_SIZE   (1024 * 100)    /* 任务堆栈 */
#define COM_BAUD_RATE           115200
#define COM_MAX_QMSG            1000            /* 消息队列长度 */

#define COM_CYCLE               ((float)(1.0/COM_BAUD_RATE))    /* 发送一个bit需要的时间单位s */
#define COM_MAX_FRAME_SIZE      38              /* 一帧数据长度 */
#define RNG_BUFFER_SIZE         (COM_MAX_FRAME_SIZE * 10)
#define COM_PER_BYTE_BIT        10              /* 串口格式为8N1时每个字节bit数为10bit */


typedef struct ComQmsg_s
{
    char time[24];
    unsigned int num;       /* 数据包计数 */
    int fog_gx;             /* fog陀螺仪数据 */
    int fog_gy;             /* fog陀螺仪数据 */
    int fog_gz;             /* fog陀螺仪数据 */
    int mems_gx;            /* mems陀螺仪数据 */
    int mems_gy;            /* mems陀螺仪数据 */
    int mems_gz;            /* mems陀螺仪数据 */
    int ax;                 /* X加表数据 */
    int ay;                 /* y加表数据 */
    int az;                 /* z加表数据 */
    short temp;             /* 温度 */
} ComQmsg_t;

/* 发送给文件管理模块的消息ID */
extern MSG_Q_ID g_ComMsgID;

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatComModule(void);    /* can模块初始化函数 */
extern int RemoveComModule(void);   /* 移除Com功能模块 */
BOOL RecvCom(void);

#ifdef __cplusplus
}
#endif


#endif
