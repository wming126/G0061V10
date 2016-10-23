/********************************************************************
�ļ�����:   dtp.c

�ļ�����:   �ṩʢ���忨VxWorks����ϵͳ��ͨ���������ƽ̨

�ļ�˵��:   �һ��VxWorks����ϵͳ�µ�ͨ�ò���ƽ̨ δ��������Ӳ��Թ��ܺͲ�����

��ǰ�汾:   V2.7

�޸ļ�¼:   2010-10-12  V1.0    ���ı  ����
            2012-03-31  V1.1    ���ı  ����    ���Ӹ��ֲ��Ժ���
            2012-04-18  V1.2    ������  ����    �������������Ժ���
            2012-04-26  V1.3    ���ı  ����    ��������㲥������
            2012-09-04  V1.4    ���ı  ����    ���Ӵ��ڲ�ѯ���ͺ���
            2012-12-19  V1.5    ���ı  ����    ����˫���л����Ժ���
            2013-04-27  V1.6    ���ı  ����    ����TCP���ܲ���
            2013-06-07  V1.7    ���ı  ����    ����VxWorks6.8֧��
            2013-06-27  V1.8    ���ı  ����    ����Һ�����������
            2013-11-06  V1.9    ���ı  ����    ���ӵ��Կ���
            2014-01-26  V2.0    ���ı  ����    ����ǧ��������
            2014-07-04  V2.1    ���ı  ����    �����ź�������
            2015-03-10  V2.2    ���ı  ����    ���˫���л������޸�
            2015-04-28  V2.3    ����    ����    ����˫���л����ܲ���
            2015-05-21  V2.4    ���ı  ����    ���Ӷ�ʱ��0����
            2015-08-13  V2.5    ���ı  ����    ����鲥����BUG
            2015-10-22  V2.6    ���ı  ����    �����������ƺ�λ��
            2016-04-08  V2.7    ���ı  ����    ���Ӳ�����ѡ��
********************************************************************/

#include "vxWorks.h"
#include "stdio.h"
#include "ioLib.h"
#include "fcntl.h"
#include "sys/times.h"
#include "in.h"
#include "iv.h"
#include "sioLib.h"
#include "cacheLib.h"
#include "wdLib.h"
#include "string.h"
#include "sockLib.h"
#include "taskLib.h"
#include "ipProto.h"
#include "sysLib.h"
#include "arch\I86\pentiumLib.h"
#include "selectLib.h"
#include "tickLib.h"
#include "logLib.h"
#include "drv\pci\pciConfigLib.h"

#include "dtp.h"

#if INCLUDE_NET_SWITCH
#if NET_SWITCH_TYPE
#if VXWORKS_TYPE
#include "netSwitch3.h"
#else
#include "netSwitch2.h"
#endif
#else
#if VXWORKS_TYPE
#include "netSwitch4.h"
#else
#include "netSwitch.h"
#endif
#endif
#endif

/* �������� ���ش���1-8 ��չ�崮��1-8 CSD�崮��1-8 */
/* ��չ������Ҫ���������ص�����²��ܲ��� */
char *g_ExtComName[] =
{
    "/tyCo/0", "/tyCo/1", "/tyCo/2", "/tyCo/3",
    "/tyCo/4", "/tyCo/5", "/tyCo/6", "/tyCo/7",
    "/tyCoExt/0", "/tyCoExt/1", "/tyCoExt/2", "/tyCoExt/3",
    "/tyCoExt/4", "/tyCoExt/5", "/tyCoExt/6", "/tyCoExt/7",
    "/tyCoCsd/0", "/tyCoCsd/1", "/tyCoCsd/2", "/tyCoCsd/3",
    "/tyCoCsd/4", "/tyCoCsd/5", "/tyCoCsd/6", "/tyCoCsd/7",
};

/* U���豸�����ļ��� */
char *g_MassUsbName[] =
{
    "/bd0/usb_test.txt", "/bd1/usb_test.txt",
    "/bd2/usb_test.txt", "/bd3/usb_test.txt",
};

/* CF���豸�����ļ��� */
char *g_AtaName[] =
{
    "/ata0a/ata_test.bin", "/ata0b/ata_test.bin",
};

/* ���ڻ���ַ */
short g_ExtComAddr[] =
{
    0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x500, 0x500, 0x600, 0x600,
    0x100, 0x108, 0x110, 0x118, 0x120, 0x128, 0x130, 0x138,
    0x100, 0x108, 0x110, 0x118, 0x120, 0x128, 0x130, 0x138,
};

int g_dtp_debug = 1;    /* ���Կ��� */

/* DMA������ҳ�Ĵ��� */
unsigned char dma_page_addr[8] = {0x87, 0x83, 0x81, 0x82, 0x8f, 0x8b, 0x89, 0x8a};

/* �ļ���дʹ�û����� */
char g_ataBuffer[8192] = {0};
unsigned int g_txBufferCount = 1;
unsigned char g_TxBuffer[16] = {0};

/* ���ڲ����� */
int g_com_baud = 115200;

/* ������ӳ��� */
int g_ComBauds[] = {115200, 230400, 460800, 921600, 1500000};

/* ���Ź�ʹ���ź���*/
static SEM_ID s_Sem2;
/* UDP����ID */
static int s_tid;

/* �ֲ��������� */
int com_test();
int eth_test();
int std_test();
int windml_test();
int tComRecv(int channel);
int com_transmit();
int com_receive();
int dtp_exit();
int socket_test();
int usb_test();
int audio_test();
int tUdpServerRecv();
int tTcpServerRecv();
void irq_isr(void *irq);
int int_test();
int file_test();
int watchdog_test();
int dma_test();
int realtime_test();
int netswitch_test();
int tUdpGroupRecv(int ip, int net);
int soft_watchdog_test();
int lpt_test();
int speaker_test();
int tUdpBroadcastRecv(int ip, int net);
int tTcpPerformRecv(int ip, int net);
int tcp_rx_performance();
int tcp_tx_performance();
int udp_client();

static void watch_dog_callback(int para);
static void watch_dog_callback2(int para);
int udp_task(int sock, struct sockaddr_in *pServerAddr);
int udp_client_2();

int tcp_client();
int udp_server();
int tcp_server();
int udp_group();
int udp_broadcast();
int lcd_test();
int dtp_debug_onoff(int onoff);
int sem_test();
int tTestSem(SEM_ID sem);
int timer0_test();
int timer0_callback();
int com_change_baudrate();

STATUS ifAddrSet(char *interfaceName, char *interfaceAddress);
STATUS ifAddrGet(char *interfaceName, char *interfaceAddress);
STATUS ifMaskSet(char *interfaceName, int netMask);
unsigned long inet_addr (const char *);
STATUS ifFlagSet (char *interfaceName, int flags);

/* �ֲ����� */
int s_com_tid[24] = {0};
int s_net_tid[256] = {0};
int s_task_over_flag = 0;
char s_TxBuffer[4096] = {0};
WDOG_ID s_wdId = NULL;  /* ���Ź�ID */
WDOG_ID s_wdId2 = NULL;  /* ���Ź�ID */
int s_ticks = 0;

static int GetKeyInput(int radix);

