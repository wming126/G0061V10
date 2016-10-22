/********************************************************************
�ļ�����:   AppEntry.h

�ļ�����:   Ӧ�ò����ͷ�ļ�

�ļ�˵��:   ���ļ�������ں�������ں���ΪAppEntry������̻�ʱ��usrAp
            pInit.c usrAppInit��������

��ǰ�汾:   V1.0

�޸ļ�¼:   2016-07-05  V1.0    ��  ��  ����
********************************************************************/
#ifndef _APP_ENTRY_H_
#define _APP_ENTRY_H_

#include "..\SRC\Driver\rtc\RtcLib.h"
#include "..\SRC\User\CanModule\CanModule.h"
#include "..\SRC\User\ManageFile\MangeFile.h"
#include "..\SRC\User\IoCtModule\IoCntModule.h"
#include "..\SRC\User\MangeUsb\MangeUsb.h"

#define VEHICLE_PRGRAM_VERSION      "Vehicle data collection V1.0"

#ifdef __cplusplus
extern "C" {
#endif

extern int AppEntry(void);
extern int AppDelete(void);

#ifdef __cplusplus
}
#endif


#endif
