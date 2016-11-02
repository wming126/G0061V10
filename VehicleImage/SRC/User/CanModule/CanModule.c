/********************************************************************
�ļ�����:   ReadCan.h

�ļ�����:   CAN����ģ��Դ�ļ�

�ļ�˵��:   �ù���ģ�����CAN�����ݶ�ȡ��Ȼ��������ݲ���װΪCanQmsg_t
            �ṹ��ͨ��vxworks����Ϣ���Ʒ��͸��ļ�����ģ��

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-06-20  V1.0    ��  ��  ����
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
#include "PciCanLib.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "CanModule.h"



/* �궨�� */
#define CAN_MODULE_DEBUG    0

static int s_CanTid[MAX_CAN];
MSG_Q_ID g_CanMsgID[MAX_CAN];

/* �ֲ��������� */
static int InitPciCan(int fd, int BaudRate);
static int tCanReceive(int fd);
static unsigned int ConvertBufferToID(sja1000_frame_t* pframe);

/********************************************************************
��������:   InitPciCan

��������:   CAN�ڳ�ʼ��

��������        ����            ����/���           ����
fd              int             input               �豸������(��ӦCAN��)
BaudRate        int             input               ������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ���CAN�ڳ�ʼ���������������Ϸ�װһ�㡣

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
int InitPciCan(int fd, int BaudRate)
{
    sja1000_config_t config;
    int ret = 0;

    /* ��ֹ�������� */
    fd = fd % 2;

    CreatePciCan2(fd);

    /* ���豸 */
    ret = OpenPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d OpenPciCan failed!%d\n", fd, ret);
        return -1;
    }

    /* ��ʼ��SJA1000оƬ */
    config.uchMOD    = 0x08;    /* ���˲� */
    config.uchCDR    = 0xC4;    /* ���������ʱ����Ҫ�޸� */
    config.uchOCR    = 0xDA;    /* ���������ʱ����Ҫ�޸� */
    config.uchBTR0   = BaudRate >> 8;
    config.uchBTR1   = BaudRate;   /* ������ */
    if(fd == 0)
    {
        config.uchACR[0] = CAN0_ACR0;
        config.uchACR[1] = CAN0_ACR1;
        config.uchACR[2] = CAN0_ACR2;
        config.uchACR[3] = CAN0_ACR3;
        config.uchAMR[0] = CAN0_AMR0;
        config.uchAMR[1] = CAN0_AMR1;
        config.uchAMR[2] = CAN0_AMR2;
        config.uchAMR[3] = CAN0_AMR3;
    }
    else
    {
        config.uchACR[0] = CAN1_ACR0;
        config.uchACR[1] = CAN1_ACR1;
        config.uchACR[2] = CAN1_ACR2;
        config.uchACR[3] = CAN1_ACR3;
        config.uchAMR[0] = CAN1_AMR0;
        config.uchAMR[1] = CAN1_AMR1;
        config.uchAMR[2] = CAN1_AMR2;
        config.uchAMR[3] = CAN1_AMR3;
    }
    config.uchIER = 0x83;       /* ʹ�����ߴ��� �������� ������� ��������Ϊ0x83 */
    config.uchRXERR = 0;
    config.uchTXERR = 0;
    config.uchEWLR = 0x60;

    /* ��ʼ��оƬ */
    ret = IoctlPciCan(fd, IOCTL_INIT_SJA, &config);
    if (ret != 0)
    {
        printf("channel %d IoctlPciCan failed(IOCTL_INIT_SJA)!%d\n", fd, ret);
    }

    /* ���FIFO */
    ret = FlushPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d FlushPciCan failed!%d\n", fd, ret);
    }

    return ret;
}

/********************************************************************
��������:   RemoveCanModule

��������:   �Ƴ�can����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ɾ��can����ģ�鴴�����������Ϣ

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
int RemoveCanModule(void)
{
    int fd = 0;

    for(fd = 0; fd < MAX_CAN; fd++)
    {
        if(s_CanTid[fd] > 0)
        {
            taskDelete(s_CanTid[fd]);
        }

        if(g_CanMsgID[fd] > 0)
        {
            msgQDelete(g_CanMsgID[fd]);
        }
    }

    /* ���յ�һ·can��������Դ */
    
    ClosePciCan(0);
    /* RemovePciCan(0); */
    RemovePciCan2(0);
    

    /* ���յڶ�·can��������Դ */
    ClosePciCan(1);
    /* RemovePciCan(1); */
    RemovePciCan2(1);
    

    return 0;
}

