/* usb2MscXBD.c - USB Mass Storage Class Driver XBD Filesystem Interface */

/*
 * Copyright (c) 2008-2009, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,13jul11,ghs  Add direct BIO handling for storage driver (WIND00287697)
01i,21oct09,w_x  Modifications for Kernel API references (WIND00187268)
01h,24sep09,w_x  Add READ FORMAT CAPACITIES command support (WIND00183566)
01g,27aug09,w_x  Unify log mechanism and variable naming with some compiler
                 warning removal in USB GEN2 class drivers (WIND00178936)
01f,20aug09,w_x  Unregister the xbdEventInstantiated event when unmount device
01e,14apr09,w_x  coding convention changes
01d,14apr09,w_x  make XBD service task parameter configurable
01c,27feb09,w_x  purge bio queue after rasie xbdEventRemove event
01b,19jan09,w_x  clean up for first check in
01a,29oct08,w_x  written
2016年7月5日，wming 21:34:13 添加u盘自动检测功能，通过消息发送到应用层
*/

/*
DESCRIPTION

This module is the XBD Filesystem Interface of the USB Mass Storage Class
driver based on WRS USB 2.x API.

This module presents an interface which is a superset of the vxWorks
Block Device driver model.  This driver implements external APIs which
would be expected of a standard block device driver.

INCLUDE FILES: vxWorks.h drv/xbd/xbd.h drv/xbd/bio.h
               drv/manager/device.h fsMonitor.h
               usb2/usb2Msc.h usb2MscP.h
*/

/* includes */

#include <vxWorks.h>
#include <drv/xbd/xbd.h>
#include <drv/xbd/bio.h>
#include <drv/erf/erfLib.h>
#include <drv/manager/device.h>
#include <fsMonitor.h>
#include <usb2/usb2Msc.h>
#include "usb2MscP.h"


/* defines */
#define BD_DEVCE_LENTH      10
/* Default wait time for XBD sync up semaphore */
#define USB2_MSC_XBD_SYNC_WAIT_TIME \
    OS_CONVERT_MILLISECONDS_TO_WAIT_VALUE(5000)

/* typedefs */

typedef struct usb2MscXbdLun
{
    XBD               xbd;              /* Must be fisrt to allow reflection */
    device_t          device;           /* Device structure that we are      */
    SEM_ID            xbdMutex;         /* lock for this wraper              */
    SEM_ID            ejectMutex;       /* lock for eject                    */
    SEM_ID            bioReadySem;      /* work available for service        */
    FUNCPTR           xbdRead;          /* driver read function pointer      */
    FUNCPTR           xbdWrite;         /* driver write function pointer     */
    struct bio       *pBioHead;         /* List of bios to process           */
    struct bio       *pBioTail;         /* Tail of the bio list              */
    int               xbdService;       /* Service task for this wrapper     */
    UINT8             lun;              /* lun value for this unit           */
    BOOL              xbdInstantiated;  /* USB XBD instantiation flag        */
    SEM_ID            xbdInstSyncSem;   /* used for XBD instantiation        */
    BOOL              bioBusy;          /* busy doing BIO                    */
    BOOL              unmounting;       /* If this LUN will be unmouned      */
    char             *pDrvName;         /* Name of the LUN in IOS system     */
    USB2_MSC_LUN_DEVICE *pMscLunDevice;  /* Pointer to the LUN structure     */
} USB2_MSC_XBD_LUN;

/* globals */

/* locals */

LOCAL int usb2MsxXbdIoctl
(
    XBD   *pXbd,
    int    request,
    void *someArg
);

LOCAL int usb2MscXbdStrategy
(
    XBD          *pXbd,
    struct bio   *pBio
);

LOCAL int usb2MscXbdDump
(
    XBD      *self,
    sector_t  blkno,
    void     *data,
    size_t    size
);

LOCAL struct xbd_funcs usb2MscXbdLunFuncs =
{
    usb2MsxXbdIoctl,
    usb2MscXbdStrategy,
    usb2MscXbdDump,
};

/* forward declarations */
extern BOOL usrUsb2MscXbdDirectBioEnabled();

#define INCLUDE_SEM     0

#if 0
extern SEM_ID g_MscHaveMountedSemId;
#endif

extern MSG_Q_ID g_MscHaveMountedMsgID;

/*******************************************************************************
*
* usb2MscXbdRead - read one or more blocks from the device
*
* This routine reads the specified physical sector(s) from a specified
* physical device. Typically called by file system when data is to be
* read from a particular device.
*
* RETURNS: OK on success, or ERROR if failed to read from device.
*
* ERRNO:
* \is
* \i S_ioLib_DEVICE_ERROR
* Low level I/O failed.
* \ie
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscXbdRead
(
    XBD      *pXbd,                 /* pointer to bulk device         */
    int       startBlk,             /* logical block number           */
    int       numBlks,              /* number of blocks to read       */
    char     *pBuffer               /* store for data                 */
)
{
    USB2_MSC_XBD_LUN       *pXbdLun = (USB2_MSC_XBD_LUN *)pXbd;
    USB2_MSC_LUN_DEVICE    *pMscLunDevice = pXbdLun->pMscLunDevice;
    STATUS                  status;
    UINT32                  requiredSize;
    UINT32                  actualSize;

    actualSize = requiredSize =
                     numBlks * pMscLunDevice->bytesPerSector;

    status = usb2MscScsiRead10(pMscLunDevice,
                               (UINT32)startBlk,
                               (UINT16)numBlks,
                               (UINT8 *)pBuffer,
                               &actualSize);

    /* Check if transfer succeeded */
    if (status != OK)
    {
        USB2_MSC_ERR("usb2MscScsiRead10 failed,"\
                     " actualSize %d but required %d\n",
                     actualSize, requiredSize,
                     3, 4, 5, 6);

        /* Set the errno to let the filesystem know the failure */
        errnoSet(S_ioLib_DEVICE_ERROR);

        return ERROR;
    }
    else
    {
        return OK;
    }
}

/*******************************************************************************
*
* usb2MscXbdWrite - write one or more blocks to the device
*
* This routine writes the specified physical sector(s) to a
* specified physical device. Typically called by file system when
* data is to be write to a particular device.
*
* RETURNS: OK on success, or ERROR if failed to write to device.
*
* ERRNO:
* \is
* \i S_ioLib_WRITE_PROTECTED
* Device is write protected.
*
* \i S_ioLib_DEVICE_ERROR
* Low level I/O failed.
* \ie
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscXbdWrite
(
    XBD      *pXbd,                 /* pointer to bulk device         */
    int       startBlk,             /* logical block number           */
    int       numBlks,              /* number of blocks to read       */
    char     *pBuffer               /* store for data                 */
)
{
    USB2_MSC_XBD_LUN       *pXbdLun = (USB2_MSC_XBD_LUN *)pXbd;
    USB2_MSC_LUN_DEVICE    *pMscLunDevice = pXbdLun->pMscLunDevice;
    STATUS                  status;
    UINT32                  requiredSize;
    UINT32                  actualSize;

    if (pMscLunDevice->writeProtected == TRUE)
    {
        USB2_MSC_ERR("Device write protected\n",
                     1, 2, 3, 4, 5, 6);
        errnoSet(S_ioLib_WRITE_PROTECTED);
        return ERROR;
    }

    actualSize = requiredSize =
                     numBlks * pMscLunDevice->bytesPerSector;

    status = usb2MscScsiWrite10(pMscLunDevice,
                                (UINT32)startBlk,
                                (UINT16)numBlks,
                                (UINT8 *)pBuffer,
                                &actualSize);

    /* Check if transfer succeeded */

    if (status != OK)
    {
        USB2_MSC_ERR("usb2MscScsiWrite10 failed,"\
                     " actualSize %d but required %d\n",
                     actualSize, requiredSize,
                     3, 4, 5, 6);

        /* Set the errno to let the filesystem know the failure */

        if (pMscLunDevice->writeProtected == TRUE)
        {
            USB2_MSC_ERR("Device write protected\n",
                         1, 2, 3, 4, 5, 6);
            errnoSet(S_ioLib_WRITE_PROTECTED);
        }
        else
        {
            errnoSet(S_ioLib_DEVICE_ERROR);
        }

        return ERROR;
    }
    else
    {
        return OK;
    }
}

