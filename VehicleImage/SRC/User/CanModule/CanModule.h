/********************************************************************
�ļ�����:   ReadCan.h

�ļ�����:   CAN����ģ��ͷ�ļ�

�ļ�˵��:   ���ļ�����ģ�鷢����Ϣ������ɼ���ֻ����Ϣ�ṹ����ϢID��
            ģ�鴴��������ģ���Ƴ�������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-06-20  V1.0    ��  ��  ����
********************************************************************/
#ifndef _READCAN_H_
#define _READCAN_H_

#pragma pack(1)

#define MAX_CAN                 2
#define CAN_TASK_PRIORITY       110 /* �������ȼ� */

#define CAN_MAX_QMSG            1000    /* ��Ϣ���г��� */
#define CAN_MODULE_STACK_SIZE   (1024 * 100)

#define CAN_BAUD_RATE           BAUDRATE_250K

/* CAN0�����˲��� */
#define CAN0_ACR0           0x70
#define CAN0_ACR1           0x60
#define CAN0_ACR2           0x00
#define CAN0_ACR3           0x00
/* #define CAN0_AMR0           0x00 */
#define CAN0_AMR0           0xE0
#define CAN0_AMR1           0x1f
#define CAN0_AMR2           0xff
#define CAN0_AMR3           0xff

/* CAN1�����˲��� */
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

/* ���͸��ļ�����ģ�����ϢID */
extern MSG_Q_ID g_CanMsgID[MAX_CAN];

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatCanModule();        /* canģ���ʼ������ */
extern int RemoveCanModule(void);   /* �Ƴ�Can����ģ�� */

#ifdef __cplusplus
}
#endif


#endif
