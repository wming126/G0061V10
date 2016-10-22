/********************************************************************
�ļ�����:   TestIoCt.c

�ļ�����:   ���Ի���PCI���ߵ�IO������

�ļ�˵��:   IO������Ĵ���ӳ�䵽PCI�豸IO�ռ�

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-07  V1.0    �� �� ����
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
#include "ioLib.h"
#include "selectLib.h"
#include "tickLib.h"
#include "rngLib.h"
#include "PciIoCntLib.h"
#include "wdLib.h"

#pragma pack(1)

static int s_tid = 0;
static unsigned int g_IntCnt = 0;   /* �жϼ��� */
static WDOG_ID s_wdId = NULL;  /* ���Ź�ID */
static int s_stop = 0;
static FILE *g_fp = NULL;
static MSG_Q_ID g_MsgQId;

typedef struct TestCntQmsg_s
{
    unsigned short cnt1;
    unsigned short cnt2;
    unsigned short delta1;
    unsigned short delta2;
} TestCntQmsg_t;

/* defines */
#define MAX_MSGS (10)
#define MAX_MSG_LEN (100)


static int tIoReceive2(void);
static void watch_dog_callback(int tick);
static int TestCt(void);
static int GetKeyInput(int radix);
static int TestIoInput(void);
static int InitCom(int comNum, int BaudRate);
static int TestIoOutput(void);
static int tCtFile(void);

