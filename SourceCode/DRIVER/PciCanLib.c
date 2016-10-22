/********************************************************************
�ļ�����:   PciCanLib.c

�ļ�����:   �忨����Դ�ļ�

�ļ�˵��:   ʵ��PCI�忨CAN����ͨѶ����

��ǰ�汾:   V1.6

�޸ļ�¼:   2014-06-25  V1.0    ������  ����
            2014-09-04  V1.1    ������  ����    ������������ṹ
            2014-11-06  V1.2    ������  ����    ���һ���ļ�������bug
            2015-10-20  V1.3    ���ı  ����    ͳһ�����������5.5�޷�ʹ������
            2016-04-21  V1.4    ���ı  ����    ������ն�֡���⣬�޸ķ��ͺ���
            2016-06-17  V1.5    ���ı  ����    ���Ӱ汾��ʾ����
            2016-08-02  V1.6    ���ı  ����    �޸�Ϊ�������ͣ�ͬʱ�����λ���ɹ�����   
********************************************************************/

#ifndef _WRS_CONFIG_SMP
#define _WRS_CONFIG_SMP /* ˫��ģʽ */
#endif

#include "stdio.h"
#include "string.h"
#include "vmLib.h"
#include "drv\pci\pciConfigLib.h"
#include "arch\I86\ivI86.h"
#include "semLib.h"
#include "rngLib.h"
#include "msgQLib.h"
#include "logLib.h"
#include "drv\pci\pciIntLib.h"
#include "taskLib.h"

#include "PciCanLib.h"

/* ���Ժ� */
#define DEBUG                   0

#ifdef _WRS_CONFIG_SMP
IMPORT UINT8 *sysInumTbl;
#undef INT_NUM_GET
#define INT_NUM_GET(irq) sysInumTbl[irq]
#else
#define INT_NUM_IRQ0            0x20
#undef INT_NUM_GET
#define INT_NUM_GET(irq)        ((int)irq + INT_NUM_IRQ0)
#endif

#define VM_STATE_MASK_FOR_ALL   VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE
#define VM_STATE_FOR_PCI        VM_STATE_VALID | VM_STATE_WRITABLE | VM_STATE_CACHEABLE_NOT
#define VM_PAGE_SIZE            4096
#define PCI_DEV_MMU_MSK         (~(VM_PAGE_SIZE - 1))

/* �Ĵ������ʺ� */
#define READ_REGISTER_UCHAR(x)      (*(volatile unsigned char *)(x))
#define READ_REGISTER_USHORT(x)     (*(volatile unsigned short *)(x))
#define READ_REGISTER_ULONG(x)      (*(volatile unsigned long *)(x))

#define WRITE_REGISTER_UCHAR(x, y)  (*(volatile unsigned char *)(x) = (unsigned char)((y) & 0xFF))
#define WRITE_REGISTER_USHORT(x, y) (*(volatile unsigned short *)(x) = (unsigned short)((y) & 0xFFFF))
#define WRITE_REGISTER_ULONG(x, y)  (*(volatile unsigned long *)(x) = (unsigned long)(y))

typedef struct pcican_device_s
{
    unsigned long ulBase0;  /* ӳ�����ַ */
    unsigned long ulBase2;  /* ӳ�����ַ */
    unsigned long ulSize;   /* ӳ���ַ��С */
    int irq;                /* �Ƿ�ע���жϱ�־ */
    int tid;                /* ����ʹ������ */
    int isr;                /* �����ж�ע���־ */
    int fpga;               /* FPGA�汾 */
    SEM_ID sem;             /* ��������ʹ���ź��� */
} pcican_device_t;

/* SJA1000оƬ��ʼ���ṹ�� ע��ṹ���ڴ�������� */
typedef struct pcican_sja1000_s
{
    unsigned long base;
    RING_ID ring;   /* ��������ʹ�õ����FIFO */
    RING_ID ring2;  /* ��������ʹ�õķ���FIFO */
    SEM_ID sem2;    /* Ӧ�ó���ʹ���ź��� */
    SEM_ID mutex;   /* ����ʹ�û����� */
    SEM_ID sem3;    /* ����ʹ���ź��� */
    SEM_ID sem4;    /* �������ʹ���ź��� */
    int tid2;       /* ��������tid */
    MSG_Q_ID msg;   /* ��������ʹ����Ϣ */
} pcican_sja1000_t;

