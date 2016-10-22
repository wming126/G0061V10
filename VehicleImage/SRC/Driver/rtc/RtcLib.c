/********************************************************************
文件名称:   RtcLib.c

文件功能:   实时时钟驱动源程序

文件说明:   实现vxworks下实时时钟的获取与设置

当前版本:   V1.0

修改记录:   2016-07-05  V1.0    王  明  创建
            2016-08-12  V1.1    周绍兴  修改 修改时间读取方式支持读取ms
********************************************************************/
#include <time.h>
#include "stdio.h"
#include "string.h"
#include "vmLib.h"
#include "arch\I86\ivI86.h"
#include "logLib.h"
#include "sysLib.h"
#include "RtcLib.h"

#define RTC_LIB_DEBUG       0

/********************************************************************
函数名称:   GetTime

函数功能:   该函数用于X86下获取系统时间

参数名称        类型            输入/输出       含义
out             char *          output          用来保存字符串格式时间
fmt             int             input           返回时间的格式

返回值  :   0

函数说明:   该函数用于X86下获取系统时间

修改记录:   2016-06-01  王  明     创建
            2016-08-12  周绍兴     修改   将bios读取方式改为系统读取方式
********************************************************************/
int GetTime(char *out, int fmt)
{
    int nbytes = 0;

    /* 参数检查 */
    if(out == NULL)
    {
        return -1;
    }

    struct tm *time;
    time_t timer;
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    timer = tp.tv_sec;
    time = gmtime(&timer);

    /* 转换成需要的格式 */
    if (fmt == 1)
    {
        nbytes = sprintf(out, "%04d-%02d-%2d %02d:%02d:%02d %dms",
                         time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
                         time->tm_hour, time->tm_min, time->tm_sec, tp.tv_nsec / 1000000);
    }
    else if(fmt == 2)
    {
        nbytes = sprintf(out, "%02d:%02d:%02d %dms",
                         time->tm_hour, time->tm_min, time->tm_sec, tp.tv_nsec / 1000000);
    }
    else if(fmt == 3)
    {
        nbytes = sprintf(out, "%02d%02d%02d%03d",
                         time->tm_hour, time->tm_min, time->tm_sec, tp.tv_nsec / 1000000);
    }
    else if(fmt == 4)
    {
        /* nbytes = sprintf(out, "%04d%02d%02d_%02d-%02d-%02d", */
        nbytes = sprintf(out, "%04d%02d%02d%02d%02d%02d",
                         time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
                         time->tm_hour, time->tm_min, time->tm_sec);
    }

    return nbytes;
}

/********************************************************************
函数名称:   PrintTime

函数功能:   打印timespec结构时间

参数名称        类型            输入/输出       含义
tp              timespec *      input           timespec结构指针

返回值  :   0

函数说明:   打印timespec结构时间

修改记录:   2016-08-12  周绍兴     创建
********************************************************************/
int PrintTime(struct timespec *tp)
{
    struct tm *time;
    time_t timer;

    timer = tp->tv_sec;
    time = gmtime(&timer);
    printf("print time:%04d-%02d-%02d %02d:%02d:%02d  %d ns\n",
           time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
           time->tm_hour, time->tm_min, time->tm_sec, tp->tv_nsec);

    return 0;
}

/********************************************************************
函数名称:   GetBiosTime

函数功能:   获取BIOS时间

参数名称        类型            输入/输出       含义
out             char *          output          用来保存字符串格式时间
fmt             int             input           返回时间的格式

返回值  :   mktime(&ahora)

函数说明:   获取BIOS时间，并返回time_t类型的时间

修改记录:   2016-06-01      王明  创建
********************************************************************/
time_t GetBiosTime(void)
{
    struct tm ahora;
    unsigned char cHour, cMin, cSec;
    unsigned char cDay, cMonth, cYear;

    sysOutByte(RTC_INDEX, RTC_SECOND);
    cSec = sysInByte(RTC_DATA);
    ahora.tm_sec = (cSec & 0x0F) + 10 * ((cSec & 0xF0) >> 4);

    sysOutByte(RTC_INDEX, RTC_MINUTE);
    cMin = sysInByte(RTC_DATA);
    ahora.tm_min = (cMin & 0x0f) + 10 * ((cMin & 0xf0) >> 4);

    sysOutByte(RTC_INDEX, RTC_HOUR);
    cHour = sysInByte(RTC_DATA);
    ahora.tm_hour = (cHour & 0x0F) + 10 * ((cHour & 0xF0) >> 4);

    sysOutByte(RTC_INDEX, RTC_DAY);
    cDay = sysInByte(RTC_DATA);
    ahora.tm_mday = (cDay & 0x0F) + 10 * ((cDay & 0xF0) >> 4);

    sysOutByte(RTC_INDEX, RTC_MONTH);
    cMonth = sysInByte(RTC_DATA);
    ahora.tm_mon = (cMonth & 0x0F) + 10 * ((cMonth & 0xF0) >> 4) - 1;

    sysOutByte(RTC_INDEX, RTC_YEAR);
    cYear = sysInByte(RTC_DATA);
    ahora.tm_year = 100 + (cYear & 0x0F) + 10 * ((cYear & 0xF0) >> 4);

#if RTC_LIB_DEBUG
    {
        printf("\r\nBios time:%04d-%02d-%02d %02d:%02d:%02d\n",
               ahora.tm_year + 1900, ahora.tm_mon + 1, ahora.tm_mday,
               ahora.tm_hour, ahora.tm_min, ahora.tm_sec);
    }
#endif

    return   mktime(&ahora);
}

/********************************************************************
函数名称:   ShowTime

函数功能:   打印系统时间

参数名称        类型            输入/输出       含义
out             char *          output          用来保存字符串格式时间
fmt             int             input           返回时间的格式

返回值  :   0

函数说明:   该函数用于X86下获取系统时间

修改记录:   2016-08-12  周绍兴     创建
********************************************************************/
int ShowTime(void)
{
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp);
    printf("\r\nCurrent time:%d s %d ns\n", tp.tv_sec, tp.tv_nsec);

    PrintTime(&tp);

    return 0;
}

/********************************************************************
函数名称:   InitSystemTime

函数功能:   用bios时间初始化系统时间

参数名称        类型            输入/输出       含义
out             char *          output          用来保存字符串格式时间
fmt             int             input           返回时间的格式

返回值  :   成功返回0，失败返回-1

函数说明:   用bios时间初始化系统时间

修改记录:   2016-08-12  周绍兴     创建
********************************************************************/
int InitSystemTime(void)
{
    int ret = 0;
    struct timespec ts;

    ts.tv_sec = GetBiosTime();
    ts.tv_nsec = 0;

    ret = clock_settime(CLOCK_REALTIME, &ts);

    return ret;
}
