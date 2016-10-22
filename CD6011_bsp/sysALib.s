/* sysALib.s - PC-386 system-dependent routines */

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
02n,25jul09,scm  add grub support...
02m,15jul09,rbc  Page Table Optimization.
02l,28apr09,rec  guest Os merge from vxWorks 6.7.0
                 force BOOT_NORMAL for Guest.
                 razor to wrhvVb
                 use _WRS_CONFIG_WRHV_GUEST for guest OS build
                 don't set cr4 when running under the hypervisor
02k,17oct08,pgh  Change RAM_LOW_ADRS/RAM_HIGH_ADRS to
                 SYS_RAM_LOW_ADRS/SYS_RAM_HIGH_ADRS.
02j,22aug08,rbc  Changes for passing EFI memory map and ACPI table pointer.
02i,21may08,rbc  Add UEFI Support.
02h,12may08,scm  WIND00118240 - correct sysReboot.
02g,16may07,scm  adjust AP init to account for RTP GDT entries...
02f,13feb07,scm  adjust sysInitCpuStartup for 36-bit addressing mode
                 support...
02e,02feb07,scm  add SMP support mods...
02d,09oct06,scm  correct GDT update, and add sysInitGDT...
                 FIXES: WIND00066325, WIND00066327
02c,07apr04,zmm  Inherit sysStartType from go(). Pentium part of SPR 94336.
02b,12nov02,hdn  made CR4 initialization only for P5 or later (spr 83992)
02a,05nov02,hdn  made sysCpuProbe() execution conditional (spr 76279)
01z,13mar02,hdn  resumed GDT loading after copying from text to RAM (spr 71298)
01y,02nov01,hdn  removed GDT loading not to access sysGdt[] in text (spr 71298)
01x,14aug01,hdn  added Pentium4 support in sysCpuProbe().
		 added sysCsSuper/Exc/Int as task/exc/int code selector.
		 added FUNC/FUNC_LABEL GTEXT/GDATA macros.
01w,12may98,hdn  renamed sysCpuid to sysCpuId.
01v,09apr98,hdn  added support for PentiumPro in sysCpuProbe().
01u,25mar97,hdn  removed a line of CD=NW=1 from sysCpuProbe().
01t,03sep96,hdn  added the compression support. removed BOOTABLE macro.
01s,17jun96,hdn  made sysCpuProbe() user-callable.
01r,13jun96,hdn  added sysInLong() sysInLongString() sysOutLong()
		 sysOutLongString().
01q,01nov94,hdn  added a way to find out Pentium in sysCpuProbe().
		 changed a way to find out 386 by checking AC bit.
01p,19oct94,hdn  renamed sysInitGdt to sysGdt.
		 added sysLoadGdt(), sysA20on().
		 added sysA20Result indicates the state of A20 line.
01o,23sep94,hdn  deleted _sysBootType, sysRegSet(), sysRegGet().
		 added jmp instruction in sysInXX() and sysOutXX().
01n,28apr94,hdn  made sysReboot() simple.
01m,06apr94,hdn  created a processor checking routine sysCpuProbe().
		 created the system GDT at GDT_BASE_OFFSET.
01l,17feb94,hdn  changed name RAM_ENTRY to RAM_HIGH_ADRS
		 changed to put the image in upper memory.
01k,27oct93,hdn  added _sysBootType.
01j,25aug93,hdn  changed a way to enable A20.
01i,12aug93,hdn  added codes to load a user defined global descriptor table.
		 made warm start works changing sysReboot().
		 deleted sysGDTRSet().
01h,09aug93,hdn  added codes to recognize a type of cpu.
01g,17jun93,hdn  updated to 5.1.
01f,08arp93,jdi  doc cleanup.
01e,26mar93,hdn  added sysReg[GS]et, sysGDTRSet. added another sysInit.
01d,16oct92,hdn  added Code Descriptors for the nesting interrupt.
01c,29sep92,hdn  added i80387 support. deleted __fixdfsi.
01b,28aug92,hdn  fixed __fixdfsi temporary.
01a,28feb92,hdn  written based on frc386 version.
*/

/*
DESCRIPTION
This module contains system-dependent routines written in assembly
language.

This module must be the first specified in the \f3ld\f1 command used to
build the system.  The sysInit() routine is the system start-up code.

INTERNAL
Many routines in this module doesn't use the "c" frame pointer %ebp@ !
This is only for the benefit of the stacktrace facility to allow it 
to properly trace tasks executing within these routines.

SEE ALSO: 
.I "i80386 32-Bit Microprocessor User's Manual"
*/