/* ȫ���豸�ṹ */
pcican_device_t g_devices[MAX_DEVICE_NUM];
pcican_sja1000_t g_sja1000s[MAX_CAN_NUM];
static char s_versions[64];

/* �ڲ��������� */
void iPciCan(void *para);
int tPciCan(void *para);
int tPciCan2(MSG_Q_ID msg);
int DrainFifo(int fd);

int InitSja(pcican_sja1000_t *pCan, sja1000_config_t *pConfig);

extern STATUS sysIntEnablePIC(int intLevel);
extern STATUS sysMmuMapAdd(void *address, UINT len, UINT initialStateMask, UINT initialState);

/********************************************************************
��������:   CreatePciCan

��������:   ��һ�׶γ�ʼ��������

��������        ����            ����/���           ����
index           int             input               �豸����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʹ������ǰ����Ҫ�ȴ����忨�豸��������ʼ��ȫ���豸������

�޸ļ�¼:   2014-06-25  ������  ����
********************************************************************/
int CreatePciCan(int index)
{
    int ret = 0;
    int BusNo;
    int DeviceNo;
    int FuncNo;
    unsigned int ul;
    pcican_device_t *pDevice = NULL;

    /* ��ֹ�������� ��ȡ�豸�ṹ��ָ�� */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* �ж��Ƿ��Ѿ�ӳ���ַ */
    if(pDevice->ulBase2 != 0)
    {
        return 0;
    }

    /* ����PCI���߲���PLX9056�豸 */
    ret = pciFindDevice(PLX9056_VENDOR_ID, PLX9056_DEVICE_ID, index, &BusNo, &DeviceNo, &FuncNo);
    if (ret == -1)
    {
        ret = -1;
        goto Exit;
    }

    /* ��ȡ�豸ӳ��ռ��ַ0 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &ul);
    if (ret == -1)
    {
        ret = -2;
        goto Exit;
    }

    pDevice->ulBase0 = ul;

    /* ӳ���ڴ���� */
    ret = sysMmuMapAdd((void *)(pDevice->ulBase0 & PCI_DEV_MMU_MSK), 4096, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_PCI);
    if (ret == -1)
    {
        /*ret = -3;
        goto Exit; ��Ӧ�ò����ʱ �޷����� */
    }

    /* ��ȡ�豸ӳ��ռ��ַ2 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, &ul);
    if (ret == -1)
    {
        ret = -4;
        goto Exit;
    }

    pDevice->ulBase2 = ul;

    /* ��ȡ�豸ӳ��ռ䳤�� */
    pciConfigOutLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, 0xFFFFFFFF);
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, &ul);
    if (ret == -1)
    {
        ret = -5;
        goto Exit;
    }

    pDevice->ulSize = (~ul | 0x0F) + 1;  /* �Ѿ�ȷ�����ڴ�ӳ�� */

    /* ӳ���ڴ���� */
    ret = sysMmuMapAdd((void *)(pDevice->ulBase2 & PCI_DEV_MMU_MSK), pDevice->ulSize, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_PCI);
    if (ret == -1)
    {
        /*ret = -6;
        goto Exit; ��Ӧ�ò����ʱ �޷����� */
    }

    /* �����д��ַ */
    pciConfigOutLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_2, pDevice->ulBase2);

    /* ��ȡ�豸�жϺ� */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &ul);
    if (ret == -1)
    {
        ret = -7;
        goto Exit;
    }

    pDevice->irq = ul & 0xFF;

    return ret;

Exit:
    RemovePciCan(index);

    return ret;
}

/********************************************************************
��������:   RemovePciCan

��������:   ɾ���忨����

��������        ����            ����/���           ����
index           int             input               �忨����(0-1)

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �����һ�׶γ�ʼ��������

�޸ļ�¼:   2014-06-25  ������  ����
********************************************************************/
int RemovePciCan(int index)
{
    int ret = 0;
    pcican_device_t *pDevice = NULL;

    /* ��ֹ�������� */
    index %= MAX_DEVICE_NUM;

    /* �ж��Ƿ��Ѿ�ӳ���ַ */
    pDevice = &g_devices[index];
    if (pDevice->ulBase2 == 0)
    {
        return -1;
    }

    /* ��ɾ���ڶ��׶� */
    RemovePciCan2(index);

    pDevice->ulBase2 = 0;

    return ret;
}

