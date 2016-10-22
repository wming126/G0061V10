/* sysLib.c - PC 3/486/Pentium/Pentium2/3/4 system-dependent library */

/*
 * Copyright 1984-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08b,15oct09,jl   Fix WIND00185251
08a,14oct09,to   Fix WIND00185615
07z,21sep09,sem  Fix WIND00174100
07y,21sep09,scm  WIND00182142 - enforce arch limitation for SMP configurable cores.
07x,16jul09,to   VB: VBI 2.0 support
07w,10jul09,to   VB: add mapping for vIoapic
                 fix sysMmuMapAdd()'s length calculation
07v,28apr09,rec  guest Os merge from vxWorks 6.7.0
                 VB: do not clear memory on vbMgmtReset if not cold boot
                 VB: add support for com3 and com4 (WIND144311)
                 update vbiMgmt
                 VB: convert to VBI naming; fix VB interrupt handling
                 VB: Remove vbInterrupt controller mapping.
                 VB: merge WR hypervisor guest OS support
                 WIND00143219 - Fix sysStaticMpApicDataGet function.
07u,20nov08,scm  multiple IO Apic support mods...
07t,17oct08,pgh  Change RAM_LOW_ADRS/RAM_HIGH_ADRS to
                 SYS_RAM_LOW_ADRS/SYS_RAM_HIGH_ADRS.
07s,29sep08,rbc  Workaround for WIND00119364.
07r,29aug08,kab  Change _WRS_VX_SMP to _WRS_CONFIG_SMP
07q,12aug08,rbc  remove wrLoad() also merge EFI/ACPI code
07p,30jun08,scm  adjust static config for new structure consts...
07o,30may08,scm  TESTING...
07n,23jun08,dcc  added startcore() code for wrLoad().
07m,28apr08,scm  WIND00103470 - SMP/SYMMETRIC_IO_MODE warm re-boot support.
07l,23may08,tor  revert INIT_HWMEMPOOL_IN_BSP
07k,14apr08,tor  BSP-provided hwMemPool[]
07j,05mar08,scm  WIND00116698.
07i,04dec07,scm  WIND00111331.
07h,13oct07,scm  WIND00107594.
07g,26sep07,pmr  fix apigen errors
07f,15sep07,scm  WIND00095242.
07e,11sep07,scm  WIND00103620, WIND00103507.
07d,31aug07,mmi  remove IPI_CTRL_INIT since move to vxBus driver
07c,23aug07,pmr  DMA init for Intel ICH Storage
07b,23aug07,spw  Fix merge conflict
07a,22aug07,pmr  support VxBus ATA
06z,22aug07,spw  added INCLUDE_BCM43XX_END
06y,15aug07,mmi  switch to new power management framework
06x,30jul07,scm  SMP TIMESTAMP work...
06w,08aug07,agf  remove duplicate variable definitions
06v,06aug07,h_k  removed #ifndef PRJ_BUILD for hwconf.c. (CQ:100492)
06u,27jul07,scm  allow Enable/DisablePIC to call apic routine directly once
                 vxBus up...
06t,25jul07,scm  remove unused var...
06s,24jul07,scm  WIND00099085...
06r,20jul07,scm  modify sysToMonitor for SMP...
06q,16jul07,ami  removed cmdLine.c inclusion
06p,21jun07,h_k  removed glbMpApicNioint, glbMpApicNloint,
                 glbMpApicInterruptTable.
06o,21jun07,scm  correct broken VIRTUAL_WIRE_MODE build...
06n,12jun07,scm  remove deprecated function sysCpuNumGet...
06m,12jun07,scm  correct WIND00096239, pcPentium fails to reboot in SMP
                 mode...
06l,22may07,scm  adjust AP init to account for OSM GDT entries...
06k,07mar07,dee  Add pc console code here so it is not dependent on serial.
                 WIND00088868, WIND00089976
06u,16may07,scm  adjust AP init to account for RTP GDT entries...
06t,11may07,scm  remove potential nested spinLock scenario...
06s,03may07,scm  modify for vxBus APIC support...
06q,28mar07,mmi  conditionally compile sysNetPciInit() upon INCLUDE_NETWORK
06p,20mar07,pmr  SMP-safe PC Console
06o,15mar07,scm  general clean up for AP startup...
06n,12mar07,scm  backed out vxbus timer support for SMP...
06m,09mar07,scm  move ioApicInit from sysIntInitPIC and call it directly from
                 sysHwInit2...
06l,05mar07,pdg  added vxbus timer support
06k,02mar07,pmr  VxBus PC Console
06j,02mar07,wap  Fix added bootmem feature
06i,28feb07,dtr  Remove old PCI configuration calls.
06h,13feb07,scm  WIND00087190.
06g,06feb07,scm  move to using intCpuLock/Unlock in place of intLock/Unlock...
06f,02feb07,scm  add SMP support mods...
06e,27dec06,tor  fix interrupt order dependency
06d,09oct06,scm  correct GDT update, and add sysInitGDT...
		 FIXES: WIND00066325, WIND00066327
06c,04sep06,tor  Make VxBus the default, remove non-VxBus support
06b,07mar06,jmt  Modify sysModel to return SYS_MODEL string
06a,30jan06,zmm  Make sysCpuId different than zero. Fix SPRs 109902 and 117076.
05z,11jan06,mdo  Change INCLUDE_NS16550_SIO to DRV_SIO_NS16550
05y,14sep05,mdo  SPR#111986 - vxBus interrupt mode fix.
05x,13sep05,pmr  GEI HEND support. (SPR 112245)
05w,02sep05,mdo  Add vxb prefix
05v,28jul05,pcm  fixed up sysToMonitor() file system code
05u,08aug05,mdo  Change WINDBUS to VXBUS
05t,04aug05,jb  Add include to obtain vxBus function prototypes
05s,03aug05,jb  Enable no-vxBus End driver co-existence
05r,03aug05,mdo  Remove adding vxBus files in using project builds
05q,02aug05,mdo  Add vxBus initialization
05p,03jun05,zmm  Fix diab compiler warnings. SPR 107351.
05o,26apr05,kab  Doc fixes (SPR 108390)
05o,15jun05,pcm  dosfs is now removable
05n,09mar05,hch  Fix SPR #106835 on duplicate MMU entry for HCD
05m,17dec04,ckj  WLAN support for Atheros AR521X
05n,25jun04,jb   Fix SPR 96587. reboot fails after kernel error in interrupt
         context.
05l,18aug04,md   PM_RESERVED_MEM is dependent on INCLUDE_EDR_PM
05k,17may04,scm  spr97436, sysPhysMemTop GDT issue...
05j,05may04,zmm  Fix diab compiler warnings.
05i,09dec03,agf  add PM_RESERVED_MEM
05h,02dec03,agf  fix compiler warnings
05g,25mar03,zmm  Fix SPR 86838. The vxShowInit() will be called for each x86 CPU
05f,05nov02,hdn  made sysCpuProbe() execution conditional (spr 76279)
05e,01oct02,hdn  added Debug Store support for Pentium4
05d,09sep02,hdn  added Thermal Monitoring support for Pentium4
05c,21jun02,pai  Linker-defined <end> symbol is now cast to an unsigned
         integer instead of a signed integer where needed.
         Updated commentary and page-sized stride in sysPhysMemTop()
         memory auto-size algorithm (SPR 79525).
05b,12jul02,dmh  include sysNvRam.c based value of NV_RAM_SIZE instead of
         IACSF
05a,11jul02,dmh  remove SFL_START_ADDR for iacsfl-based BSPs.
04z,04jul02,hdn  added the checksum to the FAST_REBOOT mechanism.
04y,18jun02,hdn  cleaned up sysPhysMemDesc[] and new reboot mechanism.
04x,03jun02,pai  Updated sysMmuMapAdd() documentation.  Modified file I/O
         status messages in sysToMonitor().
04w,05jun02,hdn  added 2MB page size support for 36Bit MMU
04v,25may02,hdn  updated sysMmuMapAdd to align VM_PAGE_SIZE (spr 77530)
         added intLock/Unlock in sysIntLock/Unlock (spr 75694)
04u,24may02,hdn  replaced PAGE_SIZE with VM_PAGE_SIZE for 4MB page
04t,23may02,pai  Add WindML device initialization to sysHwInit().
04s,20may02,rhe  added USB support for ohci cards. SPR# 76308
04r,09may02,hdn  added Pentium4 Asymmetric Multi Processor configuration
04q,29apr02,pai  Complete the fix for (SPR 8385).  Modified sysPhysMemTop()
         will now auto-size a larger address space.
04p,28apr02,hdn  added optional new i8259 PIC specific features (spr 76411)
04o,22apr02,pai  Removed configuration related to obsolete SMC Ultra Netif
         driver.
04n,09apr02,pai  Reworked ATA configuration and documentation (SPR# 73848).
         Added sysHwInit0() for the (SPR 74951) fix implementation.
04m,01apr02,jkf  Added _WRS_BSP_DEBUG_NULL_ACCESS to generate exception when
         code accesses to lower page of memory, null ptr, occur.
04l,25mar02,pai  Conditionally include MTRR table based upon PENTIUM2/3/4 CPU
         types - a modification to the version 04k implementation.
04k,22mar02,pai  Do not include <sysMtrr> table for P5/PENTIUM builds (SPR#
         73939).
04j,21mar02,pai  Make pciConfigShow configurable based upon the
         INCLUDE_PCI_CFGSHOW component (SPR 74274).
04i,12mar02,hdn  replaced redTable[] with sysInumTbl[] for HTT (spr 73738)
04h,07mar02,hdn  excluded MTRR code from P5 (spr 73939)
04g,03dec01,jkf  sysToMonitor: checks if device exists before creation,
         and using new macros for device and file name strings.
04f,27nov01,dmh  move include of iacsfl.h from sysLib.c to config.h
04e,16nov01,ahm  added power management mode initialization (SPR#32599)
04d,06nov01,hdn  added PIRQ[n] and IOAPIC support for Pentium4
04c,02nov01,dmh  add nvram for iacsfl boards. SPR# 70433
04b,01nov01,hdn  added MSRs init, reset PM, enabled MCA w pentiumMcaEnable()
04a,01nov01,jln  added support for gei82543End driver
03z,22oct01,dmh  replace iPiix4 support with pciAutoConfig. SPR# 65192.
03y,17oct01,hdn  removed duplicate sysMmuMapAdd() prototype.
         moved enabling MC exception into excArchLib.
         added LOCAL_MEM_AUTOSIZE in sysPhysMemTop().
         made LOWER_MEM_TOP configurable to preserve the MP table.
03x,11oct01,pai  Updating details related to BSP NIC driver support.  Removed
         INCLUDE_EEX32 and INCLUDE_FEI definition conditional on
         DOC macro.  Updated description of BSP driver config
         routines.  Added PCI library customization and BSP-specific
         PCI support.  Implemented new PCI Ethernet controller
         initialization (SPR# 35716) and (SPR# 69775).
03w,01oct01,hdn  replaced INT_NUM_GET(LPT0_INT_LVL) with INT_NUM_LPT0
03v,26sep01,pai  Added support for dec21x40End driver.  Added sysLn97xEnd
         driver configuration file.  Added WindML BSP routines.
         sysToMonitor() now opens bootrom.sys as RDONLY (SPR 23057).
03u,24sep01,pai  Updated LPT resource table and macros (SPR 30067).
03t,11sep01,hdn  renamed XXX_INT_VEC to INT_NUM_XXX as vector no of XXX
         updated sysIntEoiGet() as APIC's INT_LVL got cleaned up
         updated CPUID structure for PENTIUM4
         removed sysCodeSelector.
03s,16aug01,hdn  added PENTIUM2/3/4 support
03r,15aug01,hdn  included iacsfl.h if INCLUDE_IACSFL is defined.
03q,15jun00,jkf  release floppy disk on reboot(), SPR#30280
03p,15jun00,jkf  sysPhysMemTop() loop changed to report all found memory.
03o,03may00,mks  modified sysHwInit and sysToMonitor to support SFL based
         boot process.
03n,07sep99,stv  macros for including END driver components are
         conditioned according to SPR# 26296.
03m,21apr99,hdn  added conditional tffsDrv.h inclusion (SPR# 26922)
03l,12mar99,cn   added support for el3c90xEnd driver (SPR# 25327).
03k,09mar99,sbs  added support for ne2000End driver
         added support for ultraEnd driver
         added support for elt3c509End driver
03j,01feb99,jkf  added END support for AMD 7997x PCI card.
03i,26jan99,jkf  changed sysHwInit2 to use INCLUDE_ADD_BOOTMEM and
         removed ATA_MEM_DOSFS from sysToMonitor.  SPR#21338
03h,31mar98,cn   Added Enhanced Network Driver support.
03g,04jun98,hdn  made sysIntLevel() faster. added sysIntCount[] for debug.
03f,28may98,hdn  added support for APIC.
03e,12may98,hdn  merged with pcPentium/sysLib.c. obsolete INCLUDE_IDE.
03d,23apr98,yp   merged TrueFFS support.
03c,16apr98,hdn  added sysCpuid[] for sysCpuProbe().
03b,17mar98,sbs  using macro for dummy mmu entry.
         added forward declaration for sysMmuMapAdd().
         changed sysIntIdtType and sysWarmType to use macros.
         documentation update.
03a,12mar98,sbs  moved PCI initialization from sysPhysMemTop() to sysHwInit().
         changed the PCI library calls to the new updated library API.
         moved sys557PciInit() from sysPhysMemTop() to sysHwInit().
         added sysAic7880PciInit().
02z,02mar98,sbs  removed device specific mmu entries and added dynamic entries
         in sysPhysMemDesc table.
         added sysMmuMapAdd().
         added initialization of sysPhysMemDescNumEnt in sysHwInit().
02y,06jan98,hdn  included tffsDrv.h.
02x,15dec97,hdn  added support for warm start from TFFS device.
02w,10jul97,dds  added SCSI-2 support.
02v,24mar97,mas  added sysPhysMemTop(); removed NOMANUAL from sysHwInit2();
         parameterized the sysWarm* reboot variables (SPR 7806, 7850).
02u,03dec96,hdn  added sys557PciInit().
         moved PCI initialization from sysHwInit2() to sysMemTop().
02t,22nov96,dat  added sysNetif.c, for all network support rtns. (if_eex32.c
         and if_i82557 were combined into sysNetif.c)
02s,20nov96,db   conditionally defined INCLUDE_EEX32 for man page(SPR #6190).
02r,20nov96,hdn  added support for PRO100B.
02q,01nov96,hdn  added support for PCMCIA.
02p,21oct96,hdn  removed lptTimeout, added lptResources[].
02o,14oct96,dat  removed ref to i8253TimerTS.c, merged from windview102.
02n,24sep96,hdn  fixed by removing IMPORT ATA_RESOURCE ataResources[].
02m,03sep96,hdn  added the compression support.
         changed constants to ROM_WARM_HIGH and ROM_WARM_LOW.
02l,09aug96,hdn  renamed INT_VEC_IRQ0 to INT_NUM_IRQ0.
02k,26jul96,hdn  shut off warning message: "implicit declaration of function"
02j,18jul96,hdn  added support for INCLUDE_ATA.
02i,19jul96,wlf  doc: cleanup.
02h,25jun96,hdn  added support for TIMESTAMP timer.
02g,17jun96,hdn  initialized sysProcessor to NONE
02f,14jun96,hdn  added support for PCI bus.
02e,28may96,hdn  renamed PIT_INT_xxx to PIT0_INT_xxx.
02d,28sep95,dat  new BSP revision id
02c,27sep95,hdn  fixed a typo by changing IO_ADRS_ULTRA to IO_ADRS_ELC.
02b,14jun95,hdn  added a global variable sysCodeSelector.
         added a local function sysIntVecSetEnt(), sysIntVecSetExit().
         renamed pSysEndOfInt to intEOI.
         moved global function declarations to sysLib.h.
02a,14jun95,myz  moved serial configuration to sysSerial.c
01z,07jan95,hdn  added an accurate memory size checking.
01y,31oct94,hdn  changed sysMemTop() to find out a memory size.
         deleted sysGDT and used sysGdt in sysALib.s.
         added the Intel EtherExpress32 driver.
         deleted a conditional macro for INCLUDE_LPT.
         swapped 1st and 2nd parameter of fdDevCreate().
         imported globals to timeout IDE and LPT.
01x,12oct94,hdn  deleted sysBootType.
         added a conditional macro for INCLUDE_LPT.
01w,29may94,hdn  moved sysCpuProbe() to cacheArchLib.c.
         added open and read bootrom.dat in sysToMonitor().
01v,22apr94,hdn  moved sysVectorIRQ0 from i8259Pic.c.
         made new globals sysFdBuf and sysFdBufSize.
         supported the warm start from the EPROM.
01u,06apr94,hdn  added sysCpuProbe().
01t,17feb94,hdn  deleted memAddToPool() in sysHwInit2().
         added a conditional statement in sysMemTop().
         changed sysWarmType 0 to 1.
01s,03feb94,hdn  added MMU conditional macro for the limit in the GDT.
01r,29nov93,hdn  added sysBspRev () routine.
01q,22nov93,hdn  added xxdetach () routine for warm start.
01p,16nov93,hdn  added sysWarmType which controls warm start device.
01o,09nov93,hdn  added warm start (control X).
01n,08nov93,vin  added support pc console drivers.
01m,27oct93,hdn  added memAddToPool stuff to sysHwInit2().
01l,12oct93,hdn  changed PIT_INT_VEC_NUM to PIT_INT_VEC.
01k,05sep93,hdn  moved PIC related functions to intrCtl/i8259Pic.c.
         added sysDelay ().
01j,12aug93,hdn  changed a global descriptor table sysGDT.
         deleted sysGDTSet.
01i,11aug93,hdn  added a global sysVectorIRQ0.
01h,03aug93,hdn  changed a mapping IRQ to Vector Table.
01g,26jul93,hdn  added a memory descriptor table sysPhysMemDesc[].
01f,25jun93,hdn  changed sysToMonitor() to call sysReboot.
01e,24jun93,hdn  changed the initialization of PIC.
01d,17jun93,hdn  updated to 5.1.
01c,08apr93,jdi  doc cleanup.
01d,07apr93,hdn  renamed Compaq to PC.
01c,26mar93,hdn  added the global descriptor table, memAddToPool.
         moved enabling A20 to romInit.s. added cacheClear for 486.
01b,18nov92,hdn  supported nested interrupt.
01a,15may92,hdn  written based on frc386 version.
*/

/*
DESCRIPTION
This library provides board-specific routines.  The device configuration
modules and device drivers included are:

    i8253Timer.c - Intel 8253 timer driver
    i8259Intr.c - Intel 8259 Programmable Interrupt Controller (PIC) library
    ioApicIntr.c - Intel IO APIC/xAPIC driver
    ioApicIntrShow.c - Intel IO APIC/xAPIC driver show routines
    iPiix4Pci.c - low level initalization code for PCI ISA/IDE Xcelerator
    loApicIntr.c - Intel Pentium[234] Local APIC/xAPIC driver
    loApicIntrShow.c - Intel Local APIC/xAPIC driver show routines
    loApicTimer.c - Intel Pentium2/3/4 Local APIC timer library
    nullNvRam.c - null NVRAM library
    nullVme.c - null VMEbus library
    pccardLib.c - PC CARD enabler library
    pccardShow.c - PC CARD show library
    pciCfgStub.c - customizes pciConfigLib for the BSP
    pciCfgIntStub.c - customizes pciIntLib for the BSP
    pciConfigLib.c - PCI configuration space access support for PCI drivers
    pciIntLib.c - PCI shared interrupt support
    pciConfigShow.c - Show routines for PCI configuration library
    sysDec21x40End.c - system configuration module for dec21x40End driver
    sysEl3c509End.c - system configuratin module for elt3c509End driver
    sysEl3c90xEnd.c -  system configuration module for el3c90xEnd driver
    sysFei82557End.c - system configuration module for fei82557End driver
    sysGei82543End.c - system configuration module for gei82543End driver
    sysLn97xEnd.c - system configuration module for ln97xEnd driver
    sysNe2000End.c - system configuration module for ne2000End driver
    sysUltraEnd.c - system configuration module for SMC Elite ultraEnd driver
    sysWindML.c - WindML BSP support routines


INCLUDE FILES: sysLib.h

SEE ALSO:
.pG "Configuration"
*/

/* includes (header file) */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vme.h>
#include <memLib.h>
#include <sysLib.h>
#include <string.h>
#include <intLib.h>
#include <config.h>
#include <logLib.h>
#include <taskLib.h>
#include <vxLib.h>
#include <errnoLib.h>
#include <dosFsLib.h>
#include <stdio.h>
#include <cacheLib.h>
#include <vmLib.h>
#include <arch/i86/pentiumLib.h>

#include "PciCanLib.h"

#if defined(_WRS_CONFIG_WRHV_GUEST)
#include <wrhv/vbi.h>
#include <vxbTimerLib.h>
#endif

#if defined (VIRTUAL_WIRE_MODE) || defined (SYMMETRIC_IO_MODE)
#include <hwif/intCtlr/vxbMpApic.h>
#endif /* VIRTUAL_WIRE_MODE || SYMMETRIC_IO_MODE */

