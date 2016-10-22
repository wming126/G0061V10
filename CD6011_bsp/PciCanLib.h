/********************************************************************
�ļ�����:   PciCanLib.h

�ļ�����:   �忨����ͷ�ļ��ļ�

�ļ�˵��:   ����������ʹ�õ��ĺꡢ���ݽṹ����������

��ǰ�汾:   V1.5

�޸ļ�¼:   2014-06-25  V1.0    ������  ����
            2014-09-04  V1.1    ������  ����    ������������ṹ
            2014-11-06  V1.2    ������  ����    ���һ���ļ�������bug
            2015-10-20  V1.3    ���ı  ����    ͳһ�����������5.5�޷�ʹ������
            2016-04-21  V1.4    ���ı  ����    ������ն�֡���⣬�޸ķ��ͺ���
            2016-06-17  V1.5    ���ı  ����    ���Ӱ汾��ʾ����
********************************************************************/

#ifndef _PCICANLIB_H_
#define _PCICANLIB_H_

/* FPGA��ؼĴ��� */
/* �忨 #define FPGA_CAN_INT_STATE      (0x1002)    0360�忨  bit0-bit1�ж�״̬ */
#define FPGA_CAN_INT_STATE      (0x1002)    /* 0440�忨 bit0-bit2�ж�״̬ */

/* CANоƬ��ؼĴ��� */
#define CAN_CHANNEL_STRIDE      (0x100)     /* ÿ��CANͨ������ */
#define CAN_MODE_REG            (0x00)
#define CAN_CTRL_REG            (0x01)
#define CAN_STATE_REG           (0x02)
#define CAN_IRQ_REG             (0x03)
#define CAN_IRQ_ENABLE          (0x04)
#define CAN_RECV_FIFO_OFFSET    (16)
#define CAN_TRAN_FIFO_OFFSET    (16)

/* ��оƬ��ؼĴ��� */
#define PLX9056_VENDOR_ID       (0x10B5)    /* ���̱�ʶ */
#define PLX9056_DEVICE_ID       (0x9056)    /* �豸��ʶ */

#define MAX_PCICAN_NUM          (1)

#define MAX_CAN_NUM             (2)
#define INT_MASK                ((0x1 << MAX_CAN_NUM) - 1)
#define CAN_FIFO_SIZE           (13 * 8000)
#define CAN_TX_FIFO_SIZE        (13 * 1000)

#define IOCTL_INIT_SJA          (0)

/* SJA1000оƬ��ʼ���ṹ�� ע��ṹ���ڴ�������� */
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

/* SJA1000оƬ����֡���ݽṹ ע��ṹ���ڴ�������� */
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

/* ��������˵�� */
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
