/* mkboot.c - program to make a bootable device (fd, ata, tffs) */

/*
 * Copyright (c) 1989, 2001-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02a,12oct09,j_z  updated AHCI vxBus driver support.(WIND00184020)
01z,24jul09,scm  Added AHCI support.
01y,27sep08,j_z  add support for INCLUDE_DRV_STORAGE_INTEL_ICH
01x,17sep07,kab  apigen cleanup
01w,18may06,dee	 SPR:117483, WIND00057492, WIND00057622
		 make compatible with XBD filesystems for 6.4
01v,14oct04,jb	 Fix compiler warnings
01u,18jul02,jkf	 SPR#79650, honor newer partition types, now will
		 avoid corrupting FAT32 partitions, added comments,
		 support big sectors and use malloc to use less stack
01t,26jun02,hdn/ dmh  updated revision no. in bootStrap[]
01s,25jun02,hdn	 replaced bootrom_uncmp with bootrom.bin
01r,04dec01,jkf	 using dosFsVolDescGet to see if device exists
01q,24may00,jkf	 new bootStrap 1.5, fixed SPR#31310,31445,30280.
01p,12nov99,jkf	 Added a bootStrap that has support for VxWorks long 
		 filename (VXEXT 1.0/1.1) matches vxsys.asm 1.4 version. 
		 Added comments.  Removed boot disk value update, since 
		 BIOS hands us the boot disk in dl, when the bootstrap is 
		 called. by convention.	 SPR#7452
01o,01oct99,hdn	 added support for binary file.
01n,08apr99,jkf	 corrected warning, SPR#26453.
01m,27aug98,dat	 added config.h, #ifdef INCLUDE_TFFS.
01l,04mar98,hdn	 fixed a problem in mkbootTffs().
01k,03mar98,kbw	 made changes to man page text for mkbootTffs
01j,15dec97,hdn	 added support for TFFS.
01i,15feb96,hdn	 renamed to mkboot.c
01h,12jun95,hdn	 added support for ATA. added mkbootFd and mkbootAta.
01g,24jan95,jdi	 doc cleanup.
01f,25oct94,hdn	 added fdRawio() instead of using raw file system.
		 swapped 1st and 2nd parameter of vxsys().
01e,28may94,hdn	 updated the boot sector to DOS version.
01d,27jan94,hdn	 changed the entry point 0x10000 to 0x8000.
01c,16nov93,hdn	 changed name of the boot image "bootrom.dat" to "bootrom.sys".
01b,07nov93,hdn	 adopted Dave Fraser's idea.
01a,12oct93,hdn	 written
*/

/*
DESCRIPTION
This library creates a boot diskette or disk.

mkbootFd() creates a boot floppy disk.
mkbootAta() creates a boot IDE/ATA disk.
mkbootAhci() creates a boot vxBus AHCI disk.  

mkMbr() creates MasterBootRecord on sector 0 of IDE/ATA disk.
mkMbrAhci() creates MasterBootRecord on sector 0 of vxBus AHCI disk.

*/

#include <vxWorks.h>
#include <config.h>
#include <errnoLib.h>
#include <ioLib.h>
#include <stdio.h>
#include <string.h>
#include <usrLib.h>
#include <dosFsLib.h>
#include <usrFdiskPartLib.h>
#include <drv/xbd/xbd.h>
#include <xbdBlkDev.h>
#include <fsMonitor.h>

#ifdef INCLUDE_FD
#   include <drv/fdisk/nec765Fd.h>
#endif /*INCLUDE_FD */
#ifdef INCLUDE_ATA
#   include <drv/hdisk/ataDrv.h>
#endif /*INCLUDE_ATA */
#ifdef INCLUDE_VXBUS
#   include <vxBusLib.h>
#endif /* INCLUDE_VXBUS */
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
#include <../src/hwif/h/storage/vxbIntelIchStorage.h>
#endif /* INCLUDE_DRV_STORAGE_INTEL_ICH */
#ifdef INCLUDE_DRV_STORAGE_INTEL_AHCI
#include <hwif/util/vxbParamSys.h>
#include <../src/hwif/h/storage/vxbIntelAhciStorage.h>
#endif /* INCLUDE_DRV_STORAGE_INTEL_AHCI */
#ifdef INCLUDE_TFFS
#   include <tffs/tffsDrv.h>
#endif /*INCLUDE_TFFS */

#define VXSYS_FD	0		/* floppy disk */
#define VXSYS_ATA	1		/* ATA disk */
#define VXSYS_TFFS	2		/* flash memory: DOC */
#define VXSYS_AHCI	3		/* AHCI SATA disk */
#define VXSYS_DOSDEV	"/boot"
#define VXSYS_RAWDEV0	VXSYS_DOSDEV ":0"
#define VXSYS_RAWDEV1	VXSYS_DOSDEV ":1"

/* 
 * VXLONGNAMES will store the "." confusing the bootstrap, FAT/VFAT wont.
 * so we remove the "." for the bootStrap code on longnames detection.
 */
/* MUST MATCH string in bootStrap array.. */
#define VXSYS_FILE     VXSYS_DOSDEV "/BOOTROM.SYS"
#define VXSYS_FILE_VXEXT VXSYS_DOSDEV "/BOOTROM SYS"
#define DOS		"DOS"
#define VXEXT		"VXEXT"
#define FAT12		"FAT12	 "   /* must be 8 characters exactly */
#define FAT16		"FAT16	 "   /* must be 8 characters exactly */

#define MAX_SECTOR_SIZE	 (512)

/* 448 bytes for bootstrap, + 2 bytes (55aa) signature */
#define BOOTSTRAP_AND_SIGNATURE 450  

/* use this macro to put the relative jump to offset 0x3E
 * into the boot sector and copy the vxWorks bootstrap code
 * into the boot sector code area
 */
#define BUILD_BOOTSEC(x) \
    { /* modify first 3 bytes and copy bootstrap to offset 0x3E */ \
    x[0] = 0xeb;   /* x86 relative jump inst */	 \
    x[1] = 0x3c;   /* rel address for jmp */	 \
    x[2] = 0x90;   /* x86 nop */		 \
    bcopy ((const char *)bootStrap, (char *)&x[0x3e], sizeof (bootStrap));  \
    }

/* global */

int vxsysDebug = 0;

#ifdef INCLUDE_ATA
IMPORT ATA_CTRL	 ataCtrl [ATA_MAX_CTRLS]; 
#endif

#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
LOCAL  ATA_CTRL * pIchAtaCtrl;
#endif

#ifdef INCLUDE_DRV_STORAGE_INTEL_AHCI
IMPORT STATUS ahciRawio(AHCI_DRV_CTRL *, int, AHCI_RAW *);
IMPORT BLK_DEV *ahciDevCreate(AHCI_DRV_CTRL *, int, int, int);
#endif

#if defined(INCLUDE_ATA) && defined(INCLUDE_DRV_STORAGE_INTEL_ICH)
#error can't define INCLUDE_ATA and INCLUDE_DRV_STORAGE_INTEL_ICH at the same time
#endif

/* local */
/*
 * This boot code is located in the Partition Boot Record.
 * The PBR is either located in sector 0, or in a sector
 * that is identified in the partition table.  A partition table
 * is not always used.  Where a partition table is not used, as in 
 * removable CF devices, or a floppy, sector 0 is the PBB.
 * 
 * This code is always located at offset 0x3E in the appropriate
 * sector.
 *
 * This boot code load the file "bootrom.sys" into memory and executes the
 * loaded program.
 */
