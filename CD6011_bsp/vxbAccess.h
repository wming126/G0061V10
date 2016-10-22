/* vxbAccess.h - vxBus access routines header file */

/*
 * Copyright (c) 2005-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01p,31jul08,h_k  fixed dependency between drivers and vxbPci. (CQ:125581)
01o,10jun08,h_k  removed vxbAccessList structure.
01n,01may08,h_k  added vxbPciDevCfgRead/vxbPciDevCfgWrite.
01m,14apr08,h_k  disabled legacy access support for all architectures.
01l,20feb08,h_k  changed VXB_HANDLE_IO and ORDERED to optimize the I-cache
                 line usages on PPC.
01k,18jul07,h_k  corrected VXB_HANDLE_IO, VXB_HANDLE_ORDERED and
                 VXB_HANDLE_SWAP offsets for SH.
01j,06jul07,wap  Disable legacy access support for XSCALE
01i,04jul07,wap  Add special option decoding macros
01h,12jun07,tor  remove VIRT_ADDR
01g,04may07,wap  Convert to new register access API
01f,01jun06,wap  Add some utility macros
01e,29sep05,mdo  Fix gnu warnings
01d,20sep05,pdg  Fix for vxbus access routines errors (SPR #112197)
01c,10aug05,mdo  Phase in new access method
01b,01aug05,mdo Updating bus access methods
01a,15Jul05,gpd written
*/

#ifndef __INCvxbAccessh
#define __INCvxbAccessh

#ifdef __cplusplus
extern "C" {
#endif


#include <vxWorks.h>
#include <vxBusLib.h>

    /* defines */

    /* standard access methods */
#define VXB_ACCESS_PROBE            0x00000001
#define VXB_ACCESS_REG_READ8        0x00000002
#define VXB_ACCESS_REG_READ16       0x00000003
#define VXB_ACCESS_REG_READ32       0x00000004
#define VXB_ACCESS_REG_READ64       0x00000005
#define VXB_ACCESS_REG_WRITE8       0x00000006
#define VXB_ACCESS_REG_WRITE16      0x00000007
#define VXB_ACCESS_REG_WRITE32      0x00000008
#define VXB_ACCESS_REG_WRITE64      0x00000009
#define VXB_ACCESS_VOLREG_WRITE     0x0000000a
#define VXB_ACCESS_VOLREG_READ      0x0000000b
#define VXB_ACCESS_INT_CONNECT      0x0000000c
#define VXB_ACCESS_INT_DISCONN      0x0000000d
#define VXB_ACCESS_INT_VEC_GET      0x0000000e
#define VXB_ACCESS_INT_ENABLE       0x0000000f
#define VXB_ACCESS_INT_DISABLE      0x00000010
#define VXB_ACCESS_INT_ACKNOWLEDGE  0x00000011
#define VXB_ACCESS_CFG_READ         0x00000012
#define VXB_ACCESS_CFG_WRITE        0x00000013
#define VXB_ACCESS_VMEMREGION_ALLOC 0x00000014
#define STD_BUS_ACCESS_METHOD_END   0x00000015

    /* macros for endianness conversions */

#define VXBAF_BYTE_ORDER_LE_64      0xe4e40000  /* 11.10.01.00.11.10.01.00 b */
#define VXBAF_BYTE_ORDER_BE_64      0x1a1a0000  /* 00.01.10.11.00.01.10.11 b */
#define VXBAF_BYTE_ORDER_LE_32      0x00e40000  /* 11.10.01.00 b */
#define VXBAF_BYTE_ORDER_BE_32      0x001a0000  /* 00.01.10.11 b */
#define VXBAF_BYTE_ORDER_LE_16      0x00040000  /* 00.00.01.00 b */
#define VXBAF_BYTE_ORDER_BE_16      0x00010000  /* 00.00.00.01 b */

    /* conversion masks */

#define VXBAF_ENDIAN_MASK           0xFFFF0000  /* endianness mask */
#define VXBAF_OPERATION_MASK        0x0000FFFF  /* conversion operation mask */

    /* conversion flag values */

#define VXBAF_CONVERT_BYTE_ORDER    0x00000001  /* convert byte order */
#define VXBAF_CONVERT_SHORT_ORDER   0x00000002  /* convert short order */
#define VXBAF_CONVERT_LONG_ORDER    0x00000004  /* convert long order */
#define VXBAF_CONVERT_LONG_LONG     0x00000008  /* convert long long */
#define VXBAF_CPU_PIPE_FLUSH        0x00000010  /* cpu pipe flush */
#define VXBAF_IO_SPACE_OPERATION    0x00000020  /* IO space operation */
#define VXBAF_BIT_REVERSE_IN_BYTE   0x00000040  /* reverse bits in a byte */
#define VXBAF_NOT_FIRST_BUS     0x00000080  /* 
    * flag indicating that the
    * bus which has
    * received this request
    * is not the first bus on
    * which the driver resides
    */

#define VXBAF_PREVENT_OPTIMIZATION  0x00000100  /* prevent optimization */
#define VXBAF_BYTE_ORDER_KNOWN      0x00000200  /* byte order is not known */
#define VXBAF_CONVERT_OTHER         0x00000400  /* other conversions */

    /*
     * macro which indicates the flags which cannot be optimized. If
     * any new flag is added which is not related to any conversions
     * ensure that it is added here.
     */
#define VXBAF_NON_OPTIMIZED_FLAGS   (VXBAF_PREVENT_OPTIMIZATION |\
                    VXBAF_BYTE_ORDER_KNOWN |\
                    VXBAF_NOT_FIRST_BUS)

    /*
     * operation identifiers in determining the optimized version
     * of access functions
     */

