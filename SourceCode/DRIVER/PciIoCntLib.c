/********************************************************************
�ļ�����:   IoCntLib.c

�ļ�����:   GAD64655�忨��������Դ�ļ�(��Դ�忨����������˼�����)

�ļ�˵��:   GAD64655�忨��������,IO������Ĵ���ӳ�䵽PCI�豸IO�ռ�
            ���Բ���Ҫvxworks����Ҫ��������ڴ�ӳ�䣬ֱ�ӷ�����IO��
            �伴�ɡ��ð忨��ԭ���߼���������IN1-IN5�ϸ�����5·������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-07  V1.0    �� �� ����
            2016-08-10  V1.1    �� �� ���  ���io�ж�֧��
********************************************************************/
#ifndef _WRS_CONFIG_SMP
#undef _WRS_CONFIG_SMP /* ˫��ģʽ */
#endif

#include "vxWorks.h"
#include "stdio.h"
#include "ioLib.h"
#include "fcntl.h"
#include "vmLib.h"
#include "arch\I86\ivI86.h"
#include "drv\pci\pciIntLib.h"
#include "drv\pci\pciConfigLib.h"
#include "taskLib.h"
#include "sysLib.h"

#include "PciIoCntLib.h"

#define DEBUG                   0
#define PCI_IO_CNT_DEBUG        0
#define PCI_CFG_BASE_ADDRESS_0  0x10
#define CNT_READ_MODE           0       /* 0:8λ�� 1:16λ�� */

#define IO_OUT_OFFSET           0x00
#define IO_IN_OFFSET            0x02
#define CNT_OFFSET              0x10

#define CNT_DATA_REG_OFFSET     0
#define CNT_CTRL_REG_OFFSET     2
#define CNT_STATE_REG_OFFSET    3       /* Ŀǰ�߼�δ����״̬ */

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

static unsigned char s_uch;     /* ��¼�ж�״̬ */

extern void logMsg( const char *fmt, ... );

/* ����ӳ���MEM��ַ */
typedef struct pciio_device_s
{
    int OpenFlag;                           /* �����򿪱�־ */
    unsigned long ulBase0;                  /* PCI ӳ�����ַBAR0 */
    unsigned long ulSize;                   /* PCIӳ���ַ��СBARO size */
    unsigned short IoInAddr[MAX_IN_PORT];   /* IO�������ַ��ӳ�䵽IO�ռ� */
    unsigned short IoOutAddr[MAX_OUT_PORT]; /* IO�������ַ��ӳ�䵽IO�ռ� */
    unsigned short CntBase[MAX_CNT_NUM];    /* ����������ַ��ӳ�䵽IO�ռ� */
    int irq;                                /* �жϺ� */
    int tid;                                /* �ж�����ID */
    int isr;                                /* �����ж�ע���־ */
    SEM_ID sem;                             /* �жϷ��������ʹ�õ��ź��� */
    SEM_ID sem2;               /* Ӧ�ó���ʹ���ź��� */
} pciiocnt_device_t;

/* ȫ���豸�ṹ */
static pciiocnt_device_t s_devices[MAX_GAD64655_NUM];

int RemovePciIoCnt(int index);
int ClosePciIoCnt(int fd);
void iPciIo(void *para);
int tPciIo(void *para);


