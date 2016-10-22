/********************************************************************
�ļ�����:   ReadCan.h

�ļ�����:   �ļ�����ģ��ͷ�ļ�

�ļ�˵��:   �ù���ģ���������ģ�飨can�ڡ����ڡ�IO������������������Ϣ
            ������������Ϣд���ļ���

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-06-23  V1.0    ��  ��    ����
********************************************************************/
#ifndef _MANGEFILE_H_
#define _MANGEFILE_H_

#include "..\SRC\User\CanModule\CanModule.h"
#include "..\SRC\User\IoCtModule\IoCntModule.h"
#include "..\SRC\User\ComModule\ComModule.h"

#pragma pack(1)

/* #define QMSG_TIME_OUT               (1 * sysClkRateGet()) */
#define QMSG_TIME_OUT                  (WAIT_FOREVER)

#define CAN_QMSG_TASK_PRIORITY          111         /* �������ȼ� */

#define IO_QMSG_TASK_PRIORITY           111         /* �������ȼ� */

#define CNT_QMSG_TASK_PRIORITY          111         /* �������ȼ� */

#define COM_QMSG_TASK_PRIORITY          111         /* �������ȼ� */

#define CAN_TASK_STACK_SIZE             (1024 * 100) /* �����ջ */

#define IO_TASK_STACK_SIZE              (1024 * 100) /* �����ջ */

#define CNT_TASK_STACK_SIZE             (1024 * 100) /* �����ջ */

#define COM_TASK_STACK_SIZE             (1024 * 100) /* �����ջ */

/* #define CAN_FILE_PATH                "/ata0a/VehicleLog/can/" */
#define ALL_FILE_PATA                   "/ata0a/DATA"   /* ��ʱ���� */
#define CAN_FILE_PATH                   "/ata0a/DATA"   /* ��ʱ���� */
#define IO_FILE_PATH                    "/ata0a/DATA"   /* ��ʱ���� */
#define CNT_FILE_PATH                   "/ata0a/DATA"   /* ��ʱ���� */
#define COM_FILE_PATH                   "/ata0a/DATA"   /* ��ʱ���� */

#define SIGAL_FILE_MAX_SIZE             2147483647      /* �ļ���С���Ϊ2147483647 (1024 * 1024 * 1024 * 2 - 1 = 2147483647) */

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatMangeFileModule(void);
extern int RemoveMangeFileModule(void);

#ifdef __cplusplus
}
#endif


#endif
