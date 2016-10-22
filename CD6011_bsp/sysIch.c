/* sysAta.c - ATA/IDE and ATAPI CDROM (LOCAL and PCMCIA) disk device driver */

/*
 * Copyright (c) 2001-2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,28sep05,dee  SPR#112989 - remove extraneous printf statement
01a,02jun05,dee  created for bsp specific ATA functions
 */

#include <drv/pcmcia/pccardLib.h>
#include <drv/hdisk/ataDrv.h>

void sysIchAtaInit (ATA_CTRL *pCtrl);
void sysIchAtaInit2();
int sysIchAtaWait();
void sysIchAtaGive();

STATUS ichPciIdeCtrlInit      (int ctrl);
STATUS ichInitAtaDmaEngine    (int ctrl, int drive, char *pBuf, UINT32 bufLength, int direction);
STATUS ichStartAtaDmaEngine   (int ctrl);
STATUS ichStopAtaDmaEngine    (int ctrl);
short  ichAtaDmaModeNegotiate (short rwmode);
void   ichIdeCtrlReset        (void);
STATUS ichAtaDmaModeSet       (int ctrl, int drive, short rwmode);

static SEM_ID s_IchReadySem;

/**************************************************************************
*
* sysAtaInit - initialize the ATA driver external functions
*
* This routine initializes function pointers for supporting DMA and also
* initializes the interrupt handler functions.
*
* RETURNS: NONE */
void sysIchAtaInit
(
    ATA_CTRL *pCtrl
)
{
    pCtrl->ataDmaReset = (FUNCPTR)ichIdeCtrlReset;
    pCtrl->ataDmaInit = (FUNCPTR)ichPciIdeCtrlInit;
    pCtrl->ataDmaModeNegotiate = (FUNCPTR)ichAtaDmaModeNegotiate;
    pCtrl->ataDmaModeSet = (FUNCPTR)ichAtaDmaModeSet;
    pCtrl->ataDmaSet = (FUNCPTR)ichInitAtaDmaEngine;
    pCtrl->ataDmaStart = (FUNCPTR)ichStartAtaDmaEngine;
    pCtrl->ataDmaStop = (FUNCPTR)ichStopAtaDmaEngine;

    pCtrl->ataIntConnect = (FUNCPTR)intConnect;
    pCtrl->ataIntEnable  = (FUNCPTR)sysIntEnablePIC;

    pCtrl->ataHostDmaSupportOkay = TRUE;  /* this controller supports DMA */

    return ;
}

void sysIchAtaInit2()
{
    /* 创建任务同步信号量 */
    s_IchReadySem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    return ;
}

int sysIchAtaWait()
{
    /* 等待ICH驱动发送准备好信号量 */
    if (semTake(s_IchReadySem, 5000) == -1)
    {
        return -1;
    }

    return 0;
}

void sysIchAtaGive()
{
    /* 等待ICH驱动发送准备好信号量 */
    semGive(s_IchReadySem);

    return ;
}
