/* hwconf.c - Hardware configuration support module */

/*
 * Copyright (c) 2005-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02k,21sep09,sem  Fix WIND00174100
02j,26jun09,h_w  remove MCB, MOB and VxBus references for MIPC
02h,15apr09,dcc  incremented number of default MIPC hcfResource structures
02g,11mar09,jl   add support for com3 and com4 (WIND144311)
02f,05jan09,dcc  cleaned RAZOR to WRHV prefixes.
02e,03dec08,dcc  added rx_context member to mobVbRes[].
02d,19nov08,dcc  added bus_num member to MCB peer devices
02c,30oct08,to   merge WR hypervisor guest OS support
02c,28apr09,rec  guest Os merge from vxWorks 6.7.0
02b,21nov08,scm  multiple IO Apic support mods...
02a,29aug08,kab  Change _WRS_VX_SMP to _WRS_CONFIG_SMP
01z,30may08,scm  TESTING...
01y,29apr08,scm  WIND00103470 - SMP/SYMMETRIC_IO_MODE warm re-boot support.
01x,12oct07,h_k  changed maxBusSet number to PCI_MAX_BUS from 0.
01w,28sep07,scm  WIND00105939.
01v,12sep07,pmr  include keyboard, mouse, and video resources for WindML.
01u,07sep07,ami  entries added for USB Support
01t,23aug07,pmr  DMA init for Intel ICH Storage
01s,22aug07,pmr  VxBus ATA
01r,30jul07,scm  SMP TIMESTAMP work...
01q,18jul07,tor  VxBus NvRam support
01p,15jul07,tor  dynamic intr support
01o,21jun07,tor  prelim integrate intCtlr with VxBus interrupt routing
01n,19jun07,h_k  added symmetricIoMode and virtualWireMode.
01m,14jun07,dtr  Import sysPciPirqEnable function.
01l,25may07,h_k  added parameters for PCI.
01k,23may07,dlk  Use INT_NUM_IOAPIC_IRQ2 rather than INT_NUM_IRQ0
                 for i8253 timer 0 in SYMMETRIC_IO_MODE.
01j,23mar07,scm  create hcfResource array for local and io Apics...
01i,05mar07,dtr  Do not auto config PCI by default.
01h,05mar07,pdg  added timer support
01g,02mar07,pmr  Add VxBus PC Console
01g,28feb07,dtr  Support latest vxBus PCI Autoconfog.
01f,17jan07,wap  Add NE2000 VxBus END driver
01e,24Oct06,tor  added kbd & mouse support for WindML
01d,14dec05,pdg  added "clkFreq" resource to uart devices
01c,09nov05,mdo  Add parameter system table
01b,26oct05,mdo  Add bspSerialClkFrequencyGet needed for the uart on the PLB
01a,29sep05,mdo  Fix gnu warnings
*/


/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>

#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>
#include <hwif/vxbus/vxbPlbLib.h>
#include <hwif/vxbus/vxbPciLib.h>
#include <hwif/vxbus/vxbIntrCtlr.h>
#include <hwif/util/vxbParamSys.h>
#include <hwif/vxbus/hwConf.h>
#include <hwif/util/vxbNonVol.h>

#ifdef INCLUDE_USB
extern UINT32 usbMemToPci (void * pAddr);
extern void * usbPciToMem (UINT32 addr);
#endif

#include "config.h"

#include "../src/hwif/h/console/pcConsole.h"

#if defined (VIRTUAL_WIRE_MODE) || defined (SYMMETRIC_IO_MODE)
#include <hwif/intCtlr/vxbMpApic.h>
#endif /* VIRTUAL_WIRE_MODE || SYMMETRIC_IO_MODE */

IMPORT VOID sysPciPirqEnable (BOOL);

#define PCI_CLK_FREQ 1843200
#ifndef PCI_MEM_ADRS
    #define PCI_MEM_ADRS    0x20000000
    #define PCI_MEM_SIZE    0x00010000
#endif /* PCI_MEM_ADRS */

#ifndef PCI_MEMIO_ADRS
    #define PCI_MEMIO_ADRS  0x20010000
    #define PCI_MEMIO_SIZE  0x1fff0000
#endif /* PCI_MEMIO_ADRS */

#ifndef PCI_ISA_IO_ADRS
    #define PCI_ISA_IO_ADRS 0x40000000
    #define PCI_ISA_IO_SIZE 0x60000000