/********************************************************************
��������:   CreatePciCan2

��������:   �ڶ��׶γ�ʼ������

��������        ����            ����/���           ����
index           int             input               �豸����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �����ڵ���CreatePciCan�����󣬻���Ҫ���ô˺���������ʼ����

�޸ļ�¼:   2015-10-20  ���ı  ����
********************************************************************/
int CreatePciCan2(int index)
{
    int ret = 0;
    int i = 0;
    pcican_device_t *pDevice = NULL;

    /* ��ֹ�������� ��ȡ�豸�ṹ��ָ�� */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* �ж��Ƿ��Ѿ�ӳ���ַ */
    if(pDevice->ulBase2 == 0)
    {
        return -1;
    }

    /* �ж��Ƿ��Ѿ�ע���ж� */
    if (pDevice->isr == 1)
    {
        return 0;
    }

    /* ��¼CAN�ڻ���ַ */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        g_sja1000s[i].base = pDevice->ulBase2 + i * CAN_CHANNEL_STRIDE;
    }

    /* �����ź��� */
    pDevice->sem = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pDevice->sem == NULL)
    {
        ret = -2;
        goto Exit;
    }

    /* �������� */
    pDevice->tid = taskSpawn("tPciCan", 0, (VX_SUPERVISOR_MODE | VX_UNBREAKABLE), 8192, tPciCan, (int)pDevice, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pDevice->tid == -1)
    {
        ret = -3;
        goto Exit;
    }

    /* ע���жϷ������ */
    ret = pciIntConnect(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciCan, (int)pDevice);
    if (ret == -1)
    {
        ret = -4;
        goto Exit;
    }
    pDevice->isr = 1;

    /* ʹ���ж� */
    sysIntEnablePIC(pDevice->irq);

    /* ��Local Bus �ж� */
    WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68) | (0x01 << 11));

    return ret;

Exit:
    RemovePciCan2(index);

    return ret;
}

/********************************************************************
��������:   RemovePciCan2

��������:   ɾ���忨����2

��������        ����            ����/���           ����
index           int             input               �忨����(0-1)

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �ر��жϣ�����ڶ��׶γ�ʼ��������

�޸ļ�¼:   2015-10-20  ���ı  ����
********************************************************************/
int RemovePciCan2(int index)
{
    int i = 0;
    pcican_device_t *pDevice = NULL;

    /* �ȹر�����ͨ�� */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        ClosePciCan(i);
    }

    /* ��ֹ�������� ��ȡ�豸�ṹ��ָ�� */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* �ر�FPGA�ж� */
    WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, (READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68) & ~(0x01 << 11)));

    if (pDevice->isr != 0)
    {
        pciIntDisconnect2(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciCan, (int)pDevice);
        pDevice->isr = 0;
    }

    if (pDevice->tid != 0)
    {
        taskDelete(pDevice->tid);
        pDevice->tid = 0;
    }

    if (pDevice->sem != NULL)
    {
        semDelete(pDevice->sem);
        pDevice->sem = 0;
    }

    return 0;
}

/********************************************************************
��������:   OpenPciCan

��������:   ���豸

��������        ����            ����/���           ����
fd              int             input               �豸������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��������������Ҫʹ�õ��ź��������񡢶��С�ע���жϷ������ȡ�

�޸ļ�¼:   2013-07-22  ���ı  ����
********************************************************************/
int OpenPciCan(int fd)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* ������� */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->base == 0)
    {
        return -1;
    }

    /* ���������� */
    pCan->mutex = semMCreate(SEM_Q_FIFO | SEM_DELETE_SAFE);
    if (pCan->mutex == NULL)
    {
        ret = -2;
        goto Exit;
    }

    /* ����FIFO */
    pCan->ring = rngCreate(CAN_FIFO_SIZE);
    if (pCan->ring == NULL)
    {
        ret = -3;
        goto Exit;
    }

    pCan->ring2 = rngCreate(CAN_TX_FIFO_SIZE);
    if (pCan->ring2 == NULL)
    {
        ret = -3;
        goto Exit;
    }

    /* �����ź��� */
    pCan->sem2 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pCan->sem2 == NULL)
    {
        ret = -4;
        goto Exit;
    }

    pCan->sem3 = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
    if (pCan->sem3 == NULL)
    {
        ret = -5;
        goto Exit;
    }

    pCan->sem4 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pCan->sem4 == NULL)
    {
        ret = -5;
        goto Exit;
    }

    /* ������Ϣ���� */
    pCan->msg = msgQCreate(100, 32, MSG_Q_PRIORITY);
    if (pCan->msg == NULL)
    {
        ret = -6;
        goto Exit;
    }

    /* ������������ */
    pCan->tid2 = taskSpawn("tPciCan2", 100, (VX_SUPERVISOR_MODE | VX_UNBREAKABLE), 8192, tPciCan2, (int)pCan->msg, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pCan->tid2 == -1)
    {
        ret = -7;
        goto Exit;
    }

    return ret;