LOCAL const unsigned char bootStrap[BOOTSTRAP_AND_SIGNATURE] =
    {
    0xFA, 0x88, 0x16, 0x24, 0x7C, 0xB4, 0x08, 0xCD, 
    0x13, 0x72, 0x11, 0x83, 0xE1, 0x3F, 0x89, 0x0E, 
    0x18, 0x7C, 0xFE, 0xC6, 0x32, 0xD2, 0x86, 0xF2, 
    0x89, 0x16, 0x1A, 0x7C, 0xFA, 0x8C, 0xC8, 0x8E, 
    0xD8, 0x8E, 0xC0, 0xFC, 0x8E, 0xD0, 0xBC, 0xFE, 
    0x7B, 0xFB, 0xBE, 0xE1, 0x7D, 0xE8, 0x14, 0x01, 
    0x33, 0xDB, 0x8B, 0xC3, 0x8B, 0xD3, 0xA0, 0x10, 
    0x7C, 0xF7, 0x26, 0x16, 0x7C, 0x8B, 0x0E, 0x0E, 
    0x7C, 0x03, 0x0E, 0x1C, 0x7C, 0x13, 0x16, 0x1E, 
    0x7C, 0x03, 0xC8, 0x13, 0xD3, 0x89, 0x0E, 0x00, 
    0x7B, 0x89, 0x16, 0x02, 0x7B, 0xBE, 0x03, 0x7C, 
    0xBF, 0xF9, 0x7D, 0xC7, 0x06, 0x36, 0x7C, 0x20, 
    0x00, 0xB9, 0x05, 0x00, 0xF3, 0xA6, 0x75, 0x06, 
    0xC7, 0x06, 0x36, 0x7C, 0x40, 0x00, 0xA1, 0x36, 
    0x7C, 0xF7, 0x26, 0x11, 0x7C, 0x8B, 0x36, 0x0B, 
    0x7C, 0x03, 0xC6, 0x48, 0xF7, 0xF6, 0x8B, 0xC8, 
    0x51, 0xA1, 0x00, 0x7B, 0x8B, 0x16, 0x02, 0x7B, 
    0xBB, 0x00, 0x7E, 0xE8, 0xD0, 0x00, 0x73, 0x03, 
    0xE9, 0xA5, 0x00, 0x8B, 0x16, 0x0B, 0x7C, 0xBF, 
    0x00, 0x7E, 0xBE, 0xEB, 0x7D, 0x57, 0xB9, 0x0B, 
    0x00, 0xF3, 0xA6, 0x5F, 0x74, 0x1C, 0x03, 0x3E, 
    0x36, 0x7C, 0x2B, 0x16, 0x36, 0x7C, 0x75, 0xEA, 
    0x83, 0x06, 0x00, 0x7B, 0x01, 0x83, 0x16, 0x02, 
    0x7B, 0x00, 0x59, 0xE2, 0xC3, 0xBE, 0xEA, 0x7D, 
    0xEB, 0x79, 0x59, 0x01, 0x0E, 0x00, 0x7B, 0x83, 
    0x16, 0x02, 0x7B, 0x00, 0x33, 0xC9, 0xBB, 0x1C, 
    0x00, 0x83, 0x3E, 0x36, 0x7C, 0x40, 0x75, 0x03, 
    0x83, 0xC3, 0x20, 0x8B, 0x01, 0x43, 0x43, 0x8B, 
    0x11, 0xF7, 0x36, 0x0B, 0x7C, 0x40, 0xA3, 0x04, 
    0x7B, 0x83, 0xEB, 0x04, 0x8B, 0x01, 0x48, 0x48, 
    0x8A, 0x0E, 0x0D, 0x7C, 0xF7, 0xE1, 0x03, 0x06, 
    0x00, 0x7B, 0x13, 0x16, 0x02, 0x7B, 0xBB, 0x00, 
    0x08, 0x8E, 0xC3, 0x33, 0xDB, 0x50, 0x52, 0xE8, 
    0x54, 0x00, 0x5A, 0x58, 0x72, 0x2A, 0xBE, 0xF7, 
    0x7D, 0xE8, 0x30, 0x00, 0xFF, 0x0E, 0x04, 0x7B, 
    0x74, 0x0D, 0x83, 0xC0, 0x01, 0x83, 0xD2, 0x00, 
    0x8C, 0xC3, 0x83, 0xC3, 0x20, 0xEB, 0xDA, 0xA0, 
    0x24, 0x7C, 0x24, 0x80, 0x75, 0x06, 0xBA, 0xF2, 
    0x03, 0x32, 0xC0, 0xEE, 0xFF, 0x2E, 0x7E, 0x7D, 
    0xBE, 0xE6, 0x7D, 0xE8, 0x06, 0x00, 0xEB, 0xFE, 
    0x00, 0x00, 0x00, 0x08, 0x53, 0x50, 0x80, 0x3E, 
    0xE0, 0x7D, 0x00, 0x75, 0x0E, 0xAC, 0x0A, 0xC0, 
    0x74, 0x09, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 
    0x10, 0xEB, 0xF2, 0x58, 0x5B, 0xC3, 0x89, 0x1E, 
    0x06, 0x7B, 0x8B, 0x1E, 0x18, 0x7C, 0xF7, 0xF3, 
    0x42, 0x8B, 0xDA, 0x33, 0xD2, 0xF7, 0x36, 0x1A, 
    0x7C, 0x86, 0xE0, 0xB1, 0x06, 0xD2, 0xE0, 0x91, 
    0x0A, 0xCB, 0x8A, 0xF2, 0xBB, 0x05, 0x00, 0x53, 
    0x8B, 0x1E, 0x06, 0x7B, 0x8A, 0x16, 0x24, 0x7C, 
    0xB8, 0x01, 0x02, 0x51, 0x52, 0xCD, 0x13, 0x5A, 
    0x59, 0x72, 0x03, 0x5B, 0xF8, 0xC3, 0x33, 0xC0, 
    0xCD, 0x13, 0x5B, 0xFE, 0xCF, 0x75, 0xE0, 0xF9, 
    0xEB, 0xF3, 0x00, 0x56, 0x31, 0x2E, 0x36, 0x00, 
    0x21, 0x52, 0x64, 0x00, 0x21, 0x42, 0x4F, 0x4F, 
    0x54, 0x52, 0x4F, 0x4D, 0x20, 0x53, 0x59, 0x53, 
    0x00, 0x2B, 0x00, 0x56, 0x58, 0x45, 0x58, 0x54, 
    0x55, 0xAA, 
    };	/* VxSYS 1.6 */