/********************************************************************
��������:   CreatePciIoCnt

��������:   ��������

��������            ����            ����/���       ����
index               int             input           �忨����(0,1)

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ����PCI�豸����ȡ���ÿռ��ҵ�ӳ���ַ��

�޸ļ�¼:   2016-07-08  �� ��     ����
********************************************************************/
int CreatePciIoCnt(int index)
{
    int i = 0;
    int j = 0;
    int ret = 0;
    int BusNo;
    int DeviceNo;
    int FuncNo;
    unsigned int ul;
    pciiocnt_device_t *pDevice = NULL;

    /* ��ֹ�������� ��ȡ�豸�ṹ��ָ�� */
    index %= MAX_GAD64655_NUM;
    pDevice = &s_devices[index];

    /* ����PCI�豸 */
    ret = pciFindDevice(VENDOR_ID, DEVICE_ID, index, &BusNo, &DeviceNo, &FuncNo);
    if (ret == ERROR)
    {
        goto Exit;
    }

    /* ��ȡ�豸ӳ��ռ��ַ0 */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_BASE_ADDRESS_0, &ul);
    if (ret == ERROR)
    {
        ret = -2;
        goto Exit;
    }

    /* �忨ӳ�䵽IO�ռ䣬PCI�淶�涨��ַ����λ��bit0 bit1����Ч����ַΪul & 0xFC */
    pDevice->ulBase0 = (ul & 0xFFFFFFFC);


    /* ��dos��ru�ж���������Ӧ�ÿɶ�����д��λ����ӳ��ռ�Ĵ�С */
    pDevice->ulSize = 0x100;

    /* ��IO����������ַд���豸�ṹ�� */
    for(i = 0; i < MAX_GAD64655_NUM; i++)
    {
        for(j = 0; j < MAX_IN_PORT; j++)
        {
            pDevice->IoInAddr[j] = (pDevice->ulBase0 + IO_IN_OFFSET + j);
        }

        for(j = 0; j < MAX_OUT_PORT; j++)
        {
            pDevice->IoOutAddr[j] = (pDevice->ulBase0 + IO_OUT_OFFSET + j);
        }

        for(j = 0; j < MAX_CNT_NUM; j++)
        {
            pDevice->CntBase[j] = (pDevice->ulBase0 + CNT_OFFSET + j * 4);
        }
    }

    /* ��ȡ�豸�жϺ� */
    ret = pciConfigInLong(BusNo, DeviceNo, FuncNo, PCI_CFG_DEV_INT_LINE, &ul);
    if (ret == -1)
    {
        ret = -6;
        goto Exit;
    }

    pDevice->irq = ul & 0xFF;

    /* �ж��Ƿ��Ѿ�ע���ж� */
    if (pDevice->isr == 1)
    {
        return 0;
    }

    /* �����ź��� */
    pDevice->sem = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pDevice->sem == NULL)
    {
        ret = -2;
        goto Exit;
    }
    /* �������� */
    pDevice->tid = taskSpawn("tPciIo", 0, (VX_SUPERVISOR_MODE | VX_UNBREAKABLE), 8192, tPciIo, (int)pDevice, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (pDevice->tid == -1)
    {
        ret = -3;
        goto Exit;
    }

    /* ע���ж�ǰҪ������жϣ����������һ���ж� */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) | 0x01);
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) & 0xFE);
    
    /* ע���жϷ������ */
    ret = pciIntConnect(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciIo, (int)pDevice);
    if (ret == -1)
    {
        ret = -4;
        goto Exit;
    }
    pDevice->isr = 1;

    /* ʹ���ж� */
    sysIntEnablePIC(pDevice->irq);

    /* ʹ���ж�FPGA�ж� */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) | 0x01);

#if IO_INT_MODE
    /* ����ͬ���źŴ�����ʽ */
    sysOutByte(pDevice -> ulBase0 + FPGA_IO_INT_MODE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_MODE) | 0x01);
#else
    sysOutByte(pDevice -> ulBase0 + FPGA_IO_INT_MODE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_MODE) & 0xFE);
#endif

    return ret;

Exit:
    RemovePciIoCnt(index);
    return ret;
}

/********************************************************************
��������:   RemovePciIoCnt

��������:   �Ƴ��忨�豸����

��������            ����            ����/���       ����
index               int             input           �忨����(0,1)

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����һ�׶γ�ʼ��������

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int RemovePciIoCnt(int index)
{
    int ret = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ��ֹ�������� */
    index %= MAX_GAD64655_NUM;

    /* �ж��Ƿ��Ѿ�ӳ���ַ */
    pDevice = &s_devices[index];
    if (pDevice->ulBase0 == 0)
    {
        return -1;
    }

    /* �ر�FPGA�ж� */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, (sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) & 0xfe));

    if (pDevice->isr != 0)
    {
        pciIntDisconnect2(INUM_TO_IVEC(INT_NUM_GET(pDevice->irq)), iPciIo, (int)pDevice);
        pDevice->isr = 0;
    }

    if (pDevice->sem != NULL)
    {
        semDelete(pDevice->sem);
        pDevice->sem = 0;
    }

    /* ����������ݽṹ */
    memset(&s_devices[index], 0, sizeof(pciiocnt_device_t));

    return ret;
}