/*******************************************************************************
*
* usb2MscXbdDelete - delete a XBD block device
*
* This routine deletes a XBD based structure, which describes a logical
* unit on a device.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscXbdDelete
(
    USB2_MSC_LUN_DEVICE    *pMscLunDevice
)
{
    USB2_MSC_XBD_LUN       *pXbdLun;

    pXbdLun = (USB2_MSC_XBD_LUN *)pMscLunDevice->pFileSystemHook;

    if (!pXbdLun)
    {
        return ERROR;
    }

    if (pXbdLun->xbdMutex)
    {
        /* Mutex should be taken before destroy it */

        semTake(pXbdLun->xbdMutex, WAIT_FOREVER);

        /* Destroy the already allocated resources */

        semDelete(pXbdLun->xbdMutex);

        /* Set the mutex to NULL */

        pXbdLun->xbdMutex = NULL;
    }

    if (pXbdLun->ejectMutex)
    {
        /* Mutex should be taken before destroy it */

        semTake(pXbdLun->ejectMutex, WAIT_FOREVER);

        /* Destroy the already allocated resources */

        semDelete(pXbdLun->ejectMutex);

        /* Set the mutex to NULL */

        pXbdLun->ejectMutex = NULL;
    }

    if (pXbdLun->bioReadySem)
    {
        /* Destroy the already allocated resources */

        semDelete(pXbdLun->bioReadySem);

        /* Set the semaphore to NULL */

        pXbdLun->bioReadySem = NULL;
    }

    if (pXbdLun->xbdInstSyncSem)
    {
        /* Destroy the already allocated resources */

        semDelete(pXbdLun->xbdInstSyncSem);

        /* Set the semaphore to NULL */

        pXbdLun->xbdInstSyncSem = NULL;
    }

    /* Free the filesystem hook */

    OSS_FREE(pXbdLun);

    /* Set the hook as NULL */

    pMscLunDevice->pFileSystemHook = NULL;

    return OK;
}