#endif /* PCI_ISA_IO_ADRS */

#ifndef PCI_IO_ADRS
    #define PCI_IO_ADRS 0xa0000000
    #define PCI_IO_SIZE 0x5ff80000
#endif /* PCI_IO_ADRS */

#if defined (DRV_TIMER_MC146818)
#define MC146818_CLK_FREQ	4194304	
#endif /* DRV_TIMER_MC146818 */

#if defined (DRV_TIMER_IA_TIMESTAMP)

/* NOTE: Can only set timestamp frequency for UP images using
 * the TSC, SMP images use HPET...
 * 
 * Values greater than 130000000, and TSC frequency calculation 
 * begin to drift far from requested frequency.
 */

#ifndef _WRS_CONFIG_SMP
#define IA_TIMESTAMP_CLK_FREQ	124974000 
#else
/* NOTE: With HPET the counter clock period is a fixed constsant held in the
 * HPET's General Capabilities and ID Register. The frequency is calculated
 * f = 1/T, so f = 1/(COUNTER_CLK_PERIOD * 10^-15), must convert
 * femptoseconds to seconds...
 */

#define IA_TIMESTAMP_CLK_FREQ	14242000  
#endif
#endif

#if defined (_WRS_CONFIG_WRHV_GUEST)
struct hcfResource vIoApicResources[] = {
    { "regBase",   HCF_RES_INT, {(void *)ERROR} },
};
#define vIoApicNum NELEMENTS(vIoApicResources)
#endif /* _WRS_CONFIG_WRHV_GUEST */

#ifdef INCLUDE_NE2000_VXB_END
const struct hcfResource ne2000Resources[] = {
        { "regBase", HCF_RES_INT, {(void *)IO_ADRS_ENE} },
        { "intr", HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_ENE))} },
        { "intrLevel", HCF_RES_INT, {(void *)INT_LVL_ENE} },
    };
#define ne2000Num NELEMENTS(ne2000Resources)
#endif

/* vxBus resource files for onboard UARTS */

const struct hcfResource pentiumi82501Resources[] =
    {
        { "regBase",     HCF_RES_INT, {(void *)COM1_BASE_ADR} },
        { "irq",         HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_COM1))} },
        { "regInterval", HCF_RES_INT, {(void *)UART_REG_ADDR_INTERVAL} },
        { "irqLevel",    HCF_RES_INT, {(void *)COM1_INT_LVL} },
        { "clkFreq",     HCF_RES_INT, {(void *)PCI_CLK_FREQ} },
        { "fifoLen",     HCF_RES_INT, {(void *)32} }
    };
#define pentiumi82501Num NELEMENTS(pentiumi82501Resources)

const struct hcfResource pentiumi82502Resources[] =
    {
        { "regBase",     HCF_RES_INT, {(void *)COM2_BASE_ADR} },
        { "irq",         HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_COM2))} },
        { "regInterval", HCF_RES_INT, {(void *)UART_REG_ADDR_INTERVAL} },
        { "irqLevel",    HCF_RES_INT, {(void *)COM2_INT_LVL} },
        { "clkFreq",     HCF_RES_INT, {(void *)PCI_CLK_FREQ} },
        { "fifoLen",     HCF_RES_INT, {(void *)32} }
    };
#define pentiumi82502Num NELEMENTS(pentiumi82502Resources)

const struct hcfResource pentiumi82503Resources[] = 
    {
        { "regBase",     HCF_RES_INT, {(void *)COM3_BASE_ADR} },
        { "irq",         HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_COM3))} },
        { "regInterval", HCF_RES_INT, {(void *)UART_REG_ADDR_INTERVAL} },
        { "irqLevel",    HCF_RES_INT, {(void *)COM3_INT_LVL} },
        { "clkFreq",	 HCF_RES_INT, {(void *)PCI_CLK_FREQ} }
    };
#define pentiumi82503Num NELEMENTS(pentiumi82503Resources)

const struct hcfResource pentiumi82504Resources[] = 
    {
        { "regBase",     HCF_RES_INT, {(void *)COM4_BASE_ADR} },
        { "irq",         HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_COM4))} },
        { "regInterval", HCF_RES_INT, {(void *)UART_REG_ADDR_INTERVAL} },
        { "irqLevel",    HCF_RES_INT, {(void *)COM4_INT_LVL} },
        { "clkFreq",	 HCF_RES_INT, {(void *)PCI_CLK_FREQ} }
    };
