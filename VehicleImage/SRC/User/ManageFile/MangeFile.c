/********************************************************************
�ļ�����:   MangeFile.c

�ļ�����:   �ļ�����ģ��Դ�ļ�

�ļ�˵��:   �ù���ģ���������ģ�飨can�ڡ����ڡ�IO������������������Ϣ
            ������������Ϣд���ļ���

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-06-23  V1.0    �� �� ����
           2016-09-23 V1.0 	���� �޸� ����޷�ɾ��can����bug
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
#include "ioLib.h"
#include "MangeFile.h"
#include "..\SRC\Driver\rtc\RtcLib.h"
#include "dirent.h"
#include "stat.h"

/* �궨�� */
#define FILE_MODULE_DEBUG               0
#define FILE_MODULE_DEBUG_LOW_LEVEL     0

typedef struct MangeCan_s
{
    FILE *FileFd[MAX_CAN];          /* �ļ������� */
    int Tid[MAX_CAN];               /* ����ID */
} MangeCan_t;

typedef struct MangeIoCnt_s
{
    FILE *IoCntFileFd;                 /* �ļ������� */
    int IoCntTid;                      /* ����ID */
} MangeIoCnt_t;

typedef struct MangeCom_s
{
    FILE *ComFileFd;                /* �ļ������� */
    int ComTid;                     /* ����ID */
} MangeCom_t;

typedef struct FileFormat_s
{
    char *argName;
    unsigned int Value;
} FileFormat_t;

typedef struct file_time_s
{
    unsigned int YearMonDay;
    unsigned int HourMinSec;
}file_time_t;

MangeCan_t s_MangeCan;
static MangeIoCnt_t s_MangeIoCnt;
static MangeCom_t s_MangeCom;

/* �ֲ��������� */
static int tCanQmsgReceive(int CanFd);
int RemoveMangeFileModule(void);
static int tComQmsgReceive(void);
static int tIoCtQmsgReceive(void);

/********************************************************************
��������:   CreatLogFile

��������:   ������־�ļ�

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ���ݴ���Ĳ��������ļ�

�޸ļ�¼:   2016-07-06  ��  ��    ����
********************************************************************/
FILE *CreatLogFile(char *str, FileFormat_t format[])
{
    int i = 0;
    int ret = 0;
    FILE *FileFd;
    char time[50] = {'\0'};
    char fileName[50] = {'\0'};

    /* ������� */
    if(str == NULL)
    {
        printf("Parameter error!\n");
        return NULL;
    }

    /* ��ȡ�̶��ַ�����ʽ��ʱ��  */
    GetTime(time, 4);
    sprintf(fileName, "%s%s.dat", str, time);

#if FILE_MODULE_DEBUG_LOW_LEVEL
    printf("%s\n", fileName);
#endif

    /* ����־�ļ�����������ڴ����ļ�  */
    FileFd = fopen((const char *)fileName, "w+");

    if(FileFd == NULL)
    {
        printf("Open %s file faild!\n", fileName);
        return NULL;
    }

    /* �ļ�˵�� */
    ret = fprintf(FileFd, "[This file is using for record vehicle data. SENBO VERSION:V1.0 ]\n\n");

    /* �������ݱ�ͷ  */
    ret = fprintf(FileFd, "%-16s", "Time(h_m_s_ms)");
    for(i = 0; format[i].argName != NULL; i++)
    {
        /* ������ʾ */
        /*
         * for example
         *Time                 Lnum        Rnum
         *2016/07/04 18:30:34  65535       65535
        */
        ret = fprintf(FileFd, "%-12s", format[i].argName);
    }


    /* ���� */
    ret = fprintf(FileFd, "\n");

    if(ret >= 0)
    {
        fflush(FileFd);
    }
    else
    {
        printf("ERROR fprintf run eeror! there may be same problems.\n");
        return FileFd;
    }

    return FileFd;
}