#ifdef _WRS_CONFIG_SMP
#include <private/kernelLibP.h>
#include <private/windLibP.h>
#include <private/vxSmpP.h>
#include <arch/i86/regsI86.h>
#include <cpuset.h>
#include <vxIpiLib.h>
#include <arch/i86/ipiI86Lib.h>
#endif /* _WRS_CONFIG_SMP */

#include <arch/i86/vxCpuArchLib.h>

#include <vxBusLib.h>
#ifdef  INCLUDE_TFFS
#   include <tffs/tffsDrv.h>
#endif  /* INCLUDE_TFFS */

#ifdef  INCLUDE_SMCFDC37B78X
#   include <drv/multi/smcFdc37b78x.h>
#   ifndef PRJ_BUILD
#       include <multi/smcFdc37b78x.c>
#   endif /* PRJ_BUILD */
#endif  /* INCLUDE_SMCFDC37B78X */

#ifdef INCLUDE_ATA
#include "sysAta.c"
#endif
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
#include "sysIch.c"
#endif /* INCLUDE_DRV_STORAGE_INTEL_ICH */

#ifndef INCLUDE_VXBUS
#if defined(INCLUDE_PC_CONSOLE) && defined(INCLUDE_CTB69000VGA)
#   ifndef PRJ_BUILD
#       include <video/ctB69000Vga.c>
#   endif /* PRJ_BUILD */
#endif  /* INCLUDE_PC_CONSOLE && INCLUDE_CTB69000VGA */
#else
#include <hwif/timer/vxbHpetLib.h>
#endif /* !INCLUDE_VXBUS */

#ifdef _WRS_CONFIG_SMP
#if (CPU != PENTIUM4)
#error "The SMP BSP is based off of pcPentium4 only !!!"
#endif  /* (CPU == PENTIUM4) */
#endif /* _WRS_CONFIG_SMP */

#ifdef _WRS_CONFIG_SMP
#if (!defined(SYMMETRIC_IO_MODE))
#error "For the SMP BSP one must define SYMMETRIC_IO_MODE !!!"
#endif
#endif /* _WRS_CONFIG_SMP */

/* defines */

#define ROM_SIGNATURE_SIZE  16

#if (VM_PAGE_SIZE == PAGE_SIZE_4KB)
#   if  (LOCAL_MEM_LOCAL_ADRS >= 0x00100000)
#       define LOCAL_MEM_SIZE_OS    0x00180000  /* n * VM_PAGE_SIZE */
#   else
#       define LOCAL_MEM_SIZE_OS    0x00080000  /* n * VM_PAGE_SIZE */
#   endif /* (LOCAL_MEM_LOCAL_ADRS >= 0x00100000) */
#else   /* VM_PAGE_SIZE is 2/4MB */
#   define LOCAL_MEM_SIZE_OS        VM_PAGE_SIZE    /* n * VM_PAGE_SIZE */
#endif  /* (VM_PAGE_SIZE == PAGE_SIZE_4KB) */

/*
 * IA-32 protected mode physical address space 4GB (2^32) and protected
 * mode physical address space extension 64GB (2^36) size constants.
 */

#define SIZE_ADDR_SPACE_32   (0x100000000ull)
#define SIZE_ADDR_SPACE_36   (0x1000000000ull)

/* maximum address space probed when using memory auto-sizing */

#define PHYS_MEM_MAX         (SIZE_ADDR_SPACE_32)

#define HALF(x)              (((x) + 1) >> 1)

/* sysPhysMemTop() memory test patterns */

#define TEST_PATTERN_A       (0x57696E64)
#define TEST_PATTERN_B       (0x52697665)
#define TEST_PATTERN_C       (0x72537973)
#define TEST_PATTERN_D       (0x74656D73)

/* Extended BIOS Data Area */

#ifndef EBDA_START
#define EBDA_START              0x9d000
#endif

/* imports */

#if defined(SYMMETRIC_IO_MODE)
/*
 * These globals (glbLoApicOldSvr, glbLoApicOldLint0, glbLoApicOldLint1)
 * are used in sysLib.c, they avoid calling through vxbus and reduces
 * overhead, potential spinLock nesting...
 */

IMPORT UINT32 glbLoApicOldSvr;        /* original SVR */
IMPORT UINT32 glbLoApicOldLint0;      /* original LINT0 */
IMPORT UINT32 glbLoApicOldLint1;      /* original LINT1 */
#endif /* SYMMETRIC_IO_MODE */

#ifdef _WRS_CONFIG_SMP
IMPORT cpuset_t vxCpuEnabled;

IMPORT TSS      sysTss;
#endif /* _WRS_CONFIG_SMP */

#ifndef _WRS_CONFIG_SMP
IMPORT int         intCnt;                    /* interrupt mode counter */
#endif /* !_WRS_CONFIG_SMP */

IMPORT char        end;                       /* linker defined end-of-image */
IMPORT GDT         sysGdt[];                  /* the global descriptor table */
IMPORT void        elcdetach (int unit);
IMPORT VOIDFUNCPTR intEoiGet;                 /* BOI/EOI function pointer */
IMPORT void        intEnt (void);
IMPORT int         sysCpuProbe (void);        /* set a type of CPU family */

IMPORT void        sysInitGDT (void);

#ifdef _WRS_CONFIG_SMP
IMPORT void sysInitCpuStartup(void);

#if defined (INCLUDE_RTP)
IMPORT STATUS syscallArchInit (void);
#endif /* INCLUDE_RTP */

#if defined INCLUDE_PROTECT_TASK_STACK || defined INCLUDE_PROTECT_INTERRUPT_STACK
#if defined(_WRS_OSM_INIT)
IMPORT STATUS excOsmInit (UINT32, UINT32);
#endif /* defined(_WRS_OSM_INIT) */
#endif  /* INCLUDE_PROTECT_TASK_STACK || INCLUDE_PROTECT_INTERRUPT_STACK */

#endif /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_VXBUS
#ifdef INCLUDE_SIO_UTILS
IMPORT void    sysSerialConnectAll(void);
#endif /* INCLUDE_SIO_UTILS */
IMPORT void    hardWareInterFaceInit();
IMPORT FUNCPTR sysIntLvlEnableRtn;
IMPORT FUNCPTR sysIntLvlDisableRtn;
STATUS sysIntEnablePIC (int irqNo);
STATUS sysIntDisablePIC (int irqNo);
#endif /* INCLUDE_VXBUS */

#ifdef INCLUDE_BCM43XX_END
IMPORT void sysBroadComWLBusInit(void);
#endif /* INCLUDE_BCM43XX_END */

#if (CPU == PENTIUM2) || (CPU == PENTIUM3) || (CPU == PENTIUM4)
#if defined (INCLUDE_MMU_P6_32BIT)
IMPORT STATUS mmuPro32Enable (BOOL enable);   /* disable MMU */
#else
IMPORT STATUS mmuPro36Enable (BOOL enable);   /* disable MMU */
#endif /* defined (INCLUDE_MMU_P6_32BIT) */
#else
IMPORT STATUS mmuI86Enable (BOOL enable);     /* disable MMU */
#endif  /* (CPU == PENTIUM) || (CPU == PENTIUM[234]) */

IMPORT void vxGdtrSet (long long int * pGdtr);

/* globals */

#if defined(_WRS_CONFIG_WRHV_GUEST)
IMPORT void vIoApicIntLock (void);
IMPORT void vIoApicIntUnlock (void);
IMPORT STATUS vIoApicIntEnable (UINT32 entry);
IMPORT STATUS vIoApicIntDisable (UINT32 entry);
IMPORT void vIoApicIntAck (UINT32 entry);

/* pointers to hypervisor data structures */

VB_CONFIG  *wrhvVbConfig  = (void *)-1;
VB_STATUS  *wrhvVbStatus  = (void *)-1;
VB_CONTROL *wrhvVbControl = (void *)-1;
int    sysConsoleTty	=  BOARD_UART1;
#endif /* _WRS_CONFIG_WRHV_GUEST */

