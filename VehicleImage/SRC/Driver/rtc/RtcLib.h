/********************************************************************
�ļ�����:   RtcLib.c

�ļ�����:   ʵʱʱ������ͷ�ļ�

�ļ�˵��:   ʵ��vxworks��ʵʱʱ�ӵĻ�ȡ������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-05  V1.0    ��  ��  ����
            2016-08-12  V1.1    ������  �޸� �޸�ʱ���ȡ��ʽ֧�ֶ�ȡms
********************************************************************/
#ifndef _RTC_LIB_H_
#define _RTC_LIB_H_

#define RTC_INDEX           0x70
#define RTC_DATA            0x71
#define RTC_CENTURY         0x32
#define RTC_YEAR            0x09
#define RTC_MONTH           0x08
#define RTC_DAY             0x07
#define RTC_HOUR            0x04
#define RTC_MINUTE          0x02
#define RTC_SECOND          0x00

#define BCD_TO_BIN(x)       (((x) & 0x0F) + (((x) >> 4) * 10))
#define BIN_TO_BCD(x)       ((((x) / 10) << 4) + ((x) % 10))


#ifdef __cplusplus
extern "C" {
#endif

extern int InitSystemTime(void);
extern int ShowTime(void);
extern int GetTime(char *out, int fmt);

#ifdef __cplusplus
}
#endif


#endif