/*******************************************************************************
*
* usb2MscXbdCreate - create a XBD block device
*
* This routine initializes a XBD based structure, which describes a logical
* unit on a device.  A logical unit is an array of contiguously addressed
* blocks; it can be completely described by the number of blocks and the
* address of the first block in the logical unit.
*
* RETURNS: OK, or ERROR if tehre is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscXbdCreate
(
    USB2_MSC_LUN_DEVICE    *pMscLunDevice
)
{
    STATUS                  status;
    USB2_MSC_XBD_LUN       *pXbdLun;

    /* Create pointer shortcuts */

    pXbdLun = OSS_CALLOC(sizeof(USB2_MSC_XBD_LUN));

    if (!pXbdLun)
    {
        return ERROR;
    }

    /* Hook the file system data */

    pMscLunDevice->pFileSystemHook = pXbdLun;

    /* Hook the LUN device pointer */

    pXbdLun->pMscLunDevice = pMscLunDevice;

    pXbdLun->xbdMutex = semMCreate (SEM_Q_PRIORITY |
                                    SEM_INVERSION_SAFE | SEM_DELETE_SAFE);

    if (pXbdLun->xbdMutex == NULL)
    {
        USB2_MSC_ERR ("Failed to create xbdMutex for lun %d, give up.\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);

        usb2MscXbdDelete(pMscLunDevice);

        return ERROR;
    }

    /* Create the mutex used for eject and device removal sync up */

    pXbdLun->ejectMutex = semMCreate (SEM_Q_PRIORITY |
                                      SEM_INVERSION_SAFE | SEM_DELETE_SAFE);

    /* Check if it is created successfully */

    if (pXbdLun->ejectMutex == NULL)
    {
        USB2_MSC_ERR ("Failed to create ejectMutex for lun %d, give up.\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);
        usb2MscXbdDelete(pMscLunDevice);
        return ERROR;
    }

    pXbdLun->bioReadySem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

    if (pXbdLun->bioReadySem == NULL)
    {
        USB2_MSC_ERR ("Failed to create bioReady for lun %d, give up.\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);
        usb2MscXbdDelete(pMscLunDevice);
        return ERROR;
    }

    pXbdLun->xbdInstSyncSem = semBCreate (SEM_Q_PRIORITY, SEM_EMPTY);

    if (pXbdLun->xbdInstSyncSem == NULL)
    {
        USB2_MSC_ERR ("Failed to create xbdInstSyncSem for lun %d, give up.\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);
        usb2MscXbdDelete(pMscLunDevice);
        return ERROR;
    }

    /* Store the LUN value */

    pXbdLun->lun = pMscLunDevice->lun;

    pXbdLun->pBioHead = NULL;
    pXbdLun->pBioTail = NULL;
    pXbdLun->xbdService = (int)NULL;

    pXbdLun->xbdRead = usb2MscXbdRead;
    pXbdLun->xbdWrite = usb2MscXbdWrite;

    /* Default to be removable */

    pMscLunDevice->mediumRemovable = TRUE;

    /* Default to be not present until proven present */

    pMscLunDevice->mediumPresent = FALSE;

    /* Default as zero sector device */

    pMscLunDevice->bytesPerSector =
        USB2_MSC_DEFAULT_512_PER_SECTOR;
    pMscLunDevice->totalSectors =
        USB2_MSC_DEFAULT_0_SECTORS;

    USB2_MSC_VDBG("Succeed to create the XBD structure for lun %d\n",
                  pMscLunDevice->lun, 2, 3, 4, 5, 6);

    /*
     * Read out the standard INQUIRY information from the device,
     * mainly to check whether the media is removable or not, and
     * the device type is also fetched here.
     */

    if (usb2MscScsiInquiry(pMscLunDevice) != OK)
    {
        USB2_MSC_ERR ("Inquiry failed for lun %d, give up.\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);

        usb2MscXbdDelete(pMscLunDevice);

        return ERROR;
    }

    USB2_MSC_VDBG("Inquiry passed for lun %d removable %d\n",
                  pMscLunDevice->lun,
                  pMscLunDevice->mediumRemovable, 3, 4, 5, 6);

    /*
     * Issue Read Format Capacities command to be compatiable with
     * some other popular operating systems.
     */

    status = usb2MscScsiReadFormatCapacities(pMscLunDevice,
             USB2_MSC_SCSI_READ_FORMAT_CAP_LEN);

    if (status != OK)
    {
        USB2_MSC_DBG("ReadFormatCapacites failed for device lun %d\n",
                     pMscLunDevice->lun, 2, 3, 4, 5, 6);
    }

    /*
     * Try to warm up the device
     */

    status = usb2MscScsiCheckReady(pMscLunDevice);

    if (status != OK)
    {
        USB2_MSC_ERR("Device lun %d not ready\n",
                     pMscLunDevice->lun, 2, 3, 4, 5, 6);
    }
    else
    {
        USB2_MSC_VDBG("Device lun %d now ready\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);
    }

    /*
     * Read the block size and capacity of device
     * (in terms of blocks)
     */

    if (usb2MscScsiReadCapacity10(pMscLunDevice) != OK)
    {
        USB2_MSC_ERR ("ReadCapacity failed for lun %d\n",
                      pMscLunDevice->lun, 2, 3, 4, 5, 6);
    }

    pXbdLun->xbd.xbd_nblocks =  pMscLunDevice->totalSectors;

    pXbdLun->xbd.xbd_blocksize =  pMscLunDevice->bytesPerSector;

    USB2_MSC_DBG("Capacity for lun %d,"\
                 " nblocks = %lu, blocksize = %lu\n",
                 pMscLunDevice->lun,
                 pMscLunDevice->totalSectors,
                 pMscLunDevice->bytesPerSector,
                 4, 5, 6);

    /* Do write protection check */

    usb2MscWriteProtectionCheck(pMscLunDevice);

    return OK;
}

/*******************************************************************************
*
* usb2MscXbdCreateSyncHandler - XBD instantiation synchronization handler
*
* This routine is called by the filesystem when it finishes mounting the
* device. It will release the sync up semaphore to singal that the mounting
* process is done.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscXbdCreateSyncHandler
(
    UINT16 Category,
    UINT16 Type,
    void *eventData,
    void *userData
)
{
    XBD                *pXbd;
    USB2_MSC_XBD_LUN   *pXbdLun;
    devname_t          *devname;
    char bdName[BD_DEVCE_LENTH] = {'\0'};

    if ((Category == xbdEventCategory) &&
            (Type == xbdEventInstantiated))
    {
        devname = (devname_t *) eventData;
        pXbd = (XBD *) userData;
        pXbdLun = (USB2_MSC_XBD_LUN *)pXbd;

        if (strncmp ((char *) devname,
                     (char *) pXbd->xbd_dev.dv_xname,
                     sizeof (devname_t)) != OK)
        {
            USB2_MSC_ERR("XBD device name not match (devname %s dv_xname %s)\n",
                         devname, pXbd->xbd_dev.dv_xname, 3, 4, 5, 6);
            return;
        }

        erfHandlerUnregister (xbdEventCategory,
                              xbdEventInstantiated,
                              usb2MscXbdCreateSyncHandler,
                              userData);

        /* Take the mutex before checking the unmounting status */

        if (pXbdLun->ejectMutex != NULL)
        {
            if (semTake(pXbdLun->ejectMutex, WAIT_FOREVER) != OK)
            {
                return;
            }

            if (pXbdLun->unmounting == TRUE)
            {

                /* Release the mutex */

                semGive(pXbdLun->ejectMutex);

                return;
            }

            /* Release the mutex */

            semGive(pXbdLun->ejectMutex);
        }

        USB2_MSC_DBG("usb2MscXbdCreateSyncHandler singal xbdInstSync\n",
                     1, 2, 3, 4, 5, 6);

        USB2_MSC_INFO("Device %s has been claimed by filesystem\n",
                      pXbdLun->pDrvName, 2, 3, 4, 5, 6);

        semGive (pXbdLun->xbdInstSyncSem);


        /* 将设备名保存起来，通过消息发送 wming add */
        sprintf(bdName, "%s", pXbdLun->pDrvName);
        msgQSend(g_MscHaveMountedMsgID, bdName, sizeof(bdName), NO_WAIT, 0);

#if USB_COPY_DEBUG
        printf("**************************************************************\n");
        printf("sizeof(pXbdLun->pDrvName) =% d\n", sizeof(pXbdLun->pDrvName));
        printf("&pXbdLun->pDrvName = %u\n", &(pXbdLun->pDrvName));
        printf("pXbdLun->pDrvName = %s\n", pXbdLun->pDrvName);
        printf("bdName = %s\n", bdName);
        printf("**************************************************************\n");

        /* 释放信号量,检测到U盘插入并且设备状态正常  */
        /* semGive(g_MscHaveMountedSemId); */
#endif

        /* Check if there is medium change callback */

        if (pXbdLun->pMscLunDevice->pMscDevice->mediumChangeCallback)
        {
            if (pXbdLun->pMscLunDevice->pMscDevice->mediumChangeCallback
                    (pXbdLun->pMscLunDevice->pMscDevice->pClassDevice->hDevice,
                     pXbdLun->lun, TRUE) != TRUE)
            {
                /* Do not do normal hotplug handling */

                return;
            }
        }
    }

    return;
}

/*******************************************************************************
*
* usb2MscXbdRunBio - run a bio issued by the filesystem
*
* This routine exercise the bio for read from or write to the XBD block device.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscXbdRunBio
(
    USB2_MSC_XBD_LUN   *pXbdLun,  /* pointer to XBD block device wrapper */
    struct bio         *pBio      /* pointer to bio */
)
{
    XBD       *pXbd =  (XBD *)pXbdLun; /* Refelection to XBD pointer */
    sector_t   xbdTotalBlocks = pXbd->xbd_nblocks;
    sector_t   nblocks;
    unsigned   size;
    int        status;

    /* Check that all of this transaction fits in the disk */

    nblocks = pBio->bio_bcount / pXbd->xbd_blocksize;

    /*
     * If the BIO starting block number goes beyond the XBD block range,
     * done with error;
     */

    if (xbdTotalBlocks <= pBio->bio_blkno)
    {
        USB2_MSC_ERR("BIO beyond XBD range (bio:%d, xbd:%d)\n",
                     pBio->bio_blkno,
                     pXbd->xbd_nblocks,
                     3, 4, 5, 6);

        pBio->bio_resid = pBio->bio_bcount;

        bio_done (pBio, ENOSPC);

        return;
    }

    /* If we overrun the end of the disk, truncate the block number */

    if (xbdTotalBlocks < pBio->bio_blkno + nblocks)
    {
        nblocks = xbdTotalBlocks - pBio->bio_blkno;
    }

    /* If we have less than 1 block, set the resid and done it */

    if (nblocks == 0)
    {
        bio_done (pBio, 0);
        return;
    }

    /* Calculate the real size and residual */

    size = nblocks * pXbd->xbd_blocksize;
    pBio->bio_resid = pBio->bio_bcount - size;

    /* Now we actually do the read/write operation */

    if (pBio->bio_flags & BIO_READ)
    {
        /* Call the driver's read routine */

        status = pXbdLun->xbdRead(pXbd,
                                  (UINT32) pBio->bio_blkno,
                                  (UINT32) nblocks,
                                  pBio->bio_data);
    }
    else if (pBio->bio_flags & BIO_WRITE)
    {
        /* Check if the disk is write protected */

        if (pXbdLun->pMscLunDevice->writeProtected == TRUE)
        {
            /* Disk is write protected set errno and status */

            status = EACCES;

            errnoSet(S_ioLib_WRITE_PROTECTED);

            USB2_MSC_ERR("Disk is write protected\n",
                         1, 2, 3, 4, 5, 6);
        }
        else
        {
            /*
             * Disk is not write protected, call the driver's
             * write routine
             */

            status = pXbdLun->xbdWrite(pXbd,
                                       (UINT32) pBio->bio_blkno,
                                       (UINT32) nblocks,
                                       pBio->bio_data);
        }
    }
    else
    {
        status = ESRCH;
        errnoSet(ESRCH);
    }

    if (status == OK)
        bio_done (pBio, 0);
    else
        bio_done (pBio, errnoGet());
}


/*******************************************************************************
*
* usb2MscXbdGetNextBio - get the next bio in the bio chain
*
* This routine is called to get the next bio in bio chain for an XBD device.
*
* RETURNS: pointer to the next bio
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL struct bio *usb2MscXbdGetNextBio
(
    USB2_MSC_XBD_LUN   *pXbdLun  /* pointer to XBD block device wrapper */
)
{
    struct bio         *pBio;

    /* Take the mutex for this XBD interface */

    if (semTake (pXbdLun->xbdMutex, WAIT_FOREVER) == ERROR)
        return NULL;

    pBio = pXbdLun->pBioHead;

    if (pBio != NULL)
    {
        /* Update the head to point to the next BIO */

        pXbdLun->pBioHead = pBio->bio_chain;

        /* Cut this BIO out from the list */

        pBio->bio_chain = NULL;

        /*
         * If this is the last BIO, then the tail
         * must also be NULL
         */

        if (pXbdLun->pBioHead == NULL)
        {
            pXbdLun->pBioTail = NULL;
        }
    }

    semGive (pXbdLun->xbdMutex);

    return (pBio);
}

/*******************************************************************************
*
* usb2MscXbdHotPlug - check the medium status and hotplug for removable medium
*
* This routine checks the medium status and does hot plug for removable medium.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscXbdHotPlug
(
    USB2_MSC_XBD_LUN   *pXbdLun /* pointer to the XBD block wrapper */
)
{

    /* If the hotplug check is not enabled, just return */

    if (usrUsb2MscMediumHotplugCheckEabled() != TRUE)
    {
        return;
    }

    /* Validity check */

    if (!pXbdLun ||
            (pXbdLun->pMscLunDevice->mediumRemovable != TRUE))
    {
        return;
    }

    /* Check if there is medium change event */

    if (pXbdLun->pMscLunDevice->mediumChanged == TRUE)
    {
        /* Reset the medium change event */

        pXbdLun->pMscLunDevice->mediumChanged = FALSE;

        /* Check if the medium is currently present */

        if (pXbdLun->pMscLunDevice->mediumPresent == TRUE)
        {
            /*
             * Check if the medium was previously present, if it
             * is not previously present, then this is a medium
             * insert event.
             */

            if (pXbdLun->pMscLunDevice->mediumMounted == FALSE)
            {
                USB2_MSC_INFO("Now %s medium ready\n",
                              (int)pXbdLun->pDrvName, 2, 3, 4, 5, 6);

                pXbdLun->pMscLunDevice->mediumMounted = TRUE;

                /* Check if there is medium change callback */

                if (pXbdLun->pMscLunDevice->pMscDevice->mediumChangeCallback)
                {
                    if (pXbdLun->pMscLunDevice->pMscDevice->mediumChangeCallback
                            (pXbdLun->pMscLunDevice->pMscDevice->pClassDevice->hDevice,
                             pXbdLun->lun, TRUE) != TRUE)
                    {
                        /* Do not do normal hotplug handling */

                        return;
                    }
                }
                /*
                 * Read the block size and capacity of device
                 * (in terms of blocks)
                 */

                if (usb2MscScsiReadCapacity10(pXbdLun->pMscLunDevice) != OK)
                {
                    USB2_MSC_WARN ("ReadCapacity failed for lun %d\n",
                                   pXbdLun->lun, 2, 3, 4, 5, 6);
                }

                pXbdLun->xbd.xbd_nblocks
                = pXbdLun->pMscLunDevice->totalSectors;

                pXbdLun->xbd.xbd_blocksize
                = pXbdLun->pMscLunDevice->bytesPerSector;

                /* Trigger the filesystem to mount the medium */

                erfEventRaise(xbdEventCategory,
                              xbdEventPrimaryInsert,
                              ERF_ASYNC_PROC,
                              (void *)(pXbdLun->xbd.xbd_dev.dv_dev),
                              NULL);
            }

        }
        else
        {
            /*
             * Now the medium is currently not present, check if
             * the medium was previously present; if it was previously
             * present, then this is a medium removal event.
             */

            if (pXbdLun->pMscLunDevice->mediumMounted == TRUE)
            {
                struct bio             *pBio;

                USB2_MSC_INFO("Now %s medium not ready\n",
                              (int)pXbdLun->pDrvName, 2, 3, 4, 5, 6);

                pXbdLun->pMscLunDevice->mediumMounted = FALSE;

                /* Check if there is medium change callback */

                if (pXbdLun->pMscLunDevice->pMscDevice->mediumChangeCallback)
                {
                    if (pXbdLun->pMscLunDevice->pMscDevice->mediumChangeCallback
                            (pXbdLun->pMscLunDevice->pMscDevice->pClassDevice->hDevice,
                             pXbdLun->lun, FALSE) != TRUE)
                    {
                        /* Do not do normal hotplug handling */

                        return;
                    }
                }

                pXbdLun->xbd.xbd_nblocks = 0;

                pXbdLun->xbd.xbd_blocksize = 512;

                /* Trigger the filesystem to unmount the medium */

                erfEventRaise(xbdEventCategory,
                              xbdEventRemove,
                              ERF_ASYNC_PROC,
                              (void *)(pXbdLun->xbd.xbd_dev.dv_dev),
                              NULL);

                /* Then purge the bio queue */

                while ((pBio = usb2MscXbdGetNextBio(pXbdLun)) != NULL)
                    bio_done(pBio, ENXIO);

                /* Trigger the filesystem to mount the medium as rawFs */

                erfEventRaise (xbdEventCategory,
                               xbdEventSoftInsert,
                               ERF_ASYNC_PROC,
                               (void *)(pXbdLun->xbd.xbd_dev.dv_dev),
                               NULL);
            }
        }
    }
}