/********************************************************************
��������:   OpenPciIoCnt

��������:   ������

��������            ����            ����/���       ����
fd                  int             input           �豸����,���ڶ�忨֧��

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����������򿪱�־����Ϊ1

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int OpenPciIoCnt(int fd)
{
    int ret = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if (pDevice->ulBase0 == 0)
    {
        printf("Pleae creat iocnt first\n");

        ret = -1;
        goto Exit;
    }


    pDevice->sem2 = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (pDevice->sem2 == NULL)
    {
        ret = -2;
        goto Exit;
    }

    pDevice->OpenFlag = 1;

#if PCI_IO_CNT_DEBUG
    printf("pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
#endif

    return ret;

Exit:
#if PCI_IO_CNT_DEBUG
    printf("pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
#endif
    ClosePciIoCnt(fd);

    return ret;
}

/********************************************************************
��������:   ClosePciIoCnt

��������:   �ر�����

��������            ����            ����/���       ����
fd                  int             input           IO����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����������򿪱�־����Ϊ0

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int ClosePciIoCnt(int fd)
{
    int ret = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if (pDevice->ulBase0 == 0)
    {
        return -1;
    }


    if (pDevice->sem2 != 0)
    {
        semDelete(pDevice->sem2);
        pDevice->sem2 = 0;
    }


    pDevice->OpenFlag = 0;

    return ret;
}

/********************************************************************
��������:   WritePciIo

��������:   дIO��

��������            ����            ����/���       ����
fd                  int             input           �忨���������ڶ�忨֧��
port                OutPort_t       input           8bitд������
ch                  unsigned char   input           8bitд������

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����IO�Ĵ���д��ֵ��GAD64655��16·IO�����������Ϊ2��port��ÿ��
            prot 8·IO����Ӧ��ϵ����ͼ��ʾ��
            ------------------------------------------------------------------------
            |        bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0  |
            |PORT_1  OUT08   OUT07   OUT06   OUT05   OUT04   OUT03   OUT02   OUT01 |
            |PORT_2  OUT16   OUT15   OUT14   OUT13   OUT12   OUT11   OUT10   OUT09 |
            ------------------------------------------------------------------------

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int WritePciIo(int fd, OutPort_t port, unsigned char ch)
{
    unsigned short OutAddr = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!, pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
        return -1;
    }

    OutAddr = pDevice->IoOutAddr[port];

    sysOutByte(OutAddr, ch);

    return 0;
}

/********************************************************************
��������:   ReadPciIo

��������:   дIO��

��������            ����            ����/���       ����
fd                  int             input           �忨���������ڶ�忨֧��
port                InPort_t        input           GAD64655��48·IO��������Ϊ6��port��ÿ��prot 8·IO

����ֵ  :   8bit IO����ֵ

����˵��:   ������IO�Ĵ�����ȡֵ��GAD64655��48·IO��������Ϊ6��port��ÿ��
            prot 8·IO����Ӧ��ϵ����ͼ��ʾ��
            ---------------------------------------------------------------------
            |        bit7    bit6    bit5    bit4    bit3    bit2    bit1    bit0|
            |PORT_0  IN08    IN07    IN06    IN05    IN04    IN03    IN02   IN01 |
            |PORT_1  IN16    IN15    IN14    IN13    IN12    IN11    IN10   IN09 |
            |PORT_2  IN24    IN23    IN22    IN21    IN20    IN19    IN18   IN17 |
            |PORT_3  IN32    IN31    IN30    IN29    IN28    IN27    IN26   IN25 |
            |PORT_4  IN40    IN39    IN38    IN37    IN36    IN35    IN34   IN33 |
            |PORT_5  IN48    IN47    IN46    IN45    IN44    IN43    IN42   IN41 |
            ---------------------------------------------------------------------

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
unsigned char ReadPciIo(int fd, InPort_t port)
{
    unsigned short InAddr = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!, pDevice->OpenFlag = %d\n", pDevice->OpenFlag);
        return -1;
    }

    InAddr = pDevice->IoInAddr[port];

    return sysInByte(InAddr);
}

/********************************************************************
��������:   StartPciCnt

��������:   ʹ�ܼ�������ʼ����

��������            ����            ����/���       ����
fd                  int             input           �忨����(0,1)
cnt_num             int             input           ��������

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   ʹ�ܼ�������ʼ����

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int StartPciCnt(int fd, int cnt_num)
{
    unsigned char uch = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

    /* ��CNT base + 2 */
    uch = sysInByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET));

    /* CNT base + 2 Ϊ���ƼĴ���bit0Ϊ1ʱ��������ʼ����Ϊ0ʱ������ֹͣ����  */
    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch | 0x01));

    return 0;
}

/********************************************************************
��������:   StopPciCnt

��������:   ʧ�ܼ�������ֹͣ����

��������        ����            ����/���           ����
fd                  int             input           �忨����(0,1)
cnt_num             int             input           ��������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ʧ�ܼ�������ֹͣ����

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int StopPciCnt(int fd, int cnt_num)
{
    unsigned char uch = 0;

    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

    /* ��CNT base + 2 */
    uch = sysInByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET));

    /* CNT base + 2 Ϊ���ƼĴ���bit0Ϊ1ʱ��������ʼ����Ϊ0ʱ������ֹͣ����  */
    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch & 0xFE));

    return 0;
}