#define OPT_REG_READ8           0x01
#define OPT_REG_READ16          0x02
#define OPT_REG_READ32          0x03
#define OPT_REG_READ64          0x04
#define OPT_REG_WRITE8          0x05
#define OPT_REG_WRITE16         0x06
#define OPT_REG_WRITE32         0x07
#define OPT_REG_WRITE64         0x08
#define OPT_REG_WRITE_READ_BACK_8   0x09
#define OPT_REG_WRITE_READ_BACK_16  0x0A
#define OPT_REG_WRITE_READ_BACK_32  0x0B
#define OPT_REG_WRITE_READ_BACK_64  0x0C

    /* retrieve the upstream device pointer */

#define VXBAF_RETRIEVE_UPSTREAM_BUS_PTR(pDevInfo, pUpstreamDevInfo) \
    {                                                               \
    if (pDevInfo->pParentBus != NULL)                               \
        {                                                           \
        pUpstreamDevInfo = pDevInfo->pParentBus->pCtlr;             \
        }                                                           \
    else                                                            \
        pUpstreamDevInfo = NULL;                                    \
    }

    /* swap 2 bytes */

#define VXBAF_BYTE_SWAP_16(data)                                    \
    ((data) = ((((data) & 0xFF) << 8) | (((data) >> 8) & 0xFF)))

    /* swap 4 bytes */

#define VXBAF_BYTE_SWAP_32(data)                                    \
    ((data) = ((((data) & 0xFF) << 24) | (((data) & 0xFF00) << 8) | \
    (((data) & 0xFF0000) >>8) | (((data) >> 24) & 0xFF)))

#if 0
    /* swap 8 bytes */
#define VXBAF_BYTE_SWAP_64(data)                                     \
    ((data) = ((((data) & 0xFF) << 56) | (((data) & 0xFF00) << 40) | \
    (((data) & 0xFF0000) << 24) | (((data) & 0xFF000000) << 8)     | \
    (((data) >> 8) & 0xFF000000) | (((data) >> 24) & 0xFF0000)     | \
    (((data) >> 40) & 0xFF00) | (((data) >> 56) & 0xFF)))

#else
#define VXBAF_BYTE_SWAP_64(data)
#endif


#define VXB_BYTE_ORDER_CONVERT_16(flags,data,mask)                    \
    {                                                                 \
    /*                                                                \
     * check if the data is in the required byte order. If it is not, \
     * then perform the byte order conversion and update the flags    \
     */                                                               \
    if ((flags & VXBAF_ENDIAN_MASK) != mask)                          \
        {                                                             \
                                                                      \
        /* swap the bytes */                                          \
                                                                      \
        VXBAF_BYTE_SWAP_16(data);                                     \
                                                                      \
        /* clear the fields specified by masks */                     \
                                                                      \
        flags &= ~(VXBAF_ENDIAN_MASK);                                \
                                                                      \
        /* update the mask */                                         \
        flags |= mask;                                                \
                                                                      \
        /* Update the conversion bits */                              \
                                                                      \
        flags ^= (VXBAF_CONVERT_BYTE_ORDER);                          \
        }                                                             \
    }