/*******************************************************************************
*
* usb2MscXbdIdleCheck - do idle check when there is no bio from filesystem
*
* This routine is to do idle check when there is no bio issued
* from filesystem. It tries to check if the device is ready for medium
* access and if the device is write protected, then uses the updated
* status infomation to handle hotplug events, which typically would
* happen for USB card readers and USB floppies.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscXbdIdleCheck
(
    USB2_MSC_XBD_LUN   *pXbdLun /* pointer to the XBD block wrapper */
)
{
    static UINT32 modeSenseCount = 0;

    usb2MscScsiCheckReady(pXbdLun->pMscLunDevice);

    /*
     * If we are allowed to do write protection check and
     * its time to do it, let's do it by issuing mode sense
     * command and check the WP bit.
     */

    if (((++modeSenseCount) % 20) == 0)
    {
        usb2MscWriteProtectionCheck(pXbdLun->pMscLunDevice);
    }

    /* Now do the hotplug */

    usb2MscXbdHotPlug(pXbdLun);
}

/*******************************************************************************
*
* usb2MscXbdService - task level routine to handle read and write operation
*
* This routine waits on a semaphore from strategy routine. It calls
* usb2MscXbdGetNextBio and usb2MscXbdRunBio to excercise all the bios
* currently chained for this device. If the semaphore timeout, it may
* do some idle check and can handle medium hotplug on the fly.
*
* Note that this task is spawned when the device is attached to the
* system and deleted after the device is detached and all the resources
* for this device are freed.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL void usb2MscXbdService
(
    USB2_MSC_XBD_LUN   *pXbdLun /* pointer to the XBD block wrapper */
)
{
    struct bio *pBio;
    STATUS status = ERROR;
    int interval = 0;
    int waitTime = WAIT_FOREVER;

    /* If the hotplug check is enabled, then update the bio wait time */

    if (usrUsb2MscMediumHotplugCheckEabled () == TRUE)
    {
        interval = usrUsb2MscMediumHotplugCheckIntervalGet();

        waitTime = OS_CONVERT_MILLISECONDS_TO_WAIT_VALUE(interval);
    }

    while (TRUE)
    {
        /* Wait semaphore from strategy routine */

        status = semTake(pXbdLun->bioReadySem, waitTime);

        if (status != OK)
        {
            /*
             * Check if we timeout; if we do, no BIO issued from filesystem;
             * Let's do some idle check to update the device status;
             */

            if (S_objLib_OBJ_TIMEOUT == errnoGet())
            {
                /*
                 * Basically, XBD drivers will test/check everytime a R/W
                 * (in the strategy routine) is issued to check if the medium
                 * is removed/inserted; A test has shown that it may
                 * signifcantly reduce the USB storage performance.
                 *
                 * The XBD media test mechanism also exhibts one situation
                 * (bad user experience): if the medium is inserted/removed
                 * after the device is attached to the system, it will only
                 * be mounted/unmounted when there is any IO activity
                 * performed/triggered by the user, such as a user issue "ls"
                 * from the shell (because if there is no IO, then the driver
                 * has no way to report medium removal/insertion event).
                 * The user will experience some delay before the files are
                 * listed or see "Can't open...";
                 *
                 * While rewriting this USB mass storage class driver, a new
                 * mechanism is introduced to do the medium presence check,
                 * based on the fat that we can use the "free bandwidth" to
                 * do the check.
                 *
                 * When there is no BIOs issued from filesystem, the semTake
                 * timeout, then we issue a Test Unit Ready, if the medium is
                 * remvoed, the TUR will fail, and the auto sense data will
                 * tell us the medim change event, and then we raise removal
                 * event to unmount the medium (to be rawFs)... new medium
                 * insertion goes the same way.
                 *
                 * In this approach, the medium presence check will not take
                 * time slice during normal data R/W, it is just busy with
                 * its normal jobs. And if a medium removal happen just during
                 * the data transfer, then the transfer will certainly fail
                 * as expected. And an event will also be raised in next "free
                 * bandwith" medium hotplug check.
                 *
                 * With this new approach, the same performance as vxWorks
                 * 5.x is achieved but doesn't lose any medium hotplug event,
                 * which is the added fucntionlity in 6.x XBD drivers but with
                 * some perfomance penalty.
                 *
                 * Also, with the new approch, the medium is mounted/unmounted
                 * on the fly (doesn't need any user action to trigger any IO
                 * to report the medium removal/insertion), the user can
                 * experience the same behaviour as on some most popular
                 * operating systems.
                 */

                usb2MscXbdIdleCheck(pXbdLun);
            }
            else
            {
                USB2_MSC_ERR("semTake failed, but let's go on...\n",
                             1, 2, 3, 4, 5, 6);
            }

            /* What ever happend, just keep going */

            continue;
        }


        /*
         * Set the bio status flag to TRUE to indicate that bios are being
         * serviced
         */

        pXbdLun->bioBusy = TRUE;

        /* Get all the bios queued for this device and exercise them */

        while ((pBio = usb2MscXbdGetNextBio(pXbdLun)) != NULL)
        {
            USB2_MSC_VDBG("Got new BIO\n",
                          1, 2, 3, 4, 5, 6);
            usb2MscXbdRunBio (pXbdLun, pBio);
        }

        /*
         * set the pBio status flag to FALSE to indicate that all submited
         * bios have been serviced
         */

        pXbdLun->bioBusy = FALSE;

        /*
         * The medium can be hot pluged in and out during
         * the time of IO activity, so let's check and do
         * hotplug if required.
         */

        usb2MscXbdHotPlug(pXbdLun);
    }
}

