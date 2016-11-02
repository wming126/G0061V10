/********************************************************************
�ļ�����:   ComModule.h

�ļ�����:   ���ڹ���ģ��Դ�ļ�

�ļ�˵��:   �ù���ģ����ɴ��ڿ����ݶ�ȡ��Ȼ��������ݲ���װΪComQmsg_t
            �ṹ��ͨ��vxworks����Ϣ���Ʒ��͸��ļ�����ģ�顣��ģ��Э�����
            ������Ҫ��IoCntModuleģ���е��ã���ʱģʽ�£���

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-14  V1.0    ��  ��  ����
            2016-08-14  V1.1    ������  �޸� ���ƴ���Э�����ʹ�佡׳
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
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "ComModule.h"
#include "tickLib.h"
#include "rngLib.h"

/* �궨�� */
#define COM_MODULE_DEBUG    0

#if (COM_FRAME_ANALYZE_MODE == 0)
static int s_ComTid = 0;
#endif

MSG_Q_ID g_ComMsgID = NULL;
static int s_ComFd = 0;

/* �������� ���ش���1-8 */
char *s_ComName[] =
{
    "/tyCo/0", "/tyCo/1", "/tyCo/2", "/tyCo/3"
};


/* �ֲ��������� */
static int InitCom(int comNum, int BaudRate);
BOOL RecvAnalyzeComData(int fd);
#if (COM_FRAME_ANALYZE_MODE == 0)
static int tComRecv(int fd);
#endif

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
int InitCom(int comNum, int BaudRate)
{
    int ret = 0;
    int fd = 0;

    fd = open(s_ComName[comNum % 8], O_RDWR, 0);

    if(fd == ERROR)
    {
        printf("%s open faild!\n", s_ComName[comNum % 8]);
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
��������:   RemoveComModule

��������:   �Ƴ����ڹ���ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ɾ�����ڹ���ģ�鴴�����������Ϣ

�޸ļ�¼:  2016-07-14  ��  ��    ����
********************************************************************/
int RemoveComModule(void)
{
#if (COM_FRAME_ANALYZE_MODE == 0)
    if(s_ComTid > 0)
    {
        taskDelete(s_ComTid);
    }
#endif

    if(g_ComMsgID != NULL)
    {
        msgQDelete(g_ComMsgID);
    }

        if(s_ComFd > 0)
    {
        close(s_ComFd);
    }

    return 0;
}

/********************************************************************
��������:   CreatComModule

��������:   ��ʼ��Com����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʼ��Com����ģ�飬������AppEntry�ļ���AppEntry�������á�

�޸ļ�¼:   2016-07-14  ��  ��    ����
********************************************************************/
int CreatComModule(void)
{
    /* ��ʼ������*/
    s_ComFd = InitCom(TYCO_COM0, COM_BAUD_RATE);
    if(s_ComFd < 0)
    {
        goto Exit;
    }

#if (COM_FRAME_ANALYZE_MODE == 0)
    /* �������ڽ������� */
    s_ComTid = taskSpawn("tComRecv", COM_TASK_PRIORITY, 0, COM_MODULE_STACK_SIZE,
                         (FUNCPTR)tComRecv, s_ComFd, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_ComTid == ERROR)
    {
        printf("tComRecv creat faild!\n");
        goto Exit;
    }
#endif

    /* ��������ģ��ʹ�õ���Ϣ */
    g_ComMsgID = msgQCreate(COM_MAX_QMSG, sizeof(ComQmsg_t), MSG_Q_FIFO);
    if(g_ComMsgID == NULL)
    {
        goto Exit;
    }

    return 0;   /* �ɹ�����0 */

Exit:
    RemoveComModule();
    return ERROR;
}

/********************************************************************
��������:   ReadComEx

��������:   ���ڶ�ȡ��ʱ���غ���

��������        ����            ����/���           ����
fd              int             input               �����ļ�������
buffer          char*           input               ��ȡ������ָ��
maxbytes        size_t          input               ��ȡ����ֽ���
pTimeOut        struct timeval* input               ��ʱ��Ϣ�ṹ��

����ֵ  :   -1:����ʧ�� 0:��ʱ 1-maxbytes:���ص�����

����˵��:   ʹ��selectΪread������ӳ�ʱ�������ıReadComEx������������ֲ

�޸ļ�¼:   2016-08-12  ������ �޸�  ʹ��selectΪread������ӳ�ʱ
********************************************************************/
int ReadComEx(int fd, char *buffer, size_t maxbytes, struct timeval *pTimeOut)
{
    int ret = 0;
    fd_set fdset;

    /* �����ļ����������� */
    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);

    /* ʹ��select�����жϴ���״̬ */
    ret = select(fd + 1, &fdset, NULL, NULL, pTimeOut);
    if (ret <= 0)
        return ret;
    /* �жϵ�ǰ�����Ƿ������ݿɶ� */
    if (FD_ISSET(fd, &fdset))
    {
        ret = read(fd, buffer, maxbytes);
        return ret;
    }

    return -1;
}

/********************************************************************
��������:   CheckComSum

��������:   ����У���

��������        ����            ����/���           ����
pBuffer         const char *    input               ��Ҫ����У��͵�����
size            unsigned int    input               ����У������ݸ���

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����8bitУ�飬�ú�����ipmb������ֲ������У��ͻ�Ҫ�Ϳͻ�
            ʹ�÷�ʽһ�¡�

�޸ļ�¼:   2016-07-14  ��  ��    ����
            2016-08-14  ������    �޸�  ����û�Э���޸�У��ͳ���
********************************************************************/
unsigned char CheckComSum(const char *pBuffer, unsigned int size)
{
    int i = 0;
    unsigned int sum = 0;

    for(i = 0; i < size; i++)
    {
        sum += *(pBuffer + i);
    }

    return (char)sum;
}


#if (COM_FRAME_ANALYZE_MODE == 1)
/********************************************************************
��������:   AnalyzeComFrame

��������:   ������֡�е����ݲ�������Ϣ

��������        ����            ����/���           ����
buffer          char *          input               BUFFER
ComQmsg_t *     msg             output              ������Ϣ�ṹ

����ֵ  :   0:�ɹ� ��0:ʧ��(-2:У��ʹ���-1��δ�ҵ�һ��֡)

����˵��:   ������֡�е����ݲ�������Ϣ����ֲע�⴦������С������
            unsigned int num    ���ݰ�����
            unsigned int ax     X����������
            unsigned int ay     y����������
            unsigned int az     z����������
            unsigned int wx     x�ӱ�������
            unsigned int wy     y�ӱ�����
            unsigned int wz     z�ӱ�����
            unsigned short temp �¶�

�޸ļ�¼:   2016-07-14  ��  ��    ����
            2016-08-12  ������    �޸�  �����������յĴ���֡
            2016-10-22  ��  ��    �޸�  �ͻ�Э���޸�����mems��������
********************************************************************/
static int AnalyzeComFrame(unsigned char *buffer, unsigned int buffersize, ComQmsg_t *msg)
{
    unsigned char *pHeader = NULL;
    unsigned int header = 0;
    unsigned char checkSum = 0;
    int ret = -1;

#if 0
    printf("\n--------------AnalyzeComFrame-----------------\n");
    printf("AnalyzeComFrame run \n");
    printf("\n----------------------------------------------\n");
#endif

    /* ��ֲע�⴦������С������ */
    pHeader = buffer;
    while(buffersize - (pHeader - buffer) >= COM_MAX_FRAME_SIZE)
    {
        header = *((unsigned int *) pHeader);

        /* �ж�֡ͷ֡֡β */
        if(header == 0x55555555)
        {
            /* ����У��� */
            checkSum = CheckComSum((const char *)pHeader, (COM_MAX_FRAME_SIZE - 1));

            if(checkSum != pHeader[COM_MAX_FRAME_SIZE - 1])
            {
                /* ��У����� */
                msg->num = -1;
                msg->fog_gx = -1;
                msg->fog_gy = -1;
                msg->fog_gz = -1;
                
                msg->mems_gx = -1;
                msg->mems_gy = -1;
                msg->mems_gz = -1;
                
                msg->ax = -1;
                msg->ay = -1;
                msg->az = -1;

                msg->temp = -1;
                ret = -2;

                pHeader++;
            }
            else
            {
                /* �������ݽ������ͻ�Э��,Ŀǰֻ�Ǽ򵥵ĸ�ֵ */
                msg->num = *(int *)(pHeader + 4);
                msg->fog_gx =  *(int *)(pHeader + 8);
                msg->fog_gy = *(int *)(pHeader + 12);
                msg->fog_gz = *(int *)(pHeader + 16);
                
                msg->mems_gx = *(int *)(pHeader + 20);
                msg->mems_gy = *(int *)(pHeader + 24);
                msg->mems_gz = *(int *)(pHeader + 28);
                
                msg->ax = *(int *)(pHeader + 32);
                msg->ay = *(int *)(pHeader + 36);
                msg->az = *(int *)(pHeader + 40);
                
                msg->temp = *(short *)(pHeader + 44);
                ret = 0;
                break;
            }
        }
        else
        {
#if 0
            printf("Data header Error!\n");
#endif
            pHeader++;
        }
    }
    if (-1 == ret)
    {
        /* �Ҳ���֡ */
        msg->num = -2;
        msg->fog_gx = -2;
        msg->fog_gy = -2;
        msg->fog_gz = -2;
        
        msg->mems_gx = -2;
        msg->mems_gy = -2;
        msg->mems_gz = -2;
        
        msg->ax = -2;
        msg->ay = -2;
        msg->az = -2;

        msg->temp = -2;
    }

    return ret;
}


/********************************************************************
��������:   RecvCom

��������:   ��ʱ���մ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʱ���մ������ݣ��ú���Ӧ����IO�жϲ���ʱ���á�Ŀǰ����Э��
            �����������ַ�ʽ�á���һ�ַ�ʽΪ��IO�жϲ���ʱͨ����ʱ��ȡ
            �������ݣ��÷�ʽ�ĺô��ǿ���ʵ���������ʱ���ͬ�����ڶ���
            ��ʽΪ����һ������һֱ��ѯ�������ݣ��÷�ʽ�ŵ����ȶ���ֲ��
            �ߡ����ַ�ʽ�������ף�ʹ�ý��ʵ�������������Ϊ��һ�ַ�ʽ
            �ĺ��ĺ�����

�޸ļ�¼:   2016-08-12  ������    ����   �����������յĴ���֡
            2016-10-22  ��  ��    �޸�  �ͻ�Э���޸�����mems��������
********************************************************************/
BOOL RecvCom(void)
{
    int ret;
    int Received = 0;
    unsigned char RxBuffer[4096] = {0};
    ComQmsg_t ComQmsg;
    struct timeval timeout;
    char time[24];
    int flag = 99;

    /* ���ó�ʱʱ�� */
    timeout.tv_sec = 0;         /* 0 ��λs */
    timeout.tv_usec =  3000;   /* ��λus */

    long starttime = tickGet();
    long lefttime = 3;

    unsigned char *pData =  RxBuffer;
    BOOL errFlag = FALSE;

#if 0
    printf("\n------------------ComRecv---------------------\n");
    printf("ComRecv func run!\n");
    printf("\n----------------------------------------------\n");
#endif

    /* ��ȡ��ǰϵͳʱ�� */
    GetTime(time, 3);
    sprintf(ComQmsg.time, "%s", time);

    taskDelay(4);

    /* ��ӡ�������� */
    do
    {
        /* read����Ϊ�����Ժ��� */
        timeout.tv_sec = 0;         /* 0 ��λs */
        timeout.tv_usec = lefttime  * 1000;
        if (pData - RxBuffer + COM_MAX_FRAME_SIZE >= sizeof(RxBuffer))
        {
#if COM_MODULE_DEBUG
            printf("ERROR: (pData - RxBuffer + COM_MAX_FRAME_SIZE >= sizeof(RxBuffer) \n");
#endif
            break;
        }

        Received = ReadComEx(s_ComFd, (char *)pData, COM_MAX_FRAME_SIZE, &timeout);

        /* ��ʱ */
        if(Received >= COM_MAX_FRAME_SIZE)
        {
            pData += Received;
            errFlag = FALSE;
#if 0
            printf("Received == COM_MAX_FRAME_SIZE\n");
#endif
            break;
        }
        else if(Received == 0)
        {
            flag = Received;
#if 0
            printf("timeout: ReadComEx \n");
#endif
            break;
        }
        else if(Received < 0)
        {
            flag = Received;
            errFlag = TRUE;
#if COM_MODULE_DEBUG
            printf("ERROR: ReadComEx \n");
#endif
            break;
        }

        pData += Received;
        lefttime = 3 - (tickGet() - starttime);
    }
    while (lefttime <= 3);

#if 0
    /* ��ӡԭʼ���� */
    printf("\n------------------ComRecv--------------------\n");
    int i;
    for(i = 0; i < (pData - RxBuffer); i++)
    {
        printf("%-#4x ", RxBuffer[i]);
        if(i % 17 == 16)
        {
            printf("\n");
        }
    }
    printf("\n----------------------------------------------\n");
#endif

    /* �������� */
    if ((pData - RxBuffer) >= COM_MAX_FRAME_SIZE)
    {
        ret = AnalyzeComFrame(RxBuffer, (pData - RxBuffer), &ComQmsg);
    }
    else
    {
        /* ����ʧ�� */
        ComQmsg.num = -3;
        ComQmsg.fog_gx = -3;
        ComQmsg.fog_gy = -3;
        ComQmsg.fog_gz = -3;
        
        ComQmsg.mems_gx = -3;
        ComQmsg.mems_gy = -3;
        ComQmsg.mems_gz = -3;
        
        ComQmsg.ax = -3;
        ComQmsg.ay = -3;
        ComQmsg.az = -3;

        ComQmsg.temp = -3;
    }

    /* ������Ϣ */
    msgQSend(g_ComMsgID, (char *)&ComQmsg, sizeof(ComQmsg_t), NO_WAIT, MSG_PRI_NORMAL);

    /* todo �洮��ԭʼ���� */

    return errFlag;
}
#endif

#if (COM_FRAME_ANALYZE_MODE == 0)
/********************************************************************
��������:   RecvAnalyzeComData

��������:   ��ѯ�������ݲ���������

��������        ����            ����/���           ����
fd              int             input               ����fd

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ѯ�������ݲ��������ݣ��ú���Ӧ�ô���һ������ѭ���á�Ŀǰ
            ����Э������������ַ�ʽ�á���һ�ַ�ʽΪ��IO�жϲ���ʱͨ��
            ��ʱ��ȡ�������ݣ��÷�ʽ�ĺô��ǿ���ʵ���������ʱ���ͬ����
            �ڶ��ַ�ʽΪ����һ������һֱ��ѯ�������ݣ��÷�ʽ�ŵ����ȶ�
            ��ֲ�Ըߡ����ַ�ʽ�������ף�ʹ�ý��ʵ�������������Ϊ�ڶ�
            �ַ�ʽ�ĺ��ĺ�����

�޸ļ�¼:   2016-08-11  ��  ��    ����
            2016-08-12  ������    �޸�
            2016-10-22  ��  ��    �޸�  �ͻ�Э���޸�����mems��������
********************************************************************/
BOOL RecvAnalyzeComData(int fd)
{
    int i = 0;
    int ret = 0;
    int Received = 0;
    unsigned char RxBuffer[COM_MAX_FRAME_SIZE * 10] = {0}; /* ��ֹԽ������10֡��С */
    unsigned char *pBuffer = RxBuffer;

    int datalen = 0;
    char time[24] = {'\0'};
    char length = 0;

    unsigned char *pHeader = NULL;
    unsigned int header = 0;
    unsigned char checkSum = 0;

    ComQmsg_t ComQmsg;
    struct timeval timeout;

    /* ���ó�ʱʱ�� */
    timeout.tv_sec = 0;         /* 0 ��λs */
    timeout.tv_usec =  4000;    /* ��λus */

    while(1)
    {
        /* Received = ReadComEx(fd, (char*)pBuffer, COM_MAX_FRAME_SIZE, &timeout); */
        Received = read(fd, (char *)pBuffer, COM_MAX_FRAME_SIZE);

        if(Received > 0)
        {
            pBuffer += Received;
            datalen = pBuffer - RxBuffer;
            if (datalen > 4)
            {
                for(i = 0; i < datalen - 4; i++)
                {
                    /* datalen-4�ǿ�����֡ͷδ���������� */
                    /* ��֡ͷ */
                    if((*((int *)&RxBuffer[i]) == 0x55555555))
                        break;
                }

                if(i > 0)
                {
                    /* ��������֡ͷ������ */
                    datalen -= i;
                    memmove(RxBuffer, RxBuffer + i, datalen);
                    pBuffer = RxBuffer + datalen;
                }
            }
            /* ��ʼ����֡���� */
            if (datalen >= COM_MAX_FRAME_SIZE)
            {
                /* ��ȡ��ǰϵͳʱ�� */
                length = GetTime(time, 3);
                sprintf(ComQmsg.time, "%s", time);

                pHeader = RxBuffer;
                ret = -1;
                while(datalen - (pHeader - RxBuffer) >= COM_MAX_FRAME_SIZE)
                {
                    header = *((unsigned int *) pHeader);

                    /* �ж�֡ͷ֡֡β */
                    if(header == 0x55555555)
                    {
                        /* ����У��� */
                        checkSum = CheckComSum((const char *)pHeader, (COM_MAX_FRAME_SIZE - 1));

                        ComQmsg.num = *(int *)(pHeader + 4);
                        ComQmsg.fog_gx =  *(int *)(pHeader + 8);
                        ComQmsg.fog_gy = *(int *)(pHeader + 12);
                        ComQmsg.fog_gz = *(int *)(pHeader + 16);
                        
                        ComQmsg.mems_gx = *(int *)(pHeader + 20);
                        ComQmsg.mems_gy = *(int *)(pHeader + 24);
                        ComQmsg.mems_gz = *(int *)(pHeader + 28);
                        
                        ComQmsg.ax = *(int *)(pHeader + 32);
                        ComQmsg.ay = *(int *)(pHeader + 36);
                        ComQmsg.az = *(int *)(pHeader + 40);
                        
                        ComQmsg.temp = *(short *)(pHeader + 44);

                        if(checkSum != pHeader[COM_MAX_FRAME_SIZE - 1])
                        {
                            /* ��У����� */
                            printf("Check sum Error:(calc=%x,src =%x)!\n", checkSum, pHeader[COM_MAX_FRAME_SIZE - 1]);

                            /* ��У����� */
                            ComQmsg.num = -1;
                            ComQmsg.fog_gx = -1;
                            ComQmsg.fog_gy = -1;
                            ComQmsg.fog_gz = -1;
                            
                            ComQmsg.mems_gx = -1;
                            ComQmsg.mems_gy = -1;
                            ComQmsg.mems_gz = -1;
                            
                            ComQmsg.ax = -1;
                            ComQmsg.ay = -1;
                            ComQmsg.az = -1;

                            ComQmsg.temp = -1;

                            ret = -2;
                            /* ����У����һ��֡ͷ,�����¸��� pLeftdata_Pos */
                            pHeader++;
                        }
                        else
                        {
                            ret = 0;
                            pHeader += COM_MAX_FRAME_SIZE;
                            /* ��������һ��֡ */
                        }
                    }
                    else
                    {
                        pHeader++;
                    }
                }
                if (ret == -1)
                {
                    printf("[no frame��%d] ", datalen);

                    /* ����ʧ�� */
                    ComQmsg.num = -3;
                    ComQmsg.fog_gx = -3;
                    ComQmsg.fog_gy = -3;
                    ComQmsg.fog_gz = -3;
                    
                    ComQmsg.mems_gx = -3;
                    ComQmsg.mems_gy = -3;
                    ComQmsg.mems_gz = -3;
                    
                    ComQmsg.ax = -3;
                    ComQmsg.ay = -3;
                    ComQmsg.az = -3;

                    ComQmsg.temp = -3;
                }

                /* ��֡���Ƴ��Ѿ���������� */
                datalen -= (pHeader - RxBuffer);
                memmove(RxBuffer, pHeader, datalen);
                pBuffer = RxBuffer + datalen;
                /* ������Ϣ */
                msgQSend(g_ComMsgID, (char *)&ComQmsg, sizeof(ComQmsg_t), NO_WAIT, MSG_PRI_NORMAL);
            }
        }
    }
}

/********************************************************************
��������:   tComRecv

��������:   ���ݽ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ȴ����������¼�(���յ�����)���������ݣ����ڲ�ѯ����
            ����

�޸ļ�¼:   2016-07-14  ��  ��    ����
********************************************************************/
static int tComRecv(int fd)
{
    /* ��ӡ�������� */
    for (;;)
    {
        RecvAnalyzeComData(s_ComFd);
    }

    return 0;
}
#endif












