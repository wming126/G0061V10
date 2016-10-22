/********************************************************************
�ļ�����:   TestPciCan.c

�ļ�����:   ����PCI����CAN�豸

�ļ�˵��:   ����GTR64101�忨��������

��ǰ�汾:   V1.2

�޸ļ�¼:   2013-07-24  V1.0    ���ı  ����
            2014-06-26  V1.1    ������  ����    ���GTR64101�޸�
            2015-10-20  V1.2    ���ı  ����    ��������޸�
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

#include "PciCanLib.h"

#define TEST_NUMBER     (500000)
#define SUCCESS         1
#define FAILED          0

static long s_tids[MAX_CAN_NUM];
int g_pcican_debug = 1;
unsigned char g_can_id = 0;
long g_recv_err_counts[MAX_CAN_NUM];
long g_tran_err_counts[MAX_CAN_NUM];
long g_transmit_counts[MAX_CAN_NUM];
long g_received_counts[MAX_CAN_NUM];
int g_can_send_states[2];

int tCanReceive2(int fd);
int tCanTransmit(int fd);
unsigned short crc16(unsigned char *puch, int length);
static int GetKeyInput(int radix);
int InitPciCan(int fd, int BaudRate);

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

/********************************************************************
��������:   tCanReceive2

��������:   ���ݽ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ȴ����������¼�(���յ�����)���������ݣ���鲢����

�޸ļ�¼:   2014-8-10  ������  ����
********************************************************************/
int tCanReceive2(int fd)
{
    int ret = 0;
    sja1000_frame_t frame;
    unsigned short ushCheck = 0;
    int CanId = 0;

    for (;;)
    {
        memset(&frame, 0x00, sizeof(frame));
        ret = ReadPciCan(fd, &frame, WAIT_FOREVER);
        if (ret < 0)
        {
            break ;
        }
        else if (ret == 0)
        {
            printf("fd = %d ReadPciCan timeout.\n", fd);
        }
        else if (ret > 0)
        {
            /* ����У����Ƿ���ȷ */
            ushCheck = crc16(&frame.buffer[0], 10);
            if (ushCheck != *(unsigned short *)&frame.buffer[10])
            {
                g_recv_err_counts[fd] += 1;
            }
            else
            {
                g_received_counts[fd] += 1;
            }

            CanId = ConvertBufferToID(&frame);
            
            /* if(CanId == 0x383 || CanId == 0x483) */
            if(1)
            {
                if(g_pcican_debug == 1)
                {
                    printf("channel %d - ID: %04X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
                           fd, CanId, frame.header,
                           frame.buffer[0], frame.buffer[1], frame.buffer[2], frame.buffer[3],
                           frame.buffer[4], frame.buffer[5], frame.buffer[6], frame.buffer[7],
                           frame.buffer[8], frame.buffer[9], frame.buffer[10], frame.buffer[11]);
                }
            }
        } /* end for;; */
    } /* end for;; */

    return 0;
}

/********************************************************************
��������:   crc16

��������:   ����CRCУ��

��������        ����            ����/���           ����
puch            unsigned char*  input               ������ָ��
length          int             input               ���ݳ���

����ֵ  :   16bitУ����

����˵��:   ͨ��У���ж�������ȷ��

�޸ļ�¼:   2014-02-18  ������  ����
********************************************************************/
unsigned short crc16(unsigned char *puch, int length)
{
    unsigned char uch = 0x00;
    int i = 0;
    unsigned short ushCRC = 0xFFFF;

    while (length--)
    {
        uch = *puch++;

        ushCRC ^= ((int)uch << 8);

        for (i = 0; i < 8; i++)
        {
            if (ushCRC & 0x8000)
            {
                ushCRC = (ushCRC << 1) ^ 0x8005;
            }
            else
            {
                ushCRC <<= 1;
            }
        }
    }

    return ushCRC;
}

