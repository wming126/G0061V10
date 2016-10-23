/********************************************************************
文件名称:   dtp.c

文件功能:   提供盛博板卡VxWorks操作系统下通用软件测试平台

文件说明:   搭建一个VxWorks操作系统下的通用测试平台 未来方便添加测试功能和测试项

当前版本:   V2.7

修改记录:   2010-10-12  V1.0    徐佳谋  创建
            2012-03-31  V1.1    徐佳谋  升级    增加各种测试函数
            2012-04-18  V1.2    王鹤翔  升级    增加扬声器测试函数
            2012-04-26  V1.3    徐佳谋  升级    增加网络广播包测试
            2012-09-04  V1.4    徐佳谋  升级    增加串口查询发送函数
            2012-12-19  V1.5    徐佳谋  升级    增加双网切换测试函数
            2013-04-27  V1.6    徐佳谋  升级    增加TCP性能测试
            2013-06-07  V1.7    徐佳谋  升级    增加VxWorks6.8支持
            2013-06-27  V1.8    徐佳谋  升级    增加液晶屏背光控制
            2013-11-06  V1.9    徐佳谋  升级    增加调试开关
            2014-01-26  V2.0    徐佳谋  升级    增加千兆网测试
            2014-07-04  V2.1    徐佳谋  升级    增加信号量测试
            2015-03-10  V2.2    徐佳谋  升级    配合双网切换驱动修改
            2015-04-28  V2.3    王明    升级    增加双网切换性能测试
            2015-05-21  V2.4    徐佳谋  升级    增加定时器0测试
            2015-08-13  V2.5    徐佳谋  升级    解决组播接收BUG
            2015-10-22  V2.6    徐佳谋  升级    调整代码名称和位置
            2016-04-08  V2.7    徐佳谋  升级    增加波特率选项
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

/* 串口名称 板载串口1-8 扩展板串口1-8 CSD板串口1-8 */
/* 扩展串口需要在驱动加载的情况下才能测试 */
char *g_ExtComName[] =
{
    "/tyCo/0", "/tyCo/1", "/tyCo/2", "/tyCo/3",
    "/tyCo/4", "/tyCo/5", "/tyCo/6", "/tyCo/7",
    "/tyCoExt/0", "/tyCoExt/1", "/tyCoExt/2", "/tyCoExt/3",
    "/tyCoExt/4", "/tyCoExt/5", "/tyCoExt/6", "/tyCoExt/7",
    "/tyCoCsd/0", "/tyCoCsd/1", "/tyCoCsd/2", "/tyCoCsd/3",
    "/tyCoCsd/4", "/tyCoCsd/5", "/tyCoCsd/6", "/tyCoCsd/7",
};

/* U盘设备名和文件名 */
char *g_MassUsbName[] =
{
    "/bd0/usb_test.txt", "/bd1/usb_test.txt",
    "/bd2/usb_test.txt", "/bd3/usb_test.txt",
};

/* CF卡设备名和文件名 */
char *g_AtaName[] =
{
    "/ata0a/ata_test.bin", "/ata0b/ata_test.bin",
};

/* 串口基地址 */
short g_ExtComAddr[] =
{
    0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x500, 0x500, 0x600, 0x600,
    0x100, 0x108, 0x110, 0x118, 0x120, 0x128, 0x130, 0x138,
    0x100, 0x108, 0x110, 0x118, 0x120, 0x128, 0x130, 0x138,
};

int g_dtp_debug = 1;    /* 调试开关 */

/* DMA控制器页寄存器 */
unsigned char dma_page_addr[8] = {0x87, 0x83, 0x81, 0x82, 0x8f, 0x8b, 0x89, 0x8a};

/* 文件读写使用缓冲区 */
char g_ataBuffer[8192] = {0};
unsigned int g_txBufferCount = 1;
unsigned char g_TxBuffer[16] = {0};

/* 串口波特率 */
int g_com_baud = 115200;

/* 波特率映射表 */
int g_ComBauds[] = {115200, 230400, 460800, 921600, 1500000};

/* 看门狗使用信号量*/
static SEM_ID s_Sem2;
/* UDP任务ID */
static int s_tid;

/* 局部函数声明 */
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

/* 局部变量 */
int s_com_tid[24] = {0};
int s_net_tid[256] = {0};
int s_task_over_flag = 0;
char s_TxBuffer[4096] = {0};
WDOG_ID s_wdId = NULL;  /* 看门狗ID */
WDOG_ID s_wdId2 = NULL;  /* 看门狗ID */
int s_ticks = 0;

static int GetKeyInput(int radix);

/********************************************************************
函数名称:   dtp

函数功能:   测试程序主函数

参数名称        类型            输入/输出           含义
BoardType       int             input               测试板卡类型(LX3160:0x3160 LX3073:0x3072)

返回值  :   0:成功 非0:失败

函数说明:   主函数先打开驱动程序，然后提供用户人机交互界面
            并根据用户选择进行不同的功能测试，具体的测试功能由单独的函数实现
            函数框架可以在未来复用

修改记录:   2010-10-12      徐佳谋  创建
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

        /* 用户输入 */
        printf("Your choice: %d\n", input = GetKeyInput(10));
    }/* end for */
Exit:

    return 0;
}

/********************************************************************
函数名称:   GetKeyInput

函数功能:   获取键盘输入

参数名称        类型            输入/输出           含义
radix           int             input               输入数据进制(10:十进制 16:十六进制)

返回值  :   键盘输入字符转换后的十进制值或十六进制值。

函数说明:   理论上可以用scanf获取用户输入
            但是scanf函数当用户输入错误的数据时会出现异常，进而导致程序异常
            不利于程序健壮性，所以写一个函数替换。函数可应用于VxWorks和Linux

修改记录:   2010-10-27  徐佳谋  创建
            2015-07-10  王明    修改    修改16进制计算问题
********************************************************************/
int GetKeyInput(int radix)
{
    char input = 0;
    int value = 0;

    if (radix == 10)
    {
        while((input = getchar()) != 0x0a)
        {
            value = value * 10 + (input - 0x30);  /* 转换成十进制数 */
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
            value = (value << 4) + input;  /* 转换成十六进制数 */
        }
    }

    return value;
}