#define  VXB_BYTE_ORDER_CONVERT_32(flags, data, mask)                 \
    {                                                                 \
    /*                                                                \
     * check if the data is in LE byte order. If it is not,           \
     * then perform the byte order conversion and update the flags    \
     */                                                               \
    if ((flags & VXBAF_ENDIAN_MASK) != mask)                          \
        {                                                             \
                                                                      \
        /* swap the bytes */                                          \
                                                                      \
        VXBAF_BYTE_SWAP_32(data);                                     \
                                                                      \
        /* clear the fields specified by masks */                     \
                                                                      \
        flags &= ~(VXBAF_ENDIAN_MASK);                                \
                                                                      \
        /* update the mask */                                         \
        flags |= mask;                                                \
                                                                      \
        /* Update the conversion bits */                              \
                                                                      \
        flags ^= (VXBAF_CONVERT_BYTE_ORDER | VXBAF_CONVERT_SHORT_ORDER); \
        }                                                             \
    }

#define VXB_BYTE_ORDER_CONVERT_64(flags, data, mask)                  \
    {                                                                 \
    /*                                                                \
     * check if the data is in LE byte order. If it is not,           \
     * then perform the byte order conversion and update the flags    \
     */                                                               \
    if ((flags & VXBAF_ENDIAN_MASK) != mask)                          \
        {                                                             \
                                                                      \
        /* swap the bytes */                                          \
                                                                      \
        VXBAF_BYTE_SWAP_64(data);                                     \
                                                                      \
        /* clear the masks */                                         \
                                                                      \
        flags &= ~(VXBAF_ENDIAN_MASK);                                \
                                                                      \
        /* update the mask */                                         \
        flags |= mask;                                                \
                                                                      \
        /* Update the conversion bits */                              \
                                                                      \
        flags ^= (VXBAF_CONVERT_BYTE_ORDER | VXBAF_CONVERT_SHORT_ORDER |    \
                     VXBAF_CONVERT_LONG_ORDER);                       \
        }                                                             \
    }

    /* typedefs */

    /*
     * VXB_DEVCTL_HDR
     * This structure holds the access identifier and it forms the first member
     * of the structure, the pointer to which is used as argument to
     * VXB_ACCESS_LIST::vxbDevControl
     */
    typedef struct vxbDevCtlHdr
    {
        UINT32  vxbAccessId;    /* IN : bus access identifier */
    } VXB_DEVCTL_HDR, * pVXB_DEVCTL_HDR;