/********************************************************************
��������:   dtp

��������:   ���Գ���������

��������        ����            ����/���           ����
BoardType       int             input               ���԰忨����(LX3160:0x3160 LX3073:0x3072)

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �������ȴ���������Ȼ���ṩ�û��˻���������
            �������û�ѡ����в�ͬ�Ĺ��ܲ��ԣ�����Ĳ��Թ����ɵ����ĺ���ʵ��
            ������ܿ�����δ������

�޸ļ�¼:   2010-10-12      ���ı  ����
********************************************************************/
int dtp(int BoardType)
{
    volatile int input = 0;

    s_task_over_flag = 0;
    memset(s_com_tid, 0x00, sizeof(s_com_tid));
    memset(s_net_tid, 0x00, sizeof(s_net_tid));

    for (input = 100;; )
    {
        switch (input)
        {
        case 1:
            printf("return = %d\n", com_test());
            break;

        case 2:
            printf("return = %d\n", eth_test());
            break;

        case 4:
            printf("return = %d\n", usb_test());
            break;

        case 5:
            printf("return = %d\n", file_test());
            break;

        case 6:
            printf("return = %d\n", socket_test());
            break;

        case 7:
            printf("return = %d\n", audio_test());
            break;

#if INCLUDE_WINDML_TEST
        case 8:
            printf("return = %d\n", windml_test());
            break;
#endif
        case 9:
            printf("return = %d\n", int_test());
            break;

        case 10:
            printf("return = %d\n", watchdog_test());
            break;

        case 11:
            printf("return = %d\n", dma_test());
            break;

        case 12:
            printf("return = %d\n", realtime_test());
            break;

        case 13:
            printf("return = %d\n", std_test());
            break;

#if INCLUDE_NET_SWITCH
        case 14:
            printf("return = %d\n", netswitch_test());
            break;
#endif
        case 15:
            printf("return = %d\n", lpt_test());
            break;

        case 16:
            printf("return = %d\n", soft_watchdog_test());
            break;

        case 17:
            printf("return = %d\n", speaker_test());
            break;

        case 18:
            printf("return = %d\n", lcd_test());
            break;

        case 19:
            printf("return = %d\n", sem_test());
            break;

        case 20:
            printf("return = %d\n", timer0_test());
            break;

        case 98:
            printf("return = %d", dtp_debug_onoff(!g_dtp_debug));
            break;

        case 99:
            printf("Exit Program, exit code = %d\n", dtp_exit());
            goto Exit;

        default:
            printf("\n"
                   "1.  COM         Test\n"
                   "2.  ETH         Test\n"
                   "3.  KEY         Test\n"
                   "4.  USB         Test\n"
                   "5.  FILE        Test\n"
                   "6.  SOCKET      Test\n"
                   "7.  AUDIO       Test\n"

#if INCLUDE_WINDML_TEST
                   "8.  WINDML      Test\n"
#endif
                   "9.  INT         Test\n"
                   "10. WATCHDOG    Test\n"
                   "11. DMA         Test\n"
                   "12. REAL TIME   Test\n"
                   "13. STD SWITCH  Test\n"

#if INCLUDE_NET_SWITCH
                   "14. NET SWITCH  Test\n"
#endif
                   "15. LPT         Test\n"
                   "16. SOFT WD     Test\n"
                   "17. SPEAKER     Test\n"
                   "18. LCD         Test\n"
                   "19. SEM         Test\n"
                   "20. TIMER0      Test\n"
                   "98. DEBUG       Onoff(%d 0:OFF 1:ON)\n"
                   "99. Exit\n", g_dtp_debug);
        }

        /* �û����� */
        printf("Your choice: %d\n", input = GetKeyInput(10));
    }/* end for */
Exit:

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
int GetKeyInput(int radix)
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
��������:   DecToBin

��������:   ��������ʽ��ʮ������ת����ʮ������

��������        ����            ����/���           ����
Decimal         unsigned int    input               ��������ʽ��ʮ������(10101011)

����ֵ  :   ����ʮ������ֵ������� = 10100101 ����ֵ = 0xA5

����˵��:   C����û�ж���������ʾ

�޸ļ�¼:   2010-12-08      ���ı  ����
********************************************************************/
unsigned int DecToBin(unsigned int Decimal)
{
    int i = 0;
    unsigned int ret = 0;

    for (i = 0; i < 32; i++)
    {
        if((Decimal % 10) != 0)
        {
            ret = ret | (0x01 << i);
        }
        Decimal /= 10;
    }

    return ret;
}

/********************************************************************
��������:   DtpExit

��������:   �˳�DTP

��������        ����            ����/���           ����

����ֵ  :   ����ʵ��������ж���

����˵��:   dtp����˳�ʱ��Ҫ���еĲ���

�޸ļ�¼:   2010-12-06      ���ı  ����
********************************************************************/
int dtp_exit()
{
    int i = 0;

    /* �������������� */
    s_task_over_flag = 1;

    for (i = 0; i < 16; i++)
    {
        if (s_com_tid[i] != 0)
        {
            taskDelete(s_com_tid[i]);
            s_com_tid[i] = 0;
        }
        if (s_net_tid[i] != 0)
        {
            taskDelete(s_net_tid[i]);
            s_net_tid[i] = 0;
        }
    }

    return 0;
}

/********************************************************************
��������:   com_test

��������:   ���ڲ���

��������        ����            ����/���           ����

����ֵ  :   ����ʵ��������ж���

����˵��:   ���ڲ��Է�ΪCPU�忨���ԣ���չ���ڿ����Ժ�A3CSD��չ���ڿ����ԣ���Ҫ��װ��Ӧ������
            ����ʱ�ֱ�ָ�����ʹ��ںͽ��մ��� �õ��߶����������ڵķ��ͺͽ�������

�޸ļ�¼:   2010-10-12      ���ı  ����
********************************************************************/
int com_test()
{
    int input;
    int ret = 0;

    for (;;)
    {
        printf("\n"
               "1. COM Receive\n"
               "2. COM Transmit\n"
               "3. Change Baudrate %dbps\n"
               "other. Exit\n", g_com_baud);

        /* �û����� */
        printf("Your choice: %d\n", input = GetKeyInput(10));

        switch (input)
        {
        case 1:
        {
            ret = com_receive();
            break;
        }
        case 2:
        {
            ret = com_transmit();
            break;
        }
        case 3:
        {
            ret = com_change_baudrate();
            break;
        }
        default:
        {
            return 0;
        };
        }
    }

    return ret;
}

/********************************************************************
��������:   eth_test

��������:   ���ڲ���

��������        ����            ����/���           ����

����ֵ  :   ����ʵ��������ж���

����˵��:   ���ڲ�������������IP��ַ��Ȼ������������ping�������������ͨ��

�޸ļ�¼:   2010-11-17      ���ı  ����
********************************************************************/
int eth_test()
{
    int ret = 0;
    int ip = 0;     /* IP��ַ���һ�� */
    int unit = 0;
    char IpAddress[32] = {0};
    int input = 0;
    char NetName[32] = {0};

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    unit = GetKeyInput(10) % 12;
    if (unit < 6)
    {
        sprintf(NetName, "fei%d", unit);

        /* ��������Э��ջ */
        ret = ipAttach(unit, "fei");
        if (ret != 0)
        {
            printf("ipAttach failed!%d\n", unit);
            return ret;
        }
    }
    else
    {
        sprintf(NetName, "gei%d", unit - 6);

        /* ��������Э��ջ */
        ret = ipAttach(unit - 6, "gei");
        if (ret != 0)
        {
            printf("ipAttach failed!%d\n", unit);
            return ret;
        }
    }

    /* ����IP��ַ���һλ */
    printf("Input the last ip address (1-254):\n");
    input = GetKeyInput(10);
    ip = input ? (input % 255) : 1;

    /* ��������������ͬһ���� */
    /* ����IP */
    sprintf(IpAddress, "192.168.%d.%d", unit + 1, ip);
    ret = ifAddrSet(NetName, IpAddress);

    /* ʹ������ӿ� */
    ret = ifFlagSet(NetName, IFF_UP);
    if (ret != 0)
    {
        printf("ifFlagSet failed!\n");
        return ret;
    }

    /* ������������ */
    ret = ifMaskSet(NetName, 0xfffffff0);

    printf("Please ping (%s) form other computer, press enter to exit\n", IpAddress);
    GetKeyInput(10);

    /* ����ж��Э��ջ ж�غ������޷�ʹ�� */
    if (unit < 6)
    {
        ret = ipDetach(unit, "fei");
    }
    else
    {
        ret = ipDetach(unit - 6, "gei");
    }

    return ret;
}

/********************************************************************
��������:   socket_test

��������:   socket�ӿڲ���

��������        ����            ����/���           ����

����ֵ  :   ����ʵ��������ж���

����˵��:   ����UDP��TCPͨѶ

�޸ļ�¼:   2010-12-07      ���ı  ����
********************************************************************/
int socket_test()
{
    int input;
    int ret = 0;

    for (;;)
    {
        printf("\n"
               "1. UDP Client\n"
               "2. UDP Server\n"
               "3. TCP Client\n"
               "4. TCP Server\n"
               "5. UDP Group\n"
               "6. UDP Broadcast\n"
               "7. TCP Rx Performance\n"
               "8. TCP Tx Performance\n"
               "9. UDP Client2\n"
               "other. Exit\n");

        /* �û����� */
        printf("Your choice: %d\n", input = GetKeyInput(10));

        switch (input)
        {
        case 1:
        {
            ret = udp_client();
            break;
        }
        case 2:
        {
            ret = udp_server();
            break;
        }
        case 3:
        {
            ret = tcp_client();
            break;
        }
        case 4:
        {
            ret = tcp_server();
            break;
        }
        case 5:
        {
            ret = udp_group();
            break;
        }
        case 6:
        {
            ret = udp_broadcast();
            break;
        }
        case 7:
        {
            ret = tcp_rx_performance();
            break;
        }
        case 8:
        {
            ret = tcp_tx_performance();
            break;
        }
        case 9:
        {
            ret =  udp_client_2();
            break;
        }
        default:
        {
            return 0;
        };
        }
    }

    return ret;
}

/********************************************************************
��������:   udp_client

��������:   ����һ��UDP�ͻ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2010-12-07      ���ı  ����
********************************************************************/
int udp_client()
{
    int ret;
    int client = 0;
    FILE *fp = NULL;
    struct sockaddr_in serverAddr;
    int socketLength = sizeof(struct sockaddr_in);
    int i = 0;
    int sent = 0;
    int count = 0;
    int to_send = 2048;
    int ip1 = 0;
    int ip2 = 0;
    int length = 0;
    unsigned char TxBuffer[2048] = {0};
    char IpAddress[32] = {0};
    int input = 0;
    char opt = 0;

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));

    /* ���ɲ������� */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i;
    }

    /* �����׽��� */
    client = socket(AF_INET, SOCK_DGRAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create udp socket failed!\n");
        goto Exit;
    }

    /* ���÷��ͻ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* ���ý��ջ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* �����鲥TTLֵ */
    opt = 255;
    ret = setsockopt (client, IPPROTO_IP, IP_MULTICAST_TTL, &opt, sizeof(opt));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_TTL)!%d\n", errno);
        goto Exit;
    }

    /* ���뷢�ʹ��� */
    printf("UDP Test, Input Transmit Count(1-10000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 10000) : 1;

    /* ����IP��ַ�����ڶ�λ�����һλ */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;

    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* ���÷�������Ϣ */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (UDP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

#if 0
    /* ��������ʹ���ļ���Ĭ��ֵ */
    fp = fopen("udp_tx.txt", "rb");
    if (fp != NULL)
    {
        to_send = fread(TxBuffer, 1, sizeof(TxBuffer), fp);
        if (to_send != 0)
        {
            printf("send from udp_tx.txt(max 256 bytes)\n");
        }
        else     /* �ļ���û������ */
        {
            to_send = 256;
            for (i = 0; i < sizeof(TxBuffer); i++)
            {
                TxBuffer[i] = i;
            }
        }
    }
#endif

    /* �������� */
    for (i = 0; i < count; i++)
    {
        sent = sendto(client, (char *)TxBuffer, to_send, 0, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
        if (sent != to_send)
        {
            printf("sent = %d\n", sent);
            break;
        }
        taskDelay(sysClkRateGet() / 60);    /* VxWorks sendto������bug �޷����������ݷ������ */
    }

    printf("Packets are sent to %s:%d.\n", IpAddress, UDP_SERVER_PORT);

    /* �ȴ��������˻�Ӧ ע�⺯�������� */
    printf("Wait for a response from server.\n");
    length = recvfrom(client, (char *)TxBuffer, sizeof(TxBuffer), 0, (struct sockaddr *)&serverAddr, &socketLength);

    /* ��ӡ���յ����� */
    printf("--- ");
    for (i = 0; i < length; i++)
    {
        printf("%02X ", TxBuffer[i]);
        if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
    }
    printf("--- udp client\n");

Exit:
    /* �ر��׽��� */
    if (client != 0)
    {
        close(client);
    }

    /* �ر��ļ� */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
��������:   tcp_client

��������:   ����һ��TCP�ͻ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2010-12-29      ���ı  ����
********************************************************************/
int tcp_client()
{
    int ret;
    int client = 0;
    FILE *fp = NULL;
    struct sockaddr_in serverAddr;
    int i = 0;
    int sent = 0;
    int input = 0;
    int count = 0;
    int to_send = 2048;
    int ip1 = 0;
    int ip2 = 0;
    int length = 0;
    unsigned char TxBuffer[2048] = {0};
    char IpAddress[32] = {0};

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));

    /* ���ɲ������� */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i;
    }

    /* �����׽��� */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create tcp socket failed!\n");
        goto Exit;
    }

    /* ���÷��ͻ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* ���ý��ջ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* ���뷢�ʹ��� */
    printf("TCP Test, Input Transmit Count(1-10000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 10000) : 1;

    /* ����IP��ַ���һλ */
    /* ����IP��ַ�����ڶ�λ�����һλ */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;

    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* ���÷�������Ϣ */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (TCP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

    /* ���ӷ����� */
    if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) == -1)
    {
        ret = ERROR - 1;
        printf("Connect to tcp server failed!\n");
        goto Exit;
    }

#if 0
    /* ��������ʹ���ļ���Ĭ��ֵ */
    fp = fopen("tcp_tx.txt", "rb");
    if (fp != NULL)
    {
        to_send = fread(TxBuffer, 1, sizeof(TxBuffer), fp);
        if (to_send != 0)
        {
            printf("send from tcp_tx.txt(max 256 bytes)\n");
        }
        else     /* �ļ���û������ */
        {
            to_send = 256;
            for (i = 0; i < sizeof(TxBuffer); i++)
            {
                TxBuffer[i] = i;
            }
        }
    }