/********************************************************************
函数名称:   DecToBin

函数功能:   二进制样式的十进制数转换成十六进制

参数名称        类型            输入/输出           含义
Decimal         unsigned int    input               二进制样式的十进制数(10101011)

返回值  :   返回十六进制值，如参数 = 10100101 返回值 = 0xA5

函数说明:   C语言没有二进制数表示

修改记录:   2010-12-08      徐佳谋  创建
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
函数名称:   DtpExit

函数功能:   退出DTP

参数名称        类型            输入/输出           含义

返回值  :   根据实际情况自行定义

函数说明:   dtp软件退出时需要进行的操作

修改记录:   2010-12-06      徐佳谋  创建
********************************************************************/
int dtp_exit()
{
    int i = 0;

    /* 结束创建的任务 */
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
函数名称:   com_test

函数功能:   串口测试

参数名称        类型            输入/输出           含义

返回值  :   根据实际情况自行定义

函数说明:   串口测试分为CPU板卡测试，扩展串口卡测试和A3CSD扩展串口卡测试（需要安装相应驱动）
            测试时分别指定发送串口和接收串口 用导线对连接两串口的发送和接收引脚

修改记录:   2010-10-12      徐佳谋  创建
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

        /* 用户输入 */
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
函数名称:   eth_test

函数功能:   网口测试

参数名称        类型            输入/输出           含义

返回值  :   根据实际情况自行定义

函数说明:   网口测试先设置网卡IP地址，然后由其他电脑ping这个网卡来测试通断

修改记录:   2010-11-17      徐佳谋  创建
********************************************************************/
int eth_test()
{
    int ret = 0;
    int ip = 0;     /* IP地址最后一个 */
    int unit = 0;
    char IpAddress[32] = {0};
    int input = 0;
    char NetName[32] = {0};

    printf("Input the net adapter number:(0-5:fei0-fei5 6-11:gei0-gei5):\n");
    unit = GetKeyInput(10) % 12;
    if (unit < 6)
    {
        sprintf(NetName, "fei%d", unit);

        /* 网卡加载协议栈 */
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

        /* 网卡加载协议栈 */
        ret = ipAttach(unit - 6, "gei");
        if (ret != 0)
        {
            printf("ipAttach failed!%d\n", unit);
            return ret;
        }
    }

    /* 输入IP地址最后一位 */
    printf("Input the last ip address (1-254):\n");
    input = GetKeyInput(10);
    ip = input ? (input % 255) : 1;

    /* 两网卡不能设在同一网段 */
    /* 设置IP */
    sprintf(IpAddress, "192.168.%d.%d", unit + 1, ip);
    ret = ifAddrSet(NetName, IpAddress);

    /* 使能网络接口 */
    ret = ifFlagSet(NetName, IFF_UP);
    if (ret != 0)
    {
        printf("ifFlagSet failed!\n");
        return ret;
    }

    /* 设置子网掩码 */
    ret = ifMaskSet(NetName, 0xfffffff0);

    printf("Please ping (%s) form other computer, press enter to exit\n", IpAddress);
    GetKeyInput(10);

    /* 网卡卸载协议栈 卸载后网卡无法使用 */
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
函数名称:   socket_test

函数功能:   socket接口测试

参数名称        类型            输入/输出           含义

返回值  :   根据实际情况自行定义

函数说明:   测试UDP和TCP通讯

修改记录:   2010-12-07      徐佳谋  创建
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

        /* 用户输入 */
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
函数名称:   udp_client

函数功能:   创建一个UDP客户端

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2010-12-07      徐佳谋  创建
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

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));

    /* 生成测试数据 */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i;
    }

    /* 创建套接字 */
    client = socket(AF_INET, SOCK_DGRAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create udp socket failed!\n");
        goto Exit;
    }

    /* 设置发送缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 设置接收缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 设置组播TTL值 */
    opt = 255;
    ret = setsockopt (client, IPPROTO_IP, IP_MULTICAST_TTL, &opt, sizeof(opt));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_TTL)!%d\n", errno);
        goto Exit;
    }

    /* 输入发送次数 */
    printf("UDP Test, Input Transmit Count(1-10000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 10000) : 1;

    /* 输入IP地址倒数第二位和最后一位 */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;

    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* 设置服务器信息 */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (UDP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

#if 0
    /* 发送数据使用文件或默认值 */
    fp = fopen("udp_tx.txt", "rb");
    if (fp != NULL)
    {
        to_send = fread(TxBuffer, 1, sizeof(TxBuffer), fp);
        if (to_send != 0)
        {
            printf("send from udp_tx.txt(max 256 bytes)\n");
        }
        else     /* 文件中没有数据 */
        {
            to_send = 256;
            for (i = 0; i < sizeof(TxBuffer); i++)
            {
                TxBuffer[i] = i;
            }
        }
    }
#endif

    /* 发送数据 */
    for (i = 0; i < count; i++)
    {
        sent = sendto(client, (char *)TxBuffer, to_send, 0, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
        if (sent != to_send)
        {
            printf("sent = %d\n", sent);
            break;
        }
        taskDelay(sysClkRateGet() / 60);    /* VxWorks sendto函数有bug 无法阻塞到数据发送完毕 */
    }

    printf("Packets are sent to %s:%d.\n", IpAddress, UDP_SERVER_PORT);

    /* 等待服务器端回应 注意函数会阻塞 */
    printf("Wait for a response from server.\n");
    length = recvfrom(client, (char *)TxBuffer, sizeof(TxBuffer), 0, (struct sockaddr *)&serverAddr, &socketLength);

    /* 打印接收到数据 */
    printf("--- ");
    for (i = 0; i < length; i++)
    {
        printf("%02X ", TxBuffer[i]);
        if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
    }
    printf("--- udp client\n");

Exit:
    /* 关闭套接字 */
    if (client != 0)
    {
        close(client);
    }

    /* 关闭文件 */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
函数名称:   tcp_client

函数功能:   创建一个TCP客户端

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2010-12-29      徐佳谋  创建
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

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));

    /* 生成测试数据 */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i;
    }

    /* 创建套接字 */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create tcp socket failed!\n");
        goto Exit;
    }

    /* 设置发送缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 设置接收缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 输入发送次数 */
    printf("TCP Test, Input Transmit Count(1-10000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 10000) : 1;

    /* 输入IP地址最后一位 */
    /* 输入IP地址倒数第二位和最后一位 */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;

    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* 设置服务器信息 */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (TCP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

    /* 连接服务器 */
    if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) == -1)
    {
        ret = ERROR - 1;
        printf("Connect to tcp server failed!\n");
        goto Exit;
    }

#if 0
    /* 发送数据使用文件或默认值 */
    fp = fopen("tcp_tx.txt", "rb");
    if (fp != NULL)
    {
        to_send = fread(TxBuffer, 1, sizeof(TxBuffer), fp);
        if (to_send != 0)
        {
            printf("send from tcp_tx.txt(max 256 bytes)\n");
        }
        else     /* 文件中没有数据 */
        {
            to_send = 256;
            for (i = 0; i < sizeof(TxBuffer); i++)
            {
                TxBuffer[i] = i;
            }
        }
    }
#endif

    /* 发送数据 */
    for (i = 0; i < count; i++)
    {
        sent = send(client, (char *)TxBuffer, to_send, 0);
        if (sent != to_send)
        {
            printf("sent = %d\n", sent);
            break;
        }
    }

    /* 等待用户输入后关闭socket */
    printf("Packets are sent to %s:%d.\n", IpAddress, TCP_SERVER_PORT);

    /* 等待服务器端回应 注意函数会阻塞 */
    printf("Wait for a response from server.\n");
    length = recv(client, (char *)TxBuffer, sizeof(TxBuffer), 0);
    /* 打印接收到数据 */
    printf("--- ");
    for (i = 0; i < length; i++)
    {
        printf("%02X ", TxBuffer[i]);
        if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
    }
    printf("--- tcp client\n");

Exit:
    /* 关闭套接字 */
    if (client != 0)
    {
        close(client);
    }

    /* 关闭文件 */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
函数名称:   udp_server

函数功能:   创建一个UDP服务器端

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2010-12-29      徐佳谋  创建
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
        /* 创建接收任务 */
        s_net_tid[input + UDP_SERVER_TID] = taskSpawn("tUdpServerRecv", 100, 0, 1024 * 40, (FUNCPTR)tUdpServerRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* 延时 */
        taskDelay(sysClkRateGet() / 10);

    }
    else
    {
        printf("UDP server has been already established.\n");
    }

    return s_net_tid[input + UDP_SERVER_TID];
}

/********************************************************************
函数名称:   tUdpServerRecv

函数功能:   UDP服务器接收任务

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数使用阻塞方式读取 未来需要修改

修改记录:   2010-10-21      徐佳谋  创建
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

    /* 创建套接字 */
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == ERROR)
    {
        printf("Create udp socket failed!\n");
        return -1;
    }

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_CLIENT_PORT);   /* 监听端口号 */
    serverAddr.sin_addr.s_addr = ip;                /* 通过IP地址选择网卡 */

    /* 绑定端口 */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("bind udp socket failed!%d\n", errno);
        goto Exit;
    }

    printf("UDP server established, port = %d.\n", UDP_CLIENT_PORT);

    /* 显示接收数据 */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recvfrom(server, (char *)RxBuffer, sizeof(RxBuffer), 0, (struct sockaddr *)&clientAddr, &socketLength);
        if (length == ERROR)
        {
            printf("recvfrom failed!\n");
            break;
        }

        /* 打印接收到数据 */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
        }
        printf("--- udp server %d\n", net);

        /* 回应接收到的数据 */
        sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&clientAddr, socketLength);
    }

Exit:
    s_net_tid[net + UDP_SERVER_TID] = 0;
    close(server);

    return ret;
}

/********************************************************************
函数名称:   udp_group

函数功能:   创建一个UDP组播服务器端

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2011-07-04      徐佳谋  创建
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
        /* 创建接收任务 */
        s_net_tid[input + UDP_GROUP_TID] = taskSpawn("tUdpGroupRecv", 100, 0, 1024 * 40, (FUNCPTR)tUdpGroupRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* 延时 */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("UDP group has been already established.\n");
    }

    return s_net_tid[input + UDP_GROUP_TID];
}