/********************************************************************
��������:   TestPciIoCnt

��������:   ����IOCNT����

��������            ����            ����/���       ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����IOCNT����,���Գ������

�޸ļ�¼:   2016-07-08  �� ��     ����
********************************************************************/
int TestPciIoCnt(void)
{
    int input = 0;
    int i = 0;
    int ComFd = 0;
    int ret = 0;
    unsigned char TxBuffer[2] = {0xF0,0xF0};
    unsigned int IntCnt = 0;
    unsigned int com = 0;
    int file_tid = 0;
    
    s_stop = 0;

    CreatePciIoCnt(0);

    OpenPciIoCnt(0);

    for(;; input = 0)
    {
        printf("\n"
               "1.  Test IO input \n"
               "2.  Test IO outpit \n"
               "3.  Test CNT\n"
               "4.  IO INT\n"
               "99. Exit \n");

        /* �û����� */
        printf("Your choice: %d\n", input = GetKeyInput(10));


        switch (input)
        {
        case 1:
            TestIoInput();
            break;

        case 2:
            TestIoOutput();
            break;

        case 3:
            /* create message queue */
            if ((g_MsgQId = msgQCreate (500, sizeof(TestCntQmsg_t), MSG_Q_PRIORITY)) == NULL)
                return (ERROR);

            g_fp = fopen("/ata0a/CT.txt", "w+");
            if (g_fp == NULL)
            {
                printf("fopen failed!\n");
                return 0;
            }
            
            file_tid = taskSpawn("tCtFile", 100, 0, 8192, tCtFile, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            
            ret = TestCt();
            
            printf("return = %d\n", ret);
            
            if(ret == 0)
            {
                printf("The cnt data is record to /ata0a/CT.TXT\n");
            }
            break;

        case 4:
            printf("Please input using witch COM to test.(0:COM1 1:COM2 2:COM3 3:COM4)\n");
            com = GetKeyInput(10) % 4;
        
            ComFd = InitCom(com, 300);
            
            /* ��������IO�ж���Ӧ���� */
            s_tid = taskSpawn("tIoReceive2", 100, 0, 8192, tIoReceive2,
                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

            printf("Please input test times (1-10000)\n");
            IntCnt = GetKeyInput(10) % 10000;

            for(i = 0; i < IntCnt; i++)
            {
                write(ComFd, (char *)TxBuffer, 1);
                taskDelay(sysClkRateGet()/1000*83);
            }
            
            taskDelay(sysClkRateGet());

            if(g_IntCnt == IntCnt)
            {
                printf("*******OK*******\n");
                printf("g_IntCnt = %u\n", g_IntCnt);
                printf("****************\n");
                
                g_IntCnt = 0;
            }
            else
            {
                printf("------ERROR-----\n");
                printf("g_IntCnt = %u\n", g_IntCnt);
                printf("----------------\n");
                
                g_IntCnt = 0;
            }

            close(ComFd);
            break;

        case 99:
            s_stop = 1;
            goto Exit;
            break;

        default:
            printf("Invalid input, retry!\n");
            break;
        }
    }

Exit:
    if(s_tid > 0)
    {
        taskDelete(s_tid);
    }

    if(file_tid > 0)
    {
        taskDelete(file_tid);
    }

    if(g_fp != NULL)
    {
        fclose(g_fp);
    }

    /* ɾ����������Ϣ */
    if(g_MsgQId != NULL)
    {
        msgQDelete(g_MsgQId);
    }

    ClosePciIoCnt(0);
    RemovePciIoCnt(0);


    return 0;
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

�޸ļ�¼:   2010-10-27  ���ı  ����
            2015-07-10  ����    �޸�    �޸�16���Ƽ�������
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
��������:   TestIoInput

��������:   ����IO����

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����IO����

�޸ļ�¼:   2016-07-08  �� ��     ����
********************************************************************/
static int TestIoInput(void)
{
    int i = 0;
    unsigned char uch = 0;

    printf("\n");
    for(i = 0; i < MAX_IN_PORT; i++)
    {
        uch = ReadPciIo(0, (InPort1 + i));

        printf("IN_PORT%d:%-4#x", i, uch);
    }
    printf("\n");

    return 0;
}

/********************************************************************
��������:   InitCom

��������:   COM�ڳ�ʼ��

��������        ����            ����/���           ����
comNum          int             input               ��Ӧ����(1-8)
BaudRate        int             input               ������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ɴ��ڳ�ʼ���������������Ϸ�װһ�㡣����λ8λ ֹͣλ1λ
            ��У�� ����ģʽ

�޸ļ�¼:   2016-07-14  ��  ��    ����
********************************************************************/
static int InitCom(int comNum, int BaudRate)
{
    int ret = 0;
    int fd = 0;
    
    /* �������� ���ش���1-8 */
    char *ComName[] =
    {
        "/tyCo/0", "/tyCo/1", "/tyCo/2", "/tyCo/3"
    };

    fd = open(ComName[comNum % 8], O_RDWR, 0);

    if(fd == ERROR)
    {
        printf("%s open faild!\n", ComName[comNum % 8]);
        return -1;
    }

    /* ����λ8λ ֹͣλ1λ ��У�� ����ģʽ */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CREAD | CS8);
    ret += ioctl(fd, FIOBAUDRATE, BaudRate);    /* ������ */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* ԭʼģʽOPT_RAW ��ģʽOPT_LINE �������ѡ�� */
    ret += ioctl(fd, FIOFLUSH, 0);              /* ��ջ����� */

    return fd;
}

/********************************************************************
��������:   TestIoOutput

��������:   ����IO���

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����IO���

�޸ļ�¼:   2016-07-08  �� ��     ����
********************************************************************/
static int TestIoOutput(void)
{
    static unsigned char io_out = 0xff;

    io_out = ~io_out;

    WritePciIo(0, OutPort2, io_out);

    return 0;
}

/********************************************************************
��������:   tIoReceive2

��������:   ���ݽ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ȴ����������¼�(���յ�����)���������ݣ���鲢����

�޸ļ�¼:   2016-05-03  ������  ����
********************************************************************/
static int tIoReceive2(void)
{
    for (;;)
    {
        /* ��������ж� */
        if (WaitPciIo(0, WAIT_FOREVER) < 0)
        {
            logMsg("tCntComSync run error WaitPciIo!\n", 0 , 0, 0, 0, 0, 0);
            break; 
        }

        g_IntCnt++;
    } /* end for;; */

    return 0;
}

/********************************************************************
��������:   tCtFile

��������:   ���ܲ��Ժ���2

��������            ����            ����/���       ����
tick                int             input           ���Ź�����tick��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����ⲿ�������壬Ȼ����������ֵ��

�޸ļ�¼:   2016-06-13      ���ı  ����
********************************************************************/
static int tCtFile(void)
{
    TestCntQmsg_t CntQmsg;

    for(;;)
    {
        msgQReceive(g_MsgQId, (char *)&CntQmsg, sizeof(TestCntQmsg_t), WAIT_FOREVER);

        fprintf(g_fp, "CNT1 = %08d delta1 = %08d CNT2 = %08d delta2 = %08d\n", 
            CntQmsg.cnt1, CntQmsg.delta1, CntQmsg.cnt2, CntQmsg.delta2);
    }
}

/********************************************************************
��������:   TestCt

��������:   ���ܲ��Ժ���2

��������            ����            ����/���       ����
tick                int             input           ���Ź�����tick��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����ⲿ�������壬Ȼ����������ֵ��

�޸ļ�¼:   2016-06-13      ���ı  ����
********************************************************************/
static int TestCt(void)
{
    int tick = 0;
    
    /* �������Ź���ʱ�� */
    s_wdId = wdCreate();
    if (s_wdId == NULL)
    {
        printf("wdCreate failed!\n");
        return -1;
    }

    printf("Input counter read cycle(1 - 999 ms) default 5ms\n");
    tick = GetKeyInput(10) % 1000;
    if (tick == 0)
    {
        tick = 5;
    }

    /* ��������� */
    ClearPciCnt(0, 0);
    ClearPciCnt(0, 1);
    
    /* ���������� */
    StartPciCnt(0, 0);
    StartPciCnt(0, 1);
    
    /* �������Ź� */
    wdStart(s_wdId, tick, (FUNCPTR)watch_dog_callback, tick);

    return 0;
}

/********************************************************************
��������:   watch_dog_callback

��������:   ���Ź��ص�����

��������            ����            ����/���       ����
tick                int             input           ���Ź�����tick��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ���ڶ�ȡ����ֵ���Ƚ����޴�Ĳ�ֵ

�޸ļ�¼:   2016-06-13      ���ı  ����
********************************************************************/
static void watch_dog_callback(int tick)
{
    int i = 0;
    TestCntQmsg_t CntQmsg;
    unsigned short cnt[2];
    unsigned short delta[2];
    static unsigned short s_cnt[2];

    if (s_stop == 0)
    {
        /* �ظ��������Ź� */
        wdStart(s_wdId, tick, (FUNCPTR)watch_dog_callback, tick);
    }
    else
    {
        /* ɾ�����Ź� */
        wdDelete(s_wdId);
    }

    for(i = 0; i < 2; i++)
    {
        /* ������ */
        cnt[i] = ReadPciCnt(0, i);

        /* ����ת */
        if (cnt[i] >= s_cnt[i])
        {
            delta[i] = cnt[i] - s_cnt[i];
        }
        else
        {
            delta[i] = 0xFFFF - s_cnt[i] + cnt[i] + 1;
        }
        s_cnt[i] = cnt[i];
        
        if(i == 0)
        {
            CntQmsg.cnt1 = cnt[i];
            CntQmsg.delta1 = delta[i];
        }
        else
        {
            CntQmsg.cnt2 = cnt[i];
            CntQmsg.delta2 = delta[i];
        }
    }

    msgQSend(g_MsgQId, (char*)&CntQmsg, sizeof(TestCntQmsg_t), NO_WAIT, MSG_PRI_NORMAL);

    return ;
}