#endif

    /* �������� */
    for (i = 0; i < count; i++)
    {
        sent = send(client, (char *)TxBuffer, to_send, 0);
        if (sent != to_send)
        {
            printf("sent = %d\n", sent);
            break;
        }
    }

    /* �ȴ��û������ر�socket */
    printf("Packets are sent to %s:%d.\n", IpAddress, TCP_SERVER_PORT);

    /* �ȴ��������˻�Ӧ ע�⺯�������� */
    printf("Wait for a response from server.\n");
    length = recv(client, (char *)TxBuffer, sizeof(TxBuffer), 0);
    /* ��ӡ���յ����� */
    printf("--- ");
    for (i = 0; i < length; i++)
    {
        printf("%02X ", TxBuffer[i]);
        if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
    }
    printf("--- tcp client\n");

Exit:
    /* �ر��׽��� */
    if (client != 0)
    {
        close(client);
    }

    /* �ر��ļ� */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
��������:   udp_server

��������:   ����һ��UDP��������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2010-12-29      ���ı  ����
********************************************************************/
int udp_server()
{
    int input = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    input = GetKeyInput(10) % 12;
    if (input < 6)
    {
        sprintf(NetName, "fei%d", input);
    }
    else
    {
        sprintf(NetName, "gei%d", input - 6);
    }

    ifAddrGet(NetName, IpAddress);
    printf("Net adapter's ip address is %s.\n", IpAddress);

    if (s_net_tid[input + UDP_SERVER_TID] == 0)
    {
        /* ������������ */
        s_net_tid[input + UDP_SERVER_TID] = taskSpawn("tUdpServerRecv", 100, 0, 1024 * 40, (FUNCPTR)tUdpServerRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* ��ʱ */
        taskDelay(sysClkRateGet() / 10);

    }
    else
    {
        printf("UDP server has been already established.\n");
    }

    return s_net_tid[input + UDP_SERVER_TID];
}

/********************************************************************
��������:   tUdpServerRecv

��������:   UDP��������������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʹ��������ʽ��ȡ δ����Ҫ�޸�

�޸ļ�¼:   2010-10-21      ���ı  ����
********************************************************************/
int tUdpServerRecv(int ip, int net)
{
    int ret = 0;
    int server = 0;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int socketLength = sizeof(struct sockaddr_in);
    unsigned char RxBuffer[256];
    int length = 0;
    int sum = 0;
    int i = 0;

    /* �����׽��� */
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == ERROR)
    {
        printf("Create udp socket failed!\n");
        return -1;
    }

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_CLIENT_PORT);   /* �����˿ں� */
    serverAddr.sin_addr.s_addr = ip;                /* ͨ��IP��ַѡ������ */

    /* �󶨶˿� */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("bind udp socket failed!%d\n", errno);
        goto Exit;
    }

    printf("UDP server established, port = %d.\n", UDP_CLIENT_PORT);

    /* ��ʾ�������� */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recvfrom(server, (char *)RxBuffer, sizeof(RxBuffer), 0, (struct sockaddr *)&clientAddr, &socketLength);
        if (length == ERROR)
        {
            printf("recvfrom failed!\n");
            break;
        }

        /* ��ӡ���յ����� */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
        }
        printf("--- udp server %d\n", net);

        /* ��Ӧ���յ������� */
        sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&clientAddr, socketLength);
    }

Exit:
    s_net_tid[net + UDP_SERVER_TID] = 0;
    close(server);

    return ret;
}

/********************************************************************
��������:   udp_group

��������:   ����һ��UDP�鲥��������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2011-07-04      ���ı  ����
********************************************************************/
int udp_group()
{
    int input = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    input = GetKeyInput(10) % 12;
    if (input < 6)
    {
        sprintf(NetName, "fei%d", input);
    }
    else
    {
        sprintf(NetName, "gei%d", input - 6);
    }

    ifAddrGet(NetName, IpAddress);
    printf("Net adapter's ip address is %s.\n", IpAddress);

    if (s_net_tid[input + UDP_GROUP_TID] == 0)
    {
        /* ������������ */
        s_net_tid[input + UDP_GROUP_TID] = taskSpawn("tUdpGroupRecv", 100, 0, 1024 * 40, (FUNCPTR)tUdpGroupRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* ��ʱ */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("UDP group has been already established.\n");
    }

    return s_net_tid[input + UDP_GROUP_TID];
}

/********************************************************************
��������:   tUdpGroupRecv

��������:   UDP�������鲥��������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʹ��������ʽ��ȡ δ����Ҫ�޸�

�޸ļ�¼:   2011-07-04      ���ı  ����
********************************************************************/
int tUdpGroupRecv(int ip, int net)
{
    int ret = 0;
    int server = 0;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    struct sockaddr_in tempAddr;
    int socketLength = sizeof(struct sockaddr_in);
    unsigned char RxBuffer[256];
    int length = 0;
    int sum = 0;
    int i = 0;
    int on = 0;
    char opt = 0;
    struct ip_mreq mcast1;
    struct ip_mreq mcast2;

    /* �����׽��� */
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == ERROR)
    {
        printf("Create udp socket failed!\n");
        return -1;
    }

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&tempAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&mcast1, 0x00, sizeof(struct ip_mreq));
    memset(&mcast2, 0x00, sizeof(struct ip_mreq));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_GROUP_PORT);    /* �����˿ں� */
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* ����ʹ��htonl(INADDR_ANY) */

    /* �󶨶˿� */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("bind udp socket failed!%d\n", errno);
        goto Exit;
    }

    /* ���ù㲥���� */
    on = 1;
    ret = setsockopt (server, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
    if (ret != 0)
    {
        printf("setsockopt failed(SO_BROADCAST)!%d\n", errno);
        goto Exit;
    }

    /* ���õ�ַ�Ͷ˿� */
    on = 1;
    ret = setsockopt (server, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if (ret != 0)
    {
        printf("setsockopt failed(SO_REUSEADDR)!%d\n", errno);
        goto Exit;
    }

    on = 1;
    ret = setsockopt (server, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));
    if (ret != 0)
    {
        printf("setsockopt failed(SO_REUSEPORT)!%d\n", errno);
        goto Exit;
    }

    /* �����鲥���͹��� */
    ret = setsockopt (server, IPPROTO_IP, IP_MULTICAST_IF, (char *)&ip, sizeof(struct in_addr));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_IF)!%d\n", errno);
        goto Exit;
    }

    /* �����鲥TTLֵ */
    opt = 255;
    ret = setsockopt (server, IPPROTO_IP, IP_MULTICAST_TTL, &opt, sizeof(opt));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_TTL)!%d\n", errno);
        goto Exit;
    }

#if INCLUDE_NET_SWITCH
    /* ��¼ʹ���鲥���͵�socket */
    AddSocketEntry(0, &server, 1);
#endif

    /* �鲥���ݲ��ػ� */
    opt = 0;
    ret = setsockopt(server, IPPROTO_IP, IP_MULTICAST_LOOP, &opt, sizeof(opt));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_LOOP)!%d\n", errno);
        goto Exit;
    }

    /* �����鲥 */
    mcast1.imr_multiaddr.s_addr = inet_addr(UDP_GROUP_ADDRESS1);
    mcast1.imr_interface.s_addr = ip;

    /* �����鲥�� */
    ret = setsockopt(server, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mcast1, sizeof(mcast1));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_ADD_MEMBERSHIP mcast1)!%d\n", errno);
        goto Exit;
    }

#if INCLUDE_NET_SWITCH
    /* ˫�����������鲥 */
#if VXWORKS_TYPE
    AddMulticast(0, &mcast1);
#else
    AddMulticast(0, server, &mcast1);
#endif
#endif

    /* ��ʱ */
    taskDelay(sysClkRateGet() / 10);

    /* �����鲥 */
    mcast2.imr_multiaddr.s_addr = inet_addr(UDP_GROUP_ADDRESS2);
    mcast2.imr_interface.s_addr = ip;

    /* �����鲥�� */
    ret = setsockopt(server, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mcast2, sizeof(mcast2));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_ADD_MEMBERSHIP mcast2)!%d\n", errno);
        goto Exit;
    }

#if INCLUDE_NET_SWITCH
#if VXWORKS_TYPE
    /* ˫�����������鲥 */
    AddMulticast(0, &mcast2);
#else
    AddMulticast(0, server, &mcast2);
#endif
#endif

    printf("UDP group established, port = %d.\n", UDP_GROUP_PORT);

    /* ��ʾ�������� */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recvfrom(server, (char *)RxBuffer, sizeof(RxBuffer), 0, (struct sockaddr *)&clientAddr, &socketLength);
        if (length == ERROR)
        {
            printf("recvfrom failed!\n");
            break;
        }

        /* ��ӡ���յ����� */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
        }
        printf("--- udp group %d\n", net);

        /* ��Ӧ���յ�������(�����ַ)
        ret = sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&clientAddr, socketLength);
        if (ret == -1)
        {
            printf("sendto(client) ret = %d errno = %d\n", ret, errno);
        }*/

        /* ��Ӧ���յ�������(�鲥��ַ) */
        tempAddr.sin_family = AF_INET;
        tempAddr.sin_port = htons(UDP_GROUP_PORT);   /* �����˿ں� */
        tempAddr.sin_addr.s_addr = inet_addr(UDP_GROUP_ADDRESS1);
        ret = sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&tempAddr, socketLength);
        if (ret == -1)
        {
            printf("sendto(UDP_GROUP_ADDRESS1) ret = %d errno = %d\n", ret, errno);
        }

        /* ��Ӧ���յ�������(�鲥��ַ2) */
        tempAddr.sin_family = AF_INET;
        tempAddr.sin_port = htons(UDP_GROUP_PORT);   /* �����˿ں� */
        tempAddr.sin_addr.s_addr = inet_addr(UDP_GROUP_ADDRESS2);
        ret = sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&tempAddr, socketLength);
        if (ret == -1)
        {
            printf("sendto(UDP_GROUP_ADDRESS2) ret = %d errno = %d\n", ret, errno);
        }
    }

Exit:
    s_net_tid[net + UDP_SERVER_TID] = 0;

#if INCLUDE_NET_SWITCH
#if VXWORKS_TYPE
    DelMulticast(0, &mcast1);
    DelMulticast(0, &mcast2);
#else
    DelMulticast(0, server, &mcast1);
    DelMulticast(0, server, &mcast2);
#endif
    DelSocketEntry(0);
#endif

    close(server);

    return ret;
}