Exit:
    ClosePciCan(fd);

    return ret;
}

/********************************************************************
��������:   ClosePciCan

��������:   �ر�PCICAN�忨����

��������        ����            ����/���           ����
fd              int             input               �豸������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �����رմ������ź��������񡢶��С��ж�ע�ᡣ

�޸ļ�¼:   2014-06-25  ������  ����
********************************************************************/
int ClosePciCan(int fd)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* ������� */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->tid2 == 0)
    {
        return -1;
    }

    /* ��ֹCAN��оƬ�ж� */
    WRITE_REGISTER_UCHAR(pCan->base + 4, 0x00);

    /* ɾ������ */
    if (pCan->ring != NULL)
    {
        rngDelete(pCan->ring);
        pCan->ring  = 0;
    }

    if (pCan->ring2 != NULL)
    {
        rngDelete(pCan->ring2);
        pCan->ring2 = 0;
    }

    if (pCan->sem2 != NULL)
    {
        semDelete(pCan->sem2);
        pCan->sem2 = 0;
    }

    if (pCan->sem3 != NULL)
    {
        semDelete(pCan->sem3);
        pCan->sem3 = 0;
    }

    if (pCan->sem4 != NULL)
    {
        semDelete(pCan->sem4);
        pCan->sem4 = 0;
    }

    if (pCan->mutex != NULL)
    {
        semDelete(pCan->mutex);
        pCan->mutex = 0;
    }

    if (pCan->tid2 != 0)
    {
        taskDelete(pCan->tid2);
        pCan->tid2 = 0;
    }

    if (pCan->msg != NULL)
    {
        msgQDelete(pCan->msg);
        pCan->msg = 0;
    }

    return ret;
}

/********************************************************************
��������:   IoctlPciCan

��������:   ʵ�ֲ�ͬ���ܵ�������

��������        ����            ����/���           ����
fd              int             input               �豸������
cmd             int             input               ������
p               void*           input/output        �����ֶ�Ӧ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ͨ����ͬ���������������ʵ�ֲ�ͬ�Ĺ��ܡ�
            IOCTL_INIT_SJA��ʼ��оƬ��

�޸ļ�¼:   2014-06-25  ������  ����
********************************************************************/
int IoctlPciCan(int fd, int cmd, void *p)
{
    pcican_sja1000_t *pCan = NULL;
    int ret = 0;

    /* ȷ���豸��Ч */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];

    /* ���������� */
    switch(cmd & 0x00FF)
    {
    case IOCTL_INIT_SJA:            /* ��ʼ��SJA������ */
        InitSja(pCan, p);

        break;

    default:
        ;
    }

    return ret;
}