/*******************************************************************************
* usb2MscXbdGeometryCheck - check and update device geometry information
*
* This routine checks about the geometry of the USB Mass Storage
* device by checking the mode sense geometry and format params command
* feedback from the device. It also updates the XBD_GETGEOMETRY structure
* for the disk's geometry.
*
* Note : We currently do not do the above operations as not all devices
* support these mode sense pages, and if we issue these mode sense commands
* to the device, the device may start to behave wildly. Luckily for USB
* mass storage devices, we may only need to provide valid blocksize and
* total_blocks for the XBD_GEOMETRY structure, other fields can be default
* values.
*
* RETURNS: OK
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL STATUS usb2MscXbdGeometryCheck
(
    XBD            *pXbd,         /* pointer to XBD block device */
    XBD_GEOMETRY   *pGeometry     /* pointer to XBD geometry     */
)
{
    pGeometry->blocksize = pXbd->xbd_blocksize;
    pGeometry->total_blocks = pXbd->xbd_nblocks;
    pGeometry->secs_per_track = (unsigned)USB2_MSC_DEFAULT_SECS_TRACK;
    pGeometry->cylinders = pXbd->xbd_nblocks / USB2_MSC_DEFAULT_SECS_TRACK;
    pGeometry->heads = USB2_MSC_DEFAULT_HEADS;

    USB2_MSC_VDBG("Geometry : heads = %d cylinders = %d secs_per_track = %d "\
                  "total_blocks = %d blocksize = %d\n",
                  pGeometry->heads,
                  pGeometry->cylinders,
                  pGeometry->secs_per_track,
                  pGeometry->total_blocks,
                  pGeometry->blocksize, 6);

    return OK;
}


/*******************************************************************************
* usb2MscXbdMediaTest - test for media existence
*
* This routine is to check if the medium is present and ready for next
* IO access. Typically called by filesystem IO routines.
*
* RETURNS: OK, or ERROR if the medium can not be accessed.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

int usb2MscXbdMediaTest
(
    USB2_MSC_LUN_DEVICE    *pMscLunDevice
)
{
    STATUS status;
    BOOL rcBit;

    /* Call the driver's status routine */

    status = usb2MscStatusCheck(pMscLunDevice);

    rcBit = pMscLunDevice->readyChanged;

    pMscLunDevice->readyChanged = FALSE;

    if (status != OK)
        return (ERROR);

    if (rcBit)
        return (ERROR);

    return (OK);
}

/*******************************************************************************
*
* usb2MscXbdEject - eject the device and instantiate the next step
*
* This routine tries to eject the device and test if we can instantiate
* next XBD device.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

int usb2MscXbdEject
(
    USB2_MSC_LUN_DEVICE    *pMscLunDevice
)
{
    int                 status;
    struct bio         *pBio;
    USB2_MSC_XBD_LUN   *pXbdLun = (USB2_MSC_XBD_LUN *)
                                  pMscLunDevice->pFileSystemHook;

    if (!pXbdLun)
    {
        return ERROR;
    }

    /* Take the mutext before checking the unmounting flag */

    if (pXbdLun->ejectMutex != NULL)
    {
        semTake(pXbdLun->ejectMutex, WAIT_FOREVER);
    }

    /*
     * Don't try further if the device is going to be
     * removed or unmounted
     */

    if (pXbdLun->unmounting == TRUE)
    {
        /* Release the mutex */

        if (pXbdLun->ejectMutex != NULL)
        {
            semGive(pXbdLun->ejectMutex);
        }

        USB2_MSC_ERR("usb2MscXbdEject : S_ioLib_DISK_NOT_PRESENT\n",
                     1, 2, 3, 4, 5, 6);

        return S_ioLib_DISK_NOT_PRESENT;
    }

    /* Announce the ejection */

    erfEventRaise(xbdEventCategory,
                  xbdEventMediaChanged,
                  ERF_ASYNC_PROC,
                  (void *)pXbdLun->xbd.xbd_dev.dv_dev,
                  NULL);

    /* Detach the XBD handle */

    xbdDetach(&(pXbdLun->xbd));

    /* Done any pending bio's */

    while ((pBio = usb2MscXbdGetNextBio(pXbdLun)) != NULL)
    {
        bio_done(pBio, ENXIO);
    }

    /*
     * Now we instantiate the next XBD - if we have media, then its a regular
     * XBD, but if we don't, its an xbd of size 0 which fills in for the XBD
     * until media is actually inserted
     */

    if (usb2MscXbdMediaTest(pMscLunDevice) == OK)
    {
        /* Read the block size and capacity of device (in terms of blocks) */

        if (usb2MscScsiReadCapacity10(pMscLunDevice) == ERROR)
        {
            USB2_MSC_WARN ("ReadCapacity failed for lun %d\n",
                           pMscLunDevice->lun, 2, 3, 4, 5, 6);
        }

        pXbdLun->xbd.xbd_nblocks =  pMscLunDevice->totalSectors;

        pXbdLun->xbd.xbd_blocksize =  pMscLunDevice->bytesPerSector;

        USB2_MSC_DBG("ReadCapacity passed for lun %d,"\
                     " nblocks %lu, blocksize %lu\n",
                     pMscLunDevice->lun,
                     pMscLunDevice->totalSectors,
                     pMscLunDevice->bytesPerSector,
                     4, 5, 6);

        /* Check again to see if the device is online */

        if (pXbdLun->unmounting == FALSE)
        {
            USB2_MSC_DBG("Remount the full size device \n",
                         1, 2, 3, 4, 5, 6);

            /* We have new media to mount */

            status = xbdAttach(&(pXbdLun->xbd),
                               &usb2MscXbdLunFuncs,
                               pXbdLun->xbd.xbd_dev.dv_xname,
                               pXbdLun->xbd.xbd_blocksize,
                               pXbdLun->xbd.xbd_nblocks,
                               &pXbdLun->device);

            pMscLunDevice->mediumMounted = TRUE;
        }
        else
        {
            status = S_ioLib_DISK_NOT_PRESENT;
        }
    }
    else
    {
        /* Check again to see if the device is online */

        if (pXbdLun->unmounting == FALSE)
        {
            USB2_MSC_DBG("Remount the zero size device \n",
                         1, 2, 3, 4, 5, 6);

            /* We are making a 0-block length XBD */

            status = xbdAttach(&(pXbdLun->xbd),
                               &usb2MscXbdLunFuncs,
                               pXbdLun->xbd.xbd_dev.dv_xname,
                               512,
                               0,
                               &pXbdLun->device);

            pMscLunDevice->mediumMounted = FALSE;
        }
        else
        {
            status = S_ioLib_DISK_NOT_PRESENT;
        }
    }

    /* Announce our new XBD */

    if (status == OK)
    {
        USB2_MSC_DBG("Raise the xbdEventPrimaryInsert event \n",
                     1, 2, 3, 4, 5, 6);

        erfEventRaise(xbdEventCategory,
                      xbdEventPrimaryInsert,
                      ERF_ASYNC_PROC,
                      (void *)pXbdLun->device,
                      NULL);
    }

    /* Release the mutex */

    if (pXbdLun->ejectMutex != NULL)
    {
        semGive(pXbdLun->ejectMutex);
    }

    return (status);
}