/********************************************************************
��������:   udp_broadcast

��������:   ����һ��UDP�������˲��Թ㲥��

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2012-04-26      ���ı  ����
********************************************************************/
int udp_broadcast()
{
    int input = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    input = GetKeyInput(10) % 12;
    if (input < 6)
    {
        sprintf(NetName, "fei%d", input);
    }
    else
    {
        sprintf(NetName, "gei%d", input - 6);
    }

    ifAddrGet(NetName, IpAddress);
    printf("Net adapter's ip address is %s.\n", IpAddress);

    if (s_net_tid[input + UDP_BROADCAST_TID] == 0)
    {
        /* ������������ */
        s_net_tid[input + UDP_BROADCAST_TID] = taskSpawn("tUdpBroadcastRecv", 100, 0, 1024 * 40, (FUNCPTR)tUdpBroadcastRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* ��ʱ */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("UDP server has been already established.\n");
    }

    return s_net_tid[input + UDP_BROADCAST_TID];
}

/********************************************************************
��������:   tUdpBroadcastRecv

��������:   UDP�������㲥��������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʹ��������ʽ��ȡ δ����Ҫ�޸�

�޸ļ�¼:   2012-04-26      ���ı  ����
********************************************************************/
int tUdpBroadcastRecv(int ip, int net)
{
    int ret = 0;
    int server = 0;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int socketLength = sizeof(struct sockaddr_in);
    unsigned char RxBuffer[256];
    int length = 0;
    int sum = 0;
    int i = 0;
    int on = 0;

    /* �����׽��� */
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == ERROR)
    {
        printf("Create udp socket failed!\n");
        return -1;
    }

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_BROADCAST_PORT);    /* �����˿ں� */
    serverAddr.sin_addr.s_addr = ip;                    /* ͨ��IP��ַѡ������ */

    /* �󶨶˿� */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("bind udp socket failed!%d\n", errno);
        goto Exit;
    }

    /* ���ù㲥���� */
    on = 1;
    ret = setsockopt (server, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
    if (ret != 0)
    {
        printf("setsockopt failed(SO_BROADCAST)!%d\n", errno);
        goto Exit;
    }

    printf("UDP broadcast established, port = %d.\n", UDP_BROADCAST_PORT);

    /* ��ʾ�������� */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recvfrom(server, (char *)RxBuffer, sizeof(RxBuffer), 0, (struct sockaddr *)&clientAddr, &socketLength);
        if (length == ERROR)
        {
            printf("recvfrom failed!\n");
            break;
        }

        /* ��ӡ���յ����� */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
        }
        printf("--- udp broadcast %d\n", net);

        clientAddr.sin_family = AF_INET;
        clientAddr.sin_port = htons (UDP_BROADCAST_PORT);
        clientAddr.sin_addr.s_addr = ip | 0xFF000000;   /* �����㲥��ַ VxWorks6.8��ȫ���㲥������ȥ������·�ɱ������ */

        /* ��Ӧ���յ������� */
        sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&clientAddr, socketLength);
    }

Exit:
    s_net_tid[net + UDP_BROADCAST_TID] = 0;
    close(server);

    return ret;
}

/********************************************************************
��������:   tcp_server

��������:   ����һ��TCP��������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2010-12-29      ���ı  ����
********************************************************************/
int tcp_server()
{
    int input = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    input = GetKeyInput(10) % 12;
    if (input < 6)
    {
        sprintf(NetName, "fei%d", input);
    }
    else
    {
        sprintf(NetName, "gei%d", input - 6);
    }

    ifAddrGet(NetName, IpAddress);
    printf("Net adapter's ip address is %s.\n", IpAddress);

    if (s_net_tid[input + TCP_SERVER_TID] == 0)
    {
        /* ������������ */
        s_net_tid[input + TCP_SERVER_TID] = taskSpawn("tTcpServerRecv", 100, 0, 1024 * 40, (FUNCPTR)tTcpServerRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* ��ʱ */
        taskDelay(sysClkRateGet() / 10);

    }
    else
    {
        printf("TCP server has been already established.\n");
    }

    return s_net_tid[input + TCP_SERVER_TID];
}

/********************************************************************
��������:   tTcpServerRecv

��������:   TCP��������������

��������        ����            ����/���           ����
fd              int             input               ���մ��ھ��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʹ��������ʽ��ȡ δ����Ҫ�޸�

�޸ļ�¼:   2010-10-21      ���ı  ����
********************************************************************/
int tTcpServerRecv(int ip, int net)
{
    int ret = 0;
    int server = 0;
    int client = 0;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int socketLength = sizeof(struct sockaddr_in);
    unsigned char RxBuffer[256];
    int length = 0;
    int sum = 0;
    int i = 0;

    /* �����׽��� */
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == ERROR)
    {
        printf("Create tcp socket failed!\n");
        return -1;
    }

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_CLIENT_PORT);   /* �����˿ں� */
    serverAddr.sin_addr.s_addr = ip;                /* ͨ��IP��ַѡ������ */

    /* �󶨶˿� */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("Bind tcp socket failed!\n");
        goto Exit;
    }

    /* �����˿� */
    if (listen(server, 1) == -1)
    {
        printf("Listen tcp socket failed!\n");
        goto Exit;
    }

    printf("TCP server is listening, port = %d.\n", TCP_CLIENT_PORT);

    /* �ȴ��ͻ������� */
    client = accept(server, (struct sockaddr *)&clientAddr, &socketLength);
    if (client == -1)
    {
        printf("Accept tcp socket failed!\n");
        goto Exit;
    }

    /* ��ʾ�������� */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recv(client, (char *)RxBuffer, sizeof(RxBuffer), 0);
        if (length == ERROR)
        {
            printf("recv failed!\n");
            break;
        }

        if (length == 0)
        {
            printf("Perhaps tcp client has disconnected.\n");
            break;
        }

        /* ��ӡ���յ����� */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
        }
        printf("--- tcp server %d\n", net);

        /* ��Ӧ���յ������� */
        send(client, (char *)RxBuffer, length, 0);
    }

Exit:
    s_net_tid[net + TCP_SERVER_TID] = 0;
    close(client);
    close(server);

    return ret;
}

/********************************************************************
��������:   com_transmit

��������:   ���ڷ��ͺ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ���������û������һ�����ڣ������ض�����
            ����485ͨѶ ��Ҫ�����ض���

�޸ļ�¼:   2010-11-02      ���ı  ����
            2016-09-21      ��  ��  �޸� SIO_HW_OPTS_SET���6.8�������ϵ�������λ����
********************************************************************/
int com_transmit()
{
    int fd = 0;
    int i = 0;
    int ret = 0;
    int sent = 0;
    int to_send = 256;
    int input = 0;
    int TxCom = 0;
    int count = 1;
    FILE *fp = NULL;
    unsigned char TxBuffer[256] = {0};

    /* ���Է�������0x00 - 0xFF */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i + TxCom + 1;
    }

    /* ָ�����ʹ��� */
    printf("Input Transmit COM Number:(1-8:COM 9-16:EXTCOM 17-24:CSDCOM) odd\n");
    input = GetKeyInput(10);
    TxCom = (input - 1) % 24;

    /* �򿪷��ʹ��� */
    fd = open(g_ExtComName[TxCom], O_RDWR, 0);
    if (fd == ERROR)
    {
        printf("Open %s failed!\n", g_ExtComName[TxCom]);
        return fd;
    }

    printf("Open %s succeeded\n", g_ExtComName[TxCom]);

    /* ���ô��ڲ��� */
    /* ����λ8λ ֹͣλ1λ ��У�� ����ģʽ */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | PARENB);
    ret += ioctl(fd, FIOBAUDRATE, g_com_baud);  /* ������ */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* ԭʼģʽOPT_RAW ��ģʽOPT_LINE �������ѡ�� */
    ret += ioctl(fd, FIOFLUSH, 0);              /* ��ջ����� */

    /* ���뷢�ʹ��� */
    printf("COM Test, Input Transmit Count(1-10000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 10000) : 1;

    /* ���ʹ��ڷ������� */
    for (i = 0; i < count; i++)
    {
        sent += write(fd, (char *)TxBuffer, to_send);
    }
    printf("COM%d Sent %d\n", TxCom + 1, sent);

    /* VxWorks���ڷ��ͺ����޷��������Է��������Ҫ�����ȴ���� ��ʱʹ����ʱʵ�� */
    taskDelay(sysClkRateGet() / 10);

    /* ���뱣֤���ݷ�����ɺ� ���ܹرմ��� */
    close(fd);

    /* �ر��ļ� */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
��������:   com_receive

��������:   ���ڽ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ���������û����봴��һ�����ڽ�������
            ���ڽ�������ͣ��ȡ�����յ�������

�޸ļ�¼:   2010-11-02      ���ı  ����
********************************************************************/
int com_receive()
{
    int input = 0;
    int RxCom = 0;

    /* ָ�����մ��� */
    printf("Input Receive COM Number:(1-8:COM 9-16:EXTCOM 17-24:CSDCOM) odd\n");
    input = GetKeyInput(10);
    RxCom = (input - 1) % 24;

    if (s_com_tid[RxCom] == 0)
    {
        /* ������������ */
        s_com_tid[RxCom] = taskSpawn("tComRecv", 100, 0, 1024 * 40, (FUNCPTR)tComRecv, RxCom, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        /* ��ʱ */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("COM%d has been already opened.\n", RxCom);
    }

    return s_com_tid[RxCom];
}

/********************************************************************
��������:   tComRecv

��������:   ���ڽ�������

��������        ����            ����/���           ����
RxCom           int             input               ��������(0-24)

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʹ��������ʽ��ȡ δ����Ҫ�޸�

�޸ļ�¼:   2010-10-21      ���ı  ����
********************************************************************/
int tComRecv(int RxCom)
{
    int fd = 0;
    int ret = 0;
    unsigned char RxBuffer[256] = {0};
    int Received = 0;
    int sum = 0;
    int i = 0;

#if INCLUDE_COM_TIMEOUT    /* ��ͨ��ȡģʽ */
    struct timeval timeout;
#endif

    /* �򿪽��մ��� */
    fd = open(g_ExtComName[RxCom], O_RDWR, 0);
    if (fd == ERROR)
    {
        printf("Open %s COM failed!\n", g_ExtComName[RxCom]);
        return fd;
    }

    printf("Open %s succeeded\n", g_ExtComName[RxCom]);

    /* ���ô��ڲ��� */
    /* ����λ8λ ֹͣλ1λ ��У�� ����ģʽ */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | PARENB);
    ret += ioctl(fd, FIOBAUDRATE, g_com_baud);  /* ������ */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* ԭʼģʽOPT_RAW ��ģʽOPT_LINE �������ѡ�� */
    ret += ioctl(fd, FIOFLUSH, 0);              /* ��ջ����� */

    /* ��ӡ�������� */
    for (sum = 0; s_task_over_flag != 1; )
    {

#if !INCLUDE_COM_TIMEOUT    /* ��ͨ��ȡģʽ */
        Received = read(fd, (char *)RxBuffer, sizeof(RxBuffer));
#else   /* ��ʱ��ȡģʽ */
        /* ���ó�ʱʱ�� */
        timeout.tv_sec = 0;         /* 0 ��λs */
        timeout.tv_usec = 100000;   /* 100ms ��λus*/
        Received = com_read_ex(fd, RxBuffer, sizeof(RxBuffer), &timeout);
        if (Received == 0)
        {
            continue ;  /* ��ʱ�������ȡ */
        }
#endif
        sum += Received;
        if (g_dtp_debug)
        {
            printf("--- ");
            for (i = 0; i < Received; i++)
            {
                printf("%02X ", RxBuffer[i]);
                if (((i + 1) % 16) == 0) printf("\n    "); /* 16��һ���� */
            }
            printf("--- com%d\n", RxCom + 1);
        }
        else
        {
            printf("COM%d received %4d bytes, last data = %X\n", RxCom + 1, sum, RxBuffer[Received - 1]);
        }
    }

    s_com_tid[RxCom] = 0;

    /* �رմ��� */
    close(fd);

    return 0;
}

/********************************************************************
��������:   usb_test

��������:   USB�ڲ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��U��д��һ���ļ���Ȼ���ȡ����

�޸ļ�¼:   2010-12-14      ���ı  ����
********************************************************************/
int usb_test()
{
    int fd = 0;
    int i = 0;
    int ret = 0;
    int written = 0;
    int Bytesread = 0;
    int input = 0;
    int MassUsb = 0;
    unsigned char TxBuffer[1024] = {0};
    unsigned char RxBuffer[1024] = {0};
    long long int llStart = 0;
    long long int llEnd = 0;

    /* ���Է�������0x00 - 0xFF */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i + MassUsb + 1;
    }

    /* ָ��U�� */
    printf("USB Test, Input MessStorage Number:(0-1)\n");
    input = GetKeyInput(10);
    MassUsb = input % 2;

    /* ��U�� */
    fd = open(g_MassUsbName[MassUsb], O_RDWR | O_CREAT, 0644);
    if (fd == ERROR)
    {
        printf("Open %s failed!\n", g_MassUsbName[MassUsb]);
        return fd;
    }

    printf("Open %s succeeded\n", g_MassUsbName[MassUsb]);

    /* д������ļ� */
    for (i = 0; i < 1024; i++)
    {
        written += write(fd, (char *)TxBuffer, sizeof(TxBuffer));
    }
    printf("USB%d written %d(byte)\n", MassUsb, written);

    /* �ļ�ָ����� */
    lseek(fd, 0, SEEK_SET);

    pentiumTscGet64(&llStart);
    /* ��ȡ�����ļ� */
    for (i = 0; i < 1024; i++)
    {
        Bytesread += read(fd, (char *)RxBuffer, sizeof(RxBuffer));
        if (memcmp(TxBuffer, RxBuffer, sizeof(RxBuffer)) != 0)
        {
            printf("Data check error!\n");
            close(fd);
            return -1;
        }
    }
    pentiumTscGet64(&llEnd);
    printf("USB%d read %d(byte), elapse %f(ms)\n", MassUsb, Bytesread, (llEnd - llStart) * 1000.0 / BOARD_CPU_FREQUENCE);

    close(fd);

    return ret;
}

