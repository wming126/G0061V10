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
#include <drv/dma/iPIIX4Dma.h>

void sysAtaSetup (void);
void sysAtaInit (ATA_CTRL *pCtrl);


/**************************************************************************
*
* sysAtaSetup - ATA block device setup stub
*
* This routine services as stub so that the project build pulls in this file.
* RETURNS: none
* \NOMANUAL
*/
void sysAtaSetup
    (
    void
    )
    {
    _func_sysAtaInit = sysAtaInit;
    }


/**************************************************************************
*
* sysAtaInit - initialize the ATA driver external functions
*
* This routine initializes function pointers for supporting DMA and also
* initializes the interrupt handler functions.
*
* RETURNS: NONE */
void  sysAtaInit
    (
    ATA_CTRL *pCtrl
    )
    {
    pCtrl->ataDmaReset = (FUNCPTR)iPIIX4IdeCtrlReset;
    pCtrl->ataDmaInit = (FUNCPTR)iPIIX4PciIdeCtrlInit;
    pCtrl->ataDmaModeNegotiate = (FUNCPTR)iPIIX4AtaDmaModeNegotiate;
    pCtrl->ataDmaModeSet = (FUNCPTR)iPIIX4AtaDmaModeSet;
    pCtrl->ataDmaSet = (FUNCPTR)iPIIX4InitAtaDmaEngine;
    pCtrl->ataDmaStart = (FUNCPTR)iPIIX4StartAtaDmaEngine;
    pCtrl->ataDmaStop = (FUNCPTR)iPIIX4StopAtaDmaEngine;

    pCtrl->ataIntConnect = (FUNCPTR)intConnect;
    pCtrl->ataIntEnable  = (FUNCPTR)sysIntEnablePIC;

    pCtrl->ataHostDmaSupportOkay = TRUE;  /* this controller supports DMA */
    }

