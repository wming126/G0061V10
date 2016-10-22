/********************************************************************
�ļ�����:   MangeFile.c

�ļ�����:   USB�ļ�����Դ�ļ�

�ļ�˵��:   ��U�̲��뵱�忨usb��ʱ��msc�����ᷢ��һ����Ϣ���ⲿ�ֹ�Ϊ��
            ����ӡ���Ҫע����Ϣ�ĸ�ʽ����Ϊ����Ϊ10�����飬�����������⡣

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-06-23  V1.0    ��  ��    ����
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
#include "rngLib.h"
#include "semLib.h"
#include "sysLib.h"
#include "usrFsLib.h"
#include "stat.h"
#include "ioLib.h"
#include "..\SRC\User\ManageFile\MangeFile.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "..\SRC\Driver\iocnt\PciIoCntLib.h"
#include "MangeUsb.h"


/* �궨�� */
#define USB_MODULE_DEBUG               1

typedef struct MangeIoCnt_s
{
    int tid;                     /* ����ID */
    int reserve;
} MangeUsb_t;

/* ȫ�ֱ������� */
static MangeUsb_t s_MangeUsb;

/* �ⲿ�������� */
extern MSG_Q_ID g_MscHaveMountedMsgID;

/* �ֲ��������� */
int CreatUsbPath(char *usbDevsName, char *str);
int CreatMangeUsbModule(void);
int RemoveMangeFileModule(void);
static int tUsbQmsgReceive(void);
int CreatUsbPath(char *usbDevsName, char path[50]);

/********************************************************************
��������:   CreatUsbPath

��������:   ��U���д���һ����ʱ��Ϊ���Ƶ��ļ���

��������        ����            ����/���           ����
usbDevsName     char *          input               U���豸����
path[]          char            output              ���洴����·��

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   U�̲���ʱ���Ե�ǰʱ����U���д���һ���ļ��У������ڶ���
            �������ش������ļ���·����

�޸ļ�¼:   2016-07-06  �� �� ����
********************************************************************/
int CreatUsbPath(char *usbDevsName, char path[50])
{
    int ret = 0;
    char time[50] = {'\0'};
    char pathName[50] = {'\0'};

    /* ������� */
    if(path == NULL || usbDevsName == NULL)
    {
        printf("Parameter error!\n");
        return -1;
    }

    /* ��ȡ�̶��ַ�����ʽ��ʱ�� */
    GetTime(time, 4);
    sprintf(pathName, "%s/DATA%s", usbDevsName, time);

#if USB_MODULE_DEBUG
    printf("%s\n", pathName);
#endif

    ret = mkdir(pathName);
    if(ret < 0)
    {
        return ret;
        printf("mkdir run error!\n");
    }

    sprintf(path, "%s", pathName);

    return ret;
}

/********************************************************************
��������:   CreatMangeUsbModule

��������:   ��ʼ��USB����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʼ��USB����ģ��

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
int CreatMangeUsbModule(void)
{
    /* ������Ϣ�ṹ */
    memset((char *)&s_MangeUsb, 0x00, sizeof(MangeUsb_t));

    s_MangeUsb.tid = taskSpawn("tUsbQmsgReceive", USB_QMSG_TASK_PRIORITY, 0,
                               USB_TASK_STACK_SIZE, tUsbQmsgReceive, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_MangeUsb.tid == ERROR)
    {
        printf("tFlushAllModuleFile creat faild!\n");
        goto Exit;  /* ����ʧ�ܻ�����Դ */
    }

    return 0;   /* �ɹ�����0 */

Exit:
    /* ���մ�������Դ */
    RemoveMangeFileModule();
    return ERROR;
}

/********************************************************************
��������:   RemoveMangeUsbModule

��������:   �Ƴ�USB����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ɾ��USB����ģ�鴴��������

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
int RemoveMangeUsbModule(void)
{
    /* ɾ���ļ�ˢ������ */
    if(s_MangeUsb.tid > 0)
    {
        taskDelete(s_MangeUsb.tid);
    }

    return 0;
}

/********************************************************************
��������:   tUsbQmsgReceive

��������:   ���ܴ�Msc����(Mass storage)���͹�������Ϣ

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ���ܴ�Msc����(Mass storage)���͹�������Ϣ����U�̲��뵱�忨
            usb��ʱ��msc�����ᷢ��һ����Ϣ���ⲿ�ֹ���Ϊ�Լ���ӡ���Ҫ
            ע����Ϣ�ĸ�ʽ����Ϊ����Ϊ10�����飬�����������⡣

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
static int tUsbQmsgReceive(void)
{
    int i = 0;
    int nByte = 0;
    int ret = 0;

    char usbDevsName[10] = {'\0'};  /* ע�������С����Ϊ10����Ϊusb�����з��͵���Ϣ����Ϊ10 */
    char usbPath[50] = {'\0'};

    for(;;)
    {
        /* ����can����ģ�鷢������Ϣ */
        nByte = msgQReceive(g_MscHaveMountedMsgID, usbDevsName, sizeof(usbDevsName), WAIT_FOREVER);

#if USB_MODULE_DEBUG
        printf("msgQReceive ok! \n");
#endif

        CreatUsbPath(usbDevsName, usbPath);

        printf("******************************************************\n");
        printf("src:%s\n", ALL_FILE_PATA);
        printf("dest:%s\n", usbPath);
        printf("******************************************************\n");

        /* IMPORT STATUS xcopy (const char * src, const char *dest); */
        ret = xcopy(ALL_FILE_PATA, usbPath);
        if(ret == ERROR)
        {
            printf("File xcopy faild!\n");
            
            /* ���ݿ����ɹ���5s�� */
            WritePciIo(0, OutPort2, 0xff);
            taskDelay(sysClkRateGet()/2);
            WritePciIo(0, OutPort2, 0x00);
            taskDelay(sysClkRateGet()/2);
            WritePciIo(0, OutPort2, 0xff);
            taskDelay(sysClkRateGet()/2);
            WritePciIo(0, OutPort2, 0x00);
            continue;
        }

        /* ������ɺ�Ҫ��ʱһ��ʱ��ȴ�U������д�� */
        for(i = 0; i < XCOPY_DELAY_TIME; i++)
        {
            taskDelay(1000);
        }

        printf("******************************************************\n");
        printf("xcopy cmd run finish!\n");
        printf("Now you can remove your Mass stoarge!\n");
        printf("******************************************************\n");

        /* ���ݿ����ɹ���5s�� */
        WritePciIo(0, OutPort2, 0xff);
        taskDelay(sysClkRateGet() * 5);
        WritePciIo(0, OutPort2, 0x00);

    } /* end for */
}