#define _ASMLANGUAGE
#include <vxWorks.h>
#include <vsbConfig.h>
#include <asm.h>
#include <regs.h>
#include <sysLib.h>
#include <config.h>

#ifdef _WRS_CONFIG_SMP
#include <private/vxSmpP.h>
#endif /* _WRS_CONFIG_SMP */

        .data
	.globl  FUNC(copyright_wind_river)
	.long   FUNC(copyright_wind_river)

	/* externals */

	.globl	FUNC(usrInit)		/* system initialization routine */
	.globl	VAR(sysProcessor)	/* initialized to NONE(-1) in sysLib.c */

#ifdef _WRS_CONFIG_SMP
        _IA32_ASM_EXTERN_KERNEL_GLOBALS
                                                                               
        .globl  FUNC(sysInitCpuStartup) /* the cpu startup */
        .globl  FUNC(cpuInit1)          /* the cpu startup initialization */
        .globl  FUNC(sysCpuInit)        /* the cpu initialization */
#endif /* _WRS_CONFIG_SMP */

	/* internals */

	.globl	sysInit			/* start of system code */
	.globl	_sysInit		/* start of system code */
        .globl  GTEXT(sysInitGDT)
	.globl	GTEXT(sysInByte)
	.globl	GTEXT(sysInWord)
	.globl	GTEXT(sysInLong)
	.globl	GTEXT(sysInWordString)
	.globl	GTEXT(sysInLongString)
	.globl	GTEXT(sysOutByte)
	.globl	GTEXT(sysOutWord)
	.globl	GTEXT(sysOutLong)
	.globl	GTEXT(sysOutWordString)
	.globl	GTEXT(sysOutLongString)
	.globl	GTEXT(sysReboot)
	.globl	GTEXT(sysWait)
	.globl	GTEXT(sysCpuProbe)
	.globl	GTEXT(sysLoadGdt)
	.globl	GTEXT(sysGdtr)
	.globl	GTEXT(sysGdt)

	.globl  GDATA(sysCsSuper)	/* code selector: supervisor mode */
	.globl  GDATA(sysCsExc)		/* code selector: exception */
	.globl  GDATA(sysCsInt)		/* code selector: interrupt */


	/* locals */

FUNC_LABEL(vendorIdIntel)		/* CPUID vendor ID - Intel */
	.ascii	"GenuineIntel"


#ifdef INCLUDE_UEFI_BOOT_SUPPORT
	.globl  pSysUefiMemAddr   /* UEFI pointer value for memory block header */
	.globl  pSysUefiAcpiAddr   /* UEFI pointer value for ACPI info */
	.globl  uefiComplianceInfoP /* UEFI read-only compliance string */

	.balign 8, 0x00
pSysUefiMemAddr:
		.long 0x00000000
pSysUefiAcpiAddr:
		.long 0x00000000

#endif /* INCLUDE_UEFI_BOOT_SUPPORT */


	.text
	.balign 16

/*******************************************************************************
*
* sysInit - start after boot
*
* This routine is the system start-up entry point for VxWorks in RAM, the
* first code executed after booting.  It disables interrupts, sets up
* the stack, and jumps to the C routine usrInit() in usrConfig.c.
*
* The initial stack is set to grow down from the address of sysInit().  This
* stack is used only by usrInit() and is never used again.  Memory for the
* stack must be accounted for when determining the system load address.
*
* NOTE: This routine should not be called by the user.
*
* RETURNS: N/A

* sysInit ()              /@ THIS IS NOT A CALLABLE ROUTINE @/
 
*/

sysInit:
_sysInit:
	cli				/* LOCK INTERRUPT */

#ifdef GRUB_MULTIBOOT
        jmp     multiboot_entry

        /* Multiboot Header ---allows GRUB to load kernel */
        .align 8

        /* MULTIBOOT ---ELF images */
multiboot_header:
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_FLAGS_ELF
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS_ELF)

multiboot_entry:

        cmp     $MULTIBOOT_BOOTLOADER_MAGIC, %eax
        jne     multiPrologEnd

        movl    %eax,(MULTIBOOT_SCRATCH)     /* save magic */

        movl    %ebx,(MULTIBOOT_SCRATCH + 8) /* save multi-boot pointer */

        movl    $BOOT_CLEAR,%ebx
multiPrologEnd:
#else
	movl    SP_ARG1(%esp),%ebx
#endif /* GRUB_MULTIBOOT */

#ifdef INCLUDE_UEFI_BOOT_SUPPORT

	jmp overcomplianceinfo
	/* UEFI read-only compliance string */
uefiComplianceInfoP:
		.asciz   "UEFI 001.10 Compliant" /* format is XXX.YY, where YY=1, 2, ..., 9, 10, 11, etc */