/********************************************************************
��������:   CreatRollTimeFile

��������:   ��ʱ�������ʽ�����ļ�

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʱ�������ʽ�����ļ��������ļ�֮ǰɾ�����紴�����ļ�

�޸ļ�¼:   2016-09-19  ��  ��    ����
********************************************************************/
FILE *CreatRollTimeFile(char *str, FileFormat_t format[], char * dir)
{
#define SORPORT_MAX_FILE_NUM    100
#define SAVE_MAX_FILE_NUM       5    /* �����ļ����� */
    int i = 0;
    DIR *dirptr = NULL;
    struct dirent *entry;
    char fileDirName[SORPORT_MAX_FILE_NUM][255];
    char fileDirTemp[255];
    file_time_t file_time[SAVE_MAX_FILE_NUM];
    file_time_t file_time_min;
    int position = 0;
    int str_length = 0;
    char temp1[255];
    char temp2[255];
    int FileNum = 0;

    /* ������� */
    if(str == NULL || format == NULL || dir == NULL)
    {
        printf("Parameter error!\n");
        return NULL;
    }

    /* ��ȡĿ¼ */
    if((dirptr = opendir(dir)) == NULL)
    {
        printf("Open dir faild!\n");
        return NULL;
    }
    else
    {
        FileNum = 0;
        while((entry=readdir(dirptr))) /* �����ȡĿ¼���ļ� */
        {
            /* �ж��ǲ���char *str��ͷ���ַ��� */
            sprintf(fileDirTemp, "%s", entry->d_name);

            /* �ж�str��ǰ4���ַ��Ƿ���fileDirTemp��ͬ */
            if(strncmp(str, fileDirTemp, 8) == 0)
            {
                sprintf(fileDirName[FileNum], "%s", entry->d_name);
                FileNum++;

                /* ��ֹ�������Խ�� */
                if(FileNum >= SORPORT_MAX_FILE_NUM - 1)
                {
                    printf("The file num is too many!\n");
                    break;
                }
            }
        }

        if(FileNum < SAVE_MAX_FILE_NUM) /* С��SAVE_MAX_FILE_NUM���ļ�ʱֱ�Ӵ��� */
        {
            closedir(dirptr);
            return CreatLogFile(str, format);
        }
        else if(FileNum  == SAVE_MAX_FILE_NUM) /* ����SAVE_MAX_FILE_NUM���ļ�ʱ�������� */
        {
            str_length = strlen(str);

            /* todo ���ļ����ַ�������ȡʱ�� */
            for(i = 0; i < SAVE_MAX_FILE_NUM; i++)
            {
                /* ���������յ�temp1��eg:20160805����Ϊ8 */
                strncpy(temp1, (char *)&fileDirName[i][str_length], 8);
                temp1[8] = '\0';

                /* ���������յ�temp2��eg:080808����Ϊ6 */
                strncpy(temp2, (char *)&fileDirName[i][str_length + 8], 6);
                temp2[6] = '\0';

                file_time[i].YearMonDay = atoi(temp1);

                file_time[i].HourMinSec = atoi(temp2);
            }

#if FILE_MODULE_DEBUG_LOW_LEVEL
            /* ��ӡfile_time */
            for(i = 0 ; i < SAVE_MAX_FILE_NUM; i++)
            {
                printf("YearMonDay = %d HourMinSec = %d\n",  file_time[i].YearMonDay, file_time[i].HourMinSec);
            }
#endif
            /* ��file_time�������ҵ���С�� */
            file_time_min.YearMonDay = file_time[0].YearMonDay;
            file_time_min.HourMinSec = file_time[0].HourMinSec;
            position = 0;
            for(i = 0; i < SAVE_MAX_FILE_NUM; i++)
            {
                /* ���ж������� */
                if( file_time[i].YearMonDay < file_time_min.YearMonDay )
                {
                    file_time_min.YearMonDay = file_time[i].YearMonDay;
                    file_time_min.HourMinSec = file_time[i].HourMinSec;
                    position = i;
                }
                else if(file_time[i].YearMonDay == file_time_min.YearMonDay)
                {
                    /* ����������ͬʱ�ж�ʱ���� */
                    if( file_time[i].HourMinSec < file_time_min.HourMinSec )
                    {
                        file_time_min.YearMonDay = file_time[i].YearMonDay;
                        file_time_min.HourMinSec = file_time[i].HourMinSec;
                        position = i;
                    }
                }
            }

#if FILE_MODULE_DEBUG_LOW_LEVEL
            printf("rm %s position = %d\n", fileDirName[position], position);
#endif
            /* ɾ�����紴�����ļ� */
            rm(fileDirName[position]);

            /* �رմ򿪵�·�� */
            closedir(dirptr);

            /* �����ļ��������ļ������� */
            return CreatLogFile(str, format);
        }
        else /* ����SAVE_MAX_FILE_NUM���ļ�ʱɾ��Ŀ¼�������ļ�����ֹ�߼����� */
        {
            /* ɾ�������ļ���������߼��ϵĴ����޷�ʵ���ļ��Ĺ����洢 */
            /* xdelete(dir); */
            for(i = 0; i < FileNum; i++)
            {
                rm(fileDirName[i]);
            }

            /* ����һ����Ŀ¼��ע��dir������һ������·�� */
            mkdir(dir);

            closedir(dirptr);
            return CreatLogFile(str, format);
        }
    }
#undef SORPORT_MAX_FILE_NUM
#undef SAVE_MAX_FILE_NUM
}

