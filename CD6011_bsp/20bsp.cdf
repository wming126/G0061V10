/* 20bsp.cdf - BSP component description file */

/*
 * Copyright (c) 2006-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,11sep09,mze  adding new GUEST_OS_OPTION
01g,15oct08,pgh  Fix bootapp issues.
01f,12jun08,d_c  Auto-exclude test modules that test unsupported features for
                 a given BSP
01e,29aug07,jmg  Added VX_SMP_NUM_CPUS
01d,14mar07,jmt  Add INCLUDE_BOOT_FS_DEVICES component modifications
01c,23feb07,jmt  Defect 88750 - Fix problem with network boot device CDF
                 defines
01b,08feb07,pgh  vxWorks 6.5 mods.
01a,16jul06,pee  created

*/

Bsp CD6020_smp {
    NAME        board support package
    CPU         PENTIUM4
    REQUIRES    INCLUDE_KERNEL \
                INCLUDE_PCI \
                INCLUDE_PENTIUM_PCI \
                INCLUDE_PCI_OLD_CONFIG_ROUTINES \
                INCLUDE_PCPENTIUM4_PARAMS \
                DRV_TIMER_I8253 \
                DRV_NVRAM_FILE \
                INCLUDE_MMU_P6_32BIT \
                INCLUDE_CPU_LIGHT_PWR_MGR
    FP          hard
    MP_OPTIONS  SMP
    GUEST_OS_OPTION SUPPORTED
}

Component INCLUDE_FEI_END {
    NAME        BSP fei82557 End driver
    SYNOPSIS    fei82557 End
    _CHILDREN   FOLDER_BSP_CONFIG
    REQUIRES    INCLUDE_PCI
}

/* Network Boot Devices for a BSP
 * The REQUIRES line should be modified for a BSP.
 */
Component       INCLUDE_BOOT_NET_DEVICES {
    REQUIRES	INCLUDE_FEI8255X_VXB_END
}

/* Specify boot rom console device for this BSP */
Component       INCLUDE_BOOT_SHELL {
    REQUIRES += DRV_SIO_NS16550
}

/* Filesystem Boot Devices for a BSP
 * The REQUIRES line should be modified for a BSP.
 */
Component       INCLUDE_BOOT_FS_DEVICES {
    REQUIRES	INCLUDE_BOOT_FD_LOADER
}

/*
 * VX_SMP_NUM_CPUS is a SMP parameter only and only available for SMP 
 * builds. Due to a limitation of the project tool at the time this 
 * parameter is created where the tool can not recognize the ifdef SMP 
 * selection, this parameter is set up such that _CFG_PARAMS is not 
 * specified here. In the 00vxWorks.cdf file, where the parameter 
 * VX_SMP_NUM_CPUS is defined, the _CFG_PARAMS is specified only for 
 * VxWorks SMP. Hence the redefining of VX_SMP_NUM_CPUS here should only 
 * override the value and not the rest of the properties. And for UP, the 
 * parameter is ignored since the parameter is not tied to any component 
 * (_CFG_PARAMS is not specified).
 */
 
Parameter VX_SMP_NUM_CPUS {
	NAME		Number of CPUs available to be enabled for VxWorks SMP
	TYPE		UINT
	DEFAULT		4
}


/*
 * Force unsupported components to be unavailable.
 *
 * The following component definition(s) forces the named component(s)
 * to be "unavailable" as far as the project build facility (vxprj) is
 * concerned. The required component (COMPONENT_NOT_SUPPORTED) should
 * never be defined, and hence the named component(s) will never be
 * available. This little trick is used by the BSPVTS build scripts
 * (suiteBuild, bspBuildTest.tcl) to automatically exclude test modules
 * that are not applicable to a BSP because the BSP does not support a
 * given component and/or test module. If and when support is added,
 * the following definition(s) should be removed.
 */

Component               INCLUDE_TM_NVRAM {
        REQUIRES        COMPONENT_NOT_SUPPORTED
}