LOCAL const unsigned char MBR[] =
    { /* taken from FreeBSD 4.x */
    0xfc, 0x31, 0xc0, 0x8e, 0xc0, 0x8e, 0xd8, 0x8e,
    0xd0, 0xbc, 0x00, 0x7c, 0x89, 0xe6, 0xbf, 0x00,
    0x06, 0xb9, 0x00, 0x01, 0xf3, 0xa5, 0x89, 0xfd,
    0xb1, 0x08, 0xf3, 0xab, 0xfe, 0x45, 0xf2, 0xe9,
    0x00, 0x8a, 0xf6, 0x46, 0xbb, 0x20, 0x75, 0x04,
    0x84, 0xd2, 0x78, 0x03, 0x8a, 0x56, 0xba, 0x88,
    0x56, 0x00, 0xe8, 0xf6, 0x00, 0x52, 0xbb, 0xc2,
    0x07, 0x31, 0xd2, 0x88, 0x6f, 0xfc, 0x0f, 0xa3,
    0x56, 0xbb, 0x73, 0x1b, 0x8a, 0x07, 0xbf, 0x7d,
    0x07, 0xb1, 0x03, 0xf2, 0xae, 0x74, 0x10, 0xb1,
    0x0c, 0xf2, 0xae, 0x75, 0x03, 0x83, 0xc7, 0x0c,
    0x8a, 0x0d, 0x01, 0xcf, 0xe8, 0xbd, 0x00, 0x42,
    0x80, 0xc3, 0x10, 0x73, 0xd6, 0x58, 0x2c, 0x7f,
    0x3a, 0x06, 0x75, 0x04, 0x72, 0x05, 0x48, 0x74,
    0x0d, 0x30, 0xc0, 0x04, 0xb0, 0x88, 0x46, 0xb8,
    0xbf, 0xb2, 0x07, 0xe8, 0x9e, 0x00, 0xbe, 0x71,
    0x07, 0xe8, 0xaa, 0x00, 0x8a, 0x56, 0xb9, 0x4e,
    0xe8, 0x86, 0x00, 0x30, 0xe4, 0xcd, 0x1a, 0x89,
    0xd7, 0x03, 0x7e, 0xbc, 0xb4, 0x01, 0xcd, 0x16,
    0x75, 0x12, 0x30, 0xe4, 0xcd, 0x1a, 0x39, 0xfa,
    0x72, 0xf2, 0x8a, 0x46, 0xb9, 0xeb, 0x15, 0xb0,
    0x07, 0xe8, 0x8e, 0x00, 0x30, 0xe4, 0xcd, 0x16,
    0x88, 0xe0, 0x3c, 0x1c, 0x74, 0xec, 0x2c, 0x3b,
    0x3c, 0x04, 0x77, 0xeb, 0x98, 0x0f, 0xa3, 0x46,
    0x0c, 0x73, 0xe4, 0x88, 0x46, 0xb9, 0xbe, 0x00,
    0x08, 0x8a, 0x14, 0x89, 0xf3, 0x3c, 0x04, 0x9c,
    0x74, 0x0a, 0xc0, 0xe0, 0x04, 0x05, 0xbe, 0x07,
    0x93, 0xc6, 0x07, 0x80, 0x53, 0xf6, 0x46, 0xbb,
    0x40, 0x75, 0x08, 0xbb, 0x00, 0x06, 0xb4, 0x03,
    0xe8, 0x59, 0x00, 0x5e, 0x9d, 0x75, 0x06, 0x8a,
    0x56, 0xb8, 0x80, 0xea, 0x30, 0xbb, 0x00, 0x7c,
    0xb4, 0x02, 0xe8, 0x47, 0x00, 0x72, 0xa8, 0x81,
    0xbf, 0xfe, 0x01, 0x55, 0xaa, 0x75, 0xa0, 0x56,
    0xbe, 0x7b, 0x07, 0xe8, 0x1a, 0x00, 0x5e, 0xff,
    0xe3, 0xb0, 0x46, 0xe8, 0x24, 0x00, 0xb0, 0x31,
    0x00, 0xd0, 0xeb, 0x17, 0x0f, 0xab, 0x56, 0x0c,
    0xbe, 0x6e, 0x07, 0xe8, 0xeb, 0xff, 0x89, 0xfe,
    0xe8, 0x03, 0x00, 0xbe, 0x7b, 0x07, 0xac, 0xa8,
    0x80, 0x75, 0x05, 0xe8, 0x04, 0x00, 0xeb, 0xf6,
    0x24, 0x7f, 0x53, 0xbb, 0x07, 0x00, 0xb4, 0x0e,
    0xcd, 0x10, 0x5b, 0xc3, 0x8a, 0x74, 0x01, 0x8b,
    0x4c, 0x02, 0xb0, 0x01, 0x56, 0x89, 0xe7, 0xf6,
    0x46, 0xbb, 0x80, 0x74, 0x13, 0x66, 0x6a, 0x00,
    0x66, 0xff, 0x74, 0x08, 0x06, 0x53, 0x6a, 0x01,
    0x6a, 0x10, 0x89, 0xe6, 0x48, 0x80, 0xcc, 0x40,
    0xcd, 0x13, 0x89, 0xfc, 0x5e, 0xc3, 0x20, 0x20,
    0xa0, 0x0a, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c,
    0x74, 0x3a, 0xa0, 0x0d, 0x8a, 0x00, 0x05, 0x0f,
    0x01, 0x04, 0x06, 0x0b, 0x0c, 0x0e, 0x63, 0x83,
    0x9f, 0xa5, 0xa6, 0xa9, 0x0d, 0x0e, 0x0d, 0x0c,
    0x0b, 0x0a, 0x09, 0x0b, 0x0e, 0x16, 0x11, 0x14,
    0x13, 0x3f, 0xbf, 0x44, 0x4f, 0xd3, 0x55, 0x4e,
    0x49, 0xd8, 0x4c, 0x69, 0x6e, 0x75, 0xf8, 0x46,
    0x72, 0x65, 0x65, 0x42, 0x53, 0xc4, 0x90, 0x90,
    0x66, 0xbb, 0x44, 0x72, 0x69, 0x76, 0x65, 0x20,
    0xb1, 0x00, 0x80, 0x0f, 0xb6, 0x00,
    };

/* forward declaration */

LOCAL STATUS vxsys (int device, int ctrl, int drive, int fdType, char *in);
LOCAL STATUS findSubString ( char *src, char *sub);
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
IMPORT STATUS  ichAtaRawio (int ctrl, int drive, ATA_RAW *pAtaRaw);
IMPORT ATA_CTRL * ichAtaGetCtrl( int ctl );
#endif

#ifdef INCLUDE_FD
/*******************************************************************************
*
* mkbootFd - create a boot floppy disk from a specified file
*
* This command creates a boot floppy disk from a specified file
*
* EXAMPLES:
* The following example makes a bootable floppy disk from the file named
* `bootrom.bin' to the floppy drive 0: "a:", which contains a type 0 diskette.
* .CS
*     -> mkbootFd 0, 0, "bootrom.bin"
* .CE
*
* RETURNS:
* OK, or ERROR if there is an error copying from <in> to the disk.
*
*/

STATUS mkbootFd 
    (
    int drive,			/* drive number:	(0 - 3)	       */
    int fdType,			/* type of floppy disk: (0 - 1)	       */
    char *in			/* name of file to read: "bootrom.bin" */
    )
    {
    return (vxsys (VXSYS_FD, 0, drive, fdType, in));
    }
#endif /* INCLUDE_FD */

#if defined(INCLUDE_ATA) || defined(INCLUDE_DRV_STORAGE_INTEL_ICH)
/*******************************************************************************
*
* mkbootAta - create a boot ATA disk from a specified file
*
* This command creates a ATA boot disk from a specified file
* Note that the disk should have a FAT16 or a FAT12 volume.
* FAT32 volumes are not supported.  
*
* EXAMPLES:
* The following example makes a bootable hard disk from the file named
* `bootrom.bin' to the ATA ctrl 0, drive 0: "c:" drive.
* .CS
*     -> mkbootAta 0, 0, "bootrom.bin"
* .CE
*
* RETURNS:
* OK, or ERROR if there is an error copying from <in> to the disk.
*
*/

STATUS mkbootAta 
    (
    int ctrl,			/* controller number:	(0 - 1)		*/
    int drive,			/* drive number:	(0 - 1)		*/
    char *in			/* name of file to read: "bootrom.bin"	*/
    )
    {
    return (vxsys (VXSYS_ATA, ctrl, drive, 0, in));
    }
#endif /* INCLUDE_ATA || INCLUDE_DRV_STORAGE_INTEL_ICH*/