/********************************************************************
函数名称:   tUdpGroupRecv

函数功能:   UDP服务器组播接收任务

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数使用阻塞方式读取 未来需要修改

修改记录:   2011-07-04      徐佳谋  创建
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

    /* 创建套接字 */
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == ERROR)
    {
        printf("Create udp socket failed!\n");
        return -1;
    }

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&tempAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&mcast1, 0x00, sizeof(struct ip_mreq));
    memset(&mcast2, 0x00, sizeof(struct ip_mreq));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_GROUP_PORT);    /* 监听端口号 */
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* 必须使用htonl(INADDR_ANY) */

    /* 绑定端口 */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("bind udp socket failed!%d\n", errno);
        goto Exit;
    }

    /* 设置广播功能 */
    on = 1;
    ret = setsockopt (server, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
    if (ret != 0)
    {
        printf("setsockopt failed(SO_BROADCAST)!%d\n", errno);
        goto Exit;
    }

    /* 复用地址和端口 */
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

    /* 设置组播发送功能 */
    ret = setsockopt (server, IPPROTO_IP, IP_MULTICAST_IF, (char *)&ip, sizeof(struct in_addr));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_IF)!%d\n", errno);
        goto Exit;
    }

    /* 设置组播TTL值 */
    opt = 255;
    ret = setsockopt (server, IPPROTO_IP, IP_MULTICAST_TTL, &opt, sizeof(opt));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_TTL)!%d\n", errno);
        goto Exit;
    }

#if INCLUDE_NET_SWITCH
    /* 记录使用组播发送的socket */
    AddSocketEntry(0, &server, 1);
#endif

    /* 组播数据不回环 */
    opt = 0;
    ret = setsockopt(server, IPPROTO_IP, IP_MULTICAST_LOOP, &opt, sizeof(opt));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_MULTICAST_LOOP)!%d\n", errno);
        goto Exit;
    }

    /* 设置组播 */
    mcast1.imr_multiaddr.s_addr = inet_addr(UDP_GROUP_ADDRESS1);
    mcast1.imr_interface.s_addr = ip;

    /* 加入组播组 */
    ret = setsockopt(server, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mcast1, sizeof(mcast1));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_ADD_MEMBERSHIP mcast1)!%d\n", errno);
        goto Exit;
    }

#if INCLUDE_NET_SWITCH
    /* 双网冗余增加组播 */
#if VXWORKS_TYPE
    AddMulticast(0, &mcast1);
#else
    AddMulticast(0, server, &mcast1);
#endif
#endif

    /* 延时 */
    taskDelay(sysClkRateGet() / 10);

    /* 设置组播 */
    mcast2.imr_multiaddr.s_addr = inet_addr(UDP_GROUP_ADDRESS2);
    mcast2.imr_interface.s_addr = ip;

    /* 加入组播组 */
    ret = setsockopt(server, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mcast2, sizeof(mcast2));
    if (ret != 0)
    {
        printf("setsockopt failed(IP_ADD_MEMBERSHIP mcast2)!%d\n", errno);
        goto Exit;
    }

#if INCLUDE_NET_SWITCH
#if VXWORKS_TYPE
    /* 双网冗余增加组播 */
    AddMulticast(0, &mcast2);
#else
    AddMulticast(0, server, &mcast2);
#endif
#endif

    printf("UDP group established, port = %d.\n", UDP_GROUP_PORT);

    /* 显示接收数据 */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recvfrom(server, (char *)RxBuffer, sizeof(RxBuffer), 0, (struct sockaddr *)&clientAddr, &socketLength);
        if (length == ERROR)
        {
            printf("recvfrom failed!\n");
            break;
        }

        /* 打印接收到数据 */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
        }
        printf("--- udp group %d\n", net);

        /* 回应接收到的数据(单点地址)
        ret = sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&clientAddr, socketLength);
        if (ret == -1)
        {
            printf("sendto(client) ret = %d errno = %d\n", ret, errno);
        }*/

        /* 回应接收到的数据(组播地址) */
        tempAddr.sin_family = AF_INET;
        tempAddr.sin_port = htons(UDP_GROUP_PORT);   /* 监听端口号 */
        tempAddr.sin_addr.s_addr = inet_addr(UDP_GROUP_ADDRESS1);
        ret = sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&tempAddr, socketLength);
        if (ret == -1)
        {
            printf("sendto(UDP_GROUP_ADDRESS1) ret = %d errno = %d\n", ret, errno);
        }

        /* 回应接收到的数据(组播地址2) */
        tempAddr.sin_family = AF_INET;
        tempAddr.sin_port = htons(UDP_GROUP_PORT);   /* 监听端口号 */
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
函数名称:   udp_broadcast

函数功能:   创建一个UDP服务器端测试广播包

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2012-04-26      徐佳谋  创建
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
        /* 创建接收任务 */
        s_net_tid[input + UDP_BROADCAST_TID] = taskSpawn("tUdpBroadcastRecv", 100, 0, 1024 * 40, (FUNCPTR)tUdpBroadcastRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* 延时 */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("UDP server has been already established.\n");
    }

    return s_net_tid[input + UDP_BROADCAST_TID];
}

/********************************************************************
函数名称:   tUdpBroadcastRecv

函数功能:   UDP服务器广播接收任务

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数使用阻塞方式读取 未来需要修改

修改记录:   2012-04-26      徐佳谋  创建
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

    /* 创建套接字 */
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == ERROR)
    {
        printf("Create udp socket failed!\n");
        return -1;
    }

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_BROADCAST_PORT);    /* 监听端口号 */
    serverAddr.sin_addr.s_addr = ip;                    /* 通过IP地址选择网卡 */

    /* 绑定端口 */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("bind udp socket failed!%d\n", errno);
        goto Exit;
    }

    /* 设置广播功能 */
    on = 1;
    ret = setsockopt (server, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
    if (ret != 0)
    {
        printf("setsockopt failed(SO_BROADCAST)!%d\n", errno);
        goto Exit;
    }

    printf("UDP broadcast established, port = %d.\n", UDP_BROADCAST_PORT);

    /* 显示接收数据 */
    for (sum = 0; s_task_over_flag != 1; sum += length)
    {
        length = recvfrom(server, (char *)RxBuffer, sizeof(RxBuffer), 0, (struct sockaddr *)&clientAddr, &socketLength);
        if (length == ERROR)
        {
            printf("recvfrom failed!\n");
            break;
        }

        /* 打印接收到数据 */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
        }
        printf("--- udp broadcast %d\n", net);

        clientAddr.sin_family = AF_INET;
        clientAddr.sin_port = htons (UDP_BROADCAST_PORT);
        clientAddr.sin_addr.s_addr = ip | 0xFF000000;   /* 制作广播地址 VxWorks6.8下全网广播发不出去可能是路由表的问题 */

        /* 回应接收到的数据 */
        sendto(server, (char *)RxBuffer, length, 0, (struct sockaddr *)&clientAddr, socketLength);
    }

Exit:
    s_net_tid[net + UDP_BROADCAST_TID] = 0;
    close(server);

    return ret;
}

/********************************************************************
函数名称:   tcp_server

函数功能:   创建一个TCP服务器端

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2010-12-29      徐佳谋  创建
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
        /* 创建接收任务 */
        s_net_tid[input + TCP_SERVER_TID] = taskSpawn("tTcpServerRecv", 100, 0, 1024 * 40, (FUNCPTR)tTcpServerRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* 延时 */
        taskDelay(sysClkRateGet() / 10);

    }
    else
    {
        printf("TCP server has been already established.\n");
    }

    return s_net_tid[input + TCP_SERVER_TID];
}

/********************************************************************
函数名称:   tTcpServerRecv

函数功能:   TCP服务器接收任务

参数名称        类型            输入/输出           含义
fd              int             input               接收串口句柄

返回值  :   0代表成功 非0代表失败

函数说明:   函数使用阻塞方式读取 未来需要修改

修改记录:   2010-10-21      徐佳谋  创建
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

    /* 创建套接字 */
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == ERROR)
    {
        printf("Create tcp socket failed!\n");
        return -1;
    }

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_CLIENT_PORT);   /* 监听端口号 */
    serverAddr.sin_addr.s_addr = ip;                /* 通过IP地址选择网卡 */

    /* 绑定端口 */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("Bind tcp socket failed!\n");
        goto Exit;
    }

    /* 监听端口 */
    if (listen(server, 1) == -1)
    {
        printf("Listen tcp socket failed!\n");
        goto Exit;
    }

    printf("TCP server is listening, port = %d.\n", TCP_CLIENT_PORT);

    /* 等待客户端连接 */
    client = accept(server, (struct sockaddr *)&clientAddr, &socketLength);
    if (client == -1)
    {
        printf("Accept tcp socket failed!\n");
        goto Exit;
    }

    /* 显示接收数据 */
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

        /* 打印接收到数据 */
        printf("--- ");
        for (i = 0; i < length; i++)
        {
            printf("%02X ", RxBuffer[i]);
            if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
        }
        printf("--- tcp server %d\n", net);

        /* 回应接收到的数据 */
        send(client, (char *)RxBuffer, length, 0);
    }