#if INCLUDE_WINDML_TEST
/********************************************************************
��������:   windml_test

��������:   WindML����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ϵͳ��ʾ����

�޸ļ�¼:   2010-10-12      ���ı  ����
********************************************************************/
int windml_test()
{
    /* ����WindML�ṩ�Ĳ��Գ��� */
    windMLDemo(0);

    return 0;
}
#endif

/********************************************************************
��������:   audio_test

��������:   ��Ƶ�������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:

�޸ļ�¼:   2011-00-00      ���ı  ����
********************************************************************/
int audio_test()
{
    return 0;
}

/********************************************************************
��������:   dtp_debug_onoff

��������:   dtp���Կ���

��������        ����            ����/���           ����
onoff           int             input               ���Կ���(1:�� 0:�ر�)

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:

�޸ļ�¼:   2010-10-29      ���ı  ����
********************************************************************/
int dtp_debug_onoff(int onoff)
{
    g_dtp_debug = onoff;

    return 0;
}

/********************************************************************
��������:   com_read_ex

��������:   ���ڶ�ȡ��ʱ���غ���

��������        ����            ����/���           ����
fd              int             input               �����ļ�������
buffer          char*           input               ��ȡ������ָ��
maxbytes        size_t          input               ��ȡ����ֽ���
pTimeOut        struct timeval* input               ��ʱ��Ϣ�ṹ��

����ֵ  :   -1:����ʧ�� 0:��ʱ 1-maxbytes:���ص�����

����˵��:   ������װ������read������select���� �γ�һ��������ָ��ʱ����û��
            ��ȡ������ʱ�ͷ�����ǰ���������ݵĺ���

�޸ļ�¼:   2011-01-26      ���ı  ����
********************************************************************/
int com_read_ex(int fd, char *buffer, size_t maxbytes, struct timeval *pTimeOut)
{
    int sum = 0;
    int ret = 0;
    fd_set fdset;
    char *p = buffer;

    /* �����ļ����������� */
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);

    for (; sum < maxbytes;)
    {
        /* ʹ��select�����жϴ���״̬ */
        ret = select(fd + 1, &fdset, NULL, NULL, pTimeOut);
        if (ret == 0)
        {
            /* ����ʱ����������յ������� */
            return sum;
        }
        if (ret == -1)
        {
            return -1;
        }
        /* �жϵ�ǰ�����Ƿ������ݿɶ� */
        if (FD_ISSET(fd, &fdset))
        {
            ret = read(fd, p, 1);
            if (ret == -1)
            {
                return -1;
            }
            p += ret;
            sum += ret;
        }
    }

    return sum;
}

/********************************************************************
��������:   int_test

��������:   �ж���Ӧ����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����������IRQ�����Խ��в��� ������ЩIRQ��Ӱ��ϵͳ����
            BIOS����Ҫ�ͷ����IRQ

�޸ļ�¼:   2011-05-31      ���ı  ����
********************************************************************/
int int_test()
{
    int input = 0;
    int ret = 0;

    /* ָ�������ж� */
    printf("Input IRQ Number:(3,4,5,6,7,9,10,11,12,13,15)\n");
    input = GetKeyInput(10);

    /* ע���ж� */
    ret = intConnect(INUM_TO_IVEC(INT_VEC_GET(input)), irq_isr, input);
    if (ret != 0)
    {
        printf("intConnect failed!\n");
        return -1;
    }

    /* ʹ���ж� */
    ret = sysIntEnablePIC(input);
    if (ret != 0)
    {
        printf("sysIntEnablePIC failed!\n");
        return -1;
    }

    return 0;
}

/********************************************************************
��������:   file_test

��������:   �ļ���д����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����ȴ���һ��64MB���ļ���Ȼ���ȡ����ʱ�䡣
            ��ΪVxWorksʹ��PIO_2ģʽ����CF����д�ٶ���5MB���ҡ�

�޸ļ�¼:   2011-05-31      ���ı  ����
********************************************************************/
int file_test()
{
    int ret = 0;
    FILE *fp = NULL;
    int i = 0;
    long long int llStart = 0;
    long long int llEnd = 0;

    /* ����ֵ */
    for (i = 0; i < sizeof(g_ataBuffer); i++)
    {
        g_ataBuffer[i] = i;
    }

    /* ���ļ� */
    fp = fopen(g_AtaName[0], "wb+");
    if (fp == NULL)
    {
        printf("fopen failed!%s\n", g_AtaName[0]);
        return -1;
    }

    printf("Writing file...\n");

    /* д64M�ļ�������ʱ�� */
    pentiumTscGet64(&llStart);
    for (i = 0; i < 8192; i++)
    {
        ret = fwrite(g_ataBuffer, sizeof(g_ataBuffer), 1, fp);
        if (ret != 1)
        {
            printf("fwrite failed!%d\n", ferror(fp));
            return -1;
        }
    }
    pentiumTscGet64(&llEnd);

    /* ˢ�»��� */
    ret = fflush(fp);

    printf("Write 64MB file, elapsed time = %f(ms)\n", (llEnd - llStart) * 1000.0 / BOARD_CPU_FREQUENCE);

    /* �����ļ�ָ�� */
    ret = fseek(fp, 0, SEEK_SET);

    printf("Reading file...\n");

    /* ��64M�ļ�������ʱ�� */
    pentiumTscGet64(&llStart);
    for (i = 0; i < 8192; i++)
    {
        ret = fread(g_ataBuffer, sizeof(g_ataBuffer), 1, fp);
        if (ret != 1)
        {
            printf("fread failed!%d\n", ferror(fp));
            return -1;
        }
    }
    pentiumTscGet64(&llEnd);

    printf("Read 64MB file, elapsed time = %f(ms)\n", (llEnd - llStart) * 1000.0 / BOARD_CPU_FREQUENCE);

    fclose(fp);

    return 0;
}

/********************************************************************
��������:   irq_isr

��������:   �жϷ������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��ϵͳ��Ӧ�ж�ʱ ��ӡ��Ϣ

�޸ļ�¼:   2011-05-31      ���ı  ����
********************************************************************/
void irq_isr(void *irq)
{
    logMsg("IRQ %d happened.\n", (int)irq, 0, 0, 0, 0, 0);

    return ;
}

/********************************************************************
��������:   watchdog_test

��������:   Ӳ�����Ź�����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ϵͳ�����趨ʱ����������� �忨���ÿ��Ź�����

�޸ļ�¼:   2011-05-31      ���ı  ����
********************************************************************/
int watchdog_test()
{
    int input = 0;
    int ret = 0;
    int mode = 0;
    unsigned short ushRuntime = 0;

    /* ��������ģʽ */
    sysOutByte(0x2e, 0x55);

    /* �����߼��豸10 */
    sysOutByte(0x2e, 0x07);
    sysOutByte(0x2f, 0x0a);

    /* ����CLOCKI32�Ĵ��� */
    sysOutByte(0x2e, 0xf0);
    sysOutByte(0x2f, 0x01);

    /* ��ȡruntime�Ĵ������ַ */
    sysOutByte(0x2e, 0x60);
    ushRuntime = sysInByte(0x2f);

    sysOutByte(0x2e, 0x61);
    ushRuntime = (ushRuntime << 8) | sysInByte(0x2f);
    printf("ushRuntime = 0x%X\n", ushRuntime);

    /* �˳�����ģʽ */
    sysOutByte(0x2e, 0xaa);

    /* ����GP60�Ĵ��� LXϵ������0x0e PMϵ������0x0c */
    sysOutByte(ushRuntime + 0x47, 0x0e);

    /* ָ�����Ź���ʱ��λ */
    printf("Input watch dog timer unit:(1:sencond 0:minute)\n");
    input = GetKeyInput(10);
    mode = input & 0x01;

    /* ����WDT_TIME_OUT�Ĵ��� */
    sysOutByte(ushRuntime + 0x65, mode << 7);  /* 1:�� 0:�� */

    printf("Input watch dog timer count:(0-255)\n");
    input = GetKeyInput(10);

    /* ����WDT_VAL�Ĵ��� */
    sysOutByte(ushRuntime + 0x66, input);      /* ��ʱ���� */

    printf("System will restart in %d %s.\n", input & 0xff, mode ? "seconds" : "minutes");

    return ret;
}