#ifdef  VXB_LEGACY_ACCESS
    /*
     * VXB_ACCESS_LIST
     * This structure holds the details of the functions
     * which can be used for accessing the bus
     * services
     */
    typedef struct vxbAccessList
    {
        UINT32      busID;    /* bus type, for this bus */
        UINT32      vxbVersion;   /* bus subsystem version number */
        void       *pCookie;  /* adtl bus-specific cfg info */

        /* ---------------------------------------- */
        /* PROBE FUNCTION */

        /*
         * this is like vxMemProbe(), but should handle
         * device registers better
         */

        STATUS (*vxbRegisterProbe)
        (
            VXB_DEVICE_ID   devID,      /* device info */
            void       *pRegBase,       /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset,     /* offset, in bytes, of register */
            UINT32      transactionSize,/* register size */
            char    *pProbeDatum,    /* value to write */
            char    *pRetVal,        /* value read back */
            UINT32     *pFlags          /* Flags used */
        );

        /* ---------------------------------------- */
        /* REGISTRATION AND DATA READ/WRITE FUNCTIONS */

        /*
         *
         *  NOTE: The individual routines to read and write specific
         *  data sizes, e.g. registerRead8(), ..., registerWrite64() read or write
         *  the specified size data.  If, for some reason, the routine
         *  cannot make the specified transaction, it returns ERROR
         */

        STATUS (*registerRead8)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT8      *pDataBuf,   /* buffer to put data in */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerRead16)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT16     *pDataBuf,   /* buffer to put data in */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerRead32)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT32     *pDataBuf,   /* buffer to put data in */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerRead64)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT64     *pDataBuf,   /* buffer to put data in */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerWrite8)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT8      *pDataBuf,   /* data to write */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerWrite16)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT16     *pDataBuf,   /* data to write */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerWrite32)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT32     *pDataBuf,   /* data to write */
            UINT32     *pFlags      /* flags */
        );

        STATUS (*registerWrite64)
        (
            VXB_DEVICE_ID   devID,  /* device info */
            void       *pRegBase,   /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset, /* offset, in bytes, of register */
            UINT64     *pDataBuf,   /* data to write */
            UINT32     *pFlags      /* flags */
        );

        /*
         * volatile data register write
         *
         * This routine is used to write to a volatile register, then read
         * back from the same register immediately after writing to it.  Due
         * to possible bus requirements (e.g. read-after-write for posted PCI
         * write transactions), it is advisable to use this routine to read
         * and write volatile registers.
         *
         * Note that this routine, unlike the generic registerRead() and
         * registerWrite() routines, returns ERROR if the specified size
         * cannot be used.  It will not break the transaction into smaller
         * writes, nor read more than was requested.
         */

        STATUS (*volRegWrite)
        (
            VXB_DEVICE_ID   devID,      /* device info */
            void       *pRegBase,       /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset,     /* offset, in bytes, of register */
            UINT32      transactionSize,/* transaction size, in bytes */
            char    *pDataBuf,       /* buffer to read-from/write-to */
            UINT32     *pFlags          /* flags */
        );

        /*
         * volatile data register read
         *
         * This routine is used to read from a volatile register.
         *
         * Note that this routine, unlike the generic registerRead()
         * returns ERROR if the specified size
         * cannot be used.  It will not break the transaction into smaller
         * writes, nor read more than was requested.
         */

        STATUS (*volRegRead)
        (
            VXB_DEVICE_ID   devID,      /* device info */
            void       *pRegBase,       /* VXB_DEVICE::pRegBase[] entry */
            UINT32      byteOffset,     /* offset, in bytes, of register */
            UINT32      transactionSize,/* transaction size, in bytes */
            char    *pDataBuf,       /* buffer to read-from */
            UINT32     *pFlags          /* flags */
        );

        /* ---------------------------------------- */
        /* BUS-SPECIFIC INFORMATION */

        /* read bus-specific configuration information */

        /*
         *  This routine reads the bus configuration space.
         *  Busses such as RapidIO and PCI provide a configuration
         *  space, which contains information about the device and
         *  about the configuration.  This routine provides access
         *  to that information.
         */

        STATUS (*busCfgRead)
        (
            VXB_DEVICE_ID   devID,      /* device info */
            UINT32      byteOffset,     /* offset into cfg space */
            UINT32      transactionSize,/* transaction size, in bytes */
            char    *pDataBuf,       /* buffer to read-from/write-to */
            UINT32     *pFlags          /* flags */
        );

        /* write bus-specific configuration information */

        /*
         *  This routine writes the bus configuration space.  Note that
         *  it may not be possible to write into the configuration space
         *  registers.  Whether this is a posibility depends on both the
         *  bus and the device.
         */

        STATUS (*busCfgWrite)
        (
            VXB_DEVICE_ID   devID,      /* device info */
            UINT32      byteOffset,     /* offset into cfg space */
            UINT32      transactionSize,/* transaction size, in bytes */
            char    *pDataBuf,       /* buffer to read-from/write-to */
            UINT32     *pFlags          /* flags */
        );

        /*
         * The vxbDevControl() routine is called to perform certain
         * actions which are not available in the other busAccessList
         * entry points.  The structure of the call is similar to ioctl,
         * with two arguments: a VXB_DEVICE_ID and information related
         * to the command.  Each command passed to vxbDevControl()
         * is included in a vxbDevCtlHdr structure.  Depending on the
         * specific command, the vxbDevCtlHdr structure may be included
         * as the first element of a more detailed structure specific
         * to that command.
         *
         * Currently, the only supported action supported by
         * vxbDevControl() is interrupt management.  There are five entry
         * points for connecting or disconnecting an ISR, enabling or
         * disabling the interrupt, and acknowledging an interrupt cycle.
         * There is also a routine to retrieve the interrupt vector,
         * which would not normally be used by standard device drivers,
         * but which is typically used internally by VxBus bus type
         * support modules.
         */
        STATUS      (*vxbDevControl)
        (
            VXB_DEVICE_ID   devID,          /* device info */
            pVXB_DEVCTL_HDR pBusDevControl  /* parameter */
        );
    } VXB_ACCESS_LIST, * pVXB_ACCESS_LIST;
#else   /* VXB_LEGACY_ACCESS */
    typedef void    VXB_ACCESS_LIST;
    typedef void    *pVXB_ACCESS_LIST;