overcomplianceinfo:

	/* the second argument on the stack is going to be the memory address of the UEFI
	 * memory data block, pushed by the "go" routine in bootConfig.c
	 */ 
	movl $FUNC(pSysUefiMemAddr), %eax  /* get the memory map data buffer ptr address */
	movl SP_ARG2(%esp), %ecx
	movl %ecx, (%eax)		 /* store the value into the location*/

	/* the third argument on the stack is going to be the memory address of the UEFI
	 * ACPI data block, pushed by the "go" routine in bootConfig.c
	 */ 
	movl $FUNC(pSysUefiAcpiAddr), %eax  /* get the ACPI data ptr address */
	movl SP_ARG3(%esp), %ecx
	movl %ecx, (%eax)		 /* store the value into the location*/

#endif /* INCLUDE_UEFI_BOOT_SUPPORT */

	movl	$ FUNC(sysInit),%esp	/* initialize stack pointer */
	movl	$0,%ebp			/* initialize frame pointer */

	ARCH_REGS_INIT			/* initialize DR[0-7] CR0 EFLAGS */

#ifndef _WRS_CONFIG_WRHV_GUEST
	/* ARCH_CR4_INIT		/@ initialize CR4 for P5,6,7 */

	xorl	%eax, %eax		/* zero EAX */
	movl	%eax, %cr4		/* initialize CR4 */

#ifdef INCLUDE_UEFI_BOOT_SUPPORT
	pushl  	FUNC(pSysUefiAcpiAddr) /* push the pointer to the ACPI Table */
	pushl  	FUNC(pSysUefiMemAddr) /* push the pointer to the UEFI memory data block */
#endif
	pushl	%ebx			/* push the startType */
#else /* _WRS_CONFIG_WRHV_GUEST */
	movl	%ebx, FUNC(wrhvVbConfig) /* save pointer to config record */
	pushl	$BOOT_NORMAL		/* always warm boot for hypervisor */
#endif /* _WRS_CONFIG_WRHV_GUEST */
	movl	$ FUNC(usrInit),%eax
	movl	$ FUNC(sysInit),%edx	/* push return address */
	pushl	%edx			/*   for emulation for call */
	pushl	$0			/* push EFLAGS, 0 */
	pushl	$0x0008			/* a selector 0x08 is 2nd one */
	pushl	%eax			/* push EIP,  FUNC(usrInit) */
	iret				/* iret */

#ifdef _WRS_CONFIG_SMP
/*******************************************************************************
*
* sysInitCpuStartup - istartup initialization for APs...
*
* void sysInitCpuStartup (void)
*
* scratch memory usage:
*
*    scratchMem (scratch memory offset)  scratchPoint
*
*    Standard GDT Entries:
*
*    null descriptor                     scratchMem + 0x04
*
*    kernel text descriptor              scratchMem + 0x0c
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
        .balign 16,0x90
FUNC_LABEL(sysInitCpuStartup)
                                                                         
        /* cold start code in REAL MODE (16 bits) */
                                                                          
        cli                              /* LOCK INTERRUPT */
                                                                         
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        xor     %eax, %eax
                                                                         
        mov     %ax, %ds
        mov     %ax, %ss
                                                          
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $CPU_SCRATCH_POINT, %eax /* find the location of scratch mem */
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     (%eax), %eax
        mov     %ax, %sp
                                                                          
        /* load intial IDT */
                                                                         
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $CPU_SCRATCH_POINT, %eax /* find the location of scratch mem */
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     (%eax), %eax
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        add     $CPU_SCRATCH_IDT, %eax   /* base of initial idt */
                                                                          
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        lidt    (%eax)
                                                                         
        /* load intial GDT */
                                                                          
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $CPU_SCRATCH_POINT, %eax /* find the location of scratch mem */
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     (%eax), %eax
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        add     $CPU_SCRATCH_GDT, %eax   /* base of initial gdt */
                                                                           
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        lgdt    (%eax)
                                                                          
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $CPU_SCRATCH_POINT, %eax /* find the location of scratch mem */
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     (%eax), %eax
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        add     $CR3_OFFSET, %eax        /* stored value for cr3 */
                                                                          
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     (%eax), %eax
        mov     %eax, %cr3

#ifdef  INCLUDE_MMU_P6_36BIT
        /* setup PAE, etc... */
                                                                            
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $0x000006F0,%eax /* set PAE,PSE,OSXMMEXCPT,OSFXSR,PGE,MCE bits */
        mov     %eax,%cr4                /* move EAX to CR4 */
#else
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        movl    $0x000006D0,%eax /* set the OSXMMEXCPT,OSFXSR,PGE,PSE,MCE bits */
        mov     %eax,%cr4                /* move EAX to CR4 */