#ifdef INCLUDE_DRV_STORAGE_INTEL_AHCI
/*******************************************************************************
*
* mkbootAhci - create a boot AHCI disk from a specified file
*
* This command creates a AHCI boot disk from a specified file
* Note that the disk should have a FAT16 or a FAT12 volume.
* FAT32 volumes are not supported.  
*
* EXAMPLES:
* The following example makes a bootable hard disk from the file named
* `bootrom.bin' to the AHCI ctrl 0, drive 0: "c:" drive.
* .CS
*     -> mkbootAhci 0, 0, "bootrom.bin"
* .CE
*
* RETURNS:
* OK, or ERROR if there is an error copying from <in> to the disk.
*
*/

STATUS mkbootAhci 
    (
    int ctrl,	/* controller number:	(0 - 6), most board only have one controller */
    int drive,	/* drive number:	(0 - 32) */
    char *in	/* name of file to read: "bootrom.bin" */
    )
    {
    return (vxsys (VXSYS_AHCI, ctrl, drive, 0, in));
    }
#endif /* INCLUDE_DRV_STORAGE_INTEL_AHCI */

#ifdef INCLUDE_TFFS
/*******************************************************************************
*
* mkbootTffs - make the specified flash device a boot device
*
* This command sets up the flash device, <drive>, as a boot device.  
* The <removable> parameter expects a 1 if the flash device is removable 
* or a 0 if it is not. The <in> parameter specifies the name of the boot file.
*
* Note that the disk should have a FAT16 or a FAT12 volume.
* FAT32 volumes are not supported.  
*
* EXAMPLES:
* In the following example, the first zero identifies drive zero as the flash
* device to be made into a boot device.	 The second zero indicates that the 
* flash is not removable.  The 'bootrom.bin' parameter specifies the name 
* of the boot file.
* .CS
*     -> mkbootTffs 0, 0, "bootrom.bin"
* .CE
*
* RETURNS:
* OK, or ERROR if there is an error copying from <in> to the disk.
*
*/

STATUS mkbootTffs 
    (
    int drive,			/* drive number: (0 - TFFS_MAX_DRIVES - 1) */
    int removable,		/* removable or not: (TRUE - FALSE)	 */
    char *in			/* name of file to read: "bootrom.bin" */
    )
    {
    return (vxsys (VXSYS_TFFS, 0, drive, removable, in));
    }
#endif /*INCLUDE_TFFS */

/*******************************************************************************
*
* vxsys - create a boot device from a specified file
*
* This command changes a boot sector and copies the text and data of 
* a specified file to the output device.
*
* RETURNS:
* OK, or
* ERROR if <in> or <out> cannot be opened/created, or if there is an
* error copying from <in> to <out>.
*
*/

