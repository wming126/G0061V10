/********************************************************************
�ļ�����:   RtcLib.c

�ļ�����:   ʵʱʱ������Դ����

�ļ�˵��:   ʵ��vxworks��ʵʱʱ�ӵĻ�ȡ������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-05  V1.0    ��  ��  ����
            2016-08-12  V1.1    ������  �޸� �޸�ʱ���ȡ��ʽ֧�ֶ�ȡms
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
��������:   GetTime

��������:   �ú�������X86�»�ȡϵͳʱ��

��������        ����            ����/���       ����
out             char *          output          ���������ַ�����ʽʱ��
fmt             int             input           ����ʱ��ĸ�ʽ

����ֵ  :   0

����˵��:   �ú�������X86�»�ȡϵͳʱ��

�޸ļ�¼:   2016-06-01  ��  ��     ����
            2016-08-12  ������     �޸�   ��bios��ȡ��ʽ��Ϊϵͳ��ȡ��ʽ
********************************************************************/
int GetTime(char *out, int fmt)
{
    int nbytes = 0;

    /* ������� */
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

    /* ת������Ҫ�ĸ�ʽ */
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
��������:   PrintTime

��������:   ��ӡtimespec�ṹʱ��

��������        ����            ����/���       ����
tp              timespec *      input           timespec�ṹָ��

����ֵ  :   0

����˵��:   ��ӡtimespec�ṹʱ��

�޸ļ�¼:   2016-08-12  ������     ����
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
��������:   GetBiosTime

��������:   ��ȡBIOSʱ��

��������        ����            ����/���       ����
out             char *          output          ���������ַ�����ʽʱ��
fmt             int             input           ����ʱ��ĸ�ʽ

����ֵ  :   mktime(&ahora)

����˵��:   ��ȡBIOSʱ�䣬������time_t���͵�ʱ��

�޸ļ�¼:   2016-06-01      ����  ����
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
��������:   ShowTime

��������:   ��ӡϵͳʱ��

��������        ����            ����/���       ����
out             char *          output          ���������ַ�����ʽʱ��
fmt             int             input           ����ʱ��ĸ�ʽ

����ֵ  :   0

����˵��:   �ú�������X86�»�ȡϵͳʱ��

�޸ļ�¼:   2016-08-12  ������     ����
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
��������:   InitSystemTime

��������:   ��biosʱ���ʼ��ϵͳʱ��

��������        ����            ����/���       ����
out             char *          output          ���������ַ�����ʽʱ��
fmt             int             input           ����ʱ��ĸ�ʽ

����ֵ  :   �ɹ�����0��ʧ�ܷ���-1

����˵��:   ��biosʱ���ʼ��ϵͳʱ��

�޸ļ�¼:   2016-08-12  ������     ����
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