#endif  /* INCLUDE_MMU_P6_36BIT */
                                                                         
        /* turn on paging & switch to protected mode */
                                                                            
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $0x80010033,%eax         /* set the PE bit */
        mov     %eax,%cr0                /* move EAX to CR0 */
                                                                         
        jmp     clearSegs                /* near jump to flush a inst queue */
                                                                         
clearSegs:
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        xor     %eax, %eax
                                                                        
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $0x0010,%eax             /* a selector 0x10 is 3rd one */
        mov     %ax,%ds
        mov     %ax,%es
        mov     %ax,%fs
        mov     %ax,%gs
        mov     %ax,%ss
                                                                        
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     $CPU_SCRATCH_POINT, %eax /* find the location of scratch mem */
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        mov     (%eax), %eax
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        add     $AP_STK_OFFSET, %eax   /* base of initial stk */
                                                                        
        /* jump to protected mode code in high mem */
                                                                        
        .byte   0x67, 0x66               /* next inst has 32bit operand */
        ljmp    $0x08, $SYS_RAM_LOW_ADRS + cpuInit1 - sysInit

                                                                        
        .balign 16,0x90
FUNC_LABEL(cpuInit1)
                                                                       
        /* cold start code in PROTECTED MODE (32 bits) */
                                                                    
        movl    (%eax), %esp             /* initialise the stack pointer */
                                                                      
        xorl    %eax, %eax               /* zero EAX */
        movl    %eax, %edx               /* zero EDX */
                                                                     
        xorl    %ebp, %ebp               /* initialize the frame pointer */
        pushl   $0                       /* initialise the EFLAGS */
        popfl
                                                                  
        movl    $FUNC(sysCpuInit),%eax   /* jump to cpu init to complete */
                                                                     
        call    *%eax
                                                          
        /* just in case there's a problem */

cpuInitHlt1:
        hlt
        jmp     cpuInitHlt1
#endif /* _WRS_CONFIG_SMP */

/*******************************************************************************
*
* sysInitGDT - load the brand new GDT into RAM
*
* void sysInitGDT (void)
*/
        .balign 16,0x90
FUNC_LABEL(sysInitGDT)

        pushal
        movl    %esp,%ebp

        movl    $FUNC(sysGdt),%esi      /* set src addr (&sysGdt) */

#ifdef _WRS_CONFIG_SMP
        _IA32_PER_CPU_VALUE_GET(%edi,%eax,pSysGdt)
#else
	movl    FUNC(pSysGdt), %edi
#endif

        movl    %edi,%eax
        movl    $ GDT_ENTRIES,%ecx      /* number of GDT entries */
        movl    %ecx,%edx
        shll    $1,%ecx                 /* set (nLongs of GDT) to copy */
        cld
        rep
        movsl                           /* copy GDT from src to dst */

        pushl   %eax                    /* push the (GDT base addr) */
        shll    $3,%edx                 /* get (nBytes of GDT) */
        decl    %edx                    /* get (nBytes of GDT) - 1 */
        shll    $16,%edx                /* move it to the upper 16 */
        pushl   %edx                    /* push the nBytes of GDT - 1 */
        leal    2(%esp),%eax            /* get the addr of (size:addr) */
        pushl   %eax                    /* push it as a parameter */
        call    FUNC(sysLoadGdt)        /* load the brand new GDT in RAM */

        movl    %ebp,%esp
        popal                           /* re-initialize frame pointer */
        ret

