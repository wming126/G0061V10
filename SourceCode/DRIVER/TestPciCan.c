/********************************************************************
文件名称:   TestPciCan.c

文件功能:   测试PCI总线CAN设备

文件说明:   测试GTR64101板卡驱动功能

当前版本:   V1.2

修改记录:   2013-07-24  V1.0    徐佳谋  创建
            2014-06-26  V1.1    李世杰  升级    针对GTR64101修改
            2015-10-20  V1.2    徐佳谋  升级    配合驱动修改
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
函数名称:   ConvertIDtoBuffer

函数功能:   将int型ID转化成帧格式ID

参数名称        类型            输入/输出           含义
ID              unsigned int    input               需要转换的int型ID
pframe          sja1000_frame_t output              帧指针

返回值  :   0代表成功 非0代表失败

函数说明:   将int型ID转化成帧格式ID，并保存到发送帧结构当中

修改记录:   2016-04-29  王  明    创建
********************************************************************/
static int ConvertIDtoBuffer(unsigned int ID, sja1000_frame_t* pframe)
{
    if((pframe->header & 0x80) == 0x80) /* 扩展帧 */
    {
        /* 判断id有效性 */
        if(ID > 0x1fffffff)
        {
            printf("Id format error!\n");
            return -1;
        }
        
        ID = ID << 3;
        
        pframe->buffer[3] = (ID & 0xf8); /* 高5位有效 */
        pframe->buffer[2] = ((ID >> 8) & 0xff);
        pframe->buffer[1] = ((ID >> 16) & 0xff);
        pframe->buffer[0] = ((ID << 24) & 0xff);
    }
    else /* 标准帧 */
    {
        /* 判断id有效性 */
        if(ID > 0x7ff)
        {
            printf("Id format error!\n");
            return -1;
        }

        ID = ID << 5;
        
        pframe->buffer[1] = (ID & 0xe0);/* 高3位有效 */
        
        pframe->buffer[0] = ((ID >> 8) & 0xff);
    }
    
    return 0;
}
#endif

/********************************************************************
函数名称:   ConvertBufferToID

函数功能:   从接收的帧中提取int型ID

参数名称        类型            输入/输出           含义
pframe          sja1000_frame_t input               帧指针

返回值  :   RetID(int型ID)

函数说明:   从接收的帧中提取int型ID

修改记录:   2016-04-29  王  明    创建
********************************************************************/
static unsigned int ConvertBufferToID(sja1000_frame_t* pframe)
{
    unsigned int RetID = 0;

    if((pframe->header & 0x80) == 0x80) /* 扩展帧 */
    {
        /* 将数据直接转换到pframe数组中 */
        RetID = ((pframe->buffer[0] << 24) | (pframe->buffer[1] << 16)
                    | (pframe->buffer[2] << 8) | ((pframe->buffer[3]) & 0xf8) ) >> 3;
    }
    else /* 标准帧 */
    {
        RetID = ((pframe->buffer[0] << 8) | ((pframe->buffer[1]) & 0xe0) ) >> 5;
    }   
    
    return RetID;
}

/********************************************************************
函数名称:   tCanReceive2

函数功能:   数据接收任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   任务等待驱动触发事件(接收到数据)，接收数据，检查并计数

修改记录:   2014-8-10  李世杰  创建
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
            /* 计算校验和是否正确 */
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
函数名称:   crc16

函数功能:   计算CRC校验

参数名称        类型            输入/输出           含义
puch            unsigned char*  input               缓冲区指针
length          int             input               数据长度

返回值  :   16bit校验结果

函数说明:   通过校验判断数据正确性

修改记录:   2014-02-18  李世杰  创建
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
函数名称:   TestPciCan

函数功能:   测试CAN通讯(调试)

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   在使用驱动前，需要先创建板卡设备。

修改记录:   2014-08-22  李世杰  创建
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

    /* 第二阶段初始化 */
    CreatePciCan2(index);

    /* 初始化SJA1000芯片 */
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
        case 1: /* 选择一路发送数据 */
            /* 设置发送帧格式 */
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

        case 2: /* 显示计数 */
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

        case 3: /* 清除计数 */
            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                g_received_counts[i] = 0;
                g_transmit_counts[i] = 0;
                g_recv_err_counts[i] = 0;
                g_tran_err_counts[i] = 0;

                /* 清除FIFO */
                ret = FlushPciCan(i);
                if (ret != 0)
                {
                    printf("channel %d FlushPciCan failed!%d\n", i, ret);
                }
            }
            printf("Counts are clean.\n");
            break;

        case 97: /* 显示状态信息 */
            ShowPciCan(index);
            break;

        case 98:
            g_pcican_debug = !g_pcican_debug;
            printf("debug = %d\n", g_pcican_debug);
            break;

        case 99: /* 退出程序 */
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

    /* 关闭设备 */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        ClosePciCan(i);
    }

    return ret;
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

修改记录:   2010-10-27      徐佳谋  创建
********************************************************************/
static int GetKeyInput(int radix)
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
函数名称:   InitPciCan

函数功能:   CAN口初始化集合函数

参数名称        类型            输入/输出           含义
fd              int             input               设备描述符(对应CAN口)
BaudRate        int             input               波特率

返回值  :   0:成功 非0:失败

函数说明:   集合多个初始化函数，使应用程序简洁。

修改记录:   2014-08-14  李世杰  创建
            2014-08-26  徐佳谋  增加 根据驱动变化更改
********************************************************************/
int InitPciCan(int fd, int BaudRate)
{
    sja1000_config_t config;
    int ret = 0;

    /* 打开设备 */
    ret = OpenPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d OpenPciCan failed!%d\n", fd, ret);
        return -1;
    }

    /* 初始化SJA1000芯片 */
    config.uchMOD    = 0x00;
    config.uchCDR    = 0xC4;    /* 不清楚含义时不需要修改 */
    config.uchOCR    = 0xDA;    /* 不清楚含义时不需要修改 */
    config.uchBTR0   = BaudRate >> 8;
    config.uchBTR1   = BaudRate;   /* 波特率 */
    config.uchACR[0] = 0x00;
    config.uchACR[1] = 0x00;
    config.uchACR[2] = 0x00;
    config.uchACR[3] = 0x00;
    config.uchAMR[0] = 0xFF;
    config.uchAMR[1] = 0xFF;
    config.uchAMR[2] = 0xFF;
    config.uchAMR[3] = 0xFF;
    config.uchIER = 0x83;       /* 使能总线错误 接收数据 发送完成 必须设置为0x83 */
    config.uchRXERR = 0;
    config.uchTXERR = 0;
    config.uchEWLR = 0x60;

    /* 初始化芯片 */
    ret = IoctlPciCan(fd, IOCTL_INIT_SJA, &config);
    if (ret != 0)
    {
        printf("channel %d IoctlPciCan failed(IOCTL_INIT_SJA)!%d\n", fd, ret);
    }

    /* 清除FIFO */
    ret = FlushPciCan(fd);
    if (ret != 0)
    {
        printf("channel %d FlushPciCan failed!%d\n", fd, ret);
    }

    return ret;
}
