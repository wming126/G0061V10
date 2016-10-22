/********************************************************************
�ļ�����:   AppEntry.c

�ļ�����:   Ӧ�ò����Դ�ļ�

�ļ�˵��:   ���ļ�������ں�������ں���ΪAppEntry������̻�ʱ��usrAp
            pInit.c usrAppInit��������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-05  V1.0    ��  ��  ����
********************************************************************/
#include "stdio.h"
#include "string.h"
#include "semLib.h"
#include "taskLib.h"
#include "vmLib.h"
#include "logLib.h"
#include "sysLib.h"
#include "usrFsLib.h"
#include "stat.h"

#include "..\SRC\User\AppEntry\AppEntry.h"

/* �������� */
int AppDelete(void);

/********************************************************************
��������:   AppEntry

��������:   Ӧ�ó������

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   Ӧ�ó�����ڣ��������ø���ģ��Ĵ���������ע��ģ�鴴������
            ��˳��

�޸ļ�¼:   2016-07-05  V1.0    ��  ��  ����
********************************************************************/
int AppEntry(void)
{
    int ret = 0;

    /* ��ʼ��ϵͳʱ�� */
    InitSystemTime();

    /* ����ϵͳʱ��ƬΪ1ms */
    sysClkRateSet(1000);

    /* �����ʱ�ȴ�Ӳ���豸�����ã������޷������ļ����� */
    taskDelay(1000);

    /* ��ӡ����汾�� */
    printf("\n________________________________________________________________\n");
    printf("%s\n", VEHICLE_PRGRAM_VERSION);
    printf("usage:if you want to exit this program please input AppDelete");
    printf("\n________________________________________________________________\n");

  
    /* �ı䵱ǰ·�� */
    ret = cd(ALL_FILE_PATA);
    /* ��������ļ���ʧ����ALL_FILE_PATAΪ·�������ļ��� */
    if(ret == ERROR)
    {
        printf("Can not find this %s path!\n", ALL_FILE_PATA);
        mkdir(ALL_FILE_PATA);
        printf("Now creat %s path!\n", ALL_FILE_PATA);
        ret = cd(ALL_FILE_PATA);
        if(ret == ERROR)
        {
            printf("Creat %s path faild! Please check the hard disk!\n", ALL_FILE_PATA);
            return -1;
        }
    }
    printf("Enter directory succeed!\n");

  
    /* ����CAN����ģ�� */
    ret = CreatCanModule();
    if(ret < 0)
    {
        printf("CreatCanModule faild! Plese check the can board. Now exit the program!\n");
        goto Exit;
    }
    printf("CAN module init succeed!\n");

    /* ����ģ��Ҫ��IOCNTģ��֮ǰ��������Ϊincntģ������˴��ڵĶ����� */
    ret = CreatComModule();
    if(ret < 0)
    {
        printf("CreatComModule faild! Plese check the cpu board. Now exit the program!\n");
        goto Exit;
    }
    printf("COM module init succeed!\n");
    
    /* ����IO��ʱ������ģ�飬������ComModule֮�󴴽� */
    CreatIoCntModule();
    if(ret < 0)
    {
        printf("CreatIoCntModule faild! Plese check the IOCNT board. Now exit the program!\n\n");
        goto Exit;
    }
    printf("IOCNT module init succeed!\n");
    

    /* ����USB����ģ�� */
    ret = CreatMangeUsbModule();
    if(ret < 0)
    {
        printf("CreatMangeUsbModule faild! Plese check the usb componet. Now exit the program!\n");
        goto Exit;
    }
    printf("FILE module init succeed!\n");


    /* �����ļ�������ģ�飬��ģ��Ӧ����󱻴��� */
    ret = CreatMangeFileModule();
    if(ret < 0)
    {
        printf("CreatMangeFileModule faild! There may be some eerror\n");
        goto Exit;
    }
    printf("USB module init succeed!\n");

    return ret;
Exit:
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("AppEntry run error!");
    printf("Please check the board!");
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    AppDelete();
    return -1;
}

/********************************************************************
��������:   AppDelete

��������:   Ӧ�ó������

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   Ӧ�ó�����ڣ��������ø���ģ����Ƴ�������

�޸ļ�¼:   2016-07-05  V1.0    ��  ��  ����
********************************************************************/
int AppDelete(void)
{
	/* �������Ƴ�MangeFileModule */
	RemoveMangeFileModule();
	RemoveCanModule();
    RemoveIoCntModule();
    RemoveComModule();
    RemoveMangeUsbModule();

    return 0;
}