/*******************************************************************************
*
* sysInByte - input one byte from I/O space
*
* RETURNS: Byte data from the I/O port.

* UCHAR sysInByte (address)
*     int address;	/@ I/O port address @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysInByte)
	movl	SP_ARG1(%esp),%edx
	movl	$0,%eax
	inb	%dx,%al
	jmp	sysInByte0
sysInByte0:
	ret

/*******************************************************************************
*
* sysInWord - input one word from I/O space
*
* RETURNS: Word data from the I/O port.

* USHORT sysInWord (address)
*     int address;	/@ I/O port address @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysInWord)
	movl	SP_ARG1(%esp),%edx
	movl	$0,%eax
	inw	%dx,%ax
	jmp	sysInWord0
sysInWord0:
	ret

/*******************************************************************************
*
* sysInLong - input one long-word from I/O space
*
* RETURNS: Long-Word data from the I/O port.

* USHORT sysInLong (address)
*     int address;	/@ I/O port address @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysInLong)
	movl	SP_ARG1(%esp),%edx
	movl	$0,%eax
	inl	%dx,%eax
	jmp	sysInLong0
sysInLong0:
	ret

/*******************************************************************************
*
* sysOutByte - output one byte to I/O space
*
* RETURNS: N/A

* void sysOutByte (address, data)
*     int address;	/@ I/O port address @/
*     char data;	/@ data written to the port @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysOutByte)
	movl	SP_ARG1(%esp),%edx
	movl	SP_ARG2(%esp),%eax
	outb	%al,%dx
	jmp	sysOutByte0
sysOutByte0:
	ret

/*******************************************************************************
*
* sysOutWord - output one word to I/O space
*
* RETURNS: N/A

* void sysOutWord (address, data)
*     int address;	/@ I/O port address @/
*     short data;	/@ data written to the port @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysOutWord)
	movl	SP_ARG1(%esp),%edx
	movl	SP_ARG2(%esp),%eax
	outw	%ax,%dx
	jmp	sysOutWord0
sysOutWord0:
	ret

/*******************************************************************************
*
* sysOutLong - output one long-word to I/O space
*
* RETURNS: N/A

* void sysOutLong (address, data)
*     int address;	/@ I/O port address @/
*     long data;	/@ data written to the port @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysOutLong)
	movl	SP_ARG1(%esp),%edx
	movl	SP_ARG2(%esp),%eax
	outl	%eax,%dx
	jmp	sysOutLong0
sysOutLong0:
	ret

/*******************************************************************************
*
* sysInWordString - input word string from I/O space
*
* RETURNS: N/A

* void sysInWordString (port, address, count)
*     int port;		/@ I/O port address @/
*     short *address;	/@ address of data read from the port @/
*     int count;	/@ count @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysInWordString)
	pushl	%edi
	movl	SP_ARG1+4(%esp),%edx
	movl	SP_ARG2+4(%esp),%edi
	movl	SP_ARG3+4(%esp),%ecx
	cld
	rep
	insw	%dx,(%edi)
	movl	%edi,%eax
	popl	%edi
	ret

/*******************************************************************************
*
* sysInLongString - input long string from I/O space
*
* RETURNS: N/A

* void sysInLongString (port, address, count)
*     int port;		/@ I/O port address @/
*     long *address;	/@ address of data read from the port @/
*     int count;	/@ count @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysInLongString)
	pushl	%edi
	movl	SP_ARG1+4(%esp),%edx
	movl	SP_ARG2+4(%esp),%edi
	movl	SP_ARG3+4(%esp),%ecx
	cld
	rep
	insl	%dx,(%edi)
	movl	%edi,%eax
	popl	%edi
	ret

/*******************************************************************************
*
* sysOutWordString - output word string to I/O space
*
* RETURNS: N/A

* void sysOutWordString (port, address, count)
*     int port;		/@ I/O port address @/
*     short *address;	/@ address of data written to the port @/
*     int count;	/@ count @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysOutWordString)
	pushl	%esi
	movl	SP_ARG1+4(%esp),%edx
	movl	SP_ARG2+4(%esp),%esi
	movl	SP_ARG3+4(%esp),%ecx
	cld
	rep
	outsw	(%esi),%dx
	movl	%esi,%eax
	popl	%esi
	ret

/*******************************************************************************
*
* sysOutLongString - output long string to I/O space
*
* RETURNS: N/A

* void sysOutLongString (port, address, count)
*     int port;		/@ I/O port address @/
*     long *address;	/@ address of data written to the port @/
*     int count;	/@ count @/
 
*/

	.balign 16,0x90
FUNC_LABEL(sysOutLongString)
	pushl	%esi
	movl	SP_ARG1+4(%esp),%edx
	movl	SP_ARG2+4(%esp),%esi
	movl	SP_ARG3+4(%esp),%ecx
	cld
	rep
	outsl	(%esi),%dx
	movl	%esi,%eax
	popl	%esi
	ret

/*******************************************************************************
*
* sysWait - wait until the input buffer become empty
*
* wait until the input buffer become empty
*
* RETURNS: N/A

* void sysWait (void)
 
*/

	.balign 16,0x90
FUNC_LABEL(sysWait)
	xorl	%ecx,%ecx
sysWait0:
	movl	$0x64,%edx		/* Check if it is ready to write */
	inb	%dx,%al
	andb	$2,%al
	loopnz	sysWait0
	ret

/*******************************************************************************
*
* sysReboot - reboot system
*
* RETURNS: N/A
*
* NOMANUAL
*
* void sysReboot ()
*
*/

	.balign 16,0x90
FUNC_LABEL(sysReboot)

	pushl   $0x2
	call	FUNC(sysToMonitor)		/* initiate cold boot */
	ret