/********************************************************************
��������:   dma_test

��������:   i8237 DMA����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   DMA������ҪӲ����� ���Բ���DREQ��DACK�ź�
            ��ͬ��DMA����ģʽ���޸Ĵ������.ʹ�ù�˾429�忨����DMA��������
            ����OUT1A->IN1A OUT1B->IN1B
            sysOutWord(0x380 + 4, 0x6020);
            sysOutWord(0x380, 0x1234);
            sysOutWord(0x380 + 2, 0x5678);
            sysInWord(0x380 + 8) 0x4:���Է��� 0x01:������
            ���DMA���Գɹ���0x200000��ַ���д��������

�޸ļ�¼:   2011-05-31      ���ı  ����
********************************************************************/
int dma_test()
{
    int ret = 0;
    int input = 0;
    int channel = 0;
    int direction = 0;
    unsigned char uchValue = 0;
    int count = 0;

    printf("Input dma channel:(0, 1, 2, 3, 5, 6, 7)\n");
    input = GetKeyInput(10);
    channel = input % 8;

    printf("Input transfer direction:(0:IO to MEM 1:MEM to IO)\n");
    input = GetKeyInput(10);
    direction = input & 0x01;

    printf("Input transfer count:(0-65535)\n");
    input = GetKeyInput(10);
    count = input & 0xffff;

    /* �ر�CACHE���� */
    cacheInvalidate(DATA_CACHE, (void *)DMA_BUFFER_ADDR, DMA_BUFFER_SIZE);

    if (channel < 4)    /* ͨ��0 1 2 3 */
    {
        /* ��λDMA������ */
        sysOutByte(DMAC0_CLEAR_ALL, 0x00);

        /* ����DMA���� */
        sysOutByte(DMAC0_MASK, 0x04 | channel);

        /* д�빤��ģʽ */
        uchValue = DMA_MODE_SINGLE | DMA_MODE_AUTO_ENABLE | channel;
        uchValue = uchValue | (direction == 0 ? DMA_MODE_WRITE : DMA_MODE_READ);
        sysOutByte(DMAC0_MODE, uchValue);

        /* д���ڴ�ռ��ҳ��ַ */
        uchValue = (DMA_BUFFER_ADDR & 0x00ff0000) >> 16;
        sysOutByte(dma_page_addr[channel], uchValue);

        /* ����Ⱥ󴥷��Ĵ��� */
        sysOutByte(DMAC0_CLEAR_FF, 0xff);

        /* д���ڴ�ռ��ƫ�Ƶ�ַ �ȵ�λ ���λ */
        uchValue = (unsigned char)(DMA_BUFFER_ADDR & 0x00000ff);
        sysOutByte(DMAC0_CH_CA(channel), uchValue);
        uchValue = (unsigned char)(DMA_BUFFER_ADDR >> 8);
        sysOutByte(DMAC0_CH_CA(channel), uchValue);

        /* ����Ⱥ󴥷��Ĵ��� */
        sysOutByte(DMAC0_CLEAR_FF, 0xff);

        /* д�봫����� �ȵ�λ ���λ */
        uchValue = (count - 1) & 0x00ff;
        sysOutByte(DMAC0_CH_CC(channel), uchValue);
        uchValue = (count - 1) >> 8;
        sysOutByte(DMAC0_CH_CC(channel), uchValue);

        /* ����DMA����ʱ�� */
        sysOutByte(DMAC0_STATUS_CMD, DMA_CMD_DACK_L | DMA_CMD_DREQ_H | DMA_CMD_MEM_ENABLE);

        /* ʹ��DMA */
        sysOutByte(DMAC0_MASK, channel);
    }
    else                /* ͨ��4 5 6 7 ����4ͨ��������ʹ�� */
    {
        /* ��λDMA������ */
        sysOutByte(DMAC1_CLEAR_ALL, 0x00);

        /* ����DMA���� */
        sysOutByte(DMAC1_MASK, 0x04 | (channel - 4));

        /* д�빤��ģʽ */
        uchValue = DMA_MODE_SINGLE | DMA_MODE_AUTO_ENABLE | (channel - 4);
        uchValue = uchValue | (direction == 0 ? DMA_MODE_WRITE : DMA_MODE_READ);
        sysOutByte(DMAC1_MODE, uchValue);

        /* д���ڴ�ռ��ҳ��ַ 2�ֽڶ��� */
        uchValue = ((DMA_BUFFER_ADDR & 0x00ff0000) >> 16) & 0xFE;
        sysOutByte(dma_page_addr[channel], uchValue);

        /* ����Ⱥ󴥷��Ĵ��� */
        sysOutByte(DMAC1_CLEAR_FF, 0xff);

        /* д���ڴ�ռ��ƫ�Ƶ�ַ �ȵ�λ ���λ 16λ����ʱ��2���ֽ�Ϊ��λ */
        uchValue = (unsigned char)((DMA_BUFFER_ADDR >> 1) & 0x00000ff);
        sysOutByte(DMAC1_CH_CA(channel), uchValue);
        uchValue = (unsigned char)((DMA_BUFFER_ADDR >> 1) >> 8);
        sysOutByte(DMAC1_CH_CA(channel), uchValue);

        /* ����Ⱥ󴥷��Ĵ��� */
        sysOutByte(DMAC1_CLEAR_FF, 0xff);

        /* д�봫����� �ȵ�λ ���λ 16λ����ʱ��2���ֽ�Ϊ��λ�Ҽ����ݼ� */
        uchValue = (count - 1) & 0x00ff;
        sysOutByte(DMAC1_CH_CC(channel), uchValue);
        uchValue = (count - 1) >> 8;
        sysOutByte(DMAC1_CH_CC(channel), uchValue);

        /* ����DMA����ʱ�� */
        sysOutByte(DMAC1_STATUS_CMD, DMA_CMD_DACK_L | DMA_CMD_DREQ_H | DMA_CMD_MEM_ENABLE);

        /* ʹ��DMA */
        sysOutByte(DMAC1_MASK, channel - 4);
    }

    return ret;
}

/********************************************************************
��������:   realtime_test

��������:   ʵʱʱ�Ӳ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   VxWorks��û�ж�ȡϵͳʱ�亯�� ֻ��ֱ�Ӷ�ȡʵʱʱ������

�޸ļ�¼:   2011-06-10      ���ı  ����
********************************************************************/
int realtime_test()
{
    int century = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    unsigned char uch = 0;

    /* ��ȡRTCֵ */
    sysOutByte(RTC_INDEX, RTC_CENTURY); /* ���� */
    uch = sysInByte(RTC_DATA);
    century = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_YEAR);    /* �� */
    uch = sysInByte(RTC_DATA);
    year = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_MONTH);   /* �� */
    uch = sysInByte(RTC_DATA);
    month = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_DAY);     /* �� */
    uch = sysInByte(RTC_DATA);
    day = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_HOUR);    /* ʱ */
    uch = sysInByte(RTC_DATA);
    hour = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_MINUTE);  /* �� */
    uch = sysInByte(RTC_DATA);
    minute = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_SECOND);  /* �� */
    uch = sysInByte(RTC_DATA);
    second = BCD_TO_BIN(uch);

    printf("The current date and time is %4d-%02d-%02d(y-m-d) and %02d:%02d:%02d(h-m-s).\n",
           century * 100 + year, month, day, hour, minute, second);

    /* ����RTCֵ */
    sysOutByte(RTC_INDEX, RTC_CENTURY); /* ���� */
    uch = BIN_TO_BCD(20);               /* 20���� */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_YEAR);    /* �� */
    uch = BIN_TO_BCD(4);                /* 4�� */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_MONTH);   /* �� */
    uch = BIN_TO_BCD(5);                /* 5�� */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_DAY);     /* �� */
    uch = BIN_TO_BCD(6);                /* 1�� */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_HOUR);    /* ʱ */
    uch = BIN_TO_BCD(19);               /* 19ʱ */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_MINUTE);  /* �� */
    uch = BIN_TO_BCD(28);               /* 28�� */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_SECOND);  /* �� */
    uch = BIN_TO_BCD(37);               /* 37�� */
    sysOutByte(RTC_DATA, uch);

    printf("The current date and time is setted to 2004-05-06 and 19:28:37.\n");

    return 0;
}

/********************************************************************
��������:   std_test

��������:   ��׼��������л�

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ���������л���׼���������ָ�����ڿ���̨����ʾ������̨��

�޸ļ�¼:   2011-06-10      ���ı  ����
********************************************************************/
int std_test()
{
    int ret = 0;
    int STD = 0;
    int fd = 0;
    int input = 0;

    /* ָ����׼�������ʹ�ô��� */
    printf("Input STD COM Number:(0:pcConsole 1-2:COM) %dbps\n", g_com_baud);
    input = GetKeyInput(10);
    STD = input % 3;

    if (STD == 0)
    {
        /* ����ʾ������̨ */
        fd = open("/pcConsole/0", O_RDWR, 0);
    }
    else
    {
        /* �򿪴��ڿ���̨ */
        fd = open(g_ExtComName[STD - 1], O_RDWR, 0);

        /* ���ò����� */
        ret |= ioctl (fd, FIOBAUDRATE, g_com_baud);
        ret |= ioctl (fd, FIOSETOPTIONS, OPT_TERMINAL);
    }

    /* ���ñ�׼�������ʹ�õ��豸 */
    ioGlobalStdSet (STD_IN,  fd);
    ioGlobalStdSet (STD_OUT, fd);
    ioGlobalStdSet (STD_ERR, fd);

    return ret;
}

#if INCLUDE_NET_SWITCH
/********************************************************************
��������:   netswitch_callback

��������:   ˫�����л������ص�����

��������        ����            ����/���           ����
master          int             input               ��ǰ������

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʵ��˫��������

�޸ļ�¼:   2013-03-11  ���ı  ����
********************************************************************/
void netswitch_callback(int master)
{
    static int count = 0;

    if ((count++ % 600) == 0)
    {
        printf("netswitch_callback is called. master = %d.\n", master);
    }

    return ;
}

/********************************************************************
��������:   netswitch_test

��������:   ˫�����л�

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʵ��˫��������

�޸ļ�¼:   2011-07-04  ���ı  ����
            2012-12-19  ���ı  ����    ���ӿ����κ�����ARP����
********************************************************************/
int netswitch_test()
{
    int ret = 0;
    int input = 0;
    int master = 0;
    int slave = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};
    route_entry_t entry1;
    arp_entry_t entry2;

    sysClkRateSet(1000);
    printf("Set sysclkrate = 1000\n");

    printf("Input master net adapter number(0-5):\n");
    input = GetKeyInput(10);
    master = input % 6;

    printf("Input slave net adapter number(0-5):\n");
    input = GetKeyInput(10);
    slave = input % 6;

    printf("Input adapters use same mac or not(0:same 1: different)\n");
    input = GetKeyInput(10);

    ret = InitNetSwitch(master, slave, input, 0);

    /* ����·����Ϣ ʵ��Ӧ��ʱ�޸�Ϊ�ʵ�ֵ */