Exit:
    s_net_tid[net + TCP_SERVER_TID] = 0;
    close(client);
    close(server);

    return ret;
}

/********************************************************************
函数名称:   com_transmit

函数功能:   串口发送函数

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数根据用户输入打开一个串口，发送特定数据
            进行485通讯 需要增加特定库

修改记录:   2010-11-02      徐佳谋  创建
            2016-09-21      王  明  修改 SIO_HW_OPTS_SET解决6.8驱动下上电收数复位问题
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

    /* 测试发送数据0x00 - 0xFF */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i + TxCom + 1;
    }

    /* 指定发送串口 */
    printf("Input Transmit COM Number:(1-8:COM 9-16:EXTCOM 17-24:CSDCOM) odd\n");
    input = GetKeyInput(10);
    TxCom = (input - 1) % 24;

    /* 打开发送串口 */
    fd = open(g_ExtComName[TxCom], O_RDWR, 0);
    if (fd == ERROR)
    {
        printf("Open %s failed!\n", g_ExtComName[TxCom]);
        return fd;
    }

    printf("Open %s succeeded\n", g_ExtComName[TxCom]);

    /* 配置串口参数 */
    /* 数据位8位 停止位1位 奇校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | PARENB);
    ret += ioctl(fd, FIOBAUDRATE, g_com_baud);  /* 波特率 */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOFLUSH, 0);              /* 清空缓冲区 */

    /* 输入发送次数 */
    printf("COM Test, Input Transmit Count(1-10000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 10000) : 1;

    /* 发送串口发送数据 */
    for (i = 0; i < count; i++)
    {
        sent += write(fd, (char *)TxBuffer, to_send);
    }
    printf("COM%d Sent %d\n", TxCom + 1, sent);

    /* VxWorks串口发送函数无法阻塞所以发送最后需要主动等待完成 暂时使用延时实现 */
    taskDelay(sysClkRateGet() / 10);

    /* 必须保证数据发送完成后 才能关闭串口 */
    close(fd);

    /* 关闭文件 */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
函数名称:   com_receive

函数功能:   串口接收

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数根据用户输入创建一个串口接收任务
            串口接收任务不停读取串口收到的数据

修改记录:   2010-11-02      徐佳谋  创建
********************************************************************/
int com_receive()
{
    int input = 0;
    int RxCom = 0;

    /* 指定接收串口 */
    printf("Input Receive COM Number:(1-8:COM 9-16:EXTCOM 17-24:CSDCOM) odd\n");
    input = GetKeyInput(10);
    RxCom = (input - 1) % 24;

    if (s_com_tid[RxCom] == 0)
    {
        /* 创建接收任务 */
        s_com_tid[RxCom] = taskSpawn("tComRecv", 100, 0, 1024 * 40, (FUNCPTR)tComRecv, RxCom, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        /* 延时 */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("COM%d has been already opened.\n", RxCom);
    }

    return s_com_tid[RxCom];
}

/********************************************************************
函数名称:   tComRecv

函数功能:   串口接收任务

参数名称        类型            输入/输出           含义
RxCom           int             input               串口索引(0-24)

返回值  :   0代表成功 非0代表失败

函数说明:   函数使用阻塞方式读取 未来需要修改

修改记录:   2010-10-21      徐佳谋  创建
********************************************************************/
int tComRecv(int RxCom)
{
    int fd = 0;
    int ret = 0;
    unsigned char RxBuffer[256] = {0};
    int Received = 0;
    int sum = 0;
    int i = 0;

#if INCLUDE_COM_TIMEOUT    /* 普通读取模式 */
    struct timeval timeout;
#endif

    /* 打开接收串口 */
    fd = open(g_ExtComName[RxCom], O_RDWR, 0);
    if (fd == ERROR)
    {
        printf("Open %s COM failed!\n", g_ExtComName[RxCom]);
        return fd;
    }

    printf("Open %s succeeded\n", g_ExtComName[RxCom]);

    /* 配置串口参数 */
    /* 数据位8位 停止位1位 奇校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | PARENB);
    ret += ioctl(fd, FIOBAUDRATE, g_com_baud);  /* 波特率 */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOFLUSH, 0);              /* 清空缓冲区 */

    /* 打印接收数据 */
    for (sum = 0; s_task_over_flag != 1; )
    {

#if !INCLUDE_COM_TIMEOUT    /* 普通读取模式 */
        Received = read(fd, (char *)RxBuffer, sizeof(RxBuffer));
#else   /* 超时读取模式 */
        /* 设置超时时间 */
        timeout.tv_sec = 0;         /* 0 单位s */
        timeout.tv_usec = 100000;   /* 100ms 单位us*/
        Received = com_read_ex(fd, RxBuffer, sizeof(RxBuffer), &timeout);
        if (Received == 0)
        {
            continue ;  /* 超时后继续读取 */
        }
#endif
        sum += Received;
        if (g_dtp_debug)
        {
            printf("--- ");
            for (i = 0; i < Received; i++)
            {
                printf("%02X ", RxBuffer[i]);
                if (((i + 1) % 16) == 0) printf("\n    "); /* 16个一换行 */
            }
            printf("--- com%d\n", RxCom + 1);
        }
        else
        {
            printf("COM%d received %4d bytes, last data = %X\n", RxCom + 1, sum, RxBuffer[Received - 1]);
        }
    }

    s_com_tid[RxCom] = 0;

    /* 关闭串口 */
    close(fd);

    return 0;
}

/********************************************************************
函数名称:   usb_test

函数功能:   USB口测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   向U盘写入一个文件，然后读取测试

修改记录:   2010-12-14      徐佳谋  创建
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

    /* 测试发送数据0x00 - 0xFF */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i + MassUsb + 1;
    }

    /* 指定U盘 */
    printf("USB Test, Input MessStorage Number:(0-1)\n");
    input = GetKeyInput(10);
    MassUsb = input % 2;

    /* 打开U盘 */
    fd = open(g_MassUsbName[MassUsb], O_RDWR | O_CREAT, 0644);
    if (fd == ERROR)
    {
        printf("Open %s failed!\n", g_MassUsbName[MassUsb]);
        return fd;
    }

    printf("Open %s succeeded\n", g_MassUsbName[MassUsb]);

    /* 写入测试文件 */
    for (i = 0; i < 1024; i++)
    {
        written += write(fd, (char *)TxBuffer, sizeof(TxBuffer));
    }
    printf("USB%d written %d(byte)\n", MassUsb, written);

    /* 文件指针归零 */
    lseek(fd, 0, SEEK_SET);

    pentiumTscGet64(&llStart);
    /* 读取测试文件 */
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
函数名称:   windml_test

函数功能:   WindML测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   系统显示功能

修改记录:   2010-10-12      徐佳谋  创建
********************************************************************/
int windml_test()
{
    /* 调用WindML提供的测试程序 */
    windMLDemo(0);

    return 0;
}
#endif

/********************************************************************
函数名称:   audio_test

函数功能:   音频输出测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:

修改记录:   2011-00-00      徐佳谋  创建
********************************************************************/
int audio_test()
{
    return 0;
}

/********************************************************************
函数名称:   dtp_debug_onoff

函数功能:   dtp调试开关

参数名称        类型            输入/输出           含义
onoff           int             input               调试开关(1:打开 0:关闭)

返回值  :   0代表成功 非0代表失败

函数说明:

修改记录:   2010-10-29      徐佳谋  创建
********************************************************************/
int dtp_debug_onoff(int onoff)
{
    g_dtp_debug = onoff;

    return 0;
}