#endif  /* VXB_LEGACY_ACCESS */

    /*
     * VXB_ACCESS_INTERRUPT_INFO
     * This structure holds the input/output parameters of vxbIntrConnect(),
     * vxbIntrDisconnect (), vxbIntrEnable () and vxbIntrDisable ()
     * routines
     */
    typedef struct vxbAccessInterruptInfo
    {
        struct vxbDevCtlHdr header;  /* IN : bus access identifier */
        int               intIndex;  /* IN/OUT : index of the interrupt array */
        VOIDFUNCPTR           pISR;  /* IN : Interrupt Service Routine */
        void           *pParameter;  /* IN : parameter to be passed to routine */
    } VXB_ACCESS_INTERRUPT_INFO, * pVXB_ACCESS_INTERRUPT_INFO;

    typedef STATUS (*VXB_FUNC_CFGRDWR_PTR)
    (
        VXB_DEVICE_ID   devID,      /* device info */
        UINT32      byteOffset,     /* offset into cfg space */
        UINT32      transactionSize,/* transaction size, in bytes */
        char    *pDataBuf,       /* buffer to read-from/write-to */
        UINT32     *pFlags          /* flags */
    );

    typedef STATUS (*VXB_FUNC_DEVCTRL_PTR)
    (
        VXB_DEVICE_ID   devID,      /* device info */
        pVXB_DEVCTL_HDR pBusDevControl      /* parameter */
    );
    /*
     * VXB_ACCESS_INT_VECTOR_GET
     * This structure holds the input/output parameters of vxbIntrVecGet () routine
     */
    typedef struct vxbAccessIntVectorGet
    {
        struct vxbDevCtlHdr header; /* IN : bus access identifier */
        int               intIndex; /* IN : index into the interrupt info array */
        VOIDFUNCPTR     pIntVector; /* OUT : interrupt vector information */
    } VXB_ACCESS_INT_VECTOR_GET, * pVXB_ACCESS_INT_VECTOR_GET;

#ifdef  VXB_LEGACY_ACCESS
    extern void optimizeAccessFunction
    (
        UINT32          flags,              /* flags */
        pVXB_ACCESS_LIST pAccess,           /* bus access structure ptr */
        UINT32          operationId         /* operation indicator */
    );
#endif  /* VXB_LEGACY_ACCESS */


    IMPORT UINT64 vxbSwap64 (UINT64);
    IMPORT UINT32 vxbSwap32 (UINT32);
    IMPORT UINT16 vxbSwap16 (UINT16);

    IMPORT UINT8 vxbRead8 (void *, UINT8 *);
    IMPORT UINT16 vxbRead16 (void *, UINT16 *);
    IMPORT UINT32 vxbRead32 (void *, UINT32 *);
    IMPORT UINT64 vxbRead64 (void *, UINT64 *);
    IMPORT void vxbWrite8 (void *, UINT8 *, UINT8);
    IMPORT void vxbWrite16 (void *, UINT16 *, UINT16);
    IMPORT void vxbWrite32 (void *, UINT32 *, UINT32);
    IMPORT void vxbWrite64 (void *, UINT64 *, UINT64);

    IMPORT STATUS vxbPciDevCfgRead
    (
        VXB_DEVICE_ID       pDev,                   /* device info */
        UINT32              byteOffset,             /* offset into cfg space */
        UINT32              transactionSize,        /* transaction size */
        void               *pDataBuf                /* buffer to read/write */
    );

    IMPORT STATUS vxbPciDevCfgWrite
    (
        VXB_DEVICE_ID       pDev,                   /* device info */
        UINT32              byteOffset,             /* offset into cfg space */
        UINT32              transactionSize,        /* transaction size */
        UINT32              data                    /* data to write */
    );

    IMPORT STATUS (* _func_vxbPciDevCfgRead)
    (
        VXB_DEVICE_ID       pDev,                   /* device info */
        UINT32              byteOffset,             /* offset into cfg space */
        UINT32              transactionSize,        /* transaction size */
        void               *pDataBuf                /* buffer to read/write */
    );

    IMPORT STATUS (* _func_vxbPciDevCfgWrite)
    (
        VXB_DEVICE_ID       pDev,                   /* device info */
        UINT32              byteOffset,             /* offset into cfg space */
        UINT32              transactionSize,        /* transaction size */
        UINT32              data                    /* data to write */
    );

    IMPORT STATUS vxbRegMap (VXB_DEVICE_ID, int, void **);

    /*
     * Possible types of pre-defined I/O operations:
     *
     * VXB_HANDLE_MEM:      memory mapped access
     * VXB_HANDLE_IO:       i/o space access (strict ordering implied)
     * VXB_HANDLE_ORDERED:  memory mapped access, ordering enforced
     *
     * Each of these can also be qualified with:
     *
     * VXB_HANDLE_SWAP()
     *
     * To obtain the byte-swapped version of one of these routines.
     * For example:
     *
     * handle = VXB_HANDLE_SWAP(VXB_HANDLE_IO);
     *
     * Note that for 8 bit access routines, the VXB_HANDLE_SWAP() qualifier
     * has no effect.
     */