#if VXWORKS_TYPE
    strcpy(entry1.dest, "0.0.0.0");
    strcpy(entry1.gate, "192.168.1.254");
#else
    entry1.dest = inet_addr("0.0.0.0");
    entry1.gate = inet_addr("192.168.1.254");
#endif
    AddRouteEntry(0, &entry1, 1);

    /* ����ARP������Ϣ ʵ��Ӧ��ʱ�޸�Ϊ�ʵ�ֵ */
    entry2.mac[0] = 0xFF;
    entry2.mac[1] = 0xFF;
    entry2.mac[2] = 0xFF;
    entry2.mac[3] = 0xFF;
    entry2.mac[4] = 0xFF;
    entry2.mac[5] = 0xFF;
    entry2.ip[0] = 0xFF;
    entry2.ip[1] = 0xFF;
    entry2.ip[2] = 0xFF;
    entry2.ip[3] = 0xFF;
    AddArpEntry(0, &entry2, 1);

    /* ע�ᱨ���ص����� */
    RegisterAlarm(netswitch_callback);

#if NET_SWITCH_TYPE
    sprintf(NetName, "gei%d", master);
#else
    sprintf(NetName, "fei%d", master);
#endif

    ifAddrGet(NetName, IpAddress);
    printf("Current IP is %s\n", IpAddress);

    return ret;
}
#endif

/********************************************************************
��������:   lpt_test

��������:   ���ڲ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��BIOS�����ò���ΪSPP��Bi-Dir��ģʽ

�޸ļ�¼:   2011-11-16      ���ı  ����
********************************************************************/
int lpt_test()
{
    unsigned char uchOut = 0;
    unsigned char uchIn = 0;
    int mode = 0;
    int ret = 0;

    printf("LPT Base Address(0x%03X)\n", LPT_BASE_ADDRESS);

    printf("Input LPT Data Mode(0:output 1:input):\n");

    mode = GetKeyInput(10) % 2;

    /* �������ݼĴ����������ģʽ */
    sysOutByte(LPT_BASE_ADDRESS + 2, mode << 5);

    if (mode == 0)
    {
        printf("Input LPT Output Data(0x00-0xFF):\n");
        uchOut = GetKeyInput(16);
        sysOutByte(LPT_BASE_ADDRESS, uchOut);   /* ���3.3V */
    }
    else
    {
        printf("Now Change Input Data, press enter\n");
        getchar();
        uchIn = sysInByte(LPT_BASE_ADDRESS);    /* ���Ż�������5V */
        printf("LPT Input Data 0x%02X\n", uchIn);
    }

    /* ͨ��״̬�Ĵ������� */
    uchIn = sysInByte(LPT_BASE_ADDRESS + 1) & 0xF8; /* bit0 - bit2��Ч ע��bit7���� ���Ż�������5V */
    printf("LPT Input Data(status) 0x%02X\n", uchIn);

    return ret;
}

/********************************************************************
��������:   soft_watchdog_test

��������:   ������Ź�����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����VxWorks��������Ź�

�޸ļ�¼:   2011-12-04      ���ı  ����
********************************************************************/
int soft_watchdog_test()
{
    int ret = 0;
    int count = 0;
    int input = 0;

    printf("Input watchdog period(tick) :(10-65535)\n");
    input = GetKeyInput(10) & 0xffff;
    s_ticks = (input < 10) ? 10 : input;

    printf("Input watchdog rum times :(1-65535)\n");
    input = GetKeyInput(10) & 0xffff;
    count = (input > 0) ? input : 1;

    /* �������Ź���ʱ�� */
    s_wdId = wdCreate();
    if (s_wdId == NULL)
    {
        printf("wdCreate failed!\n");
        return -1;
    }

    /* �������Ź� */
    wdStart(s_wdId, s_ticks, (FUNCPTR)watch_dog_callback, count);

    return ret;
}

/********************************************************************
��������:   watch_dog_callback

��������:   ���Ź�����

��������        ����            ����/���           ����

����ֵ  :   ��

����˵��:   �����Ź���ʱ����ʱʱ����ô˺��������Ź������в���ʹ��printf������

�޸ļ�¼:   2011-05-18      ���ı  ����
********************************************************************/
static void watch_dog_callback(int para)
{
    if (para > 0)
    {
        logMsg("\nwatch_dog was called.%d\n", para, 0, 0, 0, 0 , 0);

        /* �ظ��������Ź� */
        wdStart(s_wdId, s_ticks, (FUNCPTR)watch_dog_callback, para - 1);
    }
    else
    {
        logMsg("\nwatch_dog_callback finished.\n", 0, 0, 0, 0, 0 , 0);

        /* ɾ�����Ź� */
        wdDelete(s_wdId);
    }

    return ;
}

/********************************************************************
��������:   soft_watchdog_test2

��������:   ������Ź�����

��������        ����            ����/���       ����
count           int             input           ���Ź����д���

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �������Ź����ڶ�UDP����

�޸ļ�¼:   2015-4-28      ����  ����
********************************************************************/
int soft_watchdog_test2(int count)
{
    int ret = 0;

    /* �������Ź���ʱ�� */
    s_wdId2 = wdCreate();
    if (s_wdId2 == NULL)
    {
        printf("wdCreate failed!\n");
        return -1;
    }

    /* �������Ź�������Ϊ10ms */
    sysClkRateSet(1000);
    wdStart(s_wdId2, (sysClkRateGet() / 100), (FUNCPTR)watch_dog_callback2, count);

    return ret;
}
/********************************************************************
��������:   watch_dog_callback2

��������:   ������Ź�����2

��������        ����            ����/���           ����
para            int             input               ���Ź����д���

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �������Ź����ڶ�UDP����

�޸ļ�¼:   2015-4-28      ����  ����
********************************************************************/
static void watch_dog_callback2(int para)
{
    if (para > 0)
    {
        /* ���ɼ������� */
        *(unsigned int *)(&g_TxBuffer[0]) = g_txBufferCount;

        g_txBufferCount++;

        /* �ͷ��ź��� */
        semGive(s_Sem2);

        /* �ظ��������Ź�,����Ϊ10ms */
        wdStart(s_wdId2, (sysClkRateGet() / 100), (FUNCPTR)watch_dog_callback2, para - 1);
    }
    else
    {
        /* ��������� */
        g_txBufferCount = 0;

        logMsg("\nUDP package send finished.\n", 0, 0, 0, 0, 0 , 0);

        /* ɾ�����Ź� */
        wdDelete(s_wdId2);
    }

    return ;
}