/********************************************************************
函数名称:   com_read_ex

函数功能:   串口读取超时返回函数

参数名称        类型            输入/输出           含义
fd              int             input               串口文件描述符
buffer          char*           input               读取缓冲区指针
maxbytes        size_t          input               读取最大字节数
pTimeOut        struct timeval* input               超时信息结构体

返回值  :   -1:操作失败 0:超时 1-maxbytes:返回的数据

函数说明:   函数封装基本的read函数和select函数 形成一个串口在指定时间内没有
            读取到数据时就返回以前所读到数据的函数

修改记录:   2011-01-26      徐佳谋  创建
********************************************************************/
int com_read_ex(int fd, char *buffer, size_t maxbytes, struct timeval *pTimeOut)
{
    int sum = 0;
    int ret = 0;
    fd_set fdset;
    char *p = buffer;

    /* 设置文件描述符集合 */
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);

    for (; sum < maxbytes;)
    {
        /* 使用select函数判断串口状态 */
        ret = select(fd + 1, &fdset, NULL, NULL, pTimeOut);
        if (ret == 0)
        {
            /* 当超时的情况返回收到的数据 */
            return sum;
        }
        if (ret == -1)
        {
            return -1;
        }
        /* 判断当前串口是否有数据可读 */
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
函数名称:   int_test

函数功能:   中断响应测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   并不是所有IRQ都可以进行测试 测试有些IRQ会影响系统运行
            BIOS中需要释放相关IRQ

修改记录:   2011-05-31      徐佳谋  创建
********************************************************************/
int int_test()
{
    int input = 0;
    int ret = 0;

    /* 指定测试中断 */
    printf("Input IRQ Number:(3,4,5,6,7,9,10,11,12,13,15)\n");
    input = GetKeyInput(10);

    /* 注册中断 */
    ret = intConnect(INUM_TO_IVEC(INT_VEC_GET(input)), irq_isr, input);
    if (ret != 0)
    {
        printf("intConnect failed!\n");
        return -1;
    }

    /* 使能中断 */
    ret = sysIntEnablePIC(input);
    if (ret != 0)
    {
        printf("sysIntEnablePIC failed!\n");
        return -1;
    }

    return 0;
}

/********************************************************************
函数名称:   file_test

函数功能:   文件读写测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数先创建一个64MB的文件，然后读取计算时间。
            因为VxWorks使用PIO_2模式所以CF卡读写速度在5MB左右。

修改记录:   2011-05-31      徐佳谋  创建
********************************************************************/
int file_test()
{
    int ret = 0;
    FILE *fp = NULL;
    int i = 0;
    long long int llStart = 0;
    long long int llEnd = 0;

    /* 赋初值 */
    for (i = 0; i < sizeof(g_ataBuffer); i++)
    {
        g_ataBuffer[i] = i;
    }

    /* 打开文件 */
    fp = fopen(g_AtaName[0], "wb+");
    if (fp == NULL)
    {
        printf("fopen failed!%s\n", g_AtaName[0]);
        return -1;
    }

    printf("Writing file...\n");

    /* 写64M文件并计算时间 */
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

    /* 刷新缓存 */
    ret = fflush(fp);

    printf("Write 64MB file, elapsed time = %f(ms)\n", (llEnd - llStart) * 1000.0 / BOARD_CPU_FREQUENCE);

    /* 回退文件指针 */
    ret = fseek(fp, 0, SEEK_SET);

    printf("Reading file...\n");

    /* 读64M文件并计算时间 */
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
函数名称:   irq_isr

函数功能:   中断服务程序

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   当系统响应中断时 打印信息

修改记录:   2011-05-31      徐佳谋  创建
********************************************************************/
void irq_isr(void *irq)
{
    logMsg("IRQ %d happened.\n", (int)irq, 0, 0, 0, 0, 0);

    return ;
}

/********************************************************************
函数名称:   watchdog_test

函数功能:   硬件看门狗测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   系统会在设定时间后重启电脑 板卡配置看门狗跳线

修改记录:   2011-05-31      徐佳谋  创建
********************************************************************/
int watchdog_test()
{
    int input = 0;
    int ret = 0;
    int mode = 0;
    unsigned short ushRuntime = 0;

    /* 进入配置模式 */
    sysOutByte(0x2e, 0x55);

    /* 配置逻辑设备10 */
    sysOutByte(0x2e, 0x07);
    sysOutByte(0x2f, 0x0a);

    /* 配置CLOCKI32寄存器 */
    sysOutByte(0x2e, 0xf0);
    sysOutByte(0x2f, 0x01);

    /* 读取runtime寄存器组基址 */
    sysOutByte(0x2e, 0x60);
    ushRuntime = sysInByte(0x2f);

    sysOutByte(0x2e, 0x61);
    ushRuntime = (ushRuntime << 8) | sysInByte(0x2f);
    printf("ushRuntime = 0x%X\n", ushRuntime);

    /* 退出配置模式 */
    sysOutByte(0x2e, 0xaa);

    /* 配置GP60寄存器 LX系列配置0x0e PM系列配置0x0c */
    sysOutByte(ushRuntime + 0x47, 0x0e);

    /* 指定看门狗计时单位 */
    printf("Input watch dog timer unit:(1:sencond 0:minute)\n");
    input = GetKeyInput(10);
    mode = input & 0x01;

    /* 配置WDT_TIME_OUT寄存器 */
    sysOutByte(ushRuntime + 0x65, mode << 7);  /* 1:秒 0:分 */

    printf("Input watch dog timer count:(0-255)\n");
    input = GetKeyInput(10);

    /* 配置WDT_VAL寄存器 */
    sysOutByte(ushRuntime + 0x66, input);      /* 计时个数 */

    printf("System will restart in %d %s.\n", input & 0xff, mode ? "seconds" : "minutes");

    return ret;
}

/********************************************************************
函数名称:   dma_test

函数功能:   i8237 DMA测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   DMA测试需要硬件配合 可以测量DREQ和DACK信号
            不同的DMA传输模式请修改代码测试.使用公司429板卡测试DMA步骤如下
            连接OUT1A->IN1A OUT1B->IN1B
            sysOutWord(0x380 + 4, 0x6020);
            sysOutWord(0x380, 0x1234);
            sysOutWord(0x380 + 2, 0x5678);
            sysInWord(0x380 + 8) 0x4:可以发送 0x01:发送中
            如果DMA测试成功，0x200000地址上有传输的数据

修改记录:   2011-05-31      徐佳谋  创建
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

    /* 关闭CACHE功能 */
    cacheInvalidate(DATA_CACHE, (void *)DMA_BUFFER_ADDR, DMA_BUFFER_SIZE);

    if (channel < 4)    /* 通道0 1 2 3 */
    {
        /* 复位DMA控制器 */
        sysOutByte(DMAC0_CLEAR_ALL, 0x00);

        /* 屏蔽DMA请求 */
        sysOutByte(DMAC0_MASK, 0x04 | channel);

        /* 写入工作模式 */
        uchValue = DMA_MODE_SINGLE | DMA_MODE_AUTO_ENABLE | channel;
        uchValue = uchValue | (direction == 0 ? DMA_MODE_WRITE : DMA_MODE_READ);
        sysOutByte(DMAC0_MODE, uchValue);

        /* 写入内存空间的页地址 */
        uchValue = (DMA_BUFFER_ADDR & 0x00ff0000) >> 16;
        sysOutByte(dma_page_addr[channel], uchValue);

        /* 清除先后触发寄存器 */
        sysOutByte(DMAC0_CLEAR_FF, 0xff);

        /* 写入内存空间的偏移地址 先低位 后高位 */
        uchValue = (unsigned char)(DMA_BUFFER_ADDR & 0x00000ff);
        sysOutByte(DMAC0_CH_CA(channel), uchValue);
        uchValue = (unsigned char)(DMA_BUFFER_ADDR >> 8);
        sysOutByte(DMAC0_CH_CA(channel), uchValue);

        /* 清除先后触发寄存器 */
        sysOutByte(DMAC0_CLEAR_FF, 0xff);

        /* 写入传输个数 先低位 后高位 */
        uchValue = (count - 1) & 0x00ff;
        sysOutByte(DMAC0_CH_CC(channel), uchValue);
        uchValue = (count - 1) >> 8;
        sysOutByte(DMAC0_CH_CC(channel), uchValue);

        /* 配置DMA工作时序 */
        sysOutByte(DMAC0_STATUS_CMD, DMA_CMD_DACK_L | DMA_CMD_DREQ_H | DMA_CMD_MEM_ENABLE);

        /* 使能DMA */
        sysOutByte(DMAC0_MASK, channel);
    }
    else                /* 通道4 5 6 7 其中4通道作级联使用 */
    {
        /* 复位DMA控制器 */
        sysOutByte(DMAC1_CLEAR_ALL, 0x00);

        /* 屏蔽DMA请求 */
        sysOutByte(DMAC1_MASK, 0x04 | (channel - 4));

        /* 写入工作模式 */
        uchValue = DMA_MODE_SINGLE | DMA_MODE_AUTO_ENABLE | (channel - 4);
        uchValue = uchValue | (direction == 0 ? DMA_MODE_WRITE : DMA_MODE_READ);
        sysOutByte(DMAC1_MODE, uchValue);

        /* 写入内存空间的页地址 2字节对齐 */
        uchValue = ((DMA_BUFFER_ADDR & 0x00ff0000) >> 16) & 0xFE;
        sysOutByte(dma_page_addr[channel], uchValue);

        /* 清除先后触发寄存器 */
        sysOutByte(DMAC1_CLEAR_FF, 0xff);

        /* 写入内存空间的偏移地址 先低位 后高位 16位操作时以2个字节为单位 */
        uchValue = (unsigned char)((DMA_BUFFER_ADDR >> 1) & 0x00000ff);
        sysOutByte(DMAC1_CH_CA(channel), uchValue);
        uchValue = (unsigned char)((DMA_BUFFER_ADDR >> 1) >> 8);
        sysOutByte(DMAC1_CH_CA(channel), uchValue);

        /* 清除先后触发寄存器 */
        sysOutByte(DMAC1_CLEAR_FF, 0xff);

        /* 写入传输个数 先低位 后高位 16位操作时以2个字节为单位且计数递减 */
        uchValue = (count - 1) & 0x00ff;
        sysOutByte(DMAC1_CH_CC(channel), uchValue);
        uchValue = (count - 1) >> 8;
        sysOutByte(DMAC1_CH_CC(channel), uchValue);

        /* 配置DMA工作时序 */
        sysOutByte(DMAC1_STATUS_CMD, DMA_CMD_DACK_L | DMA_CMD_DREQ_H | DMA_CMD_MEM_ENABLE);

        /* 使能DMA */
        sysOutByte(DMAC1_MASK, channel - 4);
    }

    return ret;
}

/********************************************************************
函数名称:   realtime_test

函数功能:   实时时钟测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   VxWorks下没有读取系统时间函数 只能直接读取实时时钟数据

修改记录:   2011-06-10      徐佳谋  创建
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

    /* 读取RTC值 */
    sysOutByte(RTC_INDEX, RTC_CENTURY); /* 世纪 */
    uch = sysInByte(RTC_DATA);
    century = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_YEAR);    /* 年 */
    uch = sysInByte(RTC_DATA);
    year = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_MONTH);   /* 月 */
    uch = sysInByte(RTC_DATA);
    month = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_DAY);     /* 日 */
    uch = sysInByte(RTC_DATA);
    day = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_HOUR);    /* 时 */
    uch = sysInByte(RTC_DATA);
    hour = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_MINUTE);  /* 分 */
    uch = sysInByte(RTC_DATA);
    minute = BCD_TO_BIN(uch);

    sysOutByte(RTC_INDEX, RTC_SECOND);  /* 秒 */
    uch = sysInByte(RTC_DATA);
    second = BCD_TO_BIN(uch);

    printf("The current date and time is %4d-%02d-%02d(y-m-d) and %02d:%02d:%02d(h-m-s).\n",
           century * 100 + year, month, day, hour, minute, second);

    /* 设置RTC值 */
    sysOutByte(RTC_INDEX, RTC_CENTURY); /* 世纪 */
    uch = BIN_TO_BCD(20);               /* 20世纪 */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_YEAR);    /* 年 */
    uch = BIN_TO_BCD(4);                /* 4年 */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_MONTH);   /* 月 */
    uch = BIN_TO_BCD(5);                /* 5月 */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_DAY);     /* 日 */
    uch = BIN_TO_BCD(6);                /* 1日 */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_HOUR);    /* 时 */
    uch = BIN_TO_BCD(19);               /* 19时 */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_MINUTE);  /* 分 */
    uch = BIN_TO_BCD(28);               /* 28分 */
    sysOutByte(RTC_DATA, uch);

    sysOutByte(RTC_INDEX, RTC_SECOND);  /* 秒 */
    uch = BIN_TO_BCD(37);               /* 37秒 */
    sysOutByte(RTC_DATA, uch);

    printf("The current date and time is setted to 2004-05-06 and 19:28:37.\n");

    return 0;
}

