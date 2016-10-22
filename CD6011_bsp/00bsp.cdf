/* 00bsp.cdf - BSP configuration file */

/*
 * Copyright (c) 2002, 2005-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02b,15oct08,pgh  Fix memory definitions for bootapp
02a,01dec07,mdo  CQ: WIND00110287 - Add missing components
01z,04oct07,pdg  Fix for defect WIND00105740(auxClkDefault test case failing)
01y,27sep07,rbc  Fix for WIND00087310 cleanup references to
                 INCLUDE_ADD_BOOTMEM
01x,24sep07,ami  Fix CQ:WIND00105719 (Aux Clk Issues)
01w,21sep07,rbc  Fix for WIND00105213, pull in DRV_TIMER_IA_TIMESTAMP for
                 project builds
01v,30aug07,tor  WIND00099906 aux clk
01u,06aug07,h_k  removed duplicated INCLUDE_PENTIUM_PCI definitions.
01t,26jul07,h_k  added dependency between INCLUDE_THERM_MONITOR and
                 INCLUDE_CPU_PWR_MGMT. (CQ:99505)
01s,19jul07,pee  added MP_OPTIONS to Bsp
01s,09jul07,dee  WIND00097125 - better dma support for pentium bsp
01r,28feb07,jmt  Defect 85499 - remove SELECT_IO_CONTROLLER_HUB from CDF
01q,05mar07,pdg  added vxbus timer support
01p,22jan07,scm  WIND00085499...
01o,28aug06,jmt  Add BootApp RAM Image address
01n,14jul06,jmt  Add Memory defines to support bootApp
01m,21apr06,zmm  VxBus requires INCLUDE_PENTIUM_PCI component, SPR#120277.
01l,08mar06,jmt  Add AUX_CLK_RATE parameter
01k,12oct05,mdo  Remove ns16550 configlette
01j,10oct05,mmi  Remove legacy POWER_MANAGEMENT component.
01i,20sep05,mdo  Make NAME of INCLUDE_NS16550_SIO to be more broad and not vxBus
                 specific
01h,18aug05,mdo  Fix SIO channel dependency
01g,08aug05,mdo  Change WINDBUS to VXBUS
01f,03aug05,mdo  Add vxBus Components
01e,01oct02,hdn  added DEBUG_STORE component and parameters.
01d,24sep02,hdn  added THERM_MONITOR component and parameters.
01c,12jul02,pai  Updated SYS_CLK_RATE_MAX for specific CPU types (SPR 27449).
01b,19jun02,pai  Added P6 physical address space config components.
01a,13feb02,pai  Written.
*/

/*
DESCRIPTION
This file overrides generic BSP components in comps/vxWorks/00bsp.cdf with
pcPentium4 BSP-specific versions of components and parameters defined in
the generic CDF file.
*/


/*******************************************************************************
*
* Memory definitions
*
*/

Parameter LOCAL_MEM_LOCAL_ADRS {
    NAME        Physical memory base address
    DEFAULT     0x00100000
}

Parameter RAM_HIGH_ADRS {
    NAME        Bootrom Copy region
    DEFAULT     (INCLUDE_BOOT_APP)::(0x00008000) \
                 0x00108000
}

Parameter RAM_LOW_ADRS {
    NAME        Runtime kernel load address
    DEFAULT     (INCLUDE_BOOT_RAM_IMAGE)::(0x00508000) \
                (INCLUDE_BOOT_APP)::(0x00108000) \
                0x00408000
}

/*******************************************************************************
*
* System Clock, Auxiliary Clock and Timestamp Component and Parameters
*
*/

Component INCLUDE_AUX_CLK {
    REQUIRES DRV_TIMER_MC146818
}

Component INCLUDE_TIMESTAMP {
    REQUIRES DRV_TIMER_IA_TIMESTAMP
}

Parameter SYS_CLK_RATE_MAX  {
    NAME              system clock configuration parameter
    SYNOPSIS          maximum system clock rate
    TYPE              uint
    DEFAULT           (5000)
}