/********************************************************************
��������:   WriteLogFile

��������:   ���ļ���д�ַ���

��������        ����            ����/���       ����
fp              FILE *          input           �ļ�������
str             const char *    input           Ҫд����ַ���
bLog            int             input           �Ƿ����ʱ����ʾ

����ֵ  :   0

����˵��:   ���ļ���д�ַ��������Դ�ʱ��ͷ

�޸ļ�¼:   2016-06-01      ����  ����
********************************************************************/
static int WriteLogFile(FILE *fp, FileFormat_t format[], char *time)
{
    int i = 0;
    int ret = -1;

    /* �ڱ�ͷ����д����  */
    ret = fprintf(fp, "%-16s", time);
    for(i = 0; format[i].argName != NULL; i++)
    {
        ret = fprintf(fp, "%-12d", format[i].Value);
    }

    ret = fprintf(fp, "\n");

    if(ret >= 0)
    {
        /* fflush(fp); */
        return ret;
    }
    else
    {
        printf("ERROR fprintf run eeror! there may be same problems.\n");
        return ret;
    }
}

/********************************************************************
��������:   FileSize

��������:   ���㵱ǰ�ļ���С

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʼ��Can����ģ�飬������AppEntry�ļ���AppEntry�������á�
            ��Ҫע����Ǹ�ģ��Ӧ����󱻴�������Ϊ��ģ��ʹ��������ģ
            �鴴������Դ����Ϣ����

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
unsigned long FileSize(FILE *fp)
{
#if 0
    unsigned long curpos = 0;
    unsigned long length = 0;

    /* ��¼��ǰ�ļ�ָ��λ�� */
    curpos = ftell(fp);

    /* �ƶ��ļ�ָ�뵽β�� */
    fseek(fp, 0L, SEEK_END);

    /* ��¼�ļ�β���ļ�ͷλ�� */
    length = ftell(fp);

    fseek(fp, curpos, SEEK_SET);

    return length;
#endif

    return ftell(fp);
}