/********************************************************************
函数名称:   std_test

函数功能:   标准输入输出切换

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数可以切换标准输入输出到指定串口控制台或显示器控制台上

修改记录:   2011-06-10      徐佳谋  创建
********************************************************************/
int std_test()
{
    int ret = 0;
    int STD = 0;
    int fd = 0;
    int input = 0;

    /* 指定标准输入输出使用串口 */
    printf("Input STD COM Number:(0:pcConsole 1-2:COM) %dbps\n", g_com_baud);
    input = GetKeyInput(10);
    STD = input % 3;

    if (STD == 0)
    {
        /* 打开显示器控制台 */
        fd = open("/pcConsole/0", O_RDWR, 0);
    }
    else
    {
        /* 打开串口控制台 */
        fd = open(g_ExtComName[STD - 1], O_RDWR, 0);

        /* 设置波特率 */
        ret |= ioctl (fd, FIOBAUDRATE, g_com_baud);
        ret |= ioctl (fd, FIOSETOPTIONS, OPT_TERMINAL);
    }

    /* 设置标准输入输出使用的设备 */
    ioGlobalStdSet (STD_IN,  fd);
    ioGlobalStdSet (STD_OUT, fd);
    ioGlobalStdSet (STD_ERR, fd);

    return ret;
}

#if INCLUDE_NET_SWITCH
/********************************************************************
函数名称:   netswitch_callback

函数功能:   双网卡切换报警回调函数

参数名称        类型            输入/输出           含义
master          int             input               当前主网卡

返回值  :   0代表成功 非0代表失败

函数说明:   函数实现双网卡冗余

修改记录:   2013-03-11  徐佳谋  创建
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
函数名称:   netswitch_test

函数功能:   双网卡切换

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数实现双网卡冗余

修改记录:   2011-07-04  徐佳谋  创建
            2012-12-19  徐佳谋  升级    增加跨网段和主动ARP更新
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

    /* 增加路由信息 实际应用时修改为适当值 */
#if VXWORKS_TYPE
    strcpy(entry1.dest, "0.0.0.0");
    strcpy(entry1.gate, "192.168.1.254");
#else
    entry1.dest = inet_addr("0.0.0.0");
    entry1.gate = inet_addr("192.168.1.254");
#endif
    AddRouteEntry(0, &entry1, 1);

    /* 增加ARP更新信息 实际应用时修改为适当值 */
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

    /* 注册报警回调函数 */
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
函数名称:   lpt_test

函数功能:   并口测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   在BIOS中设置并口为SPP（Bi-Dir）模式

修改记录:   2011-11-16      徐佳谋  创建
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

    /* 配置数据寄存器输入输出模式 */
    sysOutByte(LPT_BASE_ADDRESS + 2, mode << 5);

    if (mode == 0)
    {
        printf("Input LPT Output Data(0x00-0xFF):\n");
        uchOut = GetKeyInput(16);
        sysOutByte(LPT_BASE_ADDRESS, uchOut);   /* 输出3.3V */
    }
    else
    {
        printf("Now Change Input Data, press enter\n");
        getchar();
        uchIn = sysInByte(LPT_BASE_ADDRESS);    /* 引脚会上拉到5V */
        printf("LPT Input Data 0x%02X\n", uchIn);
    }

    /* 通过状态寄存器输入 */
    uchIn = sysInByte(LPT_BASE_ADDRESS + 1) & 0xF8; /* bit0 - bit2无效 注意bit7反相 引脚会上拉到5V */
    printf("LPT Input Data(status) 0x%02X\n", uchIn);

    return ret;
}