/********************************************************************
��������:   WritePciCan

��������:   ͨ��FIFO����CAN����֡(1֡)

��������        ����             ����/���           ����
fd              int              input               �豸������
pFrame          sja1000_frame_t* input               ��������ָ��

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ͨ�����������ݣ�ֱ��дSJA1000���ͼĴ��������ڲ�ѯ���͡�

�޸ļ�¼:   2014-06-25  ������  ����
            2016-04-22  ���ı  ����    �޸�Ϊ�жϷ���
********************************************************************/
int WritePciCan(int fd, sja1000_frame_t *pFrame)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* ������� */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->tid2 == 0)
    {
        return -1;
    }

    /* �ȴ������п��� */
    semTake(pCan->sem3, WAIT_FOREVER);

    /* ��֤���ʻ��� */
    semTake(pCan->mutex, WAIT_FOREVER);

    /* �������ݷ���FIFO */
    rngBufPut(pCan->ring2, (char *)pFrame, sizeof(sja1000_frame_t));

    /* ������������ */
    msgQSend(pCan->msg, (char *)&pCan, sizeof(pCan), NO_WAIT, MSG_PRI_URGENT);

    /* �жϻ������Ƿ��п��� */
    if (rngFreeBytes(pCan->ring2) >= sizeof(sja1000_frame_t))
    {
        /* ʹ�ܷ��� */
        semGive(pCan->sem3);
    }

    /* �ͷŻ��� */
    semGive(pCan->mutex);

    return ret;
}

/********************************************************************
��������:   ReadPciCan

��������:   ��ȡFIFO�е�CAN����֡(1֡)

��������        ����            ����/���           ����
fd              int             input               �豸������
pFrame          sja1000_frame_t*output              ��������ָ��
timeout         int             output              ��ȡ������ʱ(-1:���� n:����)

����ֵ  :   0:������Ϊ�� 13:����һ֡���� ����:ʧ��

����˵��:   ����������FIFO�ж�ȡ���յ������ݣ�ÿ��һ֡��

�޸ļ�¼:   2014-06-25  ������   ����
********************************************************************/
int ReadPciCan(int fd, sja1000_frame_t *pFrame, int timeout)
{
    int ret = 0;
    pcican_sja1000_t *pCan = NULL;

    /* ������� */
    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];
    if (pCan->tid2 == 0)
    {
        return -1;
    }

    /* ��֤һ�ζ������� */
    if (rngIsEmpty(pCan->ring))
    {
        /* �ȴ��ź��� */
        if (semTake(pCan->sem2, timeout) == -1)
        {
            return -2;
        }
    }

    /* ����������� */
    ret = rngBufGet(pCan->ring, (char *)pFrame, sizeof(sja1000_frame_t));
    if ((ret == 0) && (timeout == -1))
    {
        /* ͨ���ݹ������ź�������0������ */
        ret = ReadPciCan(fd, pFrame, timeout);
    }

    return ret;
}

/********************************************************************
��������:   FlushPciCan

��������:   �����������

��������        ����            ����/���           ����
*pCan           pcican_sja1000_t  input               �豸�ṹ��

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��λSJA1000оƬ����������������

�޸ļ�¼:   2014-6-26  ������  ����
********************************************************************/
int FlushPciCan(int fd)
{
    int ret = 0;
    unsigned long base;
    pcican_sja1000_t *pCan = NULL;

    fd = fd > (MAX_CAN_NUM - 1) ? 0 : fd;
    pCan = &g_sja1000s[fd];

    /* �ж�CAN���Ƿ��Ѿ��� */
    if (pCan->sem2 == NULL)
    {
        return -1;
    }

    base = pCan->base;

    /* �ͷ�SJA1000���ջ��� */
    while (READ_REGISTER_UCHAR(base + CAN_STATE_REG) & 0x01)
    {
        WRITE_REGISTER_UCHAR(base + CAN_CTRL_REG, 0x04);
    }

    /* ������������ */
    rngFlush(pCan->ring);
    rngFlush(pCan->ring2);

    /* ʹ�ܷ��� */
    semGive(pCan->sem3);

    return ret;
}

/********************************************************************
��������:   iPciCan

��������:   �忨�жϷ������

��������        ����            ����/���           ����
*para           void            input               �忨��Ϣ���ݲ���

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �жϷ�������ж��ж�Դ�������жϡ������жϡ�
            �����Ĳ����ں���������ʵ�֡�

�޸ļ�¼:   2013-07-22  ������  ����
********************************************************************/
void iPciCan(void *para)
{
    unsigned long ul = 0x00;
    unsigned char uch = 0x00;
    pcican_device_t *pDevice = para;

    /* �ж��Ƿ���Local�ж� */
    ul = READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68);
    if (!((ul & (0x01 << 15)) && (ul & (0x01 << 8))))
    {
        return ;
    }