/********************************************************************
��������:   TestPciCan

��������:   ����CANͨѶ(����)

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʹ������ǰ����Ҫ�ȴ����忨�豸��

�޸ļ�¼:   2014-08-22  ������  ����
********************************************************************/
int TestPciCan(int index)
{
    int ret = 0;
    int i = 0;
    sja1000_frame_t frame;
    int input = 0;
    unsigned short ushCheck = 0;
    int channel = 0;
    int count = 0;

    memset(&frame, 0x00, sizeof(sja1000_frame_t));
    memset(g_received_counts, 0, sizeof(g_received_counts));
    memset(g_transmit_counts, 0, sizeof(g_transmit_counts));
    memset(g_can_send_states, 0, sizeof(g_can_send_states));
    memset(&g_can_id, 0x00, sizeof(g_can_id));
    memset(s_tids, 0, sizeof(s_tids));
    memset(g_tran_err_counts, 0x00, sizeof(g_tran_err_counts));
    memset(g_recv_err_counts, 0x00, sizeof(g_recv_err_counts));

    /* �ڶ��׶γ�ʼ�� */
    CreatePciCan2(index);

    /* ��ʼ��SJA1000оƬ */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        InitPciCan(i, BAUDRATE_250K);
        if (ret != 0)
        {
            printf("InitPciCan failed!%d\n", ret);
        }
    }

    for(i = 0; i < MAX_CAN_NUM; i++)
    {
        if(s_tids[i] == 0)
        {
            s_tids[i] = taskSpawn("tCanReceive2", 30, 0, 8192, tCanReceive2, i, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        }
        else
        {
            printf("Task has been created.\n");
        }
    }

    for (input = 100;;)
    {
        switch (input)
        {
        case 1: /* ѡ��һ·�������� */
            /* ���÷���֡��ʽ */
            frame.header = 0x88;
            frame.buffer[0] = 0x11;   /* ID */
            frame.buffer[1] = 0x22;   /* ID */
            frame.buffer[2] = 0x33;   /* ID */
            frame.buffer[3] = 0x40;   /* ID */
            frame.buffer[4] = 0x55;
            frame.buffer[5] = 0x66;
            frame.buffer[6] = 0x77;
            frame.buffer[7] = 0x88;
            frame.buffer[8] = 0x99;

            printf("Input a channel to transmit (Channel: 0-%d) 250Kbps\n", MAX_CAN_NUM - 1);
            channel = GetKeyInput(10) % MAX_CAN_NUM;

            printf("Input transmit count(0-10000000)\n");
            count = GetKeyInput(10) % 10000000;

            for (i = 0; i < count; i++)
            {
                frame.buffer[9] = g_can_id++;
                ushCheck = crc16(&frame.buffer[0], 10);
                *(unsigned short *)&frame.buffer[10] = ushCheck;

                ret = WritePciCan(channel, &frame);
                if (ret != 0)
                {
                    printf("channel %d WritePciCan failed!%d\n", input, ret);
                    g_tran_err_counts[channel] += 1;
                }
                else
                {
                    g_transmit_counts[channel] += 1;
                }
            }
            printf("Transmit is finish.\n");
            break;

        case 2: /* ��ʾ���� */
            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                if ((i % 4) == 0)
                {
                    printf("\n");
                }
                printf("R%d=%9d  ", i, g_received_counts[i]);
            }
            printf("\n");
            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                if ((i % 4) == 0)
                {
                    printf("\n");
                }
                printf("T%d=%9d  ", i, g_transmit_counts[i]);
            }
            printf("\n");
            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                if ((i % 4) == 0)
                {
                    printf("\n");
                }
                printf("RERR%d=%8d  ", i, g_recv_err_counts[i]);
            }
            printf("\n");
            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                if ((i % 4) == 0)
                {
                    printf("\n");
                }
                printf("TERR%d=%8d  ", i, g_tran_err_counts[i]);
            }
            printf("\n");
            break;

        case 3: /* ������� */
            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                g_received_counts[i] = 0;
                g_transmit_counts[i] = 0;
                g_recv_err_counts[i] = 0;
                g_tran_err_counts[i] = 0;

                /* ���FIFO */
                ret = FlushPciCan(i);
                if (ret != 0)
                {
                    printf("channel %d FlushPciCan failed!%d\n", i, ret);
                }
            }
            printf("Counts are clean.\n");
            break;

        case 97: /* ��ʾ״̬��Ϣ */
            ShowPciCan(index);
            break;

        case 98:
            g_pcican_debug = !g_pcican_debug;
            printf("debug = %d\n", g_pcican_debug);
            break;

        case 99: /* �˳����� */
            goto Exit;
            break;

        default:
            printf("1.  Transmit data\n"
                   "2.  Dispaly  Counts\n"
                   "3.  Clear    counts\n"
                   "97. Display  status\n"
                   "98. Swtich debug onoff (debug = %d 0:off 1:on)\n"
                   "99. Quit\n", g_pcican_debug);
        }

        printf("%d\n", input = GetKeyInput(10));
    }