PHYS_MEM_DESC sysPhysMemDesc [] =
    {

    /* adrs and length parameters must be page-aligned (multiples of 4KB/4MB) */

#if (VM_PAGE_SIZE == PAGE_SIZE_4KB)

    /*
     * Any code access to the invalid address range will generate
     * a MMU exception and the offending task will be suspended.
     * Then use l(), lkAddr, ti(), and tt() to find the NULL access.
     */

    /* lower memory for invalid access */

    {
    (VIRT_ADDR) 0x0,
    (PHYS_ADDR) 0x0,
    _WRS_BSP_VM_PAGE_OFFSET,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

    /* lower memory for valid access */

    {
    (VIRT_ADDR) _WRS_BSP_VM_PAGE_OFFSET,
    (PHYS_ADDR) _WRS_BSP_VM_PAGE_OFFSET,
    0xa0000 - _WRS_BSP_VM_PAGE_OFFSET,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

    /* video ram, etc */

    {
    (VIRT_ADDR) 0x000a0000,
    (PHYS_ADDR) 0x000a0000,
    0x00060000,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_IO
    },

#   if (LOCAL_MEM_LOCAL_ADRS >= 0x00100000)

    /* upper memory for OS */

    {
    (VIRT_ADDR) LOCAL_MEM_LOCAL_ADRS,
    (PHYS_ADDR) LOCAL_MEM_LOCAL_ADRS,
    LOCAL_MEM_SIZE_OS,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

    /* upper memory for Application */

    {
    (VIRT_ADDR) LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE_OS,
    (PHYS_ADDR) LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE_OS,
    LOCAL_MEM_SIZE - LOCAL_MEM_SIZE_OS, /* it is changed in sysMemTop() */
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_APPLICATION
    },

#   else /* LOCAL_MEM_LOCAL_ADRS is 0x0 */

    /* upper memory for OS */

    {
    (VIRT_ADDR) 0x00100000,
    (PHYS_ADDR) 0x00100000,
    LOCAL_MEM_SIZE_OS,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

    /* upper memory for Application */

    {
    (VIRT_ADDR) 0x00100000 + LOCAL_MEM_SIZE_OS,
    (PHYS_ADDR) 0x00100000 + LOCAL_MEM_SIZE_OS,
    LOCAL_MEM_SIZE - (0x00100000 + LOCAL_MEM_SIZE_OS),  /* sysMemTop() fix */
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_APPLICATION
    },

#   endif /* (LOCAL_MEM_LOCAL_ADRS >= 0x00100000) */

#   if defined(INCLUDE_SM_NET) && (SM_MEM_ADRS != 0x0)

    /* upper memory for sm net/obj pool */

    {
    (VIRT_ADDR) SM_MEM_ADRS,
    (PHYS_ADDR) SM_MEM_ADRS,
    SM_MEM_SIZE + SM_OBJ_MEM_SIZE,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_APPLICATION
    },

#   endif /* defined(INCLUDE_SM_NET) && (SM_MEM_ADRS != 0x0) */

#else   /* VM_PAGE_SIZE is 2/4MB */

    /* 1st 2/4MB: lower mem + video ram etc + sm pool + upper mem */

    {
    (VIRT_ADDR) 0x0,
    (PHYS_ADDR) 0x0,
    VM_PAGE_SIZE,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

#   if (LOCAL_MEM_LOCAL_ADRS >= VM_PAGE_SIZE)

    /* 2nd 2/4MB: upper memory for OS */

    {
    (VIRT_ADDR) LOCAL_MEM_LOCAL_ADRS,
    (PHYS_ADDR) LOCAL_MEM_LOCAL_ADRS,
    LOCAL_MEM_SIZE_OS,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

    /* remaining 2/4MB pages: upper memory for Application */

    {
    (VIRT_ADDR) LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE_OS,
    (PHYS_ADDR) LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE_OS,
    LOCAL_MEM_SIZE - LOCAL_MEM_SIZE_OS, /* it is changed in sysMemTop() */
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_APPLICATION
    },

#   else /* LOCAL_MEM_LOCAL_ADRS is 0x0 */

    /* 2nd 2/4MB: upper memory for OS */

    {
    (VIRT_ADDR) VM_PAGE_SIZE,
    (PHYS_ADDR) VM_PAGE_SIZE,
    LOCAL_MEM_SIZE_OS,
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_OS
    },

    /* remaining 2/4MB pages: upper memory for Application */

    {
    (VIRT_ADDR) VM_PAGE_SIZE + LOCAL_MEM_SIZE_OS,
    (PHYS_ADDR) VM_PAGE_SIZE + LOCAL_MEM_SIZE_OS,
    LOCAL_MEM_SIZE - (VM_PAGE_SIZE + LOCAL_MEM_SIZE_OS), /* sysMemTop() fix */
    VM_STATE_MASK_FOR_ALL,
    VM_STATE_FOR_MEM_APPLICATION
    },

#   endif /* (LOCAL_MEM_LOCAL_ADRS >= VM_PAGE_SIZE) */

#endif  /* (VM_PAGE_SIZE == PAGE_SIZE_4KB) */

    /* entries for dynamic mappings - create sufficient entries */

    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
    DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
	DUMMY_MMU_ENTRY,
    };

int sysPhysMemDescNumEnt;   /* number Mmu entries to be mapped */

#ifndef INCLUDE_VXBUS
#ifdef  INCLUDE_PC_CONSOLE

PC_CON_DEV  pcConDv [N_VIRTUAL_CONSOLES] =
    {
    {{{{NULL}}}, FALSE, NULL, NULL},
    {{{{NULL}}}, FALSE, NULL, NULL}
    };

#endif  /* INCLUDE_PC_CONSOLE */
#endif /* INCLUDE_VXBUS */

#ifdef INCLUDE_FD

IMPORT STATUS usrFdConfig (int type, int drive, char *fileName);
FD_TYPE fdTypes[] =
    {
    {2880,18,2,80,2,0x1b,0x54,0x00,0x0c,0x0f,0x02,1,1,"1.44M"},
    {2400,15,2,80,2,0x24,0x50,0x00,0x0d,0x0f,0x02,1,1,"1.2M"},
    };
UINT    sysFdBuf     = FD_DMA_BUF_ADDR; /* floppy disk DMA buffer address */
UINT    sysFdBufSize = FD_DMA_BUF_SIZE; /* floppy disk DMA buffer size */

#endif  /* INCLUDE_FD */

#ifdef  INCLUDE_ATA

IMPORT STATUS usrAtaConfig (int ctrl, int drive, char *fileName);
#endif /* INCLUDE_ATA */

#if defined (INCLUDE_ATA) || defined (INCLUDE_DRV_STORAGE_INTEL_ICH)
ATA_TYPE ataTypes[ATA_MAX_CTRLS][ATA_MAX_DRIVES] =
    {

    /* controller zero */

    {

        /* ctrl 0 drive 0 */

        {
        ATA_CTRL0_DRV0_CYL,    /* Number of cylinders on device */
        ATA_CTRL0_DRV0_HDS,    /* Number of heads on device */
        ATA_CTRL0_DRV0_SPT,    /* Number of sectors per track on device */
        ATA_CTRL0_DRV0_BPS,    /* Number of bytes per sector on device */
        ATA_CTRL0_DRV0_WPC     /* write precompensation 0xff = don't use */
        },

        /* ctrl 0 drive 1 */

        {
        ATA_CTRL0_DRV1_CYL,    /* Number of cylinders on device */
        ATA_CTRL0_DRV1_HDS,    /* Number of heads on device */
        ATA_CTRL0_DRV1_SPT,    /* Number of sectors per track on device */
        ATA_CTRL0_DRV1_BPS,    /* Number of bytes per sector on device */
        ATA_CTRL0_DRV1_WPC     /* write precompensation 0xff = don't use */
        },
   },

   /* controller one */

   {
        /* ctrl 1 drive 0 */

        {
        ATA_CTRL1_DRV0_CYL,    /* Number of cylinders on device */
        ATA_CTRL1_DRV0_HDS,    /* Number of heads on device */
        ATA_CTRL1_DRV0_SPT,    /* Number of sectors per track on device */
        ATA_CTRL1_DRV0_BPS,    /* Number of bytes per sector on device */
        ATA_CTRL1_DRV0_WPC     /* write precompensation 0xff = don't use */
        },

        /* ctrl 1 drive 1 */

        {
        ATA_CTRL1_DRV1_CYL,    /* Number of cylinders on device */
        ATA_CTRL1_DRV1_HDS,    /* Number of heads on device */
        ATA_CTRL1_DRV1_SPT,    /* Number of sectors per track on device */
        ATA_CTRL1_DRV1_BPS,    /* Number of bytes per sector on device */
        ATA_CTRL1_DRV1_WPC     /* write precompensation 0xff = don't use */
        }
    }
    };

ATA_RESOURCE ataResources[ATA_MAX_CTRLS] =
    {

    /* ATA controller zero resources */

    {

        /*  PCCARD_RESOURCE */

        {
        ATA0_VCC,             /* 3-5 volts Vcc */
        ATA0_VPP,             /* 5-12 volts Vpp */
            {
            ATA0_IO_START0,   /* start I/O address 0 */
            ATA0_IO_START1    /* start I/O address 1 */
            },

            {
            ATA0_IO_STOP0,    /* end I/0 address 0 */
            ATA0_IO_STOP1     /* end I/0 address 1 */
            },
        ATA0_EXTRA_WAITS,     /* extra wait states 0-2 */
        ATA0_MEM_START,       /* start host mem address */
        ATA0_MEM_STOP,        /* stop host mem address */
        ATA0_MEM_WAITS,       /* mem extra wait states 0-2 */
        ATA0_MEM_OFFSET,      /* mem offset of card address */
        ATA0_MEM_LENGTH       /* length of memory */
        },
    ATA0_CTRL_TYPE,           /* IDE_LOCAL or ATA_PCMCIA */
    ATA0_NUM_DRIVES,          /* number of drives on controller */
    INT_NUM_ATA0,             /* interrupt number of controller */
    ATA0_INT_LVL,             /* interrupt level of controller */
    ATA0_CONFIG,              /* device configuration settings */
    ATA0_SEM_TIMEOUT,         /* semaphore timeout for controller */
    ATA0_WDG_TIMEOUT,         /* watchdog timeout for controller */
    ATA0_SOCKET_TWIN,         /* socket number for twin card */
    ATA0_POWER_DOWN           /* power down mode for this controller */
    },  /* ctrl 0 end */

    /* ATA controller one resources */

    {

        /*  PCCARD_RESOURCE */

        {
        ATA1_VCC,             /* 3-5 volts Vcc */
        ATA1_VPP,             /* 5-12 volts Vpp */
            {
            ATA1_IO_START0,   /* start I/O address 0 */
            ATA1_IO_START1    /* start I/O address 1 */
            },

            {
            ATA1_IO_STOP0,    /* end I/0 address 0 */
            ATA1_IO_STOP1     /* end I/0 address 1 */
            },
        ATA1_EXTRA_WAITS,     /* extra wait states 0-2 */
        ATA1_MEM_START,       /* start host mem address */
        ATA1_MEM_STOP,        /* stop host mem address */
        ATA1_MEM_WAITS,       /* mem extra wait states 0-2 */
        ATA1_MEM_OFFSET,      /* mem offset of card address */
        ATA1_MEM_LENGTH       /* length of memory */
        },
    ATA1_CTRL_TYPE,           /* IDE_LOCAL or ATA_PCMCIA */
    ATA1_NUM_DRIVES,          /* number of drives on controller */
    INT_NUM_ATA1,             /* interrupt number of controller */
    ATA1_INT_LVL,             /* interrupt level of controller */
    ATA1_CONFIG,              /* device configuration settings */
    ATA1_SEM_TIMEOUT,         /* semaphore timeout for controller */
    ATA1_WDG_TIMEOUT,         /* watchdog timeout for controller */
    ATA1_SOCKET_TWIN,         /* socket number for twin card */
    ATA1_POWER_DOWN           /* power down mode for this controller */
    }   /* ctrl 1 end */
    };
#endif /* defined (INCLUDE_ATA) || defined (INCLUDE_DRV_STORAGE_INTEL_ICH) */

#ifdef  INCLUDE_LPT

LPT_RESOURCE lptResources [N_LPT_CHANNELS] =
    {
    {LPT0_BASE_ADRS, INT_NUM_LPT0, LPT0_INT_LVL,
    TRUE, 10000, 10000, 1, 1, 0
    },

    {LPT1_BASE_ADRS, INT_NUM_LPT1, LPT1_INT_LVL,
    TRUE, 10000, 10000, 1, 1, 0
    },

    {LPT2_BASE_ADRS, INT_NUM_LPT2, LPT2_INT_LVL,
    TRUE, 10000, 10000, 1, 1, 0
    }
    };

#endif  /* INCLUDE_LPT */

int     sysBus = BUS;      /* system bus type (VME_BUS, etc) */
int     sysCpu = CPU;      /* system cpu type (MC680x0) */

char    *sysBootLine = BOOT_LINE_ADRS; /* address of boot line */
char    *sysExcMsg   = EXC_MSG_ADRS; /* catastrophic message area */

int     sysProcNum;         /* processor number of this cpu */

UINT    sysIntIdtType   = SYS_INT_INTGATE;  /* IDT entry type */
UINT    sysProcessor    = (UINT) NONE;      /* 0=386, 1=486, 2=P5, 4=P6, 5=P7 */
UINT    sysCoprocessor  = 0;        /* 0=none, 1=387, 2=487 */

int     sysWarmType = SYS_WARM_TYPE;      /* system warm boot type */
int     sysWarmFdDrive  = SYS_WARM_FD_DRIVE;  /* 0 = drive a:, 1 = b: */
int     sysWarmFdType   = SYS_WARM_FD_TYPE;   /* 0 = 3.5" 2HD, 1 = 5.25" 2HD */
int     sysWarmAtaCtrl  = SYS_WARM_ATA_CTRL;  /* controller 0 or 1 */
int     sysWarmAtaDrive = SYS_WARM_ATA_DRIVE; /* Hd drive 0 (c:), 1 (d:) */
int     sysWarmTffsDrive= SYS_WARM_TFFS_DRIVE; /* TFFS drive 0 (DOC) */

UINT    sysStrayIntCount = 0;       /* Stray interrupt count */

char    *memTopPhys = NULL;     /* top of memory */
char    *memRom     = NULL;     /* saved bootrom image */

/* Initial GDT to be initialized */

GDT *pSysGdt    = (GDT *)(LOCAL_MEM_LOCAL_ADRS + GDT_BASE_OFFSET);

/* mpCpuIndexTable is used in vxCpuArchLib.c, this gloabal avoids
 * calling through vxbus and reduces overhead, table translations
 * are done everywhere, but once up this table should never change...
 */
                                                                                
UINT8 mpCpuIndexTable[256];

#ifdef _WRS_CONFIG_SMP

/* TSS initialized */

TSS *sysTssCurrent = &sysTss;                   /* current sysTss */

FUNCPTR sysCpuInitTable[VX_MAX_SMP_CPUS] = {NULL};
unsigned int sysCpuLoopCount[VX_MAX_SMP_CPUS] = {0};
#else
TSS      sysTss;
#endif /* _WRS_CONFIG_SMP */

#ifdef _WRS_CONFIG_SMP
#ifdef DRV_TIMER_IA_TIMESTAMP
/* SMP requires an High Precision Event Timer for Timestamp. */

LOCAL void hpetMmuMap (void);
LOCAL void hpetInit (void);
#endif /* DRV_TIMER_IA_TIMESTAMP */
#endif /* _WRS_CONFIG_SMP */

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
/* These are used in sysLib.c to avoid calling out
 * through vxbus to reduces overhead, and potential
 * spinLock nesting...
 */

#if defined(SYMMETRIC_IO_MODE)
LOCAL VXB_DEVICE_ID ioApicDevID;

#ifdef _WRS_CONFIG_SMP
LOCAL UINT8 tramp_code[CPU_AP_AREA];
#endif /* _WRS_CONFIG_SMP */
#endif /* SYMMETRIC_IO_MODE */

LOCAL VXB_DEVICE_ID mpApicDevID;
LOCAL VXB_DEVICE_ID loApicDevID;

STATUS apicIntrIntHelper(VXB_DEVICE_ID pDev, void * unused);

LOCAL STATUS (*getMpApicLoIndexTable)(VXB_DEVICE_ID pInst,
                                      UINT8 ** mploApicIndexTable);
LOCAL STATUS (*getMpApicloBaseGet) (VXB_DEVICE_ID  pInst,
                                    UINT32 *mpApicloBase);
#if defined(SYMMETRIC_IO_MODE)
LOCAL STATUS (*getMpApicNioApicGet) (VXB_DEVICE_ID  pInst,
                                     UINT32 *mpApicNioApic);
LOCAL STATUS (*getMpApicAddrTableGet) (VXB_DEVICE_ID  pInst,
                                       UINT32 **mpApicAddrTable);

LOCAL STATUS (*getIoApicRedNumEntriesGet)(VXB_DEVICE_ID pInst,
                                          UINT8 *ioApicRedNumEntries);

LOCAL STATUS (*getIoApicIntrIntEnable)(VXB_DEVICE_ID pInst, 
		                       INT32 * irqNo);
LOCAL STATUS (*getIoApicIntrIntDisable)(VXB_DEVICE_ID pInst, 
		                        INT32 * irqNo);

LOCAL STATUS (*getIoApicIntrIntLock)(VXB_DEVICE_ID pInst, int * dummy);
LOCAL STATUS (*getIoApicIntrIntUnlock)(VXB_DEVICE_ID pInst, int * dummy);
#endif /* SYMMETRIC_IO_MODE */

LOCAL STATUS (*getLoApicIntrInitAP)(VXB_DEVICE_ID pInst, int *dummy);
LOCAL STATUS (*getLoApicIntrEnable)(VXB_DEVICE_ID pInst, BOOL *enable);

LOCAL STATUS (*getLoApicIntrIntLock)(VXB_DEVICE_ID pInst, int * dummy);
LOCAL STATUS (*getLoApicIntrIntUnlock)(VXB_DEVICE_ID pInst, int * dummy);

void sysStaticMpApicDataGet(MP_APIC_DATA *pMpApicData);
#endif /*  defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE) */

CPUID   sysCpuId    = {0,{0},0,0,0,0,0,0,0,0,{0,1},{0}}; /* CPUID struct. */

#ifndef _WRS_CONFIG_SMP
BOOL    sysBp       = TRUE;     /* TRUE for BP, FALSE for AP */
#endif /* !_WRS_CONFIG_SMP */

#if defined (VIRTUAL_WIRE_MODE)
UINT8   vwInumTbl[]    =        /* IRQ vs IntNum table for VIRTUAL_WIRE_MODE */
    {
    INT_NUM_IRQ0,               /* IRQ  0 Vector No */
    INT_NUM_IRQ0 + 1,           /* IRQ  1 Vector No */
    INT_NUM_IRQ0 + 2,           /* IRQ  2 Vector No */
    INT_NUM_IRQ0 + 3,           /* IRQ  3 Vector No */
    INT_NUM_IRQ0 + 4,           /* IRQ  4 Vector No */
    INT_NUM_IRQ0 + 5,           /* IRQ  5 Vector No */
    INT_NUM_IRQ0 + 6,           /* IRQ  6 Vector No */
    INT_NUM_IRQ0 + 7,           /* IRQ  7 Vector No */
    INT_NUM_IRQ0 + 8,           /* IRQ  8 Vector No */
    INT_NUM_IRQ0 + 9,           /* IRQ  9 Vector No */
    INT_NUM_IRQ0 + 10,          /* IRQ 10 Vector No */
    INT_NUM_IRQ0 + 11,          /* IRQ 11 Vector No */
    INT_NUM_IRQ0 + 12,          /* IRQ 12 Vector No */
    INT_NUM_IRQ0 + 13,          /* IRQ 13 Vector No */
    INT_NUM_IRQ0 + 14,          /* IRQ 14 Vector No */
    INT_NUM_IRQ0 + 15,          /* IRQ 15 Vector No */
    INT_NUM_LOAPIC_TIMER,       /* Local APIC Timer Vector No */
    INT_NUM_LOAPIC_ERROR,       /* Local APIC Error Vector No */
    INT_NUM_LOAPIC_LINT0,       /* Local APIC LINT0 Vector No */
    INT_NUM_LOAPIC_LINT1,       /* Local APIC LINT1 Vector No */
    INT_NUM_LOAPIC_PMC,         /* Local APIC PMC Vector No */
    INT_NUM_LOAPIC_THERMAL,     /* Local APIC Thermal Vector No */
    INT_NUM_LOAPIC_SPURIOUS,    /* Local APIC Spurious Vector No */
    INT_NUM_LOAPIC_SM,          /* Local APIC SM Vector No */
    INT_NUM_LOAPIC_SM + 1,      /* Local APIC SM Vector No */
    INT_NUM_LOAPIC_SM + 2,      /* Local APIC SM Vector No */
    INT_NUM_LOAPIC_SM + 3,      /* Local APIC SM Vector No */
    INT_NUM_LOAPIC_IPI,         /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 1,     /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 2,     /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 3,     /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 4,     /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 5,     /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 6,     /* Local APIC IPI Vector No */
    INT_NUM_LOAPIC_IPI + 7      /* Local APIC IPI Vector No */
    };
#endif /* defined (VIRTUAL_WIRE_MODE) */

#if defined(SYMMETRIC_IO_MODE)
/*
 * Under SYMMETRIC_IO_MODE sysInumTbl is created dynamically under the IO Apic
 * driver initialization.
 *
 * Multiple IO Apics are used in high-end servers to distribute irq load.
 * At this time there may be as many as 8 IO Apics in a system. The most common
 * number of inputs on a single IO Apic is 24, but they also designed for
 * 16/32/or 64 inputs.
 *
 * The common case here is a 1:1 irq<=>pin mapping.
 *
 * The mapping is critical to system operation. We need to support the first
 * 16 interrupts as legacy ISA/EISA.
 *
 * irq 0,1,2,3,4,6,8,12,13,14, and 15 are typically consumed by legacy devices.
 *
 * irq 5,7,9,10, and 11 are typically available for general use (though 5 is
 * sometimes used for audio devices and 7 is used for LPT).
 *
 * 16,17,18, and 19 are typically used for standard PCI.
 *
 * Each of the interrupts can be used programmed with any of the 224 vectors the
 * CPU is capable of. The first IO Apic will handle the ISA/EISA interrupts.
 *
 * The way this will work: if (irq <= 16) just map the irq to whatever pin is
 * requested. If (irq > 16) we enforce the mapping irq =
 * (apic*num_ioapic_entriess)+pin.
 *
 * This means that given any irq we can always derive the apic and pin.
 *
 *          apic from irq => irq / num_ioapic_entriess
 *
 *          pin from irq  => irq % num_ioapic_entriess
 */
#endif /* SYMMETRIC_IO_MODE */

UINT8   dfltInumTbl[]    =       /* IRQ vs IntNum table for default interrupt handling */
    {
    INT_NUM_IRQ0,               /* IRQ  0 Vector No */
    INT_NUM_IRQ0 + 1,           /* IRQ  1 Vector No */
    INT_NUM_IRQ0 + 2,           /* IRQ  2 Vector No */
    INT_NUM_IRQ0 + 3,           /* IRQ  3 Vector No */
    INT_NUM_IRQ0 + 4,           /* IRQ  4 Vector No */
    INT_NUM_IRQ0 + 5,           /* IRQ  5 Vector No */
    INT_NUM_IRQ0 + 6,           /* IRQ  6 Vector No */
    INT_NUM_IRQ0 + 7,           /* IRQ  7 Vector No */
    INT_NUM_IRQ0 + 8,           /* IRQ  8 Vector No */
    INT_NUM_IRQ0 + 9,           /* IRQ  9 Vector No */
    INT_NUM_IRQ0 + 10,          /* IRQ 10 Vector No */
    INT_NUM_IRQ0 + 11,          /* IRQ 11 Vector No */
    INT_NUM_IRQ0 + 12,          /* IRQ 12 Vector No */
    INT_NUM_IRQ0 + 13,          /* IRQ 13 Vector No */
    INT_NUM_IRQ0 + 14,          /* IRQ 14 Vector No */
    INT_NUM_IRQ0 + 15,          /* IRQ 15 Vector No */
#ifdef _WRS_CONFIG_WRHV_GUEST
    INT_NUM_IRQ0 + 16,          /* IRQ 16 Vector No */
    INT_NUM_IRQ0 + 17,          /* IRQ 17 Vector No */
    INT_NUM_IRQ0 + 18,          /* IRQ 18 Vector No */
    INT_NUM_IRQ0 + 19,          /* IRQ 19 Vector No */
    INT_NUM_IRQ0 + 20,          /* IRQ 20 Vector No */
    INT_NUM_IRQ0 + 21,          /* IRQ 21 Vector No */
    INT_NUM_IRQ0 + 22,          /* IRQ 22 Vector No */
    INT_NUM_IRQ0 + 23,          /* IRQ 23 Vector No */
    INT_NUM_IRQ0 + 24,          /* IRQ 24 Vector No */
    INT_NUM_IRQ0 + 25,          /* IRQ 25 Vector No */
    INT_NUM_IRQ0 + 26,          /* IRQ 26 Vector No */
    INT_NUM_IRQ0 + 27,          /* IRQ 27 Vector No */
    INT_NUM_IRQ0 + 28,          /* IRQ 28 Vector No */
    INT_NUM_IRQ0 + 29,          /* IRQ 29 Vector No */
    INT_NUM_IRQ0 + 30,          /* IRQ 30 Vector No */
    INT_NUM_IRQ0 + 31,          /* IRQ 31 Vector No */

    INT_NUM_IRQ0 + 32,          /* IRQ 32 Vector No */
    INT_NUM_IRQ0 + 33,          /* IRQ 33 Vector No */
    INT_NUM_IRQ0 + 34,          /* IRQ 34 Vector No */
    INT_NUM_IRQ0 + 35,          /* IRQ 35 Vector No */
    INT_NUM_IRQ0 + 36,          /* IRQ 36 Vector No */
    INT_NUM_IRQ0 + 37,          /* IRQ 37 Vector No */
    INT_NUM_IRQ0 + 38,          /* IRQ 38 Vector No */
    INT_NUM_IRQ0 + 39,          /* IRQ 39 Vector No */
    INT_NUM_IRQ0 + 40,          /* IRQ 40 Vector No */
    INT_NUM_IRQ0 + 41,          /* IRQ 41 Vector No */
    INT_NUM_IRQ0 + 42,          /* IRQ 42 Vector No */
    INT_NUM_IRQ0 + 43,          /* IRQ 43 Vector No */
    INT_NUM_IRQ0 + 44,          /* IRQ 44 Vector No */
    INT_NUM_IRQ0 + 45,          /* IRQ 45 Vector No */
    INT_NUM_IRQ0 + 46,          /* IRQ 46 Vector No */
    INT_NUM_IRQ0 + 47,          /* IRQ 47 Vector No */

    INT_NUM_IRQ0 + 48,          /* IRQ 48 Vector No */
    INT_NUM_IRQ0 + 49,          /* IRQ 49 Vector No */
    INT_NUM_IRQ0 + 50,          /* IRQ 50 Vector No */
    INT_NUM_IRQ0 + 51,          /* IRQ 51 Vector No */
    INT_NUM_IRQ0 + 52,          /* IRQ 52 Vector No */
    INT_NUM_IRQ0 + 53,          /* IRQ 53 Vector No */
    INT_NUM_IRQ0 + 54,          /* IRQ 54 Vector No */
    INT_NUM_IRQ0 + 55,          /* IRQ 55 Vector No */
    INT_NUM_IRQ0 + 56,          /* IRQ 56 Vector No */
    INT_NUM_IRQ0 + 57,          /* IRQ 57 Vector No */
    INT_NUM_IRQ0 + 58,          /* IRQ 58 Vector No */
    INT_NUM_IRQ0 + 59,          /* IRQ 59 Vector No */
    INT_NUM_IRQ0 + 60,          /* IRQ 60 Vector No */
    INT_NUM_IRQ0 + 61,          /* IRQ 61 Vector No */
    INT_NUM_IRQ0 + 62,          /* IRQ 62 Vector No */
    INT_NUM_IRQ0 + 63,          /* IRQ 63 Vector No */

    INT_NUM_IRQ0 + 64,          /* IRQ 64 Vector No */
    INT_NUM_IRQ0 + 65,          /* IRQ 65 Vector No */
    INT_NUM_IRQ0 + 66,          /* IRQ 66 Vector No */
    INT_NUM_IRQ0 + 67,          /* IRQ 67 Vector No */
    INT_NUM_IRQ0 + 68,          /* IRQ 68 Vector No */
    INT_NUM_IRQ0 + 69,          /* IRQ 69 Vector No */
    INT_NUM_IRQ0 + 70,          /* IRQ 70 Vector No */
    INT_NUM_IRQ0 + 71,          /* IRQ 71 Vector No */
    INT_NUM_IRQ0 + 72,          /* IRQ 72 Vector No */
    INT_NUM_IRQ0 + 73,          /* IRQ 73 Vector No */
    INT_NUM_IRQ0 + 74,          /* IRQ 74 Vector No */
    INT_NUM_IRQ0 + 75,          /* IRQ 75 Vector No */
    INT_NUM_IRQ0 + 76,          /* IRQ 76 Vector No */
    INT_NUM_IRQ0 + 77,          /* IRQ 77 Vector No */
    INT_NUM_IRQ0 + 78,          /* IRQ 78 Vector No */
    INT_NUM_IRQ0 + 79,          /* IRQ 79 Vector No */

    INT_NUM_IRQ0 + 80,          /* IRQ 80 Vector No */
    INT_NUM_IRQ0 + 81,          /* IRQ 81 Vector No */
    INT_NUM_IRQ0 + 82,          /* IRQ 82 Vector No */
    INT_NUM_IRQ0 + 83,          /* IRQ 83 Vector No */
    INT_NUM_IRQ0 + 84,          /* IRQ 84 Vector No */
    INT_NUM_IRQ0 + 85,          /* IRQ 85 Vector No */
    INT_NUM_IRQ0 + 86,          /* IRQ 86 Vector No */
    INT_NUM_IRQ0 + 87,          /* IRQ 87 Vector No */
    INT_NUM_IRQ0 + 88,          /* IRQ 88 Vector No */
    INT_NUM_IRQ0 + 89,          /* IRQ 89 Vector No */
    INT_NUM_IRQ0 + 90,          /* IRQ 90 Vector No */
    INT_NUM_IRQ0 + 91,          /* IRQ 91 Vector No */
    INT_NUM_IRQ0 + 92,          /* IRQ 92 Vector No */
    INT_NUM_IRQ0 + 93,          /* IRQ 93 Vector No */
    INT_NUM_IRQ0 + 94,          /* IRQ 94 Vector No */
    INT_NUM_IRQ0 + 95,          /* IRQ 95 Vector No */

    INT_NUM_IRQ0 + 96,          /* IRQ 96 Vector No */
    INT_NUM_IRQ0 + 97,          /* IRQ 97 Vector No */
    INT_NUM_IRQ0 + 98,          /* IRQ 98 Vector No */
    INT_NUM_IRQ0 + 99,          /* IRQ 99 Vector No */
    INT_NUM_IRQ0 + 100,         /* IRQ 100 Vector No */
    INT_NUM_IRQ0 + 101,         /* IRQ 101 Vector No */
    INT_NUM_IRQ0 + 102,         /* IRQ 102 Vector No */
    INT_NUM_IRQ0 + 103,         /* IRQ 103 Vector No */
    INT_NUM_IRQ0 + 104,         /* IRQ 104 Vector No */
    INT_NUM_IRQ0 + 105,         /* IRQ 105 Vector No */
    INT_NUM_IRQ0 + 106,         /* IRQ 106 Vector No */
    INT_NUM_IRQ0 + 107,         /* IRQ 107 Vector No */
    INT_NUM_IRQ0 + 108,         /* IRQ 108 Vector No */
    INT_NUM_IRQ0 + 109,         /* IRQ 109 Vector No */
    INT_NUM_IRQ0 + 110,         /* IRQ 110 Vector No */
    INT_NUM_IRQ0 + 111,         /* IRQ 111 Vector No */

    INT_NUM_IRQ0 + 112,         /* IRQ 112 Vector No */
    INT_NUM_IRQ0 + 113,         /* IRQ 113 Vector No */
    INT_NUM_IRQ0 + 114,         /* IRQ 114 Vector No */
    INT_NUM_IRQ0 + 115,         /* IRQ 115 Vector No */
    INT_NUM_IRQ0 + 116,         /* IRQ 116 Vector No */
    INT_NUM_IRQ0 + 117,         /* IRQ 117 Vector No */
    INT_NUM_IRQ0 + 118,         /* IRQ 118 Vector No */
    INT_NUM_IRQ0 + 119,         /* IRQ 119 Vector No */
    INT_NUM_IRQ0 + 120,         /* IRQ 120 Vector No */
    INT_NUM_IRQ0 + 121,         /* IRQ 121 Vector No */
    INT_NUM_IRQ0 + 122,         /* IRQ 122 Vector No */
    INT_NUM_IRQ0 + 123,         /* IRQ 123 Vector No */
    INT_NUM_IRQ0 + 124,         /* IRQ 124 Vector No */
    INT_NUM_IRQ0 + 125,         /* IRQ 125 Vector No */
    INT_NUM_IRQ0 + 126,         /* IRQ 126 Vector No */
    INT_NUM_IRQ0 + 127,         /* IRQ 127 Vector No */
#endif /* _WRS_CONFIG_WRHV_GUEST */
    };

UINT8 *sysInumTbl;
UINT32 sysInumTblNumEnt;

/* locals */

#ifdef  INCLUDE_ROMCARD

LOCAL short *sysRomBase[] =
    {
    (short *)0xce000, (short *)0xce800, (short *)0xcf000, (short *)0xcf800
    };

LOCAL char sysRomSignature[ROM_SIGNATURE_SIZE] =
    {
    0x55,0xaa,0x01,0x90,0x90,0x90,0x90,0x90,
    0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90
    };

#endif  /* INCLUDE_ROMCARD */

#if (CPU == PENTIUM2) || (CPU == PENTIUM3) || (CPU == PENTIUM4)

    /*
     * The cache control flags and MTRRs operate hierarchically for restricting
     * caching.  That is, if the CD flag is set, caching is prevented globally.
     * If the CD flag is clear, either the PCD flags and/or the MTRRs can be
     * used to restrict caching.  If there is an overlap of page-level caching
     * control and MTRR caching control, the mechanism that prevents caching
     * has precedence.  For example, if an MTRR makes a region of system memory
     * uncachable, a PCD flag cannot be used to enable caching for a page in
     * that region.  The converse is also true; that is, if the PCD flag is
     * set, an MTRR cannot be used to make a region of system memory cacheable.
     * If there is an overlap in the assignment of the write-back and write-
     * through caching policies to a page and a region of memory, the write-
     * through policy takes precedence.  The write-combining policy takes
     * precedence over either write-through or write-back.
     */

LOCAL MTRR sysMtrr =
    {                   /* MTRR table */
    {0,0},              /* MTRR_CAP register */
    {0,0},              /* MTRR_DEFTYPE register */

                        /* Fixed Range MTRRs */

    {{{MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB}},
     {{MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB, MTRR_WB}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_WC, MTRR_WC, MTRR_WC, MTRR_WC}},
     {{MTRR_WP, MTRR_WP, MTRR_WP, MTRR_WP, MTRR_WP, MTRR_WP, MTRR_WP, MTRR_WP}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}},
     {{MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC, MTRR_UC}}},
    {{0LL, 0LL},            /* Variable Range MTRRs */
     {0LL, 0LL},
     {0LL, 0LL},
     {0LL, 0LL},
     {0LL, 0LL},
     {0LL, 0LL},
     {0LL, 0LL},
     {0LL, 0LL}}
    };
#endif  /* (CPU == PENTIUM[2/3/4]) */


/* forward declarations */

void sysStrayInt   (void);
char * sysPhysMemTop     (void);
STATUS sysMmuMapAdd  (void * address, UINT len, UINT initialStateMask,
                      UINT initialState);
void sysIntInitPIC (void);
void sysIntEoiGet (VOIDFUNCPTR * vector,
                   VOIDFUNCPTR * routineBoi, int * parameterBoi,
                   VOIDFUNCPTR * routineEoi, int * parameterEoi);

#ifdef _WRS_CONFIG_SMP
void sysCpuInit (void);

UINT32 sysCpuAvailableGet(void);

STATUS sysCpuStart(int cpuNum, WIND_CPU_STATE *cpuState);
STATUS vxCpuStateInit(unsigned int cpu, WIND_CPU_STATE *cpuState,
	              char *stackBase, FUNCPTR entry);
STATUS sysCpuEnable(unsigned int cpuNum, WIND_CPU_STATE *cpuState);
STATUS sysCpuDisable(int cpuNum);

STATUS sysCpuStop(int cpu);
STATUS sysCpuStop_APs(void);
STATUS sysCpuStop_ABM(void);

STATUS sysCpuReset(int cpu);
STATUS sysCpuReset_APs(void);
STATUS sysCpuReset_ABM(void);
#endif /* _WRS_CONFIG_SMP */

#if !defined (SYMMETRIC_IO_MODE) || !defined (VIRTUAL_WIRE_MODE)
unsigned int dummyGetCpuIndex (void);
#endif /* !(SYMMETRIC_IO_MODE) || !(VIRTUAL_WIRE_MODE) */

/* includes (source file) */

#if (NV_RAM_SIZE != NONE)
#   include "sysNvRam.c"
#else   /* default to nullNvRam */
#   include <mem/nullNvRam.c>
#endif  /* (NV_RAM_SIZE != NONE) */

#ifndef DRV_SIO_NS16550

/* use vxBus ns16550 if INCLUDE_VXBUS is defined */

#include "sysSerial.c"
#endif /* DRV_SIO_NS16550 */

#include <vme/nullVme.c>

#ifndef _WRS_CONFIG_WRHV_GUEST
#if (!defined(SYMMETRIC_IO_MODE))
#include <intrCtl/i8259Intr.c>
#endif /* !defined(SYMMETRIC_IO_MODE) */
#endif /* !_WRS_CONFIG_WRHV_GUEST */

#ifdef  INCLUDE_PCI_BUS                     /* BSP PCI bus & config support */
#   include <drv/pci/pciConfigLib.h>
#   include <drv/pci/pciIntLib.h>
#   include <drv/pci/pciAutoConfigLib.h>

/* 24-bit PCI network class ethernet subclass and prog. I/F code */

#   include "pciCfgStub.c"
#   include "pciCfgIntStub.c"

#endif  /* INCLUDE_PCI_BUS */

#ifdef  INCLUDE_PCMCIA
#   include <pcmcia/pccardLib.c>
#   include <pcmcia/pccardShow.c>
#endif  /* INCLUDE_PCMCIA */

#ifdef  INCLUDE_NETWORK
#   include "sysNet.c"                  /* network driver support */
#endif  /* INCLUDE_NETWORK */

#if defined(INCLUDE_SCSI) || defined(INCLUDE_SCSI2)
#    include "sysScsi.c"                /* scsi support */
#endif /* INCLUDE_SCSI || INCLUDE_SCSI2 */

/* include BSP specific WindML configuration */

#if defined(INCLUDE_WINDML) && defined(INCLUDE_PCI_BUS)
#ifndef INCLUDE_VXBUS
#    include "sysWindML.c"
#endif /*  INCLUDE_VXBUS */
#endif /* INCLUDE_WINDML */

#ifdef  INCLUDE_CPU_UTIL_PWR_MGR
#if (defined (VIRTUAL_WIRED_MODE) ||  defined (SYMMETRIC_IO_MODE))
#   include "sysTherm.c"        /* Thermal Monitor support */
#endif /* (defined VIRTUAL_WIRED_MODE) ||  (defined (SYMMETRIC_IO_MODE) */
#endif /* INCLUDE_CPU_UTIL_PWR_MGR */

#ifdef  INCLUDE_DEBUG_STORE
#   include "sysDbgStr.c"       /* Debug Store support */
#endif  /* INCLUDE_DEBUG_STORE */

/* Atheros AR521X WLAN Support */

#ifdef INCLUDE_AR521X_END
    #include <wlan/bsp/sysDot11End.c>
#endif /* INCLUDE_AR521X_END */

#ifdef INCLUDE_BCM43XX_END
    #include <wlan/bsp/sysBroadComWLEnd.c>
#endif /* INCLUDE_BCM43XX_END */

#ifdef INCLUDE_VXBUS
#include <hwif/vxbus/vxBus.h>
#include "hwconf.c"
#endif /* INCLUDE_VXBUS */

#ifdef INCLUDE_VXBUS
IMPORT device_method_t * pSysPlbMethods;

#if defined(INCLUDE_PC_CONSOLE) && defined (DRV_TIMER_I8253)
LOCAL void sysConBeep (BOOL);
IMPORT char * pcConBeep_desc;
#endif /* INCLUDE_PC_CONSOLE && DRV_TIMER_I8253 */

LOCAL struct vxbDeviceMethod pc386PlbMethods[] =
    {
#if defined(INCLUDE_PC_CONSOLE) && defined (DRV_TIMER_I8253)
    DEVMETHOD(pcConBeep, sysConBeep),
#endif /* INCLUDE_PC_CONSOLE && DRV_TIMER_I8253 */
    { 0, 0 }
    };
#endif /* INCLUDE_VXBUS */

#if defined(_WRS_CONFIG_WRHV_GUEST)
/******************************************************************************
*
* hySysClkRateSet - hypervisor version of sysClkRateSet
*
* This routine is the hypervisor specific version of sysClkRateSet.  Currently
* it is not possible to set the clock rate since it is pre-set in the xml
* configuration file.
*
* RETURNS: always returns ERROR
*/

static STATUS hySysClkRateSet (void)
    {
    return (ERROR);
    }
#endif /* _WRS_CONFIG_WRHV_GUEST */

/******************************************************************************
*
* sysModel - return the model name of the CPU board
*
* This routine returns the model name of the CPU board.
*
* RETURNS: A pointer to the string "PC 386, 486, PENTIUM or PENTIUM[234]".
*/

char *sysModel (void)

    {
    return (SYS_MODEL);
    }

/*******************************************************************************
*
* sysBspRev - return the BSP version and revision number
*
* This routine returns a pointer to a BSP version and revision number, for
* example, 1.1/0. BSP_REV is concatenated to BSP_VERSION and returned.
*
* RETURNS: A pointer to the BSP version/revision string.
*/

char * sysBspRev (void)
    {
    return (BSP_VERSION BSP_REV);
    }

#ifdef INCLUDE_SYS_HW_INIT_0

/*******************************************************************************
*
* sysHwInit0 - BSP-specific hardware initialization
*
* This routine is called from usrInit() to perform BSP-specific initialization
* that must be done before cacheLibInit() is called and/or the BSS is cleared.
*
* The BSP-specific sysCpuProbe() routine is called for the purpose of
* identifying IA-32 target CPU variants, and the features or functions
* supported by the target CPU.  This information must be obtained relatively
* early during system hardware initialization, as some support libraries
* (mmuLib, cacheLib, &c.) will use the processor feature information to
* enable or disable architecture-specific and/or BSP-specific functionality.
*
* RETURNS: N/A
*
* NOMANUAL
*/

void sysHwInit0 (void)
    {

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
    _func_cpuIndexGet = NULL;
#else
    _func_cpuIndexGet = &dummyGetCpuIndex;
#endif /* (SYMMETRIC_IO_MODE) || (VIRTUAL_WIRE_MODE) */

#ifdef _WRS_CONFIG_SMP

    /* temporarily use structure to load the brand new GDT into RAM */

    _WRS_WIND_VARS_ARCH_SET(vxCpuIndexGet(),
                            pSysGdt,
                            pSysGdt);
#endif /* _WRS_CONFIG_SMP */

    sysInitGDT ();

#ifdef  INCLUDE_CPU_PROBE
    (void) sysCpuProbe ();
#else
    sysProcessor = X86CPU_DEFAULT;
#endif  /* INCLUDE_CPU_PROBE */

#if defined(_WRS_CONFIG_WRHV_GUEST)
    /* set the pointers to the hypervisor status and control pages */

    wrhvVbStatus  = wrhvVbConfig->vbStatus;
    wrhvVbControl = wrhvVbConfig->vbControl;
#endif /* _WRS_CONFIG_WRHV_GUEST */
    }

#endif  /* INCLUDE_SYS_HW_INIT_0 */

/*******************************************************************************
*
* sysHwInit - initialize the system hardware
*
* This routine initializes various features of the i386/i486 board.
* It is called from usrInit() in usrConfig.c.
*
* NOTE: This routine should not be called directly by the user application.
*
* RETURNS: N/A
*/

void sysHwInit (void)
    {
    PHYS_MEM_DESC *pMmu;
    int ix = 0;

#if defined(_WRS_CONFIG_WRHV_GUEST)
#if defined(DRV_SIO_NS16550)
    {

    HCF_DEVICE * pHcf = &hcfDeviceList[0];
    if (strstr (VBI_BOOTLINE_ADDR_GET(), "ttyS0") != NULL)
	{
	pHcf->count = pentiumi82501Num;
	pHcf->pResource = pentiumi82501Resources;
	}
    else if (strstr (VBI_BOOTLINE_ADDR_GET(), "ttyS1") != NULL)
	{
	pHcf->count = pentiumi82502Num;
	pHcf->pResource = pentiumi82502Resources;
	}
    else if (strstr (VBI_BOOTLINE_ADDR_GET(), "ttyS2") != NULL)
        {
        pHcf->count = pentiumi82503Num;
        pHcf->pResource = pentiumi82503Resources;
        }
    else if (strstr (VBI_BOOTLINE_ADDR_GET(), "ttyS3") != NULL)
        {
        pHcf->count = pentiumi82504Num;
        pHcf->pResource = pentiumi82504Resources;
        }
    }
#endif /* DRV_SIO_NS16550 */

    /* copy the boot line provided by the hypervisor to the boot line area */

    strcpy (sysBootLine, VBI_BOOTLINE_ADDR_GET());

#ifdef  INCLUDE_VXBUS
    /* bypass the system's sysClkRateSet() */

    _vxb_clkRateSetRtn = hySysClkRateSet;
#endif

#endif /* _WRS_CONFIG_WRHV_GUEST */

#if defined(VIRTUAL_WIRE_MODE)
    sysInumTbl = &vwInumTbl[0];
    sysInumTblNumEnt = NELEMENTS (vwInumTbl);
#elif defined(SYMMETRIC_IO_MODE)
#ifdef _WRS_CONFIG_SMP
    /* store trampoline code space for restoration on warm reboot */

    bcopy ((char *)(CPU_ENTRY_POINT),
                    (char *)(&tramp_code[0]),
                    (int)CPU_AP_AREA);
#endif /* _WRS_CONFIG_SMP */
#else
    sysInumTbl = &dfltInumTbl[0];
    sysInumTblNumEnt = NELEMENTS (dfltInumTbl);
#endif  /* defined(VIRTUAL_WIRE_MODE) */

#ifdef _WRS_CONFIG_SMP

    /* establish pointers to gloabal descriptor table & task state segment
     * TSS is assigned a cpu unique structure...
     */

    _WRS_WIND_VARS_ARCH_SET(vxCpuIndexGet(),
                            pSysGdt,
                            pSysGdt);

    _WRS_WIND_VARS_ARCH_SET(vxCpuIndexGet(),
                            sysTssCurrent,
                            sysTssCurrent);

    _WRS_WIND_VARS_ARCH_SET(vxCpuIndexGet(),
                            vxIntStackEnabled,
                            1);
#endif /* _WRS_CONFIG_SMP */

#if (CPU == PENTIUM) || (CPU == PENTIUM2) || (CPU == PENTIUM3) || \
    (CPU == PENTIUM4)

    /* initialize the MSRs (Model Specific Registers) 

    pentiumMsrInit ();*/

#if !defined(_WRS_CONFIG_WRHV_GUEST)
#   if  (CPU != PENTIUM)

    /* enable the MTRR (Memory Type Range Registers) */

    if ((sysCpuId.featuresEdx & CPUID_MTRR) == CPUID_MTRR)
    {
        pentiumMtrrDisable ();      /* disable MTRR */
#   ifdef INCLUDE_MTRR_GET
        (void) pentiumMtrrGet (&sysMtrr); /* get MTRR initialized by BIOS */
#   else
        (void) pentiumMtrrSet (&sysMtrr); /* set your own MTRR */
#   endif /* INCLUDE_MTRR_GET */
        pentiumMtrrEnable ();       /* enable MTRR */
    }

#   endif /* (CPU != PENTIUM) */

#   ifdef INCLUDE_PMC

    /* enable PMC (Performance Monitoring Counters) */

    pentiumPmcStop ();          /* stop PMC0 and PMC1 */
    pentiumPmcReset ();         /* reset PMC0 and PMC1 */

#   endif /* INCLUDE_PMC */

    /* enable the MCA (Machine Check Architecture) */

    pentiumMcaEnable (TRUE);
#endif /* _WRS_CONFIG_WRHV_GUEST */

#   ifdef INCLUDE_SHOW_ROUTINES

    /*
     * if excMcaInfoShow is not NULL, it is called in the default
     * exception handler when Machine Check Exception happened
     */

    {
    IMPORT FUNCPTR excMcaInfoShow;
    excMcaInfoShow = (FUNCPTR) pentiumMcaShow;
    }
#   endif /* INCLUDE_SHOW_ROUTINES */

#endif  /* (CPU == PENTIUM) || (CPU == PENTIUM[234]) */

#ifdef INCLUDE_SHOW_ROUTINES
    vxShowInit ();
#endif /* INCLUDE_SHOW_ROUTINES */

    /* initialize the number of active mappings (sysPhysMemDescNumEnt) */

    pMmu = &sysPhysMemDesc[0];

    for (ix = 0; ix < NELEMENTS (sysPhysMemDesc); ix++)
        if (pMmu->virtualAddr != (VIRT_ADDR)DUMMY_VIRT_ADDR)
            pMmu++;
        else
            break;

    sysPhysMemDescNumEnt = ix;

#if defined(_WRS_CONFIG_WRHV_GUEST)
    /* add mappings for hypervisor data structures */

    sysMmuMapAdd ((void *)VBI_CONFIG_ADDR_GET(), PAGE_SIZE_4KB,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
    sysMmuMapAdd ((void *)VBI_STATUS_ADDR_GET(), PAGE_SIZE_4KB,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
    sysMmuMapAdd ((void *)VBI_CNTRL_ADDR_GET(), PAGE_SIZE_4KB,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);

#if (VBI_VERSION_MAJOR == 2)
    /* XXX should use sizeof(VIOAPIC) instead of PAGE_SIZE_4KB */
    sysMmuMapAdd ((void *)VBI_VIOAPIC_BASE_GET(), PAGE_SIZE_4KB,
		  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
#endif

    if (VBI_CONFIG_ADDR_GET()->memoryRegionsConfigAddress)
	sysMmuMapAdd ((void *)VBI_CONFIG_ADDR_GET()->memoryRegionsConfigAddress,
		       PAGE_SIZE_4KB, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);

    if (VBI_CONFIG_ADDR_GET()->sharedMemoryRegionsConfigAddress)
	sysMmuMapAdd ((void *)VBI_CONFIG_ADDR_GET()->sharedMemoryRegionsConfigAddress,
		       PAGE_SIZE_4KB, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);

    if (VBI_CONFIG_ADDR_GET()->interruptConfiguration)
	sysMmuMapAdd ((void *)VBI_CONFIG_ADDR_GET()->interruptConfiguration,
		       PAGE_SIZE_4KB, VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
#endif /* _WRS_CONFIG_WRHV_GUEST */

    /* initialize PCI library */

#ifdef  INCLUDE_VXBUS

  pSysPlbMethods = pc386PlbMethods;
  hardWareInterFaceInit();

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
  /* establish link to vxb APIC methods */

  vxbDevIterate(apicIntrIntHelper, NULL, VXB_ITERATE_INSTANCES);
#endif /* SYMMETRIC_IO_MODE || VIRTUAL_WIRE_MODE */

  /* Connect intEnable/intDisable function pointers */

  sysIntLvlEnableRtn = (FUNCPTR)sysIntEnablePIC;
  sysIntLvlDisableRtn = (FUNCPTR)sysIntDisablePIC;

  /* initialize the PIC (Programmable Interrupt Controller) */

  sysIntInitPIC ();       /* should be after the PCI init for IOAPIC */

  intEoiGet = sysIntEoiGet;   /* function pointer used in intConnect () */

#ifdef _WRS_CONFIG_SMP
  /* init IPI vector, assign default handlers... */

  ipiVecInit (INT_NUM_LOAPIC_IPI);
#endif /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_PCI_BUS

    /* initialize PCI devices */

    /*
     * PCI-to-PCI bridge initialization should be done here, if it is.
     * It is not necessary for Intel 430HX PCISET, which splits
     * the extended memory area as follows:
     *   - Flash BIOS area from 4GByte to (4GB - 512KB)
     *   - DRAM memory from 1MB to a maximum of 512MB
     *   - PCI memory space from the top of DRAM to (4GB - 512KB)
     */

#ifdef INCLUDE_NETWORK

/* Atheros AR521X WLAN Support */

#ifdef INCLUDE_AR521X_END
    sysDot11BusInit();
#endif /* INCLUDE_AR521X_END */

#ifdef INCLUDE_BCM43XX_END
    sysBroadComWLBusInit();
#endif /* INCLUDE_BCM43XX_END */

    /* initialize PCI network controllers starting from Bus 0 */

     pciConfigForeachFunc (0, TRUE, (PCI_FOREACH_FUNC) sysNetPciInit, NULL);

#endif /* INCLUDE_NETWORK */

#if (defined(INCLUDE_SCSI) && defined(INCLUDE_AIC_7880))
    sysAic7880PciInit ();
#endif  /* INCLUDE_SCSI && INCLUDE_AIC_7880 */

#endif /* INCLUDE_PCI_BUS */
#endif /* INCLUDE_VXBUS */

    /* initializes the serial devices */

#if  (!defined(DRV_SIO_NS16550) && !defined(_WRS_CONFIG_WRHV_GUEST))
    sysSerialHwInit ();      /* initialize serial data structure */
#endif /* DRV_SIO_NS16550 */

#if defined(INCLUDE_WINDML) && defined(INCLUDE_PCI_BUS)
#ifndef INCLUDE_VXBUS
    sysWindMLHwInit ();
#endif /*  INCLUDE_VXBUS */
#endif /* INCLUDE_WINDML */

    /* 初始化2路CAN口 */
    CreatePciCan(0);
    CreatePciCan(1);
    }

/*******************************************************************************
*
* sysHwInit2 - additional system configuration and initialization
*
* This routine connects system interrupts and does any additional
* configuration necessary.
*
* RETURNS: N/A
*/

void sysHwInit2 (void)
    {
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
    sysIchAtaInit2();
#endif
#ifdef _WRS_CONFIG_SMP
#ifdef DRV_TIMER_IA_TIMESTAMP
    /* SMP requires HPET for Timestamp...
     *
     * Initialize High Precision Event Timer Functionality for
     * Timestamp usage.
     */

    hpetInit ();
#endif /* DRV_TIMER_IA_TIMESTAMP */
#endif /* _WRS_CONFIG_SMP */

#ifndef DRV_SIO_NS16550
    /* connect serial interrupt */

    sysSerialHwInit2();
#endif /* DRV_SIO_NS16550 */

    /* connect stray(spurious/phantom) interrupt */

#if !defined(_WRS_CONFIG_WRHV_GUEST)
#if defined(VIRTUAL_WIRE_MODE)
    (void)intConnect (INUM_TO_IVEC (INT_NUM_LOAPIC_SPURIOUS), sysStrayInt, 0);
    (void)intConnect (INUM_TO_IVEC (INT_NUM_GET (LPT_INT_LVL)), sysStrayInt, 0);
#elif defined(SYMMETRIC_IO_MODE)
    (void)intConnect (INUM_TO_IVEC (INT_NUM_LOAPIC_SPURIOUS), sysStrayInt, 0);
#else
    (void)intConnect (INUM_TO_IVEC (INT_NUM_GET (LPT_INT_LVL)), sysStrayInt, 0);
    (void)intConnect (INUM_TO_IVEC (INT_NUM_GET (PIC_SLAVE_STRAY_INT_LVL)), sysStrayInt, 0);
#endif /* defined(VIRTUAL_WIRE_MODE) */
#endif /* !_WRS_CONFIG_WRHV_GUEST */

#ifndef INCLUDE_VXBUS
#ifdef  INCLUDE_PC_CONSOLE

    /* connect keyboard Controller 8042 chip interrupt */

    (void) intConnect (INUM_TO_IVEC (INT_NUM_GET (KBD_INT_LVL)), kbdIntr, 0);

#endif  /* INCLUDE_PC_CONSOLE */
#endif /* INCLUDE_VXBUS */

#ifdef _WRS_CONFIG_SMP
    /* connect IPI handlers, up to IPI_MAX_HANDLERS (=8) */

    ipiConnect ((INT_NUM_LOAPIC_IPI + 0), ipiHandlerShutdown);
    ipiConnect ((INT_NUM_LOAPIC_IPI + 1), ipiHandlerTscReset);
    ipiConnect ((INT_NUM_LOAPIC_IPI + 2), ipiHandlerTlbFlush);
#endif /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_VXBUS

    vxbDevInit();

#ifdef INCLUDE_SIO_UTILS
    sysSerialConnectAll();
#endif /* INCLUDE_SIO_UTILS */

#ifdef INCLUDE_PCI_BUS
#ifdef INCLUDE_NETWORK
    /* initialize non-vxBus PCI network controllers starting from Bus 0 */

    pciConfigForeachFunc (0, TRUE, (PCI_FOREACH_FUNC) sysNetPciInit, NULL);
#endif /* INLCUDE_NETWORK */
#endif /* INCLUDE_PCI_BUS */

#endif /* INCLUDE_VXBUS */

#ifdef  INCLUDE_CPU_UTIL_PWR_MGR
#if (defined (VIRTUAL_WIRED_MODE) || defined (SYMMETRIC_IO_MODE))
    sysThermInit ();
#endif /* defined (VIRTUAL_WIRED_MODE) ||  defined (SYMMETRIC_IO_MODE */
#endif /* INCLUDE_CPU_UTIL_PWR_MGR */

#ifdef  INCLUDE_DEBUG_STORE
    sysDbgStrInit ();
#endif  /* INCLUDE_DEBUG_STORE */

#ifdef INCLUDE_VXBUS
    taskSpawn("tDevConn", 11, 0, 10000, vxbDevConnect, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
#endif /* INCLUDE_VXBUS */
#ifdef INCLUDE_ATA
    sysAtaSetup();
#endif /* INCLUDE_VXBUS */

#if defined(_WRS_CONFIG_WRHV_GUEST)
    {
    VB_SM_INFO  *smInfo  = VBI_CONFIG_ADDR_GET()->sharedMemoryRegionsConfigAddress;
    VB_MEM_INFO *memInfo = VBI_CONFIG_ADDR_GET()->memoryRegionsConfigAddress;
    uint32_t	 i;
    uint32_t	 len;
    uint32_t	 pageSize = vmPageSizeGet();

    /* map the hypervisor memory regions into the kernel */

    /* run through all the mapped memory regions */

    for (i=0; i < VBI_CONFIG_ADDR_GET()->numMem; i++, memInfo++)
	{
	/* calculate length in units of a page size */

	len = memInfo->length;
	if (len % pageSize)
	    len += pageSize;

	/* map the region 1:1 */

	if ((len > 0) && (memInfo->addr != NULL))
	    vmMap (NULL,
		   (VIRT_ADDR)memInfo->addr, (PHYS_ADDR)memInfo->addr, len);
	}

    /* run through all the shared memory regions */

    for (i=0; i < VBI_CONFIG_ADDR_GET()->numSm; i++, smInfo++)
	{
	/* calculate length in units of a page size */

	len = smInfo->length;
	if (len % pageSize)
	    len += pageSize;


	/* map the region 1:1 */

	if ((len > 0) && (smInfo->addr != NULL))
	    vmMap (NULL, (VIRT_ADDR)smInfo->addr, (PHYS_ADDR)smInfo->addr, len);
	}
    }
#endif /* _WRS_CONFIG_WRHV_GUEST */
    }

#ifdef  LOCAL_MEM_AUTOSIZE
/*******************************************************************************
*
* WRITE_MEMORY_TEST_PATTERN
*
* This routine writes the memory test pattern used in the sysPhysMemTop()
* memory auto-size algorithm.  12 bytes of data stored at <pTestAddr> are
* written to <pSaveAddr> before a 12-byte test pattern is written to
* <pTestAddr>.
*
* RETURNS: N/A
*
* SEE ALSO:  RESTORE_MEMORY_TEST_ADDRS()
*
* NOMANUAL
*/
__inline__ static void WRITE_MEMORY_TEST_PATTERN
    (
    int * pTestAddr,
    int * pSaveAddr
    )
    {
    pSaveAddr[0] = pTestAddr[0];
    pSaveAddr[1] = pTestAddr[1];
    pSaveAddr[2] = pTestAddr[2];

    pTestAddr[0] = TEST_PATTERN_A;
    pTestAddr[1] = TEST_PATTERN_B;
    pTestAddr[2] = TEST_PATTERN_C;

    cacheFlush (DATA_CACHE, pTestAddr, 16);
    }

/*******************************************************************************
*
* RESTORE_MEMORY_TEST_ADDRS
*
* This routine restores memory test locations which are modified in the
* sysPhysMemTop() memory auto-size algorithm.  12 bytes of data stored at
* <pSaveAddr> are written to <pTestAddr>.
*
* RETURNS: N/a
*
* SEE ALSO:  WRITE_MEMORY_TEST_PATTERN()
*
* NOMANUAL
*/
__inline__ static void RESTORE_MEMORY_TEST_ADDRS
    (
    int *       pTestAddr,
    const int * pSaveAddr
    )
    {
    pTestAddr[0] = pSaveAddr[0];
    pTestAddr[1] = pSaveAddr[1];
    pTestAddr[2] = pSaveAddr[2];
    }
#endif  /* LOCAL_MEM_AUTOSIZE */

/*******************************************************************************
*
* sysPhysMemTop - get the address of the top of physical memory
*
* This routine returns the address of the first missing byte of memory,
* which indicates the top of physical memory.
*
* INTERNAL
* The memory auto-size logic assumes that the manifest constant PHYS_MEM_MAX
* specifies the total size in bytes of the processor's physical address space.
* In the case of IA-32 processors, PHYS_MEM_MAX will be 4GB (2^32 bytes) or
* 64GB (2^36 bytes) if the 36-bit Physical Address Extension (PAE) is enabled
* on select processor models.  However, because the tool-chain and sysMemTop()
* API are 32-bit, this routine currently will not auto-size a 36-bit address
* space.  Moreover, this routine will not return the memory top of a platform
* with a memory device using a full 2^32 bytes of address space, as the memory
* top of such a device would be a 33-bit value.
*
* When paging is used, the processor divides the linear address space into
* fixed-size pages (of 4KB, 2MB, or 4MB in length) that can be mapped into
* physical memory and/or disk storage.  The auto-size algorithm organizes
* the physical address space using the same concept.  That is, rather than
* treating the address space as an array of bytes, the memory auto-size
* code treats the address space as an array of equal-sized pages.
*
* The auto-size algorithm attempts to locate the base-address of the first
* non-existent page address in the physical address space.  This is done by
* writing, and then reading, a test pattern to each page base-address in the
* address space.  If the test pattern is not read back from a page, it is
* assumed that the address does not physically exist.
*
* As the installed physical memory could be potentially quite large, the
* auto-size code attempts a few optimizations, chief among these being a
* binary (as opposed to linear) search of the page array (ie. address space).
* An additional optimization is obtained by avoiding a search on memory
* that _must_ exist; namely, the memory storing the VxWorks boot image or
* RTOS image from whence this routine will execute.
*
* In the case of VxWorks boot and RTOS images for IA-32, the last byte of the
* image section loaded highest in memory is assumed to be indicated by the
* address of a symbol, named <end>, which is typically supplied by the linker
* (more precisely, the linker script) used to build the image.  The search
* for remaining extant physical page addresses on the system will use the
* address of the first page following the <end> symbol, or a page-aligned
* address no lower than physical memory location 0x100000 (1Mb), as a lower
* bound on the search.  All memory locations below physical address 0x100000
* are assumed to be reserved existing target memory.
*
* RETURNS:  The address of the top of physical memory.
*/
char * sysPhysMemTop (void)
    {
    PHYS_MEM_DESC * pMmu;       /* points to memory desc. table entries */
    UINT32          tempMTP;    /* temporary variable to stop warnings */

    GDTPTR gDtp;
    INT32 nGdtEntries, nGdtBytes;
    unsigned char gdtr[6];      /* temporary GDT register storage */

    BOOL            found = FALSE;

    if (memTopPhys != NULL)
        {
        return (memTopPhys);
        }

#ifdef  LOCAL_MEM_AUTOSIZE
    {

#if defined(_WRS_CONFIG_WRHV_GUEST)

    found = TRUE;
    memTopPhys = (char *) VBI_MEM_SIZE_GET();
#else /* _WRS_CONFIG_WRHV_GUEST */

    /* Do not use a page-sized stride larger than 4Kb, as the end of usable
     * memory could possibly be within a 2Mb or 4Mb page memory range.
     */

    const UINT32 pageSize = PAGE_SIZE_4KB;

    /* The lower bound for the probe will be the page-aligned VxWorks
     * end-of-image address, or a page-aligned address no less than
     * the 1Mb physical address.
     */

    UINT8 * pPage = (UINT8 *) ROUND_UP (((UINT32)(&end) > 0x100000) ?
                          (UINT32)(&end) : (0x100000), pageSize);


    /* Subtract the number of used pages from the total number of pages
     * possible in the address space.  The resulting value is the total
     * number of pages that could possibly populate the remaining address
     * space above <pPage>.
     */

    const UINT32 pageNoUsed  = ((UINT32) pPage / pageSize);
    const UINT32 pageNoTotal = (PHYS_MEM_MAX / pageSize) - pageNoUsed;
    UINT32       delta       = HALF (pageNoTotal);

    int temp[4];


    /* find out the actual size of the memory (up to PHYS_MEM_MAX) */

    for (pPage += (pageSize * delta); delta != 0; delta >>= 1)
        {
        WRITE_MEMORY_TEST_PATTERN ((int *) pPage, &temp[0]);

        if (*((int *) pPage) != TEST_PATTERN_A)
            {

            /* The test pattern was not written, so assume that <pPage> is the
             * base address of a page beyond available memory.  Test the
             * next lowest page.  If the test pattern is writable there, assume
             * that <pPage> is the address of the first byte beyond the last
             * addressable page.
             */

            UINT8 * pPrevPage = (UINT8 *)((UINT32) pPage - pageSize);

            WRITE_MEMORY_TEST_PATTERN ((int *) pPrevPage, &temp[0]);

            if (*((int *) pPrevPage) == TEST_PATTERN_A)
                {
                RESTORE_MEMORY_TEST_ADDRS ((int *) pPrevPage, &temp[0]);

                memTopPhys = (char *)pPage;
                found      = TRUE;
                break;
                }

            pPage -= (pageSize * HALF (delta));
            }
        else
            {

            /* The test pattern was written, so assume that <pPage> is the base
             * address of a page in available memory.  Test the next highest
             * page.  If the test pattern is not writable there, assume that
             * <pNextPage> is the address of the first byte beyond that last
             * addressable page.
             */

            UINT8 * pNextPage = (UINT8 *)((UINT32) pPage + pageSize);

            RESTORE_MEMORY_TEST_ADDRS ((int *) pPage, &temp[0]);

            WRITE_MEMORY_TEST_PATTERN ((int *) pNextPage, &temp[0]);

            if (*((int *) pNextPage) != TEST_PATTERN_A)
                {
                memTopPhys = (char *)pNextPage;
                found      = TRUE;
                break;
                }

            RESTORE_MEMORY_TEST_ADDRS ((int *) pNextPage, &temp[0]);

            pPage += (pageSize * HALF (delta));
            }
        }
#endif /* _WRS_CONFIG_WRHV_GUEST */
    }
#endif  /* LOCAL_MEM_AUTOSIZE */


    if (!found)
        {
        memTopPhys = (char *)(LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE);
        }

    /* copy the global descriptor table from RAM/ROM to RAM */

    /* Get the Global Data Table Descriptor */

    vxGdtrGet ( (long long int *)&gDtp );

    /* Extract the number of bytes */

    nGdtBytes = (INT32)gDtp.wGdtr[0];

    /* and calculate the number of entries */

    nGdtEntries = (nGdtBytes + 1 ) / sizeof(GDT);

#ifdef _WRS_CONFIG_SMP
    bcopy ((char *)sysGdt,
           (char *)(_WRS_WIND_VARS_ARCH_ACCESS(pSysGdt)),
           nGdtEntries * sizeof(GDT));
#else
    bcopy ((char *)sysGdt, (char *)pSysGdt, nGdtEntries * sizeof(GDT));
#endif

    /*
     * We assume that there are no memory mapped IO addresses
     * above the "memTopPhys" if INCLUDE_PCI_BUS is not defined.
     * Thus we set the "limit" to get the General Protection Fault
     * when the memory above the "memTopPhys" is accessed.
     */

#if     !defined (INCLUDE_PCI_BUS) && \
    !defined (INCLUDE_MMU_BASIC) && !defined (INCLUDE_MMU_FULL)
        {
        int   ix;
        int   limit = (((UINT32) memTopPhys) >> 12) - 1;
#ifdef _WRS_CONFIG_SMP
        GDT *pGdt = (_WRS_WIND_VARS_ARCH_ACCESS(pSysGdt));
#else
        GDT * pGdt  = pSysGdt;
#endif /* _WRS_CONFIG_SMP */

        for (ix = 1; ix < GDT_ENTRIES; ++ix)
           {
            ++pGdt;
            pGdt->limit00 = limit & 0x0ffff;
            pGdt->limit01 = ((limit & 0xf0000) >> 16) | (pGdt->limit01 & 0xf0);
           }
        }
#endif  /* INCLUDE_PCI_BUS */

    /* load the global descriptor table. set the MMU table */

    *(short *) &gdtr[0] = GDT_ENTRIES * sizeof (GDT) - 1;
#ifdef _WRS_CONFIG_SMP
    *(int *) &gdtr[2] = (int)(_WRS_WIND_VARS_ARCH_ACCESS(pSysGdt));
#else
    *(int *) &gdtr[2] = (int)(pSysGdt);
#endif /* _WRS_CONFIG_SMP */

    sysLoadGdt ((char *)gdtr);

#if (!defined(SYMMETRIC_IO_MODE)) && defined(FAST_REBOOT)
    /*
     * save the brand new bootrom image that will be protected by MMU.
     * The last 2 bytes of ROM_SIZE are for the checksum.
     * - compression would minimize the DRAM usage.
     * - when restore, jumping to the saved image would be faster.
     */

    memTopPhys -= ROM_SIZE;
    bcopy ((char *)ROM_BASE_ADRS, memTopPhys, ROM_SIZE);
    *(UINT16 *)(memTopPhys + ROM_SIZE - 2) =
        checksum ((UINT16 *)memTopPhys, ROM_SIZE - 2);
    memRom = memTopPhys;        /* remember it */
#endif  /* !defined(SYMMETRIC_IO_MODE) && defined(FAST_REBOOT) */

    /* set the MMU descriptor table */

    tempMTP    = (UINT32)memTopPhys & ~(VM_PAGE_SIZE - 1); /* VM_PAGE_SIZE aligned */
    memTopPhys = (char *)tempMTP;

#if (VM_PAGE_SIZE == PAGE_SIZE_4KB)
    pMmu = &sysPhysMemDesc[4];      /* 5th entry: above 1.5MB upper memory */
    pMmu->len = (UINT32) memTopPhys - (UINT32) pMmu->physicalAddr;
#else   /* (VM_PAGE_SIZE == PAGE_SIZE_4KB) */
    pMmu = &sysPhysMemDesc[2];      /* 3rd entry: above 8MB upper memory */
    pMmu->len = (UINT32) memTopPhys - (UINT32) pMmu->physicalAddr;
#endif  /* (VM_PAGE_SIZE == PAGE_SIZE_4KB) */

    return (memTopPhys);
    }

/*******************************************************************************
*
* sysMemTop - get the address of the top of VxWorks memory
*
* This routine returns a pointer to the first byte of memory not
* controlled or used by VxWorks.
*
* The user can reserve memory space by defining the macro USER_RESERVED_MEM
* in config.h.  This routine returns the address of the reserved memory
* area.  The value of USER_RESERVED_MEM is in bytes.
*
* RETURNS: The address of the top of VxWorks memory.
*/

char * sysMemTop (void)
    {
    static char * memTop = NULL;

    if (memTop == NULL)
        {
        memTop = sysPhysMemTop () - USER_RESERVED_MEM;

#ifdef INCLUDE_EDR_PM

        /* account for ED&R persistent memory */

        memTop = memTop - PM_RESERVED_MEM;
#endif

        if ((UINT32)(&end) < 0x100000)      /* this is for bootrom */
            memTop = (char *)EBDA_START;    /* preserve the MP table */
        else if ((UINT32)(&end) < SYS_RAM_LOW_ADRS) /* bootrom in upper mem */
            memTop = (char *)(SYS_RAM_LOW_ADRS & 0xfff00000);
        }

    return (memTop);
    }

/*******************************************************************************
*
* sysToMonitor - transfer control to the ROM monitor
*
* This routine transfers control to the ROM monitor.  It is usually called
* only by reboot() -- which services ^X -- and by bus errors at interrupt
* level.  However, in some circumstances, the user may wish to introduce a
* new <startType> to enable special boot ROM facilities.
*
* RETURNS: Does not return.
*/

STATUS sysToMonitor
    (
    int startType   /* passed to ROM to tell it how to boot */
    )
    {
    sysOutByte (COMMAND_8042, (char) 0xfe);
#ifndef _WRS_CONFIG_WRHV_GUEST
    FUNCPTR pEntry;
    INT16 * pDst;
#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
    BOOL enable = FALSE;
#endif /*  defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE) */

#ifdef _WRS_CONFIG_SMP
    UINT32 sysShutdownLoopCounter;
#endif /* _WRS_CONFIG_SMP */

    intCpuLock();        /* LOCK INTERRUPTS */

#ifdef _WRS_CONFIG_SMP
    /* At this point we are either the bootstrap processor,
     * or an application processor...
     *
     * ...need to reset APs and go out on the bootstrap processor...
     */

    if (vxCpuIndexGet() != 0)
      {
       /* CPCs use ipiId = 0 */

       vxIpiConnect (0,
                     (IPI_HANDLER_FUNC) (sysToMonitor),
	             (void *) startType);

       vxIpiEmit(0, 1);

       taskCpuLock();       /* if not in interrupt context, taskCpuLock */

       for ( sysShutdownLoopCounter = 0; ; sysShutdownLoopCounter++)
          sysDelay();
      }

    sysCpuStop_APs ();    /* stop APs */
    sysDelay();

    sysCpuReset_APs ();   /* place APs in reset */
    sysDelay();
#endif /* _WRS_CONFIG_SMP */

    /* now running on BSP, APs in reset... */

#if (CPU == PENTIUM2) || (CPU == PENTIUM3) || (CPU == PENTIUM4)
#if defined (INCLUDE_MMU_P6_32BIT)
    mmuPro32Enable (FALSE);          /* disable MMU */
#else
    mmuPro36Enable (FALSE);          /* disable MMU */
#endif /* defined (INCLUDE_MMU_P6_32BIT) */
#else
    mmuI86Enable (FALSE);            /* disable MMU */
#endif  /* (CPU == PENTIUM) || (CPU == PENTIUM[234]) */

#if (CPU == PENTIUM) || (CPU == PENTIUM2) || (CPU == PENTIUM3) || \
    (CPU == PENTIUM4)
    /*pentiumMsrInit ();           initialize MSRs */
#endif  /* (CPU == PENTIUM) || (CPU == PENTIUM[234]) */

#if defined(SYMMETRIC_IO_MODE)
#ifdef _WRS_CONFIG_SMP
    /* restore trampoline code space for warm reboot */

    bcopy ((char *)(&tramp_code[0]),
           (char *)(CPU_ENTRY_POINT),
           (int)CPU_AP_AREA);
#endif /* _WRS_CONFIG_SMP */
#endif  /* defined(SYMMETRIC_IO_MODE) */

    /* If this is a cold reboot */

    if (startType == BOOT_COLD)
      goto sysToMonitorCold;

#if defined(SYMMETRIC_IO_MODE)
    pDst = (short *)SYS_RAM_HIGH_ADRS;  /* copy it in lower mem */
    pEntry = (FUNCPTR)(ROM_TEXT_ADRS + ROM_WARM_HIGH);
#else
    /* decide a destination RAM address and the entry point */

    if ((UINT32)(&end) > SYS_RAM_LOW_ADRS)
      {
       pDst = (short *)SYS_RAM_HIGH_ADRS;  /* copy it in lower mem */
       pEntry = (FUNCPTR)(SYS_RAM_HIGH_ADRS + ROM_WARM_HIGH);
      }
    else
      {
       pDst = (short *)SYS_RAM_LOW_ADRS;   /* copy it in upper mem */
       pEntry = (FUNCPTR)(SYS_RAM_LOW_ADRS + ROM_WARM_LOW);
      }
#endif  /* defined(SYMMETRIC_IO_MODE) */

#if (!defined(SYMMETRIC_IO_MODE)) && defined(FAST_REBOOT)
    /* restore the saved brand new bootrom image, then jump */

    if ((memRom != NULL) &&
        (*(UINT16 *)(memRom + ROM_SIZE - 2) ==
         checksum ((UINT16 *)memRom, ROM_SIZE - 2)))
      {
       INT32 ix;
       INT32 * dst = (INT32 *) ROM_TEXT_ADRS;
       INT32 * src = (INT32 *) memRom;

       pEntry = (FUNCPTR)(ROM_TEXT_ADRS + ROM_WARM_HIGH);

       for (ix = 0; ix < (ROM_SIZE >> 2); ix++)
          *dst++ = *src++;

       goto sysToMonitorWarm;
      }
#endif  /* !defined(SYMMETRIC_IO_MODE) && defined(FAST_REBOOT) */

    /* disable 16-bit memory access */

#ifdef  INCLUDE_ELC
    sysOutByte (IO_ADRS_ELC + 5, sysInByte (IO_ADRS_ELC + 5) & ~0x80);
#endif  /* INCLUDE_ELC */

#ifdef  INCLUDE_ROMCARD
    {
    INT32 ix;
    INT32 iy;
    INT32 iz;
    char buf[ROM_SIGNATURE_SIZE];
    short *pSrc;

    /* copy EPROM to RAM and jump, if there is a VxWorks EPROM */

    for (ix = 0; ix < NELEMENTS(sysRomBase); ix++)
    {
    bcopyBytes ((char *)sysRomBase[ix], buf, ROM_SIGNATURE_SIZE);
    if (strncmp (sysRomSignature, buf, ROM_SIGNATURE_SIZE) == 0)
        {
        for (iy = 0; iy < 1024; iy++)
        {
        *sysRomBase[ix] = iy;   /* map the moveable window */
        pSrc = (short *)((int)sysRomBase[ix] + 0x200);
            for (iz = 0; iz < 256; iz++)
            *pDst++ = *pSrc++;
        }
        goto sysToMonitorWarm;  /* jump to the entry point */
        }
    }
    }
#endif  /* INCLUDE_ROMCARD */

    /* If here because of fatal error during an interrupt just reboot */

#ifdef _WRS_CONFIG_SMP
    if(INT_CONTEXT())
#else
    if(intCnt > 0)
#endif
        {
        pEntry = (FUNCPTR)(ROM_TEXT_ADRS + ROM_WARM_HIGH);

        sysClkDisable ();   /* disable the system clock interrupt */
        sysIntLock ();      /* lock the used/owned interrupts */

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
	/* Shutdown Local APIC */
        (*getLoApicIntrEnable)(loApicDevID, (void *) &enable);
#endif /*  defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE) */

#if defined (SYMMETRIC_IO_MODE)
	/* Restore Local APIC initial settings prior to enable */
	*(volatile int *)(LOAPIC_BASE + 0x0f0) = /* LOAPIC_SVR */
            (int)glbLoApicOldSvr;
	*(volatile int *)(LOAPIC_BASE + 0x350) = /* LOAPIC_LINT0 */
            (int)glbLoApicOldLint0;
	*(volatile int *)(LOAPIC_BASE + 0x360) = /* LOAPIC_LINT1 */
            (int)glbLoApicOldLint1;
#endif /*  defined (SYMMETRIC_IO_MODE) */

        (*pEntry) (startType);

        /* Oops, This should not happen - Reset */

        goto sysToMonitorCold;
        }

    /* jump to the warm start entry point */

#if (((!defined(SYMMETRIC_IO_MODE)) && defined(FAST_REBOOT)) || \
		defined(INCLUDE_ROMCARD))
sysToMonitorWarm:       /* cleanup and jump to the entry point */
#endif

    {
    sysClkDisable ();   /* disable the system clock interrupt */
    sysIntLock ();      /* lock the used/owned interrupts */

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
    /* Shutdown Local APIC */
    (*getLoApicIntrEnable)(loApicDevID, (void *) &enable);
#endif /*  defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE) */

#if defined (SYMMETRIC_IO_MODE)
    /* Restore Local APIC initial settings prior to enable */
    *(volatile int *)(LOAPIC_BASE + 0x0f0) = /* LOAPIC_SVR */
	(int)glbLoApicOldSvr;
    *(volatile int *)(LOAPIC_BASE + 0x350) = /* LOAPIC_LINT0 */
	(int)glbLoApicOldLint0;
    *(volatile int *)(LOAPIC_BASE + 0x360) = /* LOAPIC_LINT1 */
	(int)glbLoApicOldLint1;
#endif /*  defined (SYMMETRIC_IO_MODE) */

    (*pEntry) (startType);

    return (OK);    /* in case we ever continue from ROM monitor */
    }

sysToMonitorCold:

    /* perform the cold boot since the warm boot is not possible */

#ifdef INCLUDE_ELC
    elcdetach (0);
#endif /* INCLUDE_ELC */

    sysClkDisable ();

    sysWait ();
    sysOutByte (COMMAND_8042, (char) 0xfe);

    sysWait ();
    sysOutByte (COMMAND_8042, (char) 0xff);

    vxGdtrSet (0);  /* crash the global descriptor table */

    return (OK);    /* in case we ever continue from ROM monitor */
#else	/* _WRS_CONFIG_WRHV_GUEST */
# if (VBI_VERSION_MAJOR == 2)
    /* XXX no warm boot support yet */

    vbiVbReset (VBI_BOARD_ID_GET(), VBI_VB_CORES_ALL,
		VBI_VBMGMT_RESET_DOWNLOAD | VBI_VBMGMT_RESET_AND_START_CORE0);

    return OK;
# else /* VBI_VERSION_MAJOR == 1 */
    uint32_t flags;
    int key;

    if (startType == BOOT_COLD)
	flags = 0;		/* clear memory if cold boot */
    else
	flags = VBI_VBMGMT_RESET_NO_CLEAR;

    key = intCpuLock();		/* LOCK INTERRUPTS */

    vbiVbMgmt (VBI_VBMGMT_RESET, VBI_CONTEXT_ID_GET(),
			(int32_t *)&errno, flags, NULL);

    /* XXX following the native vxWorks' behavior XXX */

    intCpuUnlock(key);		/* UNLOCK INTERRUPTS */
    return OK;			/* in case we ever continue from ROM monitor */
# endif /* VBI_VERSION_MAJOR */
#endif	/* _WRS_CONFIG_WRHV_GUEST */
    }

/*******************************************************************************
*
* sysIntInitPIC - initialize the interrupt controller
*
* This routine initializes the interrupt controller.
* Maps APIC and HPET Memory space.
*
* RETURNS: N/A
*
*/

void sysIntInitPIC (void)
    {
#ifndef _WRS_CONFIG_WRHV_GUEST
#if defined(VIRTUAL_WIRE_MODE)
    {
    /* Map Local APIC Address space... */

    UINT32 mpApicloBase;
    UINT32 lengthLo;    /* length of Local APIC registers */

    i8259Init ();

    /* add an entry to the sysMmuPhysDesc[] for Local APIC */

    (*getMpApicloBaseGet) (mpApicDevID, &mpApicloBase);
    lengthLo = ((UINT32)LOAPIC_LENGTH / VM_PAGE_SIZE) * VM_PAGE_SIZE;

    sysMmuMapAdd ((void *)mpApicloBase, lengthLo,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
    }
#elif   defined(SYMMETRIC_IO_MODE)
    {
    /* Map Local and IO APIC Address spaces... */

    UINT32 lengthLo;    /* length of Local APIC registers */
    UINT32 lengthIo;    /* length of IO APIC registers */

    int    i;

    UINT32 mpApicloBase;
    UINT32 mpApicNioApic;

    UINT32 *mpApicAddrTable;
    
    /* add an entry to the sysMmuPhysDesc[] for Local APIC and IO APIC */
    /* only do this once...                                            */

    (*getMpApicloBaseGet) (mpApicDevID, &mpApicloBase);
    lengthLo = ((UINT32)LOAPIC_LENGTH / VM_PAGE_SIZE) * VM_PAGE_SIZE;

    sysMmuMapAdd ((void *)mpApicloBase, lengthLo,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);

    (*getMpApicNioApicGet) (mpApicDevID, &mpApicNioApic);
    (*getMpApicAddrTableGet)(mpApicDevID, (void *)&mpApicAddrTable);

    lengthIo = ((UINT32)IOAPIC_LENGTH / VM_PAGE_SIZE) * VM_PAGE_SIZE;

    for(i=0; i<mpApicNioApic; i++)
    {
    sysMmuMapAdd ((void *)(mpApicAddrTable[i]), lengthIo,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
    }

#ifdef _WRS_CONFIG_SMP
#ifdef DRV_TIMER_IA_TIMESTAMP
    /* SMP requires an High Precision Event Timer for Timestamp...
     *
     * Map out memory space for HPET...
     */

    hpetMmuMap ();
#endif /* DRV_TIMER_IA_TIMESTAMP */
#endif /* _WRS_CONFIG_SMP */
    }
#else
    i8259Init ();
#endif  /* defined(VIRTUAL_WIRE_MODE) */
#endif  /* !_WRS_CONFIG_WRHV_GUEST */
    }

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
/*******************************************************************************
*
* apicIntrIntHelper - initialize pointers to vxBus driver routines.
*
* This routine initializes pointers to vxBus driver routines up front, rather
* than calling into vxBus API...
*
* Called from "sysPciPirqEnable" because we require intEnable/Disable early on
* during PCI initialization...
*
* RETURNS: STATUS
*
*/

STATUS apicIntrIntHelper(VXB_DEVICE_ID pDev, void * unused)
    {
    FUNCPTR func;

    /* check for MP APIC */

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(mpApicLoIndexTableGet));
    if ( func != NULL )
      {
      mpApicDevID = pDev;
      getMpApicLoIndexTable = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(mpApicloBaseGet));
    if ( func != NULL )
      {
      mpApicDevID = pDev;
      getMpApicloBaseGet = func;
      }

#if defined(SYMMETRIC_IO_MODE)
    /* check for IO APIC */

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(mpApicNioApicGet));
    if ( func != NULL )
      {
      mpApicDevID = pDev;
      getMpApicNioApicGet = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(mpApicAddrTableGet));
    if ( func != NULL )
      {
      mpApicDevID = pDev;
      getMpApicAddrTableGet = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(ioApicRedNumEntriesGet));
    if ( func != NULL )
      {
      ioApicDevID = pDev;
      getIoApicRedNumEntriesGet = func;
      }

    getIoApicIntrIntEnable = NULL;
    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(ioApicIntrIntEnable));
    if ( func != NULL )
      {
      ioApicDevID = pDev;
      getIoApicIntrIntEnable = func;
      }

    getIoApicIntrIntDisable = NULL;
    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(ioApicIntrIntDisable));
    if ( func != NULL )
      {
      ioApicDevID = pDev;
      getIoApicIntrIntDisable = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(ioApicIntrIntLock));
    if ( func != NULL )
      {
      ioApicDevID = pDev;
      getIoApicIntrIntLock = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(ioApicIntrIntUnlock));
    if ( func != NULL )
      {
      ioApicDevID = pDev;
      getIoApicIntrIntUnlock = func;
      }
#endif /* defined(SYMMETRIC_IO_MODE) */

    /* check for Local APIC */

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(loApicIntrInitAP));
    if ( func != NULL )
      {
      loApicDevID = pDev;
      getLoApicIntrInitAP = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(loApicIntrEnable));
    if ( func != NULL )
      {
      loApicDevID = pDev;
      getLoApicIntrEnable = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(loApicIntrIntLock));
    if ( func != NULL )
      {
      loApicDevID = pDev;
      getLoApicIntrIntLock = func;
      }

    func = vxbDevMethodGet(pDev, DEVMETHOD_CALL(loApicIntrIntUnlock));
    if ( func != NULL )
      {
      loApicDevID = pDev;
      getLoApicIntrIntUnlock = func;
      }

    return(OK);
    }
#else
/* Arch or BSP system-dependent implementation routine,
 * used to dummy up the UP implementation of vxCpuIndexGet. 
 * Under UP always 0. 
 */

unsigned int dummyGetCpuIndex (void)
    {
    return (0);
    }
#endif /* defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE) */

/*******************************************************************************
*
* sysIntLock - lock out all interrupts
*
* This routine saves the mask and locks out all interrupts.
*
* SEE ALSO: sysIntUnlock()
*
*/

VOID sysIntLock (void)
    {
    INT32 oldLevel = intCpuLock();  /* LOCK INTERRUPTS */
#ifndef _WRS_CONFIG_WRHV_GUEST

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
    int dummy = 0xdead;
#endif /* SYMMETRIC_IO_MODE || VIRTUAL_WIRE_MODE */

#if defined(VIRTUAL_WIRE_MODE)
    (*getLoApicIntrIntLock)(loApicDevID, (void *) &dummy);
    i8259IntLock ();
#elif defined(SYMMETRIC_IO_MODE)
    (*getLoApicIntrIntLock)(loApicDevID, (void *) &dummy);
    (*getIoApicIntrIntLock)(ioApicDevID, (void *) &dummy);
#else
    i8259IntLock ();
#endif  /* defined(VIRTUAL_WIRE_MODE) */

#else   /* _WRS_CONFIG_WRHV_GUEST */
    vIoApicIntLock();
#endif  /* _WRS_CONFIG_WRHV_GUEST */

    intCpuUnlock(oldLevel);         /* UNLOCK INTERRUPTS */
    }

/*******************************************************************************
*
* sysIntUnlock - unlock the PIC interrupts
*
* This routine restores the mask and unlocks the PIC interrupts
*
* SEE ALSO: sysIntLock()
*
*/

VOID sysIntUnlock (void)
    {
    INT32 oldLevel = intCpuLock();  /* LOCK INTERRUPTS */
#ifndef _WRS_CONFIG_WRHV_GUEST

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
    int dummy = 0xdead;
#endif /* SYMMETRIC_IO_MODE || VIRTUAL_WIRE_MODE */

#if defined(VIRTUAL_WIRE_MODE)
    (*getLoApicIntrIntUnlock)(loApicDevID, (void *) &dummy);
    i8259IntUnlock ();
#elif defined(SYMMETRIC_IO_MODE)
    (*getLoApicIntrIntUnlock)(loApicDevID, (void *) &dummy);
    (*getIoApicIntrIntUnlock)(ioApicDevID, (void *) &dummy);
#else
    i8259IntUnlock ();
#endif /* defined(VIRTUAL_WIRE_MODE) */

#else  /* _WRS_CONFIG_WRHV_GUEST */
    vIoApicIntUnlock();
#endif /* _WRS_CONFIG_WRHV_GUEST */

    intCpuUnlock(oldLevel);         /* UNLOCK INTERRUPTS */
    }

/*******************************************************************************
*
* sysIntDisablePIC - disable a bus interrupt level
*
* This routine disables a specified bus interrupt level.
*
* RETURNS: OK, or ERROR if failed.
*
*/

STATUS sysIntDisablePIC
    (
    int irqNo       /* IRQ(PIC) or INTIN(APIC) number to disable */
    )
    {
#ifndef _WRS_CONFIG_WRHV_GUEST

#if defined(SYMMETRIC_IO_MODE)
    if (getIoApicIntrIntDisable != NULL)
        return ((*getIoApicIntrIntDisable)(ioApicDevID, (void *)&irqNo));
    else
        return (vxbDevMethodRun(DEVMETHOD_CALL(ioApicIntrIntDisable),(void *)&irqNo));
#else
    return (i8259IntDisable (irqNo));
#endif /* defined(VIRTUAL_WIRE_MODE) */

#else  /* _WRS_CONFIG_WRHV_GUEST */
    return vIoApicIntDisable (irqNo);
#endif /* _WRS_CONFIG_WRHV_GUEST */
    }

/*******************************************************************************
*
* sysIntEnablePIC - enable a bus interrupt level
*
* This routine enables a specified bus interrupt level.
*
* RETURNS: OK, or ERROR if failed.
*
*/

STATUS sysIntEnablePIC
    (
    int irqNo       /* IRQ(PIC) or INTIN(APIC) number to enable */
    )
    {
#ifndef _WRS_CONFIG_WRHV_GUEST

#if defined(SYMMETRIC_IO_MODE)
      if (getIoApicIntrIntEnable != NULL)
        return ((*getIoApicIntrIntEnable)(ioApicDevID, (void *)&irqNo));
      else
        return (vxbDevMethodRun(DEVMETHOD_CALL(ioApicIntrIntEnable),(void *)&irqNo));
#else
    return (i8259IntEnable (irqNo));
#endif /* defined(VIRTUAL_WIRE_MODE) */

#else  /* _WRS_CONFIG_WRHV_GUEST */
    return vIoApicIntEnable (irqNo);
#endif /* _WRS_CONFIG_WRHV_GUEST */
    }

#if defined (SYMMETRIC_IO_MODE) || defined (VIRTUAL_WIRE_MODE)
/******************************************************************************* *
 * loApicIntEoi -  send EOI (End Of Interrupt) signal to Local APIC
 *
 * This routine sends an EOI signal to the Local APIC's interrupting source.
 *
 * RETURNS: N/A
 */

void sysLoApicIntEoi
    (
    INT32 irqNo         /* INIIN number to send EOI */
    )
    {
    *(int *)(LOAPIC_BASE + LOAPIC_EOI) = 0;
    }
#endif /* SYMMETRIC_IO_MODE || VIRTUAL_WIRE_MODE */

/*******************************************************************************
*
* sysIntEoiGet - get EOI/BOI function and its parameter
*
* This routine gets EOI function and its parameter for the interrupt controller.
* If returned EOI/BOI function is NULL, intHandlerCreateX86() replaces
* "call _routineBoi/Eoi" in intConnectCode[] with NOP instruction.
*
* RETURNS: N/A
*
*/

void sysIntEoiGet
    (
    VOIDFUNCPTR * vector,   /* interrupt vector to attach to */
    VOIDFUNCPTR * routineBoi,   /* BOI function */
    int * parameterBoi,     /* a parameter of the BOI function */
    VOIDFUNCPTR * routineEoi,   /* EOI function */
    int * parameterEoi      /* a parameter of the EOI function */
    )
    {
    int intNum = IVEC_TO_INUM (vector);
    int irqNo;

    /* set default BOI routine & parameter */

    *routineBoi   = NULL;
    *parameterBoi = 0;

#ifndef _WRS_CONFIG_WRHV_GUEST

    /* find a match in sysInumTbl[] */

    for (irqNo = 0; irqNo < sysInumTblNumEnt; irqNo++)
        {
        if (sysInumTbl[irqNo] == intNum)
            break;
        }

    *parameterEoi = irqNo;  /* irq is sysInumTblNumEnt, if no match */

#if defined (SYMMETRIC_IO_MODE)
      if (intNum == INT_NUM_LOAPIC_SPURIOUS)
        *routineEoi = NULL;        /* no EOI is necessary */
      else
        *routineEoi = sysLoApicIntEoi; /* set Local APIC's EOI routine */
#else

#if defined (VIRTUAL_WIRE_MODE)

    if (irqNo >= N_PIC_IRQS)        /* IRQ belongs to the Local APIC */
        {
        if (intNum == INT_NUM_LOAPIC_SPURIOUS)
            *routineEoi = NULL;     /* no EOI is necessary */
        else
            *routineEoi = sysLoApicIntEoi; /* set Local APIC's EOI routine */
    return;
    }

#endif /* VIRTUAL_WIRE_MODE */

    /* set the [BE]OI parameter for the master & slave PIC */

    *parameterBoi = irqNo;
    *parameterEoi = irqNo;

    /* set the right BOI routine */

    if (irqNo == 0)         /* IRQ0 BOI routine */
    {
#if (PIC_IRQ0_MODE == PIC_AUTO_EOI)
        *routineBoi   = NULL;
#elif   (PIC_IRQ0_MODE == PIC_EARLY_EOI_IRQ0)
        *routineBoi   = i8259IntBoiEem;
#elif   (PIC_IRQ0_MODE == PIC_SPECIAL_MASK_MODE_IRQ0)
        *routineBoi   = i8259IntBoiSmm;
#else
        *routineBoi   = NULL;
#endif  /* (PIC_IRQ0_MODE == PIC_AUTO_EOI) */
    }
    else if ((irqNo == PIC_MASTER_STRAY_INT_LVL) ||
         (irqNo == PIC_SLAVE_STRAY_INT_LVL))
    {
        *routineBoi   = i8259IntBoi;
    }

    /* set the right EOI routine */

    if (irqNo == 0)         /* IRQ0 EOI routine */
    {
#if (PIC_IRQ0_MODE == PIC_AUTO_EOI) || \
    (PIC_IRQ0_MODE == PIC_EARLY_EOI_IRQ0)
        *routineEoi   = NULL;
#elif   (PIC_IRQ0_MODE == PIC_SPECIAL_MASK_MODE_IRQ0)
        *routineEoi   = i8259IntEoiSmm;
#else
        *routineEoi   = i8259IntEoiMaster;
#endif  /* (PIC_IRQ0_MODE == PIC_AUTO_EOI) || (PIC_EARLY_EOI_IRQ0) */
    }
    else if (irqNo < 8)         /* IRQ[1-7] EOI routine */
    {
#if (PIC_IRQ0_MODE == PIC_AUTO_EOI)
        *routineEoi   = NULL;
#else
        *routineEoi   = i8259IntEoiMaster;
#endif  /* (PIC_IRQ0_MODE == PIC_AUTO_EOI) */
    }
    else                /* IRQ[8-15] EOI routine */
    {
#if defined (PIC_SPECIAL_FULLY_NESTED_MODE)
        *routineEoi   = i8259IntEoiSlaveSfnm;
#else
        *routineEoi   = i8259IntEoiSlaveNfnm;
#endif  /* defined (PIC_SPECIAL_FULLY_NESTED_MODE) */
    }
#endif  /* SYMMETRIC_IO_MODE */

#else  /* _WRS_CONFIG_WRHV_GUEST */

    irqNo = intNum - INT_NUM_IRQ0;
    *parameterEoi = irqNo;
    *routineEoi = vIoApicIntAck;

#endif /* _WRS_CONFIG_WRHV_GUEST */
    }

/*******************************************************************************
*
* sysIntLevel - get an IRQ(PIC) or INTIN(APIC) number in service
*
* This routine gets an IRQ(PIC) or INTIN(APIC) number in service.
* We assume the following:
*   - this function is called in intEnt()
*   - IRQ number of the interrupt is at intConnectCode [29]
*
* RETURNS: 0 - (sysInumTblNumEnt - 1), or sysInumTblNumEnt if we failed to get it.
*
*/

int sysIntLevel
    (
    int arg     /* parameter to get the stack pointer */
    )
    {
    UINT32 * pStack;
    UCHAR * pInst;
    INT32 ix;
    INT32 irqNo = sysInumTblNumEnt; /* return sysInumTblNumEnt if we failed */

    pStack = (UINT32 *)&arg;    /* get the stack pointer */
    pStack += 3;        /* skip pushed volatile registers */

    /*
     * we are looking for a return address on the stack which point
     * to the next instruction of "call _intEnt" in the malloced stub.
     * Then get the irqNo at intConnectCode [29].
     */

    for (ix = 0; ix < 10; ix++, pStack++)
    {
    pInst = (UCHAR *)*pStack;       /* return address */
    if ((*pInst == 0x50) &&         /* intConnectCode [5] */
        ((*(int *)(pInst - 4) + (int)pInst) == (int)intEnt))
        {
            irqNo = *(int *)(pInst + 24);   /* intConnectCode [29] */
        break;
        }
    }

    return (irqNo);
    }

/****************************************************************************
*
* sysProcNumGet - get the processor number
*
* This routine returns the processor number for the CPU board, which is
* set with sysProcNumSet().
*
* RETURNS: The processor number for the CPU board.
*
* SEE ALSO: sysProcNumSet()
*/

int sysProcNumGet (void)
    {
    return (sysProcNum);
    }

/****************************************************************************
*
* sysProcNumSet - set the processor number
*
* Set the processor number for the CPU board.  Processor numbers should be
* unique on a single backplane.
*
* NOTE: By convention, only Processor 0 should dual-port its memory.
*
* RETURNS: N/A
*
* SEE ALSO: sysProcNumGet()
*/

void sysProcNumSet
    (
    int procNum     /* processor number */
    )
    {
    sysProcNum = procNum;
    }

/*******************************************************************************
*
* sysDelay - allow recovery time for port accesses
*
* This routine provides a brief delay used between accesses to the same serial
* port chip.
*
* RETURNS: N/A
*/

void sysDelay (void)
    {
    char ix;

    ix = sysInByte (UNUSED_ISA_IO_ADDRESS); /* it takes 720ns */
    }

/*******************************************************************************
*
* sysUsDelay - delay specified number of microseconds
*
* This routine provides a brief delay used between accesses to the same serial
* port chip.
*
* RETURNS: N/A
*/

void sysUsDelay
    (
    int uSec
    )
    {
    int counter;

    counter = ( ( uSec + 719 ) * 1000 ) / 720;
    while ( counter-- > 0 )
        sysDelay();
    }

/*******************************************************************************
*
* sysStrayInt - Do nothing for stray interrupts.
*
* Do nothing for stray interrupts.
*/

void sysStrayInt (void)
    {
    sysStrayIntCount++;
    }

/*******************************************************************************
*
* sysMmuMapAdd - insert a new MMU mapping
*
* This routine will create a new <sysPhysMemDesc> table entry for a memory
* region of specified <length> in bytes and with a specified base
* <address>.  The <initialStateMask> and <initialState> parameters specify
* a PHYS_MEM_DESC type state mask and state for the memory region.
*
* CAVEATS
* This routine must be used before the <sysPhysMemDesc> table is
* referenced for the purpose of initializing the MMU or processor address
* space (us. in usrMmuInit()).
*
* The <length> in bytes will be rounded up to a multiple of VM_PAGE_SIZE
* bytes if necessary.
*
* The current implementation assumes a one-to-one mapping of physical to
* virtual addresses.
*
* RETURNS: OK or ERROR depending on availability of free mappings.
*
* SEE ALSO: vmLib
*/

STATUS sysMmuMapAdd
    (
    void * address,           /* memory region base address */
    UINT   length,            /* memory region length in bytes*/
    UINT   initialStateMask,  /* PHYS_MEM_DESC state mask */
    UINT   initialState       /* PHYS_MEM_DESC state */
    )
    {
    STATUS result = OK;

    PHYS_MEM_DESC * const pMmu = &sysPhysMemDesc[sysPhysMemDescNumEnt];


    if (pMmu->virtualAddr != (VIRT_ADDR) DUMMY_VIRT_ADDR)
        {
        result = ERROR;
        }
    else
        {
        pMmu->virtualAddr   = (VIRT_ADDR)address;
        pMmu->physicalAddr  = (PHYS_ADDR)address;
        pMmu->len           = ROUND_UP (length, VM_PAGE_SIZE);
        pMmu->initialStateMask  = initialStateMask;
        pMmu->initialState  = initialState;
        sysPhysMemDescNumEnt    += 1;
        }

    return (result);
    }

#ifdef DRV_SIO_NS16550
SIO_CHAN * bspSerialChanGet
    (
    int channel     /* serial channel */
    )
    {
    return ((SIO_CHAN *) ERROR);
    }
#endif /* DRV_SIO_NS16550 */

#if defined (INCLUDE_VXBUS)
#if defined(INCLUDE_PC_CONSOLE) && defined (DRV_TIMER_I8253)
/*******************************************************************************
*
* sysConBeep - sound beep function (using timer 2 for tone)
*
* This function is responsible for producing the beep
*
* RETURNS: N/A
*
* NOMANUAL
*/

LOCAL void sysConBeep
    (
    BOOL	mode	/* TRUE:long beep  FALSE:short beep */
    )
    {
    int		beepTime;
    int		beepPitch;
    FAST int	oldlevel;

    if (mode)
        {
        beepPitch = BEEP_PITCH_L;
        beepTime  = BEEP_TIME_L;	/* long beep */
        }
    else
        {
        beepPitch = BEEP_PITCH_S;
        beepTime  = BEEP_TIME_S;	/* short beep */
        }

    oldlevel = intCpuLock ();

    /* set command for counter 2, 2 byte write */

    sysOutByte(PIT_BASE_ADR + 3, (char)0xb6);
    sysOutByte(PIT_BASE_ADR + 2, (beepPitch & 0xff));
    sysOutByte(PIT_BASE_ADR + 2, (beepPitch >> 8));

    /* enable counter 2 */

    sysOutByte(DIAG_CTRL, sysInByte(DIAG_CTRL) | 0x03);

    taskDelay (beepTime);

    /* disable counter 2 */

    sysOutByte(DIAG_CTRL, sysInByte(DIAG_CTRL) & ~0x03);

    intCpuUnlock (oldlevel);
    return;
    }
#endif /* INCLUDE_PC_CONSOLE && DRV_TIMER_I8253 */
#endif /* INCLUDE_VXBUS && DRV_TIMER_I8253 */

#ifdef _WRS_CONFIG_SMP
#ifdef DRV_TIMER_IA_TIMESTAMP
/* SMP requires an High Precision Event Timer for Timestamp... */

/*******************************************************************************
*
* hpetMmuMap - Maps High Precision Event Timer Memory space.
*
* This routine adds an entry to the sysMmuPhysDesc[] for HPET.
*
* RETURNS: N/A
*/

LOCAL void hpetMmuMap (void)
    {
    UINT32 addr;      /* page aligned HPET Base Address */
    UINT32 length;    /* length of HPET register space  */

    /* add an entry to the sysMmuPhysDesc[] for HPET
     * cover all 4 possible memory address ranges...
     */

    addr   = (UINT32)HPET_TIMESTAMP;
    length = ((UINT32)HPET_MEM_ADDR_RNG / VM_PAGE_SIZE) * VM_PAGE_SIZE;

    sysMmuMapAdd ((void *)addr, length,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);

#if defined(INCLUDE_ICH7_SUPPORT)
    /* ICH7 used on idp945 (Capell Valley), need to read Root Complex Base
     * Address, and map the address range for the root complex register block...
     */

    addr = 0;
    pciConfigInLong(LPC_BUSNO, LPC_DEVNO, LPC_FUNCNO, LPC_RCBA_REG, &addr);

    addr = addr & RCBA_ADDR_MSK;
    length = ((UINT32)RCBA_MEM_ADDR_RNG / VM_PAGE_SIZE) * VM_PAGE_SIZE;
    sysMmuMapAdd ((void *)addr, length,
                  VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_IO);
#endif
    }

/*******************************************************************************
*
* hpetInit - Initialize  HPET...
*
* Initialize High Precision Event Timer Functionality for
* Timestamp usage.
*
* RETURNS: N/A
*/

LOCAL void hpetInit (void)
    {
    UINT32 scratch;    /* save & restore 32-bit Var */
#if defined(INCLUDE_ICH7_SUPPORT)
    UINT32 scratch2;    /* save & restore 32-bit Var */
#endif

    /* This is where Allagash & Capell Valley (idp945) diverge...
     *
     * Allagash makes use of the Intel 6300ESB ICH, while
     * Capell Valley (idp945) uses ICH7...
     */

    /* Enable ICH to decode the High Performance Event Timer
     * Memory Address Range...
     */

#if (!defined(INCLUDE_ICH7_SUPPORT))
    /* The LPC Bridge function resides in PCI Device:31, Function:0. */

    /* read General Control Register */
    scratch = 0;
    pciConfigInLong(LPC_BUSNO, LPC_DEVNO, LPC_FUNCNO, LPC_GEN_CNTRL, &scratch);

    /* set MMT_ADDR_EN */
    scratch = scratch | HPET_ADDR_ENABLE;

    /* write General Control Register */
    pciConfigOutLong(LPC_BUSNO, LPC_DEVNO, LPC_FUNCNO, LPC_GEN_CNTRL, scratch);
#else
    /* The RCBA resides in PCI Device:31, Function:F0. */

    /* read Root Complex Base Address */

    scratch = 0;
    pciConfigInLong(LPC_BUSNO, LPC_DEVNO, LPC_FUNCNO, LPC_RCBA_REG, &scratch);

    /* write Root Complex Base Address enabling base address for the
     * root complex register block
     */
    pciConfigOutLong(LPC_BUSNO, LPC_DEVNO, LPC_FUNCNO,
		     LPC_RCBA_REG, (scratch|RCBA_ADDR_ENBL));

    /* setup High Precision Timer Configuration Register */
    scratch = scratch & HPTC_REG_MSK;
    scratch = scratch | HPTC_REG_OFFSET;

    /* write High Precision Timer Configuration Register to enable HPET
     * memory address ranges.
     */

    scratch2 = *(volatile UINT32 *)(scratch);
    *(volatile UINT32 *)(scratch) = scratch2 | HPTC_ADDR_ENBL;
#endif

    /* IA-32 SMP Timestamp based off of a 64-bit free running counter.
     * IA-32 will be using HPET Timer #0, using default address range
     * HPET_ADDR_SEL_00 (0xFED00000)...
     *
     * counter reg initialized by default to 0x0000000000000000, and
     * comparator reg defaults to 0xffffffffffffffff. All we have to
     * really do is enable it...
     */

    /* initialize counter & comparator registers to be safe... */

    *(volatile UINT64 *)(HP_TS_MN_CNTR) = 0x0000000000000000;
    *(volatile UINT64 *)(HP_TS_T0_COMP) = 0xFFFFFFFFFFFFFFFFLL;

    /* read general config reg */

    scratch = *(volatile UINT32 *)(HP_TS_GEN_CON);

    scratch |= (UINT32)HPET_EN_CNF_MSK;               /* ENABLE_CNF */

    /* write general config reg */

    *(volatile UINT32 *)(HP_TS_GEN_CON) = scratch;

    /* 64-bit free running counter enabled and running... */
    }
#endif /* DRV_TIMER_IA_TIMESTAMP */
#endif /* _WRS_CONFIG_SMP */

#ifdef _WRS_CONFIG_SMP
/******************************************************************************
 *
 * sysCpuAvailableGet - return the number of CPUs that are to
 *                      be used by vxWorks for the SMP kernel.
 *
 * RETURNS: The number for the CPUs available
 *
 */

UINT32 sysCpuAvailableGet(void)
{
    /* enforce arch limitation  for SMP configurable cores */

    return ((UINT32) (vxCpuCount));
}

/*******************************************************************************
 *
 * vxCpuStateInit - Initialize the state to start a CPU in.
 *
 * The purpose of this function is somewhat similar to the arch-specific
 * function taskRegsInit(), except that this function initializes a
 * WIND_CPU_STATE structure suitable for the initial state of a processor,
 * whereas taskRegsInit only needs to initialize a REG_SET structure
 * for the initial state of a vxWorks task.
 *
 * RETURNS: OK or ERROR if any failure.
 *
 */

STATUS vxCpuStateInit
    (
    unsigned int cpu,
    WIND_CPU_STATE *cpuState,
    char *stackBase,
    FUNCPTR entry
    )
    {
    TSS *newTss;
    GDT *newGdt;

    GDTPTR gDtp;
    INT32 nGdtEntries, nGdtBytes;

    if ((cpu < 1) || (cpu > (sysCpuAvailableGet() - 1)))
        return (ERROR);

    if ((cpuState == NULL) || (entry== NULL) || (stackBase == NULL))
        return (ERROR);

    bzero ((char *)cpuState, sizeof(WIND_CPU_STATE));

    /* establish pointers to gloabal descriptor table & task state segment
     * TSS is assigned a cpu unique structure...
     */

    /* copy the global descriptor table from RAM/ROM to RAM */

    /* Get the Global Data Table Descriptor */

    vxGdtrGet ( (long long int *)&gDtp );

    /* Extract the number of bytes */

    nGdtBytes = (INT32)gDtp.wGdtr[0];

    /* and calculate the number of entries */

    nGdtEntries = (nGdtBytes + 1 ) / sizeof(GDT);

    newGdt = (GDT *) malloc (nGdtEntries * sizeof (GDT));

    if (newGdt == NULL)
      return (ERROR);

    bcopy ((char *)(&sysGdt), (char *)newGdt, (int)(nGdtEntries * sizeof (GDT)));

    _WRS_WIND_VARS_ARCH_SET(cpu,
                            pSysGdt,
                            newGdt);

    newTss = (TSS *) malloc (sizeof (TSS));

    if (newTss == NULL)
      return (ERROR);

    bcopy ((char *)(&sysTss), (char *)newTss, (int)sizeof (TSS));

    _WRS_WIND_VARS_ARCH_SET(cpu,
                            sysTssCurrent,
                            newTss);

    _WRS_WIND_VARS_ARCH_SET(cpu,
                            vxIntStackEnabled,
                            1);

    cpuState->regs.eflags = EFLAGS_BRANDNEW;
    cpuState->regs.esp = (ULONG) stackBase;
    cpuState->regs.pc = (INSTR *)entry;

    return (OK);
    }

/***************************************************************************
 *
 * sysCpuStart - start a pentium core
 *
 * The sysCpuStart() function takes two parameters:
 * int cpu;                  /@ core number to start @/
 * WIND_CPU_STATE *cpuState; /@ pointer to a WIND_CPU_STATE structure @/
 *
 * The intent is to implement a function with the basic features of
 * vxTaskRegsInit() that sets up the regs structure, then passes the
 * cpu number and cpuState pointer to this function, which in turn extracts
 * the needed values from the cpuState structure and starts the processor
 * running...
 *
 * RETURNS:  0K - Success
 *           ERROR - Fail
 *
 * NOMANUAL
 */

STATUS sysCpuStart(int cpu, WIND_CPU_STATE *cpuState)
    {
    STATUS status = OK;          /* return value */
    INT32  ix;
    INT32  oldLevel;
    UINT32 oldResetVector;       /* warm reset vector */
    UINT8  oldShutdownCode;      /* CMOS shutdown code */
    unsigned int *tmp_stk;       /* temp stk to pass some env params */
    unsigned int *tmpPtr;        /* temp pointer */
    FUNCPTR * baseAddr;          /* new vector base address */
    UINT8 *mploApicIndexTable;

    /* entry point of AP trampoline code */

    UINT32 entryPoint = (UINT32) CPU_ENTRY_POINT;
    UINT32 scratchPoint = (UINT32) CPU_SCRATCH_POINT;
    UINT32 scratchMem = (UINT32) scratchPoint;

    (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

    /* allow access to page 0, for access to WARM_REST_VECTOR,
     * default state (VM_STATE_VALID | VM_STATE_WRITABLE | VM_STATE_CACHEABLE)
     */

    vmMap (0, (VIRT_ADDR)0, (PHYS_ADDR)0, VM_PAGE_SIZE);

    bcopy ((char *)(&sysInitCpuStartup),
                    (char *)entryPoint,
                    (int)CPU_STARTUP_SIZE);

    oldLevel = intCpuLock();               /* LOCK INTERRUPTS */

    /* Initialization of Temporary AP Scratch Memory:
     *
     *    scratchMem (scratch memory offset)  scratchPoint
     *
     *    Standard GDT Entries:
     *
     *    null descriptor                     scratchMem + 0x04
     *
     *    kernel text descriptor              scratchMem + 0x0C
     *
     *    kernel data descriptor              scratchMem + 0x14
     *
     *    exception text descriptor           scratchMem + 0x1C
     *
     *    interrupt data descriptor           scratchMem + 0x24
     *
     *    gdt limit << 16                     scratchMem + LIM_GDT_OFFSET
     *    gdt base                            scratchMem + BASE_GDT_OFFSET
     *    address of page directory           scratchMem + CR3_OFFSET
     *
     *    idt limit                           scratchMem + LIM_IDT_OFFSET
     *    idt base address                    scratchMem + BASE_IDT_OFFSET
     *
     *    initial AP stack addr               scratchMem + AP_STK_OFFSET
     */

    /* Setup Initial AP... */

    /* scratchPoint saves location of starting point for AP scratch memory,
     * APs offset based on this value for unique memory space...
     * if AP #1, this location doubles as first valid location of AP
     * scratch memory...
     */

    *((int *)(scratchPoint)) = (unsigned int)scratchMem;

   /* first valid location of scratch memory,
    * setup offset for AP specific scratch mem
    */

   tmp_stk = (unsigned int *)(scratchMem);
   tmp_stk[0] = (unsigned int)scratchMem;

   /* setup intial GDT values */

   tmpPtr = (unsigned int *) &sysGdt;

   /* place tmp_gdt in memory */

   for (ix = 0; ix < NUM_GDT_ENTRIES; ix++)
      tmp_stk[ix+1] = *tmpPtr++;

   /* (num bytes - 1) << 16 */

   *((int *)(scratchMem + LIM_GDT_OFFSET)) = (int)0x270000;
   *((int *)(scratchMem + BASE_GDT_OFFSET)) = (int)(scratchMem + 0x04);

   /* setup initial cr3 */

   *((unsigned int *)(scratchMem + CR3_OFFSET)) = vxCr3Get();

   /* setup initial IDT values */

   baseAddr = intVecBaseGet();

   /* (IDT limit) << 16 */

   *((int *)(scratchMem + LIM_IDT_OFFSET)) = (int)0x07ff0000;

   /* IDT base address */

   *((int *)(scratchMem + BASE_IDT_OFFSET)) = (int)baseAddr;

   /* initial AP Stack Address */

   *((int *)(scratchMem + AP_STK_OFFSET)) = (int)cpuState->regs.esp;

   /* set the AP entry point address in WARM_REST_VECTOR */

   oldResetVector = *(volatile UINT32 *)WARM_RESET_VECTOR;
   sysOutByte (RTC_INDEX, BIOS_SHUTDOWN_STATUS); /* selects Shutdown Status Register */
   oldShutdownCode = sysInByte (RTC_DATA); /* get BIOS Shutdown code */

   *(volatile unsigned short *)WARM_RESET_VECTOR = 0;
   *(volatile unsigned short *)(WARM_RESET_VECTOR+2) = (entryPoint>>4);

   /* initialze the BIOS shutdown code to be 0xA */

   sysOutByte (RTC_INDEX, BIOS_SHUTDOWN_STATUS); /* selects Shutdown Status Register */
   sysOutByte (RTC_DATA, 0xA);             /* set BIOS Shutdown code to 0x0A  */

   intCpuUnlock(oldLevel);                 /* UNLOCK INTERRUPTS */

   cacheFlush ((CACHE_TYPE)DATA_CACHE,
               (void *)entryPoint,
               (size_t)0x1000);         /* allow for code & scratch mem */

   /* BSP sends AP an INIT-IPI and STARTUP-IPI */

   if (ipiStartup ((UINT32) mploApicIndexTable[cpu],
                   (UINT32) entryPoint,
                   (UINT32) 2) != OK)
     {
      printf ("\nipiStartup failed: %d\n", mploApicIndexTable[cpu]);
      status = ERROR;
     }

   /* BSP delays 200usec again */

   for (ix = 0; ix < 300; ix++)            /* 300*720 ~= 216usec */
      sysDelay ();                         /* 720ns */

   oldLevel = intCpuLock();                /* LOCK INTERRUPTS */

   /* restore the WARM_REST_VECTOR and the BIOS shutdown code */

   *(volatile UINT32 *)WARM_RESET_VECTOR = oldResetVector;
   sysOutByte (RTC_INDEX, BIOS_SHUTDOWN_STATUS); /* Shutdown Status Reg */
   sysOutByte (RTC_DATA, oldShutdownCode); /* set BIOS Shutdown code */

   intCpuUnlock(oldLevel);                 /* UNLOCK INTERRUPTS */

   /* unmap the page zero for NULL pointer detection */

   vmStateSet ((VIRT_ADDR) 0x0,
               (PHYS_ADDR) 0x0,
               VM_PAGE_SIZE,
               (VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE),
               (VM_STATE_VALID_NOT  | VM_STATE_WRITABLE_NOT  | VM_STATE_CACHEABLE_NOT));

   return (status);
   }

/******************************************************************************
 *
 * sysCpuInit - AP CPU Initialization.
 *
 * This routine is the first code executed on a secondary processor after
 * startup. It is responsible for ensuring that the registers are set
 * appropriately.
 *
 * In a mapped kernel, it is also responsible for setting up the core's MMU.
 *
 * Upon completion of these tasks, the core is ready to begin accepting
 * kernel work. The address of the initial kernel code (typically
 * windCpuEntry) has been placed in sysCpuInitTable[coreNum].
 *
 * RETURNS: NONE
 */

void sysCpuInit (void)
    {
    unsigned int a = 0;
    int coreNum;
    FUNCPTR entry;
    int dummy;
    STATUS retVal = OK;

    sysInitGDT ();

#if (CPU == PENTIUM) || (CPU == PENTIUM2) || (CPU == PENTIUM3) || \
    (CPU == PENTIUM4)

    /* initialize the MSRs (Model Specific Registers) 

    pentiumMsrInit ();*/

#if (CPU != PENTIUM)

    /* enable the MTRR (Memory Type Range Registers) */

    if ((sysCpuId.featuresEdx & CPUID_MTRR) == CPUID_MTRR)
      {
      pentiumMtrrDisable ();      /* disable MTRR */
#ifdef INCLUDE_MTRR_GET
      (void) pentiumMtrrGet (&sysMtrr); /* get MTRR initialized by BIOS */
#else
      (void) pentiumMtrrSet (&sysMtrr); /* set your own MTRR */
#endif /* INCLUDE_MTRR_GET */
      pentiumMtrrEnable ();       /* enable MTRR */
      }
#endif /* (CPU != PENTIUM) */

#ifdef INCLUDE_PMC

    /* enable PMC (Performance Monitoring Counters) */

    pentiumPmcStop ();          /* stop PMC0 and PMC1 */
    pentiumPmcReset ();         /* reset PMC0 and PMC1 */
#endif /* INCLUDE_PMC */

    /* enable the MCA (Machine Check Architecture) */

    pentiumMcaEnable (TRUE);
#endif  /* (CPU == PENTIUM) || (CPU == PENTIUM[234]) */

    (*getLoApicIntrInitAP)(loApicDevID, (void *) &dummy);

    coreNum = vxCpuIndexGet();

    entry = sysCpuInitTable[coreNum];

    /* update GDT. LDT, ect. depending on configuration...
     *
     * Note: order here is important, GDT updates for RTPs
     *       must come before OSM support, if included...
     */

#if defined (INCLUDE_RTP)
    retVal = syscallArchInit ();
#endif /* INCLUDE_RTP */

    if (retVal == OK)
    {
#if defined INCLUDE_PROTECT_TASK_STACK || defined INCLUDE_PROTECT_INTERRUPT_STACK
#if defined(_WRS_OSM_INIT)
#if defined INCLUDE_PROTECT_TASK_STACK
    retVal = excOsmInit (TASK_USER_EXC_STACK_OVERFLOW_SIZE, VM_PAGE_SIZE);
#else  /* INCLUDE_PROTECT_TASK_STACK */
    retVal = excOsmInit (0, VM_PAGE_SIZE);
#endif /* INCLUDE_PROTECT_TASK_STACK */
#endif /* defined(_WRS_OSM_INIT) */
#endif  /* INCLUDE_PROTECT_TASK_STACK || INCLUDE_PROTECT_INTERRUPT_STACK */

    if ((entry != NULL) && (retVal == OK))
      {
       entry ();

       /* should be no return */
      }
    }

    for (;;)
      {
       if (!(++a % 0x10000))
         {
          sysCpuLoopCount[coreNum]++;
         }
      }
    }

/******************************************************************************
 *
 * sysCpuEnable - enable a multi core CPU
 *
 * This routine brings a CPU out of reset
 *
 * RETURNS:  OK - Success
 *           ERROR - Fail
 *
 */
STATUS sysCpuEnable(unsigned int cpuNum, WIND_CPU_STATE *cpuState)
    {
    if ((cpuNum < 1) || (cpuNum > (sysCpuAvailableGet() - 1)))
      {
        return (ERROR);
      }

    sysCpuInitTable[cpuNum] = (FUNCPTR) cpuState->regs.pc;
    return (sysCpuStart(cpuNum, cpuState));
    }

/******************************************************************************
 *
 * sysCpuRe_Enable - re-enable a multi core CPU
 *
 * This routine brings an AP CPU through a cpu reset cycle and back on line.
 *
 * RETURNS:  OK - Success
 *           Error - Fail
 *
 */

STATUS sysCpuRe_Enable(unsigned int cpuNum)
    {
    STATUS status = OK;

    if ((cpuNum < 1) || (cpuNum > (sysCpuAvailableGet() - 1)))
      {
       return (ERROR);
      }

    status = sysCpuStop ((int)cpuNum);
    status = sysCpuReset ((int)cpuNum);
    status = kernelCpuEnable (cpuNum);

    return (status);
   }

/******************************************************************************
 *
 * sysCpuDisable - disable a multi core CPU
 *
 * This routine shuts down the specified core.
 *
 * RETURNS:  OK - Success
 *           ERROR - Fail
 *
 */

STATUS sysCpuDisable(int cpuNum)
    {
    if ((cpuNum < 1) || (cpuNum > (sysCpuAvailableGet() - 1)))
      {
       return (ERROR);
      }

    return (sysCpuStop(cpuNum));
    }

/***************************************************************************
 *
 * sysCpuStop - stop a Pentium core, for now, it is no longer available
 *              for use
 *
 * The sysCpuStop() function takes one parameter:
 * int cpu;              /@ core number to stop @/
 *
 * RETURNS: OK
 *
 * NOMANUAL
 */

STATUS sysCpuStop(int cpu)
{
 STATUS status = OK;
 int key;   /* prevent task migration */
 UINT8 *mploApicIndexTable;

 taskCpuLock();       /* if not in interrupt context, taskCpuLock */

 key = intCpuLock ();   /* prevent task migration */

 (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

 /* BSP sends AP the shutdown IPI */

 CPUSET_ATOMICCLR (vxCpuEnabled, cpu);
 status = ipiShutdown ((UINT32) mploApicIndexTable[cpu], INT_NUM_LOAPIC_IPI + 0);

 intCpuUnlock (key);

 taskCpuUnlock();     /* if not in interrupt context, taskCpuUnlock */

 return (status);
}

/* Stop all Aplication Processors (APs) */
/* ---can only run this routine from boot strap processor (BSP) */

STATUS sysCpuStop_APs (void)
{
 STATUS status = OK;
 int i;
 int key;   /* prevent task migration */
 UINT8 *mploApicIndexTable;
 int numCpus = vxCpuConfiguredGet();

 taskCpuLock();       /* if not in interrupt context, taskCpuLock */

 key = intCpuLock ();   /* prevent task migration */

 (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

 /* Skip BSP, i == 0 */

 for (i=1; i < numCpus; i++)
    {
     /* BSP sends AP the shutdown IPI */

     CPUSET_ATOMICCLR (vxCpuEnabled, i);
     status = ipiShutdown ((UINT32) mploApicIndexTable[i], INT_NUM_LOAPIC_IPI + 0);
    }

 intCpuUnlock (key);

 taskCpuUnlock();     /* if not in interrupt context, taskCpuUnlock */

 return (status);
}

/* Stop all APs but the one I'm running on, (All but me...) */

STATUS sysCpuStop_ABM (void)
{
 STATUS status = OK;
 int i, skipProc;
 int key;   /* prevent task migration */
 UINT8 *mploApicIndexTable;
 int numCpus = vxCpuConfiguredGet();

 taskCpuLock();       /* if not in interrupt context, taskCpuLock */

 key = intCpuLock ();   /* prevent task migration */

 (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

 skipProc = vxCpuIndexGet ();

 for (i=1; i < numCpus; i++)
    {
     if (i != skipProc)
       {
        /* sends AP the shutdown IPI */

        CPUSET_ATOMICCLR (vxCpuEnabled, i);
        status = ipiShutdown ((UINT32) mploApicIndexTable[i], INT_NUM_LOAPIC_IPI + 0);
       }
    }

 intCpuUnlock (key);

 taskCpuUnlock();     /* if not in interrupt context, taskCpuUnlock */

 return (status);
}

/***************************************************************************
 *
 * sysCpuReset - Reset a Pentium core
 *
 * Places the specified Application Processor (AP) into the
 * INIT reset state, i.e. wait-for-SIPI state.
 *
 * The sysCpuReset() function takes one parameter:
 * int cpu;              /@ core number to stop @/
 *
 * RETURNS: OK
 *
 * NOMANUAL
 */

STATUS sysCpuReset(int cpu)
{
 STATUS status = OK;
 int key;   /* prevent task migration */
 UINT8 *mploApicIndexTable;

 taskCpuLock();       /* if not in interrupt context, taskCpuLock */

 key = intCpuLock ();   /* prevent task migration */

 (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

 /* sends AP the INIT IPI */

 CPUSET_ATOMICCLR (vxCpuEnabled, cpu);
 status = ipiReset ((UINT32) mploApicIndexTable[cpu]);

 intCpuUnlock (key);

 taskCpuUnlock();     /* if not in interrupt context, taskCpuUnlock */

 return (status);
}

/* Reset all Aplication Processors (APs) */
/* ---can only run this routine from BSP */

STATUS sysCpuReset_APs (void)
{
 STATUS status = OK;
 int i;
 int key;   /* prevent task migration */
 UINT8 *mploApicIndexTable;
 int numCpus = vxCpuConfiguredGet();

 taskCpuLock();       /* if not in interrupt context, taskCpuLock */

 key = intCpuLock ();   /* prevent task migration */

 (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

 /* Skip BSP, i == 0 */

 for (i=1; i < numCpus; i++)
    {
     /* BSP sends AP the INIT IPI */

     CPUSET_ATOMICCLR (vxCpuEnabled, i);
     status = ipiReset ((UINT32) mploApicIndexTable[i]);
    }

 intCpuUnlock (key);

 taskCpuUnlock();     /* if not in interrupt context, taskCpuUnlock */

 return (status);
}

/* Reset all APs but the one I'm running on, (All but me...) */

STATUS sysCpuReset_ABM (void)
{
 STATUS status = OK;
 int i, skipProc;
 int key;   /* prevent task migration */
 UINT8 *mploApicIndexTable;
 int numCpus = vxCpuConfiguredGet();

 taskCpuLock();       /* if not in interrupt context, taskCpuLock */

 key = intCpuLock ();   /* prevent task migration */

 (*getMpApicLoIndexTable)(mpApicDevID, (void *)&mploApicIndexTable);

 skipProc = vxCpuIndexGet ();

 for (i=1; i < numCpus; i++)
    {
     if (i != skipProc)
       {
        /* sends AP the INIT IPI */

        CPUSET_ATOMICCLR (vxCpuEnabled, i);
        status = ipiReset ((UINT32) mploApicIndexTable[i]);
       }
    }

 intCpuUnlock (key);

 taskCpuUnlock();     /* if not in interrupt context, taskCpuUnlock */

 return (status);
}
#endif

/**************************************************************************
*
* sysIchAtaInit - initialize the ATA driver external functions
*
* This routine initializes function pointers for supporting DMA and also
* initializes the interrupt handler functions.
*
* RETURNS: NONE */



/* Static configuration of mpApic data table */

#if defined (VIRTUAL_WIRE_MODE) || defined (SYMMETRIC_IO_MODE)

/* Static configuration table for mpApicData structure,
 * allows for manual configuration of mpApic driver.
 *
 * One must be very careful when manually configuring Apics,
 * incorrect data will cause catastrophic error, i.e. BSP
 * failing to boot properly.
 *
 * The data here is dependent on the number of cores involved,
 * interrupt routing tables, basically the general configuration
 * of your specific hardware.
 *
 * The example here is for a pcPentium4 Allagash using and FEI device
 * in the 2nd pci-x slot.
 *
 * Access to this capability is obtained by setting "mpBootOp"
 * in hwconf.c to USR_MP_STRUCT.
 */

static UINT32 staticMpApicData[] =
{
/* instance pointer */
0x00000000,

/* mem location of MP_APIC_DATA */
0x00102000,

/* size of MP_APIC_DATA */
0x000001a4,

/* NONE/MP/ACPI/USR boot structure used, */
/* if using this you are USR defined (3) */
0x00000003,

/* MP Floating Pointer Structure */
0x5f504d5f, 0x000fb4a0, 0x003d0401,

/* MP Configuration Table Header */
0x00000000, 0x504d4350, 0x3704018c, 0x45544e49,
0x2020204c, 0x444e494c, 0x55484e45, 0x20545352,
0x00000000, 0x00260000, 0xfee00000, 0x006c007c,

/* def Local APIC addr */
0xfee00000,

/* number of IO APICs (MP Table) */
0x00000002,

/* mpApicAddrTable ---logical io apic id to address mapping */
0x001021a4,

/* mem location of mpApicAddrTable */
0x001021a4,

/* size of mpApicAddrTable */
0x00000008,

/* mpApicLogicalTable ---recorded id mapping */
0x001021ac,

/* mem location of mpApicLogicalTable */
0x001021ac,

/* size of mpApicLogicalTable */
0x00000002,

/* number of io interrupts (MP Table) */
0x00000017,

/* number of local interrupts (MP Table) */
0x00000002,

/* mpApicInterruptTable ---interrupt routing table */
0x001021ae,

/* mem location of mpApicInterruptTable */
0x001021ae,

/* size of mpApicInterruptTable */
0x000000c8,

/* number of buses (MP Table) */
0x00000007,

/* mpApicBusTable ---bus routing table */
0x00102276,

/* mem location of mpApicBusTable */
0x00102276,

/* size of mpApicBusTable */
0x00000038,

/* mploApicIndexTable ---loApic Id translation */
0x001022ae,

/* mem location of mploApicIndexTable */
0x001022ae,

/* size of mploApicIndexTable */
0x00000004,

/* mpCpuIndexTable ---cpu Id translation */
0x00000100, 0x03020000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000,

/* CPU counter */
0x00000004,

/* Boot Strap Processor localApicId */
0x00000000
};

static UINT32 staticMpApicAddrTable[] =
{
/* mpApicAddrTable ---logical io apic id to address mapping */
0xfec00000, 0xfec10000
};

static UINT8 staticMpApicLogicalTable[] =
{
/* mpApicLogicalTable ---recorded id mapping */
0x08, 0x09
};

static UINT32 staticMpApicInterruptTable[] =
{
/* mpApicInterruptTable ---interrupt routing table */
0x20080303, 0x00080006, 0x00000003, 0x01080106,
0x00000003, 0x02080006, 0x00000003, 0x03080306,
0x00000003, 0x04080406, 0x00000003, 0x05080506,
0x00000003, 0x06080606, 0x00050003, 0x08080806,
0x00000003, 0x09080906, 0x00000003, 0x0b080b06,
0x00000003, 0x0c080c06, 0x00000003, 0x0d080d06,
0x00000003, 0x0e080e06, 0x00000003, 0x0f080f06,
0x000f0003, 0x10080800, 0x000f0003, 0x10081000,
0x000f0003, 0x10081800, 0x000f0003, 0x12087c00,
0x000f0003, 0x11087d00, 0x000f0003, 0x10087400,
0x000f0003, 0x13087500, 0x000f0003, 0x11080405,
0x000f0003, 0x01090804, 0x00000304, 0x00ff0000,
0x00000104, 0x01ff0000
};

static UINT32 staticMpApicBusTable[] =
{
/* mpApicBusTable ---bus routing table */
0x00014350, 0x20492020, 0x01014350, 0x20492020,
0x02014350, 0x20492020, 0x03014350, 0x20492020,
0x04014350, 0x20492020, 0x05014350, 0x20492020,
0x06015349, 0x20412020
};

static UINT8 staticMploApicIndexTable[] =
{
/* mploApicIndexTable ---loApic Id translation */
0x00, 0x01, 0x6, 0x7
};

void sysStaticMpApicDataGet
    (
    MP_APIC_DATA *pMpApicTable
    )
    {
    INT32 oldLevel = intCpuLock();  /* LOCK INTERRUPTS */

    /* initialize the memory allocated */

    bzero((char *)pMpApicTable, sizeof(MP_APIC_DATA));

    /* mpApicData structure - structure holding mpApic details retrieved from
     *                        BIOS/ACPI/or USER defined methods.
     */

    bcopy ((char *) staticMpApicData,
           (char *) pMpApicTable,
           (int) sizeof (MP_APIC_DATA));

    /* logical io apic id to address mapping */

    bcopy ((char *) staticMpApicAddrTable,
           (char *) pMpApicTable->mpApicAtLoc,
           (int) pMpApicTable->mpApicAtSize);

    /* recorded id mapping */

    bcopy ((char *) staticMpApicLogicalTable,
           (char *) pMpApicTable->mpApicLtLoc,
           (int) pMpApicTable->mpApicLtSize);

    /* interrupt routing table */

    bcopy ((char *) staticMpApicInterruptTable,
           (char *) pMpApicTable->mpApicItLoc,
           (int) pMpApicTable->mpApicItSize);

    /* bus routing table */

    bcopy ((char *) staticMpApicBusTable,
           (char *) pMpApicTable->mpApicBtLoc,
           (int) pMpApicTable->mpApicBtSize);

    /* loApic Id translation */

    bcopy ((char *) staticMploApicIndexTable,
           (char *) pMpApicTable->mpApicLaLoc,
           (int) pMpApicTable->mpApicLaSize);

    intCpuUnlock(oldLevel);         /* UNLOCK INTERRUPTS */
    }

#endif  /* defined (VIRTUAL_WIRE_MODE) || defined (SYMMETRIC_IO_MODE) */

