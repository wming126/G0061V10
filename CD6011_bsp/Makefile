# MakeSkel - makefile skeleton for vw/config/pc
#
# Copyright 1984-2003 Wind River Systems, Inc.
#
# modification history
# --------------------
# 01t,26feb08,scm  Set GNU as default build.
# 01s,24jul07,scm  WIND00099085...
# 01r,16jul07,ami  removed cmdLine.c dependency for sysLib.c build
# 01q,07may07,scm  disable  FAST_REBOOT
# 01p,02mar07,rec  WIND00089420 - remove ipnet makefile workaround
# 01p,01dec06,d_c  Add dependency on sysLib.c to create cmdLine.c
# 01o,09aug06,wap  Add PXE support
# 01n,07oct04,zmm  Enable FAST_REBOOT.
# 01m,09jun04,zmm  Now when bsp2prj.tcl is fixed (SPR 94349 and 93379),
#                  RELEASE_PRJ can be removed.
# 01l,14may04,zmm  Remove unsupported images for making release.
# 01k,27oct03,fle  Added POST_HEX_BUILD_RULE to .hex rules
# 01j,25jun02,pai  Changed RAM_HIGH_ADRS, RAM_LOW_ADRS, and
#                  LOCAL_MEM_LOCAL_ADRS.
# 01i,05jul02,hdn  added EXTRA_DEFINE
# 01h,20may02,rhe  Add bootrom.bin to RELEASE
# 01g,08may02,pai  Removed build rules for deprecated bootrom_high,
#                  vxWorks_rom_low, and vxWorks_low images.
# 01f,19nov01,hdn  removed .bin rule as it is defined in the upper level
# 01e,14nov01,dat  RELEASE update
# 01d,02nov01,hdn  replaced bootrom_uncmp with bootrom_uncmp.bin
# 01c,30oct01,tpw  Standardize kernel links and bootrom conversions.
# 01b,25sep01,dat  Update for T2.2
# 01a,10aug01,hdn  written based on pc386/Makefile.
#
# DESCRIPTION
# This file contains rules for building VxWorks for the
# PC Pentium4.
#
# NOTE
# The constants ROM_TEXT_ADRS and RAM_HIGH_ADRS
# must be identical to those in config.h.
#
# INCLUDES
#     makeTarget
#*/

CPU	= PENTIUM4
TOOL	= gnu 

TGT_DIR = $(WIND_BASE)/target

include $(TGT_DIR)/h/make/defs.bsp

## Only redefine make definitions below this point, or your definitions will
## be overwritten by the makefile stubs above.

TARGET_DIR = pcPentium4
VENDOR     =
BOARD      = PC Pentium4

#
# The constants ROM_TEXT_ADRS, ROM_SIZE, and RAM_HIGH_ADRS are defined
# in config.h, MakeSkel, Makefile, and Makefile.*
# All definitions for these constants must be identical.
#

# ifdef BOOTCODE_IN_RAM
ROM_TEXT_ADRS      = 00008000	# ROM entry address - A: or C:
ROM_SIZE           = 00090000	# number of bytes of ROM space
# else
# ROM_TEXT_ADRS      = fff20000	# ROM entry address - EPROM
# ROM_SIZE           = 0007fe00	# number of bytes of ROM space
# endif

RAM_LOW_ADRS       = 00408000	# VxWorks image entry point
RAM_HIGH_ADRS      = 00108000	# Boot image entry point

EXTRA_DEFINE       = -DFAST_REBOOT

MACH_EXTRA         = ./KEY/vxbI8042Kbd.o ./APIC/vxbIoApicIntr.o ./ICH/vxbIntelIchStorage.o ./PIO/PciIoCntLib.o \
                     ./ICH/bootFsLoad.o ./PCAN/PciCanLib.o ./SIO/vxbNs16550Sio.o

RELEASE += bootrom.bin mkboot.o

RELEASE += bootrom.pxe

bootrom.pxe: bootrom.bin pxeBoot.bin
	cat pxeBoot.bin bootrom.bin > bootrom.pxe


## Only redefine make definitions above this point, or the expansion of
## makefile target dependencies may be incorrect.

include $(TGT_DIR)/h/make/rules.bsp

# Following bootable vxWorks should be placed in bootable diskette
# by "mkboot" or "mkbootFd, mkbootAta" utility.
#
#   vxWorks.st_rom	- bootable vxWorks.st(compressed): upper mem
#   bootrom		- bootrom(compressed):		   upper mem
#   bootrom_uncmp	- bootrom:			   upper mem
#
# The boot image is either bootrom_uncmp or vxWorks.st_rom.
# If the EPROM is 27020 (256 Kbytes)
#	$(BINHEX) -a 3fe00 -b romcard >> $@
# If the EPROM is 27040 (512 Kbytes)
#	$(BINHEX) -a 7fe00 -b romcard >> $@

SED	= sed

romcard_bootrom_512.hex:	depend.$(BSP_NAME) romcard.o bootrom_uncmp
	- @ $(RM) $@
	$(LD) -o romcard -X -N -e _romcard romcard.o
	$(ROMSIZEPROG) -b 7fe00 bootrom_uncmp
	$(BINHEX) -a 0 bootrom_uncmp | $(SED) -e "/S9/d" > $@
	$(BINHEX) -a 7fe00 -b romcard >> $@
	- @ $(RM) romcard.o romcard
	$(POST_HEX_BUILD_RULE)

romcard_bootrom_256.hex:	depend.$(BSP_NAME) romcard.o bootrom_uncmp
	- @ $(RM) $@
	$(LD) -o romcard -X -N -e _romcard romcard.o
	$(ROMSIZEPROG) -b 3fe00 bootrom_uncmp
	$(BINHEX) -a 0 bootrom_uncmp | $(SED) -e "/S9/d" > $@
	$(BINHEX) -a 3fe00 -b romcard >> $@
	- @ $(RM) romcard.o romcard
	$(POST_HEX_BUILD_RULE)

romcard_vxWorks_st_512.hex:	depend.$(BSP_NAME) romcard.o vxWorks.st_rom
	- @ $(RM) $@
	$(LD) -o romcard -X -N -e _romcard romcard.o
	$(ROMSIZEPROG) -b 7fe00 vxWorks.st_rom
	$(BINHEX) -a 0 vxWorks.st_rom | $(SED) -e "/S9/d" > $@
	$(BINHEX) -a 7fe00 -b romcard >> $@
	- @ $(RM) romcard.o romcard
	$(POST_HEX_BUILD_RULE)