#define pentiumi82504Num NELEMENTS(pentiumi82504Resources)

#if defined (INCLUDE_PC_CONSOLE) || defined (INCLUDE_WINDML)
/* keyboard Controller 8042 */

const struct hcfResource pentiumi8042KbdResources[] =
    {
        { "regBase",     HCF_RES_INT, {(void *)DATA_8042} },
        { "irq",         HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_KBD))} },
        { "regInterval", HCF_RES_INT, {(void *)4} }, 
        { "irqLevel",    HCF_RES_INT, {(void *)KBD_INT_LVL} },
	{ "mode",	 HCF_RES_INT, {(void *)KEYBRD_MODE} }
    };
#define pentiumi8042KbdNum NELEMENTS(pentiumi8042KbdResources)

const struct hcfResource pentiumi8042MseResources[] =
    {
        { "regBase",     HCF_RES_INT, {(void *)DATA_8042} },
        { "irq",         HCF_RES_INT, {(void *)(INUM_TO_IVEC(INT_NUM_MSE))} },
        { "regInterval", HCF_RES_INT, {(void *)4} },
        { "irqLevel",    HCF_RES_INT, {(void *)MSE_INT_LVL} }
    };
#define pentiumi8042MseNum NELEMENTS(pentiumi8042MseResources)

/* VGA card */

const struct hcfResource pentiumM6845VgaResources[] =
    {
        { "regBase",     HCF_RES_INT, {(void *) CTRL_SEL_REG} },
        { "memBase",     HCF_RES_INT, {(void *) CTRL_MEM_BASE} },
        { "colorMode",   HCF_RES_INT, {(void *) COLOR_MODE} },
        { "colorSetting",HCF_RES_INT, {(void *) DEFAULT_ATR} },
    };
#define pentiumM6845VgaNum NELEMENTS(pentiumM6845VgaResources)
#endif  /* INCLUDE_PC_CONSOLE || INCLUDE_WINDML */

const struct hcfResource pentiumPci0Resources[] = 
    {

    { "regBase", HCF_RES_INT, {(void *)0x00} },
    { "mem32Addr", HCF_RES_ADDR, { (void *)PCI_MEM_ADRS } },
    { "mem32Size", HCF_RES_INT, { (void *)PCI_MEM_SIZE } },
    { "memIo32Addr", HCF_RES_ADDR, { (void *)PCI_MEMIO_ADRS } },
    { "memIo32Size", HCF_RES_INT, { (void *)PCI_MEMIO_SIZE } },
    { "io32Addr", HCF_RES_ADDR, { (void *)PCI_IO_ADRS } },
    { "io32Size", HCF_RES_INT, { (void *)PCI_IO_SIZE } }, 
    { "io16Addr", HCF_RES_ADDR, { (void *)PCI_ISA_IO_ADRS } },
    { "io16Size", HCF_RES_INT, { (void *)PCI_ISA_IO_SIZE } }, 
    { "fbbEnable", HCF_RES_INT, { (void *)TRUE } },
    { "cacheSize", HCF_RES_INT, { (void *)(_CACHE_ALIGN_SIZE / 4) } }, 
    { "autoIntRouteSet", HCF_RES_INT, { (void *)TRUE } }, 

    /* non vxbPciAutoConfig() values */
    { "pciConfigMechanism",HCF_RES_INT, { (void *)(1)}},
    { "maxBusSet", HCF_RES_INT, { (void *)PCI_MAX_BUS } },
    { "autoConfig",HCF_RES_INT, { (void *)(FALSE)}},

#if defined (SYMMETRIC_IO_MODE)
    { "funcPirqEnable", HCF_RES_ADDR, { (void *)sysPciPirqEnable}},
#endif	/* SYMMETRIC_IO_MODE */

#ifdef INCLUDE_USB
    { "cpuToBus", HCF_RES_ADDR, { (void *) usbMemToPci}},
    { "busToCpu", HCF_RES_ADDR, { (void *) usbPciToMem}},
#endif

    { "vmStateMaskForAll",HCF_RES_INT, { (void *)(VM_STATE_MASK_FOR_ALL)}},
    { "vmStateForPci",HCF_RES_INT, { (void *)(VM_STATE_FOR_PCI)}}

    };
#define pentiumPci0Num NELEMENTS(pentiumPci0Resources)

