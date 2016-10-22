/* sioChanUtil.h - SIO Channel Utilities module */


/* Copyright (c) 2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,08apr05,tor  created
*/

#ifndef __INCsioChanUtil_H
#define __INCsioChanUtil_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

/* defines */

/* typedefs */

typedef struct sioChanMethod
{
    int sioChanNo;  /* channel number desired */
    void *pChan;    /* pChan for specified channel */
} SIO_CHANNEL_INFO;

/* globals */

IMPORT char sioChanGet_desc[];

/* locals */

/* forward declarations */

IMPORT int sioChannelNumberNextAssign();


#ifdef __cplusplus
}
#endif
#endif /* __INCsioChanUtil_H */