/********************************************************************
��������:   ReadPciCnt

��������:   ��ȡ����������ֵ

��������        ����            ����/���           ����
fd                  int             input           �忨����(0,1)
cnt_num             int             input           ��������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ȡ����������ֵ

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
unsigned short ReadPciCnt(int fd, int cnt_num)
{
    unsigned short cnt;

    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

#if (CNT_READ_MODE == 1)
    cnt = sysInWord((pDevice->CntBase[cnt_num] + CNT_DATA_REG_OFFSET));
#else

    /* �߼������ƣ���������ǰҪ�ȶ�һ�¸üĴ�������֪��ô��ģ��Դ����ż��� */
    sysInByte(pDevice->CntBase[cnt_num] + CNT_STATE_REG_OFFSET);
    
    cnt = (sysInByte((pDevice->CntBase[cnt_num] + CNT_DATA_REG_OFFSET) + 1) << 8) + (sysInByte((pDevice->CntBase[cnt_num] + CNT_DATA_REG_OFFSET)));

#endif

    return cnt;
}

/********************************************************************
��������:   ClearPciCnt

��������:   �������������ֵ

��������        ����            ����/���           ����
fd                  int             input           �忨����(0,1)
cnt_num             int             input           ��������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �������������ֵ

�޸ļ�¼:   2016-07-08  �� ��   ����
********************************************************************/
int ClearPciCnt(int fd, int cnt_num)
{
    unsigned char uch = 0;
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    if(pDevice->OpenFlag == 0)
    {
        printf("ERROR, Please open iocnt driver first!\n");
        return -1;
    }

    /* ��CNT base + 2 */
    uch = sysInByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET));

    /* CNT base + 2 Ϊ���ƼĴ���bit1Ϊ1ʱ������������������Ҫ�����bit1������ܼ�������  */
    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch | 0x02));

    sysOutByte((pDevice->CntBase[cnt_num] + CNT_CTRL_REG_OFFSET), (uch & 0xFD));

    return 0;
}

/********************************************************************
��������:   WaitPciIo

��������:   �ȴ�PCI IO�����ж�

��������            ����            ����/���       ����
index               int             input           �忨����(0,1)
timeout             int             input           �ź�����ʱ����

����ֵ  :   0����ɹ� ��0����ʧ��

����˵��:   �����ȴ��ڲ���һ�����жϴ������ź�����

�޸ļ�¼:   2016-05-03      ���ı  ����
********************************************************************/
int WaitPciIo(int fd, int timeout)
{
    pciiocnt_device_t *pDevice = NULL;

    /* ������� */
    fd = fd > MAX_GAD64655_NUM ? 0 : fd;
    pDevice = &s_devices[fd];

    /* �ȴ��ź��� */
    if (semTake(pDevice->sem2, timeout) == -1)
    {
        return -2;
    }

    return s_uch;
}

/********************************************************************
��������:   iPciIo

��������:   PCIIO�忨�жϷ������

��������        ����            ����/���           ����
*para           void            input               �忨��Ϣ���ݲ���

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   �жϷ�������ж��ж�Դ�������жϡ������жϡ�
            �����Ĳ����ں���������ʵ�֡�

�޸ļ�¼:   2016-05-03      ���ı  ����
********************************************************************/
void iPciIo(void *para)
{
    unsigned char uch = 0x00;
    pciiocnt_device_t *pDevice = para;

    /* �ж��Ƿ���IO�ж� */
    uch = sysInByte(pDevice->ulBase0 + FPGA_IO_INT_STATE);

    if((uch & 0X01) != 0X01)
    {
        return ;
    }

    /* �����ж� */
    sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, (sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) & 0xfe));

    /* �����ź���  */
    if (pDevice->sem != NULL)
    {
        semGive(pDevice->sem);
    }

    return ;
}

/********************************************************************
��������:   tPciIo

��������:   �жϺ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   Ϊ�˷�ֹ�жϷ����������ʱ��������԰忨�����ݲ������ں���
            ������ʵ�֡�

�޸ļ�¼:   2016-05-03      ���ı  ����
********************************************************************/
int tPciIo(void *para)
{
    unsigned char uch = 0x00;
    pciiocnt_device_t *pDevice = para;

    for (;;)
    {
        if (semTake(pDevice->sem, WAIT_FOREVER) == -1)
        {
            break;
        }

        for(;;)
        {
            /* ��ȡ�ж�Դ */
            uch = sysInByte(pDevice->ulBase0 + FPGA_IO_INT_STATE);

#if DEBUG
            logMsg("uch = 0x%02X\n", uch, 2, 3, 4, 5, 6);
#endif
            if ((uch & 0X01) != 0X01)
            {
                break;
            }

            s_uch = uch;

            /* ����ж� */
            sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) | 0x01);
            sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_CLEAR) & 0xFE);

            if (pDevice->sem2 != 0)
            {
                semGive(pDevice->sem2);
            }
        } /* end for */

        /* �ָ��ж� */
        sysOutByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE, sysInByte(pDevice->ulBase0 + FPGA_IO_INT_ENABLE) | 0x01);
    }

    return 0;
}