LOCAL STATUS vxsys 
    (
    int device,			/* device type:		(0 - 2) */
    int ctrl,			/* controller number:	(0 - 1) */
    int drive,			/* drive number:	(0 - 3) */
    int fdType,			/* type of floppy disk: (0 - 1) */
    char *in			/* name of file to read: "xxx"	*/
    )
    {
    BLK_DEV *pBlkDev;
    int inFd = 0;
    int outFd = 0;
    struct stat pStat;
    unsigned char *	lbaSectorZero;
    unsigned char *	dosVolBootSec;
    device_t		blkDevice_t = NULLDEV;
    STATUS		ret_code = ERROR;
    BOOL		useLongNames = FALSE;

    /* allocate buffers */

    lbaSectorZero = malloc (MAX_SECTOR_SIZE);
    dosVolBootSec = malloc (MAX_SECTOR_SIZE);

    if ((NULL == lbaSectorZero) || (NULL == dosVolBootSec))
	{
	printErr ("mkboot couldn't allocate memory\n");
	goto cleanup1;
	}
	
    bzero ((char *)lbaSectorZero, MAX_SECTOR_SIZE);
    bzero ((char *)dosVolBootSec, MAX_SECTOR_SIZE);

    switch (device)
	{
#ifdef INCLUDE_FD
	case VXSYS_FD:
	    {
	    FD_RAW fdRaw;
	    if ((UINT)drive >= FD_MAX_DRIVES)
		{
		printErr ("drive is out of range(0-%d).\n", FD_MAX_DRIVES - 1);
		goto cleanup1;
		}

	    /*							       
	     * Per MSDOS convention, DOSFS floppy disks never use FDISK
	     * partitions.  So presuming raw CHS sector 1, chs(0,0,1), 
	     * is a DOSFS volumes boot sector is appropriate for nec765 Fd.
	     * Here we setup to do a raw read of sector one.
	     * We may also presume a floppy is FAT12.
	     * chs(0,0,1) is LBA sector 0
	     */							       

	    fdRaw.cylinder   = 0;		
	    fdRaw.head	     = 0;
	    fdRaw.sector     = 1;
	    fdRaw.pBuf	     = (char *)dosVolBootSec;
	    fdRaw.nSecs	     = 1;
	    fdRaw.direction  = O_RDONLY;			/* 0 = read */
	    fdRawio (drive, fdType, &fdRaw);	 /* read the DOS boot sector */
	    
#if defined(INCLUDE_SHELL)
	    if (vxsysDebug)
		d(dosVolBootSec,MAX_SECTOR_SIZE,1);  /* print boot sector */
#endif
		 
	    /* first check to see if the floppy is formatted */
	    if (strncmp((char *) &dosVolBootSec[0x36], FAT12, strlen(FAT12)) != 0)
		{
		printErr ("Floppy is not formatted\n");
		goto cleanup1;
		}
		
	    /* check to see if vxworks long file names are in use */
	    if (strncmp((char *)&dosVolBootSec[3], VXEXT, strlen(VXEXT)) == 0)
		useLongNames = TRUE;

	    if (vxsysDebug)
		printErr ("UseLongNames is %s\n", (useLongNames) ? "TRUE":"FALSE");

	    /*
	     * modify the dos volumes boot sector so that we can jump to
	     * offset 0x3e to execute bootstrap code
	     */
	    BUILD_BOOTSEC(dosVolBootSec);

	    fdRaw.direction  = O_WRONLY;		/* write the boot sector */
	    fdRawio (drive, fdType, &fdRaw);

	    if ((pBlkDev = fdDevCreate (drive, fdType, 0, 0)) == NULL)
		{
		printErr ("Error during fdDevCreate: %x\n", errnoGet ());
		goto cleanup1;
		}

	    break;
	    }
#endif /* INCLUDE_FD */

#if defined(INCLUDE_ATA) || defined(INCLUDE_DRV_STORAGE_INTEL_ICH)
	case VXSYS_ATA:
	    {
	    unsigned char * pSys;
	    DOS_PART_TBL *pPart;
	    BOOL found		= FALSE;
	    UINT32 offset	= 0;
	    ATA_RAW ataRaw;
	    
	    if ((UINT)ctrl >= ATA_MAX_CTRLS)
		{
		printErr ("ctrl is out of range (0-%d).\n", ATA_MAX_CTRLS -1);
		goto cleanup1;
		}
	    if ((UINT)drive >= ATA_MAX_DRIVES)
		{
		printErr ("drive is out of range(0-%d).\n", ATA_MAX_DRIVES -1);
		goto cleanup1;
		}

	    /* 
	     * CHS addressing is different from LBA addressing.
	     * CHS[0,0,1] corresponds to LBA sector zero.  CHS
	     * sector numbering starts at 1.  If there are 63 
	     * sectors per track, the sectors are numbered 1-63.
	     *							      
	     * ATA disks formatted via Windows always have partitions.
	     * ATA disks formatted via vxWorks may have partitions or 
	     * they may have the dosFs volume start on LBA sector zero
	     * without any partition.
	     *
	     * If the dosFs volume starts on LBA sector zero, then     
	     * the DOS, or VXEXT strings will be present there.	    
	     *
	     * If the partition table (Master Boot Record) resides    
	     * on LBA sector zero, these strings will not be present.
	     *
	     * MSDOS compatible hard discs always have FDISK style 
	     * partitions. For those we must find the bootable partition 
	     * sector and modify the dosFs volumes boot sector therein.
	     * The master boot record, the initial partition table,
	     * is always found on LBA sector zero on MSDOS hard discs.
	     *
	     * Note that the partition should have a FAT12 or FAT16
	     * dosFs volume formatted upon it.	FAT32 will not work. 
	     */
	    ataRaw.cylinder   = 0;
	    ataRaw.head	      = 0;
	    ataRaw.sector     = 1;
	    ataRaw.pBuf	      = (char *)lbaSectorZero;
	    ataRaw.nSecs      = 1; 
	    ataRaw.direction  = O_RDONLY;
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
		ichAtaRawio (ctrl, drive, &ataRaw);
#else
		ataRawio (ctrl, drive, &ataRaw);
#endif
		
#if defined(INCLUDE_SHELL)
	    if (vxsysDebug)
		d(lbaSectorZero, MAX_SECTOR_SIZE, 1);  /* print boot sector */
#endif
	    pSys	= &lbaSectorZero[DOS_BOOT_SYS_ID];
	    pPart	= (DOS_PART_TBL *)&lbaSectorZero[DOS_BOOT_PART_TBL];

	    if ((findSubString((char *)pSys, DOS) != 0) &&
		(findSubString((char *)pSys, VXEXT) != 0))
		{
		int ix;
		for (ix = 0; ix < 4; ix++)
		    {
		    /* 
		     * Note that we are supporting partitions
		     * that could have FAT32 filesystems upon them.
		     * vxLd 1.x will ONLY work on FAT12 and FAT16
		     * filesystem, it will NOT work on FAT32,
		     * but we should still accept the partition types.
		     * Note that dosFsVolFormat can force FAT type.
		     */
		    if (pPart->dospt_status == PART_IS_BOOTABLE)
			if ((pPart->dospt_type == PART_TYPE_DOS12 ) ||
			    (pPart->dospt_type == PART_TYPE_DOS3  ) ||
			    (pPart->dospt_type == PART_TYPE_DOS4  ) ||
			    (pPart->dospt_type == PART_TYPE_DOS32 ) ||
			    (pPart->dospt_type == PART_TYPE_DOS32X) ||
			    (pPart->dospt_type == PART_TYPE_WIN95_D4))
			    {
			    found = TRUE;
			    break;
			    }
		    pPart++;
		    }
	    
		if (!found)
		    {
		    printErr ("Can't find the primary DOS partition.\n");
		    goto cleanup1;
		    }

		ataRaw.cylinder = (pPart->dospt_startSec & 0xf0) >> 4;
		ataRaw.head	= pPart->dospt_startHead;
		ataRaw.sector	= pPart->dospt_startSec & 0x0f;
		ataRaw.pBuf	= (char *)dosVolBootSec;
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
		ichAtaRawio (ctrl, drive, &ataRaw);
#else
		ataRawio (ctrl, drive, &ataRaw); /* read the boot sector */
#endif
#if defined(INCLUDE_SHELL)
		if (vxsysDebug)
		    {
		    printf("Partition %d; CHS of PBR is %d,%d,%d\n", 
			   ix, ataRaw.cylinder, ataRaw.head, ataRaw.sector);
		    d(dosVolBootSec, MAX_SECTOR_SIZE, 1);  /* print boot sector */
		    }
#endif
		
		offset = pPart->dospt_absSec;

		if (strncmp((char *)&dosVolBootSec[3], VXEXT, 
					 strlen(VXEXT)) == 0)
		    {
		    useLongNames = TRUE;
		    }

		if (vxsysDebug)
		    printErr ("UseLongNames is %s\n", 
			      (useLongNames) ? "TRUE":"FALSE");
		}
	    else  /* disk is formatted with vxWorks without partition */
		{
		if (strncmp((char *)pSys, VXEXT, strlen(VXEXT)) == 0)
		    {
		    useLongNames = TRUE;
		    }

		if (vxsysDebug)
		    printErr ("UseLongNames is %s\n", 
			      (useLongNames) ? "TRUE":"FALSE");

		ataRaw.cylinder	  = 0;	/* read/reread the dosFs volume boot sector */
		ataRaw.head	  = 0;
		ataRaw.sector	  = 1;
		ataRaw.pBuf	  = (char *)dosVolBootSec;
		ataRaw.nSecs	  = 1;
		ataRaw.direction  = O_RDONLY;
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
		ichAtaRawio (ctrl, drive, &ataRaw);
#else
		ataRawio (ctrl, drive, &ataRaw);
#endif
		}

	    /*
	     * Below, we attempt to avoid corrupting a FAT32 image.
	     * For FAT32, the 16bit sectors per FAT field (at offset
	     * 0x16 in a MSDOS FAT volumes boot record) will allways
	     * be zero.	 For FAT12, FAT16 it is always non-zero.
	     * We will not continue if this offset is zero.
	     */

	    if ((UINT16) (0x0000) == (UINT16)(dosVolBootSec [0x16])) 
		{
		printErr ("\nThis appears to be a FAT32 volume.\n"
			  "Sectors per FAT, offset 0x16 in the volumes "
			  "boot record is zero.\n"
			  "mkbootAta supports only FAT16 or FAT12.\n"
			  "dosFsVolFormat can force a FAT type.\n");
		goto cleanup1;
		}

	    /*
	     * modify the dos volumes partition boot record with the bootcode
	     * that will load bootrom.sys 
	     */
	    BUILD_BOOTSEC(dosVolBootSec);   /* modify the boot sector */

	    /* all other values for ataRawio are previously setup from 
             * previous use
	     */
	    ataRaw.direction  = O_WRONLY;		/* write the boot sector */
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
		ichAtaRawio (ctrl, drive, &ataRaw);
#else
	    ataRawio (ctrl, drive, &ataRaw);
#endif
	    /*
	     * only get a new block dev pointer if one doesn't already exist
	     * for the ctrl/drive specified. pAtaDev is only setup if the
	     * device has been created.	 Otherwise it is null.
	     */
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
		pIchAtaCtrl=ichAtaGetCtrl(ctrl);
	    if (NULL != pIchAtaCtrl->drive[drive].pAtaDev)
		pBlkDev = &pIchAtaCtrl->drive[drive].pAtaDev->blkDev;
	    else if ((pBlkDev = ichAtaDevCreate (ctrl, drive, 0, offset)) == NULL)
		{
		printErr ("Error during ichAtaDevCreate: %x\n", errnoGet ());
		goto cleanup1;
		}
#else
	    if (NULL != ataCtrl[ctrl].drive[drive].pAtaDev)
		pBlkDev = &ataCtrl[ctrl].drive[drive].pAtaDev->blkDev;
	    else if ((pBlkDev = ataDevCreate (ctrl, drive, 0, offset)) == NULL)
		{
		printErr ("Error during ataDevCreate: %x\n", errnoGet ());
		goto cleanup1;
		}
#endif

	    break;
	    }
#endif	/* INCLUDE_ATA || INCLUDE_DRV_STORAGE_INTEL_ICH*/

#ifdef INCLUDE_DRV_STORAGE_INTEL_AHCI
	case VXSYS_AHCI:
	    {
	    unsigned char * pSys;
	    DOS_PART_TBL *pPart;
	    BOOL found		= FALSE;
	    UINT32 offset	= 0;
	    AHCI_RAW ahciRaw;
	    VXB_DEVICE_ID pDev;
            AHCI_DRIVE  *pDrive;
	    AHCI_DRV_CTRL  *pCtrl;

	    if ((UINT)ctrl >= AHCI_MAX_CTRLS)
		{
		printErr ("ctrl is out of range (0-%d).\n", AHCI_MAX_CTRLS -1);
		goto cleanup1;
		}
	    if ((UINT)drive >= AHCI_MAX_DRIVES)
		{
		printErr ("drive is out of range(0-%d).\n", AHCI_MAX_DRIVES -1);
		goto cleanup1;
		}

            pDev = vxbInstByNameFind(AHCI_NAME, ctrl);
	    if(pDev == NULL)
	        {
	        printErr ("ctrl %d error\n");
	        goto cleanup1;
	        }

            pCtrl = pDev->pDrvCtrl;
            pDrive = &pCtrl->drives[drive];

	    /* 
	     * CHS addressing is different from LBA addressing.
	     * CHS[0,0,1] corresponds to LBA sector zero.  CHS
	     * sector numbering starts at 1.  If there are 63 
	     * sectors per track, the sectors are numbered 1-63.
	     *							      
	     * AHCI disks formatted via Windows always have partitions.
	     * AHCI disks formatted via vxWorks may have partitions or 
	     * they may have the dosFs volume start on LBA sector zero
	     * without any partition.
	     *
	     * If the dosFs volume starts on LBA sector zero, then     
	     * the DOS, or VXEXT strings will be present there.	    
	     *
	     * If the partition table (Master Boot Record) resides    
	     * on LBA sector zero, these strings will not be present.
	     *
	     * MSDOS compatible hard discs always have FDISK style 
	     * partitions. For those we must find the bootable partition 
	     * sector and modify the dosFs volumes boot sector therein.
	     * The master boot record, the initial partition table,
	     * is always found on LBA sector zero on MSDOS hard discs.
	     *
	     * Note that the partition should have a FAT12 or FAT16
	     * dosFs volume formatted upon it.	FAT32 will not work. 
	     */
	    ahciRaw.cylinder   = 0;
	    ahciRaw.head       = 0;
	    ahciRaw.sector     = 1;
	    ahciRaw.pBuf       = (char *)lbaSectorZero;
	    ahciRaw.nSecs      = 1; 
	    ahciRaw.direction  = O_RDONLY;
	    ahciRawio (pCtrl, drive, &ahciRaw);
#if defined(INCLUDE_SHELL)
	    if (vxsysDebug)
		d(lbaSectorZero, MAX_SECTOR_SIZE, 1);  /* print boot sector */
#endif
	    pSys	= &lbaSectorZero[DOS_BOOT_SYS_ID];
	    pPart	= (DOS_PART_TBL *)&lbaSectorZero[DOS_BOOT_PART_TBL];

	    if ((findSubString((char *)pSys, DOS) != 0) &&
		(findSubString((char *)pSys, VXEXT) != 0))
		{
		int ix;
		for (ix = 0; ix < 4; ix++)
		    {
		    /* 
		     * Note that we are supporting partitions
		     * that could have FAT32 filesystems upon them.
		     * vxLd 1.x will ONLY work on FAT12 and FAT16
		     * filesystem, it will NOT work on FAT32,
		     * but we should still accept the partition types.
		     * Note that dosFsVolFormat can force FAT type.
		     */
		    if (pPart->dospt_status == PART_IS_BOOTABLE)
			if ((pPart->dospt_type == PART_TYPE_DOS12 ) ||
			    (pPart->dospt_type == PART_TYPE_DOS3  ) ||
			    (pPart->dospt_type == PART_TYPE_DOS4  ) ||
			    (pPart->dospt_type == PART_TYPE_DOS32 ) ||
			    (pPart->dospt_type == PART_TYPE_DOS32X) ||
			    (pPart->dospt_type == PART_TYPE_WIN95_D4))
			    {
			    found = TRUE;
			    break;
			    }
		    pPart++;
		    }
	    
		if (!found)
		    {
		    printErr ("Can't find the primary DOS partition.\n");
		    goto cleanup1;
		    }

		ahciRaw.cylinder = (pPart->dospt_startSec & 0xf0) >> 4;
		ahciRaw.head	= pPart->dospt_startHead;
		ahciRaw.sector	= pPart->dospt_startSec & 0x0f;
		ahciRaw.pBuf	= (char *)dosVolBootSec;

		ahciRawio (pCtrl, drive, &ahciRaw); /* read the boot sector */
#if defined(INCLUDE_SHELL)
		if (vxsysDebug)
		    {
		    printf("Partition %d; CHS of PBR is %d,%d,%d\n", 
			   ix, ahciRaw.cylinder, ahciRaw.head, ahciRaw.sector);
		    d(dosVolBootSec, MAX_SECTOR_SIZE, 1);  /* print boot sector */
		    }
#endif
		
		offset = pPart->dospt_absSec;

		if (strncmp((char *)&dosVolBootSec[3], VXEXT, 
					 strlen(VXEXT)) == 0)
		    {
		    useLongNames = TRUE;
		    }

		if (vxsysDebug)
		    printErr ("UseLongNames is %s\n", 
			      (useLongNames) ? "TRUE":"FALSE");
		}
	    else  /* disk is formatted with vxWorks without partition */
		{
		if (strncmp((char *)pSys, VXEXT, strlen(VXEXT)) == 0)
		    {
		    useLongNames = TRUE;
		    }

		if (vxsysDebug)
		    printErr ("UseLongNames is %s\n", 
			      (useLongNames) ? "TRUE":"FALSE");

		ahciRaw.cylinder	  = 0;	/* read/reread the dosFs volume boot sector */
		ahciRaw.head	  = 0;
		ahciRaw.sector	  = 1;
		ahciRaw.pBuf	  = (char *)dosVolBootSec;
		ahciRaw.nSecs	  = 1;
		ahciRaw.direction  = O_RDONLY;
		ahciRawio (pCtrl, drive, &ahciRaw);
		}

	    /*
	     * Below, we attempt to avoid corrupting a FAT32 image.
	     * For FAT32, the 16bit sectors per FAT field (at offset
	     * 0x16 in a MSDOS FAT volumes boot record) will allways
	     * be zero.	 For FAT12, FAT16 it is always non-zero.
	     * We will not continue if this offset is zero.
	     */

	    if ((UINT16) (0x0000) == (UINT16)(dosVolBootSec [0x16])) 
		{
		printErr ("\nThis appears to be a FAT32 volume.\n"
			  "Sectors per FAT, offset 0x16 in the volumes "
			  "boot record is zero.\n"
			  "mkbootAhci supports only FAT16 or FAT12.\n"
			  "dosFsVolFormat can force a FAT type.\n");
		goto cleanup1;
		}

	    /*
	     * modify the dos volumes partition boot record with the bootcode
	     * that will load bootrom.sys 
	     */
	    BUILD_BOOTSEC(dosVolBootSec);   /* modify the boot sector */

	    /* all other values for ahciRawio are previously setup from 
             * previous use
	     */
	    ahciRaw.direction  = O_WRONLY;		/* write the boot sector */
	    ahciRawio (pCtrl, drive, &ahciRaw);

	    /*
	     * only get a new block dev pointer if one doesn't already exist
	     * for the ctrl/drive specified. pAhciDev is only setup if the
	     * device has been created.	 Otherwise it is null.
	     */
	    if (NULL != pDrive->pAhciDev)
		pBlkDev = &pDrive->pAhciDev->blkDev;

	    else if ((pBlkDev = ahciDevCreate (pCtrl, drive, 0, offset)) == NULL)
		{
		printErr ("Error during ahciDevCreate: %x\n", errnoGet ());
		goto cleanup1;
		}

	    break;
	    }
#endif /* INCLUDE_DRV_STORAGE_INTEL_AHCI */

#ifdef INCLUDE_TFFS
	case VXSYS_TFFS:
	    {
	    unsigned char * pSys;
	    DOS_PART_TBL *pPart;
	    BOOL found		= FALSE;
	    UINT32 offset	= 0;
	    int removable	= fdType;
	    
	    if ((UINT)drive >= TFFS_MAX_DRIVES)
		{
		printErr ("drive is out of range (0-%d).\n", 
				TFFS_MAX_DRIVES-1);
		goto cleanup1;
		}

	    /* mount the TFFS */

	    if ((pBlkDev = tffsDevCreate (drive, removable)) == NULL)
		{
		printErr ("Error during tffsDevCreate: %x\n", errnoGet ());
		goto cleanup1;
		}

	    /* read the partition table */

	    tffsRawio (drive, TFFS_ABS_READ, 0, 1, (int)&lbaSectorZero);

	    offset	= 0;

	    pSys	= &lbaSectorZero[DOS_BOOT_SYS_ID];
	    pPart	= (DOS_PART_TBL *)&lbaSectorZero[DOS_BOOT_PART_TBL];

	    if ((findSubString((char *)pSys, DOS) != 0) &&
		(findSubString((char *)pSys, VXEXT)!= 0))
		{
		int ix;
		for (ix = 0; ix < 4; ix++)
		    {
		    if (pPart->dospt_status == PART_IS_BOOTABLE)
			if ((pPart->dospt_type == PART_TYPE_DOS12 ) ||
			    (pPart->dospt_type == PART_TYPE_DOS3  ) ||
			    (pPart->dospt_type == PART_TYPE_DOS4  ) ||
			    (pPart->dospt_type == PART_TYPE_DOS32 ) ||
			    (pPart->dospt_type == PART_TYPE_DOS32X) ||
			    (pPart->dospt_type == PART_TYPE_WIN95_D4))
			    {
			    found = TRUE;
			    break;
			    }
		    pPart++;
		    }
	    
		if (found)
		    offset = pPart->dospt_absSec;
		}

	    /* read the boot sector */

	    tffsRawio (drive, TFFS_ABS_READ, offset, 1, (int)&dosVolBootSec);

	    if (strncmp((char *)&dosVolBootSec[3], VXEXT, strlen(VXEXT)) == 0)
		{
		useLongNames = TRUE;
		}

	    if (vxsysDebug)
		printErr ("UseLongNames is %s\n", 
			  (useLongNames) ? "TRUE":"FALSE");

	    /*
	     * Below, we attempt to avoid corrupting a FAT32 image.
	     * For FAT32, the 16bit sectors per FAT field (at offset
	     * 0x16 in a MSDOS FAT volumes boot record) will allways
	     * be zero.	 For FAT12, FAT16 it is always non-zero.
	     * We will not continue if this offset is zero.
	     */

	    if ((UINT16)(0x0000) == (UINT16)(dosVolBootSec [0x16])) 
		{
		printErr ("\nThis appears to be a FAT32 volume.\n"
			  "Sectors per FAT, offset 0x16 in the volumes "
			  "boot record is zero.\n"
			  "mkbootTffs supports only FAT16 or FAT12.\n"
			  "dosFsVolFormat can force a FAT type.\n");
		goto cleanup1;
		}

	    /*
	     * modify the dos volumes boot sector so that we can jump to
	     * offset 0x3e to execute bootstrap code
	     */
	    BUILD_BOOTSEC(dosVolBootSec);

	    /* write the boot sector */
	    tffsRawio (drive, TFFS_ABS_WRITE, offset, 1, (int)&dosVolBootSec);

	    break;
	    }
#endif /*INCLUDE_TFFS */

	default:
	    printErr ("unknown device (0-1).\n");
	    goto cleanup1;
	} /* end switch */

    if ((inFd = open (in, O_RDONLY, 0644)) == ERROR)
	{
	printErr ("Can't open \"%s\"\n", in);
	goto cleanup1;
	}

    /* Create a name for the name mapping in the FSM */
    /* Install name mapping */
    fsmNameInstall (VXSYS_RAWDEV0, VXSYS_DOSDEV);
    fsmNameInstall (VXSYS_RAWDEV1, VXSYS_DOSDEV);
    
    /* Already have pBlkDev from above */
    /* Create an XBD wrapper */
    blkDevice_t = xbdBlkDevCreateSync (pBlkDev, VXSYS_DOSDEV);
    if (NULLDEV == blkDevice_t)
	{
	printErr ("Error creating block dev wrapper.\n");
	goto cleanup2;
	}

    if (useLongNames == FALSE)
	outFd = open (VXSYS_FILE, O_CREAT | O_RDWR, 0644);
    else
	outFd = open (VXSYS_FILE_VXEXT, O_CREAT | O_RDWR, 0644);
	    
    if (outFd == ERROR)
	{
	printErr ("Can't open \"%s\"\n", VXSYS_FILE);
	goto cleanup3;
	}
	
    /* The file is opened, now we have to make sure that it is contiguous
     * for the bootloader.  The ioctl preallocates the size of the input
     * file for the newly opened output file.  The size cannot exceed
     * ROM_SIZE.
     */ 
    if (ERROR == stat(in, &pStat))
	{
	printErr ("Can't stat input file %s\n", in);
	goto cleanup4;
	}
    if (pStat.st_size > ROM_SIZE)
	{
	printErr ("%s (0x%x bytes) is bigger than the max ROM_SIZE"
		  " of 0x%x bytes\n", in, (long)pStat.st_size, ROM_SIZE);
	goto cleanup4;
	}

    if (ioctl (outFd, FIOCONTIG, (long)pStat.st_size) == ERROR)
	{
	printErr ("Error during ioctl FIOCONTIG: %x\n", errnoGet ());
	goto cleanup4;
	}

    { /* begin local scope */
    int bytes_read;
    int write_status;
    int ix = 0;

    while (ix <= ROM_SIZE) /* will break out of loop when bytes read=0 or error */
	{     /* do not write more than the max rom size */
	bytes_read = read (inFd, (char *)dosVolBootSec, MAX_SECTOR_SIZE);
	if (bytes_read == ERROR)
	    {
	    printErr ("Error during read file: %x\n", errnoGet ());
	    goto cleanup4;
	    }
	if (bytes_read == 0)
	    break;
				
	/* there is data to write, write out to file */
	ix += bytes_read;
	write_status = write (outFd, (char *)dosVolBootSec, bytes_read);
	if (write_status == ERROR)
	    {
	    printErr ("Error during write fd: %x\n", errnoGet ());
	    goto cleanup4;
	    }
	} /* end while */
    printf ("num bytes written = %d\n", ix);
    }  /* end of local scope */
    ret_code = OK;  /* this is the only good return code */

cleanup4:
    close (outFd);
cleanup3:
    { /* begin local scope */
    BLK_DEV *blkPtr;
    xbdBlkDevDelete (blkDevice_t, &blkPtr);
    if (blkPtr != pBlkDev)
	printErr("error in block device delete\n");
    fsmNameUninstall (VXSYS_RAWDEV0);
    fsmNameUninstall (VXSYS_RAWDEV1);
    } /* end local scope */
cleanup2:
    close (inFd);	
cleanup1:
    if (NULL != lbaSectorZero)
	free (lbaSectorZero);
    if (NULL != dosVolBootSec)
	free (dosVolBootSec);

    return (ret_code);
    }
    