#if defined (DRV_TIMER_I8253)
struct hcfResource i8253DevResources[] = {
    { "regBase", HCF_RES_INT, {(void *)PIT_BASE_ADR} },
    { "clkFreq", HCF_RES_INT, {(void *)PIT_CLOCK} },
#if defined (SYMMETRIC_IO_MODE)
    { "intr0", HCF_RES_INT, {(void *)INUM_TO_IVEC (INT_NUM_IOAPIC_IRQ2)}},
#else
    { "intr0", HCF_RES_INT, {(void *)INUM_TO_IVEC (INT_NUM_IRQ0)}},
#endif
    { "intr0Level", HCF_RES_INT, {(void *)PIT0_INT_LVL}},
    { "clkRateMin", HCF_RES_INT, {(void *)SYS_CLK_RATE_MIN} },
    { "clkRateMax", HCF_RES_INT, {(void *)SYS_CLK_RATE_MAX} },
    { "regInterval",HCF_RES_INT, {(void *)PIT_REG_ADDR_INTERVAL} }
};

#define i8253DevNum NELEMENTS(i8253DevResources)
#endif /* DRV_TIMER_I8253 */

#if defined (DRV_TIMER_LOAPIC)
struct hcfResource loApicTimerResources[] = {
    { "regBase",   HCF_RES_INT, {(void *)(LOAPIC_BASE)} },
    { "intr",      HCF_RES_INT, {(void *)INUM_TO_IVEC (INT_NUM_LOAPIC_TIMER)}},
    { "intrLevel", HCF_RES_INT, {(void *)INT_NUM_LOAPIC_TIMER}},
    { "clkFreq",   HCF_RES_INT, {(void *)APIC_TIMER_CLOCK_HZ} },
    { "clkRateMin",HCF_RES_INT, {(void *)SYS_CLK_RATE_MIN} },
    { "clkRateMax",HCF_RES_INT, {(void *)SYS_CLK_RATE_MAX} },
};

#define loApicTimerDevNum NELEMENTS(loApicTimerResources)
#endif /* DRV_TIMER_LOAPIC */

#if defined (DRV_TIMER_IA_TIMESTAMP)
struct hcfResource iaTimestampResources[] = {
    { "regBase",   HCF_RES_INT, {(void *)0} },
    { "clkFreq",   HCF_RES_INT, {(void *)IA_TIMESTAMP_CLK_FREQ} },
#ifdef _WRS_CONFIG_SMP
    { "clkRateMin", HCF_RES_INT, {(void *)IA_TIMESTAMP_CLK_FREQ} },
    { "clkRateMax", HCF_RES_INT, {(void *)IA_TIMESTAMP_CLK_FREQ} }
#else
    { "clkRateMin", HCF_RES_INT, {(void *)1000} },
    { "clkRateMax", HCF_RES_INT, {(void *)IA_TIMESTAMP_CLK_FREQ} }
#endif
};

#define iaTimestampNum NELEMENTS(iaTimestampResources)
#endif /* DRV_TIMER_IA_TIMESTAMP */

#if defined (DRV_TIMER_MC146818)
struct hcfResource mc146818DevResources[] = {
    { "regBase", HCF_RES_INT, {(void *)RTC_INDEX} },
    { "irq", HCF_RES_INT, {(void *)INUM_TO_IVEC(INT_NUM_RTC)}},
    { "irqLevel", HCF_RES_INT, {(void *)RTC_INT_LVL}},
    { "clkFreq", HCF_RES_INT, {(void *)MC146818_CLK_FREQ} },
    { "clkRateMin", HCF_RES_INT, {(void *)2} },
    { "clkRateMax", HCF_RES_INT, {(void *)8192} },
};

#define mc146818DevNum NELEMENTS(mc146818DevResources)
#endif /* DRV_TIMER_MC146818 */

#if defined (VIRTUAL_WIRE_MODE) || defined (SYMMETRIC_IO_MODE) 
struct hcfResource mpApicResources[] = {
    { "regBase",   HCF_RES_INT, {(void *)ERROR} },
    { "mpBootOp", HCF_RES_INT, {(void *)MP_MP_STRUCT} },
    { "mpDataLoc", HCF_RES_INT, {(void *)MPAPIC_DATA_START} },
    { "mpDataGet", HCF_RES_ADDR, { (void *)sysStaticMpApicDataGet} },
#if defined (SYMMETRIC_IO_MODE)
    { "symmetricIoMode",   HCF_RES_INT, {(void *)TRUE} },
#else
    { "symmetricIoMode",   HCF_RES_INT, {(void *)FALSE} },
#endif  /* SYMMETRIC_IO_MODE */
};
#define mpApicNum NELEMENTS(mpApicResources)