#if DEBUG
    logMsg("ul = 0x%08X\n", ul, 0, 0, 0, 0, 0);   /* ��Ӱ����� */
#endif

    /* �ж��Ƿ���CAN�ж� */
    uch = READ_REGISTER_UCHAR(pDevice->ulBase2 + FPGA_CAN_INT_STATE) & INT_MASK;
    if (uch == 0x00)
    {
        return ;
    }

    /* �����ж� */
    WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, ul & ~(0x01 << 8));

    /* �����ź���  */
    if (pDevice->sem != NULL)
    {
        semGive(pDevice->sem);
    }

    return ;
}

/********************************************************************
��������:   tPciCan

��������:   �жϺ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   Ϊ�˷�ֹ�жϷ����������ʱ��������԰忨�����ݲ������ں���
            ������ʵ�֡�

�޸ļ�¼:   2014-06-25  ������  ����
********************************************************************/
int tPciCan(void *para)
{
    int i = 0;
    unsigned char uch;
    pcican_device_t *pDevice = para;
    int states[MAX_CAN_NUM];
    pcican_sja1000_t *pCan = NULL;

    for (;;)
    {
        memset(states, 0x00, sizeof(states));

        if (semTake(pDevice->sem, WAIT_FOREVER) == -1)
        {
            break;
        }

        for(;;)
        {
            uch = READ_REGISTER_UCHAR(pDevice->ulBase2 + FPGA_CAN_INT_STATE) & INT_MASK;
            if (uch == 0x00)
            {
                break;
            }

            for (i = 0; i < MAX_CAN_NUM; i++)
            {
                if (uch & (0x01 << i))
                {
                    states[i] = DrainFifo(i);
                }
            }
        } /* end for */

        /* �ָ��ж� */
        WRITE_REGISTER_ULONG(pDevice->ulBase0 + 0x68, (READ_REGISTER_ULONG(pDevice->ulBase0 + 0x68) | (0x01 << 8)));

        /* ����Ӧ�ò��¼� */
        for (i = 0; i < MAX_CAN_NUM; i++)
        {
            pCan = &g_sja1000s[i];
            if (pCan->sem2 != NULL && states[i])
            {
                semGive(pCan->sem2);
            }
        }
    }

    return 0;
}

/********************************************************************
��������:   tPciCan2

��������:   ���ݷ�������

��������        ����            ����/���           ����
msg             MSG_Q_ID        input               ����ʹ�õ���Ϣ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ʹ�����������ݣ����Է�ֹ���ַ������ȼ��������⡣

�޸ļ�¼:   2014-08-19  ���ı  ����
********************************************************************/
int tPciCan2(MSG_Q_ID msg)
{
    int i = 0;
    pcican_sja1000_t *pCan = NULL;
    unsigned long base = 0;
    sja1000_frame_t frame;

    for (;;)
    {
        /* ʹ����Ϣ���� */
        if (msgQReceive(msg, (char *)&pCan, sizeof(pCan), WAIT_FOREVER) == -1)
        {
            break;
        }
        base = pCan->base;

        for (;;)
        {
            if (rngIsEmpty(pCan->ring2))
            {
                break;
            }

            rngBufGet(pCan->ring2, (char *)&frame, sizeof(sja1000_frame_t));

            /* �򻺳���д������ */
            WRITE_REGISTER_UCHAR(base + CAN_TRAN_FIFO_OFFSET, frame.header);

            for(i = 0; i < 12; i++)
            {
                WRITE_REGISTER_UCHAR(base + CAN_TRAN_FIFO_OFFSET + 1 + i, frame.buffer[i]);
            }

            /* �������� ʹ�ó������� */
            WRITE_REGISTER_UCHAR(base + CAN_CTRL_REG, 0x01);

            /* �жϻ��������� ��ѯ�ķ���
            while((READ_REGISTER_UCHAR(pCan->base + CAN_STATE_REG) & 0x04) == 0x00);*/

            /* �ȴ����������� �жϵķ��� */
            semTake(pCan->sem4, WAIT_FOREVER);
        }

        /* ʹ�ܷ��� */
        semGive(pCan->sem3);
    }

    return 0;
}

