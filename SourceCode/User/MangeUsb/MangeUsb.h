/********************************************************************
文件名称:   ReadCan.h

文件功能:   USB文件拷贝头文件

文件说明:   当U盘插入当板卡usb口时，msc驱动会发送一个消息，这部分功为自
            己添加。需要注意消息的格式必须为长度为10的数组，否则曾在问题。

当前版本:   V1.0

修改记录:   2016-06-23  V1.0    王  明    创建
********************************************************************/
#ifndef _MANGEUSB_H_
#define _MANGEUSB_H_

#pragma pack(1)

#define USB_QMSG_TASK_PRIORITY          111         /* 任务优先级 */
#define USB_TASK_STACK_SIZE             (1024 * 10) /* 任务堆栈 */
#define XCOPY_DELAY_TIME                2          /* 单位s */


#ifdef __cplusplus
extern "C" {
#endif

extern int CreatMangeUsbModule(void);
extern int RemoveMangeUsbModule(void);

#ifdef __cplusplus
}
#endif


#endif
