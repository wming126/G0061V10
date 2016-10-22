/********************************************************************
�ļ�����:   ReadCan.h

�ļ�����:   USB�ļ�����ͷ�ļ�

�ļ�˵��:   ��U�̲��뵱�忨usb��ʱ��msc�����ᷢ��һ����Ϣ���ⲿ�ֹ�Ϊ��
            ����ӡ���Ҫע����Ϣ�ĸ�ʽ����Ϊ����Ϊ10�����飬�����������⡣

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-06-23  V1.0    ��  ��    ����
********************************************************************/
#ifndef _MANGEUSB_H_
#define _MANGEUSB_H_

#pragma pack(1)

#define USB_QMSG_TASK_PRIORITY          111         /* �������ȼ� */
#define USB_TASK_STACK_SIZE             (1024 * 10) /* �����ջ */
#define XCOPY_DELAY_TIME                2          /* ��λs */


#ifdef __cplusplus
extern "C" {
#endif

extern int CreatMangeUsbModule(void);
extern int RemoveMangeUsbModule(void);

#ifdef __cplusplus
}
#endif


#endif