#if defined(INCLUDE_ATA) || defined(INCLUDE_DRV_STORAGE_INTEL_ICH)
/*******************************************************************************
 *
 * mkMbr - create MasterBootRecord on sector 0 of the specified hard disk
 *
 * This command creates an MBR (FreeBSD version) on sector 0 of the
 * specified hard drive.  This will allow partitioning and booting of vxWorks
 * images from within a vxWorks application.  The hard disk will not have
 * to be first "fdisk'd" on a DOS type platform.
 *
 * EXAMPLE:
 * The following example places the MBR on sector 0 of the hard disk
 * .CS
 *     -> mkMbr 0, 0
 * .CE
 *
 * RETURNS:
 * OK, or ERROR if there is an error copying from <in> to the disk.
 *
 */
STATUS mkMbr 
    (
    int ctrl,			/* controller number:	(0 - 1)		 */
    int drive			/* drive number:	(0 - 1)		 */
    )
    {
    ATA_RAW ataRaw;
    char * lbaSectorZero;
    
    if (vxsysDebug)
	printErr("size of MBR is 0x%x\n", sizeof(MBR));
	
    if ((UINT)ctrl >= ATA_MAX_CTRLS)
	{
	printErr ("ctrl is out of range (0-%d).\n", ATA_MAX_CTRLS -1);
	return ERROR;
	}
    if ((UINT)drive >= ATA_MAX_DRIVES)
	{
	printErr ("drive is out of range(0-%d).\n", ATA_MAX_DRIVES -1);
	return ERROR;
	}
	
    lbaSectorZero  = malloc (MAX_SECTOR_SIZE);

    if (NULL == lbaSectorZero)
	{
	printErr ("mkboot couldn't allocate memory\n");
	return ERROR;
	}
	
    bzero (lbaSectorZero, MAX_SECTOR_SIZE);

    /* 
     * CHS addressing is different from LBA addressing.
     * CHS[0,0,1] corresponds to LBA sector zero.  CHS
     * sector numbering starts at 1.  If there are 63 
     * sectors per track, the sectors are numbered 1-63.
     * 
     * MSDOS compatible hard discs always have FDISK style 
     * partitions. For those we must find the bootable partition 
     * sector and modify the dosFs volumes boot sector therein.
     * The master boot record, the initial partition table,
     * is always found on LBA sector zero on MSDOS hard discs.
     *
     */

    ataRaw.cylinder   = 0;
    ataRaw.head	      = 0;
    ataRaw.sector     = 1;
    ataRaw.pBuf	      = lbaSectorZero;
    ataRaw.nSecs      = 1; 
    ataRaw.direction  = O_RDONLY;
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
	ichAtaRawio (ctrl, drive, &ataRaw);
#else
    ataRawio (ctrl, drive, &ataRaw);
#endif
#if defined(INCLUDE_SHELL)
    if (vxsysDebug)
	d(lbaSectorZero, MAX_SECTOR_SIZE, 1);  /* print boot sector */
#endif
    bcopy ((char *)MBR, (char *)&lbaSectorZero[0], sizeof (MBR));
    ataRaw.direction  = O_WRONLY;		/* write the boot sector */
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
	ichAtaRawio (ctrl, drive, &ataRaw);
#else
	ataRawio (ctrl, drive, &ataRaw);
#endif
    free (lbaSectorZero);
    return OK;
    }