LOCAL const struct intrCtlrInputs loApicInputs[] = {
    { VXB_INTR_DYNAMIC, "yn", 0, 0 },
};

LOCAL const struct intrCtlrCpu loApicCpu[] = {
    { COM2_INT_LVL, 1 },
};

LOCAL struct hcfResource loApicIntrResources[] = {
    { "regBase",           HCF_RES_INT,  {(void *)ERROR} },
    { "input",	           HCF_RES_ADDR, {(void *)&loApicInputs[0] } },
    { "inputTableSize",    HCF_RES_INT,  {(void *)NELEMENTS(loApicInputs) } },
    { "cpuRoute",          HCF_RES_ADDR, {(void *)&loApicCpu[0] } },
    { "cpuRouteTableSize", HCF_RES_INT,  {(void *)NELEMENTS(loApicCpu) } },
#if defined (SYMMETRIC_IO_MODE)
    { "symmetricIoMode",   HCF_RES_INT, {(void *)TRUE} },
#else
    { "symmetricIoMode",   HCF_RES_INT, {(void *)FALSE} },
#endif  /* SYMMETRIC_IO_MODE */
#if defined (VIRTUAL_WIRE_MODE)
    { "virtualWireMode",   HCF_RES_INT, {(void *)TRUE} },
#else
    { "virtualWireMode",   HCF_RES_INT, {(void *)FALSE} },
#endif  /* VIRTUAL_WIRE_MODE */
}; 
#define loApicIntrNum NELEMENTS(loApicIntrResources)
#endif /* VIRTUAL_WIRE_MODE || SYMMETRIC_IO_MODE */

#if defined (SYMMETRIC_IO_MODE) 
/* May use the same info here for multiple IO Apics since
 * everything is determined via mpApic self-discovery during
 * initialization.
 */

struct hcfResource ioApicIntr0Resources[] = {
    { "regBase", HCF_RES_INT, {(void *)ERROR} },
};

#define ioApicIntr0Num NELEMENTS(ioApicIntr0Resources)
#endif /* SYMMETRIC_IO_MODE */

NVRAM_SEGMENT flNvRam0Segments[] = {
    { "bootline", 0, NV_BOOT_OFFSET, BOOT_LINE_SIZE },
};

const struct hcfResource flNvRam0Resources[] = {
    { "regBase",        HCF_RES_INT, { (void *)-1 } },
    { "segments",       HCF_RES_ADDR, { (void *)&flNvRam0Segments[0] } },
    { "numSegments",	HCF_RES_INT, { (void *)NELEMENTS(flNvRam0Segments) } },
    { "size",           HCF_RES_INT, { (void *)NV_RAM_SIZE } },
    { "fileName",       HCF_RES_STRING, { (void *)"/fd0/nvram.txt" } },
};
#define flNvRam0Num NELEMENTS(flNvRam0Resources)

#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
IMPORT ATA_RESOURCE ataResources[ATA_MAX_CTRLS];
IMPORT ATA_TYPE ataTypes [ATA_MAX_CTRLS][ATA_MAX_DRIVES];
IMPORT void sysIchAtaInit (ATA_CTRL *);