/********************************************************************
��������:   udp_client_2

��������:   ����һ��UDP�ͻ��ˣ����10ms����һ��UDP���ݰ�

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ע�������ջ ʹ������ģʽ

�޸ļ�¼:   2015-4-28      ����  ����
********************************************************************/
int udp_client_2()
{
    int ret;
    int to_send = 16;
    int count = 0;
    int ip1 = 0;
    int ip2 = 0;
    char IpAddress[32] = {0};
    unsigned long input = 0;
    int client = 0;
    struct sockaddr_in serverAddr;

    /* �����׽��� */
    client = socket(AF_INET, SOCK_DGRAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create udp socket failed!\n");
        goto Exit;
    }

    /* ���÷��ͻ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* ���ý��ջ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&g_TxBuffer, 0x00, sizeof(g_TxBuffer));

    /* ���뷢�ʹ��� */
    printf("UDP Test, Input Transmit Count(1-1000000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 1000000) : 1;

    /* ����IP��ַ�����ڶ�λ�����һλ */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;
    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* ���÷�������Ϣ */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (UDP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

    s_Sem2 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (s_Sem2 == NULL)
    {
        printf("semBCreate failed!\n");
        goto Exit;
    }

    /* ����taskSend���� */
    s_tid = taskSpawn("udp_task", 101, 0, 30 * 1024, (FUNCPTR)udp_task, client, (int)&serverAddr, 0, 0, 0, 0, 0, 0, 0, 0);
    if (s_tid == -1)
    {
        printf("taskSpawn failed!\n");
        goto Exit;
    }

    /* �������Ź����ڲ�������Ϊ10ms��ʱ */
    soft_watchdog_test2(count);

    /* ��ʱ�������������ݷ��� */
    printf("Press any key to stop send %s:%d.\n", IpAddress, UDP_SERVER_PORT);
    GetKeyInput(10);

Exit:
    /* �ر��׽��� */
    if(client != 0)
    {
        close(client);
    }

    /*ɾ���ź��� */
    if(s_Sem2 != 0)
    {
        semDelete(s_Sem2);
    }

    /* ɾ������ */
    if(s_tid != 0)
    {
        taskDelete(s_tid);
    }

    /* ɾ�����Ź� */
    wdDelete(s_wdId2);

    /* ���Ź���������� */
    g_txBufferCount = 0;

    return ret;
}

/********************************************************************
��������:   udp_task

��������:   ����udp����

��������        ����                ����/���   ����
sock            int                 input       ��������ʹ�õ�socket
serverAddr      struct sockaddr_in* input       ���͵�ַ����ָ��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����һֱ������ֱ�����Ź������ź���

�޸ļ�¼:   2015-4-28      ����  ����
********************************************************************/
int udp_task(int sock, struct sockaddr_in *pServerAddr)
{
    int sent = 0;

    for(;;)
    {
        /* �����������ȴ����Ź������ź��� */
        if(semTake(s_Sem2, WAIT_FOREVER) == ERROR)
        {
            return -1;
        }
        sent = sendto(sock, (char *)g_TxBuffer, 16, 0, (struct sockaddr *)pServerAddr, sizeof(struct sockaddr_in));
        printf(".", sent);
    }

    return 0;
}

/********************************************************************
��������:   speaker_test

��������:   ���������Գ���

��������        ����            ����/���           ����

����ֵ  :   ��

����˵��:   �����������ɶ�ʱ��2��������ʱ��2���ź��ɶ˿�B������
            ������ʹ��ʱ��Ҫ���ߡ�

�޸ļ�¼:   2012-04-18      ������  ����
********************************************************************/
int speaker_test()
{
    unsigned short ushData = 0;
    unsigned char uchMsb = 0;
    unsigned char uchLsb = 0;
    unsigned char uchReg = 0;
    float input = 0;
    int ret = 0;

    printf("Input speaker frequency(Hz) :(20-5000)\n");
    input = GetKeyInput(10) & 0xffff;
    input = ((input < 20) || (input > 5000)) ? 100 : input;

    ushData = (unsigned short)(CLOCK / input);
    uchLsb = ushData & 0xFF;
    uchMsb = ushData >> 8;

    printf("BEEPING(%04X)...if it do not work, check the jumper\n", ushData);

    sysOutByte(TIMER_CONTROL, 0xb6);            /*���ö�ʱ��2������ʽ*/
    sysOutByte(TIMER2, uchLsb);
    sysOutByte(TIMER2, uchMsb);

    uchReg = sysInByte(TIMER2_GATE);
    sysOutByte(TIMER2_GATE, uchReg | 0x03);     /*����������*/

    printf("Press Any Key to Stop\n");
    getchar();

    sysOutByte(TIMER2_GATE, uchReg);            /*�رշ�����*/

    return ret;
}

/********************************************************************
��������:   com_write_ex

��������:   ��ѯ��ʽ���ʹ�������

��������        ����            ����/���           ����
ushComBase      unsigned short  input               ���ڻ���ַ
TxBuffer        unsigned char   input               �������ݻ�����
length          int             input               �������ݳ���(��λ�ֽ�)

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��Щʱ��(��Ч�ʷ��ʹ�������ʱ)��Ҫʹ�ò�ѯ��ʽ���ʹ�������

�޸ļ�¼:   2012-09-04      ���ı  ����
********************************************************************/
int com_write_ex(unsigned short ushComBase, unsigned char TxBuffer[], int length)
{
    int i = 0;

    for (i = 0; i < length; i++)
    {
        sysOutByte(ushComBase, TxBuffer[i]);        /* �������� */
        while(!(sysInByte(ushComBase + 5) & 0x20)); /* �ȴ����ݷ������ �˴��жϷ�����������485 */
    }

    return 0;
}

/********************************************************************
��������:   tcp_rx_performance

��������:   ������������TCPͨѶʱ������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��������������������Ľ�������

�޸ļ�¼:   2013-04-27      ���ı  ����
********************************************************************/
int tcp_rx_performance()
{
    int input = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};

    /* ʹ��Tick���� ������TickΪ1ms */
    sysClkRateSet(1000);

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    input = GetKeyInput(10) % 12;
    if (input < 6)
    {
        sprintf(NetName, "fei%d", input);
    }
    else
    {
        sprintf(NetName, "gei%d", input - 6);
    }
    ifAddrGet(NetName, IpAddress);
    printf("Net adapter's ip address is %s.\n", IpAddress);

    if (s_net_tid[input + TCP_PERFORM_TID] == 0)
    {
        /* ������������ */
        s_net_tid[input + TCP_PERFORM_TID] = taskSpawn("tTcpPerformRecv", 100, 0, 1024 * 40, (FUNCPTR)tTcpPerformRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* ��ʱ */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("TCP perform has been already established.\n");
    }

    return s_net_tid[input + TCP_PERFORM_TID];
}

/********************************************************************
��������:   tTcpPerformRecv

��������:   TCP��������������

��������        ����            ����/���           ����
fd              int             input               ���մ��ھ��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ʹ��������ʽ��ȡ δ����Ҫ�޸�

�޸ļ�¼:   2013-04-27      ���ı  ����
********************************************************************/
int tTcpPerformRecv(int ip, int net)
{
    int ret = 0;
    int server = 0;
    int client = 0;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int socketLength = sizeof(struct sockaddr_in);
    unsigned char RxBuffer[256];
    int length = 0;
    long sum = 0;
    int start = 0;
    int end = 0;
    float speed = 0;

    /* �����׽��� */
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == ERROR)
    {
        printf("Create tcp socket failed!\n");
        return -1;
    }

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_CLIENT_PORT);   /* �����˿ں� */
    serverAddr.sin_addr.s_addr = ip;                /* ͨ��IP��ַѡ������ */

    /* �󶨶˿� */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("Bind tcp socket failed!\n");
        goto Exit;
    }

    /* �����˿� */
    if (listen(server, 1) == -1)
    {
        printf("Listen tcp socket failed!\n");
        goto Exit;
    }

    printf("TCP server is listening, port = %d.\n", TCP_CLIENT_PORT);

    /* �ȴ��ͻ������� */
    client = accept(server, (struct sockaddr *)&clientAddr, &socketLength);
    if (client == -1)
    {
        printf("Accept tcp socket failed!\n");
        goto Exit;
    }

    /* ��ʼ��ʱ */
    start = tickGet();

    /* ��ʾ�������� */
    for (sum = 0; s_task_over_flag != 1 && sum < TCP_PERFORMANCE_SIZE; sum += length)
    {
        length = recv(client, (char *)RxBuffer, sizeof(RxBuffer), 0);
        if (length == ERROR)
        {
            printf("recv failed!\n");
            break;
        }

        if (length == 0)
        {
            printf("Perhaps tcp client has disconnected.\n");
            break;
        }
    }

    end = tickGet();

    speed = ((float)sum / 1048.567) / (end - start);

    printf("TCP performance = %f MB\n", speed);

Exit:
    s_net_tid[net + TCP_PERFORM_TID] = 0;
    close(client);
    close(server);

    return ret;
}

/********************************************************************
��������:   tcp_tx_performance

��������:   ������������TCPͨѶʱ������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ��������������������Ľ�������

�޸ļ�¼:   2013-04-27      ���ı  ����
********************************************************************/
int tcp_tx_performance()
{
    int ret = 0;
    int client = 0;
    FILE *fp = NULL;
    struct sockaddr_in serverAddr;
    int i = 0;
    int sent = 0;
    int input = 0;
    int to_send = 2048;
    int ip1 = 0;
    int ip2 = 0;
    unsigned char TxBuffer[2048] = {0};
    char IpAddress[32] = {0};
    int start = 0;
    int end = 0;
    float speed = 0;
    int sum = 0;

    /* ʹ��Tick���� ������TickΪ1ms */
    sysClkRateSet(1000);

    /* �������� */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));

    /* ���ɲ������� */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i;
    }

    /* �����׽��� */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create tcp socket failed!\n");
        goto Exit;
    }

    /* ���÷��ͻ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* ���ý��ջ�������С */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* ����IP��ַ���һλ */
    /* ����IP��ַ�����ڶ�λ�����һλ */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;

    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* ���÷�������Ϣ */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (TCP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

    /* ���ӷ����� */
    if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) == -1)
    {
        ret = ERROR - 1;
        printf("Connect to tcp server failed!\n");
        goto Exit;
    }

    /* ��ʼ��ʱ */
    start = tickGet();

    /* �������� */
    for (sum = 0; sum < TCP_PERFORMANCE_SIZE; sum += sent)
    {
        sent = send(client, (char *)TxBuffer, to_send, 0);
        if (sent != to_send)
        {
            printf("sent = %d\n", sent);
            break;
        }
    }

    end = tickGet();

    speed = ((float)sum / 1048.567) / (end - start);

    printf("TCP performance = %f MB\n", speed);

Exit:
    /* �ر��׽��� */
    if (client != 0)
    {
        close(client);
    }

    /* �ر��ļ� */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
��������:   lcd_test

��������:   ����LCD�ı�����ƹ���

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����ֻ��AT5010��CD6010�忨��Ч���Ĵ������ߺš��豸�š����ܺŹ̶���

�޸ļ�¼:   2013-06-27      ���ı  ����
********************************************************************/
int lcd_test()
{
    int ret = 0;
    unsigned char uch = 0;

    /* ��ȡPCI�豸���ÿռ� */
    pciConfigInByte(0x00, 0x02, 0x00, 0xF4, &uch);

    printf("Input New LCD BackLight Value(0x00-0xFF):(Now = 0x%02X)\n", uch);
    uch = (unsigned char)GetKeyInput(16);

    pciConfigOutByte(0x00, 0x02, 0x00, 0xF4, uch);

    return ret;
}

/********************************************************************
��������:   sem_test

��������:   �����ź�������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����������񣬲��Զ�ֵ�ź�����

�޸ļ�¼:   2014-07-04      ���ı  ����
********************************************************************/
int sem_test()
{
    SEM_ID sem;

    /* ������ֵ�ź��� */
    sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    /* ������������ */
    taskSpawn("tTestSem", 100, 0, 1024 * 40, (FUNCPTR)tTestSem, (int)sem, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    printf("Press any key to give semaphore\n");
    getchar();

    semGive(sem);

    taskDelay(sysClkRateGet());

    semDelete(sem);

    return 0;
}

/********************************************************************
��������:   tTestSem

��������:   �����ź���������

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����������񣬲��Զ�ֵ�ź�����

�޸ļ�¼:   2014-07-04      ���ı  ����
********************************************************************/
int tTestSem(SEM_ID sem)
{
    semTake(sem, WAIT_FOREVER);

    printf("semaphore has been taken.\n");

    return 0;
}

/********************************************************************
��������:   timer0_test

��������:   ����ϵͳ�ж�0

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �������Զ�ʱ��0��ͨ������RTS����źŲ�����

�޸ļ�¼:   2015-05-21      ���ı  ����
********************************************************************/
int timer0_test()
{
    int input = 0;

    printf("Input the system clock rate:(1-1000):\n");
    input = GetKeyInput(10);
    if ((input > 1000) || (input == 0))
    {
        input = 1000;
    }

    /* ����ϵͳʱ�� */
    sysClkRateSet(input);

    printf("sysClkRateGet = %d\n", sysClkRateGet());

    /* ע��ص����� */
    sysClkConnect(timer0_callback, 0);

    return 0;
}

/********************************************************************
��������:   timer0_callback

��������:   ��ʱ��0�Ļص�����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ���ƴ���RTS������Ρ�

�޸ļ�¼:   2015-05-21      ���ı  ����
********************************************************************/
int timer0_callback()
{
    static unsigned char uch = 0x02;

    sysOutByte(0x3F8 + 4, uch);
    uch = ~uch;

    return 0;
}

/********************************************************************
��������:   com_change_baudrate

��������:   �޸Ĵ��ڲ�����

��������        ����            ����/���           ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �޸Ĵ��ڲ����ʡ�

�޸ļ�¼:   2016-04-08      ���ı  ����
********************************************************************/
int com_change_baudrate()
{
    int com = 0;
    int input = 0;
    int fd = 0;
    int ret = 0;

    /* ָ������ */
    printf("Input COM Number:(1-8:COM 9-16:EXTCOM 17-24:CSDCOM)\n");
    input = GetKeyInput(10) % 24;
    com = (input - 1);

    /* ���ò����� */
    printf("Input Baudrate:(0:115.2Kbps 1:230.4Kbps 2:460.8Kbps 3:921.6Kbps 4:1.5Mbps)\n");
    input = GetKeyInput(10) % 5;
    g_com_baud = g_ComBauds[input];

    /* �򿪷��ʹ��� */
    fd = open(g_ExtComName[com], O_RDWR, 0);
    if (fd == ERROR)
    {
        printf("Open %s failed!\n", g_ExtComName[com]);
        return fd;
    }

    printf("Open %s succeeded\n", g_ExtComName[com]);

    /* ���ô��ڲ��� */
    /* ����λ8λ ֹͣλ1λ ��У�� ����ģʽ */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | PARENB);
    ret += ioctl(fd, FIOBAUDRATE, g_com_baud);  /* ������ */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* ԭʼģʽOPT_RAW ��ģʽOPT_LINE �������ѡ�� */
    ret += ioctl(fd, FIOFLUSH, 0);              /* ��ջ����� */

    close(fd);

    return ret;
}