/********************************************************************
函数名称:   soft_watchdog_test

函数功能:   软件看门狗测试

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   测试VxWorks的软件看门狗

修改记录:   2011-12-04      徐佳谋  创建
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

    /* 创建看门狗定时器 */
    s_wdId = wdCreate();
    if (s_wdId == NULL)
    {
        printf("wdCreate failed!\n");
        return -1;
    }

    /* 启动看门狗 */
    wdStart(s_wdId, s_ticks, (FUNCPTR)watch_dog_callback, count);

    return ret;
}

/********************************************************************
函数名称:   watch_dog_callback

函数功能:   看门狗程序

参数名称        类型            输入/输出           含义

返回值  :   无

函数说明:   当看门狗定时器超时时会调用此函数。看门狗程序中不能使用printf函数。

修改记录:   2011-05-18      徐佳谋  创建
********************************************************************/
static void watch_dog_callback(int para)
{
    if (para > 0)
    {
        logMsg("\nwatch_dog was called.%d\n", para, 0, 0, 0, 0 , 0);

        /* 重复触发看门狗 */
        wdStart(s_wdId, s_ticks, (FUNCPTR)watch_dog_callback, para - 1);
    }
    else
    {
        logMsg("\nwatch_dog_callback finished.\n", 0, 0, 0, 0, 0 , 0);

        /* 删除看门狗 */
        wdDelete(s_wdId);
    }

    return ;
}

/********************************************************************
函数名称:   soft_watchdog_test2

函数功能:   软件看门狗测试

参数名称        类型            输入/输出       含义
count           int             input           看门狗运行次数

返回值  :   0代表成功 非0代表失败

函数说明:   创建看门狗用于对UDP测试

修改记录:   2015-4-28      王明  创建
********************************************************************/
int soft_watchdog_test2(int count)
{
    int ret = 0;

    /* 创建看门狗定时器 */
    s_wdId2 = wdCreate();
    if (s_wdId2 == NULL)
    {
        printf("wdCreate failed!\n");
        return -1;
    }

    /* 启动看门狗，周期为10ms */
    sysClkRateSet(1000);
    wdStart(s_wdId2, (sysClkRateGet() / 100), (FUNCPTR)watch_dog_callback2, count);

    return ret;
}
/********************************************************************
函数名称:   watch_dog_callback2

函数功能:   软件看门狗测试2

参数名称        类型            输入/输出           含义
para            int             input               看门狗运行次数

返回值  :   0代表成功 非0代表失败

函数说明:   创建看门狗用于对UDP测试

修改记录:   2015-4-28      王明  创建
********************************************************************/
static void watch_dog_callback2(int para)
{
    if (para > 0)
    {
        /* 生成计数数据 */
        *(unsigned int *)(&g_TxBuffer[0]) = g_txBufferCount;

        g_txBufferCount++;

        /* 释放信号量 */
        semGive(s_Sem2);

        /* 重复触发看门狗,周期为10ms */
        wdStart(s_wdId2, (sysClkRateGet() / 100), (FUNCPTR)watch_dog_callback2, para - 1);
    }
    else
    {
        /* 清除计数器 */
        g_txBufferCount = 0;

        logMsg("\nUDP package send finished.\n", 0, 0, 0, 0, 0 , 0);

        /* 删除看门狗 */
        wdDelete(s_wdId2);
    }

    return ;
}

/********************************************************************
函数名称:   udp_client_2

函数功能:   创建一个UDP客户端，间隔10ms发送一次UDP数据包

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   注意任务堆栈 使用阻塞模式

修改记录:   2015-4-28      王明  创建
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

    /* 创建套接字 */
    client = socket(AF_INET, SOCK_DGRAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create udp socket failed!\n");
        goto Exit;
    }

    /* 设置发送缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 设置接收缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&g_TxBuffer, 0x00, sizeof(g_TxBuffer));

    /* 输入发送次数 */
    printf("UDP Test, Input Transmit Count(1-1000000)\n");
    input = GetKeyInput(10);
    count = input ? (input % 1000000) : 1;

    /* 输入IP地址倒数第二位和最后一位 */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;
    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* 设置服务器信息 */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (UDP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

    s_Sem2 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (s_Sem2 == NULL)
    {
        printf("semBCreate failed!\n");
        goto Exit;
    }

    /* 创建taskSend任务 */
    s_tid = taskSpawn("udp_task", 101, 0, 30 * 1024, (FUNCPTR)udp_task, client, (int)&serverAddr, 0, 0, 0, 0, 0, 0, 0, 0);
    if (s_tid == -1)
    {
        printf("taskSpawn failed!\n");
        goto Exit;
    }

    /* 创建看门狗用于产生周期为10ms定时 */
    soft_watchdog_test2(count);

    /* 此时会阻塞，当数据发送 */
    printf("Press any key to stop send %s:%d.\n", IpAddress, UDP_SERVER_PORT);
    GetKeyInput(10);

Exit:
    /* 关闭套接字 */
    if(client != 0)
    {
        close(client);
    }

    /*删除信号量 */
    if(s_Sem2 != 0)
    {
        semDelete(s_Sem2);
    }

    /* 删除任务 */
    if(s_tid != 0)
    {
        taskDelete(s_tid);
    }

    /* 删除看门狗 */
    wdDelete(s_wdId2);

    /* 看门狗清除计数器 */
    g_txBufferCount = 0;

    return ret;
}

/********************************************************************
函数名称:   udp_task

函数功能:   创建udp任务

参数名称        类型                输入/输出   含义
sock            int                 input       发送数据使用的socket
serverAddr      struct sockaddr_in* input       发送地址变量指针

返回值  :   0代表成功 非0代表失败

函数说明:   任务一直阻塞，直到看门狗触发信号量

修改记录:   2015-4-28      王明  创建
********************************************************************/
int udp_task(int sock, struct sockaddr_in *pServerAddr)
{
    int sent = 0;

    for(;;)
    {
        /* 任务阻塞，等待看门狗触发信号量 */
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
函数名称:   speaker_test

函数功能:   蜂鸣器测试程序

参数名称        类型            输入/输出           含义

返回值  :   无

函数说明:   蜂鸣器输入由定时器2决定，定时器2门信号由端口B决定。
            蜂鸣器使用时需要跳线。

修改记录:   2012-04-18      王鹤翔  创建
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

    sysOutByte(TIMER_CONTROL, 0xb6);            /*设置定时器2工作方式*/
    sysOutByte(TIMER2, uchLsb);
    sysOutByte(TIMER2, uchMsb);

    uchReg = sysInByte(TIMER2_GATE);
    sysOutByte(TIMER2_GATE, uchReg | 0x03);     /*开启蜂鸣器*/

    printf("Press Any Key to Stop\n");
    getchar();

    sysOutByte(TIMER2_GATE, uchReg);            /*关闭蜂鸣器*/

    return ret;
}

/********************************************************************
函数名称:   com_write_ex

函数功能:   查询方式发送串口数据

参数名称        类型            输入/输出           含义
ushComBase      unsigned short  input               串口基地址
TxBuffer        unsigned char   input               发送数据缓冲区
length          int             input               发送数据长度(单位字节)

返回值  :   0代表成功 非0代表失败

函数说明:   有些时候(高效率发送串口数据时)需要使用查询方式发送串口数据

修改记录:   2012-09-04      徐佳谋  创建
********************************************************************/
int com_write_ex(unsigned short ushComBase, unsigned char TxBuffer[], int length)
{
    int i = 0;

    for (i = 0; i < length; i++)
    {
        sysOutByte(ushComBase, TxBuffer[i]);        /* 发送数据 */
        while(!(sysInByte(ushComBase + 5) & 0x20)); /* 等待数据发送完成 此处判断方法不适用于485 */
    }

    return 0;
}

/********************************************************************
函数名称:   tcp_rx_performance

函数功能:   测试网卡进行TCP通讯时的性能

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   利用这个函数测试网卡的接收性能

修改记录:   2013-04-27      徐佳谋  创建
********************************************************************/
int tcp_rx_performance()
{
    int input = 0;
    char IpAddress[32] = {0};
    char NetName[32] = {0};

    /* 使用Tick计算 先设置Tick为1ms */
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
        /* 创建接收任务 */
        s_net_tid[input + TCP_PERFORM_TID] = taskSpawn("tTcpPerformRecv", 100, 0, 1024 * 40, (FUNCPTR)tTcpPerformRecv, inet_addr(IpAddress), input, 0, 0, 0, 0, 0, 0, 0, 0);

        /* 延时 */
        taskDelay(sysClkRateGet() / 10);
    }
    else
    {
        printf("TCP perform has been already established.\n");
    }

    return s_net_tid[input + TCP_PERFORM_TID];
}

