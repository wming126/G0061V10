/********************************************************************
�ļ�����:   IoCtModule.h

�ļ�����:   IOCNT����ģ��ͷ�ļ�

�ļ�˵��:   �ù���ģ�����IO�ڶ�ʱ�����ݶ�ȡ��Ȼ��������ݲ���װΪIoCtQmsg_t
            �ṹ��ͨ��vxworks����Ϣ���Ʒ��͸��ļ�����ģ��

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-06  V1.0    ��  ��  ����
********************************************************************/
#ifndef _IOCNT_MODULE_H_
#define _IOCNT_MODULE_H_

#pragma pack(1)

#define IO_CNT_MODULE_DEBUG          0

#define IO_INT_RECV_TASK_PRIORITY           60          /* �������ȼ� */
#define IO_INT_RECV_TASK_STACK_SIZE         (1024 * 100) /* �����ջ */

#define CNT_MODULE_QMSG_TASK_PRIORITY       101         /* �������ȼ� */
#define CNT_MODULE_TASK_STACK_SIZE          (1024 * 100) /* �����ջ */

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

/* ���͸��ļ�����ģ�����ϢID */
extern MSG_Q_ID g_IoCntMsgID;

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatIoCntModule(void);      /* canģ���ʼ������ */
extern int RemoveIoCntModule(void);     /* �Ƴ�Can����ģ�� */

#ifdef __cplusplus
}
#endif

#endif