/********************************************************************
��������:   CreatCanModule

��������:   ��ʼ��Can����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʼ��Can����ģ�飬������AppEntry�ļ���AppEntry�������á�

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
int CreatCanModule(void)
{
    int fd = 0;
    int ret = 0;

    /* ��ʼ����CAN,������������Ҫ����Դ��������Ϣ��*/
    for(fd = 0; fd < MAX_CAN; fd++)
    {
        /* ��ʼ��CAN */
        ret = InitPciCan(fd, BAUDRATE_250K);
        if(ret < 0)
        {
            goto Exit;  /* ��ʼ��ʧ�ܻ�����Դ */
        }

        /* ����CAN�������� */
        s_CanTid[fd] = taskSpawn("tCanReceive", CAN_TASK_PRIORITY, 0, CAN_MODULE_STACK_SIZE, tCanReceive, fd, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        if(s_CanTid[fd] == ERROR)
        {
            goto Exit;  /* ����ʧ�ܻ�����Դ */
        }

        /* ������Ϣ */
        g_CanMsgID[fd] = msgQCreate(CAN_MAX_QMSG, sizeof(CanQmsg_t), MSG_Q_FIFO);
        if(g_CanMsgID[fd] == NULL)
        {
            goto Exit;  /* ����ʧ�ܻ�����Դ */
        }
    }

    return 0;   /* �ɹ�����0 */

Exit:
    RemoveCanModule();
    return ERROR;
}

#if 0
/********************************************************************
��������:   ConvertIDtoBuffer

��������:   ��int��IDת����֡��ʽID

��������        ����            ����/���           ����
ID              unsigned int    input               ��Ҫת����int��ID
pframe          sja1000_frame_t output              ָ֡��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��int��IDת����֡��ʽID�������浽����֡�ṹ����

�޸ļ�¼:   2016-04-29  ��  ��    ����
********************************************************************/
static int ConvertIDtoBuffer(unsigned int ID, sja1000_frame_t* pframe)
{
    if((pframe->header & 0x80) == 0x80) /* ��չ֡ */
    {
        /* �ж�id��Ч�� */
        if(ID > 0x1fffffff)
        {
            printf("Id format error!\n");
            return -1;
        }
        
        ID = ID << 3;
        
        pframe->buffer[3] = (ID & 0xf8); /* ��5λ��Ч */
        pframe->buffer[2] = ((ID >> 8) & 0xff);
        pframe->buffer[1] = ((ID >> 16) & 0xff);
        pframe->buffer[0] = ((ID << 24) & 0xff);
    }
    else /* ��׼֡ */
    {
        /* �ж�id��Ч�� */
        if(ID > 0x7ff)
        {
            printf("Id format error!\n");
            return -1;
        }

        ID = ID << 5;
        
        pframe->buffer[1] = (ID & 0xe0);/* ��3λ��Ч */
        
        pframe->buffer[0] = ((ID >> 8) & 0xff);
    }
    
    return 0;
}
#endif

/********************************************************************
��������:   ConvertBufferToID

��������:   �ӽ��յ�֡����ȡint��ID

��������        ����            ����/���           ����
pframe          sja1000_frame_t input               ָ֡��

����ֵ  :   RetID(int��ID)

����˵��:   �ӽ��յ�֡����ȡint��ID

�޸ļ�¼:   2016-04-29  ��  ��    ����
********************************************************************/
static unsigned int ConvertBufferToID(sja1000_frame_t* pframe)
{
    unsigned int RetID = 0;

    if((pframe->header & 0x80) == 0x80) /* ��չ֡ */
    {
        /* ������ֱ��ת����pframe������ */
        RetID = ((pframe->buffer[0] << 24) | (pframe->buffer[1] << 16)
                    | (pframe->buffer[2] << 8) | ((pframe->buffer[3]) & 0xf8) ) >> 3;
    }
    else /* ��׼֡ */
    {
        RetID = ((pframe->buffer[0] << 8) | ((pframe->buffer[1]) & 0xe0) ) >> 5;
    }   
    
    return RetID;
}