#endif	/* INCLUDE_ATA  or INCLUDE_DRV_STORAGE_INTEL_ICH*/

#ifdef INCLUDE_DRV_STORAGE_INTEL_AHCI
/*******************************************************************************
 *
 * mkMbrAhci - create MasterBootRecord on sector 0 of the specified hard disk
 *
 * This command creates an MBR (FreeBSD version) on sector 0 of the
 * specified hard drive.  This will allow partitioning and booting of vxWorks
 * images from within a vxWorks application.  The hard disk will not have
 * to be first "fdisk'd" on a DOS type platform.
 *
 * EXAMPLE:
 * The following example places the MBR on sector 0 of the hard disk
 * .CS
 *     -> mkMbrAhci 0, 0
 * .CE
 *
 * RETURNS:
 * OK, or ERROR if there is an error copying from <in> to the disk.
 *
 */
STATUS mkMbrAhci
    (
    int ctrl,			/* controller number:	(0 - 1)		 */
    int drive			/* drive number:	(0 - 1)		 */
    )
    {
    AHCI_RAW ahciRaw;
    char * lbaSectorZero;
    VXB_DEVICE_ID pDev = NULL;

    if (vxsysDebug)
	printErr("size of MBR is 0x%x\n", sizeof(MBR));
	
    if ((UINT)ctrl >= AHCI_MAX_CTRLS)
	{
	printErr ("ctrl is out of range (0-%d).\n", AHCI_MAX_CTRLS -1);
	return ERROR;
	}
    if ((UINT)drive >= AHCI_MAX_DRIVES)
	{
	printErr ("drive is out of range(0-%d).\n", AHCI_MAX_DRIVES -1);
	return ERROR;
	}
    
    pDev = vxbInstByNameFind(AHCI_NAME, ctrl);
    if(pDev == NULL)
        {
	printErr ("ctrl %d error\n");
	return ERROR;
	}

    lbaSectorZero  = malloc (MAX_SECTOR_SIZE);

    if (NULL == lbaSectorZero)
	{
	printErr ("mkboot couldn't allocate memory\n");
	return ERROR;
	}

    bzero (lbaSectorZero, MAX_SECTOR_SIZE);

    /* 
     * CHS addressing is different from LBA addressing.
     * CHS[0,0,1] corresponds to LBA sector zero.  CHS
     * sector numbering starts at 1.  If there are 63 
     * sectors per track, the sectors are numbered 1-63.
     * 
     * MSDOS compatible hard discs always have FDISK style 
     * partitions. For those we must find the bootable partition 
     * sector and modify the dosFs volumes boot sector therein.
     * The master boot record, the initial partition table,
     * is always found on LBA sector zero on MSDOS hard discs.
     *
     */

    ahciRaw.cylinder   = 0;
    ahciRaw.head       = 0;
    ahciRaw.sector     = 1;
    ahciRaw.pBuf       = lbaSectorZero;
    ahciRaw.nSecs      = 1; 
    ahciRaw.direction  = O_RDONLY;
    ahciRawio (pDev->pDrvCtrl, drive, &ahciRaw);
#if defined(INCLUDE_SHELL)
    if (vxsysDebug)
	d(lbaSectorZero, MAX_SECTOR_SIZE, 1);  /* print boot sector */
#endif
    bcopy ((char *)MBR, (char *)&lbaSectorZero[0], sizeof (MBR));
    ahciRaw.direction  = O_WRONLY;		/* write the boot sector */
    ahciRawio (pDev->pDrvCtrl, drive, &ahciRaw);

    free (lbaSectorZero);
    return OK;
    }

#endif /* INCLUDE_DRV_STORAGE_INTEL_AHCI */

/*******************************************************************************
*
* findSubString - find a string within a string
*
* This  function looks for a substring within a given string.
*
* RETURNS:
* OK, if the substring is found
* ERROR if no match is found
* 
***********************************************************/
LOCAL STATUS findSubString
    (
    char *src,	    /* string to search */
    char *sub 	    /* substring we are searching for */
    )
    {
    int i;
    int size1;
    int size2;

    i = 0;
    size1 = strlen(src);
    size2 = strlen(sub);

    while (size2 <= size1)
        {
	if (strncmp(&src[i++], sub, size2) == 0)
	    return OK;
	--size1;	/* decrement size of string, since we are advancing in it */
	}
    return ERROR;   /* substring not found */
    }