/********************************************************************
��������:   CreatMangeFileModule

��������:   ��ʼ��Can����ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ��ʼ��Can����ģ�飬������AppEntry�ļ���AppEntry�������á�
            ��Ҫע����Ǹ�ģ��Ӧ����󱻴�������Ϊ��ģ��ʹ��������ģ
            �鴴������Դ����Ϣ����

�޸ļ�¼:   2016-06-23  ��  ��    ����
            2016-09-23 ��  ��    �޸� ����޷�ɾ��can����bug
********************************************************************/
int CreatMangeFileModule(void)
{
    int CanFd = 0;

    /* ������Ϣ�ṹ */
    memset((char *)&s_MangeCan, 0x00, sizeof(MangeCan_t));

    /* ����CAN�ļ�������Ҫ����Դ */
    for(CanFd = 0; CanFd < MAX_CAN; CanFd++)
    {
        s_MangeCan.Tid[CanFd] = taskSpawn("tCanQmsg", CAN_QMSG_TASK_PRIORITY, 0,
                                          CAN_TASK_STACK_SIZE, tCanQmsgReceive, CanFd, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        if(s_MangeCan.Tid[CanFd] == ERROR)
        {
            printf("tCanQmsg creat faild canfd = %d\n", CanFd);
            goto Exit;  /* ����ʧ�ܻ�����Դ */
        }
    }

    /* ������Ϣ�ṹ */
    memset((char *)&s_MangeIoCnt, 0x00, sizeof(MangeIoCnt_t));
    /* IO��Ϣ�������� */
    s_MangeIoCnt.IoCntTid = taskSpawn("tIoCtQmsgReceive", IO_QMSG_TASK_PRIORITY, 0,
                                      IO_TASK_STACK_SIZE, tIoCtQmsgReceive, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_MangeIoCnt.IoCntTid == ERROR)
    {
        printf("tIoQmsgReceive creat faild!\n");
        goto Exit;  /* ����ʧ�ܻ�����Դ */
    }

    /* ���������ļ�������Ҫ����Դ  */
    s_MangeCom.ComTid = taskSpawn("tComQmsgReceive", COM_QMSG_TASK_PRIORITY, 0,
                                  COM_TASK_STACK_SIZE, tComQmsgReceive, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_MangeCom.ComTid == ERROR)
    {
        printf("tComQmsgReceive creat faild!\n");
        goto Exit;  /* ����ʧ�ܻ�����Դ */
    }

    return 0;   /* �ɹ�����0 */

Exit:
    /* ���մ�������Դ */
    RemoveMangeFileModule();
    return ERROR;
}

/********************************************************************
��������:   RemoveMangeFileModule

��������:   �Ƴ��ļ�������ģ��

��������        ����            ����/���           ����

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ɾ��can����ģ�鴴�����������Ϣ

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
int RemoveMangeFileModule(void)
{
    int CanFd = 0;
    int ret = 0;

    /* ɾ��CAN����ģ�鴴������Դ */
    for(CanFd = 0; CanFd < MAX_CAN; CanFd++)
    {
    	/* ��������Ѿ�������ɾ������ */
        if(s_MangeCan.Tid[CanFd] > 0)
        {
        	ret = taskDelete(s_MangeCan.Tid[CanFd]);
        	if(ret < 0)
        	{
        		printf("taskDelete(s_MangeCan.Tid[CanFd] faild!\n");
        	}
        }
        
    	if(s_MangeCan.FileFd[CanFd] != NULL)
    	{
    		fclose(s_MangeCan.FileFd[CanFd]);
    	}
    }

    /* ��������Ѿ�������ɾ������ */
    if(s_MangeIoCnt.IoCntTid > 0)
    {
    	if(s_MangeIoCnt.IoCntFileFd != NULL)
    		fclose(s_MangeIoCnt.IoCntFileFd);
    	taskDelete(s_MangeIoCnt.IoCntTid);
    }

    /* ��������Ѿ�������ɾ������ */
    if(s_MangeCom.ComTid > 0)
    {
    	if(s_MangeCom.ComFileFd != NULL)
    		fclose(s_MangeCom.ComFileFd);
    	taskDelete(s_MangeCom.ComTid);
    }

    return 0;
}