const struct hcfResource ata0Resources[] = {
    { "ataResources",   HCF_RES_ADDR, { (void *)&ataResources[0] } },
    { "ataTypes",       HCF_RES_ADDR, { (void *)&ataTypes[0][0] } },
    { "dev00",          HCF_RES_STRING, { (void *)"/ata0a" } },
    { "sysAtaInit",     HCF_RES_ADDR, { (void *)sysIchAtaInit } },
};
#define ata0Num NELEMENTS(ata0Resources)
#endif /* INCLUDE_DRV_STORAGE_INTEL_ICH */
#ifdef _WRS_CONFIG_WRHV_GUEST
struct hcfDevice hcfDeviceList[] = {
#ifdef DRV_SIO_NS16550
    { "ns16550", 0, VXB_BUSID_PLB, 0, pentiumi82501Num, pentiumi82501Resources },
#endif
    { "vIoApicIntr", 0, VXB_BUSID_PLB, 0, vIoApicNum, vIoApicResources},
#else
const struct hcfDevice hcfDeviceList[] = {
#ifdef DRV_SIO_NS16550
    { "ns16550", 0, VXB_BUSID_PLB, 0, pentiumi82501Num, pentiumi82501Resources },
    { "ns16550", 1, VXB_BUSID_PLB, 0, pentiumi82502Num, pentiumi82502Resources },
    { "ns16550", 2, VXB_BUSID_PLB, 0, pentiumi82503Num, pentiumi82503Resources },
    { "ns16550", 3, VXB_BUSID_PLB, 0, pentiumi82504Num, pentiumi82504Resources },
#endif /* DRV_SIO_NS16550 */
#endif /*_WRS_CONFIG_WRHV_GUEST */
#if defined (VIRTUAL_WIRE_MODE) || defined (SYMMETRIC_IO_MODE) 
    { "mpApic", 0, VXB_BUSID_PLB, 0, mpApicNum, mpApicResources },
    { "loApicIntr", 0, VXB_BUSID_PLB, 0, loApicIntrNum, loApicIntrResources },
#if defined (SYMMETRIC_IO_MODE) 
    /* The majority of boards only have 2, but just incase... */
    { "ioApicIntr", 0, VXB_BUSID_PLB, 0, ioApicIntr0Num, ioApicIntr0Resources },
    { "ioApicIntr", 1, VXB_BUSID_PLB, 0, ioApicIntr0Num, ioApicIntr0Resources },
    { "ioApicIntr", 2, VXB_BUSID_PLB, 0, ioApicIntr0Num, ioApicIntr0Resources },
    { "ioApicIntr", 3, VXB_BUSID_PLB, 0, ioApicIntr0Num, ioApicIntr0Resources },
#endif /* SYMMETRIC_IO_MODE */
#endif /* VIRTUAL_WIRE_MODE || SYMMETRIC_IO_MODE */
#ifdef INCLUDE_NE2000_VXB_END
    { "ene", 0, VXB_BUSID_PLB, 0, ne2000Num, ne2000Resources },
#endif
    { "pentiumPci", 0, VXB_BUSID_NEXUS, 0, pentiumPci0Num, pentiumPci0Resources },
#if defined (INCLUDE_PC_CONSOLE) || defined (INCLUDE_WINDML)
    { "i8042Kbd", 0, VXB_BUSID_PLB, 0, pentiumi8042KbdNum, pentiumi8042KbdResources },
    { "i8042Mse", 0, VXB_BUSID_PLB, 0, pentiumi8042MseNum, pentiumi8042MseResources },
    { "m6845Vga", 0, VXB_BUSID_PLB, 0, pentiumM6845VgaNum, pentiumM6845VgaResources },
#endif /* INCLUDE_PC_CONSOLE || INCLUDE_WINDML */
#if defined (DRV_TIMER_I8253)
    { "i8253TimerDev", 0, VXB_BUSID_PLB, 0, i8253DevNum, i8253DevResources },
#endif /* DRV_TIMER_I8253 */
#if defined (DRV_TIMER_LOAPIC)
    { "loApicTimer", 0, VXB_BUSID_PLB, 0, loApicTimerDevNum, loApicTimerResources },
#endif /* DRV_TIMER_LOAPIC */
#if defined (DRV_TIMER_IA_TIMESTAMP)
    { "iaTimestamp", 0, VXB_BUSID_PLB, 0, iaTimestampNum, iaTimestampResources },
#endif /* DRV_TIMER_IA_TIMESTAMP */
#if defined (DRV_TIMER_MC146818)
    { "mc146818Rtc", 0, VXB_BUSID_PLB, 0, mc146818DevNum, mc146818DevResources },
#endif /* DRV_TIMER_MC146818 */
    { "fileNvRam", 0, VXB_BUSID_PLB, 0, flNvRam0Num, flNvRam0Resources },
#ifdef INCLUDE_DRV_STORAGE_INTEL_ICH
    { "intelIchAta", 0, VXB_BUSID_PCI, 0, ata0Num, ata0Resources },
#endif /* INCLUDE_DRV_STORAGE_INTEL_ICH */
#ifdef _WRS_CONFIG_WRHV_GUEST
#endif /*_WRS_CONFIG_WRHV_GUEST */
};
const int hcfDeviceNum = NELEMENTS(hcfDeviceList);

VXB_INST_PARAM_OVERRIDE sysInstParamTable[] =
    {
    { NULL, 0, NULL, VXB_PARAM_END_OF_LIST, {(void *)0} }
    };