/*******************************************************************************
*
* sysCpuProbe - perform CPUID if supported and check a type of CPU FAMILY
*
* This routine performs CPUID if supported and check a type of CPU FAMILY.
* This routine is called only once in cacheArchLibInit().  If it is
* called later, it returns the previously obtained result.
*
* RETURNS: a type of CPU FAMILY; 0(386), 1(486), 2(P5/Pentium), 
*	   4(P6/PentiumPro) or 5(P7/Pentium4).
*
* UINT sysCpuProbe (void)

*/

        .balign 16,0x90
FUNC_LABEL(sysCpuProbe)
	cmpl	$ NONE, FUNC(sysProcessor) /* is it executed already? */
	je	sysCpuProbeStart	/*   no: start the CPU probing */
	movl	FUNC(sysProcessor), %eax /* return the sysProcessor */
	ret

sysCpuProbeStart:
	pushfl				/* save EFLAGS */
        cli				/* LOCK INTERRUPT */

	/* check 386. AC bit is a new bit for 486, 386 can not toggle */

	pushfl				/* push EFLAGS */
	popl	%edx			/* pop EFLAGS on EDX */
	movl	%edx, %ecx		/* save original EFLAGS to ECX */
	xorl	$ EFLAGS_AC, %edx	/* toggle AC bit */
	pushl	%edx			/* push new EFLAGS */
	popfl				/* set new EFLAGS */
	pushfl				/* push EFLAGS */
	popl	%edx			/* pop EFLAGS on EDX */
	xorl	%edx, %ecx		/* if AC bit is toggled ? */
        jz	sysCpuProbe386		/*   no: it is 386 */
	pushl	%ecx			/* push original EFLAGS */
	popfl				/* restore original EFLAGS */

	/* check 486. ID bit is a new bit for Pentium, 486 can not toggle */

	pushfl				/* push EFLAGS */
	popl	%edx			/* pop EFLAGS on EDX */
	movl	%edx, %ecx		/* save original EFLAGS to ECX */
	xorl	$ EFLAGS_ID, %edx	/* toggle ID bit */
	pushl	%edx			/* push new EFLAGS */
	popfl				/* set new EFLAGS */
	pushfl				/* push EFLAGS */
	popl	%edx			/* pop EFLAGS on EDX */
	xorl	%edx, %ecx		/* if ID bit is toggled ? */
	jz	sysCpuProbe486		/*   no: it is 486 */

	/* execute CPUID to get vendor, family, model, stepping, features */

	pushl	%ebx			/* save EBX */
	movl	$ CPUID_486, FUNC(sysCpuId)+CPUID_SIGNATURE /* set it 486 */

	/* EAX=0, get the highest value and the vendor ID */

	movl	$0, %eax		/* set EAX 0 */
	cpuid				/* execute CPUID */

	/* check the vendor ID */

	cmpl	%ebx, VAR(vendorIdIntel)+0		/* comp vendor id[0] */
	jne	sysCpuProbeUnknown
	cmpl	%edx, VAR(vendorIdIntel)+4		/* comp vendor id[1] */
	jne	sysCpuProbeUnknown
	cmpl	%ecx, VAR(vendorIdIntel)+8		/* comp vendor id[2] */
	jne	sysCpuProbeUnknown

	/* Intel CPUs will be investigated farther, for now */

	movl	%eax, FUNC(sysCpuId)+CPUID_HIGHVALUE	/* save high value */
	movl	%ebx, FUNC(sysCpuId)+CPUID_VENDORID	/* save vendor id[0] */
	movl	%edx, FUNC(sysCpuId)+CPUID_VENDORID+4	/* save vendor id[1] */
	movl	%ecx, FUNC(sysCpuId)+CPUID_VENDORID+8	/* save vendor id[2] */
	cmpl	$1, %eax				/* is CPUID(1) ok? */
	jl	sysCpuProbeEnd				/*   no: end probe */

	/* EAX=1, get the processor signature and feature flags */

	movl	$1, %eax		/* set EAX 1 */
	cpuid				/* execute CPUID */
	movl	%eax, FUNC(sysCpuId)+CPUID_SIGNATURE	/* save signature */
	movl	%edx, FUNC(sysCpuId)+CPUID_FEATURES_EDX	/* save feature EDX */
	movl	%ecx, FUNC(sysCpuId)+CPUID_FEATURES_ECX	/* save feature ECX */
	movl	%ebx, FUNC(sysCpuId)+CPUID_FEATURES_EBX	/* save feature EBX */
	cmpl	$2, FUNC(sysCpuId)+CPUID_HIGHVALUE	/* is CPUID(2) ok? */
	jl	sysCpuProbeEnd				/*   no: end probe */

	/* EAX=2, get the configuration parameters */

	movl	$2, %eax		/* set EAX 2 */
	cpuid				/* execute CPUID */
	movl	%eax, FUNC(sysCpuId)+CPUID_CACHE_EAX	/* save config EAX */
	movl	%ebx, FUNC(sysCpuId)+CPUID_CACHE_EBX	/* save config EBX */
	movl	%ecx, FUNC(sysCpuId)+CPUID_CACHE_ECX	/* save config ECX */
	movl	%edx, FUNC(sysCpuId)+CPUID_CACHE_EDX	/* save config EDX */
	cmpl	$3, FUNC(sysCpuId)+CPUID_HIGHVALUE	/* is CPUID(3) ok? */
	jl	sysCpuProbeEnd				/*   no: end probe */
	
	/* EAX=3, get the processor serial no */

	movl	$3, %eax		/* set EAX 3 */
	cpuid				/* execute CPUID */
	movl	%edx, FUNC(sysCpuId)+CPUID_SERIALNO	/* save serialno[2] */
	movl	%ecx, FUNC(sysCpuId)+CPUID_SERIALNO+4	/* save serialno[3] */

	/* EAX=0x80000000, to see if the Brand String is supported */

	movl	$0x80000000, %eax	/* set EAX 0x80000000 */
	cpuid				/* execute CPUID */
	cmpl	$0x80000000, %eax	/* is Brand String supported? */
	jbe	sysCpuProbeEnd		/*   no: end probe */

	/* EAX=0x8000000[234], get the Brand String */

	movl	$0x80000002, %eax	/* set EAX 0x80000002 */
	cpuid				/* execute CPUID */
	movl	%eax, FUNC(sysCpuId)+CPUID_BRAND_STR	/* save brandStr[0] */
	movl	%ebx, FUNC(sysCpuId)+CPUID_BRAND_STR+4	/* save brandStr[1] */
	movl	%ecx, FUNC(sysCpuId)+CPUID_BRAND_STR+8	/* save brandStr[2] */
	movl	%edx, FUNC(sysCpuId)+CPUID_BRAND_STR+12	/* save brandStr[3] */

	movl	$0x80000003, %eax	/* set EAX 0x80000003 */
	cpuid				/* execute CPUID */
	movl	%eax, FUNC(sysCpuId)+CPUID_BRAND_STR+16	/* save brandStr[4] */
	movl	%ebx, FUNC(sysCpuId)+CPUID_BRAND_STR+20	/* save brandStr[5] */
	movl	%ecx, FUNC(sysCpuId)+CPUID_BRAND_STR+24	/* save brandStr[6] */
	movl	%edx, FUNC(sysCpuId)+CPUID_BRAND_STR+28	/* save brandStr[7] */

	movl	$0x80000004, %eax	/* set EAX 0x80000004 */
	cpuid				/* execute CPUID */
	movl	%eax, FUNC(sysCpuId)+CPUID_BRAND_STR+32	/* save brandStr[8] */
	movl	%ebx, FUNC(sysCpuId)+CPUID_BRAND_STR+36	/* save brandStr[9] */
	movl	%ecx, FUNC(sysCpuId)+CPUID_BRAND_STR+40	/* save brandStr[10] */
	movl	%edx, FUNC(sysCpuId)+CPUID_BRAND_STR+44	/* save brandStr[11] */
	
	