/********************************************************************
��������:   tCanQmsgReceive

��������:   can������Ϣ����

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ���������can����ģ�鷢������Ϣ

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
static int tCanQmsgReceive(int CanFd)
{
    int nByte = 0;
    unsigned long fileSize = 0;
    CanQmsg_t CanQmsg;
    char filename[50];

    /* �����ļ���ͷע�����һ������дNULL */
    FileFormat_t format[] =
    {
        {"CBIOID", 0},
        {"CNT", 0},
        {NULL, 0},
        {NULL, 0},
    };

    for(;;)
    {
        /* ������Ϣ�ṹ */
        memset((char *)&CanQmsg, '\0', sizeof(CanQmsg_t));

        /* ����can����ģ�鷢������Ϣ */
        nByte = msgQReceive(g_CanMsgID[CanFd], (char *)&CanQmsg, sizeof(CanQmsg_t), QMSG_TIME_OUT);

#if 0
        printf("msgQReceive!\n");
#endif

        /* ֻ�л�ȡ���ź���ʱ�Ŵ����ļ��������ݴ����ļ�  */
        if(s_MangeCan.FileFd[CanFd] == NULL)
        {
            sprintf(filename, "CL_CAN%d_Data", CanFd);

            /* s_MangeCan.FileFd[CanFd] = CreatLogFile((char *)filename, format); */
            s_MangeCan.FileFd[CanFd] = CreatRollTimeFile((char *)filename, format, "/ata0a/DATA");

            if(s_MangeCan.FileFd[CanFd] == NULL)
            {
                printf("Open %s file faild!\n", filename);
                return -1;
            }
        }

        format[0].Value = CanQmsg.CBIO_ID;
        format[1].Value = CanQmsg.counter;

        /* �ж϶�ȡ�������ݴ�С */
        if(nByte == sizeof(CanQmsg_t))
        {
            WriteLogFile(s_MangeCan.FileFd[CanFd], format, CanQmsg.time);
        }

        /* ��ѯ�ļ���С */
        fileSize = FileSize(s_MangeCan.FileFd[CanFd]);

        if(fileSize >= SIGAL_FILE_MAX_SIZE)
        {
            fflush(s_MangeCan.FileFd[CanFd]);
            fclose(s_MangeCan.FileFd[CanFd]);
            s_MangeCan.FileFd[CanFd] = NULL;
            /* s_MangeCan.FileFd[CanFd] = CreatLogFile((char *)filename, format); */
            s_MangeCan.FileFd[CanFd]  = CreatRollTimeFile((char *)filename, format, "/ata0a/DATA");
            if(s_MangeCan.FileFd[CanFd] == NULL)
            {
                printf("Open %s file faild!\n", filename);
                return -1;
            }
        }
        else    /* ���û�г����涨��С�����ִ�г��� */
        {
            continue;
        }

    } /* end for */
}

/********************************************************************
��������:   tIoCtQmsgReceive

��������:   I/O��������Ϣ��������

��������        ����            ����/���           ����


����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ���������I/O����������ģ�鷢������Ϣ

�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
static int tIoCtQmsgReceive(void)
{
    int nByte = 0;
    unsigned long fileSize = 0;
    char filename[50];
    IoCntQmsg_t IoCntQmsg;

    /* �����ļ���ͷע�����һ������дNULL */
    FileFormat_t format[] =
    {
        {"CNT1", 0},
        {"CNT2", 0},
        {"DELTA1", 0},
        {"DELTA2", 0},
        {"IO1", 0},
        {"IO2", 0},
        {NULL, 0},
        {NULL, 0},
    };

    for(;;)
    {
        /* ������Ϣ�ṹ */
        memset((char *)&IoCntQmsg, '\0', sizeof(IoCntQmsg_t));

        /* ����io����ģ�鷢������Ϣ */
        nByte = msgQReceive(g_IoCntMsgID, (char *)&IoCntQmsg, sizeof(IoCntQmsg_t), QMSG_TIME_OUT);

        /* ֻ�л�ȡ���ź���ʱ�Ŵ����ļ��������ݴ����ļ�  */
        if(s_MangeIoCnt.IoCntFileFd == NULL)
        {
            sprintf(filename, "CNT_Data");
            /* s_MangeIoCnt.IoCntFileFd = CreatLogFile((char *)filename, format); */
            s_MangeIoCnt.IoCntFileFd = CreatRollTimeFile((char *)filename, format, "/ata0a/DATA");
            if(s_MangeIoCnt.IoCntFileFd == NULL)
            {
                printf("Open %s file faild!\n", filename);
                return -1;
            }
        }

        format[0].Value = IoCntQmsg.cnt1;
        format[1].Value = IoCntQmsg.cnt2;
        format[2].Value = IoCntQmsg.delta1;
        format[3].Value = IoCntQmsg.delta2;
        format[4].Value = IoCntQmsg.io1;
        format[5].Value = IoCntQmsg.io2;

#if 0
        printf("IoCntQmsg.io1 = %d IoCntQmsg.io2 = %d\n", IoCntQmsg.io1, IoCntQmsg.io2);

#endif

        WriteLogFile(s_MangeIoCnt.IoCntFileFd, format, IoCntQmsg.time);

        /* ��ѯ�ļ���С */
        fileSize = FileSize(s_MangeIoCnt.IoCntFileFd);

        if(fileSize >= SIGAL_FILE_MAX_SIZE)
        {
            fflush(s_MangeIoCnt.IoCntFileFd);
            fclose(s_MangeIoCnt.IoCntFileFd);
            /* s_MangeIoCnt.IoCntFileFd = CreatLogFile((char *)filename, format); */
            s_MangeIoCnt.IoCntFileFd = CreatRollTimeFile((char *)filename, format, "/ata0a/DATA");
            if(s_MangeIoCnt.IoCntFileFd == NULL)
            {
                printf("Open %s file faild!\n", filename);
                return -1;
            }
        }
        else    /* ���û�г����涨��С�����ִ�г��� */
        {
            continue;
        }
    } /* end for */

    return 0;
}