Exit:
    for(i = 0; i < MAX_CAN_NUM; i++)
    {
        if (s_tids[i] != 0)
        {
            taskDelete(s_tids[i]);
            s_tids[i] = 0;
        }
    }

    /* �ر��豸 */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        ClosePciCan(i);
    }

    return ret;
}

/********************************************************************
��������:   GetKeyInput

��������:   ��ȡ��������

��������        ����            ����/���           ����
radix           int             input               �������ݽ���(10:ʮ���� 16:ʮ������)

����ֵ  :   ���������ַ�ת�����ʮ����ֵ��ʮ������ֵ��

����˵��:   �����Ͽ�����scanf��ȡ�û�����
            ����scanf�������û�������������ʱ������쳣���������³����쳣
            �����ڳ���׳�ԣ�����дһ�������滻��������Ӧ����VxWorks��Linux

�޸ļ�¼:   2010-10-27      ���ı  ����
********************************************************************/
static int GetKeyInput(int radix)
{
    char input = 0;
    int value = 0;

    if (radix == 10)
    {
        while((input = getchar()) != 0x0a)
        {
            value = value * 10 + (input - 0x30);  /* ת����ʮ������ */
        }
    }
    else
    {
        while((input = getchar()) != 0x0a)
        {
            if (input <= 0x39)
            {
                input -= 48;
            }
            else if (input <= 0x46)
            {
                input -= 55;
            }
            else
            {
                input -= 87;
            }
            value = (value << 4) + input;  /* ת����ʮ�������� */
        }
    }

    return value;
}

/********************************************************************
��������:   InitPciCan

��������:   CAN�ڳ�ʼ�����Ϻ���

��������        ����            ����/���           ����
fd              int             input               �豸������(��ӦCAN��)
BaudRate        int             input               ������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ���϶����ʼ��������ʹӦ�ó����ࡣ

�޸ļ�¼:   2014-08-14  ������  ����
            2014-08-26  ���ı  ���� ���������仯����
********************************************************************/
int InitPciCan(int fd, int BaudRate)
{
    sja1000_config_t config;
    int ret = 0;

    /* ���豸 */
    ret = OpenPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d OpenPciCan failed!%d\n", fd, ret);
        return -1;
    }

    /* ��ʼ��SJA1000оƬ */
    config.uchMOD    = 0x00;
    config.uchCDR    = 0xC4;    /* ���������ʱ����Ҫ�޸� */
    config.uchOCR    = 0xDA;    /* ���������ʱ����Ҫ�޸� */
    config.uchBTR0   = BaudRate >> 8;
    config.uchBTR1   = BaudRate;   /* ������ */
    config.uchACR[0] = 0x00;
    config.uchACR[1] = 0x00;
    config.uchACR[2] = 0x00;
    config.uchACR[3] = 0x00;
    config.uchAMR[0] = 0xFF;
    config.uchAMR[1] = 0xFF;
    config.uchAMR[2] = 0xFF;
    config.uchAMR[3] = 0xFF;
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