/*******************************************************************************
* usb2MscXbdTest - test to see if media is present or not.
*
* This routine is to test if medium is present; If a change of media
* has occurred, test XBD's for 0 size and eject the device and
* instantiate the next device accordingly.
*
* RETURNS: OK, or ERROR if the media can not be accessed.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

int usb2MscXbdTest
(
    USB2_MSC_LUN_DEVICE *pMscLunDevice
)
{
    BOOL status = ERROR;
    USB2_MSC_XBD_LUN      *pXbdLun;

    /* Get the filesystem hook */

    pXbdLun = (USB2_MSC_XBD_LUN *)pMscLunDevice->pFileSystemHook;

    status = usb2MscXbdMediaTest(pMscLunDevice);

    if (pMscLunDevice->mediumMounted == TRUE)
    {
        /* We are a full-size XBD - if there is no media, then eject */

        if (status == ERROR)
        {
            USB2_MSC_INFO("Now %s medium not ready\n",
                          (int)pXbdLun->pDrvName, 2, 3, 4, 5, 6);

            /* Removal happened */

            usb2MscXbdEject(pMscLunDevice);

            return (S_ioLib_MEDIA_CHANGED);
        }
    }
    else
    {
        /* We are a 0 size XBD */

        if (status == ERROR)
        {
            status = usb2MscXbdMediaTest(pMscLunDevice);
            if (status == OK)
            {
                USB2_MSC_INFO("Now %s medium ready\n",
                              (int)pXbdLun->pDrvName, 2, 3, 4, 5, 6);

                /* if there IS media then eject */

                usb2MscXbdEject(pMscLunDevice);

                return (S_ioLib_MEDIA_CHANGED);
            }
        }
    }
    return (OK);
}

/***************************************************************************
*
* usbBulkDevIoctl - perform a device-specific io control
*
* Typically called to invoke device-specific io control functions
* which may not necessarily needed by a filesystem.
*
* RETURNS: the status of the request, or ERROR if the request is unsupported.
*
* ERRNO:
* \is
* \i S_ioLib_UNKNOWN_REQUEST
* A not impletemented/unknown command is recevied.
* \ie
*
* \NOMANUAL
*/

LOCAL int usb2MsxXbdIoctl
(
    XBD   *pXbd,                    /* pointer to XBD device       */
    int    request,                 /* request type                 */
    void *someArg                   /* arguments related to request */
)
{
    device_t                dev;
    struct bio             *pBio;
    STATUS                  status = OK;
    USB2_MSC_XBD_LUN       *pXbdLun = (USB2_MSC_XBD_LUN *)pXbd;
    USB2_MSC_LUN_DEVICE    *pMscLunDevice = pXbdLun->pMscLunDevice;

    /* Check if we need to do status check */

    if ((pMscLunDevice->mediumRemovable == TRUE) &&
            (usrUsb2MscMediumHotplugCheckEabled() != TRUE) &&
            (usrUsb2MscStatusCheckEnabled() == TRUE))
    {
        USB2_MSC_VDBG("start usb2MscXbdTest\n", 1, 2, 3, 4, 5, 6);

        status = usb2MscXbdTest(pMscLunDevice);

        if (status == S_ioLib_MEDIA_CHANGED)
        {
            USB2_MSC_ERR("S_ioLib_MEDIA_CHANGED\n", 1, 2, 3, 4, 5, 6);

            return status;
        }
        USB2_MSC_VDBG("usb2MscXbdTest passed\n", 1, 2, 3, 4, 5, 6);
    }

    switch (request)
    {
    case FIODISKFORMAT:
        USB2_MSC_DBG("FIODISKFORMAT\n",
                     1, 2, 3, 4, 5, 6);

        /* Call format unit with default parameters */

        status = usb2MscScsiFormatUnit(pMscLunDevice,
                                       FALSE,
                                       0,
                                       0,
                                       0,
                                       0,
                                       0);
        break;

    case XBD_GETGEOMETRY:
        USB2_MSC_DBG("XBD_GETGEOMETRY\n",
                     1, 2, 3, 4, 5, 6);

        status = usb2MscXbdGeometryCheck(pXbd,
                                         (XBD_GEOMETRY *)someArg);
        break;

    case XBD_GETBASENAME:
        USB2_MSC_DBG("XBD_GETBASENAME\n",
                     1, 2, 3, 4, 5, 6);

        dev = pXbd->xbd_dev.dv_dev;

        if (devName(dev, someArg) == ERROR)
            status = errno;

        break;

    case XBD_SYNC:
        USB2_MSC_DBG("XBD_SYNC\n",
                     1, 2, 3, 4, 5, 6);
        /*
         * From the tested USB disks, no support of synchronize disk
         * is provided, simply return OK
         */

        break;

    case XBD_SOFT_EJECT:
    case XBD_HARD_EJECT:
        USB2_MSC_DBG("ioctl %s\n",
                     (request == XBD_SOFT_EJECT) ?
                     "XBD_SOFT_EJECT" : "XBD_HARD_EJECT", 2, 3, 4, 5, 6);

        /* Take the mutex */

        if (semTake(pXbdLun->xbdMutex, WAIT_FOREVER) == OK)
        {
            status = OK;

            /* First raise a removal event */

            erfEventRaise(xbdEventCategory,
                          xbdEventRemove,
                          ERF_ASYNC_PROC,
                          (void *)(pXbdLun->xbd.xbd_dev.dv_dev),
                          NULL);

            /* Then purge the bio queue */

            while ((pBio = usb2MscXbdGetNextBio(pXbdLun)) != NULL)
                bio_done(pBio, ENXIO);

            /* Last raise an insertion event */

            if (request == XBD_SOFT_EJECT)
            {
                erfEventRaise (xbdEventCategory,
                               xbdEventSoftInsert,
                               ERF_ASYNC_PROC,
                               (void *)(pXbdLun->xbd.xbd_dev.dv_dev),
                               NULL);
            }
            else
            {
                erfEventRaise (xbdEventCategory,
                               xbdEventPrimaryInsert,
                               ERF_ASYNC_PROC,
                               (void *)(pXbdLun->xbd.xbd_dev.dv_dev),
                               NULL);
            }

            /* Release the mutex */

            semGive(pXbdLun->xbdMutex);
        }
        else
        {
            status = ERROR;
        }
        break;

    case XBD_TEST:
        USB2_MSC_VDBG("XBD_TEST\n",
                      1, 2, 3, 4, 5, 6);
        status = OK;
        break;

    case FIOSYNC:
        USB2_MSC_VDBG("FIOSYNC\n",
                      1, 2, 3, 4, 5, 6);
        status = OK;
        break;

    case XBD_STACK_COMPLETE:
        USB2_MSC_DBG("XBD_STACK_COMPLETE\n",
                     1, 2, 3, 4, 5, 6);

        /* Take the mutex */

        if (semTake(pXbdLun->xbdMutex, WAIT_FOREVER) == OK)
        {
            status = OK;

            if (!pXbdLun->xbdInstantiated)
            {
                USB2_MSC_VDBG("Lun %d instantiated\n",
                              pXbdLun->lun, 2, 3, 4, 5, 6);

                erfEventRaise (xbdEventCategory,
                               xbdEventInstantiated,
                               ERF_ASYNC_PROC,
                               pXbd->xbd_dev.dv_xname,
                               NULL);

                pXbdLun->xbdInstantiated = TRUE;
            }

            /* Release the mutex */

            semGive(pXbdLun->xbdMutex);
        }
        else
        {
            status = ERROR;
        }
        break;
        /*
         * Compile time check for XBD_GETINFO, which was not
         * defined prior to vxWorks 6.6
         */

#ifdef XBD_GETINFO
    case XBD_GETINFO:
        USB2_MSC_DBG("XBD_GETINFO\n",
                     1, 2, 3, 4, 5, 6);

        if (someArg == NULL)
        {
            status = ENXIO;
        }
        else
        {
            XBD_INFO   *pInfo = (XBD_INFO *) someArg;

            status = OK;

            /*
             * Get the read/write status of the drive.  We assume it
             * has been created
             */

            pInfo->properties = 0;

            if (pXbdLun->pMscLunDevice->writeProtected == TRUE)
                pInfo->properties |= XBD_INFO_READONLY;

            /*
             * This is redundant with the XBD_GETGEOMETRY call above
             */

            if (usb2MscXbdGeometryCheck(pXbd, &pInfo->xbdGeometry) == ERROR)
            {
                USB2_MSC_ERR("Geometry failed in GET_INFO\n",
                             1, 2, 3, 4, 5, 6);
                status = EACCES;
            }

            /* Clear reserved area */

            memset(pInfo->reserved, 0, 4 * sizeof(UINT32));

        } /* end of XBD_GETINFO ioctl */
        break;
#endif /* XBD_GETINFO */
    default:
        errnoSet (S_ioLib_UNKNOWN_REQUEST);

        USB2_MSC_ERR("S_ioLib_UNKNOWN_REQUEST %d %d\n",
                     request,
                     (int)someArg,
                     3, 4, 5, 6);

        status = ENOTSUP;

        break;
    }

    return (status);
}


/*******************************************************************************
*
* usb2MscXbdStrategy - strategy routine for the XBD block device
*
* This routine effects the data transaction. The information
* in the bio is used by the device driver to transfer data. This
* is an asynchronous function in that once the data in the bio
* is used to setup the data transfer, or queued in the FIFO XBD
* bio queue, the function returns. It releases a semaphore to
* the usb2MscXbdService task to handle the bio.
*
* RETURNS: OK, or status code describing the failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL int usb2MscXbdStrategy
(
    XBD          *pXbd,             /* pointer to XBD */
    struct bio   *pBio              /* pointer to bio */
)
{
    USB2_MSC_XBD_LUN       *pXbdLun = (USB2_MSC_XBD_LUN *)pXbd;
    struct bio             *pLastBio = pBio;
    USB2_MSC_LUN_DEVICE    *pMscLunDevice = pXbdLun->pMscLunDevice;
    int                     status = ERROR;

    /* Check if we need to do status check */

    if ((pMscLunDevice->mediumRemovable == TRUE) &&
            (usrUsb2MscMediumHotplugCheckEabled() != TRUE) &&
            (usrUsb2MscStatusCheckEnabled() == TRUE))
    {
        USB2_MSC_VDBG("start usb2MscXbdTest\n", 1, 2, 3, 4, 5, 6);

        status = usb2MscXbdTest(pMscLunDevice);

        if (status != OK)
        {
            USB2_MSC_ERR("usb2MscXbdTest failed\n", 1, 2, 3, 4, 5, 6);

            /* Purge BIO queue */

            while (pLastBio != NULL)
            {
                bio_done (pLastBio, status);

                pLastBio = pLastBio->bio_chain;
            }

            return status;
        }
        USB2_MSC_VDBG("usb2MscXbdTest passed\n", 1, 2, 3, 4, 5, 6);
    }

    /* Don't try further if medium not present */

    if ((pMscLunDevice->mediumRemovable == TRUE) &&
            (pMscLunDevice->mediumPresent != TRUE))
    {
        USB2_MSC_ERR("S_ioLib_DISK_NOT_PRESENT\n",
                     1, 2, 3, 4, 5, 6);

        status = S_ioLib_DISK_NOT_PRESENT;

        /* Purge BIO queue */

        while (pLastBio != NULL)
        {
            bio_done (pLastBio, S_ioLib_DISK_NOT_PRESENT);

            pLastBio = pLastBio->bio_chain;
        }

        return (status);
    }

    if (usrUsb2MscXbdDirectBioEnabled() == TRUE)
    {
        pXbdLun->bioBusy = TRUE;

        usb2MscXbdRunBio (pXbdLun, pBio);

        pXbdLun->bioBusy = FALSE;
    }
    else
    {
        /* Take the mutex semaphore for this XBD interface */

        if (semTake (pXbdLun->xbdMutex, WAIT_FOREVER) == ERROR)
        {
            USB2_MSC_ERR("xbdMutex wrong\n",
                         1, 2, 3, 4, 5, 6);

            /* Purge BIO queue */

            while (pLastBio != NULL)
            {
                bio_done (pLastBio, ENXIO);

                pLastBio = pLastBio->bio_chain;
            }

            return ERROR;
        }
        /* Get the last BIO in the BIO chain */

        while (pLastBio->bio_chain != NULL)
        {
            /* Get to Next */

            pLastBio = pLastBio->bio_chain;
        }

        /* Check if the tail is valid */

        if (pXbdLun->pBioTail)
        {
            pXbdLun->pBioTail->bio_chain = pBio;
        }
        else
        {
            pXbdLun->pBioHead = pBio;
        }

        pXbdLun->pBioTail = pLastBio;

        /* Release the mutex semaphore */

        semGive (pXbdLun->xbdMutex);

        /* Trigger our service task */

        semGive(pXbdLun->bioReadySem);

    }

    return (OK);
}

/*******************************************************************************
* usb2MscXbdDump - dump data to device
*
* This routine effects the data transaction specified in the
* bio with interrupts off. This call is similar to the strategy
* call, only it executes with interrupts off. This is intended
* to allow a filesystem to dump data to the device prior to a
* system crash.
*
* RETURNS: bio_error status of the strategy call for the bio.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

LOCAL int usb2MscXbdDump
(
    XBD      *self,
    sector_t  blkno,
    void     *data,
    size_t    size
)
{
    struct bio     varBio;

    /* Set up a BIO for this transaction */

    varBio.bio_dev     = self->xbd_dev.dv_dev;
    varBio.bio_blkno   = blkno;
    varBio.bio_bcount  = size;
    varBio.bio_data    = data;
    varBio.bio_error   = 0;
    varBio.bio_flags   = BIO_WRITE;
    varBio.bio_done    = NULL;
    varBio.bio_caller1 = NULL;
    varBio.bio_chain   = NULL;

    /* Call our own strategy routine on it */

    usb2MscXbdStrategy(self, &varBio);

    return (varBio.bio_error);
}

