/********************************************************************
�ļ�����:   IoCtModule.c

�ļ�����:   IO�ڶ�ʱ��ģ��

�ļ�˵��:   �ù���ģ�����IO�ڶ�ʱ�����ݶ�ȡ��Ȼ��������ݲ���װΪIoCtQmsg_t
            �ṹ��ͨ��vxworks����Ϣ���Ʒ��͸��ļ�����ģ�顣������Э�����
            ʹ�ó�ʱģʽʱ����tCntComSync�����е���RecvCom()������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-06  V1.0    ��  ��  ����
********************************************************************/
#include "semLib.h"
#include "drv\pci\pciIntLib.h"
#include "taskLib.h"
#include "stdio.h"
#include "string.h"
#include "vmLib.h"
#include "drv\pci\pciConfigLib.h"
#include "arch\I86\ivI86.h"
#include "logLib.h"
#include "sysLib.h"
#include "wdLib.h"
#include "PciCanLib.h"
#include "..\SRC\Driver\iocnt\PciIoCntLib.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "IoCntModule.h"
#include "..\SRC\User\ComModule\ComModule.h"

#define IO_CNT_DEBUG        0

int s_IoCntTid = 0;

MSG_Q_ID g_IoCntMsgID;


/* �ֲ��������� */
static int ReadIoCntCallBack(int fd);
int tCntComSync(void *para);

/********************************************************************
��������:   RemoveIoCntModule

��������:   �Ƴ�IOCNT����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �Ƴ�IOCNT����ģ��

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
int RemoveIoCntModule(void)
{
    int ret = 0;

    /* ɾ������������ */
    if(s_IoCntTid > 0)
    {
        taskDelete(s_IoCntTid);
    }
    
    /* ɾ����������Ϣ */
    if(g_IoCntMsgID != NULL)
    {
        msgQDelete(g_IoCntMsgID);
    }
    
    ret = ClosePciIoCnt(0);
    if(ret != 0)
    {
        return ret;
    }
    
    ret = RemovePciIoCnt(0);
    if(ret != 0)
    {
        return ret;
    }

    return ret;   /* �ɹ�����0 */
}

/********************************************************************
��������:   CreatIoCntModule

��������:   ����IOCNT����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����IOCNT����ģ��

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
int CreatIoCntModule(void)
{
    int ret = 0;

    ret = CreatePciIoCnt(0);
    if(ret != 0)
    {
        goto Exit;
    }

    ret = OpenPciIoCnt(0);
    if(ret != 0)
    {
        goto Exit;
    }

    g_IoCntMsgID = msgQCreate(IOCNT_MAX_QMSG, sizeof(IoCntQmsg_t), MSG_Q_FIFO);
    if(g_IoCntMsgID == NULL)
    {
        goto Exit;  /* ����ʧ�ܻ�����Դ */
    }

    /* ����CAN�������� */
    s_IoCntTid = taskSpawn("tCntComSync", IO_INT_RECV_TASK_PRIORITY, 0, IO_INT_RECV_TASK_STACK_SIZE, tCntComSync, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_IoCntTid == ERROR)
    {
        goto Exit;  /* ����ʧ�ܻ�����Դ */
    }

    return 0;   /* �ɹ�����0 */

Exit:
    RemoveIoCntModule();
    return ERROR;
}

/********************************************************************
��������:   ReadIoCntCallBack

��������:   �����������ݶ�ȡ����

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �����������ݶ�ȡ����
������
�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
static int ReadIoCntCallBack(int fd)
{
    char time[50] = {'\0'};
    IoCntQmsg_t IoCntMsg;
    unsigned char uch;
    unsigned short cnt;
    unsigned short cnt2;
    unsigned short delta1;
    unsigned short delta2;
    static unsigned short s_cnt = 0;
    static unsigned short s_cnt2 = 0;

    memset(&IoCntMsg, 0, sizeof(IoCntQmsg_t));

    /* ��ȡ��ǰϵͳʱ�� */
    GetTime(time, 3);

    sprintf(IoCntMsg.time, "%s", time);

    /* ������ */
    cnt = ReadPciCnt(0, 0);

    /* ����ת */
    if (cnt >= s_cnt)
    {
        delta1 = cnt - s_cnt;
    }
    else
    {
        delta1 = 0xFFFF - s_cnt + cnt + 1;
    }
    s_cnt = cnt;
    
    /* IoCntMsg.cnt1 = delta1; */
    IoCntMsg.delta1 = delta1;
    IoCntMsg.cnt1 = cnt;


    /* ������ */
    cnt2 = ReadPciCnt(0, 1);
    
    /* ����ת */
    if (cnt2 >= s_cnt2)
    {
        delta2 = cnt2 - s_cnt2;
    }
    else
    {
        delta2 = 0xFFFF - s_cnt2 + cnt2 + 1;
    }
    s_cnt2 = cnt2;

    IoCntMsg.delta2 = delta2;
    IoCntMsg.cnt2 = cnt2;


    uch = ReadPciIo(0, InPort2);

    /* bit0 Ϊ io1 */
    IoCntMsg.io1 = uch & 0x01;
    /* bit1 Ϊ io2 */
    IoCntMsg.io2 = (uch >> 1) & 0x01;

#if 0
    printf("IoCntMsg.io1 = %d IoCntMsg.io2 = %d ch = %d\n", IoCntMsg.io1, IoCntMsg.io2, uch);
#endif
    
    msgQSend(g_IoCntMsgID, (char *)&IoCntMsg, sizeof(IoCntQmsg_t), NO_WAIT, 0);

    return 0;
}

/********************************************************************
��������:   tCntComSync

��������:   �жϵȴ�����

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ȴ����������¼�(���յ�����)���������ݣ���鲢����

�޸ļ�¼:   2016-05-03  ������  ����
********************************************************************/
int tCntComSync(void *para)
{
    int ret = 0;
    int startFlag = 0;

    for (;;)
    {
        /* �ȴ�ͬ���źŴ����жϣ������ж�<0����� */
        if (WaitPciIo(0, WAIT_FOREVER) < 0)
        {
            logMsg("tCntComSync run error WaitPciIo!\n", 0 , 0, 0, 0, 0, 0);
            break;
        }

        if(startFlag != 1)
        {
            ret += StartPciCnt(0, 0);
            ret += StartPciCnt(0, 1);
            if(ret >= 0)
            {
                startFlag = 1;
            }
        }

        /* ͬ���źŵ�������ʼ��ȡ���������� */
        ReadIoCntCallBack(0);

#if (COM_FRAME_ANALYZE_MODE == 1)
        RecvCom();
#endif
    } /* end for;; */

    return 0;
}