#define VXB_HANDLE_MEM          0

#if (CPU_FAMILY == PPC)
#define VXB_HANDLE_IO           8
#define VXB_HANDLE_ORDERED      24
#define VXB_HANDLE_SWAP(x)  ((x) + 48)
#elif (CPU_FAMILY == I80X86) || (CPU_FAMILY == SH)
#define VXB_HANDLE_IO           16
#define VXB_HANDLE_ORDERED      32
#define VXB_HANDLE_SWAP(x)  ((x) + 48)
#else
#define VXB_HANDLE_IO           32
#define VXB_HANDLE_ORDERED      64
#define VXB_HANDLE_SWAP(x)  ((x) + 96)
#endif

#define VXB_HANDLE_OP_READ  0x00
#define VXB_HANDLE_OP_WRITE 0x10
#define VXB_HANDLE_WIDTH(x) ((x) & 0x0F)
#define VXB_HANDLE_OP(x)    ((x) & 0xF0)

    /*
     * General byte order swapping functions.
     */
#define bswap16(x)      ((LSB(x) << 8) | MSB(x))
#define bswap32(x)      LONGSWAP((UINT32)(x))
#define bswap64(x)  /* not yet */

#if _BYTE_ORDER == _LITTLE_ENDIAN
#define htobe16(x)      bswap16((x))
#define htobe32(x)      bswap32((x))
#define htobe64(x)      bswap64((x))
#define htole16(x)      ((UINT16)(x))
#define htole32(x)      ((UINT32)(x))
#define htole64(x)      ((UINT64)(x))

#define be16toh(x)      bswap16((x))
#define be32toh(x)      bswap32((x))
#define be64toh(x)      bswap64((x))
#define le16toh(x)      ((UINT16)(x))
#define le32toh(x)      ((UINT32)(x))
#define le64toh(x)      ((UINT64)(x))
#else /* _BYTE_ORDER != _LITTLE_ENDIAN */
#define htobe16(x)      ((UINT16)(x))
#define htobe32(x)      ((UINT32)(x))
#define htobe64(x)      ((UINT64)(x))
#define htole16(x)      bswap16((x))
#define htole32(x)      bswap32((x))
#define htole64(x)      bswap64((x))

#define be16toh(x)      ((UINT16)(x))
#define be32toh(x)      ((UINT32)(x))
#define be64toh(x)      ((UINT64)(x))
#define le16toh(x)      bswap16((x))
#define le32toh(x)      bswap32((x))
#define le64toh(x)      bswap64((x))
#endif /* _BYTE_ORDER == _LITTLE_ENDIAN */

#ifdef  VXB_LEGACY_ACCESS
#define VXB_PCI_BUS_CFG_READ(pDev, byteOffset, transactionSize, data)   \
    pDev->pAccess->busCfgRead (pDev, byteOffset, transactionSize,   \
                   (void *) &data, NULL)

#define VXB_PCI_BUS_CFG_WRITE(pDev, byteOffset, transactionSize, data)  \
    pDev->pAccess->busCfgWrite (pDev, byteOffset, transactionSize,  \
                (void *) &data, NULL)

#else   /* VXB_LEGACY_ACCESS */

#define VXB_PCI_BUS_CFG_READ(pDev, byteOffset, transactionSize, data)   \
    ((_func_vxbPciDevCfgRead == NULL) ? ERROR :             \
     _func_vxbPciDevCfgRead (pDev, byteOffset, transactionSize,     \
                 (void *) &data))

#define VXB_PCI_BUS_CFG_WRITE(pDev, byteOffset, transactionSize, data)  \
    ((_func_vxbPciDevCfgWrite == NULL) ? ERROR :            \
     _func_vxbPciDevCfgWrite (pDev, byteOffset, transactionSize,    \
                  (UINT32) data))

#endif  /* VXB_LEGACY_ACCESS */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbAccessh */

