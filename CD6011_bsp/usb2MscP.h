/* usb2MscP.h - USB Mass Storage Class Driver Private Header */

/*
 * Copyright (c) 2008-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,24sep09,w_x  Add READ FORMAT CAPACITIES command support (WIND00183566)
01e,17sep09,w_x  Avoid allocating endpoint status from stack (WIND00182242)
01d,27aug09,w_x  Unify log mechanism in USB GEN2 class drivers (WIND00178936)
01c,14apr09,w_x  coding convention changes
01b,19jan09,w_x  clean up for first check in
01a,29oct08,w_x  written
*/

#ifndef __INCusb2MscPh
#define __INCusb2MscPh

#ifdef __cplusplus
extern "C" {
#endif

#include <usb2/usb2Msc.h>

    /* Defined in usb2Msc.c */

    IMPORT USB2_CLASS_DRIVER *pUsb2MscDriver;

    /************ BBB related definitions - START ******/

    /* Class specific Mass storage reset request    */

#define USB2_MSC_BBB_RESET                      0xFF

    /* Class specific Get Max LUN request           */

#define USB2_MSC_BBB_GET_MAX_LUN                0xFE

    /* Command Block Wrapper Signature 'USBC'       */

#define USB2_MSC_CBW_SIGNATURE                  0x43425355
#define USB2_MSC_CBW_MAX_CDB_LEN                16

    /* Command Block Wrapper Flag                   */

#define USB2_MSC_CBW_FLAGS_DATA_IN              0x80
#define USB2_MSC_CBW_FLAGS_DATA_OUT             0x00
#define USB2_MSC_CBW_FLAGS_DATA_NONE            0x00

    /* Command Status Wrapper Signature 'USBS'      */

#define USB2_MSC_CSW_SIGNATURE                  0x53425355

    /* Command Status Wrapper Status                */

#define USB2_MSC_CSW_STATUS_SUCCESS             0x00
#define USB2_MSC_CSW_STATUS_FAILED              0x01
#define USB2_MSC_CSW_STATUS_PHASE_ERROR         0x02

    /* CBW and CSW length                           */

#define USB2_MSC_CBW_LENGTH                     31
#define USB2_MSC_CSW_LENGTH                     13

    /************ BBB related definitions - END ******/

    /************ CB[I] related definitions - START ******/

#define USB2_MSC_CBI_STATUS_SUCCESS             0x00
#define USB2_MSC_CBI_STATUS_FAILED              0x01
#define USB2_MSC_CBI_STATUS_PHASE_ERROR         0x02
#define USB2_MSC_CBI_STATUS_PERSISTENT_ERROR    0x03

#define USB2_MSC_CBI_STATUS_BUFFER_LENGTH       2

    /************ CB[I] related definitions - END ******/

    /*
     * Default values for disk geometry of block devices
     */

#define USB2_MSC_DEFAULT_SECS_TRACK             1
#define USB2_MSC_DEFAULT_HEADS                  1
#define USB2_MSC_DEFAULT_0_SECTORS              0
#define USB2_MSC_DEFAULT_512_PER_SECTOR         512

    /*
     * Macro to check if we can allow I/O requests
     */

#define USB2_MSC_ALLOW_IO( p ) \
   ( ( p != NULL ) && \
     ( p->ioReady == TRUE) && \
     (p->deviceRemoved == FALSE) )

    extern UINT32  usb2MscDebug;

#define USB2_MSC_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    USB2_CLASS_ERR(usb2Msc, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_MSC_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    USB2_CLASS_DBG(usb2Msc, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_MSC_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    USB2_CLASS_VDBG(usb2Msc, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_MSC_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    USB2_CLASS_INFO(usb2Msc, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_MSC_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    USB2_CLASS_WARN(usb2Msc, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

    /* Command Block Wrapper */

    typedef struct usb2MscCbw
    {
        UINT32    dCBWSignature;              /* CBW Signature                  */
        UINT32    dCBWTag;                    /* Tag field                      */
        UINT32    dCBWDataTransferLength;     /* Size of data (bytes)           */
        UINT8     bmCBWFlags;                 /* direction bit                  */
        UINT8     bCBWLUN;                    /* Logical Unit Number            */
        UINT8     bCBWCBLength;               /* Length of command block        */
        UINT8     CBWCB [16];                 /* buffer for command block       */
    } WRS_PACK_ALIGN(1) USB2_MSC_CBW;

    /* Command Status Wrapper */

    typedef struct usb2MscCsw
    {
        UINT32    dCSWSignature;              /* CBW Signature                  */
        UINT32    dCSWTag;                    /* Tag field                      */
        UINT32    dCSWDataResidue;            /* Size of residual data (bytes)  */
        UINT8     bCSWStatus;                 /* buffer for command block       */
    } WRS_PACK_ALIGN(1) USB2_MSC_CSW;

    typedef struct
    {
        /* Class device specific infoamtion */

        USB2_CLASS_DEVICE      *pClassDevice;   /* GEN2 Class device information */
        USBD_DEVICE_INFO       *pDeviceInfo;    /* USBD device information       */
        UINT8                   uSpeed;         /* Device speed reported by USBD */
        BOOL                    ioReady;        /* Boolean for ready for I/O     */
        BOOL                    deviceRemoved;  /* Boolean for device removed    */
        int                     resetTimeout;   /* Device reset command timeout  */
        int                     commandTimeout; /* Device normal command timeout */
        int                     statusTimeout;  /* Device status timeout         */
        SEM_ID                  bulkOutSem;     /* Binary semaphpre for BULK OUT */
        SEM_ID                  bulkInSem;      /* Binary semaphpre for BULK IN  */
        SEM_ID                  intInSem;       /* Binary semaphpre for INT IN   */
        USBHST_URB              bulkOutUrb;     /* URB for BULK OUT endpoint     */
        USBHST_URB              bulkInUrb;      /* URB for BULK IN endpoint      */
        USBHST_URB              intInUrb;       /* URB for INT IN endpoint       */
        UINT32                  uBulkOutBufferSize; /* Size of BULK OUT transfer */
        UINT32                  uBulkInBufferSize;  /* Size of BULK IN transfer  */
        UINT32                  uIntInBufferSize;   /* Size of INT IN transfer   */
        UINT8                   bBulkOutEndPointAddr; /* BULK OUT EP address     */
        UINT8                   bBulkInEndPointAddr;  /* BULK IN EP address      */
        UINT8                   bIntInEndPointAddr;   /* INT  IN EP address      */
        USB2_MSC_QUIRKY_INFO   *pQuirky;              /* Quirky device entry     */
        UINT32                  staticFlags;          /* Static quirky flags     */
        UINT32                  dynamicFlags;         /* Dynamical quirky flags  */
        UINT8                   subClassCode;         /* Device subclass code    */
        UINT8                   protocolCode;         /* Device protocol code    */
        UINT8                   interfaceNum;         /* Device interface number */
        UINT8                   curAltSetting;        /* Alternate setting       */
        UINT8                   maxLun;               /* Total number of LUNs    */
        UINT32                  curCBWTag;           /* CBW dCBWTag increased   */
        /* for every command       */
        UINT32                  dCSWSignatureCompare; /* value to be compared    */
        /* with CSW dCSWSignature  */
        UINT32                  dCSWDataResidueLast;  /* To save last residue    */
        UINT8                  *pWorkspace;           /* Short transfer buffer   */
        UINT16                  endpointStatus;       /* Avoid allocate on stack */
        ULONG                   hUsrConfig;           /* Handle to user context  */
        ULONG                   hDirectAccess;        /* Handle to Direct Access */
        ULONG                   hCompliance;          /* Handle to compliance tst*/
        ULONG                   hLunDevice[USB2_MSC_MAX_LUN]; /* Handle for LUN  */
        FUNCPTR                 mediumChangeCallback; /* Medium Change callback  */
        void                   *pFurtherExt;          /* For further extention   */
    } USB2_MSC_DEVICE;

    typedef struct usb2_msc_lun_device
    {
        USB2_MSC_DEVICE    *pMscDevice;         /* Parent represent the device   */
        UINT8               lun;                /* LUN that we represent         */
        SEM_ID              lunMutex;           /* Access lock                   */
        UINT32              readSectorTimeout;  /* Sector read timeout           */
        UINT32              writeSectorTimeout; /* Sector read timeout           */
        UINT32              scsiCommandTimeout; /* Sector read timeout           */
        long long           totalSectors;       /* Total number of sectors       */
        unsigned            bytesPerSector;     /* Size in bytes per sector      */
        UINT64              totalCapacityKB;    /* Total capacity in KB          */
        UINT8               scsiLevel;          /* SCSI level of the device      */
        UINT8               scsiPDT;            /* SCSI Peripheral Device Type   */
        UINT8               scsiPQ;             /* SCSI Peripheral Qualifier     */
        UINT8               mediumType;         /* SCSI medium type              */
        BOOL                mediumRemovable;    /* Removable media bit (RMB)     */
        BOOL                mediumPresent;      /* A medium is present           */
        BOOL                mediumMounted;      /* Is this mounted by filesystem */
        BOOL                writeProtected;     /* Medium/device write-protected */
        BOOL                removing;           /* Device marked for removal     */
        BOOL                busy;               /* Device marked as busy         */
        BOOL                mediumChanged;      /* Medium has changed            */
        BOOL                readyChanged;       /* Ready changed                 */
        UINT8              *pCmdBuffer;         /* Command buffer                */
        UINT8              *pDataBuffer;        /* Driver internal data buffer   */
        VOID               *pFileSystemHook;

        /* Device personality, add 1 byte to allow fixup */

        char                deviceVIDString [ USB2_MSC_SCSI_INQUIRY_VENDOR_ID_LENGTH + 1 ];
        char                devicePIDString [ USB2_MSC_SCSI_INQUIRY_PRODUCT_ID_LENGTH + 1 ];
        char                deviceREVString [ USB2_MSC_SCSI_INQUIRY_REV_LEVEL_LENGTH + 1 ];

        /* Sense data related */

        UINT8               bSenseKey;          /* Sense Key information         */
        UINT8               bASC;               /* Additional Sense Code         */
        UINT8               bASCQ;              /* ASC Qualifier                 */
        BOOL                bSenseValid;        /* Is the last sense data valid  */
        UINT8               bSenseDataLength;   /* Sense data length             */
        UINT8              *pSenseBuffer;       /* Buffer of sense data          */
    } USB2_MSC_LUN_DEVICE;

    /******* usb2Msc.c exported routines - START *****/

    void usb2MscFixupAsciiString
    (
        char   *string,
        int     length
    );

    BOOL usb2MscIsEndpointHalted
    (
        USB2_MSC_DEVICE    *pMscDevice,
        UINT8               bEndpointAddr
    );

    STATUS usb2MscResetEndpoint
    (
        USB2_MSC_DEVICE    *pMscDevice,
        UINT8               bEndpointAddr
    );

    USBHST_STATUS usb2MscBulkOutTransfer
    (
        USB2_MSC_DEVICE    *pMscDevice,
        UINT8              *pTransferBuffer,
        UINT32              uRequestedLentgh,
        UINT32             *pActualLength,
        int                 timeout
    );

    USBHST_STATUS usb2MscBulkInTransfer
    (
        USB2_MSC_DEVICE    *pMscDevice,
        UINT8              *pTransferBuffer,
        UINT32              uRequestedLentgh,
        UINT32             *pActualLength,
        int                 timeout
    );

    USBHST_STATUS usb2MscInterruptInTransfer
    (
        USB2_MSC_DEVICE    *pMscDevice,
        UINT8              *pTransferBuffer,
        UINT32              uRequestedLentgh,
        UINT32             *pActualLength,
        int                 timeout
    );

    USB2_MSC_TRANSPORT_STATUS usb2MscTransport
    (
        USB2_MSC_DEVICE                *pMscDevice,
        USB2_MSC_SCSI_COMMAND_INFO     *pCmdInfo,
        USB2_MSC_DATA_TRANSFER_INFO    *pDataInfo
    );

    /******* usb2Msc.c exported routines - END *****/

    /******* usb2MscBBB.c exported routines - START *****/

    STATUS usb2MscBulkOnlyResetEndpoints
    (
        USB2_MSC_DEVICE    *pMscDevice
    );

    STATUS usb2MscBulkOnlyResetRecovery
    (
        USB2_MSC_DEVICE    *pMscDevice
    );

    UINT8 usb2MscBulkOnlyGetMaxLun
    (
        USB2_MSC_DEVICE    *pMscDevice
    );

    USB2_MSC_TRANSPORT_STATUS usb2MscBulkOnlyTransport
    (
        USB2_MSC_DEVICE                *pMscDevice,
        USB2_MSC_SCSI_COMMAND_INFO     *pCmdInfo,
        USB2_MSC_DATA_TRANSFER_INFO    *pDataInfo
    );

    /******* usb2MscBBB.c exported routines - END *****/

    /******* usb2MscCBI.c exported routines - START *****/

    USB2_MSC_TRANSPORT_STATUS usb2MscCBITransport
    (
        USB2_MSC_DEVICE                *pMscDevice,
        USB2_MSC_SCSI_COMMAND_INFO     *pCmdInfo,
        USB2_MSC_DATA_TRANSFER_INFO    *pDataInfo
    );

    /******* usb2MscCBI.c exported routines - START *****/

    /******* usb2MscCommandSet.c exported routines - START *****/

    STATUS usb2MscScsiRequestSense
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscCommandSetTransport
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        USB2_MSC_SCSI_COMMAND_INFO     *pCmdInfo,
        USB2_MSC_DATA_TRANSFER_INFO    *pDataInfo
    );

    STATUS usb2MscScsiInquiry
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscScsiStartStopUnit
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        BOOL                            startStop,
        BOOL                            loadEject,
        UINT8                           powerCondition
    );

    STATUS usb2MscScsiTestUnitReady
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscScsiCheckReady
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscScsiReadFormatCapacities
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        UINT16                          allocationLen
    );

    STATUS usb2MscScsiReadCapacity10
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscScsiFormatUnit
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        BOOL                            cmpDefectList,
        int                             defListFormat,
        int                             vendorUnique,
        int                             interleave,
        UINT8                          *buffer,
        int                             bufLength
    );

    STATUS usb2MscScsiModeSense10
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        UINT8                           bDBD,
        UINT8                           pageControl,
        UINT8                           pageCode,
        UINT16                          allocationLen
    );

    STATUS usb2MscScsiModeSense6
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        UINT8                           bDBD,
        UINT8                           pageControl,
        UINT8                           pageCode,
        UINT8                           allocationLen
    );

    STATUS usb2MscScsiModeSense
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        UINT8                           pageControl,
        UINT8                           pageCode,
        UINT8                           allocationLen
    );

    void usb2MscWriteProtectionCheck
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscScsiRead10
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        int                             startSector,
        int                             numSectors,
        UINT8                          *pTransferBuffer,
        UINT32                         *pTransferSize
    );

    STATUS usb2MscScsiWrite10
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice,
        int                             startSector,
        int                             numSectors,
        UINT8                          *pTransferBuffer,
        UINT32                         *pTransferSize
    );

    STATUS usb2MscStatusCheck
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    /******* usb2MscCommandSet.c exported routines - END *****/

    /******* usb2MscXBD.c exported routines - START *****/

    STATUS usb2MscXbdMount
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscXbdUnmount
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    /******* usb2MscXBD.c exported routines - END *****/

    /******* usb2MscBLK.c exported routines - START *****/

    STATUS usb2MscBlkDevMount
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    STATUS usb2MscBlkDevUnmount
    (
        USB2_MSC_LUN_DEVICE            *pMscLunDevice
    );

    /******* usb2MscBLK.c exported routines - END *****/

    /******* usb2MscDirectAccess.c exported routines - START *****/

    STATUS usb2MscDirectAccessInit (void);

    STATUS usb2MscDirectAccessUnInit
    (
        void
    );

    STATUS usb2MscDirectAccessDeviceAdd
    (
        USB2_MSC_DEVICE                *pMscDevice
    );

    STATUS usb2MscDirectAccessDeviceRemove
    (
        USB2_MSC_DEVICE                *pMscDevice
    );

    /******* usb2MscDirectAccess.c exported routines - END *****/

    /******* usb2MscCompliance.c exported routines - START *****/

    STATUS usb2MscComplianceTestDeviceAdd
    (
        USB2_MSC_DEVICE                *pMscDevice,
        UINT8                           lun
    );

    STATUS usb2MscComplianceTestDeviceRemove
    (
        USB2_MSC_DEVICE                *pMscDevice,
        UINT8                           lun
    );

    /******* usb2MscCompliance.c exported routines - END *****/

#ifdef __cplusplus
}
#endif
#endif  /* __INCusb2MscPh */