Parameter SYS_CLK_RATE_MIN  {
    NAME              system clock configuration parameter
    SYNOPSIS          minimum system clock rate
    TYPE              uint
    DEFAULT           (19)
}

Parameter SYS_CLK_RATE {
    NAME              system clock configuration parameter
    SYNOPSIS          number of ticks per second
    TYPE              uint
    DEFAULT           (60)
}

Parameter AUX_CLK_RATE {
    DEFAULT         (128)
}
/*******************************************************************************
*
* Cache Configuration Parameters
*
*/
Parameter USER_D_CACHE_MODE  {
    NAME              pcPentium4 configuration parameter
    SYNOPSIS          write-back data cache mode
    TYPE              uint
    DEFAULT           (CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
}

/*******************************************************************************
*
* Additional Intel Architecture show routines
*
*/
Component INCLUDE_INTEL_CPU_SHOW {
    NAME              Intel Architecture processor show routines
    SYNOPSIS          IA-32 processor show routines
    HDR_FILES         vxLib.h
    MODULES           vxShow.o
    INIT_RTN          vxShowInit ();
    _INIT_ORDER       usrShowInit
    _CHILDREN         FOLDER_SHOW_ROUTINES
    _DEFAULTS         += FOLDER_SHOW_ROUTINES
}

/*******************************************************************************
*
* pcPentium4 BSP-specific configuration folder
*
*/
Folder FOLDER_BSP_CONFIG  {
    NAME              pcPentium4 BSP configuration options
    SYNOPSIS          BSP-specific configuration
    CHILDREN          INCLUDE_PCPENTIUM4_PARAMS \
                      INCLUDE_THERM_MONITOR     \
                      INCLUDE_DEBUG_STORE
    DEFAULTS          INCLUDE_PCPENTIUM4_PARAMS
    _CHILDREN         FOLDER_HARDWARE
    _DEFAULTS         += FOLDER_HARDWARE
}

/*******************************************************************************
*
* BSP parameters Component
*
*/
Component INCLUDE_PCPENTIUM4_PARAMS  {
    NAME              BSP build parameters
    SYNOPSIS          expose BSP configurable parameters
    LAYER             1
    CFG_PARAMS        INCLUDE_MTRR_GET    \
                      INCLUDE_PMC         \
                      INCLUDE_BOOT_ADDMEM \
                      ADDED_BOOTMEM_SIZE  \
                      ADDED_BOOTMEM_ADDR
    HELP              pcPentium4
}

Parameter INCLUDE_MTRR_GET  {
    NAME              pcPentium4 configuration parameter
    SYNOPSIS          get Memory Type Range Register settings from the BIOS
    TYPE              exists
    DEFAULT           TRUE
}

Parameter INCLUDE_PMC  {
    NAME              pcPentium4 configuration parameter
    SYNOPSIS          Performance Monitoring Counter library support
    TYPE              exists
    DEFAULT           TRUE
}

Parameter INCLUDE_BOOT_ADDMEM  {
    NAME              pcPentium4 configuration parameter
    SYNOPSIS          add upper memory to low memory bootrom
    TYPE              exists
    DEFAULT           TRUE
}

Parameter ADDED_BOOTMEM_SIZE  {
    NAME              pcPentium4 configuration parameter
    SYNOPSIS          amount of memory added to bootrom memory pool
    TYPE              uint
    DEFAULT           (0x00400000)
}

Parameter ADDED_BOOTMEM_ADDR  {
    NAME              pcPentium4 configuration paramete
    SYNOPSIS          Location of the top of memory
    TYPE              uint
    DEFAULT           (0x00708000)
}

/*******************************************************************************
*
* Physical Address Space Components
*
*/
Component INCLUDE_MMU_P6_32BIT  {
    NAME              32-bit physical address space
    SYNOPSIS          configure 32-bit address space support
    CFG_PARAMS        VM_PAGE_SIZE
    EXCLUDES          INCLUDE_MMU_P6_36BIT
    _CHILDREN         FOLDER_MMU
    _DEFAULTS         += FOLDER_MMU
    HELP              pcPentium4
}

Component INCLUDE_MMU_P6_36BIT  {
    NAME              36-bit physical address space extension
    SYNOPSIS          configure 36-bit address space extension support
    CFG_PARAMS        VM_PAGE_SIZE
    EXCLUDES          INCLUDE_MMU_P6_32BIT LOCAL_MEM_AUTOSIZE
    _CHILDREN         FOLDER_MMU
    HELP              pcPentium4
}

Parameter VM_PAGE_SIZE {
    NAME              VM page size
    SYNOPSIS          virtual memory page size (PAGE_SIZE_{4KB/2MB/4MB})
    TYPE              uint
    DEFAULT           PAGE_SIZE_4KB
}

/*******************************************************************************
*
* Thermal Monitor and Geyserville III Component and Parameters
*
*/
Component INCLUDE_THERM_MONITOR  {
    NAME              Thermal Monitor and Geyserville III support
    SYNOPSIS          configure Thermal Monitor and Geyserville III support
    CFG_PARAMS        TM_MODE \
                      TM_AC_CHK_RTN
    _REQUIRES         INCLUDE_CPU_PWR_MGMT
    REQUIRES          INCLUDE_CPU_PWR_MGMT
    HELP              pcPentium4
}

Parameter TM_MODE {
    NAME              Thermal Management mode
    SYNOPSIS          configure Thermal Management mode
    TYPE              uint
    DEFAULT           GV3_AUTO
}

Parameter TM_AC_CHK_RTN {
    NAME              power source check routine
    SYNOPSIS          function pointer for the power source check routine
    DEFAULT           NULL
}

/*******************************************************************************
*
* Debug Store BTS/PEBS Component and Parameters
*
*/
Component INCLUDE_DEBUG_STORE  {
    NAME              Debug Store BTS/PEBS support
    SYNOPSIS          configure Debug Store BTS/PEBS support
    CFG_PARAMS        DS_SYS_MODE \
                      BTS_ENABLED \
                      BTS_INT_MODE \
                      BTS_BUF_MODE \
                      PEBS_ENABLED \
                      PEBS_EVENT \
                      PEBS_METRIC \
                      PEBS_OS \
                      PEBS_RESET
    HELP              pcPentium4
}

Parameter DS_SYS_MODE {
    NAME              Debug Store BTS/PEBS operating mode
    SYNOPSIS          configure the Debug Store BTS/PEBS operating mode
    TYPE              bool
    DEFAULT           FALSE
}

Parameter BTS_ENABLED {
    NAME              enable or disable the BTS
    SYNOPSIS          enable or disable the BTS
    TYPE              bool
    DEFAULT           TRUE
}

Parameter BTS_INT_MODE {
    NAME              configure the BTS interrupt mode
    SYNOPSIS          configure the BTS interrupt mode
    TYPE              bool
    DEFAULT           TRUE
}

Parameter BTS_BUF_MODE {
    NAME              configure the BTS buffering mode
    SYNOPSIS          configure the BTS buffering mode
    TYPE              bool
    DEFAULT           TRUE
}

Parameter PEBS_ENABLED {
    NAME              enable or disable the PEBS
    SYNOPSIS          enable or disable the PEBS
    TYPE              bool
    DEFAULT           TRUE
}

Parameter PEBS_EVENT {
    NAME              specify the PEBS event
    SYNOPSIS          specify the PEBS event
    TYPE              uint
    DEFAULT           PEBS_FRONT_END
}

Parameter PEBS_METRIC {
    NAME              specify the PEBS metric
    SYNOPSIS          specify the PEBS metric
    TYPE              uint
    DEFAULT           PEBS_MEMORY_STORES
}

Parameter PEBS_OS {
    NAME              configure the PEBS execution mode
    SYNOPSIS          configure the PEBS execution mode
    TYPE              bool
    DEFAULT           TRUE
}

Parameter PEBS_RESET {
    NAME              specify the PEBS reset counter value
    SYNOPSIS          specify the PEBS reset counter value
    TYPE              uint
    DEFAULT           (-1LL)
}



Parameter FTPS_INITIAL_DIR {
    NAME        FTP initial directory
    DEFAULT     "/ata0a"
}
