/* sysNvRam.c - x86 nvram api for block devices */

/*
 * Copyright 1984-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,28feb07,pgh  Fix WIND00078862
01f,18oct06,tor  Added lseek(offset) in set and get routines
01f,08aug06,dmh  respect value of offset parameter
01e,11aug05,pcm  corrected NVRAMFILE pathname
01d,29jul05,pcm  changed INCLUDE_DOSFS to INCLUDE_DOSFS_MAIN
01c,15jun05,pcm  dosFs is now removable
01b,18jul02,rhe  Remove possible compile time warning message. SPR 79857
01a,20jun02,dmh  created. now even without eeprom peecees have storage for the bootline
*/

/*
DESCRIPTION:

This file implements the nvram api using standard io system calls
for non-volatile media such as flash ram, floppy disks and hard disk
drives.  It is primarily intended for saving and modifying boot parameters
but could in theory be used for general purpose information.  A file of
NV_RAM_SIZE size is used for storing the "nvram" data.
*/

/* includes */

#include <vxWorks.h>
#include <logLib.h>
#include <string.h>
#include "config.h"

#define NVRAMFILE  "/nvram.txt"
#define NVRAMPATH   BOOTROM_DIR "" NVRAMFILE

/******************************************************************************
*
* sysNvRamGet - get the contents of non-volatile RAM
*
* This routine copies the contents of non-volatile memory into a specified
* string.  The string is terminated with an EOS.
*
* RETURNS: OK, or ERROR if access is outside the non-volatile RAM range.
*
* SEE ALSO: sysNvRamSet()
*/

STATUS sysNvRamGet
    (
    char *string,    /* where to copy non-volatile RAM    */
    int strLen,      /* maximum number of bytes to copy   */
    int offset       /* byte offset into non-volatile RAM */
    )
    {
    int fd, bytes;

    if ((offset < 0) || (strLen < 0) || ((offset + strLen) > NV_RAM_SIZE))
        return (ERROR);

    fd = open (NVRAMPATH, O_RDWR, 0);
    if (fd == ERROR)
        {
        logMsg ("%s: open failed\n", (int)__FUNCTION__, 0, 0, 0, 0, 0);
        return (ERROR);
        }

    if (lseek (fd, offset, SEEK_SET) != offset)
        {
        close (fd);
        return (ERROR);
        }

    bytes = read (fd, string, strLen);
    if (bytes == ERROR)
        {
        logMsg ("%s: read failed\n", (int)__FUNCTION__, 0, 0, 0, 0, 0);
        close (fd);
        return (ERROR);
        }
    else
        {
        string[bytes] = EOS;
        close (fd);
        return (OK);
        }
    }

/*******************************************************************************
*
* sysNvRamSet - write to non-volatile RAM
*
* This routine copies a specified string into non-volatile RAM.
*
* RETURNS: OK, or ERROR if access is outside the non-volatile RAM range.
*
* SEE ALSO: sysNvRamGet()
*/

STATUS sysNvRamSet
    (
    char *string,     /* string to be copied into non-volatile RAM */
    int strLen,       /* maximum number of bytes to copy           */
    int offset        /* byte offset into non-volatile RAM         */
    )
    {
    int fd;

    if ((offset < 0) || (strLen < 0) || ((offset + strLen) > NV_RAM_SIZE))
        return (ERROR);

    fd = open (NVRAMPATH, O_RDWR | O_CREAT, 2);
    if (fd == ERROR)
        {
        logMsg ("%s: open failed\n", (int)__FUNCTION__, 0, 0, 0, 0, 0);
        return (ERROR);
        }
  
    if (lseek (fd, offset, SEEK_SET) != offset)
        {
        close (fd);
        return (ERROR);
        }
    
    if (write (fd, string, strLen) != strLen)
        {
        logMsg ("%s: write failed\n", (int)__FUNCTION__, 0, 0, 0, 0, 0);
        close (fd);
        return (ERROR);
        }
    else
        {
        close (fd);
        return (OK);
        }
    }


