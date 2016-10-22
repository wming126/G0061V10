/* 22comp_mipc.cdf - configuration for MCB/MSD/MIPC */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,21aug09,bwa  added MIPC_SM_NODE_IRQ parameter.
01c,29jun09,h_w  remove MCB, MOB and VxBus references for MIPC
01b,21apr09,dcc  updated default values for PLB_1 parameters.
01a,08jan09,dcc  derived from ads8572_AMP version.
*/

Folder FOLDER_MIPC {
	_CHILDREN	FOLDER_MULTIOS
}

Component INCLUDE_MIPC_UNSUPPORTED {
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Parameter MIPC_SM_SYSTEM_POOL_BASE {
    SYNOPSIS    For Wind River HyperVisor, this value must be equal to the \
lowest shared memory virtual address defined in the config_pentium/vxworks.xml \
file, that is intended to be used by the wrhv_0 bus.
    DEFAULT     0xFD000000
}

Parameter MIPC_SM_SYSTEM_POOL_SIZE {
    DEFAULT     0x80000
}

Parameter MIPC_SM_NODE_IRQ {
    Synopsis	Ignored by hypervisor guests. If building an SMP image, \
use the value 3. If building a UP image, 3 will work, 0 might give better \
performance.
    DEFAULT     3
}