sysCpuProbeEnd:
	popl	%ebx			/* restore EBX */
	movl	FUNC(sysCpuId)+CPUID_SIGNATURE, %eax	/* get the signature */
	andl	$ CPUID_FAMILY, %eax	/* mask it with FAMILY */
	cmpl	$ CPUID_486, %eax	/* is the CPU FAMILY 486 ? */
	je	sysCpuProbe486		/*   yes: jump to ..486 */
	cmpl	$ CPUID_PENTIUM, %eax	/* is the CPU FAMILY PENTIUM ? */
	je	sysCpuProbePentium	/*   yes: jump to ..Pentium */
	cmpl	$ CPUID_PENTIUMPRO, %eax /* is the CPU FAMILY PENTIUMPRO ? */
	je	sysCpuProbePentiumpro	/*   yes: jump to ..Pentiumpro */
	cmpl	$ CPUID_EXTENDED, %eax	/* is the CPU FAMILY EXTENDED ? */
	je	sysCpuProbeExtended	/*   yes: jump to ..Extended */

sysCpuProbeUnknown:
	popl	%ebx			/* restore EBX */
        movl    $ X86CPU_DEFAULT, %eax	/* it is defined in config.h */
	jmp	sysCpuProbeExit

sysCpuProbe486:
        movl    $ X86CPU_486, %eax	/* set 1 for 486 */
	jmp	sysCpuProbeExit

