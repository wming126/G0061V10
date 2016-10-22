/********************************************************************
文件名称:   MangeFile.c

文件功能:   文件管理模块源文件

文件说明:   该功能模块接收其他模块（can口、串口、IO、计数器）发来的消息
            并将发来的消息写入文件。

当前版本:   V1.0

修改记录:   2016-06-23  V1.0    王 明 创建
           2016-09-23 V1.0 	王明 修改 解决无法删除can任务bug
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

/* 宏定义 */
#define FILE_MODULE_DEBUG               0
#define FILE_MODULE_DEBUG_LOW_LEVEL     0

typedef struct MangeCan_s
{
    FILE *FileFd[MAX_CAN];          /* 文件描述符 */
    int Tid[MAX_CAN];               /* 任务ID */
} MangeCan_t;

typedef struct MangeIoCnt_s
{
    FILE *IoCntFileFd;                 /* 文件描述符 */
    int IoCntTid;                      /* 任务ID */
} MangeIoCnt_t;

typedef struct MangeCom_s
{
    FILE *ComFileFd;                /* 文件描述符 */
    int ComTid;                     /* 任务ID */
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

/* 局部函数声明 */
static int tCanQmsgReceive(int CanFd);
int RemoveMangeFileModule(void);
static int tComQmsgReceive(void);
static int tIoCtQmsgReceive(void);

/********************************************************************
函数名称:   CreatLogFile

函数功能:   创建日志文件

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   根据传入的参数创建文件

修改记录:   2016-07-06  王  明    创建
********************************************************************/
FILE *CreatLogFile(char *str, FileFormat_t format[])
{
    int i = 0;
    int ret = 0;
    FILE *FileFd;
    char time[50] = {'\0'};
    char fileName[50] = {'\0'};

    /* 参数检查 */
    if(str == NULL)
    {
        printf("Parameter error!\n");
        return NULL;
    }

    /* 获取固定字符串格式的时间  */
    GetTime(time, 4);
    sprintf(fileName, "%s%s.dat", str, time);

#if FILE_MODULE_DEBUG_LOW_LEVEL
    printf("%s\n", fileName);
#endif

    /* 打开日志文件，如果不存在创建文件  */
    FileFd = fopen((const char *)fileName, "w+");

    if(FileFd == NULL)
    {
        printf("Open %s file faild!\n", fileName);
        return NULL;
    }

    /* 文件说明 */
    ret = fprintf(FileFd, "[This file is using for record vehicle data. SENBO VERSION:V1.0 ]\n\n");

    /* 绘制数据表头  */
    ret = fprintf(FileFd, "%-16s", "Time(h_m_s_ms)");
    for(i = 0; format[i].argName != NULL; i++)
    {
        /* 定长显示 */
        /*
         * for example
         *Time                 Lnum        Rnum
         *2016/07/04 18:30:34  65535       65535
        */
        ret = fprintf(FileFd, "%-12s", format[i].argName);
    }


    /* 换行 */
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
函数名称:   CreatRollTimeFile

函数功能:   以时间滚动方式创建文件

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   以时间滚动方式创建文件，创建文件之前删除最早创建的文件

修改记录:   2016-09-19  王  明    创建
********************************************************************/
FILE *CreatRollTimeFile(char *str, FileFormat_t format[], char * dir)
{
#define SORPORT_MAX_FILE_NUM    100
#define SAVE_MAX_FILE_NUM       5    /* 滚动文件个数 */
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

    /* 参数检查 */
    if(str == NULL || format == NULL || dir == NULL)
    {
        printf("Parameter error!\n");
        return NULL;
    }

    /* 读取目录 */
    if((dirptr = opendir(dir)) == NULL)
    {
        printf("Open dir faild!\n");
        return NULL;
    }
    else
    {
        FileNum = 0;
        while((entry=readdir(dirptr))) /* 逐个读取目录下文件 */
        {
            /* 判断是不是char *str开头的字符串 */
            sprintf(fileDirTemp, "%s", entry->d_name);

            /* 判断str的前4个字符是否与fileDirTemp相同 */
            if(strncmp(str, fileDirTemp, 8) == 0)
            {
                sprintf(fileDirName[FileNum], "%s", entry->d_name);
                FileNum++;

                /* 防止数组访问越界 */
                if(FileNum >= SORPORT_MAX_FILE_NUM - 1)
                {
                    printf("The file num is too many!\n");
                    break;
                }
            }
        }

        if(FileNum < SAVE_MAX_FILE_NUM) /* 小于SAVE_MAX_FILE_NUM个文件时直接创建 */
        {
            closedir(dirptr);
            return CreatLogFile(str, format);
        }
        else if(FileNum  == SAVE_MAX_FILE_NUM) /* 等于SAVE_MAX_FILE_NUM个文件时滚动创建 */
        {
            str_length = strlen(str);

            /* todo 从文件名字符串中提取时间 */
            for(i = 0; i < SAVE_MAX_FILE_NUM; i++)
            {
                /* 拷贝年月日到temp1中eg:20160805长度为8 */
                strncpy(temp1, (char *)&fileDirName[i][str_length], 8);
                temp1[8] = '\0';

                /* 拷贝年月日到temp2中eg:080808长度为6 */
                strncpy(temp2, (char *)&fileDirName[i][str_length + 8], 6);
                temp2[6] = '\0';

                file_time[i].YearMonDay = atoi(temp1);

                file_time[i].HourMinSec = atoi(temp2);
            }

#if FILE_MODULE_DEBUG_LOW_LEVEL
            /* 打印file_time */
            for(i = 0 ; i < SAVE_MAX_FILE_NUM; i++)
            {
                printf("YearMonDay = %d HourMinSec = %d\n",  file_time[i].YearMonDay, file_time[i].HourMinSec);
            }
#endif
            /* 从file_time数组中找到最小的 */
            file_time_min.YearMonDay = file_time[0].YearMonDay;
            file_time_min.HourMinSec = file_time[0].HourMinSec;
            position = 0;
            for(i = 0; i < SAVE_MAX_FILE_NUM; i++)
            {
                /* 先判断年月日 */
                if( file_time[i].YearMonDay < file_time_min.YearMonDay )
                {
                    file_time_min.YearMonDay = file_time[i].YearMonDay;
                    file_time_min.HourMinSec = file_time[i].HourMinSec;
                    position = i;
                }
                else if(file_time[i].YearMonDay == file_time_min.YearMonDay)
                {
                    /* 当年月日相同时判断时分秒 */
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
            /* 删除最早创建的文件 */
            rm(fileDirName[position]);

            /* 关闭打开的路径 */
            closedir(dirptr);

            /* 创建文件并返回文件描述符 */
            return CreatLogFile(str, format);
        }
        else /* 大于SAVE_MAX_FILE_NUM个文件时删除目录下所有文件，防止逻辑错误 */
        {
            /* 删除所有文件否则存在逻辑上的错误无法实现文件的滚动存储 */
            /* xdelete(dir); */
            for(i = 0; i < FileNum; i++)
            {
                rm(fileDirName[i]);
            }

            /* 创建一个空目录，注意dir必须是一个绝对路径 */
            mkdir(dir);

            closedir(dirptr);
            return CreatLogFile(str, format);
        }
    }
#undef SORPORT_MAX_FILE_NUM
#undef SAVE_MAX_FILE_NUM
}

/********************************************************************
函数名称:   WriteLogFile

函数功能:   往文件里写字符串

参数名称        类型            输入/输出       含义
fp              FILE *          input           文件描述符
str             const char *    input           要写入的字符串
bLog            int             input           是否添加时间显示

返回值  :   0

函数说明:   往文件里写字符串，可以带时间头

修改记录:   2016-06-01      王明  创建
********************************************************************/
static int WriteLogFile(FILE *fp, FileFormat_t format[], char *time)
{
    int i = 0;
    int ret = -1;

    /* 在表头下面写参数  */
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
函数名称:   FileSize

函数功能:   计算当前文件大小

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   初始化Can功能模块，函数在AppEntry文件的AppEntry函数调用。
            需要注意的是该模块应该最后被创建，因为该模块使用了其他模
            块创建的资源（消息）。

修改记录:   2016-06-23  王  明    创建
********************************************************************/
unsigned long FileSize(FILE *fp)
{
#if 0
    unsigned long curpos = 0;
    unsigned long length = 0;

    /* 记录当前文件指针位置 */
    curpos = ftell(fp);

    /* 移动文件指针到尾部 */
    fseek(fp, 0L, SEEK_END);

    /* 记录文件尾到文件头位置 */
    length = ftell(fp);

    fseek(fp, curpos, SEEK_SET);

    return length;
#endif

    return ftell(fp);
}

/********************************************************************
函数名称:   CreatMangeFileModule

函数功能:   初始化Can功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   初始化Can功能模块，函数在AppEntry文件的AppEntry函数调用。
            需要注意的是该模块应该最后被创建，因为该模块使用了其他模
            块创建的资源（消息）。

修改记录:   2016-06-23  王  明    创建
            2016-09-23 王  明    修改 解决无法删除can任务bug
********************************************************************/
int CreatMangeFileModule(void)
{
    int CanFd = 0;

    /* 清零消息结构 */
    memset((char *)&s_MangeCan, 0x00, sizeof(MangeCan_t));

    /* 创建CAN文件管理需要的资源 */
    for(CanFd = 0; CanFd < MAX_CAN; CanFd++)
    {
        s_MangeCan.Tid[CanFd] = taskSpawn("tCanQmsg", CAN_QMSG_TASK_PRIORITY, 0,
                                          CAN_TASK_STACK_SIZE, tCanQmsgReceive, CanFd, 0, 0, 0, 0, 0, 0, 0, 0, 0);

        if(s_MangeCan.Tid[CanFd] == ERROR)
        {
            printf("tCanQmsg creat faild canfd = %d\n", CanFd);
            goto Exit;  /* 创建失败回收资源 */
        }
    }

    /* 清零消息结构 */
    memset((char *)&s_MangeIoCnt, 0x00, sizeof(MangeIoCnt_t));
    /* IO消息接受任务 */
    s_MangeIoCnt.IoCntTid = taskSpawn("tIoCtQmsgReceive", IO_QMSG_TASK_PRIORITY, 0,
                                      IO_TASK_STACK_SIZE, tIoCtQmsgReceive, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_MangeIoCnt.IoCntTid == ERROR)
    {
        printf("tIoQmsgReceive creat faild!\n");
        goto Exit;  /* 创建失败回收资源 */
    }

    /* 创建串口文件管理需要的资源  */
    s_MangeCom.ComTid = taskSpawn("tComQmsgReceive", COM_QMSG_TASK_PRIORITY, 0,
                                  COM_TASK_STACK_SIZE, tComQmsgReceive, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if(s_MangeCom.ComTid == ERROR)
    {
        printf("tComQmsgReceive creat faild!\n");
        goto Exit;  /* 创建失败回收资源 */
    }

    return 0;   /* 成功返回0 */

Exit:
    /* 回收创建的资源 */
    RemoveMangeFileModule();
    return ERROR;
}

/********************************************************************
函数名称:   RemoveMangeFileModule

函数功能:   移除文件管理功能模块

参数名称        类型            输入/输出           含义

返回值  :   0:成功 非0:失败

函数说明:   函数删除can功能模块创建的任务和消息

修改记录:   2016-06-23  王  明    创建
********************************************************************/
int RemoveMangeFileModule(void)
{
    int CanFd = 0;
    int ret = 0;

    /* 删除CAN管理模块创建的资源 */
    for(CanFd = 0; CanFd < MAX_CAN; CanFd++)
    {
    	/* 如果任务已经创建则删除任务 */
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

    /* 如果任务已经创建则删除任务 */
    if(s_MangeIoCnt.IoCntTid > 0)
    {
    	if(s_MangeIoCnt.IoCntFileFd != NULL)
    		fclose(s_MangeIoCnt.IoCntFileFd);
    	taskDelete(s_MangeIoCnt.IoCntTid);
    }

    /* 如果任务已经创建则删除任务 */
    if(s_MangeCom.ComTid > 0)
    {
    	if(s_MangeCom.ComFileFd != NULL)
    		fclose(s_MangeCom.ComFileFd);
    	taskDelete(s_MangeCom.ComTid);
    }

    return 0;
}

/********************************************************************
函数名称:   tCanQmsgReceive

函数功能:   can接收消息任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   该任务接收can功能模块发来的消息

修改记录:   2016-06-23  王  明    创建
********************************************************************/
static int tCanQmsgReceive(int CanFd)
{
    int nByte = 0;
    unsigned long fileSize = 0;
    CanQmsg_t CanQmsg;
    char filename[50];

    /* 定义文件表头注意最后一个必须写NULL */
    FileFormat_t format[] =
    {
        {"CBIOID", 0},
        {"CNT", 0},
        {NULL, 0},
        {NULL, 0},
    };

    for(;;)
    {
        /* 清零消息结构 */
        memset((char *)&CanQmsg, '\0', sizeof(CanQmsg_t));

        /* 接收can功能模块发来的消息 */
        nByte = msgQReceive(g_CanMsgID[CanFd], (char *)&CanQmsg, sizeof(CanQmsg_t), QMSG_TIME_OUT);

#if 0
        printf("msgQReceive!\n");
#endif

        /* 只有获取到信号量时才创建文件，有数据创建文件  */
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

        /* 判断读取到的数据大小 */
        if(nByte == sizeof(CanQmsg_t))
        {
            WriteLogFile(s_MangeCan.FileFd[CanFd], format, CanQmsg.time);
        }

        /* 查询文件大小 */
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
        else    /* 如果没有超出规定大小责继续执行程序 */
        {
            continue;
        }

    } /* end for */
}

/********************************************************************
函数名称:   tIoCtQmsgReceive

函数功能:   I/O计数器消息接收任务

参数名称        类型            输入/输出           含义


返回值  :   0:成功 非0:失败

函数说明:   该任务接收I/O计数器功能模块发来的消息

修改记录:   2016-06-23  王  明    创建
********************************************************************/
static int tIoCtQmsgReceive(void)
{
    int nByte = 0;
    unsigned long fileSize = 0;
    char filename[50];
    IoCntQmsg_t IoCntQmsg;

    /* 定义文件表头注意最后一个必须写NULL */
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
        /* 清零消息结构 */
        memset((char *)&IoCntQmsg, '\0', sizeof(IoCntQmsg_t));

        /* 接收io功能模块发来的消息 */
        nByte = msgQReceive(g_IoCntMsgID, (char *)&IoCntQmsg, sizeof(IoCntQmsg_t), QMSG_TIME_OUT);

        /* 只有获取到信号量时才创建文件，有数据创建文件  */
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

        /* 查询文件大小 */
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
        else    /* 如果没有超出规定大小责继续执行程序 */
        {
            continue;
        }
    } /* end for */

    return 0;
}

/********************************************************************
函数名称:   tComQmsgReceive

函数功能:   数据接收任务

参数名称        类型            输入/输出           含义
para            void*           input               任务参数

返回值  :   0:成功 非0:失败

函数说明:   任务等待驱动触发事件(接收到数据)，接收数据
并计数
修改记录:   2016-06-23  王  明    创建
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
        /* 清零消息结构 */
        memset((char *)&ComQmsg, '\0', sizeof(ComQmsg_t));

        /* 接收io功能模块发来的消息 */
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

        /* 定义文件表头注意最后一个必须写NULL */
        format[0].Value = ComQmsg.num;
        format[1].Value = ComQmsg.ax;
        format[2].Value = ComQmsg.ay;
        format[3].Value = ComQmsg.az;
        format[4].Value = ComQmsg.wx;
        format[5].Value = ComQmsg.wy;
        format[6].Value = ComQmsg.wz;
        format[7].Value = ComQmsg.temp;

        /* 判断读取到的数据大小 */
        WriteLogFile(s_MangeCom.ComFileFd, format, ComQmsg.time);

        /* 查询文件大小 */
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
        else    /* 如果没有超出规定大小责继续执行程序 */
        {
            continue;
        }
    } /* end for */

    return 0;
}