/********************************************************************
��������:   DrainFifo

��������:   ���հ忨����CANͨ����FIFO������

��������        ����                ����/���           ����
fd              int                 input               �豸ͨ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��Ӳ��FIFO���ݷ������FIFO��

�޸ļ�¼:   2013-07-22  ���ı  ����
********************************************************************/
int DrainFifo(int fd)
{
    int ret = 0;
    int i = 0;
    unsigned long base;
    unsigned char buffer[13];
    pcican_sja1000_t *pCan = &g_sja1000s[fd];
    unsigned char uch;
    unsigned char uch2;

    base = pCan->base;

    /* ��ȡ�ж�״̬ */
    uch = READ_REGISTER_UCHAR(base + CAN_IRQ_REG);
    if (uch & 0x80) /* ���ߴ��� */
    {
        /* ��λоƬ */
        uch2 = READ_REGISTER_UCHAR(base + CAN_MODE_REG);
        WRITE_REGISTER_UCHAR(base + CAN_MODE_REG, uch2 | 0x01);
        WRITE_REGISTER_UCHAR(base + CAN_MODE_REG, uch2 & 0xfe);

        /* �������ʧ���������� */
        semGive(pCan->sem4);
        semGive(pCan->sem3);

        logMsg("fd = %d bus off reset!\n", fd, 2, 3, 4, 5, 6);

        ret = 0;
    }

    if (uch & 0x02) /* ������� */
    {
        semGive(pCan->sem4);

        ret = 0;
    }

    if(uch & 0x01)
    {
        /* ��ȡ����ƴװ��һ��֡��ʽ */
        for(i = 0; i < 13; i++)
        {
            buffer[i] = READ_REGISTER_UCHAR(base + CAN_RECV_FIFO_OFFSET + i);
        }

#if DEBUG
        logMsg("channel %d number = %d - %02X \n",
               fd, i, buffer[0], 0, 0, 0);

        logMsg("%02X %02X %02X %02X %02X %02X\n",
               buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6]);

        logMsg("%02X %02X %02X %02X %02X %02X\n",
               buffer[7], buffer[8], buffer[9], buffer[10], buffer[11], buffer[12]);
#endif

        if (rngIsFull(pCan->ring))
        {
            logMsg("channel %d 's soft fifo is full. Now flush.\n", fd, 0, 0, 0, 0, 0);
            rngFlush(pCan->ring);
        }

        /* �������FIFO */
        ret = rngBufPut(pCan->ring, (char *)buffer, sizeof(buffer));

        /* �ͷ�SJA1000���ջ��� */
        WRITE_REGISTER_UCHAR(base + CAN_CTRL_REG, 0x04);
    }

    return ret;
}

/********************************************************************
��������:   InitSja

��������:   ��ʼ��SJA1000оƬ

��������        ����                ����/���           ����
*pCan           pcican_sja1000_t    input               �豸�ṹ��
pConfig         sja1000_config_t*   input               ������Ϣ�ṹ��

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   canоƬ��ʼ��������ͨ��ioctl_pcican����

�޸ļ�¼:   2014-06-25  ������  ����
            2015-11-25  ���ı  ����    ���Ӳ���
********************************************************************/
int InitSja(pcican_sja1000_t *pCan, sja1000_config_t *pConfig)
{
    int ret = 0;
    unsigned long base;

    /* ��֤���ʻ��� */
    semTake(pCan->mutex, WAIT_FOREVER);

    /* ��ȡ����ַ */
    base = pCan->base;

    /* ��ʼ����resetģʽ���� */
    WRITE_REGISTER_UCHAR(base + CAN_MODE_REG, 0x01);

    if ((READ_REGISTER_UCHAR(base + CAN_MODE_REG) & 0x01) == 0x00)
    {
        return -1;
    }

    WRITE_REGISTER_UCHAR(base + 31, pConfig->uchCDR);    /* 0xc4 set clock divider PELICAN MODE */
    WRITE_REGISTER_UCHAR(base + 8, pConfig->uchOCR);     /* 0xda set output control */

    /* ���ò����� */
    WRITE_REGISTER_UCHAR(base + 6, pConfig->uchBTR0);
    WRITE_REGISTER_UCHAR(base + 7, pConfig->uchBTR1);

    /* ���ô������� */
    WRITE_REGISTER_UCHAR(base + 13, pConfig->uchEWLR);

    /*������������*/
    WRITE_REGISTER_UCHAR(base + 14, 0);
    WRITE_REGISTER_UCHAR(base + 15, 0);

    /*����code �� mask ����������չ��can��resetģʽ�µ�����ֵ����operatģʽ����Ч*/
    WRITE_REGISTER_UCHAR(base + 16, pConfig->uchACR[0]);
    WRITE_REGISTER_UCHAR(base + 17, pConfig->uchACR[1]);
    WRITE_REGISTER_UCHAR(base + 18, pConfig->uchACR[2]);
    WRITE_REGISTER_UCHAR(base + 19, pConfig->uchACR[3]);
    WRITE_REGISTER_UCHAR(base + 20, pConfig->uchAMR[0]);
    WRITE_REGISTER_UCHAR(base + 21, pConfig->uchAMR[1]);
    WRITE_REGISTER_UCHAR(base + 22, pConfig->uchAMR[2]);
    WRITE_REGISTER_UCHAR(base + 23, pConfig->uchAMR[3]);

    /* ʹ��������ж� */
    WRITE_REGISTER_UCHAR(base + 4, pConfig->uchIER);

    /* ��������ģʽ */
    WRITE_REGISTER_UCHAR(base + 0, pConfig->uchMOD & 0xfe);

    if ((READ_REGISTER_UCHAR(base + 0) & 0x01) == 0x01)
    {
        ret = -2;
    }

    /* �ͷŻ��� */
    semGive(pCan->mutex);

    return ret;
}

