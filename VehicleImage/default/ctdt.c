/* ctors and dtors arrays -- to be used by runtime system */
/*   to call static constructors and destructors          */
/*                                                        */
/* NOTE: Use a C compiler to compile this file. If you    */
/*       are using GNU C++, be sure to use compile this   */
/*       file using a GNU compiler with the               */
/*       -fdollars-in-identifiers flag.                   */


extern void (*_ctors[])();
void (*_ctors[])() =
    {
    0
    };

void _GLOBAL__D_0___gthread_once();

extern void (*_dtors[])();
void (*_dtors[])() =
    {
    _GLOBAL__D_0___gthread_once,
    0
    };

#include <vxWorks.h>
#include <config.h>

/* build variables */
#if defined(INCLUDE_LOADER) || defined(INCLUDE_WDB)
#ifdef __GNUC__
__asm("	.section \".wrs_build_vars\",\"a\"");
#endif
#ifdef __DCC__
__asm("	.section \".wrs_build_vars\",\"r\"");
#endif
__asm("	.global _wrs_build_vars");
__asm("	.global _wrs_build_vars_end");
__asm("_wrs_build_vars:");
#else
#ifdef __GNUC__
__asm("	.section \".wrs_build_vars\",\"a\"");
#endif
#ifdef __DCC__
__asm("	.section \".wrs_build_vars\",\"n\"");
#endif
#endif
__asm("	.ascii \"set WIND_HOME C:/WindRiver\"");
__asm("	.byte 0");
__asm("	.ascii \"set WIND_BASE $(WIND_HOME)/vxworks-6.8\"");
__asm("	.byte 0");
__asm("	.ascii \"set PRJ_FULL_PATH $(WIND_HOME)/MyWorkspace/VehicleImage\"");
__asm("	.byte 0");
__asm("	.ascii \"set VSB_DIR $(WIND_BASE)/target/lib\"");
__asm("	.byte 0");
__asm("	.ascii \"set BSP_DIR $(WIND_BASE)/target/config/CD6011_bsp\"");
__asm("	.byte 0");
__asm("	.ascii \"set ANALYSIS_DKM_DIR $(VSB_DIR)/pentium/PENTIUM4/common/dkm/analysis\"");
__asm("	.byte 0");
__asm(" .ascii \"tag SMP 0\"");
__asm(" .byte 0");
__asm(" .ascii \"assert $(SMP)==0\"");
__asm(" .byte 0");
#if defined(INCLUDE_LOADER) || defined(INCLUDE_WDB)
__asm("_wrs_build_vars_end:");
#endif
__asm("	.ascii \"end\"");
__asm("	.byte 0");
__asm("	.previous");