/*******************************************************************************
*
* usb2MscXbdMount - mount a drive to the filesystem
*
* This function mounts the drive to the filesystem.
*
* RETURNS: OK or ERROR
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS usb2MscXbdMount
(
    USB2_MSC_LUN_DEVICE *pMscLunDevice
)
{
    STATUS                  status;
    USB2_MSC_XBD_LUN       *pXbdLun;
    char                   *pSvrTaskName;

    status = usb2MscXbdCreate(pMscLunDevice);

    /* Check if the XBD for the LUN created OK */

    if ((status != OK) || !pMscLunDevice->pFileSystemHook)
    {
        USB2_MSC_ERR("Failed to create XBD\n",
                     1, 2, 3, 4, 5, 6);
        return ERROR;
    }

    /* Cast the created filesystem hook as USB2_MSC_XBD_LUN */

    pXbdLun = (USB2_MSC_XBD_LUN *)pMscLunDevice->pFileSystemHook;

    /* Get the drive name */

    pXbdLun->pDrvName = usrUsb2MscDrvNameGet(
                            pMscLunDevice->pMscDevice->hUsrConfig,
                            pMscLunDevice->lun);

    /* Get the service task name */

    pSvrTaskName = usrUsb2MscServiceTaskNameGet(
                       pMscLunDevice->pMscDevice->hUsrConfig,
                       pMscLunDevice->lun);

    /* Register new event handler for base device synchronization */

    status = erfHandlerRegister (xbdEventCategory,
                                 xbdEventInstantiated,
                                 usb2MscXbdCreateSyncHandler,
                                 pXbdLun,
                                 (UINT16)NULL);

    if (status != OK)
    {
        USB2_MSC_ERR("Failed to register usb2MscXbdCreateSyncHandler\n",
                     1, 2, 3, 4, 5, 6);

        usb2MscXbdDelete(pMscLunDevice);

        return (ERROR);
    }

    if (usrUsb2MscXbdDirectBioEnabled() == FALSE)
    {
        /* Spawn a service task for this XBD */

        pXbdLun->xbdService = taskSpawn(pSvrTaskName,
                                        usrUsb2MscServiceTaskPriorityGet(),
                                        usrUsb2MscServiceTaskOptionsGet(),
                                        usrUsb2MscServiceTaskStackSizeGet(),
                                        (FUNCPTR)usb2MscXbdService,
                                        (int)pXbdLun,
                                        0, 0, 0, 0, 0, 0, 0, 0, 0);

        if (pXbdLun->xbdService == ERROR)
        {
            USB2_MSC_ERR("usb2MscXbdService taskSpawn failed\n",
                         1, 2, 3, 4, 5, 6);

            erfHandlerUnregister(xbdEventCategory,
                                 xbdEventInstantiated,
                                 usb2MscXbdCreateSyncHandler,
                                 pXbdLun);

            usb2MscXbdDelete(pMscLunDevice);

            return ERROR;
        }
    }

    USB2_MSC_INFO("Mounting device (PDT %p PQ %p RMB %p) "\
                  "VID = %s : PID = %s : REV = %s\n",
                  pMscLunDevice->scsiPDT,
                  pMscLunDevice->scsiPQ,
                  pMscLunDevice->mediumRemovable,
                  pMscLunDevice->deviceVIDString,
                  pMscLunDevice->devicePIDString,
                  pMscLunDevice->deviceREVString);

    USB2_MSC_INFO("Device %p LUN %d of %lu (KB) "\
                  "will be mounted with base name %s\n",
                  pMscLunDevice->pMscDevice->pClassDevice->hDevice,
                  pXbdLun->lun,
                  pMscLunDevice->totalCapacityKB,
                  pXbdLun->pDrvName,
                  5, 6);

    if (pMscLunDevice->mediumPresent == TRUE)
    {
        /* Full size disk file system initialization */

        status = xbdAttach(&pXbdLun->xbd,
                           &usb2MscXbdLunFuncs,
                           pXbdLun->pDrvName,
                           pXbdLun->xbd.xbd_blocksize,
                           pXbdLun->xbd.xbd_nblocks,
                           &(pXbdLun->device));
        if (status == OK)
        {
            USB2_MSC_VDBG("xbdAttach OK for full size XBD\n",
                          1, 2, 3, 4, 5, 6);

            erfEventRaise(xbdEventCategory,
                          xbdEventPrimaryInsert,
                          ERF_ASYNC_PROC,
                          (void *)(pXbdLun->device),
                          NULL);

            pXbdLun->pMscLunDevice->mediumMounted = TRUE;

            semTake (pXbdLun->xbdInstSyncSem, USB2_MSC_XBD_SYNC_WAIT_TIME);
        }
        else
        {
            USB2_MSC_ERR("xbdAttach failed for full size XBD\n",
                         1, 2, 3, 4, 5, 6);

            erfHandlerUnregister (xbdEventCategory,
                                  xbdEventInstantiated,
                                  usb2MscXbdCreateSyncHandler,
                                  pXbdLun);

            if (usrUsb2MscXbdDirectBioEnabled() == FALSE)
                taskDelete (pXbdLun->xbdService);

            usb2MscXbdDelete(pMscLunDevice);

            return ERROR;
        }
    }
    else
    {
        /* 0 size XBD instantiation */

        status = xbdAttach(&pXbdLun->xbd,
                           &usb2MscXbdLunFuncs,
                           pXbdLun->pDrvName,
                           512,
                           0,
                           &(pXbdLun->device));
        if (status == OK)
        {
            USB2_MSC_ERR("xbdAttach OK for zero size XBD\n",
                         1, 2, 3, 4, 5, 6);

            erfEventRaise(xbdEventCategory,
                          xbdEventPrimaryInsert,
                          ERF_ASYNC_PROC,
                          (void *)(pXbdLun->device),
                          NULL);

            semTake (pXbdLun->xbdInstSyncSem, USB2_MSC_XBD_SYNC_WAIT_TIME);
        }
        else
        {
            USB2_MSC_ERR("xbdAttach failed for zero size XBD\n",
                         1, 2, 3, 4, 5, 6);

            erfHandlerUnregister (xbdEventCategory,
                                  xbdEventInstantiated,
                                  usb2MscXbdCreateSyncHandler,
                                  pXbdLun);

            if (usrUsb2MscXbdDirectBioEnabled() == FALSE)
                taskDelete (pXbdLun->xbdService);

            usb2MscXbdDelete(pMscLunDevice);

            return ERROR;
        }
    }

    USB2_MSC_DBG("usb2MscXbdMount exited \n",
                 1, 2, 3, 4, 5, 6);

    return OK;
}


/*******************************************************************************
*
* usb2MscXbdUnmount - unmount a drive from the filesystem
*
* This routine unmounts the drive from the filesystem.
*
* RETURNS: OK, or ERROR if there is any failure.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS usb2MscXbdUnmount
(
    USB2_MSC_LUN_DEVICE *pMscLunDevice
)
{
    USB2_MSC_XBD_LUN      *pXbdLun;
    struct bio *pBio;

    /* Get the filesystem hook */

    pXbdLun = (USB2_MSC_XBD_LUN *)pMscLunDevice->pFileSystemHook;

    if (!pXbdLun)
    {
        USB2_MSC_ERR("File system not mounted\n",
                     1, 2, 3, 4, 5, 6);

        /* Return OK since we do not need to unmount it */

        return OK;
    }

    /* Filesystem uninitalization */

    /* Take the mutex before unmounting the device */

    if (pXbdLun->ejectMutex != NULL)
    {
        semTake(pXbdLun->ejectMutex, WAIT_FOREVER);
    }

    /* Set the unmounting flag to stop any further IO */

    pXbdLun->unmounting = TRUE;

    /*
     * Unregister the xbdEventInstantiated event to stop
     * usb2MscXbdCreateSyncHandler being called after the
     * device has been removed
     */

    erfHandlerUnregister (xbdEventCategory,
                          xbdEventInstantiated,
                          usb2MscXbdCreateSyncHandler,
                          pXbdLun);

    erfEventRaise(xbdEventCategory,
                  xbdEventRemove,
                  ERF_ASYNC_PROC,
                  (void *)pXbdLun->xbd.xbd_dev.dv_dev,
                  NULL);

    xbdDetach (&(pXbdLun->xbd));

    /* Unmap the XBD device */

    devUnmap((struct device *) & (pXbdLun->xbd));

    /*
     * Execute all the remaining bios and wait for more bios when
     * dv_dev is not NULLDEV
     */

    while (((pBio = usb2MscXbdGetNextBio(pXbdLun)) != NULL) ||
            (pXbdLun->xbd.xbd_dev.dv_dev != NULLDEV))
    {
        if (pBio != NULL)
            bio_done(pBio, ENXIO);
        else
            taskDelay(1);
    }

    /*
     * Before deleting the XBD service task, wait for all BIO's to
     * be serviced.
     * This is important because it may be possible that while we are
     * deleting the thread some BIOs are submitted but yet to be
     * serviced.
     */

    while (pXbdLun->bioBusy)
    {
        taskDelay (1);
    }

    if (pXbdLun ->xbdService != (int)NULL)
    {
        taskDelete(pXbdLun->xbdService);
    }

    /* Release the mutex */

    if (pXbdLun->ejectMutex != NULL)
    {
        semGive(pXbdLun->ejectMutex);
    }

    USB2_MSC_INFO("%s has been unmounted\n",
                  pXbdLun->pDrvName, 2, 3, 4, 5, 6);

    /* Delete the block device structure */

    usb2MscXbdDelete(pMscLunDevice);

    return OK;
}

