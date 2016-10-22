/********************************************************************
�ļ�����:   ComModule.h

�ļ�����:   ���ڹ���ģ��ͷ�ļ�

�ļ�˵��:   ���ļ�����ģ�鷢����Ϣ������ɼ���ֻ����Ϣ�ṹ����ϢID��
            ģ�鴴��������ģ���Ƴ�������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-14  V1.0    ��  ��  ����
            2016-08-14  V1.1    ������  �޸� ���ƴ���Э�����ʹ�佡׳
********************************************************************/
#ifndef _COMMODULE_H_
#define _COMMODULE_H_

#pragma pack(1)

#define COM_FRAME_ANALYZE_MODE  1               /*1:��ʱ���� 0����ѯ���� */

#define MAX_COM                 1
#define TYCO_COM0               0
#define TYCO_COM1               1
#define COM_TASK_PRIORITY       90              /* �������ȼ� */
#define COM_MODULE_STACK_SIZE   (1024 * 100)    /* �����ջ */
#define COM_BAUD_RATE           115200
#define COM_MAX_QMSG            1000            /* ��Ϣ���г��� */

#define COM_CYCLE               ((float)(1.0/COM_BAUD_RATE))    /* ����һ��bit��Ҫ��ʱ�䵥λs */
#define COM_MAX_FRAME_SIZE      38              /* һ֡���ݳ��� */
#define RNG_BUFFER_SIZE         (COM_MAX_FRAME_SIZE * 10)
#define COM_PER_BYTE_BIT        10              /* ���ڸ�ʽΪ8N1ʱÿ���ֽ�bit��Ϊ10bit */


typedef struct ComQmsg_s
{
    char time[24];
    unsigned int num;       /* ���ݰ����� */
    int fog_gx;             /* fog���������� */
    int fog_gy;             /* fog���������� */
    int fog_gz;             /* fog���������� */
    int mems_gx;            /* mems���������� */
    int mems_gy;            /* mems���������� */
    int mems_gz;            /* mems���������� */
    int ax;                 /* X�ӱ����� */
    int ay;                 /* y�ӱ����� */
    int az;                 /* z�ӱ����� */
    short temp;             /* �¶� */
} ComQmsg_t;

/* ���͸��ļ�����ģ�����ϢID */
extern MSG_Q_ID g_ComMsgID;

#ifdef __cplusplus
extern "C" {
#endif

extern int CreatComModule(void);    /* canģ���ʼ������ */
extern int RemoveComModule(void);   /* �Ƴ�Com����ģ�� */
BOOL RecvCom(void);

#ifdef __cplusplus
}
#endif


#endif