/********************************************************************
函数名称:   tTcpPerformRecv

函数功能:   TCP服务器接收任务

参数名称        类型            输入/输出           含义
fd              int             input               接收串口句柄

返回值  :   0代表成功 非0代表失败

函数说明:   函数使用阻塞方式读取 未来需要修改

修改记录:   2013-04-27      徐佳谋  创建
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

    /* 创建套接字 */
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == ERROR)
    {
        printf("Create tcp socket failed!\n");
        return -1;
    }

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));
    memset(&clientAddr, 0x00, sizeof(struct sockaddr_in));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_CLIENT_PORT);   /* 监听端口号 */
    serverAddr.sin_addr.s_addr = ip;                /* 通过IP地址选择网卡 */

    /* 绑定端口 */
    if (bind(server, (struct sockaddr *)&serverAddr, socketLength) == -1)
    {
        printf("Bind tcp socket failed!\n");
        goto Exit;
    }

    /* 监听端口 */
    if (listen(server, 1) == -1)
    {
        printf("Listen tcp socket failed!\n");
        goto Exit;
    }

    printf("TCP server is listening, port = %d.\n", TCP_CLIENT_PORT);

    /* 等待客户端连接 */
    client = accept(server, (struct sockaddr *)&clientAddr, &socketLength);
    if (client == -1)
    {
        printf("Accept tcp socket failed!\n");
        goto Exit;
    }

    /* 开始计时 */
    start = tickGet();

    /* 显示接收数据 */
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
函数名称:   tcp_tx_performance

函数功能:   测试网卡进行TCP通讯时的性能

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   利用这个函数测试网卡的接收性能

修改记录:   2013-04-27      徐佳谋  创建
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

    /* 使用Tick计算 先设置Tick为1ms */
    sysClkRateSet(1000);

    /* 必须清零 */
    memset(&serverAddr, 0x00, sizeof(struct sockaddr_in));

    /* 生成测试数据 */
    for (i = 0; i < sizeof(TxBuffer); i++)
    {
        TxBuffer[i] = i;
    }

    /* 创建套接字 */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == ERROR)
    {
        ret = ERROR;
        printf("Create tcp socket failed!\n");
        goto Exit;
    }

    /* 设置发送缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_SNDBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_SNDBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 设置接收缓冲区大小 */
    ret = setsockopt(client, SOL_SOCKET, SO_RCVBUF, (char *)&to_send, sizeof(to_send));
    if (ret < 0)
    {
        printf("setsockopt(SO_RCVBUF) failed!%d\n", ret);
        goto Exit;
    }

    /* 输入IP地址最后一位 */
    /* 输入IP地址倒数第二位和最后一位 */
    printf("Input the third and fouth ip address (1-254):\n");
    input = GetKeyInput(10);
    ip1 = input ? (input % 255) : 1;
    input = GetKeyInput(10);
    ip2 = input ? (input % 255) : 1;

    sprintf(IpAddress, "192.168.%d.%d", ip1, ip2);

    /* 设置服务器信息 */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (TCP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IpAddress);

    /* 连接服务器 */
    if (connect(client, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) == -1)
    {
        ret = ERROR - 1;
        printf("Connect to tcp server failed!\n");
        goto Exit;
    }

    /* 开始计时 */
    start = tickGet();

    /* 发送数据 */
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
    /* 关闭套接字 */
    if (client != 0)
    {
        close(client);
    }

    /* 关闭文件 */
    if (fp != NULL)
    {
        fclose(fp);
    }

    return ret;
}

/********************************************************************
函数名称:   lcd_test

函数功能:   测试LCD的背光控制功能

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数只对AT5010、CD6010板卡有效。寄存器总线号、设备号、功能号固定。

修改记录:   2013-06-27      徐佳谋  创建
********************************************************************/
int lcd_test()
{
    int ret = 0;
    unsigned char uch = 0;

    /* 读取PCI设备配置空间 */
    pciConfigInByte(0x00, 0x02, 0x00, 0xF4, &uch);

    printf("Input New LCD BackLight Value(0x00-0xFF):(Now = 0x%02X)\n", uch);
    uch = (unsigned char)GetKeyInput(16);

    pciConfigOutByte(0x00, 0x02, 0x00, 0xF4, uch);

    return ret;
}

/********************************************************************
函数名称:   sem_test

函数功能:   测试信号量功能

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数创建任务，测试二值信号量等

修改记录:   2014-07-04      徐佳谋  创建
********************************************************************/
int sem_test()
{
    SEM_ID sem;

    /* 创建二值信号量 */
    sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    /* 创建测试任务 */
    taskSpawn("tTestSem", 100, 0, 1024 * 40, (FUNCPTR)tTestSem, (int)sem, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    printf("Press any key to give semaphore\n");
    getchar();

    semGive(sem);

    taskDelay(sysClkRateGet());

    semDelete(sem);

    return 0;
}

/********************************************************************
函数名称:   tTestSem

函数功能:   测试信号量的任务

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数创建任务，测试二值信号量等

修改记录:   2014-07-04      徐佳谋  创建
********************************************************************/
int tTestSem(SEM_ID sem)
{
    semTake(sem, WAIT_FOREVER);

    printf("semaphore has been taken.\n");

    return 0;
}

/********************************************************************
函数名称:   timer0_test

函数功能:   测试系统中断0

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   函数测试定时器0，通过串口RTS输出信号测量。

修改记录:   2015-05-21      徐佳谋  创建
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

    /* 设置系统时钟 */
    sysClkRateSet(input);

    printf("sysClkRateGet = %d\n", sysClkRateGet());

    /* 注册回调函数 */
    sysClkConnect(timer0_callback, 0);

    return 0;
}

/********************************************************************
函数名称:   timer0_callback

函数功能:   定时器0的回调函数

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   控制串口RTS输出波形。

修改记录:   2015-05-21      徐佳谋  创建
********************************************************************/
int timer0_callback()
{
    static unsigned char uch = 0x02;

    sysOutByte(0x3F8 + 4, uch);
    uch = ~uch;

    return 0;
}

/********************************************************************
函数名称:   com_change_baudrate

函数功能:   修改串口波特率

参数名称        类型            输入/输出           含义

返回值  :   0代表成功 非0代表失败

函数说明:   修改串口波特率。

修改记录:   2016-04-08      徐佳谋  创建
********************************************************************/
int com_change_baudrate()
{
    int com = 0;
    int input = 0;
    int fd = 0;
    int ret = 0;

    /* 指定串口 */
    printf("Input COM Number:(1-8:COM 9-16:EXTCOM 17-24:CSDCOM)\n");
    input = GetKeyInput(10) % 24;
    com = (input - 1);

    /* 设置波特率 */
    printf("Input Baudrate:(0:115.2Kbps 1:230.4Kbps 2:460.8Kbps 3:921.6Kbps 4:1.5Mbps)\n");
    input = GetKeyInput(10) % 5;
    g_com_baud = g_ComBauds[input];

    /* 打开发送串口 */
    fd = open(g_ExtComName[com], O_RDWR, 0);
    if (fd == ERROR)
    {
        printf("Open %s failed!\n", g_ExtComName[com]);
        return fd;
    }

    printf("Open %s succeeded\n", g_ExtComName[com]);

    /* 配置串口参数 */
    /* 数据位8位 停止位1位 奇校验 本地模式 */
    ret += ioctl(fd, SIO_HW_OPTS_SET, CLOCAL | CS8 | PARODD | PARENB);
    ret += ioctl(fd, FIOBAUDRATE, g_com_baud);  /* 波特率 */
    ret += ioctl(fd, FIOSETOPTIONS, OPT_RAW);   /* 原始模式OPT_RAW 行模式OPT_LINE 根据情况选择 */
    ret += ioctl(fd, FIOFLUSH, 0);              /* 清空缓冲区 */

    close(fd);

    return ret;
}
