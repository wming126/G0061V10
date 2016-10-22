/********************************************************************
文件名称:   PciCanLib.h

文件功能:   板卡驱动头文件文件

文件说明:   定义驱动中使用到的宏、数据结构、函数声明

当前版本:   V1.5

修改记录:   2014-06-25  V1.0    李世杰  创建
            2014-09-04  V1.1    李世杰  升级    重新设计驱动结构
            2014-11-06  V1.2    李世杰  升级    解决一个文件描述符bug
            2015-10-20  V1.3    徐佳谋  升级    统一函数名，解决5.5无法使用问题
            2016-04-21  V1.4    徐佳谋  升级    解决接收丢帧问题，修改发送函数
            2016-06-17  V1.5    徐佳谋  增加    增加版本显示函数
********************************************************************/

#ifndef _PCICANLIB_H_
#define _PCICANLIB_H_

/* FPGA相关寄存器 */
/* 板卡 #define FPGA_CAN_INT_STATE      (0x1002)    0360板卡  bit0-bit1中断状态 */
#define FPGA_CAN_INT_STATE      (0x1002)    /* 0440板卡 bit0-bit2中断状态 */

/* CAN芯片相关寄存器 */
#define CAN_CHANNEL_STRIDE      (0x100)     /* 每个CAN通道步进 */
#define CAN_MODE_REG            (0x00)
#define CAN_CTRL_REG            (0x01)
#define CAN_STATE_REG           (0x02)
#define CAN_IRQ_REG             (0x03)
#define CAN_IRQ_ENABLE          (0x04)
#define CAN_RECV_FIFO_OFFSET    (16)
#define CAN_TRAN_FIFO_OFFSET    (16)

/* 桥芯片相关寄存器 */
#define PLX9056_VENDOR_ID       (0x10B5)    /* 厂商标识 */
#define PLX9056_DEVICE_ID       (0x9056)    /* 设备标识 */

#define MAX_PCICAN_NUM          (1)

#define MAX_CAN_NUM             (2)
#define INT_MASK                ((0x1 << MAX_CAN_NUM) - 1)
#define CAN_FIFO_SIZE           (13 * 8000)
#define CAN_TX_FIFO_SIZE        (13 * 1000)

#define IOCTL_INIT_SJA          (0)

/* SJA1000芯片初始化结构体 注意结构体内存对齐问题 */
typedef struct sja1000_config_s
{
    unsigned char uchMOD;       /* Mode Register */
    unsigned char uchCDR;       /* Clock Divider Register */
    unsigned char uchOCR;       /* Output Control Register */
    unsigned char uchBTR0;      /* Bus0 Timing Register */
    unsigned char uchBTR1;      /* Bus1 Timing Register */
    unsigned char uchACR[4];    /* Acceptance Code Register */
    unsigned char uchAMR[4];    /* Acceptance Mask Register */
    unsigned char uchIER;       /* Interrupt Enable Register */
    unsigned char uchRXERR;     /* RX Error Counter Register */
    unsigned char uchTXERR;     /* TX Error Counter Register */
    unsigned char uchEWLR;      /* Error Warning Limit Register */
} sja1000_config_t;

/* SJA1000芯片数据帧数据结构 注意结构体内存对齐问题 */
typedef struct sja1000_frame_s
{
    unsigned char header;
    unsigned char buffer[12];
} sja1000_frame_t;

enum Baud_Rate
{
    BAUDRATE_1000K   = 0x0014,
    BAUDRATE_800K    = 0x0016,
    BAUDRATE_500K    = 0x001C,
    BAUDRATE_250K    = 0x011C,
};

/* 导出函数说明 */
int CreatePciCan(int index);
int RemovePciCan(int index);
int CreatePciCan2(int index);
int RemovePciCan2(int index);
int OpenPciCan(int fd);
int ClosePciCan(int fd);
int WritePciCan(int fd, sja1000_frame_t *pFrame);
int ReadPciCan(int fd, sja1000_frame_t *pFrame, int timeout);
int IoctlPciCan(int fd, int cmd, void *p);
int FlushPciCan(int fd);
int ShowPciCan(int fd);
char *GetPciCan(int index);

#endif