/********************************************************************
��������:   tComQmsgReceive

��������:   ���ݽ�������

��������        ����            ����/���           ����
para            void*           input               �������

����ֵ  :   0:�ɹ� ��0:ʧ��

����˵��:   ����ȴ����������¼�(���յ�����)����������
������
�޸ļ�¼:   2016-06-23  ��  ��    ����
********************************************************************/
static int tComQmsgReceive(void)
{
    int nByte = 0;
    char filename[50];
    unsigned long fileSize = 0;
    ComQmsg_t ComQmsg;

    FileFormat_t format[] =
    {
        {"Num", 0},
        {"Wx", 0},
        {"Wy", 0},
        {"Wz", 0},
        {"Ax", 0},
        {"Ay", 0},
        {"Az", 0},
        {"T", 0},
        {NULL, 0},
        {NULL, 0},
    };

    for(;;)
    {
        /* ������Ϣ�ṹ */
        memset((char *)&ComQmsg, '\0', sizeof(ComQmsg_t));

        /* ����io����ģ�鷢������Ϣ */
        nByte = msgQReceive(g_ComMsgID, (char *)&ComQmsg, sizeof(ComQmsg_t), QMSG_TIME_OUT);

        if(s_MangeCom.ComFileFd == NULL)
        {

            sprintf(filename, "RS422_IMU_Data");
            /* s_MangeCom.ComFileFd = CreatLogFile((char *)filename, format); */
            s_MangeCom.ComFileFd = CreatRollTimeFile((char *)filename, format, "/ata0a/DATA");
            if(s_MangeCom.ComFileFd == NULL)
            {
                printf("Open %s file faild!\n", filename);
                return -1;
            }
        }

        /* �����ļ���ͷע�����һ������дNULL */
        format[0].Value = ComQmsg.num;
        format[1].Value = ComQmsg.ax;
        format[2].Value = ComQmsg.ay;
        format[3].Value = ComQmsg.az;
        format[4].Value = ComQmsg.wx;
        format[5].Value = ComQmsg.wy;
        format[6].Value = ComQmsg.wz;
        format[7].Value = ComQmsg.temp;

        /* �ж϶�ȡ�������ݴ�С */
        WriteLogFile(s_MangeCom.ComFileFd, format, ComQmsg.time);

        /* ��ѯ�ļ���С */
        fileSize = FileSize(s_MangeCom.ComFileFd);

        if(fileSize >= SIGAL_FILE_MAX_SIZE)
        {
            fflush(s_MangeCom.ComFileFd);
            fclose(s_MangeCom.ComFileFd);
            /* s_MangeCom.ComFileFd = CreatLogFile((char *)filename, format); */
            s_MangeCom.ComFileFd = CreatRollTimeFile((char *)filename, format, "/ata0a/DATA");
            if(s_MangeCom.ComFileFd == NULL)
            {
                printf("Open %s file faild!\n", filename);
                return -1;
            }
        }
        else    /* ���û�г����涨��С�����ִ�г��� */
        {
            continue;
        }
    } /* end for */

    return 0;
}