/********************************************************************
��������:   ShowPciCan

��������:   ��ʾ������Ϣ

��������        ����            ����/���           ����
index           int             input               �豸������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ������ʾ������ǰ�Ĵ���ֵ������ʱʹ�á�

�޸ļ�¼:   2014-06-26  ������  ����
********************************************************************/
int ShowPciCan(int index)
{
    int i = 0;
    unsigned long base = 0;
    pcican_device_t *pDevice = NULL;
    pcican_sja1000_t *pCan = NULL;

    if (index >= MAX_DEVICE_NUM)
    {
        return -1;
    }

    /* ȷ���豸��Ч */
    pDevice = &g_devices[index];

    printf("PCICAN Device information: index = %d\n", index);

    printf("ulBase0 = 0x%08X, ulBase2 = 0x%08X, ulSize = 0x%08X\n", pDevice->ulBase0, pDevice->ulBase2, pDevice->ulSize);

    printf("irq = %d, version = %s\n", pDevice->irq, GetPciCan(index));

    /* ��ȡ2��ͨ�����ж�״̬��FIFO״̬ */
    for (i = 0; i < MAX_CAN_NUM; i++)
    {
        pCan = &g_sja1000s[i];
        base = pCan->base;

        WRITE_REGISTER_UCHAR(base + 0, 0x00);

        printf("base = 0x%08X, mod = 0x%02X, sr = 0x%02X, ir = 0x%02X, ier = 0x%02X\n", base,
               READ_REGISTER_UCHAR(base + 0) & 0x1F, READ_REGISTER_UCHAR(base + 2), READ_REGISTER_UCHAR(base + 3), READ_REGISTER_UCHAR(base + 4));
    }

    return 0;
}

/********************************************************************
��������:   GetPciCan

��������:   ��ȡ�����FPGA�汾��

��������        ����                ����/���           ����
index           int                 input               �豸������

����ֵ  :   �����FPGA�汾��Ϣ�ַ�����

����˵��:   Ϊ�����ָ��������FPGA�汾�����Ӱ汾��Ϣ������

�޸ļ�¼:   2016-06-17  ���ı  ����
********************************************************************/
char *GetPciCan(int index)
{
    pcican_device_t *pDevice = NULL;

    /* ��ֹ�������� ��ȡ�豸�ṹ��ָ�� */
    index %= MAX_DEVICE_NUM;
    pDevice = &g_devices[index];

    /* �ж��Ƿ��Ѿ�ӳ���ַ */
    if(pDevice->ulBase2 == 0)
    {
        return 0;
    }

    sprintf(s_versions, "CD6020 VxWorks 6.8.3 SMP G0044V12 PLX9056 FPGA = 0x%02X", READ_REGISTER_UCHAR(pDevice->ulBase0 + 0x32F));

    return s_versions;
}