sysCpuProbePentium:
	movl	$ X86CPU_PENTIUM, %eax	/* set 2 for P5/Pentium */
	jmp	sysCpuProbeExit

sysCpuProbePentiumpro:
	movl	$ X86CPU_PENTIUMPRO, %eax /* set 4 for P6/PentiumPro */
	jmp	sysCpuProbeExit

sysCpuProbeExtended:
	movl	FUNC(sysCpuId)+CPUID_SIGNATURE, %eax	/* get the signature */
	andl	$ CPUID_EXT_FAMILY, %eax /* mask it with EXTENDED FAMILY */
	cmpl	$ CPUID_PENTIUM4, %eax	/* is the CPU FAMILY 486 ? */
	je	sysCpuProbePentium4	/*   yes: jump to ..Pentium4 */

	jmp	sysCpuProbe486		/* unknown CPU. assume it 486 */

sysCpuProbePentium4:
	movl	$ X86CPU_PENTIUM4, %eax	/* set 5 for P7/Pentium4 */
	jmp	sysCpuProbeExit

sysCpuProbe386:
        movl    $ X86CPU_386, %eax	/* set 0 for 386 */

sysCpuProbeExit:
	popfl				/* restore EFLAGS */
	movl	%eax, FUNC(sysProcessor) /* set the CPU FAMILY */
	ret

/*******************************************************************************
*
* sysLoadGdt - load the global descriptor table.
*
* RETURNS: N/A
*
* NOMANUAL

* void sysLoadGdt (char *sysGdtr)
 
*/

        .balign 16,0x90
FUNC_LABEL(sysLoadGdt)
	movl	4(%esp),%eax
	lgdt	(%eax)
	movw	$0x0010,%ax		/* a selector 0x10 is 3rd one */
	movw	%ax,%ds	
	movw	%ax,%es
	movw	%ax,%fs
	movw	%ax,%gs
	movw	%ax,%ss
	ret

/*******************************************************************************
*
* sysGdt - the global descriptor table.
*
* RETURNS: N/A
*
* NOMANUAL
*
*/

	.text
        .balign 16,0x90
FUNC_LABEL(sysGdtr)
	.word	0x0027			/* size   : 39(8 * 5 - 1) bytes */
	.long	FUNC(sysGdt)

	.balign 16,0x90
FUNC_LABEL(sysGdt)
	/* 0(selector=0x0000): Null descriptor */
	.word	0x0000
	.word	0x0000
	.byte	0x00
	.byte	0x00
	.byte	0x00
	.byte	0x00

	/* 1(selector=0x0008): Code descriptor, for the supervisor mode task */
	.word	0xffff			/* limit: xffff */
	.word	0x0000			/* base : xxxx0000 */
	.byte	0x00			/* base : xx00xxxx */
	.byte	0x9a			/* Code e/r, Present, DPL0 */
	.byte	0xcf			/* limit: fxxxx, Page Gra, 32bit */
	.byte	0x00			/* base : 00xxxxxx */

	/* 2(selector=0x0010): Data descriptor */
	.word	0xffff			/* limit: xffff */
	.word	0x0000			/* base : xxxx0000 */
	.byte	0x00			/* base : xx00xxxx */
	.byte	0x92			/* Data r/w, Present, DPL0 */
	.byte	0xcf			/* limit: fxxxx, Page Gra, 32bit */
	.byte	0x00			/* base : 00xxxxxx */

	/* 3(selector=0x0018): Code descriptor, for the exception */
	.word	0xffff			/* limit: xffff */
	.word	0x0000			/* base : xxxx0000 */
	.byte	0x00			/* base : xx00xxxx */
	.byte	0x9a			/* Code e/r, Present, DPL0 */
	.byte	0xcf			/* limit: fxxxx, Page Gra, 32bit */
	.byte	0x00			/* base : 00xxxxxx */

	/* 4(selector=0x0020): Code descriptor, for the interrupt */
	.word	0xffff			/* limit: xffff */
	.word	0x0000			/* base : xxxx0000 */
	.byte	0x00			/* base : xx00xxxx */
	.byte	0x9a			/* Code e/r, Present, DPL0 */
	.byte	0xcf			/* limit: fxxxx, Page Gra, 32bit */
	.byte	0x00			/* base : 00xxxxxx */


        .data
        .balign 32,0x90
FUNC_LABEL(sysCsSuper)
        .long   0x00000008              /* CS for supervisor mode task */
FUNC_LABEL(sysCsExc)
        .long   0x00000018              /* CS for exception */
FUNC_LABEL(sysCsInt)
        .long   0x00000020              /* CS for interrupt */