#if 0
/********************************************************************
��������:   AnalyzeCanFrame

��������:   ����can֡�е����ݲ�������Ϣ

��������        ����            ����/���           ����
fd              int             input               can�豸������
sja1000_frame_t*frame           input               can����֡
CanQmsg_t *     msg             output              ������Ϣ�ṹ

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����can֡�е����ݲ�������Ϣ

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
static int AnalyzeCanFrame(int fd, sja1000_frame_t *frame, CanQmsg_t *msg)
{
    char time[24] = {'\0'};
    char length = 0;
    int CbioId = 0;

#if 0
    CbioId = ConvertBufferToID(frame);
    
    /* ����˳������ϵ��������� */
    if(CbioId != 0x383 && CbioId != 0x483)
    {
        return -1;
    }


    /* ����ּ��� */
    if(CbioId = 0x383)
    {
        /* �����ݷ�װ��Qmsg�ṹ����  */
        msg->Lnum = ((frame->buffer[5] << 8) + frame->buffer[4]);
    }


    /* �ҳ��ּ��� */
    if(CbioId = 0x483)
    {
        /* �����ݷ�װ��Qmsg�ṹ����  */
        msg->Rnum = ((frame->buffer[5] << 8) + frame->buffer[4]);
    }


    /* ��ȡ��ǰϵͳʱ�� */
    length = GetTime(time, 3);

    /* ��ʱ���װ��Qmsg�ṹ���� */
    /* strncpy(msg->time, time, length + 1); */

    sprintf(msg->time, "%s", time);

    /* �����ݷ�װ��Qmsg�ṹ����  */
    msg->counter = ((frame->buffer[5] << 8) + frame->buffer[4]);

    /* �������� */
    msg->CBIO_ID = 0x55;

#if CAN_MODULE_DEBUG
    printf("\n------------Can module send mesg--------------\n");
    printf("msg->time:%s\n", msg->time);
    printf("msg->counter:%d\n", msg->counter);
    printf("\n----------------------------------------------\n");
#endif
#endif
    return 0;
}
#endif

/********************************************************************
��������:   tCanReceive

��������:   ���ݽ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ȴ����������¼�(���յ�����)

�޸ļ�¼:   2016-06-20  ��  ��    ����
********************************************************************/
static int tCanReceive(int fd)
{
    int ret = 0;
    sja1000_frame_t frame;
    CanQmsg_t msg;
    char time[24] = {'\0'};
    int CbioId = 0;

    memset(&frame, 0x00, sizeof(frame));
    memset(&msg, 0x00, sizeof(CanQmsg_t));
    
    for(;;)
    {
        ret = ReadPciCan(fd, &frame, 10);

        if(ret <= 0)
        {
            /* ���û�н��յ�������0�ṹ */
            memset(&frame, 0x00, sizeof(frame));
            continue;
        }
        else if(ret > 0)
        {
#if CAN_MODULE_DEBUG
            printf("\n------------------CAN FRAME-------------------\n");
            printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
                   fd, frame.header,
                   frame.buffer[0], frame.buffer[1], frame.buffer[2], frame.buffer[3],
                   frame.buffer[4], frame.buffer[5], frame.buffer[6], frame.buffer[7],
                   frame.buffer[8], frame.buffer[9], frame.buffer[10], frame.buffer[11]);
            printf("\n----------------------------------------------\n");
#endif

            CbioId = ConvertBufferToID(&frame);

            /* ����˳������ϵ��������� */
            if(CbioId != 0x383 && CbioId != 0x483)
            {
                /* ���û�н��յ�������0�ṹ */
                memset(&frame, 0x00, sizeof(frame));
                continue;
            }

            /* ����ּ��� */
            if(CbioId == 0x383)
            {
#if 0
                printf("CbioId = 0x383\n");
#endif
                GetTime(time, 3);
				sprintf(msg.time, "%s", time);

                /* �����ݷ�װ��Qmsg�ṹ����  */
                msg.counter = ((frame.buffer[4] << 8) + frame.buffer[3]);
                msg.CBIO_ID = 0x383;

                /* ��msg��Ϣ���͸��ļ�����ģ�� */
                msgQSend(g_CanMsgID[fd], (char *)&msg, sizeof(CanQmsg_t), NO_WAIT, 0);
                
                memset(&msg, 0x00, sizeof(CanQmsg_t));
            }

            /* �ҳ��ּ��� */
            if(CbioId == 0x483)
            {
                GetTime(time, 3);
                sprintf(msg.time, "%s", time);
#if 0
                printf("CbioId = 0x483\n");
#endif
                
                /* �����ݷ�װ��Qmsg�ṹ����  */
                msg.counter = ((frame.buffer[4] << 8) + frame.buffer[3]);
                msg.CBIO_ID = 0x483;

                /* ��msg��Ϣ���͸��ļ�����ģ�� */
                msgQSend(g_CanMsgID[fd], (char *)&msg, sizeof(CanQmsg_t), NO_WAIT, 0);

                memset(&msg, 0x00, sizeof(CanQmsg_t));
            }
        }
    } /* end for */
}
