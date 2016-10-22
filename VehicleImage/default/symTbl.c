/* symTbl.c - standalone symbol tables wrapper */

/* CREATED BY C:/WindRiver/vxworks-6.8/host/resource/hutils/tcl/makeSymTbl.tcl
 *  WITH ARGS pentium tmp.o symTbl.c
 *         ON Mon Sep 26 11:41:09 +0800 2016
 */

#include "vxWorks.h"
#include "symbol.h"

IMPORT int AppDelete ();
IMPORT int AppEntry ();
IMPORT int BufferPageCross ();
IMPORT int CheckComSum ();
IMPORT int ClearPciCnt ();
IMPORT int ClosePciCan ();
IMPORT int ClosePciIoCnt ();
IMPORT int CreatCanModule ();
IMPORT int CreatComModule ();
IMPORT int CreatIoCntModule ();
IMPORT int CreatLogFile ();
IMPORT int CreatMangeFileModule ();
IMPORT int CreatMangeUsbModule ();
IMPORT int CreatRollTimeFile ();
IMPORT int CreatUsbPath ();
IMPORT int CreatePciCan ();
IMPORT int CreatePciCan2 ();
IMPORT int CreatePciIoCnt ();
IMPORT int DecToBin ();
IMPORT int DrainFifo ();
IMPORT int EVP_DecodeBlock ();
IMPORT int EVP_DecodeFinal ();
IMPORT int EVP_DecodeInit ();
IMPORT int EVP_DecodeUpdate ();
IMPORT int EVP_EncodeBlock ();
IMPORT int EVP_EncodeFinal ();
IMPORT int EVP_EncodeInit ();
IMPORT int EVP_EncodeUpdate ();
IMPORT int FileSize ();
IMPORT int FlushPciCan ();
IMPORT int GetBiosTime ();
IMPORT int GetPciCan ();
IMPORT int GetTime ();
IMPORT int InitPciCan ();
IMPORT int InitSja ();
IMPORT int InitSystemTime ();
IMPORT int IoctlPciCan ();
IMPORT int MD5_Final ();
IMPORT int MD5_Init ();
IMPORT int MD5_Transform ();
IMPORT int MD5_Update ();
IMPORT int MD5_version;
IMPORT int OpenPciCan ();
IMPORT int OpenPciIoCnt ();
IMPORT int PrintTime ();
IMPORT int ReadComEx ();
IMPORT int ReadPciCan ();
IMPORT int ReadPciCnt ();
IMPORT int ReadPciIo ();
IMPORT int RecvCom ();
IMPORT int RemoveCanModule ();
IMPORT int RemoveComModule ();
IMPORT int RemoveIoCntModule ();
IMPORT int RemoveMangeFileModule ();
IMPORT int RemoveMangeUsbModule ();
IMPORT int RemovePciCan ();
IMPORT int RemovePciCan2 ();
IMPORT int RemovePciIoCnt ();
IMPORT int SHA224 ();
IMPORT int SHA224_Final ();
IMPORT int SHA224_Init ();
IMPORT int SHA224_Update ();
IMPORT int SHA256 ();
IMPORT int SHA256_Final ();
IMPORT int SHA256_Init ();
IMPORT int SHA256_Transform ();
IMPORT int SHA256_Update ();
IMPORT int SHA256_version;
IMPORT int ShowPciCan ();
IMPORT int ShowTime ();
IMPORT int StartPciCnt ();
IMPORT int StopPciCnt ();
IMPORT int TestPciCan ();
IMPORT int TestPciIoCnt ();
IMPORT int WaitPciIo ();
IMPORT int WritePciCan ();
IMPORT int WritePciIo ();
IMPORT int _GLOBAL__D_0___gthread_once ();
IMPORT int _Randseed;
IMPORT int _Unwind_Backtrace ();
IMPORT int _Unwind_DeleteException ();
IMPORT int _Unwind_FindEnclosingFunction ();
IMPORT int _Unwind_Find_FDE ();
IMPORT int _Unwind_ForcedUnwind ();
IMPORT int _Unwind_GetCFA ();
IMPORT int _Unwind_GetDataRelBase ();
IMPORT int _Unwind_GetGR ();
IMPORT int _Unwind_GetIP ();
IMPORT int _Unwind_GetIPInfo ();
IMPORT int _Unwind_GetLanguageSpecificData ();
IMPORT int _Unwind_GetRegionStart ();
IMPORT int _Unwind_GetTextRelBase ();
IMPORT int _Unwind_RaiseException ();
IMPORT int _Unwind_Resume ();
IMPORT int _Unwind_Resume_or_Rethrow ();
IMPORT int _Unwind_SetGR ();
IMPORT int _Unwind_SetIP ();
IMPORT int ___x_gnu___gcc_bcmp_o;
IMPORT int ___x_gnu__absvdi2_o;
IMPORT int ___x_gnu__absvsi2_o;
IMPORT int ___x_gnu__addvdi3_o;
IMPORT int ___x_gnu__addvsi3_o;
IMPORT int ___x_gnu__ashldi3_o;
IMPORT int ___x_gnu__ashrdi3_o;
IMPORT int ___x_gnu__clear_cache_o;
IMPORT int ___x_gnu__clz_o;
IMPORT int ___x_gnu__clzdi2_o;
IMPORT int ___x_gnu__clzsi2_o;
IMPORT int ___x_gnu__cmpdi2_o;
IMPORT int ___x_gnu__ctzdi2_o;
IMPORT int ___x_gnu__ctzsi2_o;
IMPORT int ___x_gnu__divdc3_o;
IMPORT int ___x_gnu__divdi3_o;
IMPORT int ___x_gnu__divsc3_o;
IMPORT int ___x_gnu__divtc3_o;
IMPORT int ___x_gnu__divxc3_o;
IMPORT int ___x_gnu__enable_execute_stack_o;
IMPORT int ___x_gnu__eprintf_o;
IMPORT int ___x_gnu__ffsdi2_o;
IMPORT int ___x_gnu__ffssi2_o;
IMPORT int ___x_gnu__fixdfdi_o;
IMPORT int ___x_gnu__fixsfdi_o;
IMPORT int ___x_gnu__fixtfdi_o;
IMPORT int ___x_gnu__fixunsdfdi_o;
IMPORT int ___x_gnu__fixunsdfsi_o;
IMPORT int ___x_gnu__fixunssfdi_o;
IMPORT int ___x_gnu__fixunssfsi_o;
IMPORT int ___x_gnu__fixunstfdi_o;
IMPORT int ___x_gnu__fixunsxfdi_o;
IMPORT int ___x_gnu__fixunsxfsi_o;
IMPORT int ___x_gnu__fixxfdi_o;
IMPORT int ___x_gnu__floatdidf_o;
IMPORT int ___x_gnu__floatdisf_o;
IMPORT int ___x_gnu__floatditf_o;
IMPORT int ___x_gnu__floatdixf_o;
IMPORT int ___x_gnu__floatundidf_o;
IMPORT int ___x_gnu__floatundisf_o;
IMPORT int ___x_gnu__floatunditf_o;
IMPORT int ___x_gnu__floatundixf_o;
IMPORT int ___x_gnu__lshrdi3_o;
IMPORT int ___x_gnu__moddi3_o;
IMPORT int ___x_gnu__muldc3_o;
IMPORT int ___x_gnu__muldi3_o;
IMPORT int ___x_gnu__mulsc3_o;
IMPORT int ___x_gnu__multc3_o;
IMPORT int ___x_gnu__mulvdi3_o;
IMPORT int ___x_gnu__mulvsi3_o;
IMPORT int ___x_gnu__mulxc3_o;
IMPORT int ___x_gnu__negdi2_o;
IMPORT int ___x_gnu__negvdi2_o;
IMPORT int ___x_gnu__negvsi2_o;
IMPORT int ___x_gnu__paritydi2_o;
IMPORT int ___x_gnu__paritysi2_o;
IMPORT int ___x_gnu__popcount_tab_o;
IMPORT int ___x_gnu__popcountdi2_o;
IMPORT int ___x_gnu__popcountsi2_o;
IMPORT int ___x_gnu__powidf2_o;
IMPORT int ___x_gnu__powisf2_o;
IMPORT int ___x_gnu__powitf2_o;
IMPORT int ___x_gnu__powixf2_o;
IMPORT int ___x_gnu__subvdi3_o;
IMPORT int ___x_gnu__subvsi3_o;
IMPORT int ___x_gnu__trampoline_o;
IMPORT int ___x_gnu__ucmpdi2_o;
IMPORT int ___x_gnu__udiv_w_sdiv_o;
IMPORT int ___x_gnu__udivdi3_o;
IMPORT int ___x_gnu__udivmoddi4_o;
IMPORT int ___x_gnu__umoddi3_o;
IMPORT int ___x_gnu_emutls_o;
IMPORT int ___x_gnu_gthr_gnat_o;
IMPORT int ___x_gnu_unwind_c_o;
IMPORT int ___x_gnu_unwind_dw2_fde_o;
IMPORT int ___x_gnu_unwind_dw2_o;
IMPORT int ___x_gnu_unwind_sjlj_o;
IMPORT int ___x_gnu_vxlib_o;
IMPORT int __absvdi2 ();
IMPORT int __absvsi2 ();
IMPORT int __addvdi3 ();
IMPORT int __addvsi3 ();
IMPORT int __ashldi3 ();
IMPORT int __ashrdi3 ();
IMPORT int __assert ();
IMPORT int __clear_cache ();
IMPORT int __clocale;
IMPORT int __clz_tab;
IMPORT int __clzdi2 ();
IMPORT int __clzsi2 ();
IMPORT int __cmpdi2 ();
IMPORT int __common_intrinsicsInit ();
IMPORT int __costate;
IMPORT int __cplusLoadObjFiles;
IMPORT int __cplusLoad_o;
IMPORT int __cplusUsr_o;
IMPORT int __cplusXtors_o;
IMPORT int __ctype;
IMPORT int __ctype_tolower;
IMPORT int __ctype_toupper;
IMPORT int __ctzdi2 ();
IMPORT int __ctzsi2 ();
IMPORT int __daysSinceEpoch ();
IMPORT int __deregister_frame ();
IMPORT int __deregister_frame_info ();
IMPORT int __deregister_frame_info_bases ();
IMPORT int __divdc3 ();
IMPORT int __divdi3 ();
IMPORT int __divsc3 ();
IMPORT int __divxc3 ();
IMPORT int __emutls_get_address ();
IMPORT int __emutls_register_common ();
IMPORT int __enable_execute_stack ();
IMPORT int __errno ();
IMPORT int __ffsdi2 ();
IMPORT int __ffssi2 ();
IMPORT int __fixdfdi ();
IMPORT int __fixsfdi ();
IMPORT int __fixunsdfdi ();
IMPORT int __fixunsdfsi ();
IMPORT int __fixunssfdi ();
IMPORT int __fixunssfsi ();
IMPORT int __fixunsxfdi ();
IMPORT int __fixunsxfsi ();
IMPORT int __fixxfdi ();
IMPORT int __floatdidf ();
IMPORT int __floatdisf ();
IMPORT int __floatdixf ();
IMPORT int __floatundidf ();
IMPORT int __floatundisf ();
IMPORT int __floatundixf ();
IMPORT int __frame_state_for ();
IMPORT int __gcc_bcmp ();
IMPORT int __gcc_intrinsicsInit ();
IMPORT int __gcc_personality_v0 ();
IMPORT int __getDstInfo ();
IMPORT int __getDstInfoSub ();
IMPORT int __getTime ();
IMPORT int __getZoneInfo ();
IMPORT int __gnat_default_lock ();
IMPORT int __gnat_default_unlock ();
IMPORT int __gnat_install_locks ();
IMPORT int __gthr_supp_vxw_5x_o;
IMPORT int __gthread_active_p ();
IMPORT int __gthread_enter_tls_dtor_context ();
IMPORT int __gthread_enter_tsd_dtor_context ();
IMPORT int __gthread_get_tls_data ();
IMPORT int __gthread_get_tsd_data ();
IMPORT int __gthread_getspecific ();
IMPORT int __gthread_key_create ();
IMPORT int __gthread_key_delete ();
IMPORT int __gthread_leave_tls_dtor_context ();
IMPORT int __gthread_leave_tsd_dtor_context ();
IMPORT int __gthread_mutex_lock ();
IMPORT int __gthread_mutex_unlock ();
IMPORT int __gthread_once ();
IMPORT int __gthread_set_tls_data ();
IMPORT int __gthread_set_tsd_data ();
IMPORT int __gthread_setspecific ();
IMPORT int __includeGnuIntrinsics;
IMPORT int __julday ();
IMPORT int __locale;
IMPORT int __loctime;
IMPORT int __lshrdi3 ();
IMPORT int __moddi3 ();
IMPORT int __muldc3 ();
IMPORT int __muldi3 ();
IMPORT int __mulsc3 ();
IMPORT int __mulvdi3 ();
IMPORT int __mulvsi3 ();
IMPORT int __mulxc3 ();
IMPORT int __negdi2 ();
IMPORT int __negvdi2 ();
IMPORT int __negvsi2 ();
IMPORT int __paritydi2 ();
IMPORT int __paritysi2 ();
IMPORT int __popcount_tab;
IMPORT int __popcountdi2 ();
IMPORT int __popcountsi2 ();
IMPORT int __powidf2 ();
IMPORT int __powisf2 ();
IMPORT int __powixf2 ();
IMPORT int __register_frame ();
IMPORT int __register_frame_info ();
IMPORT int __register_frame_info_bases ();
IMPORT int __register_frame_info_table ();
IMPORT int __register_frame_info_table_bases ();
IMPORT int __register_frame_table ();
IMPORT int __rta_longjmp;
IMPORT int __sclose ();
IMPORT int __sflags ();
IMPORT int __sflush ();
IMPORT int __sfvwrite ();
IMPORT int __smakebuf ();
IMPORT int __sread ();
IMPORT int __srefill ();
IMPORT int __srget ();
IMPORT int __sseek ();
IMPORT int __stderr ();
IMPORT int __stdin ();
IMPORT int __stdout ();
IMPORT int __strxfrm ();
IMPORT int __subvdi3 ();
IMPORT int __subvsi3 ();
IMPORT int __swbuf ();
IMPORT int __swrite ();
IMPORT int __swsetup ();
IMPORT int __ucmpdi2 ();
IMPORT int __udiv_w_sdiv ();
IMPORT int __udivdi3 ();
IMPORT int __udivmoddi4 ();
IMPORT int __umoddi3 ();
IMPORT int __vxmux_assert ();
IMPORT int __wdbEventListIsEmpty;
IMPORT int _api_nbio;
IMPORT int _applLog ();
IMPORT int _archHelp_msg;
IMPORT int _archIORead16 ();
IMPORT int _archIORead32 ();
IMPORT int _archIORead8 ();
IMPORT int _archIOWrite16 ();
IMPORT int _archIOWrite32 ();
IMPORT int _archIOWrite8 ();
IMPORT int _clockRealtime;
IMPORT int _dbgArchInit ();
IMPORT int _dbgBrkDisplayHard ();
IMPORT int _dbgDsmInstRtn;
IMPORT int _dbgFuncCallCheck ();
IMPORT int _dbgInstSizeGet ();
IMPORT int _dbgRetAdrsGet ();
IMPORT int _dbgTaskPCGet ();
IMPORT int _dbgTaskPCSet ();
IMPORT int _endM2Packet_1213 ();
IMPORT int _endM2Packet_2233 ();
IMPORT int _func_CPToUtf16;
IMPORT int _func_CPToUtf8;
IMPORT int _func_PCIeRootForeach;
IMPORT int _func_SysBootParamsGet;
IMPORT int _func_aimMmuLockRegionsImport;
IMPORT int _func_cacheFuncsSet;
IMPORT int _func_classListAdd;
IMPORT int _func_classListInit;
IMPORT int _func_classListLock;
IMPORT int _func_classListRemove;
IMPORT int _func_classListTblInit;
IMPORT int _func_classListUnlock;
IMPORT int _func_consoleOut;
IMPORT int _func_coprocShow;
IMPORT int _func_coprocTaskRegsShow;
IMPORT int _func_cpuIndexGet;
IMPORT int _func_cpuPwrIdleEnter;
IMPORT int _func_cpuPwrIntEnterHook;
IMPORT int _func_cpuPwrIntExitHook;
IMPORT int _func_dosChkStatPrint;
IMPORT int _func_dosDirOldShow;
IMPORT int _func_dosFsFatShow;
IMPORT int _func_dosVDirShow;
IMPORT int _func_edrEvt;
IMPORT int _func_end2VxBusConnect;
IMPORT int _func_end8023AddressForm;
IMPORT int _func_endEtherAddressForm;
IMPORT int _func_endEtherPacketAddrGet;
IMPORT int _func_endEtherPacketDataGet;
IMPORT int _func_envGet;
IMPORT int _func_eventReceive;
IMPORT int _func_eventRsrcSend;
IMPORT int _func_eventSend;
IMPORT int _func_eventStart;
IMPORT int _func_eventTerminate;
IMPORT int _func_evtLogCpc;
IMPORT int _func_evtLogPayload;
IMPORT int _func_evtLogPayloadString;
IMPORT int _func_evtLogReserveTaskName;
IMPORT int _func_evtLogSyscall;
IMPORT int _func_excBaseHook;
IMPORT int _func_excInfoShow;
IMPORT int _func_excIntHook;
IMPORT int _func_excJobAdd;
IMPORT int _func_excPanicHook;
IMPORT int _func_exit;
IMPORT int _func_fastUdpErrorNotify;
IMPORT int _func_fastUdpInput;
IMPORT int _func_fastUdpPortTest;
IMPORT int _func_fclose;
IMPORT int _func_fcntl_dup;
IMPORT int _func_fileDoesNotExist;
IMPORT int _func_fioFltFormatRtn;
IMPORT int _func_fioFltScanRtn;
IMPORT int _func_fppRestoreRtn;
IMPORT int _func_fppSaveRtn;
IMPORT int _func_ftpLs;
IMPORT int _func_ftpTransientFatal;
IMPORT int _func_ftruncMmanHook;
IMPORT int _func_handleAlloc;
IMPORT int _func_handleFreeAll;
IMPORT int _func_ioGlobalStdGet;
IMPORT int _func_ioPxCreateOrOpen;
IMPORT int _func_ioTaskStdSet;
IMPORT int _func_iosPathFdEntryIoctl;
IMPORT int _func_iosPosixFdEntryIoctl;
IMPORT int _func_iosRtpIoTableSizeGet;
IMPORT int _func_iosRtpIoTableSizeSet;
IMPORT int _func_isrConnect;
IMPORT int _func_isrCreate;
IMPORT int _func_isrDelete;
IMPORT int _func_isrDisconnect;
IMPORT int _func_isrDispatcher;
IMPORT int _func_isrInfo;
IMPORT int _func_jobAdd;
IMPORT int _func_jobExcAdd;
IMPORT int _func_jobTaskWorkAdd;
IMPORT int _func_kernelModuleListIdGet;
IMPORT int _func_kernelRoundRobinHook;
IMPORT int _func_lf_advlock;
IMPORT int _func_loadRtpDeltaBaseAddrApply;
IMPORT int _func_loadRtpSymsPolicyOverride;
IMPORT int _func_logMsg;
IMPORT int _func_m2PollStatsIfPoll;
IMPORT int _func_memPartRealloc;
IMPORT int _func_memPartReallocInternal;
IMPORT int _func_memalign;
IMPORT int _func_mmuCacheFlushLoadAdrsGet;
IMPORT int _func_mmuCurrentGet;
IMPORT int _func_moduleIdFigure;
IMPORT int _func_moduleSegInfoGet;
IMPORT int _func_netAttrDeReg;
IMPORT int _func_netAttrReg;
IMPORT int _func_netChDirByName;
IMPORT int _func_netDaemonIxToQId;
IMPORT int _func_netDaemonQIdToIx;
IMPORT int _func_netLsByName;
IMPORT int _func_netPoolShow;
IMPORT int _func_objCoreRelease;
IMPORT int _func_objHandleToObjId;
IMPORT int _func_objNameVerifiedSet;
IMPORT int _func_objOwnerListAdd;
IMPORT int _func_objOwnerListRemove;
IMPORT int _func_objOwnerReclaim;
IMPORT int _func_objOwnerSetBaseInternal;
IMPORT int _func_objOwnerSetInternal;
IMPORT int _func_objRtpObjEachHook;
IMPORT int _func_ownerListLock;
IMPORT int _func_ownerListUnlock;
IMPORT int _func_pciAutoCfgCtl;
IMPORT int _func_pgMgrPageAlloc;
IMPORT int _func_pgMgrPageFree;
IMPORT int _func_pgMgrPageMap;
IMPORT int _func_printErr;
IMPORT int _func_printExcPrintHook;
IMPORT int _func_proofUtf8String;
IMPORT int _func_pthread_testandset_canceltype;
IMPORT int _func_pxCpuTimerCancel;
IMPORT int _func_pxCpuTimerCreate;
IMPORT int _func_pxCpuTimerDelete;
IMPORT int _func_pxCpuTimerStart;
IMPORT int _func_pxSSThreadIntHook;
IMPORT int _func_pxSSThreadStateInit;
IMPORT int _func_qPriBMapNativeResort;
IMPORT int _func_regsShow;
IMPORT int _func_remCurIdGet;
IMPORT int _func_remCurIdSet;
IMPORT int _func_rtpDelete;
IMPORT int _func_rtpDeleteHookAdd;
IMPORT int _func_rtpDeleteHookDelete;
IMPORT int _func_rtpExtraCmdGet;
IMPORT int _func_rtpHandleIdGet;
IMPORT int _func_rtpIdVerify;
IMPORT int _func_rtpInitCompleteHookAdd;
IMPORT int _func_rtpInitCompleteHookDelete;
IMPORT int _func_rtpPause;
IMPORT int _func_rtpPostCreateHookAdd;
IMPORT int _func_rtpPostCreateHookDelete;
IMPORT int _func_rtpPreCreateHookAdd;
IMPORT int _func_rtpPreCreateHookDelete;
IMPORT int _func_rtpShlSymbolsRegister;
IMPORT int _func_rtpShlSymbolsUnregister;
IMPORT int _func_rtpShow;
IMPORT int _func_rtpSigExcKill;
IMPORT int _func_rtpSigPendDestroy;
IMPORT int _func_rtpSigPendInit;
IMPORT int _func_rtpSigPendKill;
IMPORT int _func_rtpSigaction;
IMPORT int _func_rtpSigpending;
IMPORT int _func_rtpSigprocmask;
IMPORT int _func_rtpSigqueue;
IMPORT int _func_rtpSigsuspend;
IMPORT int _func_rtpSigtimedwait;
IMPORT int _func_rtpSpawn;
IMPORT int _func_rtpSymTblIdGet;
IMPORT int _func_rtpTaskKill;
IMPORT int _func_rtpTaskSigBlock;
IMPORT int _func_rtpTaskSigCheck;
IMPORT int _func_rtpTaskSigPendKill;
IMPORT int _func_rtpTaskSigqueue;
IMPORT int _func_rtpVarAdd;
IMPORT int _func_scMemValidate;
IMPORT int _func_sdUnmapAll;
IMPORT int _func_selPtyAdd;
IMPORT int _func_selPtyDelete;
IMPORT int _func_selPtySlaveAdd;
IMPORT int _func_selPtySlaveDelete;
IMPORT int _func_selTyAdd;
IMPORT int _func_selTyDelete;
IMPORT int _func_selWakeup;
IMPORT int _func_selWakeupAll;
IMPORT int _func_selWakeupListInit;
IMPORT int _func_selWakeupListTerm;
IMPORT int _func_semExchange;
IMPORT int _func_semRTake;
IMPORT int _func_semWTake;
IMPORT int _func_shellBpByIdRemove;
IMPORT int _func_shellDbgCallPrint;
IMPORT int _func_shellDbgStackTrace;
IMPORT int _func_shellExcPrint;
IMPORT int _func_shlRtpDeleteAll;
IMPORT int _func_shlRtpInfoGet;
IMPORT int _func_sigExcKill;
IMPORT int _func_sigTimeoutRecalc;
IMPORT int _func_sigeventInit;
IMPORT int _func_sigfillset;
IMPORT int _func_signalMmanHook;
IMPORT int _func_sigprocmask;
IMPORT int _func_smObjObjShow;
IMPORT int _func_spy;
IMPORT int _func_spyClkStart;
IMPORT int _func_spyClkStop;
IMPORT int _func_spyReport;
IMPORT int _func_spyStop;
IMPORT int _func_spyTask;
IMPORT int _func_symByValueAndTypeFind;
IMPORT int _func_symByValueFind;
IMPORT int _func_symEach;
IMPORT int _func_symFindByName;
IMPORT int _func_symFindByValue;
IMPORT int _func_symFindByValueAndType;
IMPORT int _func_symFindSymbol;
IMPORT int _func_symNameGet;
IMPORT int _func_symRegister;
IMPORT int _func_symTblShutdown;
IMPORT int _func_symTypeGet;
IMPORT int _func_symValueGet;
IMPORT int _func_taskCreateHookAdd;
IMPORT int _func_taskDeleteHookAdd;
IMPORT int _func_taskMemCtxSwitch;
IMPORT int _func_taskPxAttrCreate;
IMPORT int _func_taskPxAttrGet;
IMPORT int _func_taskPxAttrSet;
IMPORT int _func_taskRegsShowRtn;
IMPORT int _func_taskStackAlloc;
IMPORT int _func_taskStackFree;
IMPORT int _func_tipStart;
IMPORT int _func_tmrConnect;
IMPORT int _func_tmrDisable;
IMPORT int _func_tmrEnable;
IMPORT int _func_tmrFreq;
IMPORT int _func_tmrPeriod;
IMPORT int _func_tmrStamp;
IMPORT int _func_tmrStampLock;
IMPORT int _func_unldByModuleId;
IMPORT int _func_utf16ToCP;
IMPORT int _func_utf16ToUtf8String;
IMPORT int _func_utf16ToUtf8StringBOM;
IMPORT int _func_utf8ToCP;
IMPORT int _func_utf8ToUtf16String;
IMPORT int _func_utf8ToUtf16StringBOM;
IMPORT int _func_utflen16;
IMPORT int _func_utflen8;
IMPORT int _func_valloc;
IMPORT int _func_virtExtraMapInfoGet;
IMPORT int _func_virtSegInfoGet;
IMPORT int _func_vxMemProbeHook;
IMPORT int _func_vxbDelayCommon;
IMPORT int _func_vxbIntConnect;
IMPORT int _func_vxbIntDisable;
IMPORT int _func_vxbIntDisconnect;
IMPORT int _func_vxbIntDynaConnect;
IMPORT int _func_vxbIntDynaCtlrInputInit;
IMPORT int _func_vxbIntDynaVecAlloc;
IMPORT int _func_vxbIntDynaVecDevMultiProgram;
IMPORT int _func_vxbIntDynaVecDisable;
IMPORT int _func_vxbIntDynaVecEnable;
IMPORT int _func_vxbIntDynaVecOwnerFind;
IMPORT int _func_vxbIntDynaVecProgram;
IMPORT int _func_vxbIntEnable;
IMPORT int _func_vxbPciAutoConfig;
IMPORT int _func_vxbPciDevCfgRead;
IMPORT int _func_vxbPciDevCfgWrite;
IMPORT int _func_vxbUserHookDevInit;
IMPORT int _func_vxdbgBreakpoint;
IMPORT int _func_vxdbgFuncs;
IMPORT int _func_vxdbgRtpCont;
IMPORT int _func_vxdbgRtpIdVerify;
IMPORT int _func_vxdbgRtpStop;
IMPORT int _func_vxdbgTrace;
IMPORT int _func_wdbBreakpoint;
IMPORT int _func_wdbExternEnterHookAdd;
IMPORT int _func_wdbExternExitHookAdd;
IMPORT int _func_wdbExternNotifyHost;
IMPORT int _func_wdbExternRcvHook;
IMPORT int _func_wdbIsNowExternal;
IMPORT int _func_wdbResumeSystem;
IMPORT int _func_wdbSuspendSystem;
IMPORT int _func_wdbTaskBpByIdRemove;
IMPORT int _func_wdbTrace;
IMPORT int _func_windSemRWDelete;
IMPORT int _func_windTickAnnounceHook;
IMPORT int _func_workQDbgTextDump;
IMPORT int _hostAdd ();
IMPORT int _hostDelete ();
IMPORT int _hostGetByAddr ();
IMPORT int _hostGetByName ();
IMPORT int _hostTblSearchByName2 ();
IMPORT int _ipcom_gethostbyaddr_r;
IMPORT int _ipcom_gethostbyname_r;
IMPORT int _ipdhcpc_callback_hook;
IMPORT int _linkMemReqClAlign;
IMPORT int _linkMemReqMlinkAlign;
IMPORT int _muxProtosPerEndInc;
IMPORT int _muxProtosPerEndStart;
IMPORT int _netMemReqDefault ();
IMPORT int _netSysctl;
IMPORT int _netSysctlCli;
IMPORT int _pLinkPoolFuncTbl;
IMPORT int _pNetBufCollect;
IMPORT int _pNetDpool;
IMPORT int _pNetPoolFuncTbl;
IMPORT int _pNetSysPool;
IMPORT int _pSigQueueFreeHead;
IMPORT int _panicHook;
IMPORT int _procNumWasSet;
IMPORT int _setjmpSetup ();
IMPORT int _sigCtxLoad ();
IMPORT int _sigCtxRtnValSet ();
IMPORT int _sigCtxSave ();
IMPORT int _sigCtxSetup ();
IMPORT int _sigCtxStackEnd ();
IMPORT int _sigfaulttable;
IMPORT int _sysInit ();
IMPORT int _taskSuspend ();
IMPORT int _vxb_clkConnectRtn;
IMPORT int _vxb_clkDisableRtn;
IMPORT int _vxb_clkEnableRtn;
IMPORT int _vxb_clkRateGetRtn;
IMPORT int _vxb_clkRateSetRtn;
IMPORT int _vxb_delayRtn;
IMPORT int _vxb_msDelayRtn;
IMPORT int _vxb_usDelayRtn;
IMPORT int _vxmux_pNullPoolFuncTbl;
IMPORT int _wdbCtxLoad ();
IMPORT int _wdbCtxSave ();
IMPORT int _zbufDeleteEmpty ();
IMPORT int _zbufGetSeg ();
IMPORT int _zbufSetSeg ();
IMPORT int abort ();
IMPORT int abs ();
IMPORT int absSymbols_Bounds ();
IMPORT int absSymbols_Common ();
IMPORT int accept ();
IMPORT int access ();
IMPORT int acos ();
IMPORT int aimFppLibInit ();
IMPORT int aimMmuBaseLibInit ();
IMPORT int allocChunkEndGuardSize;
IMPORT int applLoggerInit ();
IMPORT int applLoggerStop ();
IMPORT int applUtilInstInit ();
IMPORT int applUtilLogSem;
IMPORT int asctime ();
IMPORT int asctime_r ();
IMPORT int asin ();
IMPORT int assertlist;
IMPORT int ata0Resources;
IMPORT int ataResources;
IMPORT int ataTypes;
IMPORT int atan ();
IMPORT int atan2 ();
IMPORT int atexit ();
IMPORT int atof ();
IMPORT int atoi ();
IMPORT int atol ();
IMPORT int atomic32Add ();
IMPORT int atomic32And ();
IMPORT int atomic32Cas ();
IMPORT int atomic32Clear ();
IMPORT int atomic32Dec ();
IMPORT int atomic32Get ();
IMPORT int atomic32Inc ();
IMPORT int atomic32Nand ();
IMPORT int atomic32Or ();
IMPORT int atomic32Set ();
IMPORT int atomic32Sub ();
IMPORT int atomic32Xor ();
IMPORT int attrib ();
IMPORT int audio_test ();
IMPORT int avlUintDelete ();
IMPORT int avlUintInsert ();
IMPORT int avlUintMaximumGet ();
IMPORT int avlUintMinimumGet ();
IMPORT int avlUintPredecessorGet ();
IMPORT int avlUintSearch ();
IMPORT int avlUintSuccessorGet ();
IMPORT int avlUintTreeWalk ();
IMPORT int b ();
IMPORT int baseExcOSMStack;
IMPORT int bcmp ();
IMPORT int bcopy ();
IMPORT int bcopyBytes ();
IMPORT int bcopyLongs ();
IMPORT int bcopyWords ();
IMPORT int bd ();
IMPORT int bdall ();
IMPORT int bfill ();
IMPORT int bfillBytes ();
IMPORT int bfillLongs ();
IMPORT int bfillWords ();
IMPORT int bh ();
IMPORT int bind ();
IMPORT int bindresvport ();
IMPORT int bindresvportCommon ();
IMPORT int bindresvport_af ();
IMPORT int binvert ();
IMPORT int bioInit ();
IMPORT int bio_alloc ();
IMPORT int bio_done ();
IMPORT int bio_free ();
IMPORT int bootApp ();
IMPORT int bootAppBootFileLoadAndGo ();
IMPORT int bootAppInit ();
IMPORT int bootAppPrintHeaderFunc;
IMPORT int bootAppPrintf ();
IMPORT int bootAppShellFunc;
IMPORT int bootAppTask ();
IMPORT int bootAppTaskId;
IMPORT int bootBpAnchorExtract ();
IMPORT int bootChange ();
IMPORT int bootCmdNameSkip ();
IMPORT int bootCommandHandlerAdd ();
IMPORT int bootCommandHelpAdd ();
IMPORT int bootDelayedInit;
IMPORT int bootDevFormatHelpAdd ();
IMPORT int bootDisableMmuBeforeEntry;
IMPORT int bootFlagHelpAdd ();
IMPORT int bootFsFileLoad ();
IMPORT int bootFsLoad ();
IMPORT int bootFsLoadInit ();
IMPORT int bootGoOverrideFunc;
IMPORT int bootLeaseExtract ();
IMPORT int bootLoad ();
IMPORT int bootLoadModule ();
IMPORT int bootLoadRoutine;
IMPORT int bootLoaderAdd ();
IMPORT int bootMemBase;
IMPORT int bootNetDevStopAllFunc;
IMPORT int bootNetSettingsUpdateFunc;
IMPORT int bootNetmaskExtract ();
IMPORT int bootParamCheck ();
IMPORT int bootParamsErrorPrint ();
IMPORT int bootParamsPrompt ();
IMPORT int bootParamsShow ();
IMPORT int bootPrintDevsFuncAdd ();
IMPORT int bootScanNum ();
IMPORT int bootShellAutobootFunc;
IMPORT int bootShellDevFormatHelpAddFunc;
IMPORT int bootShellFlagHelpAddFunc;
IMPORT int bootShellHelpAddFunc;
IMPORT int bootShellPrintDevAddFunc;
IMPORT int bootShellPrintfFunc;
IMPORT int bootShellPrompt;
IMPORT int bootSpaceSkip ();
IMPORT int bootStringToStruct ();
IMPORT int bootStringToStructAdd ();
IMPORT int bootStructToString ();
IMPORT int bsearch ();
IMPORT int bspSerialChanGet ();
IMPORT int bswap ();
IMPORT int busCtlrBaseAddrCvt_desc;
IMPORT int busCtlrCfgInfo_desc;
IMPORT int busCtlrDevCfgRead_desc;
IMPORT int busCtlrDevCfgWrite_desc;
IMPORT int busCtlrDevCtlr_desc;
IMPORT int busCtlrInterruptInfo_desc;
IMPORT int bzero ();
IMPORT int c ();
IMPORT int cacheArchClear ();
IMPORT int cacheArchClearEntry ();
IMPORT int cacheArchDisable ();
IMPORT int cacheArchDmaFree ();
IMPORT int cacheArchDmaMalloc ();
IMPORT int cacheArchEnable ();
IMPORT int cacheArchFlush ();
IMPORT int cacheArchLibInit ();
IMPORT int cacheArchLock ();
IMPORT int cacheArchUnlock ();
IMPORT int cacheClear ();
IMPORT int cacheDataEnabled;
IMPORT int cacheDataMode;
IMPORT int cacheDisable ();
IMPORT int cacheDmaFree ();
IMPORT int cacheDmaFreeRtn;
IMPORT int cacheDmaFuncs;
IMPORT int cacheDmaMalloc ();
IMPORT int cacheDmaMallocRtn;
IMPORT int cacheDrvFlush ();
IMPORT int cacheDrvInvalidate ();
IMPORT int cacheDrvPhysToVirt ();
IMPORT int cacheDrvVirtToPhys ();
IMPORT int cacheEnable ();
IMPORT int cacheFlush ();
IMPORT int cacheFlushBytes;
IMPORT int cacheForeignClear ();
IMPORT int cacheForeignFlush ();
IMPORT int cacheForeignInvalidate ();
IMPORT int cacheFuncsSet ();
IMPORT int cacheI86Clear ();
IMPORT int cacheI86Disable ();
IMPORT int cacheI86Enable ();
IMPORT int cacheI86Flush ();
IMPORT int cacheI86Lock ();
IMPORT int cacheI86Reset ();
IMPORT int cacheI86Unlock ();
IMPORT int cacheInvalidate ();
IMPORT int cacheLib;
IMPORT int cacheLibInit ();
IMPORT int cacheLock ();
IMPORT int cacheMmuAvailable;
IMPORT int cacheNullFuncs;
IMPORT int cachePen4Clear ();
IMPORT int cachePen4Flush ();
IMPORT int cachePipeFlush ();
IMPORT int cacheTextLocalUpdate ();
IMPORT int cacheTextUpdate ();
IMPORT int cacheUnlock ();
IMPORT int cacheUserFuncs;
IMPORT int calloc ();
IMPORT int catInfo;
IMPORT int cbrt ();
IMPORT int cd ();
IMPORT int ceil ();
IMPORT int cfree ();
IMPORT int changeFpReg ();
IMPORT int changeLogLevel ();
IMPORT int changeReg ();
IMPORT int chdir ();
IMPORT int checkStack ();
IMPORT int checksum ();
IMPORT int chkdsk ();
IMPORT int chmod ();
IMPORT int classCreateConnect ();
IMPORT int classDestroyConnect ();
IMPORT int classIdTable;
IMPORT int classInit ();
IMPORT int classLibInit ();
IMPORT int classListLibInit ();
IMPORT int classMemPartIdSet ();
IMPORT int classOpenConnect ();
IMPORT int classShowConnect ();
IMPORT int clearerr ();
IMPORT int clock ();
IMPORT int clockLibInit ();
IMPORT int clock_getres ();
IMPORT int clock_gettime ();
IMPORT int clock_gettime_wd ();
IMPORT int clock_nanosleep ();
IMPORT int clock_setres ();
IMPORT int clock_settime ();
IMPORT int close ();
IMPORT int closedir ();
IMPORT int com_change_baudrate ();
IMPORT int com_read_ex ();
IMPORT int com_receive ();
IMPORT int com_test ();
IMPORT int com_transmit ();
IMPORT int com_write_ex ();
IMPORT int commit ();
IMPORT int completionPathComplete ();
IMPORT int completionPathListGet ();
IMPORT int completionPathShow ();
IMPORT int completionSymComplete ();
IMPORT int completionSymListGet ();
IMPORT int completionSymShow ();
IMPORT int connect ();
IMPORT int connectWithTimeout ();
IMPORT int consoleFd;
IMPORT int convertAttrFromArchDepToIndep ();
IMPORT int convertAttrFromArchIndepToDep ();
IMPORT int coprocCtxReplicate ();
IMPORT int coprocCtxStorageSizeGet ();
IMPORT int coprocDescriptorsInit ();
IMPORT int coprocDisable ();
IMPORT int coprocEnable ();
IMPORT int coprocLibInit ();
IMPORT int coprocMRegs ();
IMPORT int coprocRegListShow ();
IMPORT int coprocSave ();
IMPORT int coprocShow ();
IMPORT int coprocShowInit ();
IMPORT int coprocShowOnDebug ();
IMPORT int coprocTaskCreateHook ();
IMPORT int coprocTaskDeleteHook ();
IMPORT int coprocTaskRegsGet ();
IMPORT int coprocTaskRegsSet ();
IMPORT int coprocTaskRegsShow ();
IMPORT int coprocTaskSwapHook ();
IMPORT int coprocsDiscover ();
IMPORT int copy ();
IMPORT int copyStreams ();
IMPORT int copyright_wind_river;
IMPORT int copysign ();
IMPORT int cos ();
IMPORT int cosh ();
IMPORT int cp ();
IMPORT int cplusCallCtors ();
IMPORT int cplusCallDtors ();
IMPORT int cplusCtors ();
IMPORT int cplusCtorsLink ();
IMPORT int cplusDemangle ();
IMPORT int cplusDemangle2 ();
IMPORT int cplusDemangle2Func;
IMPORT int cplusDemangleFunc;
IMPORT int cplusDemangleToBuffer ();
IMPORT int cplusDemangleToBufferFunc;
IMPORT int cplusDemanglerMode;
IMPORT int cplusDemanglerSet ();
IMPORT int cplusDemanglerStyle;
IMPORT int cplusDemanglerStyleInit ();
IMPORT int cplusDemanglerStyleSet ();
IMPORT int cplusDtors ();
IMPORT int cplusDtorsLink ();
IMPORT int cplusLoadFixup ();
IMPORT int cplusMangledSymCheck ();
IMPORT int cplusMangledSymGet ();
IMPORT int cplusMatchMangled ();
IMPORT int cplusMatchMangledListGet ();
IMPORT int cplusUnloadFixup ();
IMPORT int cplusUserAsk ();
IMPORT int cplusXtorGet ();
IMPORT int cplusXtorSet ();
IMPORT int cplusXtorStrategy;
IMPORT int cpuPwrArchLibInit ();
IMPORT int cpuPwrCStateHookSet ();
IMPORT int cpuPwrCStateSet ();
IMPORT int cpuPwrCheckHotRtn ();
IMPORT int cpuPwrEventHandlersSet ();
IMPORT int cpuPwrFrameWorkInit ();
IMPORT int cpuPwrIntEnter ();
IMPORT int cpuPwrIntExit ();
IMPORT int cpuPwrLightMgrInit ();
IMPORT int cpuPwrMgrEnable ();
IMPORT int cpuPwrMgrIsEnabled ();
IMPORT int cpuPwrPStateGet ();
IMPORT int cpuPwrPStateSet ();
IMPORT int cpuPwrTaskCreateRtn ();
IMPORT int cpuPwrTaskPStateGet ();
IMPORT int cpuPwrTaskPStateSet ();
IMPORT int cpuPwrTaskSwapRtn ();
IMPORT int cpuPwrTempThreshGet ();
IMPORT int cpuPwrTempThreshSet ();
IMPORT int cpuPwrThermIntConnect ();
IMPORT int cpuPwrThermIntHandler ();
IMPORT int cpuPwrUtilPeriodSet ();
IMPORT int cpuPwrWdDownRtn ();
IMPORT int cpuPwrWdStartFailed;
IMPORT int cpuPwrWdUpRtn ();
IMPORT int crc16 ();
IMPORT int creat ();
IMPORT char * creationDate;
IMPORT int cret ();
IMPORT int ctime ();
IMPORT int ctime_r ();
IMPORT int d ();
IMPORT int dbgBpEpCoreRtn ();
IMPORT int dbgBpListPrint ();
IMPORT int dbgCallPrint ();
IMPORT int dbgDisassemble ();
IMPORT int dbgDynPrintfCommonRtn ();
IMPORT int dbgHelp ();
IMPORT int dbgInit ();
IMPORT int dbgPrintDsp;
IMPORT int dbgPrintFpp;
IMPORT int dbgPrintSimd;
IMPORT int dbgStackTrace ();
IMPORT int dbgTaskTraceCoreRtn ();
IMPORT int debugIx;
IMPORT int debugPwrMgmt;
IMPORT int defaultDrv;
IMPORT int devAttach ();
IMPORT int devDetach ();
IMPORT int devInit ();
IMPORT int devMap ();
IMPORT int devMapUnsafe ();
IMPORT int devName ();
IMPORT int devResourceGet ();
IMPORT int devResourceIntrGet ();
IMPORT int devUnmap ();
IMPORT int devUnmapUnsafe ();
IMPORT int devs ();
IMPORT int dfltInumTbl;
IMPORT int difftime ();
IMPORT int dirList ();
IMPORT int diskFormat ();
IMPORT int diskInit ();
IMPORT int div ();
IMPORT int div_r ();
IMPORT int dllAdd ();
IMPORT int dllCount ();
IMPORT int dllEach ();
IMPORT int dllGet ();
IMPORT int dllInit ();
IMPORT int dllInsert ();
IMPORT int dllRemove ();
IMPORT int dllTerminate ();
IMPORT int dma_page_addr;
IMPORT int dma_test ();
IMPORT int dosChkDebug;
IMPORT int dosChkDsk ();
IMPORT int dosChkLibInit ();
IMPORT int dosChkMinDate;
IMPORT int dosDirHdlrsList;
IMPORT int dosDirOldDebug;
IMPORT int dosDirOldLibInit ();
IMPORT int dosFatHdlrsList;
IMPORT int dosFsCacheCreateRtn;
IMPORT int dosFsCacheDataDirDefaultSize;
IMPORT int dosFsCacheDeleteRtn;
IMPORT int dosFsCacheFatDefaultSize;
IMPORT int dosFsCacheMountRtn;
IMPORT int dosFsCacheShow ();
IMPORT int dosFsCacheUnmountRtn;
IMPORT int dosFsChkDsk ();
IMPORT int dosFsChkRtn;
IMPORT int dosFsClose ();
IMPORT int dosFsDebug;
IMPORT int dosFsDevCreate ();
IMPORT int dosFsDevDelete ();
IMPORT int dosFsDiskProbe ();
IMPORT int dosFsDrvNum;
IMPORT int dosFsFatInit ();
IMPORT int dosFsFdFree ();
IMPORT int dosFsFdGet ();
IMPORT int dosFsFmtLargeWriteSize;
IMPORT int dosFsFmtLibInit ();
IMPORT int dosFsFmtRtn;
IMPORT int dosFsHdlrInstall ();
IMPORT int dosFsIoctl ();
IMPORT int dosFsLastAccessDateEnable ();
IMPORT int dosFsLibInit ();
IMPORT int dosFsMonitorDevCreate ();
IMPORT int dosFsMsgLevel;
IMPORT int dosFsMutexOptions;
IMPORT int dosFsOpen ();
IMPORT int dosFsShow ();
IMPORT int dosFsShowInit ();
IMPORT int dosFsTCacheShow ();
IMPORT int dosFsVolDescGet ();
IMPORT int dosFsVolFormat ();
IMPORT int dosFsVolFormatFd ();
IMPORT int dosFsVolIsFat12 ();
IMPORT int dosFsVolUnmount ();
IMPORT int dosFsVolumeBioBufferSize;
IMPORT int dosFsVolumeOptionsGet ();
IMPORT int dosFsVolumeOptionsSet ();
IMPORT int dosFsXbdBlkCopy ();
IMPORT int dosFsXbdBlkRead ();
IMPORT int dosFsXbdBlkWrite ();
IMPORT int dosFsXbdBytesRW ();
IMPORT int dosFsXbdIoctl ();
IMPORT int dosPathParse ();
IMPORT int dosSetVolCaseSens ();
IMPORT int dosVDirDebug;
IMPORT int dosVDirLibInit ();
IMPORT int dosVDirMutexOpt;
IMPORT int dosVDirReaddirPlus ();
IMPORT int dosfsDiskFormat ();
IMPORT int dosfsDiskToHost16 ();
IMPORT int dosfsDiskToHost32 ();
IMPORT int dosfsHostToDisk16 ();
IMPORT int dosfsHostToDisk32 ();
IMPORT int dprintf ();
IMPORT int dprintfVerboseLvl;
IMPORT int drem ();
IMPORT int drvTable;
IMPORT int dsmAsize;
IMPORT int dsmData ();
IMPORT int dsmDebug;
IMPORT int dsmDsize;
IMPORT int dsmInst ();
IMPORT int dsmNbytes ();
IMPORT int dtp ();
IMPORT int dtp_debug_onoff ();
IMPORT int dtp_exit ();
IMPORT int dummyErrno;
IMPORT int dummyGetCpuIndex ();
IMPORT int dup ();
IMPORT int dup2 ();
IMPORT int e ();
IMPORT int eax ();
IMPORT int ebp ();
IMPORT int ebx ();
IMPORT int ecx ();
IMPORT int edi ();
IMPORT int edrErrorInjectStub ();
IMPORT int edrErrorPolicyHookRemove ();
IMPORT int edrFlagsGet ();
IMPORT int edrInitFatalPolicyHandler ();
IMPORT int edrInterruptFatalPolicyHandler ();
IMPORT int edrIsDebugMode ();
IMPORT int edrKernelFatalPolicyHandler ();
IMPORT int edrPolicyHandlerHookAdd ();
IMPORT int edrPolicyHandlerHookGet ();
IMPORT int edrRtpFatalPolicyHandler ();
IMPORT int edrStubInit ();
IMPORT int edrSysDbgFlag;
IMPORT int edrSystemDebugModeGet ();
IMPORT int edrSystemDebugModeInit ();
IMPORT int edrSystemDebugModeSet ();
IMPORT int edx ();
IMPORT int eflags ();
IMPORT int elfArchInitHook;
IMPORT int elfArchMdlLoadHook;
IMPORT int elfArchReloc ();
IMPORT int elfArchSymProcessHook;
IMPORT int elfArchVerify ();
IMPORT int emu387Func;
IMPORT int emuInitFunc;
IMPORT int end8023AddressForm ();
IMPORT int endDevName ();
IMPORT int endDevTbl;
IMPORT int endEtherAddressForm ();
IMPORT int endEtherCrc32BeGet ();
IMPORT int endEtherCrc32LeGet ();
IMPORT int endEtherHdrInit ();
IMPORT int endEtherPacketAddrGet ();
IMPORT int endEtherPacketDataGet ();
IMPORT int endFindByName ();
IMPORT int endFirstUnitFind ();
IMPORT int endFlagsClr ();
IMPORT int endFlagsGet ();
IMPORT int endFlagsSet ();
IMPORT int endLibInit ();
IMPORT int endList;
IMPORT int endM2Free ();
IMPORT int endM2Init ();
IMPORT int endM2Ioctl ();
IMPORT int endM2Packet;
IMPORT int endMibIfInit ();
IMPORT int endMultiLstCnt ();
IMPORT int endMultiLstFirst ();
IMPORT int endMultiLstNext ();
IMPORT int endObjFlagSet ();
IMPORT int endObjInit ();
IMPORT int endObjectUnload ();
IMPORT int endPollStatsInit ();
IMPORT int endPoolClSize;
IMPORT int endPoolCreate ();
IMPORT int endPoolDestroy ();
IMPORT int endPoolJumboClSize;
IMPORT int endPoolJumboCreate ();
IMPORT int endRcvRtnCall ();
IMPORT int endTxSemGive ();
IMPORT int endTxSemTake ();
IMPORT int envGet ();
IMPORT int envLibInit ();
IMPORT int envLibSem;
IMPORT int envLibSemId;
IMPORT int envPrivateCreate ();
IMPORT int envPrivateDestroy ();
IMPORT int envShow ();
IMPORT int erfCatDefSem;
IMPORT int erfCatEventQueues;
IMPORT int erfCategoriesAvailable ();
IMPORT int erfCategoryAllocate ();
IMPORT int erfCategoryQueueCreate ();
IMPORT int erfDbCatSem;
IMPORT int erfDefaultEventQueue;
IMPORT int erfEventQueueSize;
IMPORT int erfEventRaise ();
IMPORT int erfEventTaskOptions;
IMPORT int erfEventTaskPriority;
IMPORT int erfEventTaskStackSize;
IMPORT int erfHandlerDb;
IMPORT int erfHandlerRegister ();
IMPORT int erfHandlerUnregister ();
IMPORT int erfLibInit ();
IMPORT int erfLibInitialized;
IMPORT int erfMaxNumCat;
IMPORT int erfMaxNumType;
IMPORT int erfMaxNumUserCat;
IMPORT int erfMaxNumUserType;
IMPORT int erfNumUserCatDef;
IMPORT int erfNumUserTypeDef;
IMPORT int erfTypeAllocate ();
IMPORT int erfTypesAvailable ();
IMPORT int errno;
IMPORT int errnoGet ();
IMPORT int errnoOfTaskGet ();
IMPORT int errnoOfTaskSet ();
IMPORT int errnoSet ();
IMPORT int esi ();
IMPORT int esp ();
IMPORT int eth_test ();
IMPORT int etherMultiAdd ();
IMPORT int etherMultiDel ();
IMPORT int etherMultiGet ();
IMPORT int etherbroadcastaddr;
IMPORT int eventClear ();
IMPORT int eventInit ();
IMPORT int eventLibInit ();
IMPORT int eventPointStubLibInit ();
IMPORT int eventPointSwHandle ();
IMPORT int eventPointSwStubConnect ();
IMPORT int eventReceive ();
IMPORT int eventRsrcSend ();
IMPORT int eventRsrcShow ();
IMPORT int eventSend ();
IMPORT int eventStart ();
IMPORT int eventTaskShow ();
IMPORT int eventTerminate ();
IMPORT int evtAction;
IMPORT int excCallTbl ();
IMPORT int excDoBell;
IMPORT int excExcHandle ();
IMPORT int excExcepHook;
IMPORT int excGetExcCnt ();
IMPORT int excHookAdd ();
IMPORT int excInit ();
IMPORT int excIntHandle ();
IMPORT int excIntStub ();
IMPORT int excJobAdd ();
IMPORT int excMcaInfoShow;
IMPORT int excOSMStack;
IMPORT int excOSMStackCurrent;
IMPORT int excOSMTss;
IMPORT int excOSMTssCurrent;
IMPORT int excOsmInit ();
IMPORT int excShowInit ();
IMPORT int excStub ();
IMPORT int excVecInit ();
IMPORT int exit ();
IMPORT int exp ();
IMPORT int exp__E ();
IMPORT int expm1 ();
IMPORT int fabs ();
IMPORT int facos ();
IMPORT int fasin ();
IMPORT int fat16ClustValueGet ();
IMPORT int fat16ClustValueSet ();
IMPORT int fat16Debug;
IMPORT int fat16VolMount ();
IMPORT int fatClugFac;
IMPORT int fatan ();
IMPORT int fatan2 ();
IMPORT int fcbrt ();
IMPORT int fceil ();
IMPORT int fchmod ();
IMPORT int fclose ();
IMPORT int fcntl ();
IMPORT int fcntl_dup ();
IMPORT int fcos ();
IMPORT int fcosh ();
IMPORT int fdClass;
IMPORT int fdInvalidDrv;
IMPORT int fdatasync ();
IMPORT int fdopen ();
IMPORT int fdprintf ();
IMPORT int feof ();
IMPORT int ferror ();
IMPORT int fexp ();
IMPORT int ffabs ();
IMPORT int ffloor ();
IMPORT int fflush ();
IMPORT int ffmod ();
IMPORT int ffsLsb ();
IMPORT int ffsMsb ();
IMPORT int fgetc ();
IMPORT int fgetpos ();
IMPORT int fgets ();
IMPORT int fhypot ();
IMPORT int fieldSzIncludeSign;
IMPORT int file_test ();
IMPORT int fileno ();
IMPORT int finfinity ();
IMPORT int finite ();
IMPORT int fioBaseLibInit ();
IMPORT int fioBufPrint ();
IMPORT int fioBufPut ();
IMPORT int fioFltInstall ();
IMPORT int fioFormatV ();
IMPORT int fioLibInit ();
IMPORT int fioRdString ();
IMPORT int fioRead ();
IMPORT int fioScanV ();
IMPORT int fioSnBufPut ();
IMPORT int firint ();
IMPORT int firound ();
IMPORT int firstCmd;
IMPORT int firstLoader;
IMPORT int flNvRam0Resources;
IMPORT int flNvRam0Segments;
IMPORT int floatInit ();
IMPORT int flog ();
IMPORT int flog10 ();
IMPORT int flog2 ();
IMPORT int floor ();
IMPORT int fmod ();
IMPORT int fopen ();
IMPORT int fpCtlRegName;
IMPORT int fpRegName;
IMPORT int fpTypeGet ();
IMPORT int fpXctlRegName;
IMPORT int fpathconf ();
IMPORT int fpow ();
IMPORT int fppArchInit ();
IMPORT int fppArchSwitchHook ();
IMPORT int fppArchSwitchHookEnable ();
IMPORT int fppArchTaskCreateInit ();
IMPORT int fppClex ();
IMPORT int fppCtxCreate ();
IMPORT int fppCtxDelete ();
IMPORT int fppCtxToRegs ();
IMPORT int fppCwGet ();
IMPORT int fppCwSet ();
IMPORT int fppDisable ();
IMPORT int fppDtoDx ();
IMPORT int fppDxtoD ();
IMPORT int fppEnable ();
IMPORT int fppFcw;
IMPORT int fppFsw;
IMPORT int fppNclex ();
IMPORT int fppProbe ();
IMPORT int fppProbeSup ();
IMPORT int fppRegsToCtx ();
IMPORT int fppRestore ();
IMPORT int fppSave ();
IMPORT int fppSwGet ();
IMPORT int fppTaskRegsGet ();
IMPORT int fppTaskRegsSet ();
IMPORT int fppWait ();
IMPORT int fppXctxToRegs ();
IMPORT int fppXregsToCtx ();
IMPORT int fppXrestore ();
IMPORT int fppXsave ();
IMPORT int fprintf ();
IMPORT int fputc ();
IMPORT int fputs ();
IMPORT int fread ();
IMPORT int free ();
IMPORT int freopen ();
IMPORT int frexp ();
IMPORT int fround ();
IMPORT int fsEventUtilLibInit ();
IMPORT int fsMonitorInit ();
IMPORT int fsPathAddedEventRaise ();
IMPORT int fsPathAddedEventSetup ();
IMPORT int fsWaitForPath ();
IMPORT int fscanf ();
IMPORT int fseek ();
IMPORT int fsetpos ();
IMPORT int fsin ();
IMPORT int fsincos ();
IMPORT int fsinh ();
IMPORT int fsmGetDriver ();
IMPORT int fsmGetVolume ();
IMPORT int fsmInitialized;
IMPORT int fsmNameInstall ();
IMPORT int fsmNameMap ();
IMPORT int fsmNameUninstall ();
IMPORT int fsmProbeInstall ();
IMPORT int fsmProbeUninstall ();
IMPORT int fsmUnmountHookAdd ();
IMPORT int fsmUnmountHookDelete ();
IMPORT int fsmUnmountHookRun ();
IMPORT int fsqrt ();
IMPORT int fstat ();
IMPORT int fstatfs ();
IMPORT int fstatfs64 ();
IMPORT int fsync ();
IMPORT int ftan ();
IMPORT int ftanh ();
IMPORT int ftell ();
IMPORT int ftpCommand ();
IMPORT int ftpCommandEnhanced ();
IMPORT int ftpDataConnGet ();
IMPORT int ftpDataConnInit ();
IMPORT int ftpDataConnInitPassiveMode ();
IMPORT int ftpHookup ();
IMPORT int ftpLibDebugOptionsSet ();
IMPORT int ftpLibInit ();
IMPORT int ftpLogin ();
IMPORT int ftpLs ();
IMPORT int ftpReplyGet ();
IMPORT int ftpReplyGetEnhanced ();
IMPORT int ftpReplyTimeout;
IMPORT int ftpTransientConfigGet ();
IMPORT int ftpTransientConfigSet ();
IMPORT int ftpTransientFatalInstall ();
IMPORT int ftpVerbose;
IMPORT int ftpXfer ();
IMPORT int ftplDebug;
IMPORT int ftplPasvModeDisable;
IMPORT int ftplTransientMaxRetryCount;
IMPORT int ftplTransientRetryInterval;
IMPORT int ftrunc ();
IMPORT int fwrite ();
IMPORT int gRHConfigDescriptor;
IMPORT int gRHDeviceDescriptor;
IMPORT int g_AtaName;
IMPORT int g_BusNum;
IMPORT int g_CanMsgID;
IMPORT int g_ComBauds;
IMPORT int g_ComMsgID;
IMPORT int g_Compat_NT;
IMPORT int g_DevNum;
IMPORT int g_EHCDControllerCount;
IMPORT int g_EHCDHandle;
IMPORT int g_ExtComAddr;
IMPORT int g_ExtComName;
IMPORT int g_FunNum;
IMPORT int g_IoCntMsgID;
IMPORT int g_ListAccessEvent;
IMPORT int g_MassUsbName;
IMPORT int g_MscHaveMountedMsgID;
IMPORT int g_NativeInfos;
IMPORT int g_TxBuffer;
IMPORT int g_USBDRequestFunctions;
IMPORT int g_ataBuffer;
IMPORT int g_can_id;
IMPORT int g_can_send_states;
IMPORT int g_com_baud;
IMPORT int g_devices;
IMPORT int g_dtp_debug;
IMPORT int g_pEHCDData;
IMPORT int g_pUHCDData;
IMPORT int g_pcican_debug;
IMPORT int g_received_counts;
IMPORT int g_recv_err_counts;
IMPORT int g_sja1000s;
IMPORT int g_tran_err_counts;
IMPORT int g_transmit_counts;
IMPORT int g_txBufferCount;
IMPORT int g_usbHstFunctionList;
IMPORT int geiRegister ();
IMPORT int genPhyDevRegistration;
IMPORT int genPhyRegister ();
IMPORT int getArg ();
IMPORT int getOptServ ();
IMPORT int getSymNames ();
IMPORT int getc ();
IMPORT int getchar ();
IMPORT int getcwd ();
IMPORT int getenv ();
IMPORT int gethostname ();
IMPORT int getlhostbyaddr ();
IMPORT int getlhostbyname ();
IMPORT int getopt ();
IMPORT int getoptInit ();
IMPORT int getopt_r ();
IMPORT int getpeername ();
IMPORT int getpid ();
IMPORT int gets ();
IMPORT int getsockname ();
IMPORT int getsockopt ();
IMPORT int getw ();
IMPORT int getwd ();
IMPORT int glbMpApicInterruptTable;
IMPORT int glbMpApicIoBaseId;
IMPORT int glbMpApicNioint;
IMPORT int glbMpApicNloint;
IMPORT int globalBusCtrlID;
IMPORT int globalIchDrvCtrl;
IMPORT int globalNoStackFill;
IMPORT int gmtime ();
IMPORT int gmtime_r ();
IMPORT int go ();
IMPORT int gopherHookAdd ();
IMPORT int gopherWriteChar ();
IMPORT int gopherWriteScalar ();
IMPORT int gpGlobalBus;
IMPORT int h ();
IMPORT int hHcDriver;
IMPORT int handleContextGet ();
IMPORT int handleContextGetBase ();
IMPORT int handleContextSet ();
IMPORT int handleInit ();
IMPORT int handleShow ();
IMPORT int handleShowConnect ();
IMPORT int handleTerminate ();
IMPORT int handleTypeGet ();
IMPORT int handleVerify ();
IMPORT int hardWareInterFaceBusInit ();
IMPORT int hardWareInterFaceInit ();
IMPORT int hashFuncIterScale ();
IMPORT int hashFuncModulo ();
IMPORT int hashFuncMultiply ();
IMPORT int hashKeyCmp ();
IMPORT int hashKeyStrCmp ();
IMPORT int hashLibInit ();
IMPORT int hashTblCreate ();
IMPORT int hashTblDelete ();
IMPORT int hashTblDestroy ();
IMPORT int hashTblEach ();
IMPORT int hashTblFind ();
IMPORT int hashTblInit ();
IMPORT int hashTblPut ();
IMPORT int hashTblRemove ();
IMPORT int hashTblTerminate ();
IMPORT int hcfDeviceGet ();
IMPORT int hcfDeviceList;
IMPORT int hcfDeviceNum;
IMPORT int hdprintf ();
IMPORT int help ();
IMPORT int hookAddToHead ();
IMPORT int hookAddToTail ();
IMPORT int hookDelete ();
IMPORT int hookFind ();
IMPORT int hostAdd ();
IMPORT int hostDelete ();
IMPORT int hostGetByAddr ();
IMPORT int hostGetByName ();
IMPORT int hostInitFlag;
IMPORT int hostList;
IMPORT int hostListSem;
IMPORT int hostTblInit ();
IMPORT int hostTblSearchByAddr ();
IMPORT int hostTblSearchByAddr2 ();
IMPORT int hostTblSearchByName ();
IMPORT int hostTblSearchByName2 ();
IMPORT int hostTblSetup ();
IMPORT int hostentAlloc ();
IMPORT int hostentFree ();
IMPORT int hostnameSetup ();
IMPORT int hrfsDiskFormat ();
IMPORT int hrfsFmtRtn;
IMPORT int hwMemAlloc ();
IMPORT int hwMemFree ();
IMPORT int hwMemLibInit ();
IMPORT int hwMemPool;
IMPORT int hwMemPoolCreate ();
IMPORT int hw_node;
IMPORT int hypot ();
IMPORT int i ();
IMPORT int i8042vxbRegister ();
IMPORT int i8253DevResources;
IMPORT int i8259Init ();
IMPORT int i8259IntBoi ();
IMPORT int i8259IntBoiEem ();
IMPORT int i8259IntBoiSmm ();
IMPORT int i8259IntEoiMaster ();
IMPORT int i8259IntEoiSlave ();
IMPORT int i8259IntEoiSlaveNfnm ();
IMPORT int i8259IntEoiSlaveSfnm ();
IMPORT int i8259IntEoiSmm ();
IMPORT int iPciCan ();
IMPORT int iPciIo ();
IMPORT int iam ();
IMPORT int ichAtaBlkRW ();
IMPORT int ichAtaCmd ();
IMPORT int ichAtaConfig ();
IMPORT int ichAtaConfigInit ();
IMPORT int ichAtaCtrlReset ();
IMPORT int ichAtaDevCreate ();
IMPORT int ichAtaDevIdentify ();
IMPORT int ichAtaDmaModeNegotiate ();
IMPORT int ichAtaDmaModeSet ();
IMPORT int ichAtaDmaRW ();
IMPORT int ichAtaDmaToggle ();
IMPORT int ichAtaDrv ();
IMPORT int ichAtaDumptest ();
IMPORT int ichAtaGetCtrl ();
IMPORT int ichAtaInit ();
IMPORT int ichAtaParamRead ();
IMPORT int ichAtaPiInit ();
IMPORT int ichAtaRW ();
IMPORT int ichAtaRawio ();
IMPORT int ichAtaShow ();
IMPORT int ichAtaShowInit ();
IMPORT int ichAtaStatusChk ();
IMPORT int ichAtaXbdDevCreate ();
IMPORT int ichAtaXbdRawio ();
IMPORT int ichAtapiBytesPerSectorGet ();
IMPORT int ichAtapiBytesPerTrackGet ();
IMPORT int ichAtapiCtrlMediumRemoval ();
IMPORT int ichAtapiCurrentCylinderCountGet ();
IMPORT int ichAtapiCurrentHeadCountGet ();
IMPORT int ichAtapiCurrentMDmaModeGet ();
IMPORT int ichAtapiCurrentPioModeGet ();
IMPORT int ichAtapiCurrentRwModeGet ();
IMPORT int ichAtapiCurrentSDmaModeGet ();
IMPORT int ichAtapiCurrentUDmaModeGet ();
IMPORT int ichAtapiCylinderCountGet ();
IMPORT int ichAtapiDriveSerialNumberGet ();
IMPORT int ichAtapiDriveTypeGet ();
IMPORT int ichAtapiFeatureEnabledGet ();
IMPORT int ichAtapiFeatureSupportedGet ();
IMPORT int ichAtapiFirmwareRevisionGet ();
IMPORT int ichAtapiHeadCountGet ();
IMPORT int ichAtapiInit ();
IMPORT int ichAtapiIoctl ();
IMPORT int ichAtapiMaxMDmaModeGet ();
IMPORT int ichAtapiMaxPioModeGet ();
IMPORT int ichAtapiMaxSDmaModeGet ();
IMPORT int ichAtapiMaxUDmaModeGet ();
IMPORT int ichAtapiModelNumberGet ();
IMPORT int ichAtapiPktCmd ();
IMPORT int ichAtapiPktCmdSend ();
IMPORT int ichAtapiRead10 ();
IMPORT int ichAtapiReadCapacity ();
IMPORT int ichAtapiReadTocPmaAtip ();
IMPORT int ichAtapiRemovMediaStatusNotifyVerGet ();
IMPORT int ichAtapiScan ();
IMPORT int ichAtapiSeek ();
IMPORT int ichAtapiSetCDSpeed ();
IMPORT int ichAtapiStartStopUnit ();
IMPORT int ichAtapiStopPlayScan ();
IMPORT int ichAtapiTestUnitRdy ();
IMPORT int ichAtapiVersionNumberGet ();
IMPORT int ichIdeCtrlReset ();
IMPORT int ichIdeDrvInstalled;
IMPORT int ichInitAtaDmaEngine ();
IMPORT int ichPciIdeCtrlInit ();
IMPORT int ichStartAtaDmaEngine ();
IMPORT int ichStopAtaDmaEngine ();
IMPORT int ifAddrAdd ();
IMPORT int ifAddrDelete ();
IMPORT int ifAddrGet ();
IMPORT int ifAddrSet ();
IMPORT int ifAllRoutesDelete ();
IMPORT int ifBroadcastGet ();
IMPORT int ifBroadcastSet ();
IMPORT int ifDstAddrGet ();
IMPORT int ifDstAddrSet ();
IMPORT int ifFlagChange ();
IMPORT int ifFlagGet ();
IMPORT int ifFlagSet ();
IMPORT int ifIndexToIfName ();
IMPORT int ifLibInit ();
IMPORT int ifMaskGet ();
IMPORT int ifMaskSet ();
IMPORT int ifMetricGet ();
IMPORT int ifMetricSet ();
IMPORT int ifNameToIfIndex ();
IMPORT int ifProxyArpDisable ();
IMPORT int ifProxyArpEnable ();
IMPORT int ifRouteDelete ();
IMPORT int ifconfig ();
IMPORT int in_netof ();
IMPORT int index ();
IMPORT int inet_addr ();
IMPORT int inet_aton ();
IMPORT int inet_lnaof ();
IMPORT int inet_makeaddr ();
IMPORT int inet_makeaddr_b ();
IMPORT int inet_netof ();
IMPORT int inet_netof_string ();
IMPORT int inet_network ();
IMPORT int inet_ntoa ();
IMPORT int inet_ntoa_b ();
IMPORT int inet_ntop ();
IMPORT int inet_pton ();
IMPORT int infinity ();
IMPORT int initApplLogger ();
IMPORT int instParamModify_desc;
IMPORT int intArchConnect ();
IMPORT int intArchDisconnect ();
IMPORT int intBoiExit ();
IMPORT int intCnt;
IMPORT int intConnect ();
IMPORT int intContext ();
IMPORT int intCount ();
IMPORT int intCpuLock ();
IMPORT int intCpuMicroLock ();
IMPORT int intCpuMicroUnlock ();
IMPORT int intCpuUnlock ();
IMPORT int intDisable ();
IMPORT int intDisconnect ();
IMPORT int intEOI;
IMPORT int intEnable ();
IMPORT int intEnt ();
IMPORT int intEoiGet;
IMPORT int intExit ();
IMPORT int intHandlerCreate ();
IMPORT int intHandlerCreateI86 ();
IMPORT int intLevelSet ();
IMPORT int intLock ();
IMPORT int intLockLevelGet ();
IMPORT int intLockLevelSet ();
IMPORT int intLockMask;
IMPORT int intNest;
IMPORT int intRegsLock ();
IMPORT int intRegsUnlock ();
IMPORT int intRestrict ();
IMPORT int intStackEnable ();
IMPORT int intUnlock ();
IMPORT int intVBRSet ();
IMPORT int intVecBaseGet ();
IMPORT int intVecBaseSet ();
IMPORT int intVecGet ();
IMPORT int intVecGet2 ();
IMPORT int intVecSet ();
IMPORT int intVecSet2 ();
IMPORT int intVecSetEnt;
IMPORT int intVecSetExit;
IMPORT int intVecTableWriteProtect ();
IMPORT int int_test ();
IMPORT int ioApicIntrBaseGet_desc;
IMPORT int ioApicIntrDrvInitializedCount;
IMPORT int ioApicIntrIntDisable_desc;
IMPORT int ioApicIntrIntEnable_desc;
IMPORT int ioApicIntrIntLock_desc;
IMPORT int ioApicIntrIntUnlock_desc;
IMPORT int ioApicIntrVersionGet_desc;
IMPORT int ioApicNumIoApics;
IMPORT int ioApicRed0_15;
IMPORT int ioApicRed16_23;
IMPORT int ioApicRedNumEntries;
IMPORT int ioApicRedNumEntriesGet_desc;
IMPORT int ioDefPath;
IMPORT int ioDefPathCat ();
IMPORT int ioDefPathGet ();
IMPORT int ioDefPathSet ();
IMPORT int ioDefPathSetInternal ();
IMPORT int ioFullFileNameGet ();
IMPORT int ioGlobalStdGet ();
IMPORT int ioGlobalStdSet ();
IMPORT int ioHelp ();
IMPORT int ioMaxLinkLevels;
IMPORT int ioPxCreateOrOpen ();
IMPORT int ioTaskStdGet ();
IMPORT int ioTaskStdSet ();
IMPORT int ioctl ();
IMPORT int iosClose ();
IMPORT int iosCreate ();
IMPORT int iosDelete ();
IMPORT int iosDevAdd ();
IMPORT int iosDevCheck ();
IMPORT int iosDevDelCallback ();
IMPORT int iosDevDelDrv ();
IMPORT int iosDevDelete ();
IMPORT int iosDevFind ();
IMPORT int iosDevMatch ();
IMPORT int iosDevReplace ();
IMPORT int iosDevReplaceExt ();
IMPORT int iosDevResume ();
IMPORT int iosDevShow ();
IMPORT int iosDevSuspend ();
IMPORT int iosDrvInit ();
IMPORT int iosDrvInstall ();
IMPORT int iosDrvIoctl ();
IMPORT int iosDrvIoctlMemValSet ();
IMPORT int iosDrvRemove ();
IMPORT int iosDrvShow ();
IMPORT int iosDvList;
IMPORT int iosFdDevFind ();
IMPORT int iosFdDrvValue ();
IMPORT int iosFdEntryGet ();
IMPORT int iosFdEntryIoctl ();
IMPORT int iosFdEntryPool;
IMPORT int iosFdEntryReturn ();
IMPORT int iosFdEntrySet ();
IMPORT int iosFdFree ();
IMPORT int iosFdMap ();
IMPORT int iosFdMaxFiles ();
IMPORT int iosFdNew ();
IMPORT int iosFdSet ();
IMPORT int iosFdShow ();
IMPORT int iosFdTable;
IMPORT int iosFdTableLock ();
IMPORT int iosFdTableUnlock ();
IMPORT int iosFdValue ();
IMPORT int iosInit ();
IMPORT int iosIoctl ();
IMPORT int iosIoctlInternal ();
IMPORT int iosLibInitialized;
IMPORT int iosLock ();
IMPORT int iosMaxDrivers;
IMPORT int iosMaxFiles;
IMPORT int iosNextDevGet ();
IMPORT int iosNonRmvFdEntrySet ();
IMPORT int iosOpen ();
IMPORT int iosPathFdEntryIoctl ();
IMPORT int iosPathLibInit ();
IMPORT int iosPse52Mode;
IMPORT int iosPxLibInit ();
IMPORT int iosPxLibInitialized;
IMPORT int iosRead ();
IMPORT int iosRmvFdEntrySet ();
IMPORT int iosRmvLibInit ();
IMPORT int iosRtpDefPathGet ();
IMPORT int iosRtpDefPathSet ();
IMPORT int iosRtpDevCloseOrInvalidate ();
IMPORT int iosRtpFdEntryMap ();
IMPORT int iosRtpFdInvalid ();
IMPORT int iosRtpFdReserve ();
IMPORT int iosRtpFdReserveCntrl ();
IMPORT int iosRtpFdSetup ();
IMPORT int iosRtpFdShow ();
IMPORT int iosRtpFdTableGet ();
IMPORT int iosRtpFdTableSizeGet ();
IMPORT int iosRtpFdTblEntryGet ();
IMPORT int iosRtpFdUnmap2 ();
IMPORT int iosRtpIoTableSizeGet ();
IMPORT int iosRtpIoTableSizeSet ();
IMPORT int iosRtpLibInit ();
IMPORT int iosRtpTableSizeSet ();
IMPORT int iosShowInit ();
IMPORT int iosUnlock ();
IMPORT int iosWrite ();
IMPORT int ipAttach ();
IMPORT int ipDetach ();
IMPORT int ip_inaddr_any;
IMPORT int ipc_node;
IMPORT int ipcomNetTask ();
IMPORT int ipcom_accept ();
IMPORT int ipcom_accept_usr ();
IMPORT int ipcom_access ();
IMPORT int ipcom_allocate_fw_cache ();
IMPORT int ipcom_asctime_r_vxworks ();
IMPORT int ipcom_atomic_add ();
IMPORT int ipcom_atomic_add_and_return ();
IMPORT int ipcom_atomic_dec ();
IMPORT int ipcom_atomic_get ();
IMPORT int ipcom_atomic_inc ();
IMPORT int ipcom_atomic_set ();
IMPORT int ipcom_atomic_sub ();
IMPORT int ipcom_atomic_sub_and_return ();
IMPORT int ipcom_auth_chap_login ();
IMPORT int ipcom_auth_default_hash_rtn ();
IMPORT int ipcom_auth_hash ();
IMPORT int ipcom_auth_hash_get ();
IMPORT int ipcom_auth_hash_rtn_install ();
IMPORT int ipcom_auth_login ();
IMPORT int ipcom_auth_old_and_unsecure_hash_rtn ();
IMPORT int ipcom_auth_useradd ();
IMPORT int ipcom_auth_useradd_hash ();
IMPORT int ipcom_auth_userdel ();
IMPORT int ipcom_auth_userget ();
IMPORT int ipcom_auth_userlist ();
IMPORT int ipcom_bind ();
IMPORT int ipcom_bind_usr ();
IMPORT int ipcom_block_create ();
IMPORT int ipcom_block_delete ();
IMPORT int ipcom_block_post ();
IMPORT int ipcom_block_wait ();
IMPORT int ipcom_cache_line_size ();
IMPORT int ipcom_calloc ();
IMPORT int ipcom_chdir ();
IMPORT int ipcom_chmod ();
IMPORT int ipcom_clearenv ();
IMPORT int ipcom_closedir ();
IMPORT int ipcom_closelog ();
IMPORT int ipcom_cmd_cat ();
IMPORT int ipcom_cmd_cd ();
IMPORT int ipcom_cmd_cp ();
IMPORT int ipcom_cmd_date ();
IMPORT int ipcom_cmd_getenv ();
IMPORT int ipcom_cmd_if_caps_to_str ();
IMPORT int ipcom_cmd_if_flags_to_str ();
IMPORT int ipcom_cmd_key_to_str ();
IMPORT int ipcom_cmd_ls ();
IMPORT int ipcom_cmd_mkdir ();
IMPORT int ipcom_cmd_mv ();
IMPORT int ipcom_cmd_pwd ();
IMPORT int ipcom_cmd_rm ();
IMPORT int ipcom_cmd_rmdir ();
IMPORT int ipcom_cmd_setenv ();
IMPORT int ipcom_cmd_sockaddr_to_str ();
IMPORT int ipcom_cmd_str_to_key ();
IMPORT int ipcom_cmd_str_to_key2 ();
IMPORT int ipcom_cmd_time ();
IMPORT int ipcom_cmd_uuencode ();
IMPORT int ipcom_cmsg_nxthdr ();
IMPORT int ipcom_conf_max_link_hdr_size;
IMPORT int ipcom_conf_pkt_pool_buffer_alignment;
IMPORT int ipcom_conf_pkt_pool_buffer_extra_space;
IMPORT int ipcom_configure ();
IMPORT int ipcom_configure_reserved_cpus ();
IMPORT int ipcom_connect ();
IMPORT int ipcom_connect_usr ();
IMPORT int ipcom_cpu_is_online ();
IMPORT int ipcom_cpu_reserved_alloc ();
IMPORT int ipcom_cpu_reserved_free ();
IMPORT int ipcom_create ();
IMPORT int ipcom_ctime_r_vxworks ();
IMPORT int ipcom_dns;
IMPORT int ipcom_dns_init_ok;
IMPORT int ipcom_drv_eth_create ();
IMPORT int ipcom_drv_eth_exit ();
IMPORT int ipcom_drv_eth_init ();
IMPORT int ipcom_drv_eth_ip_attach ();
IMPORT int ipcom_errno_get ();
IMPORT int ipcom_errno_set ();
IMPORT int ipcom_fclose ();
IMPORT int ipcom_fdopen ();
IMPORT int ipcom_feof ();
IMPORT int ipcom_ferror ();
IMPORT int ipcom_fflush ();
IMPORT int ipcom_fileclose ();
IMPORT int ipcom_fileno ();
IMPORT int ipcom_fileopen ();
IMPORT int ipcom_fileread ();
IMPORT int ipcom_filewrite ();
IMPORT int ipcom_fopen ();
IMPORT int ipcom_forwarder_config_cache_size ();
IMPORT int ipcom_forwarder_config_fw_max ();
IMPORT int ipcom_forwarder_create_cf ();
IMPORT int ipcom_forwarder_current_core ();
IMPORT int ipcom_forwarder_fw_per_port ();
IMPORT int ipcom_forwarder_get_fwcache_util_level_limit ();
IMPORT int ipcom_forwarder_get_key_shift ();
IMPORT int ipcom_forwarder_get_nonfw_stats ();
IMPORT int ipcom_forwarder_get_ports_for_interface ();
IMPORT int ipcom_forwarder_ipsec_sa_cache_size;
IMPORT int ipcom_forwarder_ipsec_single_output_queue;
IMPORT int ipcom_forwarder_mtu ();
IMPORT int ipcom_forwarder_startup_delay ();
IMPORT int ipcom_fread ();
IMPORT int ipcom_free ();
IMPORT int ipcom_freeaddrinfo ();
IMPORT int ipcom_freeaddrinfo2 ();
IMPORT int ipcom_freeifaddrs ();
IMPORT int ipcom_fseek ();
IMPORT int ipcom_fstat ();
IMPORT int ipcom_ftell ();
IMPORT int ipcom_fwrite ();
IMPORT int ipcom_get_cpuid ();
IMPORT int ipcom_get_ip_if_name ();
IMPORT int ipcom_getaddrinfo ();
IMPORT int ipcom_getaddrinfo2 ();
IMPORT int ipcom_getcwd ();
IMPORT int ipcom_getenv ();
IMPORT int ipcom_getenv_as_int ();
IMPORT int ipcom_getenv_r ();
IMPORT int ipcom_gethostbyaddr ();
IMPORT int ipcom_gethostbyaddr_r ();
IMPORT int ipcom_gethostbyaddrlocal ();
IMPORT int ipcom_gethostbyname ();
IMPORT int ipcom_gethostbyname_r ();
IMPORT int ipcom_gethostbynamelocal ();
IMPORT int ipcom_getifaddrs ();
IMPORT int ipcom_getlogmask_on ();
IMPORT int ipcom_getnameinfo ();
IMPORT int ipcom_getnameinfo2 ();
IMPORT int ipcom_getopt ();
IMPORT int ipcom_getopt_clear ();
IMPORT int ipcom_getopt_clear_r ();
IMPORT int ipcom_getopt_data;
IMPORT int ipcom_getopt_r ();
IMPORT int ipcom_getpeername ();
IMPORT int ipcom_getpeername_usr ();
IMPORT int ipcom_getpid ();
IMPORT int ipcom_getprotobyname ();
IMPORT int ipcom_getprotobynumber ();
IMPORT int ipcom_getservbyname ();
IMPORT int ipcom_getservbyport ();
IMPORT int ipcom_getsockaddrbyaddr ();
IMPORT int ipcom_getsockaddrbyaddrname ();
IMPORT int ipcom_getsockname ();
IMPORT int ipcom_getsockname_usr ();
IMPORT int ipcom_getsockopt ();
IMPORT int ipcom_getsockopt_usr ();
IMPORT int ipcom_gettimeofday ();
IMPORT int ipcom_h_errno;
IMPORT int ipcom_hash_add ();
IMPORT int ipcom_hash_delete ();
IMPORT int ipcom_hash_for_each ();
IMPORT int ipcom_hash_get ();
IMPORT int ipcom_hash_new ();
IMPORT int ipcom_hash_remove ();
IMPORT int ipcom_hash_update ();
IMPORT int ipcom_heap_sort ();
IMPORT int ipcom_if_attach ();
IMPORT int ipcom_if_attach_and_lock ();
IMPORT int ipcom_if_changelinkaddr ();
IMPORT int ipcom_if_changemtu ();
IMPORT int ipcom_if_changename ();
IMPORT int ipcom_if_detach ();
IMPORT int ipcom_if_free ();
IMPORT int ipcom_if_freenameindex ();
IMPORT int ipcom_if_indextoname ();
IMPORT int ipcom_if_malloc ();
IMPORT int ipcom_if_nameindex ();
IMPORT int ipcom_if_nametoindex ();
IMPORT int ipcom_if_nametonetif ();
IMPORT int ipcom_ima_stack_task ();
IMPORT int ipcom_in_checksum ();
IMPORT int ipcom_in_checksum_finish ();
IMPORT int ipcom_in_checksum_memcpy ();
IMPORT int ipcom_in_checksum_update ();
IMPORT int ipcom_inet_addr ();
IMPORT int ipcom_inet_aton ();
IMPORT int ipcom_inet_ntoa ();
IMPORT int ipcom_inet_ntop ();
IMPORT int ipcom_inet_pton ();
IMPORT int ipcom_init_config_vars ();
IMPORT int ipcom_initd ();
IMPORT int ipcom_interrupt_disable ();
IMPORT int ipcom_interrupt_enable ();
IMPORT int ipcom_ipc_close ();
IMPORT int ipcom_ipc_free ();
IMPORT int ipcom_ipc_install ();
IMPORT int ipcom_ipc_isopen ();
IMPORT int ipcom_ipc_malloc ();
IMPORT int ipcom_ipc_open ();
IMPORT int ipcom_ipc_receive ();
IMPORT int ipcom_ipc_send ();
IMPORT int ipcom_ipc_size ();
IMPORT int ipcom_ipc_uninstall ();
IMPORT int ipcom_ipd_datamsg ();
IMPORT int ipcom_ipd_exit ();
IMPORT int ipcom_ipd_init ();
IMPORT int ipcom_ipd_input ();
IMPORT int ipcom_ipd_input_process ();
IMPORT int ipcom_ipd_kill ();
IMPORT int ipcom_ipd_products;
IMPORT int ipcom_ipd_read ();
IMPORT int ipcom_ipd_reconfigure ();
IMPORT int ipcom_ipd_send ();
IMPORT int ipcom_ipd_sendmsg ();
IMPORT int ipcom_ipd_start ();
IMPORT int ipcom_ipproto_name ();
IMPORT int ipcom_is_pid_valid ();
IMPORT int ipcom_is_stack_task ();
IMPORT int ipcom_job_queue_init ();
IMPORT int ipcom_job_queue_pipe_schedule ();
IMPORT int ipcom_job_queue_schedule ();
IMPORT int ipcom_job_queue_schedule_singleton ();
IMPORT int ipcom_job_queue_schedule_singleton_delayed ();
IMPORT int ipcom_job_queue_singleton_delete ();
IMPORT int ipcom_job_queue_singleton_new ();
IMPORT int ipcom_list_first ();
IMPORT int ipcom_list_init ();
IMPORT int ipcom_list_insert_after ();
IMPORT int ipcom_list_insert_before ();
IMPORT int ipcom_list_insert_first ();
IMPORT int ipcom_list_insert_last ();
IMPORT int ipcom_list_last ();
IMPORT int ipcom_list_next ();
IMPORT int ipcom_list_prev ();
IMPORT int ipcom_list_remove ();
IMPORT int ipcom_list_unlink_head ();
IMPORT int ipcom_listen ();
IMPORT int ipcom_listen_usr ();
IMPORT int ipcom_lseek ();
IMPORT int ipcom_malloc ();
IMPORT int ipcom_mask_to_prefixlen ();
IMPORT int ipcom_mb ();
IMPORT int ipcom_mcmd_route ();
IMPORT int ipcom_memory_pool_new ();
IMPORT int ipcom_microtime ();
IMPORT int ipcom_millisleep ();
IMPORT int ipcom_mkdir ();
IMPORT int ipcom_mutex_create ();
IMPORT int ipcom_mutex_delete ();
IMPORT int ipcom_mutex_lock ();
IMPORT int ipcom_mutex_unlock ();
IMPORT int ipcom_null_pool_create;
IMPORT int ipcom_num_configured_cpus ();
IMPORT int ipcom_num_online_cpus ();
IMPORT int ipcom_once ();
IMPORT int ipcom_once_mutex;
IMPORT int ipcom_opendir ();
IMPORT int ipcom_openlog ();
IMPORT int ipcom_parse_argstr ();
IMPORT int ipcom_pipe_attr_init ();
IMPORT int ipcom_pipe_free ();
IMPORT int ipcom_pipe_generic_create ();
IMPORT int ipcom_pipe_job_queue_create ();
IMPORT int ipcom_pipe_lockless_create ();
IMPORT int ipcom_pipe_new ();
IMPORT int ipcom_pipe_register_type ();
IMPORT int ipcom_pipe_tv_zero;
IMPORT int ipcom_pkt_alloc_info ();
IMPORT int ipcom_pkt_copy_info ();
IMPORT int ipcom_pkt_create ();
IMPORT int ipcom_pkt_free ();
IMPORT int ipcom_pkt_get_data ();
IMPORT int ipcom_pkt_get_info ();
IMPORT int ipcom_pkt_get_info_safe ();
IMPORT int ipcom_pkt_get_length ();
IMPORT int ipcom_pkt_hdrspace ();
IMPORT int ipcom_pkt_input ();
IMPORT int ipcom_pkt_input_queue ();
IMPORT int ipcom_pkt_make_linear ();
IMPORT int ipcom_pkt_malloc ();
IMPORT int ipcom_pkt_output_done ();
IMPORT int ipcom_pkt_set_info ();
IMPORT int ipcom_pktbuf_free ();
IMPORT int ipcom_port;
IMPORT int ipcom_port_pkt_hdr_extra_size;
IMPORT int ipcom_pqueue_delete ();
IMPORT int ipcom_pqueue_for_each ();
IMPORT int ipcom_pqueue_get ();
IMPORT int ipcom_pqueue_get_next ();
IMPORT int ipcom_pqueue_insert ();
IMPORT int ipcom_pqueue_new ();
IMPORT int ipcom_pqueue_nop_store_index ();
IMPORT int ipcom_pqueue_remove ();
IMPORT int ipcom_pqueue_remove_next ();
IMPORT int ipcom_pqueue_size ();
IMPORT int ipcom_preempt_disable ();
IMPORT int ipcom_preempt_enable ();
IMPORT int ipcom_priority_map;
IMPORT int ipcom_proc_acreate ();
IMPORT int ipcom_proc_attr_init ();
IMPORT int ipcom_proc_cpu_affinity_clr ();
IMPORT int ipcom_proc_cpu_affinity_get ();
IMPORT int ipcom_proc_cpu_affinity_set ();
IMPORT int ipcom_proc_cpu_affinity_set_all ();
IMPORT int ipcom_proc_create ();
IMPORT int ipcom_proc_exit ();
IMPORT int ipcom_proc_find ();
IMPORT int ipcom_proc_free ();
IMPORT int ipcom_proc_getprio ();
IMPORT int ipcom_proc_init ();
IMPORT int ipcom_proc_malloc ();
IMPORT int ipcom_proc_self ();
IMPORT int ipcom_proc_setprio ();
IMPORT int ipcom_proc_vr_get ();
IMPORT int ipcom_proc_vr_set ();
IMPORT int ipcom_proc_yield ();
IMPORT int ipcom_proxy_sys_var ();
IMPORT int ipcom_rand ();
IMPORT int ipcom_random ();
IMPORT int ipcom_random_init ();
IMPORT int ipcom_random_seed_state ();
IMPORT int ipcom_readdir ();
IMPORT int ipcom_realloc ();
IMPORT int ipcom_recv ();
IMPORT int ipcom_recv_usr ();
IMPORT int ipcom_recvfrom ();
IMPORT int ipcom_recvfrom_usr ();
IMPORT int ipcom_recvmsg ();
IMPORT int ipcom_recvmsg_usr ();
IMPORT int ipcom_register_dev_name_mapping ();
IMPORT int ipcom_rename ();
IMPORT int ipcom_reserve_fw_cpu ();
IMPORT int ipcom_rewind ();
IMPORT int ipcom_rmb ();
IMPORT int ipcom_rmdir ();
IMPORT int ipcom_route_add ();
IMPORT int ipcom_route_first_entry ();
IMPORT int ipcom_route_free_table ();
IMPORT int ipcom_route_init_subtree_mask ();
IMPORT int ipcom_route_key_cmp ();
IMPORT int ipcom_route_lookup ();
IMPORT int ipcom_route_new_table ();
IMPORT int ipcom_route_next_entry ();
IMPORT int ipcom_route_remove ();
IMPORT int ipcom_route_walk_tree ();
IMPORT int ipcom_route_walk_tree_backwards ();
IMPORT int ipcom_rtp_tcb_index_get_fd ();
IMPORT int ipcom_run_cmd ();
IMPORT int ipcom_sem_create ();
IMPORT int ipcom_sem_delete ();
IMPORT int ipcom_sem_flush ();
IMPORT int ipcom_sem_getvalue ();
IMPORT int ipcom_sem_interrupt_flush ();
IMPORT int ipcom_sem_interrupt_post ();
IMPORT int ipcom_sem_post ();
IMPORT int ipcom_sem_wait ();
IMPORT int ipcom_send ();
IMPORT int ipcom_send_usr ();
IMPORT int ipcom_sendmsg ();
IMPORT int ipcom_sendmsg_usr ();
IMPORT int ipcom_sendto ();
IMPORT int ipcom_sendto_usr ();
IMPORT int ipcom_set_add ();
IMPORT int ipcom_set_clone ();
IMPORT int ipcom_set_contains ();
IMPORT int ipcom_set_delete ();
IMPORT int ipcom_set_equal ();
IMPORT int ipcom_set_for_each ();
IMPORT int ipcom_set_intersection ();
IMPORT int ipcom_set_new ();
IMPORT int ipcom_set_remove ();
IMPORT int ipcom_set_remove_all ();
IMPORT int ipcom_set_subtract ();
IMPORT int ipcom_set_union ();
IMPORT int ipcom_setenv ();
IMPORT int ipcom_setenv_as_int ();
IMPORT int ipcom_sethostname ();
IMPORT int ipcom_setlogfile ();
IMPORT int ipcom_setlogmask_on ();
IMPORT int ipcom_setlogudp ();
IMPORT int ipcom_setsockopt ();
IMPORT int ipcom_setsockopt_usr ();
IMPORT int ipcom_settimeofday ();
IMPORT int ipcom_shell_add_cmd ();
IMPORT int ipcom_shell_cmd_head;
IMPORT int ipcom_shell_find_cmd ();
IMPORT int ipcom_shell_find_cmd_hook;
IMPORT int ipcom_shell_fread ();
IMPORT int ipcom_shell_fwrite ();
IMPORT int ipcom_shell_remove_cmd ();
IMPORT int ipcom_shutdown ();
IMPORT int ipcom_shutdown_usr ();
IMPORT int ipcom_slab_add ();
IMPORT int ipcom_slab_alloc_from ();
IMPORT int ipcom_slab_alloc_try ();
IMPORT int ipcom_slab_free ();
IMPORT int ipcom_slab_get_objects_per_slab ();
IMPORT int ipcom_slab_memory_pool_list;
IMPORT int ipcom_slab_new ();
IMPORT int ipcom_slab_once;
IMPORT int ipcom_sleep ();
IMPORT int ipcom_sockaddr_to_prefixlen ();
IMPORT int ipcom_socket ();
IMPORT int ipcom_socket_usr ();
IMPORT int ipcom_socketclose ();
IMPORT int ipcom_socketclose_usr ();
IMPORT int ipcom_socketioctl ();
IMPORT int ipcom_socketioctl_usr ();
IMPORT int ipcom_socketread ();
IMPORT int ipcom_socketread_usr ();
IMPORT int ipcom_socketselect ();
IMPORT int ipcom_socketselect_usr ();
IMPORT int ipcom_socketwrite ();
IMPORT int ipcom_socketwrite_usr ();
IMPORT int ipcom_socketwritev ();
IMPORT int ipcom_socketwritev_usr ();
IMPORT int ipcom_spinlock_create ();
IMPORT int ipcom_spinlock_delete ();
IMPORT int ipcom_spinlock_lock ();
IMPORT int ipcom_spinlock_unlock ();
IMPORT int ipcom_srand ();
IMPORT int ipcom_srandom ();
IMPORT int ipcom_stackd_init ();
IMPORT int ipcom_start ();
IMPORT int ipcom_stat ();
IMPORT int ipcom_stderr ();
IMPORT int ipcom_stdin ();
IMPORT int ipcom_stdout ();
IMPORT int ipcom_str_in_list ();
IMPORT int ipcom_strcasecmp ();
IMPORT int ipcom_strerror ();
IMPORT int ipcom_strerror_r ();
IMPORT int ipcom_strncasecmp ();
IMPORT int ipcom_sysctl ();
IMPORT int ipcom_syslog ();
IMPORT int ipcom_syslog_facility_names;
IMPORT int ipcom_syslog_priority_names;
IMPORT int ipcom_syslogd_init ();
IMPORT int ipcom_sysvar_ext_setv ();
IMPORT int ipcom_sysvar_for_each ();
IMPORT int ipcom_sysvar_get ();
IMPORT int ipcom_sysvar_get0 ();
IMPORT int ipcom_sysvar_get_as_int ();
IMPORT int ipcom_sysvar_get_as_int0 ();
IMPORT int ipcom_sysvar_get_descriptive_int0 ();
IMPORT int ipcom_sysvar_getvr ();
IMPORT int ipcom_sysvar_set ();
IMPORT int ipcom_sysvar_set0 ();
IMPORT int ipcom_sysvar_set_tree ();
IMPORT int ipcom_sysvar_setv ();
IMPORT int ipcom_sysvar_unset ();
IMPORT int ipcom_tmo_cancel ();
IMPORT int ipcom_tmo_get ();
IMPORT int ipcom_tmo_request ();
IMPORT int ipcom_tmo_reset ();
IMPORT int ipcom_umask ();
IMPORT int ipcom_unlink ();
IMPORT int ipcom_unsetenv ();
IMPORT int ipcom_usr_create ();
IMPORT int ipcom_version;
IMPORT int ipcom_vsyslog ();
IMPORT int ipcom_vxshell_add_cmd ();
IMPORT int ipcom_vxshell_add_cmd_hook;
IMPORT int ipcom_vxworks_pkt_pool_hdr_ctor ();
IMPORT int ipcom_vxworks_proc_free ();
IMPORT int ipcom_vxworks_rtp_del_hook_add ();
IMPORT int ipcom_vxworks_task_del_hook ();
IMPORT int ipcom_wait_queue_add_current_proc ();
IMPORT int ipcom_wait_queue_init ();
IMPORT int ipcom_wait_queue_is_empty ();
IMPORT int ipcom_wait_queue_wakeup_all_procs ();
IMPORT int ipcom_wait_queue_wakeup_one_proc ();
IMPORT int ipcom_windnet_socketwritev ();
IMPORT int ipcom_windnet_socklib_init ();
IMPORT int ipcom_windnet_socklib_init_cb ();
IMPORT int ipcom_windnet_socklib_sock_size ();
IMPORT int ipcom_windnet_socklib_socket_free ();
IMPORT int ipcom_windnet_socklib_socket_init ();
IMPORT int ipcom_wmb ();
IMPORT int ipcom_wv_event_2 ();
IMPORT int ipcom_wv_marker_1 ();
IMPORT int ipcom_wv_marker_2 ();
IMPORT int ipftps_authenticate ();
IMPORT int ipftps_conf_sysvar;
IMPORT int ipftps_configure ();
IMPORT int ipftps_create ();
IMPORT int ipftps_main ();
IMPORT int ipftps_session ();
IMPORT int ipftps_start ();
IMPORT int ipftps_version ();
IMPORT int ipmcrypto_MD5_Final ();
IMPORT int ipmcrypto_MD5_Init ();
IMPORT int ipmcrypto_MD5_Update ();
IMPORT int ipmcrypto_md5_calculate ();
IMPORT int ipnet;
IMPORT int ipnet_arp_ioctl ();
IMPORT int ipnet_arp_request ();
IMPORT int ipnet_arp_set_state ();
IMPORT int ipnet_bit_array_clr ();
IMPORT int ipnet_bit_array_test_and_set ();
IMPORT int ipnet_bool_map;
IMPORT int ipnet_boot_config ();
IMPORT int ipnet_cmd_if_type_to_str ();
IMPORT int ipnet_cmd_ifconfig ();
IMPORT int ipnet_cmd_ifconfig_hook;
IMPORT int ipnet_cmd_init_addrs ();
IMPORT int ipnet_cmd_msec_since ();
IMPORT int ipnet_cmd_qc_hook;
IMPORT int ipnet_cmd_route_hook;
IMPORT int ipnet_cmd_rt_flags_to_str ();
IMPORT int ipnet_cmd_rt_flags_to_str_short ();
IMPORT int ipnet_conf_boot_cmd;
IMPORT int ipnet_conf_cache_bufsiz;
IMPORT int ipnet_conf_inq_max;
IMPORT int ipnet_conf_interfaces;
IMPORT int ipnet_conf_ip4_min_mtu;
IMPORT int ipnet_conf_link_layer;
IMPORT int ipnet_conf_max_dgram_frag_list_len;
IMPORT int ipnet_conf_max_reassembly_list_len;
IMPORT int ipnet_conf_max_sockets;
IMPORT int ipnet_conf_memory_limit;
IMPORT int ipnet_conf_reassembly_timeout;
IMPORT int ipnet_conf_sysvar_ext;
IMPORT int ipnet_configure ();
IMPORT int ipnet_create ();
IMPORT int ipnet_create_reassembled_packet ();
IMPORT int ipnet_ctrl ();
IMPORT int ipnet_ctrl_sig ();
IMPORT int ipnet_do_close ();
IMPORT int ipnet_eth_add_hdr ();
IMPORT int ipnet_eth_if_init ();
IMPORT int ipnet_eth_update_mib2_lastchange ();
IMPORT int ipnet_finish_transport_checksum ();
IMPORT int ipnet_flags;
IMPORT int ipnet_fragment_packet ();
IMPORT int ipnet_get_sock ();
IMPORT int ipnet_has_priv ();
IMPORT int ipnet_icmp4_dst_create_rt ();
IMPORT int ipnet_icmp4_param_init ();
IMPORT int ipnet_icmp4_send ();
IMPORT int ipnet_if_can_detach ();
IMPORT int ipnet_if_clean ();
IMPORT int ipnet_if_clean_ppp_peer ();
IMPORT int ipnet_if_clean_snd_queue ();
IMPORT int ipnet_if_detach ();
IMPORT int ipnet_if_drv_ioctl ();
IMPORT int ipnet_if_drv_output ();
IMPORT int ipnet_if_free ();
IMPORT int ipnet_if_get_index_array ();
IMPORT int ipnet_if_indextonetif ();
IMPORT int ipnet_if_init ();
IMPORT int ipnet_if_init_ppp_peer ();
IMPORT int ipnet_if_link_ioctl ();
IMPORT int ipnet_if_nametonetif ();
IMPORT int ipnet_if_output ();
IMPORT int ipnet_if_set_ipv4_ppp_peer ();
IMPORT int ipnet_if_to_sockaddr_dl ();
IMPORT int ipnet_ifconfig_if_change_state ();
IMPORT int ipnet_igmpv3_report_change ();
IMPORT int ipnet_increase_hdr_space ();
IMPORT int ipnet_ioctl_move_if_rt_to_vr ();
IMPORT int ipnet_ip4_add_addr ();
IMPORT int ipnet_ip4_add_addr2 ();
IMPORT int ipnet_ip4_add_route_table ();
IMPORT int ipnet_ip4_addr_to_sockaddr ();
IMPORT int ipnet_ip4_change_addr_mask ();
IMPORT int ipnet_ip4_configure_route_table ();
IMPORT int ipnet_ip4_get_addr_entry ();
IMPORT int ipnet_ip4_get_addr_type ();
IMPORT int ipnet_ip4_get_addr_type2 ();
IMPORT int ipnet_ip4_get_mss ();
IMPORT int ipnet_ip4_get_src_addr ();
IMPORT int ipnet_ip4_init ();
IMPORT int ipnet_ip4_input ();
IMPORT int ipnet_ip4_insert_addr_cache ();
IMPORT int ipnet_ip4_is_part_of_same_pkt ();
IMPORT int ipnet_ip4_kioevent ();
IMPORT int ipnet_ip4_lladdr_conflict ();
IMPORT int ipnet_ip4_netif_get_subbrd ();
IMPORT int ipnet_ip4_output ();
IMPORT int ipnet_ip4_remove_addr ();
IMPORT int ipnet_ip4_remove_addr_cache ();
IMPORT int ipnet_ip4_rfc1256_mode_update ();
IMPORT int ipnet_ip4_schedule_host_unreachable ();
IMPORT int ipnet_ip4_sendto ();
IMPORT int ipnet_is_loopback ();
IMPORT int ipnet_is_sock_exceptional ();
IMPORT int ipnet_is_sock_readable ();
IMPORT int ipnet_is_sock_writable ();
IMPORT int ipnet_is_stack_task ();
IMPORT int ipnet_kioevent ();
IMPORT int ipnet_loopback_attach ();
IMPORT int ipnet_loopback_get_netif ();
IMPORT int ipnet_loopback_if_init ();
IMPORT int ipnet_mcast_build_if_filter ();
IMPORT int ipnet_mcast_build_source_change_report ();
IMPORT int ipnet_mcast_clear ();
IMPORT int ipnet_mcast_free ();
IMPORT int ipnet_mcast_init ();
IMPORT int ipnet_mcast_report_finish ();
IMPORT int ipnet_mcast_schedule_membership_report ();
IMPORT int ipnet_mcast_time_to_msec ();
IMPORT int ipnet_msec_now ();
IMPORT int ipnet_neigh_free_all_pending ();
IMPORT int ipnet_neigh_init ();
IMPORT int ipnet_neigh_queue_until_resolved ();
IMPORT int ipnet_neigh_send_all_pending ();
IMPORT int ipnet_neigh_set_state ();
IMPORT int ipnet_neigh_timeout ();
IMPORT int ipnet_netif_change_flags ();
IMPORT int ipnet_next_ephemeral_port ();
IMPORT int ipnet_packet_getsockopt ();
IMPORT int ipnet_packet_input ();
IMPORT int ipnet_packet_setsockopt ();
IMPORT int ipnet_pcap_ioctl ();
IMPORT int ipnet_ping_stat_init ();
IMPORT int ipnet_ping_stat_receive ();
IMPORT int ipnet_ping_stat_report ();
IMPORT int ipnet_ping_stat_transmit ();
IMPORT int ipnet_pipe_create ();
IMPORT int ipnet_pkt_clone ();
IMPORT int ipnet_pkt_input ();
IMPORT int ipnet_pkt_pool_hdr_count_hint ();
IMPORT int ipnet_pkt_pool_hdr_ctor_func;
IMPORT int ipnet_pkt_pool_init ();
IMPORT int ipnet_pkt_pool_slab_desc;
IMPORT int ipnet_pkt_queue_delete ();
IMPORT int ipnet_pkt_queue_fifo_template ();
IMPORT int ipnet_pkt_queue_init ();
IMPORT int ipnet_pkt_queue_new ();
IMPORT int ipnet_ppp_if_init ();
IMPORT int ipnet_qc_unif_config_hook;
IMPORT int ipnet_queue_received_packet ();
IMPORT int ipnet_raw_input ();
IMPORT int ipnet_reassembly ();
IMPORT int ipnet_release_sock ();
IMPORT int ipnet_resume_stack ();
IMPORT int ipnet_route_add ();
IMPORT int ipnet_route_add_cloned_rt ();
IMPORT int ipnet_route_add_table ();
IMPORT int ipnet_route_apply_mask ();
IMPORT int ipnet_route_cache_invalidate ();
IMPORT int ipnet_route_create_llinfo_entry ();
IMPORT int ipnet_route_create_mask ();
IMPORT int ipnet_route_delete ();
IMPORT int ipnet_route_delete2 ();
IMPORT int ipnet_route_delete_name ();
IMPORT int ipnet_route_delete_table ();
IMPORT int ipnet_route_delete_vr ();
IMPORT int ipnet_route_first_entry ();
IMPORT int ipnet_route_for_each_data_init ();
IMPORT int ipnet_route_get_name ();
IMPORT int ipnet_route_get_rtab ();
IMPORT int ipnet_route_get_table_ids ();
IMPORT int ipnet_route_has_changed ();
IMPORT int ipnet_route_has_expired ();
IMPORT int ipnet_route_is_virtual_router_valid ();
IMPORT int ipnet_route_key_cmp ();
IMPORT int ipnet_route_key_to_sockaddr ();
IMPORT int ipnet_route_lock ();
IMPORT int ipnet_route_lookup ();
IMPORT int ipnet_route_lookup_ecmp ();
IMPORT int ipnet_route_lookup_ip4_dont_route ();
IMPORT int ipnet_route_next_entry ();
IMPORT int ipnet_route_notify_func ();
IMPORT int ipnet_route_policy_get_rule_chain ();
IMPORT int ipnet_route_policy_ioctl ();
IMPORT int ipnet_route_raw_lookup ();
IMPORT int ipnet_route_raw_lookup2 ();
IMPORT int ipnet_route_remove_all ();
IMPORT int ipnet_route_remove_all_cb_for_each_entry ();
IMPORT int ipnet_route_rotate_gateways ();
IMPORT int ipnet_route_set_lifetime ();
IMPORT int ipnet_route_set_name ();
IMPORT int ipnet_route_set_rtab ();
IMPORT int ipnet_route_sockaddr_to_key ();
IMPORT int ipnet_route_unlock ();
IMPORT int ipnet_route_vr_and_table_from_name ();
IMPORT int ipnet_route_walk_tree ();
IMPORT int ipnet_routesock_addr_add ();
IMPORT int ipnet_routesock_addr_delete ();
IMPORT int ipnet_routesock_if_announce ();
IMPORT int ipnet_routesock_if_change ();
IMPORT int ipnet_routesock_rt_add ();
IMPORT int ipnet_routesock_rt_change ();
IMPORT int ipnet_routesock_rt_delete ();
IMPORT int ipnet_routesock_rt_miss ();
IMPORT int ipnet_routesock_rt_redirect ();
IMPORT int ipnet_routesock_rt_resolve ();
IMPORT int ipnet_schedule_pkt_report ();
IMPORT int ipnet_sec_now ();
IMPORT int ipnet_sig_free ();
IMPORT int ipnet_sock_add_to_rx_cache ();
IMPORT int ipnet_sock_alloc_private_data ();
IMPORT int ipnet_sock_bind ();
IMPORT int ipnet_sock_bind_addr_removed ();
IMPORT int ipnet_sock_bind_to_port ();
IMPORT int ipnet_sock_change_addr_entry ();
IMPORT int ipnet_sock_create_lookup_tables ();
IMPORT int ipnet_sock_data_avail ();
IMPORT int ipnet_sock_drop_all_multicast_memberships ();
IMPORT int ipnet_sock_free ();
IMPORT int ipnet_sock_get_bound_socket_size ();
IMPORT int ipnet_sock_get_ops ();
IMPORT int ipnet_sock_get_route ();
IMPORT int ipnet_sock_has_waiting_writers ();
IMPORT int ipnet_sock_ip4_get_mcast_data ();
IMPORT int ipnet_sock_ip4_get_ops ();
IMPORT int ipnet_sock_ip4_lookup ();
IMPORT int ipnet_sock_ip4_mcast_delete_data ();
IMPORT int ipnet_sock_ip4_register ();
IMPORT int ipnet_sock_packet_register ();
IMPORT int ipnet_sock_pkt_drain ();
IMPORT int ipnet_sock_register_ops ();
IMPORT int ipnet_sock_route_register ();
IMPORT int ipnet_sock_rx_cache_invalidate ();
IMPORT int ipnet_sock_set_reachable ();
IMPORT int ipnet_sock_set_unreachable ();
IMPORT int ipnet_sock_tcp_register ();
IMPORT int ipnet_sock_udp_register ();
IMPORT int ipnet_sock_unbind ();
IMPORT int ipnet_sock_unconnect ();
IMPORT int ipnet_sock_update_reuse ();
IMPORT int ipnet_sockopt_ip4_addr_to_netif ();
IMPORT int ipnet_softirq_init ();
IMPORT int ipnet_softirq_run ();
IMPORT int ipnet_softirq_schedule ();
IMPORT int ipnet_start ();
IMPORT int ipnet_stats_tcp_established ();
IMPORT int ipnet_suspend_stack ();
IMPORT int ipnet_sys_accept ();
IMPORT int ipnet_sys_bind ();
IMPORT int ipnet_sys_connect ();
IMPORT int ipnet_sys_get_ancillary_data ();
IMPORT int ipnet_sys_getname ();
IMPORT int ipnet_sys_getsockopt ();
IMPORT int ipnet_sys_if_attach ();
IMPORT int ipnet_sys_if_changelinkaddr ();
IMPORT int ipnet_sys_if_changemtu ();
IMPORT int ipnet_sys_if_changename ();
IMPORT int ipnet_sys_if_detach ();
IMPORT int ipnet_sys_if_free ();
IMPORT int ipnet_sys_if_indexname ();
IMPORT int ipnet_sys_if_malloc ();
IMPORT int ipnet_sys_if_nametonetif ();
IMPORT int ipnet_sys_listen ();
IMPORT int ipnet_sys_poll ();
IMPORT int ipnet_sys_poll_async ();
IMPORT int ipnet_sys_poll_done ();
IMPORT int ipnet_sys_sendmsg ();
IMPORT int ipnet_sys_setsockopt ();
IMPORT int ipnet_sys_shutdown ();
IMPORT int ipnet_sys_socket ();
IMPORT int ipnet_sys_socketclose ();
IMPORT int ipnet_sys_socketioctl ();
IMPORT int ipnet_sys_sysctl ();
IMPORT int ipnet_sysctl_create_ifinfo ();
IMPORT int ipnet_sysctl_if_add_addrs_one ();
IMPORT int ipnet_sysvar_netif_get_as_int ();
IMPORT int ipnet_sysvar_netif_get_as_int_ex ();
IMPORT int ipnet_timeout_cancel ();
IMPORT int ipnet_timeout_msec_until ();
IMPORT int ipnet_timeout_schedule ();
IMPORT int ipnet_timeval_to_msec ();
IMPORT int ipnet_udp_input ();
IMPORT int ipnet_usr_sock_get_ops ();
IMPORT int ipnet_usr_sock_get_pipe ();
IMPORT int ipnet_usr_sock_get_response_pipe ();
IMPORT int ipnet_usr_sock_get_route_cache_id ();
IMPORT int ipnet_usr_sock_init ();
IMPORT int ipnet_usr_sock_init_sig ();
IMPORT int ipnet_usr_sock_recvmsg ();
IMPORT int ipnet_usr_sock_wait_until_writable ();
IMPORT int ipnet_version ();
IMPORT int ipstack_ifconfig_print_info ();
IMPORT int iptcp;
IMPORT int iptcp_accept ();
IMPORT int iptcp_change_state_global ();
IMPORT int iptcp_close ();
IMPORT int iptcp_conf_default_backlog;
IMPORT int iptcp_configure ();
IMPORT int iptcp_connect ();
IMPORT int iptcp_create ();
IMPORT int iptcp_drop_connection ();
IMPORT int iptcp_get_rto ();
IMPORT int iptcp_get_state ();
IMPORT int iptcp_getsockopt ();
IMPORT int iptcp_icmp4_report ();
IMPORT int iptcp_input ();
IMPORT int iptcp_ioctl ();
IMPORT int iptcp_listen ();
IMPORT int iptcp_pkt_drain ();
IMPORT int iptcp_send ();
IMPORT int iptcp_send_reset ();
IMPORT int iptcp_setsockopt ();
IMPORT int iptcp_shutdown ();
IMPORT int iptcp_sock_free ();
IMPORT int iptcp_sock_init ();
IMPORT int iptcp_start ();
IMPORT int iptcp_usr_recv ();
IMPORT int iptcp_version ();
IMPORT int iptcp_window_update ();
IMPORT int irint ();
IMPORT int iround ();
IMPORT int irq_isr ();
IMPORT int isalnum ();
IMPORT int isalpha ();
IMPORT int isatty ();
IMPORT int iscntrl ();
IMPORT int isdigit ();
IMPORT int isgraph ();
IMPORT int islower ();
IMPORT int isprint ();
IMPORT int ispunct ();
IMPORT int isrDeferIsrReroute ();
IMPORT int isrDeferJobAdd ();
IMPORT int isrDeferLibInit ();
IMPORT int isrDeferQueueGet ();
IMPORT int isrIdCurrent;
IMPORT int isrJobPool;
IMPORT int isspace ();
IMPORT int isupper ();
IMPORT int isxdigit ();
IMPORT int jobAdd ();
IMPORT int jobExcAdd ();
IMPORT int jobLibInit ();
IMPORT int jobLibTaskInstalled;
IMPORT int jobQueueCreate ();
IMPORT int jobQueueInit ();
IMPORT int jobQueueLibInit ();
IMPORT int jobQueuePost ();
IMPORT int jobQueuePriorityMask ();
IMPORT int jobQueueProcess ();
IMPORT int jobQueueProcessFunc;
IMPORT int jobQueueStdJobsAlloc ();
IMPORT int jobQueueStdPoolInit ();
IMPORT int jobQueueStdPost ();
IMPORT int jobQueueTask ();
IMPORT int kbdConvertCharSet_desc;
IMPORT int kbdCurrConSet_desc;
IMPORT int kbdInit_desc;
IMPORT int kbdLedGet_desc;
IMPORT int kbdLedSet_desc;
IMPORT int kbdModeSet_desc;
IMPORT int kbdNumSet_desc;
IMPORT int kernSysctlInit ();
IMPORT int kern_node;
IMPORT int kernelBaseInit ();
IMPORT int kernelCpuEnable ();
IMPORT int kernelId;
IMPORT int kernelIdGet ();
IMPORT int kernelInit ();
IMPORT int kernelIsCpuIdle ();
IMPORT int kernelIsIdle;
IMPORT int kernelIsSystemIdle ();
IMPORT int kernelModuleListId;
IMPORT int kernelObjClassId;
IMPORT int kernelRoundRobinInstall ();
IMPORT int kernelState;
IMPORT int kernelTimeSlice ();
IMPORT int kernelVersion ();
IMPORT int kernel_sysctl ();
IMPORT int kill ();
IMPORT int l ();
IMPORT int labs ();
IMPORT int lastCmd;
IMPORT int lastLoader;
IMPORT int lcd_test ();
IMPORT int ld ();
IMPORT int ldCommonMatchAll;
IMPORT int ldexp ();
IMPORT int ldiv ();
IMPORT int ldiv_r ();
IMPORT int ledBeep ();
IMPORT int ledBwdFind ();
IMPORT int ledCDelete ();
IMPORT int ledChange ();
IMPORT int ledClose ();
IMPORT int ledComplete ();
IMPORT int ledCompletionSet ();
IMPORT int ledControl ();
IMPORT int ledDfltComplete ();
IMPORT int ledFwdFind ();
IMPORT int ledHistCurrentNumGet ();
IMPORT int ledHistFind ();
IMPORT int ledHistNextGet ();
IMPORT int ledHistNumGet ();
IMPORT int ledHistPrevGet ();
IMPORT int ledHistResize ();
IMPORT int ledHistoryAdd ();
IMPORT int ledHistoryClone ();
IMPORT int ledHistoryCreate ();
IMPORT int ledHistoryFree ();
IMPORT int ledHistoryLineAllocate ();
IMPORT int ledHistorySet ();
IMPORT int ledInactivityDelaySet ();
IMPORT int ledLibInit ();
IMPORT int ledModeDefaultNameGet ();
IMPORT int ledModeNameGet ();
IMPORT int ledModeRegister ();
IMPORT int ledModeSet ();
IMPORT int ledNWrite ();
IMPORT int ledOpen ();
IMPORT int ledPreempt ();
IMPORT int ledPreemptSet ();
IMPORT int ledRead ();
IMPORT int ledRedraw ();
IMPORT int ledReplace ();
IMPORT int ledSearch ();
IMPORT int link ();
IMPORT int linkBufPoolInit ();
IMPORT int linkDataSyms;
IMPORT int linkSyms;
IMPORT int linkedCtorsInitialized;
IMPORT int listen ();
IMPORT int lkAddr ();
IMPORT int lkAddrInternal ();
IMPORT int lkup ();
IMPORT int ll ();
IMPORT int llr ();
IMPORT int loadCommonSymbolProcess ();
IMPORT int loadDefinedSymbolProcess ();
IMPORT int loadElfFileHeaderReadAndCheck ();
IMPORT int loadElfInit ();
IMPORT int loadElfProgramHeaderTableReadAndCheck ();
IMPORT int loadElfRelEntryRead ();
IMPORT int loadElfRelaEntryRead ();
IMPORT int loadElfSectionHeaderCheck ();
IMPORT int loadFormat;
IMPORT int loadLibInit ();
IMPORT int loadModule ();
IMPORT int loadModuleAt ();
IMPORT int loadModuleInfoFromFd ();
IMPORT int loadModuleInfoFromFilenameClose ();
IMPORT int loadModuleInfoFromFilenameOpen ();
IMPORT int loadModuleInfoInit ();
IMPORT int loadModuleInfoRelease ();
IMPORT int loadModuleSeek ();
IMPORT int loadModuleStringRead ();
IMPORT int loadModuleTagsCheck ();
IMPORT int loadModuleValueRead ();
IMPORT int loadSectionsInstall ();
IMPORT int loadSegInfoDescAllocate ();
IMPORT int loadSegInfoDescFree ();
IMPORT int loadSegmentsAllocate ();
IMPORT int loadShareTgtMemAlign ();
IMPORT int loadShareTgtMemFree ();
IMPORT int loadShareTgtMemSet ();
IMPORT int loadSysSymTblLoad ();
IMPORT int loadUndefinedSymbolProcess ();
IMPORT int loaderCacheBufferSize;
IMPORT int localToGlobalOffset;
IMPORT int localeconv ();
IMPORT int localtime ();
IMPORT int localtime_r ();
IMPORT int log ();
IMPORT int log10 ();
IMPORT int log2 ();
IMPORT int logDecorationChange ();
IMPORT int logFd;
IMPORT int logFdAdd ();
IMPORT int logFdDelete ();
IMPORT int logFdFromRlogin;
IMPORT int logFdSem;
IMPORT int logFdSet ();
IMPORT int logInfo;
IMPORT int logInit ();
IMPORT int logLevelChange ();
IMPORT int logMsg ();
IMPORT int logShow ();
IMPORT int logTask ();
IMPORT int logTaskId;
IMPORT int logTaskOptions;
IMPORT int logTaskPriority;
IMPORT int logTaskStackSize;
IMPORT int logb ();
IMPORT int loggerInfoShow ();
IMPORT int loginDefaultEncrypt ();
IMPORT int loginEncryptGet ();
IMPORT int loginEncryptInstall ();
IMPORT int loginHostname;
IMPORT int loginInit ();
IMPORT int loginPassword;
IMPORT int loginPrompt ();
IMPORT int loginPrompt2 ();
IMPORT int loginStringSet ();
IMPORT int loginTimeOutInSecond;
IMPORT int loginUserAdd ();
IMPORT int loginUserDelete ();
IMPORT int loginUserShow ();
IMPORT int loginUserVerify ();
IMPORT int loginUsername;
IMPORT int loginVerify_node;
IMPORT int logout ();
IMPORT int longjmp ();
IMPORT int lpt_test ();
IMPORT int ls ();
IMPORT int lseek ();
IMPORT int lsr ();
IMPORT int lstAdd ();
IMPORT int lstConcat ();
IMPORT int lstCount ();
IMPORT int lstDelete ();
IMPORT int lstExtract ();
IMPORT int lstFind ();
IMPORT int lstFirst ();
IMPORT int lstFree ();
IMPORT int lstFree2 ();
IMPORT int lstGet ();
IMPORT int lstInit ();
IMPORT int lstInsert ();
IMPORT int lstLast ();
IMPORT int lstLibInit ();
IMPORT int lstNStep ();
IMPORT int lstNext ();
IMPORT int lstNth ();
IMPORT int lstPrevious ();
IMPORT int m ();
IMPORT int m2If64BitCounters;
IMPORT int m6845vxbRegister ();
IMPORT int mRegs ();
IMPORT int m_prepend ();
IMPORT int malloc ();
IMPORT int mathAcosFunc;
IMPORT int mathAsinFunc;
IMPORT int mathAtan2Func;
IMPORT int mathAtanFunc;
IMPORT int mathCbrtFunc;
IMPORT int mathCeilFunc;
IMPORT int mathCosFunc;
IMPORT int mathCoshFunc;
IMPORT int mathErrNoInit ();
IMPORT int mathExpFunc;
IMPORT int mathFabsFunc;
IMPORT int mathFacosFunc;
IMPORT int mathFasinFunc;
IMPORT int mathFatan2Func;
IMPORT int mathFatanFunc;
IMPORT int mathFcbrtFunc;
IMPORT int mathFceilFunc;
IMPORT int mathFcosFunc;
IMPORT int mathFcoshFunc;
IMPORT int mathFexpFunc;
IMPORT int mathFfabsFunc;
IMPORT int mathFfloorFunc;
IMPORT int mathFfmodFunc;
IMPORT int mathFhypotFunc;
IMPORT int mathFinfinityFunc;
IMPORT int mathFirintFunc;
IMPORT int mathFiroundFunc;
IMPORT int mathFlog10Func;
IMPORT int mathFlog2Func;
IMPORT int mathFlogFunc;
IMPORT int mathFloorFunc;
IMPORT int mathFmodFunc;
IMPORT int mathFpowFunc;
IMPORT int mathFroundFunc;
IMPORT int mathFsinFunc;
IMPORT int mathFsincosFunc;
IMPORT int mathFsinhFunc;
IMPORT int mathFsqrtFunc;
IMPORT int mathFtanFunc;
IMPORT int mathFtanhFunc;
IMPORT int mathFtruncFunc;
IMPORT int mathHardAcos ();
IMPORT int mathHardAsin ();
IMPORT int mathHardAtan ();
IMPORT int mathHardAtan2 ();
IMPORT int mathHardCeil ();
IMPORT int mathHardCos ();
IMPORT int mathHardExp ();
IMPORT int mathHardFabs ();
IMPORT int mathHardFloor ();
IMPORT int mathHardFmod ();
IMPORT int mathHardFmodIeee ();
IMPORT int mathHardFuncInit ();
IMPORT int mathHardInfinity ();
IMPORT int mathHardIrint ();
IMPORT int mathHardIround ();
IMPORT int mathHardLog ();
IMPORT int mathHardLog10 ();
IMPORT int mathHardLog2 ();
IMPORT int mathHardPow ();
IMPORT int mathHardRound ();
IMPORT int mathHardSin ();
IMPORT int mathHardSincos ();
IMPORT int mathHardSqrt ();
IMPORT int mathHardTan ();
IMPORT int mathHardTrunc ();
IMPORT int mathHypotFunc;
IMPORT int mathInfinityFunc;
IMPORT int mathIrintFunc;
IMPORT int mathIroundFunc;
IMPORT int mathLog10Func;
IMPORT int mathLog2Func;
IMPORT int mathLogFunc;
IMPORT int mathPowFunc;
IMPORT int mathRoundFunc;
IMPORT int mathSinFunc;
IMPORT int mathSincosFunc;
IMPORT int mathSinhFunc;
IMPORT int mathSqrtFunc;
IMPORT int mathTanFunc;
IMPORT int mathTanhFunc;
IMPORT int mathTruncFunc;
IMPORT int max_hdr;
IMPORT int max_linkhdr;
IMPORT int max_protohdr;
IMPORT int mblen ();
IMPORT int mbstowcs ();
IMPORT int mbtowc ();
IMPORT int md5_block_host_order ();
IMPORT int mdlSymSyncLibInit ();
IMPORT int mdlSymSyncModAdd ();
IMPORT int mdlSymSyncModInfoGet ();
IMPORT int mdlSymSyncModuleRemove ();
IMPORT int mdlSymSyncStop ();
IMPORT int mdlSymSyncSymListAdd ();
IMPORT int mdlSymSyncSymListGet ();
IMPORT int memAddToPool ();
IMPORT int memBlockSizeGet ();
IMPORT int memDefaultAlignment;
IMPORT int memFindMax ();
IMPORT int memInfoGet ();
IMPORT int memInfoInit ();
IMPORT int memInit ();
IMPORT int memMsgBlockError;
IMPORT int memMsgBlockTooBig;
IMPORT int memOptionsGet ();
IMPORT int memOptionsSet ();
IMPORT int memPartAddToPool ();
IMPORT int memPartAlignedAlloc ();
IMPORT int memPartAlloc ();
IMPORT int memPartAllocErrorRtn;
IMPORT int memPartBlockErrorRtn;
IMPORT int memPartBlockIsValid ();
IMPORT int memPartBlockValidate ();
IMPORT int memPartClassId;
IMPORT int memPartCreate ();
IMPORT int memPartCreateHookSet ();
IMPORT int memPartDelete ();
IMPORT int memPartDeleteFree ();
IMPORT int memPartEdrErrorInject ();
IMPORT int memPartFindMax ();
IMPORT int memPartFree ();
IMPORT int memPartFreeListWalk ();
IMPORT int memPartHooksInstall ();
IMPORT int memPartInfoGet ();
IMPORT int memPartInit ();
IMPORT int memPartInsertFree ();
IMPORT int memPartLibInit ();
IMPORT int memPartOptionsDefault;
IMPORT int memPartOptionsGet ();
IMPORT int memPartOptionsSet ();
IMPORT int memPartRealloc ();
IMPORT int memPartReallocInternal ();
IMPORT int memPartShow ();
IMPORT int memPartVerifiedLock ();
IMPORT int memPoolEndAdrs;
IMPORT int memRom;
IMPORT int memShow ();
IMPORT int memShowInit ();
IMPORT int memSysPartId;
IMPORT int memTopPhys;
IMPORT int memalign ();
IMPORT int memchr ();
IMPORT int memcmp ();
IMPORT int memcpy ();
IMPORT int memmove ();
IMPORT int memoryDump ();
IMPORT int memoryModify ();
IMPORT int memset ();
IMPORT int mib2ErrorAdd ();
IMPORT int mib2Init ();
IMPORT int miiBusCreate ();
IMPORT int miiBusDelete ();
IMPORT int miiBusGet ();
IMPORT int miiBusIdleErrorCheck ();
IMPORT int miiBusListAdd ();
IMPORT int miiBusListDel ();
IMPORT int miiBusMediaAdd ();
IMPORT int miiBusMediaDefaultSet ();
IMPORT int miiBusMediaDel ();
IMPORT int miiBusMediaListGet ();
IMPORT int miiBusMediaUpdate ();
IMPORT int miiBusModeGet ();
IMPORT int miiBusModeSet ();
IMPORT int miiBusRead ();
IMPORT int miiBusRegister ();
IMPORT int miiBusWrite ();
IMPORT int miiMediaUpdate_desc;
IMPORT int miiModeGet_desc;
IMPORT int miiModeSet_desc;
IMPORT int miiRead_desc;
IMPORT int miiWrite_desc;
IMPORT int mkdir ();
IMPORT int mktime ();
IMPORT int mmuArchCopySize;
IMPORT int mmuArchLibAttrs;
IMPORT int mmuArchLibFuncs;
IMPORT int mmuCacheStateTransTbl;
IMPORT int mmuInvalidState;
IMPORT int mmuLibFuncs;
IMPORT int mmuMaskTransTbl;
IMPORT int mmuPhysAddrShift;
IMPORT int mmuPro32Enable ();
IMPORT int mmuPro32Enabled;
IMPORT int mmuPro32LibInit ();
IMPORT int mmuPro32Off ();
IMPORT int mmuPro32On ();
IMPORT int mmuPro32Page0UnMap ();
IMPORT int mmuPro32Page0UnMapped;
IMPORT int mmuPro32PdbrGet ();
IMPORT int mmuPro32PdbrSet ();
IMPORT int mmuPro32PhysAddrSet ();
IMPORT int mmuPro32TLBEntryFlush ();
IMPORT int mmuPro32TLBFlush ();
IMPORT int mmuProtStateTransTbl;
IMPORT int mmuValidStateTransTbl;
IMPORT int modf ();
IMPORT int modlist;
IMPORT int moduleCheck ();
IMPORT int moduleCreate ();
IMPORT int moduleCreateHookAdd ();
IMPORT int moduleCreateHookDelete ();
IMPORT int moduleDelete ();
IMPORT int moduleDescDestroy ();
IMPORT int moduleEach ();
IMPORT int moduleFindByGroup ();
IMPORT int moduleFindByName ();
IMPORT int moduleFindByNameAndPath ();
IMPORT int moduleFirstSectionGet ();
IMPORT int moduleFlagsGet ();
IMPORT int moduleIdFigure ();
IMPORT int moduleIdListGet ();
IMPORT int moduleIdVerify ();
IMPORT int moduleInfoGet ();
IMPORT int moduleInit ();
IMPORT int moduleLibInit ();
IMPORT int moduleNameGet ();
IMPORT int moduleNextSectionGet ();
IMPORT int moduleSectionChecksumSet ();
IMPORT int moduleSectionDescFree ();
IMPORT int moduleSectionDescGet ();
IMPORT int moduleSectionRegister ();
IMPORT int moduleSegAdd ();
IMPORT int moduleSegEach ();
IMPORT int moduleSegFirst ();
IMPORT int moduleSegGet ();
IMPORT int moduleSegInfoGet ();
IMPORT int moduleSegNext ();
IMPORT int moduleShow ();
IMPORT int moduleShowInit ();
IMPORT int moduleUndefSymAdd ();
IMPORT int mpApicAddrTableGet_desc;
IMPORT int mpApicBusTableGet_desc;
IMPORT int mpApicCpuIndexTableGet_desc;
IMPORT int mpApicDataShow_desc;
IMPORT int mpApicFpsGet_desc;
IMPORT int mpApicInterruptTableGet_desc;
IMPORT int mpApicLoIndexTableGet_desc;
IMPORT int mpApicLogicalTableGet_desc;
IMPORT int mpApicNbusGet_desc;
IMPORT int mpApicNioApicGet_desc;
IMPORT int mpApicNiointGet_desc;
IMPORT int mpApicNlointGet_desc;
IMPORT int mpApicloBaseGet_desc;
IMPORT int mpCpuIndexTable;
IMPORT int msgQClassId;
IMPORT int msgQCreate ();
IMPORT int msgQCreateLibInit ();
IMPORT int msgQDelete ();
IMPORT int msgQDestroy ();
IMPORT int msgQDistInfoGetRtn;
IMPORT int msgQDistNumMsgsRtn;
IMPORT int msgQDistReceiveRtn;
IMPORT int msgQDistSendRtn;
IMPORT int msgQDistShowRtn;
IMPORT int msgQEvStart ();
IMPORT int msgQEvStop ();
IMPORT int msgQInfoGet ();
IMPORT int msgQInit ();
IMPORT int msgQInitialize ();
IMPORT int msgQLibInit ();
IMPORT int msgQLibInstalled;
IMPORT int msgQNumMsgs ();
IMPORT int msgQReceive ();
IMPORT int msgQSend ();
IMPORT int msgQSmInfoGetRtn;
IMPORT int msgQSmNumMsgsRtn;
IMPORT int msgQSmReceiveRtn;
IMPORT int msgQSmSendRtn;
IMPORT int msgQSmShowRtn;
IMPORT int msgQTerminate ();
IMPORT int mutexOptionsHostLib;
IMPORT int mutexOptionsIosLib;
IMPORT int mutexOptionsLogLib;
IMPORT int mutexOptionsNetDrv;
IMPORT int mutexOptionsSelectLib;
IMPORT int mutexOptionsSymLib;
IMPORT int mutexOptionsTyLib;
IMPORT int mutexOptionsVmBaseLib;
IMPORT int mux2Bind ();
IMPORT int mux2LibInit ();
IMPORT int mux2OverEndInit ();
IMPORT int mux2OverEndOutputFilterChainDrops;
IMPORT int mux2PollReceive ();
IMPORT int mux2PollSend ();
IMPORT int mux2Send ();
IMPORT int muxAddressForm ();
IMPORT int muxBind ();
IMPORT int muxBindCommon ();
IMPORT int muxBindStyles;
IMPORT int muxCommonInit ();
IMPORT int muxDebug;
IMPORT int muxDevAcquire ();
IMPORT int muxDevConnect_desc;
IMPORT int muxDevExists ();
IMPORT int muxDevLoad ();
IMPORT int muxDevRelease ();
IMPORT int muxDevStart ();
IMPORT int muxDevStop ();
IMPORT int muxDevStopAll ();
IMPORT int muxDevUnload ();
IMPORT int muxDevUnloadAsync ();
IMPORT int muxEndJobQDo ();
IMPORT int muxEndJobQDoJob ();
IMPORT int muxEndListGet ();
IMPORT int muxEndQnumGet ();
IMPORT int muxEndRxJobQueue ();
IMPORT int muxEndStyles;
IMPORT int muxError ();
IMPORT int muxErrorPost ();
IMPORT int muxErrorSkip ();
IMPORT int muxIfTypeGet ();
IMPORT int muxIoctl ();
IMPORT int muxIpcomPktFreeMblk ();
IMPORT int muxIpcomPktToMblkTx ();
IMPORT int muxL2PortDetachRtn;
IMPORT int muxLibInit ();
IMPORT int muxLinkDownNotify ();
IMPORT int muxLinkHeaderCreate ();
IMPORT int muxLinkUpNotify ();
IMPORT int muxLock;
IMPORT int muxMCastAddrAdd ();
IMPORT int muxMCastAddrDel ();
IMPORT int muxMCastAddrGet ();
IMPORT int muxMblkFreeIpcomPktOutDone ();
IMPORT int muxMblkToIpcomPktMallocDrops;
IMPORT int muxMblkToIpcomPktTx ();
IMPORT int muxMblkToIpcomPktTxChainDrops;
IMPORT int muxPacketAddrGet ();
IMPORT int muxPacketDataGet ();
IMPORT int muxPollReceive ();
IMPORT int muxPollSend ();
IMPORT int muxProtoInfoGet ();
IMPORT int muxProtoListGet ();
IMPORT int muxReceive ();
IMPORT int muxSend ();
IMPORT int muxShow ();
IMPORT int muxTkBind ();
IMPORT int muxTkCookieGet ();
IMPORT int muxTkDrvCheck ();
IMPORT int muxTkLibInit ();
IMPORT int muxTkOverEndInit ();
IMPORT int muxTkPollReceive ();
IMPORT int muxTkPollSend ();
IMPORT int muxTkSend ();
IMPORT int muxTxRestart ();
IMPORT int muxUnbind ();
IMPORT int mv ();
IMPORT int name_node;
IMPORT int namelessPrefix;
IMPORT int nbioAppend ();
IMPORT int nbioBegin ();
IMPORT int nbioDrop ();
IMPORT int nbioEnd ();
IMPORT int nbioFdPrint ();
IMPORT int nbioFlush ();
IMPORT int nbioFormatV ();
IMPORT int nbioLog ();
IMPORT int nbioLogInfoInit ();
IMPORT int nbioLogInfoMsgsAdd ();
IMPORT int nbioLogInfoSync ();
IMPORT int nbioLogInfoTerminate ();
IMPORT int nbioLogInit ();
IMPORT int nbioLogServerInit ();
IMPORT int nbioLogTaskName;
IMPORT int nbioLogTaskOptions;
IMPORT int nbioLogTaskPriority;
IMPORT int nbioLogTaskStackSize;
IMPORT int nbioOutput ();
IMPORT int nbioPoolSemOptions;
IMPORT int nbioSync ();
IMPORT int netAttachFlag;
IMPORT int netBufClOffset;
IMPORT int netBufLibInit ();
IMPORT int netBufLibInitialize ();
IMPORT int netBufLock;
IMPORT int netBufPoolInit ();
IMPORT int netClBlkFree ();
IMPORT int netClBlkGet ();
IMPORT int netClBlkJoin ();
IMPORT int netClFree ();
IMPORT int netClPoolIdGet ();
IMPORT int netClusterGet ();
IMPORT int netDaemonQ ();
IMPORT int netDaemonQnum ();
IMPORT int netDaemonsCount ();
IMPORT int netDaemonsStart ();
IMPORT int netDevBootFlag;
IMPORT int netDevCreate ();
IMPORT int netDevCreate2 ();
IMPORT int netDrv ();
IMPORT int netDrvDebugLevelSet ();
IMPORT int netDrvFileDoesNotExist ();
IMPORT int netDrvFileDoesNotExistInstall ();
IMPORT int netErrnoSet ();
IMPORT int netHelp ();
IMPORT int netJobAdd ();
IMPORT int netJobNum;
IMPORT int netJobQueueId;
IMPORT int netLibInitialize ();
IMPORT int netLsByName ();
IMPORT int netMblkChainDup ();
IMPORT int netMblkClChainFree ();
IMPORT int netMblkClFree ();
IMPORT int netMblkClGet ();
IMPORT int netMblkClJoin ();
IMPORT int netMblkDup ();
IMPORT int netMblkFree ();
IMPORT int netMblkFromBufCopy ();
IMPORT int netMblkGet ();
IMPORT int netMblkOffsetToBufCopy ();
IMPORT int netMblkToBufCopy ();
IMPORT int netPoolCreate ();
IMPORT int netPoolCreateValidate ();
IMPORT int netPoolDelete ();
IMPORT int netPoolIdGet ();
IMPORT int netPoolIdGetWork ();
IMPORT int netPoolInit ();
IMPORT int netPoolInitWrapper ();
IMPORT int netPoolKheapInit ();
IMPORT int netPoolNameGet ();
IMPORT int netPoolRelPri;
IMPORT int netPoolRelease ();
IMPORT int netTaskId;
IMPORT int netTaskNamePrefix;
IMPORT int netTaskOptions;
IMPORT int netTaskPriority;
IMPORT int netTaskStackSize;
IMPORT int netTupleFree ();
IMPORT int netTupleGet ();
IMPORT int netVersionString;
IMPORT int netmask;
IMPORT int next_node;
IMPORT int noDev ();
IMPORT int nonVolGet_desc;
IMPORT int nonVolSet_desc;
IMPORT int ns16550SioRegister ();
IMPORT int numLogFds;
IMPORT int numberOfCmdHandlers;
IMPORT int numberOfLoaders;
IMPORT int nvRamSegDefGet ();
IMPORT int objAlloc ();
IMPORT int objAllocExtra ();
IMPORT int objArchLibInit ();
IMPORT int objClassIdGet ();
IMPORT int objClassTypeGet ();
IMPORT int objContextGet ();
IMPORT int objContextSet ();
IMPORT int objCoreInit ();
IMPORT int objCoreInvalidate ();
IMPORT int objCoreReclaim ();
IMPORT int objCoreTerminate ();
IMPORT int objCoreUnlink ();
IMPORT int objEach ();
IMPORT int objFree ();
IMPORT int objGenericVerify ();
IMPORT int objInfo ();
IMPORT int objInfoInit ();
IMPORT int objLibInit ();
IMPORT int objMemAlloc ();
IMPORT int objMemFree ();
IMPORT int objNameGet ();
IMPORT int objNameLenGet ();
IMPORT int objNamePtrGet ();
IMPORT int objNamePtrSet ();
IMPORT int objNameSet ();
IMPORT int objNameToId ();
IMPORT int objOwnerGet ();
IMPORT int objOwnerLibInstalled;
IMPORT int objOwnerSet ();
IMPORT int objOwnerSetBase ();
IMPORT int objShow ();
IMPORT int objVerify ();
IMPORT int objVerifyError ();
IMPORT int objVerifyMagicRead ();
IMPORT int objVerifyTypeRead ();
IMPORT int objectShow ();
IMPORT int oidfmt_node;
IMPORT int oidsInList;
IMPORT int open ();
IMPORT int opendir ();
IMPORT int oprintf ();
IMPORT int optarg;
IMPORT int opterr;
IMPORT int optind;
IMPORT int optopt;
IMPORT int optreset;
IMPORT int osmFatalMsg;
IMPORT int osmGuardPageSize;
IMPORT int osmTask ();
IMPORT int ossCalloc ();
IMPORT int ossFree ();
IMPORT int ossFreeFuncPtr;
IMPORT int ossInitialize ();
IMPORT int ossMalloc ();
IMPORT int ossMallocFuncPtr;
IMPORT int ossMemUsedGet ();
IMPORT int ossMutexCreate ();
IMPORT int ossMutexDestroy ();
IMPORT int ossMutexRelease ();
IMPORT int ossMutexTake ();
IMPORT int ossOldFree ();
IMPORT int ossOldInstall ();
IMPORT int ossOldMalloc ();
IMPORT int ossPartFree ();
IMPORT int ossPartIdGet ();
IMPORT int ossPartMalloc ();
IMPORT int ossPartSizeGet ();
IMPORT int ossPartSizeSet ();
IMPORT int ossSemCreate ();
IMPORT int ossSemDestroy ();
IMPORT int ossSemGive ();
IMPORT int ossSemTake ();
IMPORT int ossShutdown ();
IMPORT int ossStatus ();
IMPORT int ossThreadCreate ();
IMPORT int ossThreadDestroy ();
IMPORT int ossThreadSleep ();
IMPORT int ossTime ();
IMPORT int pAddrString;
IMPORT int pBusHead;
IMPORT int pBusListHead;
IMPORT int pClkCookie;
IMPORT int pClkTimer;
IMPORT int pCoprocDescList;
IMPORT int pDataCollectorFunctions;
IMPORT int pDbgClnt;
IMPORT int pDevName;
IMPORT int pDriverListHead;
IMPORT int pEndPktDev;
IMPORT int pHead;
IMPORT int pInPkt;
IMPORT int pIosDevCloseRtn;
IMPORT int pIosFdEntrySetRtn;
IMPORT int pIosFdInvalidRtn;
IMPORT int pIosRemovableDevDrv;
IMPORT int pIosSuspendedDevDrv;
IMPORT int pJobPool;
IMPORT int pLoadRoutine;
IMPORT int pLoaderHooksCall;
IMPORT int pM2TrapRtn;
IMPORT int pM2TrapRtnArg;
IMPORT int pMibRtn;
IMPORT int pMpApicData;
IMPORT int pNetPoolHead;
IMPORT int pNullFd;
IMPORT int pPlbBus;
IMPORT int pPlbDev;
IMPORT int pPlbDevControl;
IMPORT int pRebootHookTbl;
IMPORT int pRootMemStart;
IMPORT int pRtpDbgCmdSvc;
IMPORT int pSockIoctlMemVal;
IMPORT int pSymRelRtn;
IMPORT int pSysClkName;
IMPORT int pSysGdt;
IMPORT int pSysPlbMethods;
IMPORT int pSysctlCtxList;
IMPORT int pTaskLastDspTcb;
IMPORT int pTaskLastFpTcb;
IMPORT int pTgtName;
IMPORT int pUnixIoctlMemVal;
IMPORT int pUnloaderHooksCall;
IMPORT int pUsb2MscDriver;
IMPORT int pVmBaseFuncsSet;
IMPORT int pVmInvPageMapRtn;
IMPORT int pVxbDelayCookie;
IMPORT int pVxbDelayTimer;
IMPORT int pVxbSpinLockGive;
IMPORT int pVxbSpinLockTake;
IMPORT int pWdbClnt;
IMPORT int pWdbCommIf;
IMPORT int pWdbCtxBpIf;
IMPORT int pWdbExternSystemRegs;
IMPORT int pWdbMemRegions;
IMPORT int pWdbRtIf;
IMPORT int pWdbXport;
IMPORT int pWvNetEventMap;
IMPORT int panic ();
IMPORT int panicSuspend;
IMPORT int partLibCreate ();
IMPORT int partLibCreateSz ();
IMPORT int pathBuild ();
IMPORT int pathCat ();
IMPORT int pathCondense ();
IMPORT int pathLastName ();
IMPORT int pathLastNamePtr ();
IMPORT int pathParse ();
IMPORT int pathSplit ();
IMPORT int pathconf ();
IMPORT int pause ();
IMPORT int pc ();
IMPORT int pcConBeep_desc;
IMPORT int pcConDevBind ();
IMPORT int pcConDevCreate ();
IMPORT int pcConDrv ();
IMPORT int pciBusAnnounceDevices ();
IMPORT int pciCfgInit ();
IMPORT int pciConfigEnable ();
IMPORT int pciConfigExtCapFind ();
IMPORT int pciConfigForeachFunc ();
IMPORT int pciConfigInByte ();
IMPORT int pciConfigInLong ();
IMPORT int pciConfigInWord ();
IMPORT int pciConfigModifyByte ();
IMPORT int pciConfigModifyLong ();
IMPORT int pciConfigModifyWord ();
IMPORT int pciConfigOutByte ();
IMPORT int pciConfigOutLong ();
IMPORT int pciConfigOutWord ();
IMPORT int pciConnect ();
IMPORT int pciDevConfig ();
IMPORT int pciDevMatch ();
IMPORT int pciDeviceAnnounce ();
IMPORT int pciFindClass ();
IMPORT int pciFindDevice ();
IMPORT int pciHcfRecordFind ();
IMPORT int pciInit1 ();
IMPORT int pciInit2 ();
IMPORT int pciIntConnect ();
IMPORT int pciIntDisconnect ();
IMPORT int pciIntDisconnect2 ();
IMPORT int pciIntVectorToIRQ ();
IMPORT int pciRegister ();
IMPORT int pentiumBtc ();
IMPORT int pentiumBts ();
IMPORT int pentiumCr4Get ();
IMPORT int pentiumCr4Set ();
IMPORT int pentiumM6845VgaResources;
IMPORT int pentiumMcaEnable ();
IMPORT int pentiumMsrGet ();
IMPORT int pentiumMsrInit ();
IMPORT int pentiumMsrP5;
IMPORT int pentiumMsrP5NumEnt;
IMPORT int pentiumMsrP6;
IMPORT int pentiumMsrP6NumEnt;
IMPORT int pentiumMsrP7;
IMPORT int pentiumMsrP7NumEnt;
IMPORT int pentiumMsrSet ();
IMPORT int pentiumMtrrDisable ();
IMPORT int pentiumMtrrEnable ();
IMPORT int pentiumMtrrGet ();
IMPORT int pentiumMtrrSet ();
IMPORT int pentiumP5PmcGet ();
IMPORT int pentiumP5PmcGet0 ();
IMPORT int pentiumP5PmcGet1 ();
IMPORT int pentiumP5PmcReset ();
IMPORT int pentiumP5PmcReset0 ();
IMPORT int pentiumP5PmcReset1 ();
IMPORT int pentiumP5PmcStart0 ();
IMPORT int pentiumP5PmcStart1 ();
IMPORT int pentiumP5PmcStop0 ();
IMPORT int pentiumP5PmcStop1 ();
IMPORT int pentiumP6PmcGet ();
IMPORT int pentiumP6PmcGet0 ();
IMPORT int pentiumP6PmcGet1 ();
IMPORT int pentiumP6PmcReset ();
IMPORT int pentiumP6PmcReset0 ();
IMPORT int pentiumP6PmcReset1 ();
IMPORT int pentiumP6PmcStart ();
IMPORT int pentiumP6PmcStop ();
IMPORT int pentiumP6PmcStop1 ();
IMPORT int pentiumPci0Resources;
IMPORT int pentiumPciBusDevGet ();
IMPORT int pentiumPciMmuMapAdd ();
IMPORT int pentiumPciPhysMemHandle ();
IMPORT int pentiumPciPhysMemShow ();
IMPORT int pentiumPciRegister ();
IMPORT int pentiumPmcGet ();
IMPORT int pentiumPmcGet0 ();
IMPORT int pentiumPmcGet1 ();
IMPORT int pentiumPmcReset ();
IMPORT int pentiumPmcReset0 ();
IMPORT int pentiumPmcReset1 ();
IMPORT int pentiumPmcStart ();
IMPORT int pentiumPmcStart0 ();
IMPORT int pentiumPmcStart1 ();
IMPORT int pentiumPmcStop ();
IMPORT int pentiumPmcStop0 ();
IMPORT int pentiumPmcStop1 ();
IMPORT int pentiumSerialize ();
IMPORT int pentiumTlbFlush ();
IMPORT int pentiumTscGet32 ();
IMPORT int pentiumTscGet64 ();
IMPORT int pentiumTscReset ();
IMPORT int pentiumi8042KbdResources;
IMPORT int pentiumi8042MseResources;
IMPORT int pentiumi82501Resources;
IMPORT int pentiumi82502Resources;
IMPORT int pentiumi82503Resources;
IMPORT int pentiumi82504Resources;
IMPORT int period ();
IMPORT int periodHost ();
IMPORT int periodRun ();
IMPORT int perror ();
IMPORT int pipeDevCreate ();
IMPORT int pipeDevDelete ();
IMPORT int pipeDrv ();
IMPORT int pipeMsgQOptions;
IMPORT int plbConnect ();
IMPORT int plbDevMatch ();
IMPORT int plbInit1 ();
IMPORT int plbInit2 ();
IMPORT int plbIntrGet ();
IMPORT int plbIntrSet ();
IMPORT int plbRegister ();
IMPORT int poolBlockAdd ();
IMPORT int poolCreate ();
IMPORT int poolDelete ();
IMPORT int poolFreeCount ();
IMPORT int poolIdListGet ();
IMPORT int poolIncrementGet ();
IMPORT int poolIncrementSet ();
IMPORT int poolItemGet ();
IMPORT int poolItemReturn ();
IMPORT int poolLibInit ();
IMPORT int poolListGbl;
IMPORT int poolTotalCount ();
IMPORT int poolUnusedBlocksFree ();
IMPORT int pow ();
IMPORT int ppGlobalEnviron;
IMPORT int print64 ();
IMPORT int print64Fine ();
IMPORT int print64Mult ();
IMPORT int print64Row ();
IMPORT int printBootShellPrompt;
IMPORT int printErr ();
IMPORT int printErrno ();
IMPORT int printErrorMessageHere ();
IMPORT int printExc ();
IMPORT int printLogo ();
IMPORT int printf ();
IMPORT int priv_targetName;
IMPORT int ptyDevCreate ();
IMPORT int ptyDevRemove ();
IMPORT int ptyDrv ();
IMPORT int putc ();
IMPORT int putchar ();
IMPORT int putenv ();
IMPORT int puts ();
IMPORT int putw ();
IMPORT int pwd ();
IMPORT int qAdvance ();
IMPORT int qCalibrate ();
IMPORT int qEach ();
IMPORT int qFifoClass;
IMPORT int qFifoClassId;
IMPORT int qFifoEach ();
IMPORT int qFifoGet ();
IMPORT int qFifoInfo ();
IMPORT int qFifoInit ();
IMPORT int qFifoNext ();
IMPORT int qFifoPut ();
IMPORT int qFifoRemove ();
IMPORT int qFifoRestore ();
IMPORT int qFirst ();
IMPORT int qGet ();
IMPORT int qGetExpired ();
IMPORT int qInfo ();
IMPORT int qInit ();
IMPORT int qKey ();
IMPORT int qNullRtn ();
IMPORT int qPriBMapClassId;
IMPORT int qPriBMapEach ();
IMPORT int qPriBMapGet ();
IMPORT int qPriBMapInfo ();
IMPORT int qPriBMapInit ();
IMPORT int qPriBMapKey ();
IMPORT int qPriBMapNext ();
IMPORT int qPriBMapPut ();
IMPORT int qPriBMapRemove ();
IMPORT int qPriBMapResort ();
IMPORT int qPriBMapRestore ();
IMPORT int qPriBMapSet ();
IMPORT int qPriDeltaAdvance ();
IMPORT int qPriDeltaClassId;
IMPORT int qPriDeltaEach ();
IMPORT int qPriDeltaGet ();
IMPORT int qPriDeltaGetExpired ();
IMPORT int qPriDeltaInfo ();
IMPORT int qPriDeltaInit ();
IMPORT int qPriDeltaKey ();
IMPORT int qPriDeltaNext ();
IMPORT int qPriDeltaPut ();
IMPORT int qPriDeltaRemove ();
IMPORT int qPriDeltaResort ();
IMPORT int qPriDeltaTerminate ();
IMPORT int qPriListAdvance ();
IMPORT int qPriListCalibrate ();
IMPORT int qPriListClassId;
IMPORT int qPriListEach ();
IMPORT int qPriListFromTailClassId;
IMPORT int qPriListGet ();
IMPORT int qPriListGetExpired ();
IMPORT int qPriListInfo ();
IMPORT int qPriListInit ();
IMPORT int qPriListKey ();
IMPORT int qPriListNext ();
IMPORT int qPriListPut ();
IMPORT int qPriListPutFromTail ();
IMPORT int qPriListRemove ();
IMPORT int qPriListResort ();
IMPORT int qPriListTerminate ();
IMPORT int qPut ();
IMPORT int qRemove ();
IMPORT int qResort ();
IMPORT int qTerminate ();
IMPORT int qTradPriBMapClassId;
IMPORT int qTradPriBMapSetCompatible ();
IMPORT int qTradPriListClassId;
IMPORT int qTradPriListSetCompatible ();
IMPORT int qsort ();
IMPORT int raise ();
IMPORT int rand ();
IMPORT int rawFsDevInit ();
IMPORT int rawFsDrvNum;
IMPORT int rawFsFdListMutexOptions;
IMPORT int rawFsFdMutexOptions;
IMPORT int rawFsInit ();
IMPORT int rawFsVolMutexOptions;
IMPORT int rawFsVolUnmount ();
IMPORT int rcmd ();
IMPORT int rcmd_af ();
IMPORT int read ();
IMPORT int readdir ();
IMPORT int readdir_r ();
IMPORT int readv ();
IMPORT int readyQBMap;
IMPORT int readyQHead;
IMPORT int realloc ();
IMPORT int realtime_test ();
IMPORT int reboot ();
IMPORT int rebootHookAdd ();
IMPORT int rebootHookTbl;
IMPORT int rebootHookTblSize;
IMPORT int recv ();
IMPORT int recvfrom ();
IMPORT int recvmsg ();
IMPORT int regsShow ();
IMPORT int regsShowOutput ();
IMPORT int reld ();
IMPORT int remCurIdGet ();
IMPORT int remCurIdSet ();
IMPORT int remLastResvPort;
IMPORT int remLibInit ();
IMPORT int remNumConnRetrials;
IMPORT int remPasswd;
IMPORT int remStdErrSetupTimeout;
IMPORT int remUser;
IMPORT int remove ();
IMPORT int rename ();
IMPORT int repeat ();
IMPORT int repeatHost ();
IMPORT int repeatRun ();
IMPORT int reschedule ();
IMPORT int restartTaskName;
IMPORT int restartTaskOptions;
IMPORT int restartTaskPriority;
IMPORT int restartTaskStackSize;
IMPORT int rewind ();
IMPORT int rewinddir ();
IMPORT int rindex ();
IMPORT int rm ();
IMPORT int rmdir ();
IMPORT int rngBufGet ();
IMPORT int rngBufPut ();
IMPORT int rngCreate ();
IMPORT int rngDelete ();
IMPORT int rngFlush ();
IMPORT int rngFreeBytes ();
IMPORT int rngIsEmpty ();
IMPORT int rngIsFull ();
IMPORT int rngMoveAhead ();
IMPORT int rngNBytes ();
IMPORT int rngPutAhead ();
IMPORT int rootMemNBytes;
IMPORT int rootTaskId;
IMPORT int round ();
IMPORT int roundRobinHookInstalled;
IMPORT int roundRobinOn;
IMPORT int roundRobinSlice;
IMPORT int rresvport ();
IMPORT int rresvportCommon ();
IMPORT int rresvport_af ();
IMPORT int rtpCallHandlerAddr;
IMPORT int rtpDeleteMsg;
IMPORT int rtpSigDeleteMsg;
IMPORT int rtpSigStopMsg;
IMPORT int rtpStopMsg;
IMPORT char * runtimeName;
IMPORT char * runtimeVersion;
IMPORT int s ();
IMPORT int sStepLibInit ();
IMPORT int s_ComName;
IMPORT int s_IoCntTid;
IMPORT int s_MangeCan;
IMPORT int s_TxBuffer;
IMPORT int s_com_tid;
IMPORT int s_net_tid;
IMPORT int s_task_over_flag;
IMPORT int s_ticks;
IMPORT int s_wdId;
IMPORT int s_wdId2;
IMPORT int salEvtRtn;
IMPORT int scalb ();
IMPORT int scanCharSet ();
IMPORT int scanField ();
IMPORT int scanf ();
IMPORT int selNodeAdd ();
IMPORT int selNodeDelete ();
IMPORT int selTaskDeleteHookAdd ();
IMPORT int selWakeup ();
IMPORT int selWakeupAll ();
IMPORT int selWakeupListInit ();
IMPORT int selWakeupListLen ();
IMPORT int selWakeupListTerm ();
IMPORT int selWakeupType ();
IMPORT int select ();
IMPORT int selectInit ();
IMPORT int semBCreate ();
IMPORT int semBGive ();
IMPORT int semBGiveDefer ();
IMPORT int semBGiveNoLock ();
IMPORT int semBGiveScalable ();
IMPORT int semBInit ();
IMPORT int semBInitialize ();
IMPORT int semBTake ();
IMPORT int semBTakeNoLock ();
IMPORT int semBTakeScalable ();
IMPORT int semCCreate ();
IMPORT int semCGive ();
IMPORT int semCGiveDefer ();
IMPORT int semCInit ();
IMPORT int semCInitialize ();
IMPORT int semCTake ();
IMPORT int semClass;
IMPORT int semClassId;
IMPORT int semCreateTbl;
IMPORT int semDelete ();
IMPORT int semDeleteLibInit ();
IMPORT int semDestroy ();
IMPORT int semEvIsFreeTbl;
IMPORT int semEvStart ();
IMPORT int semEvStop ();
IMPORT int semFlush ();
IMPORT int semFlushDefer ();
IMPORT int semFlushDeferTbl;
IMPORT int semFlushTbl;
IMPORT int semGive ();
IMPORT int semGiveDefer ();
IMPORT int semGiveDeferTbl;
IMPORT int semGiveNoLockTbl;
IMPORT int semGiveTbl;
IMPORT int semInfo ();
IMPORT int semInfoGet ();
IMPORT int semIntRestrict ();
IMPORT int semInvalid ();
IMPORT int semLibInit ();
IMPORT int semLocalIdVerify ();
IMPORT int semMCreate ();
IMPORT int semMGive ();
IMPORT int semMGiveForce ();
IMPORT int semMGiveKernWork ();
IMPORT int semMGiveNoLock ();
IMPORT int semMGiveScalable ();
IMPORT int semMInit ();
IMPORT int semMInitialize ();
IMPORT int semMPendQPut ();
IMPORT int semMTake ();
IMPORT int semMTakeByProxy ();
IMPORT int semMTakeNoLock ();
IMPORT int semMTakeScalable ();
IMPORT int semQFlush ();
IMPORT int semQFlushDefer ();
IMPORT int semQInit ();
IMPORT int semRTake ();
IMPORT int semRWCreate ();
IMPORT int semRWGive ();
IMPORT int semRWGiveForce ();
IMPORT int semRWInitialize ();
IMPORT int semRWLibMaxReaders;
IMPORT int semSmInfoRtn;
IMPORT int semSmShowRtn;
IMPORT int semTake ();
IMPORT int semTakeNoLockTbl;
IMPORT int semTakeTbl;
IMPORT int semTerminate ();
IMPORT int semWTake ();
IMPORT int sem_test ();
IMPORT int send ();
IMPORT int sendmsg ();
IMPORT int sendto ();
IMPORT int setbuf ();
IMPORT int setbuffer ();
IMPORT int sethostname ();
IMPORT int setjmp ();
IMPORT int setlinebuf ();
IMPORT int setlocale ();
IMPORT int setsockopt ();
IMPORT int setvbuf ();
IMPORT int sfsFmtRtn;
IMPORT int shConfig ();
IMPORT int sha256_block_data_order ();
IMPORT int sha256_block_host_order ();
IMPORT int shellAbort ();
IMPORT int shellAbortHandledByShell ();
IMPORT int shellBackgroundInit ();
IMPORT int shellBackgroundRead ();
IMPORT int shellCmdAdd ();
IMPORT int shellCmdAliasAdd ();
IMPORT int shellCmdAliasArrayAdd ();
IMPORT int shellCmdAliasDelete ();
IMPORT int shellCmdAliasShow ();
IMPORT int shellCmdArrayAdd ();
IMPORT int shellCmdCheck ();
IMPORT int shellCmdExec ();
IMPORT int shellCmdInfoArgsStore ();
IMPORT int shellCmdInfoCmdLineStore ();
IMPORT int shellCmdInfoFinalNameStore ();
IMPORT int shellCmdInfoGet ();
IMPORT int shellCmdInfoInitialNameStore ();
IMPORT int shellCmdInit ();
IMPORT int shellCmdMatchingAliasListGet ();
IMPORT int shellCmdMatchingCmdListGet ();
IMPORT int shellCmdMemRegister ();
IMPORT int shellCmdMemUnregister ();
IMPORT int shellCmdPreParseAdd ();
IMPORT int shellCmdPreParsedGet ();
IMPORT int shellCmdStatementExec ();
IMPORT int shellCmdStatementSplit ();
IMPORT int shellCmdSymTabIdGet ();
IMPORT int shellCmdTaskIdConvert ();
IMPORT int shellCmdTopicAdd ();
IMPORT int shellCompatibleCheck ();
IMPORT int shellCompatibleSet ();
IMPORT int shellCompletionPathnameGet ();
IMPORT int shellConfigDefaultGet ();
IMPORT int shellConfigDefaultSet ();
IMPORT int shellConfigDefaultValueGet ();
IMPORT int shellConfigDefaultValueSet ();
IMPORT int shellConfigDefaultValueUnset ();
IMPORT int shellConfigGet ();
IMPORT int shellConfigLibInit ();
IMPORT int shellConfigSet ();
IMPORT int shellConfigValueGet ();
IMPORT int shellConfigValueSet ();
IMPORT int shellConfigValueUnset ();
IMPORT int shellConsoleInit ();
IMPORT int shellConsoleTaskId;
IMPORT int shellContextFinalize ();
IMPORT int shellContextInit ();
IMPORT int shellContextListLock ();
IMPORT int shellContextListUnlock ();
IMPORT int shellDataAdd ();
IMPORT int shellDataAllRemove ();
IMPORT int shellDataFirst ();
IMPORT int shellDataFromNameAdd ();
IMPORT int shellDataFromNameGet ();
IMPORT int shellDataGet ();
IMPORT int shellDataNext ();
IMPORT int shellDataRemove ();
IMPORT int shellErrnoGet ();
IMPORT int shellErrnoSet ();
IMPORT int shellExec ();
IMPORT int shellExitWrapper ();
IMPORT int shellFirst ();
IMPORT int shellFromNameGet ();
IMPORT int shellFromTaskGet ();
IMPORT int shellFromTaskParentContextGet ();
IMPORT int shellGenericInit ();
IMPORT int shellHistory ();
IMPORT int shellIdVerify ();
IMPORT int shellInOutBgndClose ();
IMPORT int shellInOutBgndGet ();
IMPORT int shellInOutBgndIoClose ();
IMPORT int shellInOutBgndOpen ();
IMPORT int shellInOutBgndRegister ();
IMPORT int shellInOutBlockingBlock ();
IMPORT int shellInOutBlockingBlockedDataGet ();
IMPORT int shellInOutBlockingClose ();
IMPORT int shellInOutBlockingDataSet ();
IMPORT int shellInOutBlockingGet ();
IMPORT int shellInOutBlockingOnDataClose ();
IMPORT int shellInOutBlockingOpen ();
IMPORT int shellInOutBlockingUnblock ();
IMPORT int shellInOutGet ();
IMPORT int shellInOutInitialGet ();
IMPORT int shellInOutInputHookAdd ();
IMPORT int shellInOutInputHookDelete ();
IMPORT int shellInOutInputHookSet ();
IMPORT int shellInOutInputHookUnset ();
IMPORT int shellInOutInputUniqueCheck ();
IMPORT int shellInOutMasterPtyGet ();
IMPORT int shellInOutRedirectClose ();
IMPORT int shellInOutRedirectOpen ();
IMPORT int shellInOutRedirectRestore ();
IMPORT int shellInOutRedirectScript ();
IMPORT int shellInOutRedirectSet ();
IMPORT int shellInOutSet ();
IMPORT int shellInOutSlavePtyGet ();
IMPORT int shellInOutUse ();
IMPORT int shellInternalArgStackAllocate ();
IMPORT int shellInternalArgumentEval ();
IMPORT int shellInternalDataSymbolGet ();
IMPORT int shellInternalDecValueDisplay ();
IMPORT int shellInternalFuncDoubleArgAdd ();
IMPORT int shellInternalFuncFloatArgAdd ();
IMPORT int shellInternalFuncIntArgAdd ();
IMPORT int shellInternalFuncLLongArgAdd ();
IMPORT int shellInternalFunctionCall ();
IMPORT int shellInternalHexValueDisplay ();
IMPORT int shellInternalKernelSymbolCreate ();
IMPORT int shellInternalOptFree ();
IMPORT int shellInternalOptGet ();
IMPORT int shellInternalStrSpaceTokenize ();
IMPORT int shellInternalStrToChar ();
IMPORT int shellInternalStrToFloat ();
IMPORT int shellInternalStrToInt ();
IMPORT int shellInternalStrToInt2 ();
IMPORT int shellInternalStrToInt32 ();
IMPORT int shellInternalStrTokenize ();
IMPORT int shellInternalStrUnquote ();
IMPORT int shellInternalSymTblFromRtpGet ();
IMPORT int shellInternalSymTblFromTaskGet ();
IMPORT int shellInternalSymbolDisplay ();
IMPORT int shellInternalSymbolGet ();
IMPORT int shellInternalSymbolsResolve ();
IMPORT int shellInternalTaskNameMatch ();
IMPORT int shellInternalTextSymbolGet ();
IMPORT int shellInternalValueDisplay ();
IMPORT int shellInterpByNameFind ();
IMPORT int shellInterpCInit ();
IMPORT int shellInterpC_create_buffer ();
IMPORT int shellInterpC_delete_buffer ();
IMPORT int shellInterpC_flush_buffer ();
IMPORT int shellInterpC_init_buffer ();
IMPORT int shellInterpC_load_buffer_state ();
IMPORT int shellInterpC_scan_buffer ();
IMPORT int shellInterpC_scan_bytes ();
IMPORT int shellInterpC_scan_string ();
IMPORT int shellInterpC_switch_to_buffer ();
IMPORT int shellInterpCin;
IMPORT int shellInterpCleng;
IMPORT int shellInterpClex ();
IMPORT int shellInterpCmdLibInit ();
IMPORT int shellInterpCout;
IMPORT int shellInterpCparse ();
IMPORT int shellInterpCrestart ();
IMPORT int shellInterpCtext;
IMPORT int shellInterpCtxCreate ();
IMPORT int shellInterpCtxGet ();
IMPORT int shellInterpDefaultNameGet ();
IMPORT int shellInterpDelete ();
IMPORT int shellInterpEvaluate ();
IMPORT int shellInterpLibInit ();
IMPORT int shellInterpNameGet ();
IMPORT int shellInterpPromptDftSet ();
IMPORT int shellInterpPromptGet ();
IMPORT int shellInterpPromptSet ();
IMPORT int shellInterpRegister ();
IMPORT int shellInterpRestart ();
IMPORT int shellInterpSet ();
IMPORT int shellInterpSwitch ();
IMPORT int shellLibInit ();
IMPORT int shellLineLenGet ();
IMPORT int shellLock ();
IMPORT int shellLoginInstall ();
IMPORT int shellLogout ();
IMPORT int shellLogout2 ();
IMPORT int shellLogoutInstall ();
IMPORT int shellMaxSessionsSet ();
IMPORT int shellMemAllRegFree ();
IMPORT int shellMemCalloc ();
IMPORT int shellMemFree ();
IMPORT int shellMemLibInit ();
IMPORT int shellMemMalloc ();
IMPORT int shellMemRealloc ();
IMPORT int shellMemRegAllFree ();
IMPORT int shellMemRegFree ();
IMPORT int shellMemRegMalloc ();
IMPORT int shellMemRegister ();
IMPORT int shellMemStrdup ();
IMPORT int shellMemStringAdd ();
IMPORT int shellMemStringFree ();
IMPORT int shellMemStringIsAllocated ();
IMPORT int shellMemStringShow ();
IMPORT int shellMemUnregister ();
IMPORT int shellNext ();
IMPORT int shellOutputLock ();
IMPORT int shellOutputUnlock ();
IMPORT int shellParserControl ();
IMPORT int shellPrint ();
IMPORT int shellPrintErr ();
IMPORT int shellPromptFmtDftSet ();
IMPORT int shellPromptFmtSet ();
IMPORT int shellPromptFmtStrAdd ();
IMPORT int shellPromptGet ();
IMPORT int shellPromptLibInit ();
IMPORT int shellPromptPrint ();
IMPORT int shellPromptSet ();
IMPORT int shellRemoteConfigStr;
IMPORT int shellResourceReleaseHookAdd ();
IMPORT int shellRestart ();
IMPORT int shellScriptAbort ();
IMPORT int shellScriptNoAbort ();
IMPORT int shellSecureInit ();
IMPORT int shellTask ();
IMPORT int shellTaskDefaultBaseNameGet ();
IMPORT int shellTaskDefaultBaseNameSet ();
IMPORT int shellTaskDefaultOptionsGet ();
IMPORT int shellTaskDefaultOptionsSet ();
IMPORT int shellTaskDefaultPriorityGet ();
IMPORT int shellTaskDefaultPrioritySet ();
IMPORT int shellTaskDefaultStackSizeGet ();
IMPORT int shellTaskDefaultStackSizeSet ();
IMPORT int shellTaskGet ();
IMPORT int shellTaskIdDefault ();
IMPORT int shellTerminate ();
IMPORT int shellWorkingMemCtxAttach ();
IMPORT int shellWorkingMemCtxAttachedShow ();
IMPORT int shellWorkingMemCtxCurrentGet ();
IMPORT int shellWorkingMemCtxCurrentSet ();
IMPORT int shellWorkingMemCtxDetach ();
IMPORT int shellWorkingMemCtxDuplicate ();
IMPORT int shellWorkingMemCtxGet ();
IMPORT int shellWorkingMemCtxIdConvert ();
IMPORT int shellWorkingMemCtxLastGet ();
IMPORT int shellWorkingMemCtxRtnSet ();
IMPORT int show ();
IMPORT int showLoggerInfo ();
IMPORT int showRtnTbl;
IMPORT int shutdown ();
IMPORT int sigEvtRtn;
IMPORT int sigFfsMsb ();
IMPORT int sigInit ();
IMPORT int sigPendDestroy ();
IMPORT int sigPendInit ();
IMPORT int sigPendKill ();
IMPORT int sigaction ();
IMPORT int sigaddset ();
IMPORT int sigblock ();
IMPORT int sigdelset ();
IMPORT int sigemptyset ();
IMPORT int sigfillset ();
IMPORT int sigismember ();
IMPORT int signal ();
IMPORT int sigpending ();
IMPORT int sigprocmask ();
IMPORT int sigqueue ();
IMPORT int sigqueueInit ();
IMPORT int sigreturn ();
IMPORT int sigsetjmp ();
IMPORT int sigsetmask ();
IMPORT int sigsuspend ();
IMPORT int sigtimedwait ();
IMPORT int sigvec ();
IMPORT int sigwait ();
IMPORT int sigwaitinfo ();
IMPORT int sin ();
IMPORT int sincos ();
IMPORT int sinh ();
IMPORT int sioChanConnect_desc;
IMPORT int sioChanGet_desc;
IMPORT int sioEnable_desc;
IMPORT int sioIntEnable_desc;
IMPORT int sioNextChannelNumberAssign ();
IMPORT int sizeNodesAlloc ();
IMPORT int sllCount ();
IMPORT SL_NODE *sllEach ();
IMPORT SL_NODE *sllGet ();
IMPORT int sllInit ();
IMPORT SL_NODE *sllPrevious ();
IMPORT void sllPutAtHead ();
IMPORT void sllPutAtTail ();
IMPORT void sllRemove ();
IMPORT int sllTerminate ();
IMPORT int smMemPartAddToPoolRtn;
IMPORT int smMemPartAllocRtn;
IMPORT int smMemPartFindMaxRtn;
IMPORT int smMemPartFreeRtn;
IMPORT int smMemPartOptionsSetRtn;
IMPORT int smMemPartReallocRtn;
IMPORT int smMemPartShowRtn;
IMPORT int smObjPoolMinusOne;
IMPORT int smObjTaskDeleteFailRtn;
IMPORT int smObjTcbFreeFailRtn;
IMPORT int smObjTcbFreeRtn;
IMPORT int snprintf ();
IMPORT int so ();
IMPORT int sockLibAdd ();
IMPORT int sockLibInit ();
IMPORT int sockLibMap;
IMPORT int socket ();
IMPORT int socketDevHdr;
IMPORT int socket_test ();
IMPORT int soft_watchdog_test ();
IMPORT int soft_watchdog_test2 ();
IMPORT int sp ();
IMPORT int spTaskOptions;
IMPORT int spTaskPriority;
IMPORT int spTaskStackSize;
IMPORT int speaker_test ();
IMPORT int spinLockIsrEhcd;
IMPORT int spinLockIsrGive ();
IMPORT int spinLockIsrInit ();
IMPORT int spinLockIsrTake ();
IMPORT int spinLockRestrict ();
IMPORT int spinLockTaskGive ();
IMPORT int spinLockTaskInit ();
IMPORT int spinLockTaskTake ();
IMPORT int sprintf ();
IMPORT int spy ();
IMPORT int spyClkStart ();
IMPORT int spyClkStop ();
IMPORT int spyHelp ();
IMPORT int spyReport ();
IMPORT int spyStop ();
IMPORT int spyTask ();
IMPORT int sqrt ();
IMPORT int srand ();
IMPORT int sscanf ();
IMPORT int stat ();
IMPORT int statSymTbl;
IMPORT int statfs ();
IMPORT int statfs64 ();
IMPORT int std_test ();
IMPORT int stdioFp ();
IMPORT int stdioFpCreate ();
IMPORT int stdioFpDestroy ();
IMPORT int stdioInit ();
IMPORT int stopApplLogger ();
IMPORT int strFree ();
IMPORT int strcasecmp ();
IMPORT int strcat ();
IMPORT int strchr ();
IMPORT int strcmp ();
IMPORT int strcoll ();
IMPORT int strcpy ();
IMPORT int strcspn ();
IMPORT int strdup ();
IMPORT int strerror ();
IMPORT int strerrorIf ();
IMPORT int strerror_r ();
IMPORT int strftime ();
IMPORT int strlcpy ();
IMPORT int strlen ();
IMPORT int strncasecmp ();
IMPORT int strncat ();
IMPORT int strncmp ();
IMPORT int strncpy ();
IMPORT int strpbrk ();
IMPORT int strrchr ();
IMPORT int strspn ();
IMPORT int strstr ();
IMPORT int strtod ();
IMPORT int strtok ();
IMPORT int strtok_r ();
IMPORT int strtol ();
IMPORT int strtoul ();
IMPORT int strxfrm ();
IMPORT int substrcmp ();
IMPORT int swab ();
IMPORT int symAdd ();
IMPORT int symByCNameFind ();
IMPORT int symByValueAndTypeFind ();
IMPORT int symByValueFind ();
IMPORT int symEach ();
IMPORT int symFindByName ();
IMPORT int symFindByNameAndType ();
IMPORT int symFindByValue ();
IMPORT int symFindByValueAndType ();
IMPORT int symFindSymbol ();
IMPORT int symFree ();
IMPORT int symGroupDefault;
IMPORT int symLibInit ();
IMPORT int symListGet ();
IMPORT int symLkupPgSz;
IMPORT int symName ();
IMPORT int symNameGet ();
IMPORT int symRegister ();
IMPORT int symRemove ();
IMPORT int symShow ();
IMPORT int symShowInit ();
IMPORT int symTblAdd ();
IMPORT int symTblCreate ();
IMPORT int symTblDelete ();
IMPORT int symTblRemove ();
IMPORT int symTblShutdown ();
IMPORT int symTblSymSetRemove ();
IMPORT int symTypeGet ();
IMPORT int symTypeToStringConvert ();
IMPORT int symValueGet ();
IMPORT int syncLoadRtn;
IMPORT int syncSymAddRtn;
IMPORT int syncSymRemoveRtn;
IMPORT int syncUnldRtn;
IMPORT int sysAdaEnable;
IMPORT int sysAddGdt ();
IMPORT int sysBootFile;
IMPORT int sysBootHost;
IMPORT int sysBootLine;
IMPORT int sysBootParams;
IMPORT int sysBp;
IMPORT int sysBspDevFilter_desc;
IMPORT int sysBspRev ();
IMPORT int sysBus;
IMPORT int sysBusIntAck ();
IMPORT int sysBusIntGen ();
IMPORT int sysBusTas ();
IMPORT int sysBusToLocalAdrs ();
IMPORT int sysClkConnect ();
IMPORT int sysClkDevUnitNo;
IMPORT int sysClkDisable ();
IMPORT int sysClkEnable ();
IMPORT int sysClkHandleGet ();
IMPORT int sysClkInit ();
IMPORT int sysClkRateGet ();
IMPORT int sysClkRateSet ();
IMPORT int sysClkTimerNo;
IMPORT int sysCoprocessor;
IMPORT int sysCplusEnable;
IMPORT int sysCpu;
IMPORT int sysCpuId;
IMPORT int sysCpuProbe ();
IMPORT int sysCr3;
IMPORT int sysCsExc;
IMPORT int sysCsInt;
IMPORT int sysCsSuper;
IMPORT int sysCsUser;
IMPORT int sysDelay ();
IMPORT int sysDsSuper;
IMPORT int sysDsUser;
IMPORT int sysExcMsg;
IMPORT int sysFlags;
IMPORT int sysGdt ();
IMPORT int sysGdtr ();
IMPORT int sysHwInit ();
IMPORT int sysHwInit0 ();
IMPORT int sysHwInit2 ();
IMPORT int sysIchAtaGive ();
IMPORT int sysIchAtaInit ();
IMPORT int sysIchAtaInit2 ();
IMPORT int sysIchAtaWait ();
IMPORT int sysInByte ();
IMPORT int sysInLong ();
IMPORT int sysInLongString ();
IMPORT int sysInWord ();
IMPORT int sysInWordString ();
IMPORT int sysInit ();
IMPORT int sysInitGDT ();
IMPORT int sysInstParamTable;
IMPORT int sysIntDisablePIC ();
IMPORT int sysIntEnablePIC ();
IMPORT int sysIntEoiGet ();
IMPORT int sysIntIdtType;
IMPORT int sysIntInitPIC ();
IMPORT int sysIntLevel ();
IMPORT int sysIntLock ();
IMPORT int sysIntLvlDisableRtn;
IMPORT int sysIntLvlEnableRtn;
IMPORT int sysIntUnlock ();
IMPORT int sysInumTbl;
IMPORT int sysInumTblNumEnt;
IMPORT int sysLoadGdt ();
IMPORT int sysLocalToBusAdrs ();
IMPORT int sysMailboxConnect ();
IMPORT int sysMailboxEnable ();
IMPORT int sysMemTop ();
IMPORT int sysMmuMapAdd ();
IMPORT int sysModel ();
IMPORT int sysNetMacNVRamAddrGet ();
IMPORT int sysNetPciInit ();
IMPORT int sysNvRamGet ();
IMPORT int sysNvRamSet ();
IMPORT int sysOSMGdtScratch;
IMPORT int sysOSMGdtScratchCurrent;
IMPORT int sysOSMLdt;
IMPORT int sysOSMLdtCurrent;
IMPORT int sysOSMTaskGateInit ();
IMPORT int sysOutByte ();
IMPORT int sysOutLong ();
IMPORT int sysOutLongString ();
IMPORT int sysOutWord ();
IMPORT int sysOutWordString ();
IMPORT int sysPciIvecToIrq ();
IMPORT int sysPhysMemDesc;
IMPORT int sysPhysMemDescNumEnt;
IMPORT int sysPhysMemTop ();
IMPORT int sysProcNum;
IMPORT int sysProcNumGet ();
IMPORT int sysProcNumSet ();
IMPORT int sysProcessor;
IMPORT int sysReboot ();
IMPORT int sysSerialChanConnect ();
IMPORT int sysSerialChanGet ();
IMPORT int sysSerialConnectAll ();
IMPORT int sysSsUser;
IMPORT int sysStart ();
IMPORT int sysStartType;
IMPORT int sysStrayInt ();
IMPORT int sysStrayIntCount;
IMPORT int sysSymPhysMemBottom;
IMPORT int sysSymPhysMemSize;
IMPORT int sysSymTbl;
IMPORT int sysTextProtect;
IMPORT int sysToMonitor ();
IMPORT int sysTss;
IMPORT int sysTssCurrent;
IMPORT int sysUsDelay ();
IMPORT int sysVmContext;
IMPORT int sysWait ();
IMPORT int sysWarmAtaCtrl;
IMPORT int sysWarmAtaDrive;
IMPORT int sysWarmFdDrive;
IMPORT int sysWarmFdType;
IMPORT int sysWarmTffsDrive;
IMPORT int sysWarmType;
IMPORT int sysctl ();
IMPORT int sysctlCtxList;
IMPORT int sysctlInit ();
IMPORT int sysctl__children;
IMPORT int sysctl_add_oid ();
IMPORT int sysctl_add_oid_internal ();
IMPORT int sysctl_ctx_entry_add ();
IMPORT int sysctl_ctx_entry_find ();
IMPORT int sysctl_ctx_free ();
IMPORT int sysctl_ctx_init ();
IMPORT int sysctl_find_oid ();
IMPORT int sysctl_handle_int ();
IMPORT int sysctl_handle_long ();
IMPORT int sysctl_handle_opaque ();
IMPORT int sysctl_handle_reg ();
IMPORT int sysctl_handle_string ();
IMPORT int sysctl_node;
IMPORT int sysctl_register_oid ();
IMPORT int sysctl_remove_oid ();
IMPORT int sysctl_sysctl_debug_dump_node ();
IMPORT int sysctl_unregister_oid ();
IMPORT int sysctlbyname ();
IMPORT int sysctlnametomib ();
IMPORT int system ();
IMPORT int tCanReceive2 ();
IMPORT int tCntComSync ();
IMPORT int tComRecv ();
IMPORT int tExcTaskExcStk;
IMPORT int tExcTaskStk;
IMPORT int tExcTaskTcb;
IMPORT int tPciCan ();
IMPORT int tPciCan2 ();
IMPORT int tPciIo ();
IMPORT int tTcpPerformRecv ();
IMPORT int tTcpServerRecv ();
IMPORT int tTestSem ();
IMPORT int tUdpBroadcastRecv ();
IMPORT int tUdpGroupRecv ();
IMPORT int tUdpServerRecv ();
IMPORT int tagCheckEvaluateAsserts ();
IMPORT int tagCheckModuleAdd ();
IMPORT int tagCheckModuleDel ();
IMPORT int tagCheckStatementAdd ();
IMPORT int taglist;
IMPORT int tan ();
IMPORT int tanh ();
IMPORT int taskATenable;
IMPORT int taskActivate ();
IMPORT int taskArgsGet ();
IMPORT int taskArgsSet ();
IMPORT int taskBpHook;
IMPORT int taskBpHookSet ();
IMPORT int taskClassId;
IMPORT int taskCont ();
IMPORT int taskCpuAffinityGet ();
IMPORT int taskCpuAffinitySet ();
IMPORT int taskCpuLock ();
IMPORT int taskCpuUnlock ();
IMPORT int taskCpuUnlockNoResched ();
IMPORT int taskCreat ();
IMPORT int taskCreate ();
IMPORT int taskCreateHookAdd ();
IMPORT int taskCreateHookDelete ();
IMPORT int taskCreateHookInit ();
IMPORT int taskCreateLibInit ();
IMPORT int taskCreateTable;
IMPORT int taskCreateWithGuard ();
IMPORT int taskDelay ();
IMPORT int taskDelete ();
IMPORT int taskDeleteForce ();
IMPORT int taskDeleteHookAdd ();
IMPORT int taskDeleteHookDelete ();
IMPORT int taskDeleteTable;
IMPORT int taskDestroy ();
IMPORT int taskEach ();
IMPORT int taskIdCurrent;
IMPORT int taskIdDefault ();
IMPORT int taskIdFigure ();
IMPORT int taskIdListGet ();
IMPORT int taskIdListSort ();
IMPORT int taskIdSelf ();
IMPORT int taskIdVerify ();
IMPORT int taskInfoGet ();
IMPORT int taskInit ();
IMPORT int taskInitExcStk ();
IMPORT int taskInitialize ();
IMPORT int taskIsDelayed ();
IMPORT int taskIsPended ();
IMPORT int taskIsReady ();
IMPORT int taskIsStopped ();
IMPORT int taskIsSuspended ();
IMPORT int taskKerExcStackSize;
IMPORT int taskKerExcStkOverflowSize;
IMPORT int taskKerExecStkOverflowSize;
IMPORT int taskKerExecStkUnderflowSize;
IMPORT int taskLibInit ();
IMPORT int taskListCount ();
IMPORT int taskLock ();
IMPORT int taskName ();
IMPORT int taskNameToId ();
IMPORT int taskOptionsGet ();
IMPORT int taskOptionsSet ();
IMPORT int taskOptionsString ();
IMPORT int taskPriNormalGet ();
IMPORT int taskPriorityGet ();
IMPORT int taskPrioritySet ();
IMPORT int taskRegName;
IMPORT int taskRegsFmt;
IMPORT int taskRegsGet ();
IMPORT int taskRegsInit ();
IMPORT int taskRegsModify ();
IMPORT int taskRegsSet ();
IMPORT int taskRegsShow ();
IMPORT int taskReservedFieldGet ();
IMPORT int taskReservedFieldSet ();
IMPORT int taskReservedNumAllot ();
IMPORT int taskReset ();
IMPORT int taskRestart ();
IMPORT int taskResume ();
IMPORT int taskRtnValueSet ();
IMPORT int taskSRSet ();
IMPORT int taskSafe ();
IMPORT int taskSchedInfoGet ();
IMPORT int taskShow ();
IMPORT int taskShowInit ();
IMPORT int taskSpareFieldGet ();
IMPORT int taskSpareFieldSet ();
IMPORT int taskSpareNumAllot ();
IMPORT int taskSpawn ();
IMPORT int taskStackAllot ();
IMPORT int taskStackSizeGet ();
IMPORT int taskStatusString ();
IMPORT int taskStop ();
IMPORT int taskStopForce ();
IMPORT int taskStopMsg;
IMPORT int taskSuspend ();
IMPORT int taskSwapHookAdd ();
IMPORT int taskSwapHookAttach ();
IMPORT int taskSwapHookDelete ();
IMPORT int taskSwapHookDetach ();
IMPORT int taskSwapReference;
IMPORT int taskSwapTable;
IMPORT int taskSwitchHookAdd ();
IMPORT int taskSwitchHookDelete ();
IMPORT int taskSwitchTable;
IMPORT int taskTcb ();
IMPORT int taskTerminate ();
IMPORT int taskUndelay ();
IMPORT int taskUnlock ();
IMPORT int taskUnsafe ();
IMPORT int taskUsrExcStackSize;
IMPORT int taskUsrExcStkOverflowSize;
IMPORT int taskUsrExecStkOverflowSize;
IMPORT int taskUsrExecStkUnderflowSize;
IMPORT int taskVarAdd ();
IMPORT int taskVarDelete ();
IMPORT int taskVarGet ();
IMPORT int taskVarInfo ();
IMPORT int taskVarInit ();
IMPORT int taskVarSet ();
IMPORT int taskWaitShow ();
IMPORT int taskWaitShowCoreRtn ();
IMPORT int tcbReserveBitmap;
IMPORT int tcbSpareBitmap;
IMPORT int tcp_client ();
IMPORT int tcp_rx_performance ();
IMPORT int tcp_server ();
IMPORT int tcp_tx_performance ();
IMPORT int td ();
IMPORT int ti ();
IMPORT int tick64Get ();
IMPORT int tick64Set ();
IMPORT int tickAnnounce ();
IMPORT int tickAnnounceHookAdd ();
IMPORT int tickGet ();
IMPORT int tickQHead;
IMPORT int tickSet ();
IMPORT int time ();
IMPORT int timer0_callback ();
IMPORT int timer0_test ();
IMPORT int timex ();
IMPORT int timexClear ();
IMPORT int timexFunc ();
IMPORT int timexHelp ();
IMPORT int timexInit ();
IMPORT int timexN ();
IMPORT int timexPost ();
IMPORT int timexPre ();
IMPORT int timexShow ();
IMPORT int tip ();
IMPORT int tipConfigString;
IMPORT int tipEscapeChar;
IMPORT int tipLibInit ();
IMPORT int tipStart ();
IMPORT int tmpfile ();
IMPORT int tmpnam ();
IMPORT int tolower ();
IMPORT int toupper ();
IMPORT int tr ();
IMPORT int trcDefaultArgs;
IMPORT int trcLibFuncs;
IMPORT int trcStack ();
IMPORT int trcStackCtxTrace ();
IMPORT int trcStackTrace ();
IMPORT int trcSyscallCheck ();
IMPORT int trunc ();
IMPORT int ts ();
IMPORT int tt ();
IMPORT int ttyDevCreate ();
IMPORT int ttyDrv ();
IMPORT int tw ();
IMPORT int tyAbortFuncGet ();
IMPORT int tyAbortFuncSet ();
IMPORT int tyAbortGet ();
IMPORT int tyAbortSet ();
IMPORT int tyBackspaceChar;
IMPORT int tyBackspaceSet ();
IMPORT int tyDeleteLineChar;
IMPORT int tyDeleteLineSet ();
IMPORT int tyDevInit ();
IMPORT int tyDevRemove ();
IMPORT int tyDevTerminate ();
IMPORT int tyEOFGet ();
IMPORT int tyEOFSet ();
IMPORT int tyEofChar;
IMPORT int tyIRd ();
IMPORT int tyITx ();
IMPORT int tyIoctl ();
IMPORT int tyLibInit ();
IMPORT int tyMonitorTrapSet ();
IMPORT int tyRead ();
IMPORT int tyWrite ();
IMPORT int tyXoffHookSet ();
IMPORT int uNum;
IMPORT int udpCommIfInit ();
IMPORT int udpRcv ();
IMPORT int udp_broadcast ();
IMPORT int udp_client ();
IMPORT int udp_client_2 ();
IMPORT int udp_group ();
IMPORT int udp_server ();
IMPORT int udp_task ();
IMPORT int ungetc ();
IMPORT int unld ();
IMPORT int unldByGroup ();
IMPORT int unldByModuleId ();
IMPORT int unldByNameAndPath ();
IMPORT int unldLibInit ();
IMPORT int unlink ();
IMPORT int unmount ();
IMPORT int usb2ClassDeviceAddCallbackSet ();
IMPORT int usb2ClassDeviceCreate ();
IMPORT int usb2ClassDeviceDelCallbackSet ();
IMPORT int usb2ClassDeviceDelete ();
IMPORT int usb2ClassDeviceIsValid ();
IMPORT int usb2ClassDriverCreate ();
IMPORT int usb2ClassDriverDelete ();
IMPORT int usb2DeviceDeleteHelperDeInit ();
IMPORT int usb2DeviceDeleteHelperInit ();
IMPORT int usb2DeviceDeleteMsgPost ();
IMPORT int usb2DriverIsEmpty ();
IMPORT int usb2FindEndpoint ();
IMPORT int usb2FindInterface ();
IMPORT int usb2HlpDebug;
IMPORT int usb2MscBlkDevCreate ();
IMPORT int usb2MscBlkDevIoctl ();
IMPORT int usb2MscBlkDevMount ();
IMPORT int usb2MscBlkDevStatusCheck ();
IMPORT int usb2MscBlkDevUnmount ();
IMPORT int usb2MscBulkInTransfer ();
IMPORT int usb2MscBulkOnlyGetMaxLun ();
IMPORT int usb2MscBulkOnlyMassStorageReset ();
IMPORT int usb2MscBulkOnlyResetEndpoints ();
IMPORT int usb2MscBulkOnlyResetRecovery ();
IMPORT int usb2MscBulkOnlyTransport ();
IMPORT int usb2MscBulkOutTransfer ();
IMPORT int usb2MscBulkTransfer ();
IMPORT int usb2MscCBICommandBlockReset ();
IMPORT int usb2MscCBICommandTransfer ();
IMPORT int usb2MscCBIResetRecovery ();
IMPORT int usb2MscCBIStatusTransfer ();
IMPORT int usb2MscCBITransport ();
IMPORT int usb2MscCheckOptimalInterface ();
IMPORT int usb2MscCommandSetTransport ();
IMPORT int usb2MscComplianceCase10Test ();
IMPORT int usb2MscComplianceCase11Test ();
IMPORT int usb2MscComplianceCase12Test ();
IMPORT int usb2MscComplianceCase13Test ();
IMPORT int usb2MscComplianceCase1Test ();
IMPORT int usb2MscComplianceCase2Test ();
IMPORT int usb2MscComplianceCase3Test ();
IMPORT int usb2MscComplianceCase4Test ();
IMPORT int usb2MscComplianceCase5Test ();
IMPORT int usb2MscComplianceCase6Test ();
IMPORT int usb2MscComplianceCase7Test ();
IMPORT int usb2MscComplianceCase8Test ();
IMPORT int usb2MscComplianceCase9Test ();
IMPORT int usb2MscComplianceClassSpecificRequestTest ();
IMPORT int usb2MscComplianceErrorRecoveryTest ();
IMPORT int usb2MscComplianceInquiryTest ();
IMPORT int usb2MscComplianceInterfaceDescriptorTest ();
IMPORT int usb2MscComplianceLogCBW ();
IMPORT int usb2MscComplianceLogCSW ();
IMPORT int usb2MscComplianceLogCurrentStatistics ();
IMPORT int usb2MscComplianceLogError ();
IMPORT int usb2MscComplianceLogFinalStatistics ();
IMPORT int usb2MscComplianceLogHstStatus ();
IMPORT int usb2MscComplianceLogInfo ();
IMPORT int usb2MscComplianceLogLangId ();
IMPORT int usb2MscComplianceLogWarning ();
IMPORT int usb2MscComplianceModeSelect10Test ();
IMPORT int usb2MscComplianceModeSelect6Test ();
IMPORT int usb2MscComplianceModeSense10Test ();
IMPORT int usb2MscComplianceModeSense6Test ();
IMPORT int usb2MscCompliancePowerUpTest ();
IMPORT int usb2MscCompliancePreliminaryProcedure ();
IMPORT int usb2MscCompliancePreventAllowMediumRemovalTest ();
IMPORT int usb2MscComplianceRead10Test ();
IMPORT int usb2MscComplianceRead12Test ();
IMPORT int usb2MscComplianceReadCapacityTest ();
IMPORT int usb2MscComplianceReadTOCTest ();
IMPORT int usb2MscComplianceRecoveryProcedure ();
IMPORT int usb2MscComplianceRequestSense ();
IMPORT int usb2MscComplianceRequestSenseTest ();
IMPORT int usb2MscComplianceSerialNumberTest ();
IMPORT int usb2MscComplianceStartStopUnitTest ();
IMPORT int usb2MscComplianceTestDeviceAdd ();
IMPORT int usb2MscComplianceTestDeviceRemove ();
IMPORT int usb2MscComplianceTestUnitReadyTest ();
IMPORT int usb2MscComplianceTransport ();
IMPORT int usb2MscComplianceTransportCommon ();
IMPORT int usb2MscComplianceVerify10Test ();
IMPORT int usb2MscComplianceVerifySerialNumber ();
IMPORT int usb2MscComplianceWrite10Test ();
IMPORT int usb2MscComplianceWrite12Test ();
IMPORT int usb2MscCompliancebCBLengthTest ();
IMPORT int usb2MscDebug;
IMPORT int usb2MscDirectAccessDeviceAdd ();
IMPORT int usb2MscDirectAccessDeviceRemove ();
IMPORT int usb2MscDirectAccessInit ();
IMPORT int usb2MscDirectAccessOpen ();
IMPORT int usb2MscDirectAccessScsiPassThrough ();
IMPORT int usb2MscDirectAccessUnInit ();
IMPORT int usb2MscDrvInit ();
IMPORT int usb2MscDrvUnInit ();
IMPORT int usb2MscFindOptimalInterface ();
IMPORT int usb2MscFixupAsciiString ();
IMPORT int usb2MscGetTotalLun ();
IMPORT int usb2MscInterruptInTransfer ();
IMPORT int usb2MscIsEndpointHalted ();
IMPORT int usb2MscResetDevice ();
IMPORT int usb2MscResetEndpoint ();
IMPORT int usb2MscScsiCheckReady ();
IMPORT int usb2MscScsiFormatUnit ();
IMPORT int usb2MscScsiHandleSenseData ();
IMPORT int usb2MscScsiInquiry ();
IMPORT int usb2MscScsiModeSense ();
IMPORT int usb2MscScsiModeSense10 ();
IMPORT int usb2MscScsiModeSense6 ();
IMPORT int usb2MscScsiRead10 ();
IMPORT int usb2MscScsiRead10Internal ();
IMPORT int usb2MscScsiReadCapacity10 ();
IMPORT int usb2MscScsiReadFormatCapacities ();
IMPORT int usb2MscScsiRequestSense ();
IMPORT int usb2MscScsiStartStopUnit ();
IMPORT int usb2MscScsiTestUnitReady ();
IMPORT int usb2MscScsiWrite10 ();
IMPORT int usb2MscScsiWrite10Internal ();
IMPORT int usb2MscStatusCheck ();
IMPORT int usb2MscTransport ();
IMPORT int usb2MscWriteProtectionCheck ();
IMPORT int usb2MscXbdEject ();
IMPORT int usb2MscXbdMediaTest ();
IMPORT int usb2MscXbdMount ();
IMPORT int usb2MscXbdTest ();
IMPORT int usb2MscXbdUnmount ();
IMPORT int usb2ReleaseDevice ();
IMPORT int usb2ReleaseDriver ();
IMPORT int usb2TakeDevice ();
IMPORT int usb2TakeDriver ();
IMPORT int usb2VendorClassSpecific ();
IMPORT int usb2WindViewLog ();
IMPORT int usb2WvFilter;
IMPORT int usbConfigCountGet ();
IMPORT int usbConfigDescrGet ();
IMPORT int usbDescrParse ();
IMPORT int usbDescrParseSkip ();
IMPORT int usbEhcdAddBandwidth ();
IMPORT int usbEhcdAddToFreeITDList ();
IMPORT int usbEhcdAddToFreeQHList ();
IMPORT int usbEhcdAddToFreeQTDList ();
IMPORT int usbEhcdAddToFreeSITDList ();
IMPORT int usbEhcdAlign ();
IMPORT int usbEhcdAsynchScheduleDisable ();
IMPORT int usbEhcdAsynchScheduleEnable ();
IMPORT int usbEhcdCalculateBusTime ();
IMPORT int usbEhcdCancelURB ();
IMPORT int usbEhcdCheckBandwidth ();
IMPORT int usbEhcdClearTTRequestComplete ();
IMPORT int usbEhcdCopyRHInterruptData ();
IMPORT int usbEhcdCreateInterruptTree ();
IMPORT int usbEhcdCreatePipe ();
IMPORT int usbEhcdCreateQTDs ();
IMPORT int usbEhcdDeletePipe ();
IMPORT int usbEhcdDestroyInterruptTree ();
IMPORT int usbEhcdDisableHC ();
IMPORT int usbEhcdExit ();
IMPORT int usbEhcdFillQTDBuffer ();
IMPORT int usbEhcdFormEmptyQH ();
IMPORT int usbEhcdFormEmptyQTD ();
IMPORT int usbEhcdFreeAllLists ();
IMPORT int usbEhcdGenerateITDs ();
IMPORT int usbEhcdGenerateSITDs ();
IMPORT int usbEhcdGetFrameNumber ();
IMPORT int usbEhcdGetFreeITD ();
IMPORT int usbEhcdGetFreeQH ();
IMPORT int usbEhcdGetFreeQTD ();
IMPORT int usbEhcdGetFreeSITD ();
IMPORT int usbEhcdISR ();
IMPORT int usbEhcdInit ();
IMPORT int usbEhcdInstantiate ();
IMPORT int usbEhcdInterruptHandler ();
IMPORT int usbEhcdIsBandwidthAvailable ();
IMPORT int usbEhcdIsRequestPending ();
IMPORT int usbEhcdLinkITDs ();
IMPORT int usbEhcdLinkSITDs ();
IMPORT int usbEhcdModifyDefaultPipe ();
IMPORT int usbEhcdRHCancelURB ();
IMPORT int usbEhcdRHDeletePipe ();
IMPORT int usbEhcdRHSubmitURB ();
IMPORT int usbEhcdResetTTRequestComplete ();
IMPORT int usbEhcdRhClearPortFeature ();
IMPORT int usbEhcdRhCreatePipe ();
IMPORT int usbEhcdRhGetHubDescriptor ();
IMPORT int usbEhcdRhGetPortStatus ();
IMPORT int usbEhcdRhProcessClassSpecificRequest ();
IMPORT int usbEhcdRhProcessControlRequest ();
IMPORT int usbEhcdRhProcessInterruptRequest ();
IMPORT int usbEhcdRhProcessStandardRequest ();
IMPORT int usbEhcdRhSetPortFeature ();
IMPORT int usbEhcdSetBitRate ();
IMPORT int usbEhcdSubBandwidth ();
IMPORT int usbEhcdSubDeviceBandwidth ();
IMPORT int usbEhcdSubmitURB ();
IMPORT int usbEhcdUnLinkITD ();
IMPORT int usbEhcdUnLinkSITD ();
IMPORT int usbEhcdUpdateBandwidth ();
IMPORT int usbEhcdUpdateITDData ();
IMPORT int usbEhcdUpdateNonIsochStatusAndBytes ();
IMPORT int usbEhcdUpdateSITDData ();
IMPORT int usbExit ();
IMPORT int usbHidIdleSet ();
IMPORT int usbHidProtocolSet ();
IMPORT int usbHidReportSet ();
IMPORT int usbHstBusDeregister ();
IMPORT int usbHstBusRegister ();
IMPORT int usbHstClearFeature ();
IMPORT int usbHstCommonCallback ();
IMPORT int usbHstDriverDeregister ();
IMPORT int usbHstDriverRegister ();
IMPORT int usbHstGetConfiguration ();
IMPORT int usbHstGetDescriptor ();
IMPORT int usbHstGetFrameNumber ();
IMPORT int usbHstGetInterface ();
IMPORT int usbHstGetStatus ();
IMPORT int usbHstHCDDeregister ();
IMPORT int usbHstHCDRegister ();
IMPORT int usbHstResetDevice ();
IMPORT int usbHstSelectiveResume ();
IMPORT int usbHstSelectiveSuspend ();
IMPORT int usbHstSetBitRate ();
IMPORT int usbHstSetConfiguration ();
IMPORT int usbHstSetDescriptor ();
IMPORT int usbHstSetFeature ();
IMPORT int usbHstSetInterface ();
IMPORT int usbHstSetSynchFrame ();
IMPORT int usbHstURBCancel ();
IMPORT int usbHstURBSubmit ();
IMPORT int usbHstWaitUrbComplete ();
IMPORT int usbHubExit ();
IMPORT int usbHubGetRootHubHandle ();
IMPORT int usbHubInit ();
IMPORT int usbHubNodeIDGet ();
IMPORT int usbHubPollingIntervalGet ();
IMPORT int usbHubPollingIntervalSet ();
IMPORT int usbHubPortCntGet ();
IMPORT int usbInit ();
IMPORT int usbListFirst ();
IMPORT int usbListLink ();
IMPORT int usbListLinkProt ();
IMPORT int usbListNext ();
IMPORT int usbListUnlink ();
IMPORT int usbListUnlinkProt ();
IMPORT int usbLogMsg ();
IMPORT int usbMemToPci ();
IMPORT int usbOhcdInit ();
IMPORT int usbOhciExit ();
IMPORT int usbOhciInstantiate ();
IMPORT int usbOhciPowerOffPorts ();
IMPORT int usbPciByteGet ();
IMPORT int usbPciByteIn ();
IMPORT int usbPciByteOut ();
IMPORT int usbPciConfigHeaderGet ();
IMPORT int usbPciDwordGet ();
IMPORT int usbPciDwordIn ();
IMPORT int usbPciDwordOut ();
IMPORT int usbPciIntConnect ();
IMPORT int usbPciIntRestore ();
IMPORT int usbPciMemFlush ();
IMPORT int usbPciMemInvalidate ();
IMPORT int usbPciMemioOffset ();
IMPORT int usbPciToMem ();
IMPORT int usbPciWordGet ();
IMPORT int usbPciWordIn ();
IMPORT int usbPciWordOut ();
IMPORT int usbRecurringTime ();
IMPORT int usbTransferTime ();
IMPORT int usbUhcdCalculateBusTime ();
IMPORT int usbUhcdCanIsoBeAccomodated ();
IMPORT int usbUhcdCancelRhRequest ();
IMPORT int usbUhcdCancelUrb ();
IMPORT int usbUhcdClearPortFeature ();
IMPORT int usbUhcdCleartdOnSysError ();
IMPORT int usbUhcdCompletedTdHandler ();
IMPORT int usbUhcdCopy ();
IMPORT int usbUhcdCreateFrameList ();
IMPORT int usbUhcdCreatePipe ();
IMPORT int usbUhcdDeleteFrameList ();
IMPORT int usbUhcdDeletePipe ();
IMPORT int usbUhcdDeleteQhContext ();
IMPORT int usbUhcdEnterCritical ();
IMPORT int usbUhcdExit ();
IMPORT int usbUhcdFillIsoStatus ();
IMPORT int usbUhcdFillNonisoStatus ();
IMPORT int usbUhcdFindHcdPipe ();
IMPORT int usbUhcdFindLinkForQh ();
IMPORT int usbUhcdFindPosForIntQh ();
IMPORT int usbUhcdFindQlinkToTree ();
IMPORT int usbUhcdFindTreeBw ();
IMPORT int usbUhcdFormEmptyPipe ();
IMPORT int usbUhcdFormEmptyQh ();
IMPORT int usbUhcdFormEmptyTd ();
IMPORT int usbUhcdFreeTds ();
IMPORT int usbUhcdGdConfigDescriptor;
IMPORT int usbUhcdGdDeviceDescriptor;
IMPORT int usbUhcdGetBit ();
IMPORT int usbUhcdGetBusState ();
IMPORT int usbUhcdGetConfiguration ();
IMPORT int usbUhcdGetCurrentEndpointDetails ();
IMPORT int usbUhcdGetDescriptor ();
IMPORT int usbUhcdGetDetailsForEndpoints ();
IMPORT int usbUhcdGetFrameNumber ();
IMPORT int usbUhcdGetHubDescriptor ();
IMPORT int usbUhcdGetHubStatus ();
IMPORT int usbUhcdGetIsoTransferLength ();
IMPORT int usbUhcdGetPortStatus ();
IMPORT int usbUhcdGetStatus ();
IMPORT int usbUhcdGetTransferLength ();
IMPORT int usbUhcdHcReset ();
IMPORT int usbUhcdInit ();
IMPORT int usbUhcdInstantiate ();
IMPORT int usbUhcdIsBandwidthAvailable ();
IMPORT int usbUhcdIsBitReset ();
IMPORT int usbUhcdIsBitSet ();
IMPORT int usbUhcdIsLinked ();
IMPORT int usbUhcdIsRequestPending ();
IMPORT int usbUhcdIsValidPipe ();
IMPORT int usbUhcdIsr ();
IMPORT int usbUhcdLeaveCritical ();
IMPORT int usbUhcdLinkItds ();
IMPORT int usbUhcdLinkQheadBetween ();
IMPORT int usbUhcdMakeFrameelementLE ();
IMPORT int usbUhcdMakeIsocTds ();
IMPORT int usbUhcdMakeQDLE ();
IMPORT int usbUhcdMakeTDLE ();
IMPORT int usbUhcdMakeTds ();
IMPORT int usbUhcdMaxIsoBwLinkedTo ();
IMPORT int usbUhcdModifyDefaultPipe ();
IMPORT int usbUhcdPortClearBit ();
IMPORT int usbUhcdPortSetBit ();
IMPORT int usbUhcdProcessCompletedTds ();
IMPORT int usbUhcdProcessIsocTds ();
IMPORT int usbUhcdProcessRhControlTransfer ();
IMPORT int usbUhcdProcessRhInterruptTransfer ();
IMPORT int usbUhcdQueueRhRequest ();
IMPORT int usbUhcdReadReg ();
IMPORT int usbUhcdRegxClearBit ();
IMPORT int usbUhcdRegxSetBit ();
IMPORT int usbUhcdRhCreatePipe ();
IMPORT int usbUhcdRhDeletePipe ();
IMPORT int usbUhcdSetBitRate ();
IMPORT int usbUhcdSetConfiguration ();
IMPORT int usbUhcdSetPortFeature ();
IMPORT int usbUhcdSubmitUrb ();
IMPORT int usbUhcdUnlinkItds ();
IMPORT int usbUhcdWriteReg ();
IMPORT int usbUhciDelay ();
IMPORT int usbUhciLog2 ();
IMPORT int usbVxbRootHubAdd ();
IMPORT int usbVxbRootHubRemove ();
IMPORT int usb_test ();
IMPORT int usbdAddressGet ();
IMPORT int usbdAddressSet ();
IMPORT int usbdBusCntGet ();
IMPORT int usbdBusCountGet ();
IMPORT int usbdBusStateSet ();
IMPORT int usbdClientRegister ();
IMPORT int usbdClientUnregister ();
IMPORT int usbdConfigurationGet ();
IMPORT int usbdConfigurationSet ();
IMPORT int usbdCurrentFrameGet ();
IMPORT int usbdDescriptorGet ();
IMPORT int usbdDescriptorSet ();
IMPORT int usbdDynamicAttachRegister ();
IMPORT int usbdDynamicAttachUnRegister ();
IMPORT int usbdExit ();
IMPORT int usbdFeatureClear ();
IMPORT int usbdFeatureSet ();
IMPORT int usbdFrameWindowGet ();
IMPORT int usbdHubPortCountGet ();
IMPORT int usbdInit ();
IMPORT int usbdInitialize ();
IMPORT int usbdInterfaceGet ();
IMPORT int usbdInterfaceSet ();
IMPORT int usbdMngmtCallbackSet ();
IMPORT int usbdNodeIdGet ();
IMPORT int usbdNodeInfoGet ();
IMPORT int usbdOsalDbg;
IMPORT int usbdPipeCreate ();
IMPORT int usbdPipeDestroy ();
IMPORT int usbdRootNodeIDGet ();
IMPORT int usbdRootNodeIdGet ();
IMPORT int usbdShutdown ();
IMPORT int usbdStatisticsGet ();
IMPORT int usbdStatusGet ();
IMPORT int usbdSynchFrameGet ();
IMPORT int usbdTransfer ();
IMPORT int usbdTransferAbort ();
IMPORT int usbdTranslateDeviceHandle ();
IMPORT int usbdTranslationInit ();
IMPORT int usbdVendorSpecific ();
IMPORT int usbdVersionGet ();
IMPORT int usbtuClientList;
IMPORT int usbtuDataUrbCompleteCallback ();
IMPORT int usbtuDataVendorSpecificCallback ();
IMPORT int usbtuDevList;
IMPORT int usbtuInitClientIrpCompleteThreadFn ();
IMPORT int usbtuInitDeviceAdd ();
IMPORT int usbtuInitDeviceRemove ();
IMPORT int usbtuInitDeviceResume ();
IMPORT int usbtuInitDeviceSuspend ();
IMPORT int usbtuInitFindDriverInfo ();
IMPORT int usbtuInitHandleClientEvent ();
IMPORT int usbtuInitHandleDeviceEvent ();
IMPORT int usbtuInitWvFilter;
IMPORT int usbtuMutex;
IMPORT int userUsb2MscPrintBuffer ();
IMPORT int usrAppInit ();
IMPORT int usrBootLineCrack ();
IMPORT int usrBootLineGet ();
IMPORT int usrBootLineInit ();
IMPORT int usrBootLineParse ();
IMPORT int usrBreakpointSet ();
IMPORT int usrCacheEnable ();
IMPORT int usrClock ();
IMPORT int usrDosfsInit ();
IMPORT int usrFtpInit ();
IMPORT int usrInit ();
IMPORT int usrIosCoreInit ();
IMPORT int usrIosExtraInit ();
IMPORT int usrIsrDeferInit ();
IMPORT int usrKernelCoreInit ();
IMPORT int usrKernelExtraInit ();
IMPORT int usrKernelInit ();
IMPORT int usrLoaderInit ();
IMPORT int usrMmuInit ();
IMPORT int usrModuleLoad ();
IMPORT int usrNetAppInit ();
IMPORT int usrNetApplUtilInit ();
IMPORT int usrNetBoot ();
IMPORT int usrNetDaemonInit ();
IMPORT int usrNetDevNameGet ();
IMPORT int usrNetEndLibInit ();
IMPORT int usrNetHostInit ();
IMPORT int usrNetIfconfigInit ();
IMPORT int usrNetRemoteCreate ();
IMPORT int usrNetRemoteInit ();
IMPORT int usrNetUtilsInit ();
IMPORT int usrNetmaskGet ();
IMPORT int usrNetworkInit ();
IMPORT int usrPcConsoleInit ();
IMPORT int usrRoot ();
IMPORT int usrRtpAppInit ();
IMPORT int usrSecurity ();
IMPORT int usrSerialInit ();
IMPORT int usrShell ();
IMPORT int usrShellInit ();
IMPORT int usrShowInit ();
IMPORT int usrStandaloneInit ();
IMPORT int usrSymTblInit ();
IMPORT int usrSysHwInit2 ();
IMPORT int usrSysSymTblInit ();
IMPORT int usrSysctlInit ();
IMPORT int usrTipInit ();
IMPORT int usrToolsInit ();
IMPORT int usrUsb2HelperInit ();
IMPORT int usrUsb2MscCommandTimeoutGet ();
IMPORT int usrUsb2MscCommandTimeoutSet ();
IMPORT int usrUsb2MscComplianceEnabled ();
IMPORT int usrUsb2MscComplianceEnabledSet ();
IMPORT int usrUsb2MscComplianceTestLogFileBaseNameSet ();
IMPORT int usrUsb2MscComplianceTestLogFileClose ();
IMPORT int usrUsb2MscComplianceTestLogFileOpen ();
IMPORT int usrUsb2MscDefaultMediumChangeCallback ();
IMPORT int usrUsb2MscDirectAccessEnabled ();
IMPORT int usrUsb2MscDirectAccessEnabledSet ();
IMPORT int usrUsb2MscDrvNameGet ();
IMPORT int usrUsb2MscDumpQuirkyDevices ();
IMPORT int usrUsb2MscFilesystemInterfaceGet ();
IMPORT int usrUsb2MscFilesystemInterfaceSet ();
IMPORT int usrUsb2MscInit ();
IMPORT int usrUsb2MscLookupQuirkyInfo ();
IMPORT int usrUsb2MscMaxBlocksPerTransferGet ();
IMPORT int usrUsb2MscMaxBlocksPerTransferSet ();
IMPORT int usrUsb2MscMediumHotplugCheckEabled ();
IMPORT int usrUsb2MscMediumHotplugCheckEabledSet ();
IMPORT int usrUsb2MscMediumHotplugCheckIntervalGet ();
IMPORT int usrUsb2MscMediumHotplugCheckIntervalSet ();
IMPORT int usrUsb2MscNameInstall ();
IMPORT int usrUsb2MscNameUninstall ();
IMPORT int usrUsb2MscReserveDevice ();
IMPORT int usrUsb2MscResetTimeoutGet ();
IMPORT int usrUsb2MscResetTimeoutSet ();
IMPORT int usrUsb2MscServiceTaskNameGet ();
IMPORT int usrUsb2MscServiceTaskOptionsGet ();
IMPORT int usrUsb2MscServiceTaskOptionsSet ();
IMPORT int usrUsb2MscServiceTaskPriorityGet ();
IMPORT int usrUsb2MscServiceTaskPrioritySet ();
IMPORT int usrUsb2MscServiceTaskStackSizeGet ();
IMPORT int usrUsb2MscServiceTaskStackSizeSet ();
IMPORT int usrUsb2MscStatusCheckEnabled ();
IMPORT int usrUsb2MscStatusCheckEnabledSet ();
IMPORT int usrUsb2MscStatusTimeoutGet ();
IMPORT int usrUsb2MscStatusTimeoutSet ();
IMPORT int usrUsb2MscTest ();
IMPORT int usrUsb2MscUninit ();
IMPORT int usrUsb2MscUnreserveDevice ();
IMPORT int usrUsb2MscWriteProtectionCheckEnabled ();
IMPORT int usrUsb2MscWriteProtectionCheckEnabledSet ();
IMPORT int usrUsb2MscXbdDirectBioEnabled ();
IMPORT int usrUsbHubInit ();
IMPORT int usrUsbResubmitUrbCheckEnabled ();
IMPORT int usrUsbWaitTimeOutValueGet ();
IMPORT int usrVxbTimerSysInit ();
IMPORT int usrWdbBanner ();
IMPORT int usrWdbBp ();
IMPORT int usrWdbGopherInit ();
IMPORT int usrWdbInit ();
IMPORT int usrWdbInitDone ();
IMPORT int usr_ext_node;
IMPORT int uswab ();
IMPORT int utime ();
IMPORT int valloc ();
IMPORT int version ();
IMPORT int vfdprintf ();
IMPORT int vfprintf ();
IMPORT int vgaCurAttrib_desc;
IMPORT int vgaCursorMove_desc;
IMPORT int vgaCursorSet_desc;
IMPORT int vgaScreenRev_desc;
IMPORT int viLedLibInit ();
IMPORT int vmBaseGlobalMapInit ();
IMPORT int vmBaseLibInit ();
IMPORT int vmBasePageSizeGet ();
IMPORT int vmBaseStateSet ();
IMPORT int vmBufferWrite ();
IMPORT int vmContextClassId;
IMPORT int vmContigBlockEach ();
IMPORT int vmCurrentGet ();
IMPORT int vmGlobalMapInit ();
IMPORT int vmInfoGet ();
IMPORT int vmKernelContextIdGet ();
IMPORT int vmLibInfo;
IMPORT int vmMap ();
IMPORT int vmMaxPhysBitsGet ();
IMPORT int vmPageLock ();
IMPORT int vmPageMap ();
IMPORT int vmPageOptimize ();
IMPORT int vmPageSizeGet ();
IMPORT int vmPageUnlock ();
IMPORT int vmPgMap ();
IMPORT int vmPhysTranslate ();
IMPORT int vmStateGet ();
IMPORT int vmStateSet ();
IMPORT int vmTextProtect ();
IMPORT int vmTranslate ();
IMPORT int vm_node;
IMPORT int voprintf ();
IMPORT int vprintf ();
IMPORT int vsnprintf ();
IMPORT int vsprintf ();
IMPORT int vxAbsTicks;
IMPORT int vxAtomicAdd ();
IMPORT int vxAtomicAnd ();
IMPORT int vxAtomicClear ();
IMPORT int vxAtomicDec ();
IMPORT int vxAtomicGet ();
IMPORT int vxAtomicInc ();
IMPORT int vxAtomicNand ();
IMPORT int vxAtomicOr ();
IMPORT int vxAtomicQuadRead ();
IMPORT int vxAtomicQuadWrite ();
IMPORT int vxAtomicSet ();
IMPORT int vxAtomicSub ();
IMPORT int vxAtomicXor ();
IMPORT int vxBaseCpuPhysIndex;
IMPORT int vxC1StateSet ();
IMPORT int vxCas ();
IMPORT int vxCpuConfigured;
IMPORT int vxCpuConfiguredGet ();
IMPORT int vxCpuCount;
IMPORT int vxCpuEnabled;
IMPORT int vxCpuEnabledGet ();
IMPORT int vxCpuIdGet ();
IMPORT int vxCpuIndexGet ();
IMPORT int vxCpuLoApicId ();
IMPORT int vxCpuReserve ();
IMPORT int vxCpuReservedGet ();
IMPORT int vxCpuSetConfigured;
IMPORT int vxCpuSetReserved;
IMPORT int vxCpuSetReservedAvail;
IMPORT int vxCpuUnreserve ();
IMPORT int vxCr0Get ();
IMPORT int vxCr0Set ();
IMPORT int vxCr2Get ();
IMPORT int vxCr2Set ();
IMPORT int vxCr3Get ();
IMPORT int vxCr3Set ();
IMPORT int vxCr4Get ();
IMPORT int vxCr4Set ();
IMPORT int vxCsGet ();
IMPORT int vxDrGet ();
IMPORT int vxDrSet ();
IMPORT int vxDsGet ();
IMPORT int vxEflagsGet ();
IMPORT int vxEflagsSet ();
IMPORT int vxEventPendQ;
IMPORT int vxGdtrGet ();
IMPORT int vxGdtrSet ();
IMPORT int vxIOProbeSup ();
IMPORT int vxIOProbeTrap ();
IMPORT int vxIdleEntHookRtn ();
IMPORT int vxIdleExtHookRtn ();
IMPORT int vxIdleNent;
IMPORT int vxIdleNext;
IMPORT int vxIdleTick1st;
IMPORT int vxIdleTickBusy;
IMPORT int vxIdleTickEnt;
IMPORT int vxIdleTickExt;
IMPORT int vxIdleTickIdle;
IMPORT int vxIdleTsc1st;
IMPORT int vxIdleTscBusy;
IMPORT int vxIdleTscEnt;
IMPORT int vxIdleTscExt;
IMPORT int vxIdleTscIdle;
IMPORT int vxIdleUtilGet ();
IMPORT int vxIdtrGet ();
IMPORT int vxIntStackBase;
IMPORT int vxIntStackEnabled;
IMPORT int vxIntStackEnd;
IMPORT int vxIntStackOverflowSize;
IMPORT int vxIntStackPtr;
IMPORT int vxIntStackUnderflowSize;
IMPORT int vxKernelSchedDesc;
IMPORT int vxLdtrGet ();
IMPORT int vxLdtrSet ();
IMPORT int vxMemArchProbe ();
IMPORT int vxMemArchProbeInit ();
IMPORT int vxMemCommonProbe ();
IMPORT int vxMemProbe ();
IMPORT int vxMemProbeByteRead ();
IMPORT int vxMemProbeByteWrite ();
IMPORT int vxMemProbeErrorRtn ();
IMPORT int vxMemProbeInit ();
IMPORT int vxMemProbeLongRead ();
IMPORT int vxMemProbeLongWrite ();
IMPORT int vxMemProbeSup ();
IMPORT int vxMemProbeWordRead ();
IMPORT int vxMemProbeWordWrite ();
IMPORT int vxRsdpPtr;
IMPORT int vxSsGet ();
IMPORT int vxTas ();
IMPORT int vxTaskEntry ();
IMPORT int vxTssGet ();
IMPORT int vxTssSet ();
IMPORT char * vxWorksVersion;
IMPORT const unsigned int vxWorksVersionMaint;
IMPORT const unsigned int vxWorksVersionMajor;
IMPORT const unsigned int vxWorksVersionMinor;
IMPORT int vxbAccessFree ();
IMPORT int vxbBusAnnounce ();
IMPORT int vxbBusListLock;
IMPORT int vxbBusTypeRegister ();
IMPORT int vxbBusTypeString ();
IMPORT int vxbBusTypeUnregister ();
IMPORT int vxbDelay ();
IMPORT int vxbDelayLibInit ();
IMPORT int vxbDelayTimerFreeRunning;
IMPORT int vxbDevAccessAnnounce ();
IMPORT int vxbDevConnect ();
IMPORT int vxbDevConnectInternal ();
IMPORT int vxbDevInit ();
IMPORT int vxbDevInitInternal ();
IMPORT int vxbDevIterate ();
IMPORT int vxbDevMethodGet ();
IMPORT int vxbDevMethodRun ();
IMPORT int vxbDevParent ();
IMPORT int vxbDevPath ();
IMPORT int vxbDevRegMap_desc;
IMPORT int vxbDevRegister ();
IMPORT int vxbDevRemovalAnnounce ();
IMPORT int vxbDevStructAlloc ();
IMPORT int vxbDevStructFree ();
IMPORT int vxbDevStructListLock;
IMPORT int vxbDeviceAnnounce ();
IMPORT int vxbDeviceDriverRelease ();
IMPORT int vxbDeviceMethodRun ();
IMPORT int vxbDriverUnregister ();
IMPORT int vxbDrvRescan ();
IMPORT int vxbDrvUnlink_desc;
IMPORT int vxbDrvVerCheck ();
IMPORT int vxbFileNvRamGet ();
IMPORT int vxbFileNvRamRegister ();
IMPORT int vxbFileNvRamSet ();
IMPORT int vxbGlobalListsLock;
IMPORT int vxbI8253TimerDrvRegister ();
IMPORT int vxbInit ();
IMPORT int vxbInstByNameFind ();
IMPORT int vxbInstParamByIndexGet ();
IMPORT int vxbInstParamByNameGet ();
IMPORT int vxbInstParamSet ();
IMPORT int vxbInstUnitGet ();
IMPORT int vxbInstUnitSet ();
IMPORT int vxbIntAcknowledge ();
IMPORT int vxbIntConnect ();
IMPORT int vxbIntCtlrAck_desc;
IMPORT int vxbIntCtlrConnect_desc;
IMPORT int vxbIntCtlrCpuReroute_desc;
IMPORT int vxbIntCtlrDisable_desc;
IMPORT int vxbIntCtlrDisconnect_desc;
IMPORT int vxbIntCtlrEnable_desc;
IMPORT int vxbIntCtlrIntReroute_desc;
IMPORT int vxbIntDisable ();
IMPORT int vxbIntDisconnect ();
IMPORT int vxbIntDynaVecDisable_desc;
IMPORT int vxbIntDynaVecEnable_desc;
IMPORT int vxbIntDynaVecProgram_desc;
IMPORT int vxbIntEnable ();
IMPORT int vxbIntVectorGet ();
IMPORT int vxbIntelIchStorageRegister ();
IMPORT int vxbIoApicIntrDrvRegister ();
IMPORT int vxbIoApicIntrShowAll ();
IMPORT int vxbLibError ();
IMPORT int vxbLibInit ();
IMPORT int vxbLockDelete ();
IMPORT int vxbLockGive ();
IMPORT int vxbLockInit ();
IMPORT int vxbLockTake ();
IMPORT int vxbMpApicDataShow ();
IMPORT int vxbMpApicDrvRegister ();
IMPORT int vxbMpBiosIoIntMapShow ();
IMPORT int vxbMpBiosLocalIntMapShow ();
IMPORT int vxbMpBiosShow ();
IMPORT int vxbMsDelay ();
IMPORT int vxbNextUnitGet ();
IMPORT int vxbNonVolGet ();
IMPORT int vxbNonVolLibInit ();
IMPORT int vxbNonVolSet ();
IMPORT int vxbPciAccessCookieSet ();
IMPORT int vxbPciAccessInit ();
IMPORT int vxbPciBusCfgRead ();
IMPORT int vxbPciBusCfgWrite ();
IMPORT int vxbPciBusTypeInit ();
IMPORT int vxbPciConfigBdfPack ();
IMPORT int vxbPciConfigExtCapFind ();
IMPORT int vxbPciConfigForeachFunc ();
IMPORT int vxbPciConfigInByte ();
IMPORT int vxbPciConfigInLong ();
IMPORT int vxbPciConfigInWord ();
IMPORT int vxbPciConfigLibInit ();
IMPORT int vxbPciConfigModifyByte ();
IMPORT int vxbPciConfigModifyLong ();
IMPORT int vxbPciConfigModifyWord ();
IMPORT int vxbPciConfigOutByte ();
IMPORT int vxbPciConfigOutLong ();
IMPORT int vxbPciConfigOutWord ();
IMPORT int vxbPciConfigReset ();
IMPORT int vxbPciDevCfgRead ();
IMPORT int vxbPciDevCfgWrite ();
IMPORT int vxbPciDevConfig ();
IMPORT int vxbPciFindClass ();
IMPORT int vxbPciFindDevice ();
IMPORT int vxbPciInt ();
IMPORT int vxbPciIntConnect ();
IMPORT int vxbPciIntDisconnect ();
IMPORT int vxbPciIntDisconnect2 ();
IMPORT int vxbPciIntLibInit ();
IMPORT int vxbPciMSICtl ();
IMPORT int vxbPciMSIDisable ();
IMPORT int vxbPciMSIEnable ();
IMPORT int vxbPciMSIIsCap ();
IMPORT int vxbPciMSIProgram ();
IMPORT int vxbPciSpecialCycle ();
IMPORT int vxbRead16 ();
IMPORT int vxbRead32 ();
IMPORT int vxbRead64 ();
IMPORT int vxbRead8 ();
IMPORT int vxbRegMap ();
IMPORT int vxbResourceFind ();
IMPORT int vxbSerialChanGet ();
IMPORT int vxbSubDevAction ();
IMPORT int vxbSwap16 ();
IMPORT int vxbSwap32 ();
IMPORT int vxbSwap64 ();
IMPORT int vxbSysClkConnect ();
IMPORT int vxbSysClkDisable ();
IMPORT int vxbSysClkEnable ();
IMPORT int vxbSysClkLibInit ();
IMPORT int vxbSysClkRateGet ();
IMPORT int vxbSysClkRateSet ();
IMPORT int vxbTimerAlloc ();
IMPORT int vxbTimerFeaturesGet ();
IMPORT int vxbTimerFuncGet_desc;
IMPORT int vxbTimerNumberGet_desc;
IMPORT int vxbTimerRelease ();
IMPORT int vxbUsDelay ();
IMPORT int vxbUsbEhciRegister ();
IMPORT int vxbUsbHcdUhciDevDeregister ();
IMPORT int vxbUsbOhciRegister ();
IMPORT int vxbUsbUhciRegister ();
IMPORT int vxbWrite16 ();
IMPORT int vxbWrite32 ();
IMPORT int vxbWrite64 ();
IMPORT int vxbWrite8 ();
IMPORT int vxdbgBpAdd ();
IMPORT int vxdbgBpAddrCheck ();
IMPORT int vxdbgBpAllDisable ();
IMPORT int vxdbgBpDelete ();
IMPORT int vxdbgBpFind ();
IMPORT int vxdbgBpList;
IMPORT int vxdbgBpMsgDrop ();
IMPORT int vxdbgBpMsgGet ();
IMPORT int vxdbgBpMsgPost ();
IMPORT int vxdbgBpMsgQCreate ();
IMPORT int vxdbgBpMsgQHdlrIsRunning ();
IMPORT int vxdbgClntRegister ();
IMPORT int vxdbgCont ();
IMPORT int vxdbgEnable ();
IMPORT int vxdbgHookAdd ();
IMPORT int vxdbgLockUnbreakable;
IMPORT int vxdbgMemAccess ();
IMPORT int vxdbgMemMove ();
IMPORT int vxdbgMemRead ();
IMPORT int vxdbgMemScan ();
IMPORT int vxdbgMemWrite ();
IMPORT int vxdbgSafeUnbreakable;
IMPORT int vxdbgStep ();
IMPORT int vxdbgStop ();
IMPORT int vxdbgTaskCont ();
IMPORT int vxdbgTaskLibInit ();
IMPORT int vxdbgTaskStep ();
IMPORT int vxdbgTaskStop ();
IMPORT int vxdbgUnbreakableOld;
IMPORT int vxfs_ramdisk_init_hook;
IMPORT int vxmux_calculate_transport_checksum ();
IMPORT int vxmux_mux_mblk_init ();
IMPORT int vxmux_null_buf_init ();
IMPORT int vxmux_null_pool;
IMPORT int w ();
IMPORT int watchdog_test ();
IMPORT int wcstombs ();
IMPORT int wctomb ();
IMPORT int wdCancel ();
IMPORT int wdClassId;
IMPORT int wdCreate ();
IMPORT int wdCreateLibInit ();
IMPORT int wdDelete ();
IMPORT int wdDestroy ();
IMPORT int wdInit ();
IMPORT int wdInitialize ();
IMPORT int wdLibInit ();
IMPORT int wdStart ();
IMPORT int wdTerminate ();
IMPORT int wdTick ();
IMPORT int wdbAvailModes;
IMPORT int wdbAvailOptions;
IMPORT int wdbBpAddHookAdd ();
IMPORT int wdbBpSyncLibInit ();
IMPORT int wdbBpSysEnterHook;
IMPORT int wdbBpSysExitHook;
IMPORT int wdbCksum ();
IMPORT int wdbCmdLoop ();
IMPORT int wdbCnctModePost ();
IMPORT int wdbCommDevInit ();
IMPORT int wdbCommMtu;
IMPORT int wdbCommMtuGet ();
IMPORT int wdbConfig ();
IMPORT int wdbConnectHookAdd ();
IMPORT int wdbConnectLibInit ();
IMPORT int wdbCtxCreateNotify ();
IMPORT int wdbCtxCs;
IMPORT int wdbCtxDeleteNotify ();
IMPORT int wdbCtxEvtLibInit ();
IMPORT int wdbCtxExitEventGet ();
IMPORT int wdbCtxExitLibInit ();
IMPORT int wdbCtxExitNotifyHook ();
IMPORT int wdbCtxLibInit ();
IMPORT int wdbCtxStartEventGet ();
IMPORT int wdbCtxStartLibInit ();
IMPORT int wdbDbgArchInit ();
IMPORT int wdbDbgBpStub ();
IMPORT int wdbDbgBreakpoint ();
IMPORT int wdbDbgCtxCs;
IMPORT int wdbDbgHwAddrCheck ();
IMPORT int wdbDbgHwBpFind ();
IMPORT int wdbDbgHwBpSet ();
IMPORT int wdbDbgPreBreakpoint ();
IMPORT int wdbDbgPreTrace ();
IMPORT int wdbDbgRegsClear ();
IMPORT int wdbDbgRegsSet ();
IMPORT int wdbDbgSysCallCheck ();
IMPORT int wdbDbgTrace ();
IMPORT int wdbDbgTraceModeClear ();
IMPORT int wdbDbgTraceModeSet ();
IMPORT int wdbDbgTraceStub ();
IMPORT int wdbDirectCallLibInit ();
IMPORT int wdbE ();
IMPORT int wdbEndDebug;
IMPORT int wdbEndDeviceAddress;
IMPORT int wdbEndPktDevInit ();
IMPORT int wdbEventDeq ();
IMPORT int wdbEventLibInit ();
IMPORT int wdbEventNodeInit ();
IMPORT int wdbEventPost ();
IMPORT int wdbEvtptClassConnect ();
IMPORT int wdbEvtptLibInit ();
IMPORT int wdbExcLibInit ();
IMPORT int wdbExternEnterHookAdd ();
IMPORT int wdbExternExitHookAdd ();
IMPORT int wdbExternInit ();
IMPORT int wdbExternLibInit ();
IMPORT int wdbExternRegLibInit ();
IMPORT int wdbFuncCallLibInit ();
IMPORT int wdbGopherLibInit ();
IMPORT int wdbInfoGet ();
IMPORT int wdbInstallCommIf ();
IMPORT int wdbInstallRtIf ();
IMPORT int wdbIsInitialized;
IMPORT int wdbIsNowExternal ();
IMPORT int wdbIsReady;
IMPORT int wdbMbufAlloc ();
IMPORT int wdbMbufFree ();
IMPORT int wdbMbufInit ();
IMPORT int wdbMdlSymSyncLibInit ();
IMPORT int wdbMemCoreLibInit ();
IMPORT int wdbMemLibInit ();
IMPORT int wdbMode;
IMPORT int wdbModeSet ();
IMPORT int wdbModeSetHookAdd ();
IMPORT int wdbNotifyHost ();
IMPORT int wdbNumMemRegions;
IMPORT int wdbOneShot;
IMPORT int wdbPort;
IMPORT int wdbRegsBuffer;
IMPORT int wdbRegsBufferSize;
IMPORT int wdbRegsLibInit ();
IMPORT int wdbRpcGetArgs ();
IMPORT int wdbRpcNotifyConnect ();
IMPORT int wdbRpcNotifyHost ();
IMPORT int wdbRpcRcv ();
IMPORT int wdbRpcReply ();
IMPORT int wdbRpcReplyErr ();
IMPORT int wdbRpcResendReply ();
IMPORT int wdbRpcXportInit ();
IMPORT int wdbRtIf;
IMPORT int wdbRtLibInit ();
IMPORT int wdbRunsExternal ();
IMPORT int wdbRunsTasking ();
IMPORT int wdbSp ();
IMPORT int wdbSvcAdd ();
IMPORT int wdbSvcDispatch ();
IMPORT int wdbSvcHookAdd ();
IMPORT int wdbSvcLibInit ();
IMPORT int wdbSysBpDisableAll ();
IMPORT int wdbSysBpEnableAll ();
IMPORT int wdbSysBpLibInit ();
IMPORT int wdbSysModeInit ();
IMPORT int wdbSystemSuspend ();
IMPORT int wdbTargetIsConnected ();
IMPORT int wdbTask ();
IMPORT int wdbTaskBpAdd ();
IMPORT int wdbTaskBpLibInit ();
IMPORT int wdbTaskCont ();
IMPORT int wdbTaskCreateHookAdd ();
IMPORT int wdbTaskDeleteHookAdd ();
IMPORT int wdbTaskExtraModules;
IMPORT int wdbTaskHookInit ();
IMPORT int wdbTaskModeInit ();
IMPORT int wdbTaskRegLibInit ();
IMPORT int wdbTaskRestartHook;
IMPORT int wdbTaskStep ();
IMPORT int wdbTaskStop ();
IMPORT int wdbTgtInfoLibInit ();
IMPORT int wdbToolName;
IMPORT int wdbUserEvtLibInit ();
IMPORT int wdbUserEvtPost ();
IMPORT int wdbVioChannelRegister ();
IMPORT int wdbVioChannelUnregister ();
IMPORT int wdbVioDrv ();
IMPORT int wdbVioLibInit ();
IMPORT int wdbXdrCreate ();
IMPORT int wdbXdrGetVal ();
IMPORT int wdbXdrGetpos ();
IMPORT int wdbXdrInline ();
IMPORT int wdbXdrPutVal ();
IMPORT int wdbXdrPutbytes ();
IMPORT int wdbXdrSetpos ();
IMPORT int whoami ();
IMPORT int windCont ();
IMPORT int windDelay ();
IMPORT int windDelete ();
IMPORT int windExit ();
IMPORT int windIntStackSet ();
IMPORT int windLoadContext ();
IMPORT int windNullReturn ();
IMPORT int windPendQFlush ();
IMPORT int windPendQGet ();
IMPORT int windPendQPut ();
IMPORT int windPendQRemove ();
IMPORT int windPendQTerminate ();
IMPORT int windPriNormalSet ();
IMPORT int windPrioritySet ();
IMPORT int windReadyQPut ();
IMPORT int windReadyQRemove ();
IMPORT int windResume ();
IMPORT int windSemDelete ();
IMPORT int windSemRWDelete ();
IMPORT int windStop ();
IMPORT int windSuspend ();
IMPORT int windTickAnnounce ();
IMPORT int windTickAnnounceN ();
IMPORT int windTickWaitGet ();
IMPORT int windUndelay ();
IMPORT int windWdCancel ();
IMPORT int windWdStart ();
IMPORT int workQAdd0 ();
IMPORT int workQAdd1 ();
IMPORT int workQAdd2 ();
IMPORT int workQDoWork ();
IMPORT int workQInit ();
IMPORT int workQIsEmpty;
IMPORT int workQIx;
IMPORT int workQPanic ();
IMPORT int workQPanicHook;
IMPORT int workQWorkInProgress;
IMPORT int write ();
IMPORT int writev ();
IMPORT int xattrib ();
IMPORT int xbdAttach ();
IMPORT int xbdAttachExt ();
IMPORT int xbdBlkDevCreate ();
IMPORT int xbdBlkDevCreateSync ();
IMPORT int xbdBlkDevDelete ();
IMPORT int xbdBlkDevLibInit ();
IMPORT int xbdBlkDevServTskPri;
IMPORT int xbdBlockSize ();
IMPORT int xbdCreatePartition ();
IMPORT int xbdCreatePartitionSz ();
IMPORT int xbdDetach ();
IMPORT int xbdDump ();
IMPORT int xbdEventCategory;
IMPORT int xbdEventInstantiated;
IMPORT int xbdEventMediaChanged;
IMPORT int xbdEventPrimaryInsert;
IMPORT int xbdEventRemove;
IMPORT int xbdEventSecondaryInsert;
IMPORT int xbdEventSoftInsert;
IMPORT int xbdGetBioSched ();
IMPORT int xbdGetNextBioGeneric ();
IMPORT int xbdInit ();
IMPORT int xbdIoctl ();
IMPORT int xbdNBlocks ();
IMPORT int xbdPartitionDevCreate ();
IMPORT int xbdSetBioSched ();
IMPORT int xbdSize ();
IMPORT int xbdSrvTaskGeneric ();
IMPORT int xbdStrategy ();
IMPORT int xbdStrategyGeneric ();
IMPORT int xcopy ();
IMPORT int xdelete ();
IMPORT int xdrCksum ();
IMPORT int xdr_ARRAY ();
IMPORT int xdr_BOOL ();
IMPORT int xdr_CHECKSUM ();
IMPORT int xdr_ENUM ();
IMPORT int xdr_REFERENCE ();
IMPORT int xdr_TGT_ADDR_T ();
IMPORT int xdr_TGT_LONG_T ();
IMPORT int xdr_UINT32 ();
IMPORT int xdr_VOID ();
IMPORT int xdr_WDB_AGENT_INFO ();
IMPORT int xdr_WDB_CALL_RETURN_INFO ();
IMPORT int xdr_WDB_CONNECT_INFO ();
IMPORT int xdr_WDB_CONNECT_PARAMS ();
IMPORT int xdr_WDB_CORE ();
IMPORT int xdr_WDB_CTX ();
IMPORT int xdr_WDB_CTX_CREATE_DESC ();
IMPORT int xdr_WDB_CTX_KILL_DESC ();
IMPORT int xdr_WDB_CTX_STEP_DESC ();
IMPORT int xdr_WDB_DIRECT_CALL_RET ();
IMPORT int xdr_WDB_EVTPT_ADD_DESC ();
IMPORT int xdr_WDB_EVTPT_DEL_DESC ();
IMPORT int xdr_WDB_EVT_DATA ();
IMPORT int xdr_WDB_EVT_INFO ();
IMPORT int xdr_WDB_MEM_REGION ();
IMPORT int xdr_WDB_MEM_SCAN_DESC ();
IMPORT int xdr_WDB_MEM_XFER ();
IMPORT int xdr_WDB_MOD_INFO ();
IMPORT int xdr_WDB_OPQ_DATA_T ();
IMPORT int xdr_WDB_PARAM_WRAPPER ();
IMPORT int xdr_WDB_REG_READ_DESC ();
IMPORT int xdr_WDB_REG_WRITE_DESC ();
IMPORT int xdr_WDB_REPLY_WRAPPER ();
IMPORT int xdr_WDB_RT_INFO ();
IMPORT int xdr_WDB_SECT_INFO ();
IMPORT int xdr_WDB_SEG_INFO ();
IMPORT int xdr_WDB_STRING_ARRAY ();
IMPORT int xdr_WDB_STRING_T ();
IMPORT int xdr_WDB_SYM_ID ();
IMPORT int xdr_WDB_SYM_ID_LIST ();
IMPORT int xdr_WDB_SYM_INFO ();
IMPORT int xdr_WDB_SYM_LIST ();
IMPORT int xdr_WDB_SYM_MOD_DESC ();
IMPORT int xdr_WDB_TGT_INFO ();
IMPORT int xdr_WDB_TGT_INFO_2 ();
IMPORT int xpFuncs;
IMPORT int zbufCreate ();
IMPORT int zbufCut ();
IMPORT int zbufDelete ();
IMPORT int zbufDup ();
IMPORT int zbufExtractCopy ();
IMPORT int zbufInsert ();
IMPORT int zbufInsertBuf ();
IMPORT int zbufInsertCopy ();
IMPORT int zbufLength ();
IMPORT int zbufLibInit ();
IMPORT int zbufSegData ();
IMPORT int zbufSegFind ();
IMPORT int zbufSegLength ();
IMPORT int zbufSegNext ();
IMPORT int zbufSegPrev ();
IMPORT int zbufSockBufSend ();
IMPORT int zbufSockBufSendto ();
IMPORT int zbufSockLibInit ();
IMPORT int zbufSockRecv ();
IMPORT int zbufSockRecvfrom ();
IMPORT int zbufSockSend ();
IMPORT int zbufSockSendto ();
IMPORT int zbufSplit ();
IMPORT int zbuf_free ();

SYMBOL standTbl [6076] =
    {
        {{NULL}, "AppDelete", (char*) AppDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AppEntry", (char*) AppEntry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BufferPageCross", (char*) BufferPageCross, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CheckComSum", (char*) CheckComSum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClearPciCnt", (char*) ClearPciCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClosePciCan", (char*) ClosePciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClosePciIoCnt", (char*) ClosePciIoCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatCanModule", (char*) CreatCanModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatComModule", (char*) CreatComModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatIoCntModule", (char*) CreatIoCntModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatLogFile", (char*) CreatLogFile, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatMangeFileModule", (char*) CreatMangeFileModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatMangeUsbModule", (char*) CreatMangeUsbModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatRollTimeFile", (char*) CreatRollTimeFile, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatUsbPath", (char*) CreatUsbPath, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatePciCan", (char*) CreatePciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatePciCan2", (char*) CreatePciCan2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreatePciIoCnt", (char*) CreatePciIoCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DecToBin", (char*) DecToBin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DrainFifo", (char*) DrainFifo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_DecodeBlock", (char*) EVP_DecodeBlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_DecodeFinal", (char*) EVP_DecodeFinal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_DecodeInit", (char*) EVP_DecodeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_DecodeUpdate", (char*) EVP_DecodeUpdate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_EncodeBlock", (char*) EVP_EncodeBlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_EncodeFinal", (char*) EVP_EncodeFinal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_EncodeInit", (char*) EVP_EncodeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EVP_EncodeUpdate", (char*) EVP_EncodeUpdate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FileSize", (char*) FileSize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlushPciCan", (char*) FlushPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBiosTime", (char*) GetBiosTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPciCan", (char*) GetPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTime", (char*) GetTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitPciCan", (char*) InitPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitSja", (char*) InitSja, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitSystemTime", (char*) InitSystemTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IoctlPciCan", (char*) IoctlPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MD5_Final", (char*) MD5_Final, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MD5_Init", (char*) MD5_Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MD5_Transform", (char*) MD5_Transform, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MD5_Update", (char*) MD5_Update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MD5_version", (char*) &MD5_version, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "OpenPciCan", (char*) OpenPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OpenPciIoCnt", (char*) OpenPciIoCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PrintTime", (char*) PrintTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadComEx", (char*) ReadComEx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadPciCan", (char*) ReadPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadPciCnt", (char*) ReadPciCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadPciIo", (char*) ReadPciIo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RecvCom", (char*) RecvCom, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveCanModule", (char*) RemoveCanModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveComModule", (char*) RemoveComModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveIoCntModule", (char*) RemoveIoCntModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveMangeFileModule", (char*) RemoveMangeFileModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveMangeUsbModule", (char*) RemoveMangeUsbModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemovePciCan", (char*) RemovePciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemovePciCan2", (char*) RemovePciCan2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemovePciIoCnt", (char*) RemovePciIoCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA224", (char*) SHA224, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA224_Final", (char*) SHA224_Final, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA224_Init", (char*) SHA224_Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA224_Update", (char*) SHA224_Update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA256", (char*) SHA256, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA256_Final", (char*) SHA256_Final, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA256_Init", (char*) SHA256_Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA256_Transform", (char*) SHA256_Transform, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA256_Update", (char*) SHA256_Update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SHA256_version", (char*) &SHA256_version, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ShowPciCan", (char*) ShowPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ShowTime", (char*) ShowTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "StartPciCnt", (char*) StartPciCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "StopPciCnt", (char*) StopPciCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestPciCan", (char*) TestPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestPciIoCnt", (char*) TestPciIoCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WaitPciIo", (char*) WaitPciIo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WritePciCan", (char*) WritePciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WritePciIo", (char*) WritePciIo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL__D_0___gthread_once", (char*) _GLOBAL__D_0___gthread_once, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Randseed", (char*) &_Randseed, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_Unwind_Backtrace", (char*) _Unwind_Backtrace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_DeleteException", (char*) _Unwind_DeleteException, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_FindEnclosingFunction", (char*) _Unwind_FindEnclosingFunction, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_Find_FDE", (char*) _Unwind_Find_FDE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_ForcedUnwind", (char*) _Unwind_ForcedUnwind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetCFA", (char*) _Unwind_GetCFA, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetDataRelBase", (char*) _Unwind_GetDataRelBase, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetGR", (char*) _Unwind_GetGR, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetIP", (char*) _Unwind_GetIP, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetIPInfo", (char*) _Unwind_GetIPInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetLanguageSpecificData", (char*) _Unwind_GetLanguageSpecificData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetRegionStart", (char*) _Unwind_GetRegionStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_GetTextRelBase", (char*) _Unwind_GetTextRelBase, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_RaiseException", (char*) _Unwind_RaiseException, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_Resume", (char*) _Unwind_Resume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_Resume_or_Rethrow", (char*) _Unwind_Resume_or_Rethrow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_SetGR", (char*) _Unwind_SetGR, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Unwind_SetIP", (char*) _Unwind_SetIP, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "___x_gnu___gcc_bcmp_o", (char*) &___x_gnu___gcc_bcmp_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__absvdi2_o", (char*) &___x_gnu__absvdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__absvsi2_o", (char*) &___x_gnu__absvsi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__addvdi3_o", (char*) &___x_gnu__addvdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__addvsi3_o", (char*) &___x_gnu__addvsi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ashldi3_o", (char*) &___x_gnu__ashldi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ashrdi3_o", (char*) &___x_gnu__ashrdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__clear_cache_o", (char*) &___x_gnu__clear_cache_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__clz_o", (char*) &___x_gnu__clz_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__clzdi2_o", (char*) &___x_gnu__clzdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__clzsi2_o", (char*) &___x_gnu__clzsi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__cmpdi2_o", (char*) &___x_gnu__cmpdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ctzdi2_o", (char*) &___x_gnu__ctzdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ctzsi2_o", (char*) &___x_gnu__ctzsi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divdc3_o", (char*) &___x_gnu__divdc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divdi3_o", (char*) &___x_gnu__divdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divsc3_o", (char*) &___x_gnu__divsc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divtc3_o", (char*) &___x_gnu__divtc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divxc3_o", (char*) &___x_gnu__divxc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__enable_execute_stack_o", (char*) &___x_gnu__enable_execute_stack_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__eprintf_o", (char*) &___x_gnu__eprintf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ffsdi2_o", (char*) &___x_gnu__ffsdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ffssi2_o", (char*) &___x_gnu__ffssi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixdfdi_o", (char*) &___x_gnu__fixdfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixsfdi_o", (char*) &___x_gnu__fixsfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixtfdi_o", (char*) &___x_gnu__fixtfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunsdfdi_o", (char*) &___x_gnu__fixunsdfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunsdfsi_o", (char*) &___x_gnu__fixunsdfsi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunssfdi_o", (char*) &___x_gnu__fixunssfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunssfsi_o", (char*) &___x_gnu__fixunssfsi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunstfdi_o", (char*) &___x_gnu__fixunstfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunsxfdi_o", (char*) &___x_gnu__fixunsxfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunsxfsi_o", (char*) &___x_gnu__fixunsxfsi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixxfdi_o", (char*) &___x_gnu__fixxfdi_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatdidf_o", (char*) &___x_gnu__floatdidf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatdisf_o", (char*) &___x_gnu__floatdisf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatditf_o", (char*) &___x_gnu__floatditf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatdixf_o", (char*) &___x_gnu__floatdixf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatundidf_o", (char*) &___x_gnu__floatundidf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatundisf_o", (char*) &___x_gnu__floatundisf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatunditf_o", (char*) &___x_gnu__floatunditf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatundixf_o", (char*) &___x_gnu__floatundixf_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__lshrdi3_o", (char*) &___x_gnu__lshrdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__moddi3_o", (char*) &___x_gnu__moddi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__muldc3_o", (char*) &___x_gnu__muldc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__muldi3_o", (char*) &___x_gnu__muldi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__mulsc3_o", (char*) &___x_gnu__mulsc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__multc3_o", (char*) &___x_gnu__multc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__mulvdi3_o", (char*) &___x_gnu__mulvdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__mulvsi3_o", (char*) &___x_gnu__mulvsi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__mulxc3_o", (char*) &___x_gnu__mulxc3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__negdi2_o", (char*) &___x_gnu__negdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__negvdi2_o", (char*) &___x_gnu__negvdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__negvsi2_o", (char*) &___x_gnu__negvsi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__paritydi2_o", (char*) &___x_gnu__paritydi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__paritysi2_o", (char*) &___x_gnu__paritysi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__popcount_tab_o", (char*) &___x_gnu__popcount_tab_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__popcountdi2_o", (char*) &___x_gnu__popcountdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__popcountsi2_o", (char*) &___x_gnu__popcountsi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__powidf2_o", (char*) &___x_gnu__powidf2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__powisf2_o", (char*) &___x_gnu__powisf2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__powitf2_o", (char*) &___x_gnu__powitf2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__powixf2_o", (char*) &___x_gnu__powixf2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__subvdi3_o", (char*) &___x_gnu__subvdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__subvsi3_o", (char*) &___x_gnu__subvsi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__trampoline_o", (char*) &___x_gnu__trampoline_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ucmpdi2_o", (char*) &___x_gnu__ucmpdi2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udiv_w_sdiv_o", (char*) &___x_gnu__udiv_w_sdiv_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udivdi3_o", (char*) &___x_gnu__udivdi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udivmoddi4_o", (char*) &___x_gnu__udivmoddi4_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__umoddi3_o", (char*) &___x_gnu__umoddi3_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_emutls_o", (char*) &___x_gnu_emutls_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_gthr_gnat_o", (char*) &___x_gnu_gthr_gnat_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_unwind_c_o", (char*) &___x_gnu_unwind_c_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_unwind_dw2_fde_o", (char*) &___x_gnu_unwind_dw2_fde_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_unwind_dw2_o", (char*) &___x_gnu_unwind_dw2_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_unwind_sjlj_o", (char*) &___x_gnu_unwind_sjlj_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_vxlib_o", (char*) &___x_gnu_vxlib_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__absvdi2", (char*) __absvdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__absvsi2", (char*) __absvsi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__addvdi3", (char*) __addvdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__addvsi3", (char*) __addvsi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ashldi3", (char*) __ashldi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ashrdi3", (char*) __ashrdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__assert", (char*) __assert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__clear_cache", (char*) __clear_cache, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__clocale", (char*) &__clocale, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__clz_tab", (char*) &__clz_tab, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__clzdi2", (char*) __clzdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__clzsi2", (char*) __clzsi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cmpdi2", (char*) __cmpdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__common_intrinsicsInit", (char*) __common_intrinsicsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__costate", (char*) &__costate, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusLoadObjFiles", (char*) &__cplusLoadObjFiles, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusLoad_o", (char*) &__cplusLoad_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusUsr_o", (char*) &__cplusUsr_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusXtors_o", (char*) &__cplusXtors_o, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__ctype", (char*) &__ctype, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__ctype_tolower", (char*) &__ctype_tolower, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__ctype_toupper", (char*) &__ctype_toupper, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__ctzdi2", (char*) __ctzdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ctzsi2", (char*) __ctzsi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__daysSinceEpoch", (char*) __daysSinceEpoch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__deregister_frame", (char*) __deregister_frame, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__deregister_frame_info", (char*) __deregister_frame_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__deregister_frame_info_bases", (char*) __deregister_frame_info_bases, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divdc3", (char*) __divdc3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divdi3", (char*) __divdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divsc3", (char*) __divsc3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divxc3", (char*) __divxc3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__emutls_get_address", (char*) __emutls_get_address, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__emutls_register_common", (char*) __emutls_register_common, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__enable_execute_stack", (char*) __enable_execute_stack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__errno", (char*) __errno, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ffsdi2", (char*) __ffsdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ffssi2", (char*) __ffssi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixdfdi", (char*) __fixdfdi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixsfdi", (char*) __fixsfdi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunsdfdi", (char*) __fixunsdfdi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunsdfsi", (char*) __fixunsdfsi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunssfdi", (char*) __fixunssfdi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunssfsi", (char*) __fixunssfsi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunsxfdi", (char*) __fixunsxfdi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunsxfsi", (char*) __fixunsxfsi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixxfdi", (char*) __fixxfdi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatdidf", (char*) __floatdidf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatdisf", (char*) __floatdisf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatdixf", (char*) __floatdixf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatundidf", (char*) __floatundidf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatundisf", (char*) __floatundisf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatundixf", (char*) __floatundixf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__frame_state_for", (char*) __frame_state_for, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gcc_bcmp", (char*) __gcc_bcmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gcc_intrinsicsInit", (char*) __gcc_intrinsicsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gcc_personality_v0", (char*) __gcc_personality_v0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getDstInfo", (char*) __getDstInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getDstInfoSub", (char*) __getDstInfoSub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getTime", (char*) __getTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getZoneInfo", (char*) __getZoneInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gnat_default_lock", (char*) __gnat_default_lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gnat_default_unlock", (char*) __gnat_default_unlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gnat_install_locks", (char*) __gnat_install_locks, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthr_supp_vxw_5x_o", (char*) &__gthr_supp_vxw_5x_o, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__gthread_active_p", (char*) __gthread_active_p, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_enter_tls_dtor_context", (char*) __gthread_enter_tls_dtor_context, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_enter_tsd_dtor_context", (char*) __gthread_enter_tsd_dtor_context, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_get_tls_data", (char*) __gthread_get_tls_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_get_tsd_data", (char*) __gthread_get_tsd_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_getspecific", (char*) __gthread_getspecific, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_key_create", (char*) __gthread_key_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_key_delete", (char*) __gthread_key_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_leave_tls_dtor_context", (char*) __gthread_leave_tls_dtor_context, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_leave_tsd_dtor_context", (char*) __gthread_leave_tsd_dtor_context, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_mutex_lock", (char*) __gthread_mutex_lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_mutex_unlock", (char*) __gthread_mutex_unlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_once", (char*) __gthread_once, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_set_tls_data", (char*) __gthread_set_tls_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_set_tsd_data", (char*) __gthread_set_tsd_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gthread_setspecific", (char*) __gthread_setspecific, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__includeGnuIntrinsics", (char*) &__includeGnuIntrinsics, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__julday", (char*) __julday, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__locale", (char*) &__locale, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__loctime", (char*) &__loctime, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__lshrdi3", (char*) __lshrdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__moddi3", (char*) __moddi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__muldc3", (char*) __muldc3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__muldi3", (char*) __muldi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mulsc3", (char*) __mulsc3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mulvdi3", (char*) __mulvdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mulvsi3", (char*) __mulvsi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mulxc3", (char*) __mulxc3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negdi2", (char*) __negdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negvdi2", (char*) __negvdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negvsi2", (char*) __negvsi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__paritydi2", (char*) __paritydi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__paritysi2", (char*) __paritysi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__popcount_tab", (char*) &__popcount_tab, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__popcountdi2", (char*) __popcountdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__popcountsi2", (char*) __popcountsi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__powidf2", (char*) __powidf2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__powisf2", (char*) __powisf2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__powixf2", (char*) __powixf2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__register_frame", (char*) __register_frame, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__register_frame_info", (char*) __register_frame_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__register_frame_info_bases", (char*) __register_frame_info_bases, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__register_frame_info_table", (char*) __register_frame_info_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__register_frame_info_table_bases", (char*) __register_frame_info_table_bases, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__register_frame_table", (char*) __register_frame_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rta_longjmp", (char*) &__rta_longjmp, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__sclose", (char*) __sclose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sflags", (char*) __sflags, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sflush", (char*) __sflush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sfvwrite", (char*) __sfvwrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__smakebuf", (char*) __smakebuf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sread", (char*) __sread, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__srefill", (char*) __srefill, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__srget", (char*) __srget, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sseek", (char*) __sseek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stderr", (char*) __stderr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stdin", (char*) __stdin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stdout", (char*) __stdout, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__strxfrm", (char*) __strxfrm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__subvdi3", (char*) __subvdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__subvsi3", (char*) __subvsi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__swbuf", (char*) __swbuf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__swrite", (char*) __swrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__swsetup", (char*) __swsetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ucmpdi2", (char*) __ucmpdi2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udiv_w_sdiv", (char*) __udiv_w_sdiv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udivdi3", (char*) __udivdi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udivmoddi4", (char*) __udivmoddi4, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__umoddi3", (char*) __umoddi3, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vxmux_assert", (char*) __vxmux_assert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__wdbEventListIsEmpty", (char*) &__wdbEventListIsEmpty, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_api_nbio", (char*) &_api_nbio, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_applLog", (char*) _applLog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_archHelp_msg", (char*) &_archHelp_msg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_archIORead16", (char*) _archIORead16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_archIORead32", (char*) _archIORead32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_archIORead8", (char*) _archIORead8, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_archIOWrite16", (char*) _archIOWrite16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_archIOWrite32", (char*) _archIOWrite32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_archIOWrite8", (char*) _archIOWrite8, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_clockRealtime", (char*) &_clockRealtime, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_dbgArchInit", (char*) _dbgArchInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgBrkDisplayHard", (char*) _dbgBrkDisplayHard, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgDsmInstRtn", (char*) &_dbgDsmInstRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_dbgFuncCallCheck", (char*) _dbgFuncCallCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgInstSizeGet", (char*) _dbgInstSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgRetAdrsGet", (char*) _dbgRetAdrsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgTaskPCGet", (char*) _dbgTaskPCGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgTaskPCSet", (char*) _dbgTaskPCSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_endM2Packet_1213", (char*) _endM2Packet_1213, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_endM2Packet_2233", (char*) _endM2Packet_2233, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_func_CPToUtf16", (char*) &_func_CPToUtf16, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_CPToUtf8", (char*) &_func_CPToUtf8, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_PCIeRootForeach", (char*) &_func_PCIeRootForeach, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_SysBootParamsGet", (char*) &_func_SysBootParamsGet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_aimMmuLockRegionsImport", (char*) &_func_aimMmuLockRegionsImport, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_cacheFuncsSet", (char*) &_func_cacheFuncsSet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_classListAdd", (char*) &_func_classListAdd, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_classListInit", (char*) &_func_classListInit, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_classListLock", (char*) &_func_classListLock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_classListRemove", (char*) &_func_classListRemove, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_classListTblInit", (char*) &_func_classListTblInit, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_classListUnlock", (char*) &_func_classListUnlock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_consoleOut", (char*) &_func_consoleOut, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_coprocShow", (char*) &_func_coprocShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_coprocTaskRegsShow", (char*) &_func_coprocTaskRegsShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_cpuIndexGet", (char*) &_func_cpuIndexGet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_cpuPwrIdleEnter", (char*) &_func_cpuPwrIdleEnter, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_cpuPwrIntEnterHook", (char*) &_func_cpuPwrIntEnterHook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_cpuPwrIntExitHook", (char*) &_func_cpuPwrIntExitHook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_dosChkStatPrint", (char*) &_func_dosChkStatPrint, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_dosDirOldShow", (char*) &_func_dosDirOldShow, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_dosFsFatShow", (char*) &_func_dosFsFatShow, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_dosVDirShow", (char*) &_func_dosVDirShow, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_edrEvt", (char*) &_func_edrEvt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_end2VxBusConnect", (char*) &_func_end2VxBusConnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_end8023AddressForm", (char*) &_func_end8023AddressForm, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_endEtherAddressForm", (char*) &_func_endEtherAddressForm, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_endEtherPacketAddrGet", (char*) &_func_endEtherPacketAddrGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_endEtherPacketDataGet", (char*) &_func_endEtherPacketDataGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_envGet", (char*) &_func_envGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_eventReceive", (char*) &_func_eventReceive, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_eventRsrcSend", (char*) &_func_eventRsrcSend, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_eventSend", (char*) &_func_eventSend, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_eventStart", (char*) &_func_eventStart, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_eventTerminate", (char*) &_func_eventTerminate, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogCpc", (char*) &_func_evtLogCpc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogPayload", (char*) &_func_evtLogPayload, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogPayloadString", (char*) &_func_evtLogPayloadString, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogReserveTaskName", (char*) &_func_evtLogReserveTaskName, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogSyscall", (char*) &_func_evtLogSyscall, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excBaseHook", (char*) &_func_excBaseHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excInfoShow", (char*) &_func_excInfoShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excIntHook", (char*) &_func_excIntHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excJobAdd", (char*) &_func_excJobAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excPanicHook", (char*) &_func_excPanicHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_exit", (char*) &_func_exit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fastUdpErrorNotify", (char*) &_func_fastUdpErrorNotify, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fastUdpInput", (char*) &_func_fastUdpInput, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fastUdpPortTest", (char*) &_func_fastUdpPortTest, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fclose", (char*) &_func_fclose, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fcntl_dup", (char*) &_func_fcntl_dup, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_fileDoesNotExist", (char*) &_func_fileDoesNotExist, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_fioFltFormatRtn", (char*) &_func_fioFltFormatRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fioFltScanRtn", (char*) &_func_fioFltScanRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fppRestoreRtn", (char*) &_func_fppRestoreRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_fppSaveRtn", (char*) &_func_fppSaveRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_ftpLs", (char*) &_func_ftpLs, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ftpTransientFatal", (char*) &_func_ftpTransientFatal, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_ftruncMmanHook", (char*) &_func_ftruncMmanHook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_handleAlloc", (char*) &_func_handleAlloc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_handleFreeAll", (char*) &_func_handleFreeAll, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ioGlobalStdGet", (char*) &_func_ioGlobalStdGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ioPxCreateOrOpen", (char*) &_func_ioPxCreateOrOpen, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_ioTaskStdSet", (char*) &_func_ioTaskStdSet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_iosPathFdEntryIoctl", (char*) &_func_iosPathFdEntryIoctl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_iosPosixFdEntryIoctl", (char*) &_func_iosPosixFdEntryIoctl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_iosRtpIoTableSizeGet", (char*) &_func_iosRtpIoTableSizeGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_iosRtpIoTableSizeSet", (char*) &_func_iosRtpIoTableSizeSet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_isrConnect", (char*) &_func_isrConnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_isrCreate", (char*) &_func_isrCreate, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_isrDelete", (char*) &_func_isrDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_isrDisconnect", (char*) &_func_isrDisconnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_isrDispatcher", (char*) &_func_isrDispatcher, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_isrInfo", (char*) &_func_isrInfo, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_jobAdd", (char*) &_func_jobAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_jobExcAdd", (char*) &_func_jobExcAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_jobTaskWorkAdd", (char*) &_func_jobTaskWorkAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_kernelModuleListIdGet", (char*) &_func_kernelModuleListIdGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_kernelRoundRobinHook", (char*) &_func_kernelRoundRobinHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_lf_advlock", (char*) &_func_lf_advlock, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_loadRtpDeltaBaseAddrApply", (char*) &_func_loadRtpDeltaBaseAddrApply, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_loadRtpSymsPolicyOverride", (char*) &_func_loadRtpSymsPolicyOverride, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_logMsg", (char*) &_func_logMsg, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_m2PollStatsIfPoll", (char*) &_func_m2PollStatsIfPoll, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_memPartRealloc", (char*) &_func_memPartRealloc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_memPartReallocInternal", (char*) &_func_memPartReallocInternal, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_memalign", (char*) &_func_memalign, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_mmuCacheFlushLoadAdrsGet", (char*) &_func_mmuCacheFlushLoadAdrsGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_mmuCurrentGet", (char*) &_func_mmuCurrentGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_moduleIdFigure", (char*) &_func_moduleIdFigure, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_moduleSegInfoGet", (char*) &_func_moduleSegInfoGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netAttrDeReg", (char*) &_func_netAttrDeReg, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netAttrReg", (char*) &_func_netAttrReg, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netChDirByName", (char*) &_func_netChDirByName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_netDaemonIxToQId", (char*) &_func_netDaemonIxToQId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netDaemonQIdToIx", (char*) &_func_netDaemonQIdToIx, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netLsByName", (char*) &_func_netLsByName, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netPoolShow", (char*) &_func_netPoolShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objCoreRelease", (char*) &_func_objCoreRelease, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objHandleToObjId", (char*) &_func_objHandleToObjId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objNameVerifiedSet", (char*) &_func_objNameVerifiedSet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objOwnerListAdd", (char*) &_func_objOwnerListAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objOwnerListRemove", (char*) &_func_objOwnerListRemove, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objOwnerReclaim", (char*) &_func_objOwnerReclaim, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objOwnerSetBaseInternal", (char*) &_func_objOwnerSetBaseInternal, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objOwnerSetInternal", (char*) &_func_objOwnerSetInternal, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_objRtpObjEachHook", (char*) &_func_objRtpObjEachHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ownerListLock", (char*) &_func_ownerListLock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ownerListUnlock", (char*) &_func_ownerListUnlock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pciAutoCfgCtl", (char*) &_func_pciAutoCfgCtl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pgMgrPageAlloc", (char*) &_func_pgMgrPageAlloc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pgMgrPageFree", (char*) &_func_pgMgrPageFree, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pgMgrPageMap", (char*) &_func_pgMgrPageMap, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_printErr", (char*) &_func_printErr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_printExcPrintHook", (char*) &_func_printExcPrintHook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_proofUtf8String", (char*) &_func_proofUtf8String, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pthread_testandset_canceltype", (char*) &_func_pthread_testandset_canceltype, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pxCpuTimerCancel", (char*) &_func_pxCpuTimerCancel, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pxCpuTimerCreate", (char*) &_func_pxCpuTimerCreate, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pxCpuTimerDelete", (char*) &_func_pxCpuTimerDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pxCpuTimerStart", (char*) &_func_pxCpuTimerStart, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pxSSThreadIntHook", (char*) &_func_pxSSThreadIntHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pxSSThreadStateInit", (char*) &_func_pxSSThreadStateInit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_qPriBMapNativeResort", (char*) &_func_qPriBMapNativeResort, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_regsShow", (char*) &_func_regsShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_remCurIdGet", (char*) &_func_remCurIdGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_remCurIdSet", (char*) &_func_remCurIdSet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpDelete", (char*) &_func_rtpDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpDeleteHookAdd", (char*) &_func_rtpDeleteHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpDeleteHookDelete", (char*) &_func_rtpDeleteHookDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpExtraCmdGet", (char*) &_func_rtpExtraCmdGet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_rtpHandleIdGet", (char*) &_func_rtpHandleIdGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpIdVerify", (char*) &_func_rtpIdVerify, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpInitCompleteHookAdd", (char*) &_func_rtpInitCompleteHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpInitCompleteHookDelete", (char*) &_func_rtpInitCompleteHookDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpPause", (char*) &_func_rtpPause, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpPostCreateHookAdd", (char*) &_func_rtpPostCreateHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpPostCreateHookDelete", (char*) &_func_rtpPostCreateHookDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpPreCreateHookAdd", (char*) &_func_rtpPreCreateHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpPreCreateHookDelete", (char*) &_func_rtpPreCreateHookDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpShlSymbolsRegister", (char*) &_func_rtpShlSymbolsRegister, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpShlSymbolsUnregister", (char*) &_func_rtpShlSymbolsUnregister, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpShow", (char*) &_func_rtpShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigExcKill", (char*) &_func_rtpSigExcKill, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigPendDestroy", (char*) &_func_rtpSigPendDestroy, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigPendInit", (char*) &_func_rtpSigPendInit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigPendKill", (char*) &_func_rtpSigPendKill, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigaction", (char*) &_func_rtpSigaction, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigpending", (char*) &_func_rtpSigpending, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigprocmask", (char*) &_func_rtpSigprocmask, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigqueue", (char*) &_func_rtpSigqueue, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigsuspend", (char*) &_func_rtpSigsuspend, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSigtimedwait", (char*) &_func_rtpSigtimedwait, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSpawn", (char*) &_func_rtpSpawn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpSymTblIdGet", (char*) &_func_rtpSymTblIdGet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_rtpTaskKill", (char*) &_func_rtpTaskKill, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpTaskSigBlock", (char*) &_func_rtpTaskSigBlock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpTaskSigCheck", (char*) &_func_rtpTaskSigCheck, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpTaskSigPendKill", (char*) &_func_rtpTaskSigPendKill, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpTaskSigqueue", (char*) &_func_rtpTaskSigqueue, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_rtpVarAdd", (char*) &_func_rtpVarAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_scMemValidate", (char*) &_func_scMemValidate, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sdUnmapAll", (char*) &_func_sdUnmapAll, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selPtyAdd", (char*) &_func_selPtyAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selPtyDelete", (char*) &_func_selPtyDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selPtySlaveAdd", (char*) &_func_selPtySlaveAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selPtySlaveDelete", (char*) &_func_selPtySlaveDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selTyAdd", (char*) &_func_selTyAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selTyDelete", (char*) &_func_selTyDelete, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeup", (char*) &_func_selWakeup, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeupAll", (char*) &_func_selWakeupAll, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeupListInit", (char*) &_func_selWakeupListInit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeupListTerm", (char*) &_func_selWakeupListTerm, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_semExchange", (char*) &_func_semExchange, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_semRTake", (char*) &_func_semRTake, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_semWTake", (char*) &_func_semWTake, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_shellBpByIdRemove", (char*) &_func_shellBpByIdRemove, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_shellDbgCallPrint", (char*) &_func_shellDbgCallPrint, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_shellDbgStackTrace", (char*) &_func_shellDbgStackTrace, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_shellExcPrint", (char*) &_func_shellExcPrint, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_shlRtpDeleteAll", (char*) &_func_shlRtpDeleteAll, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_shlRtpInfoGet", (char*) &_func_shlRtpInfoGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigExcKill", (char*) &_func_sigExcKill, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigTimeoutRecalc", (char*) &_func_sigTimeoutRecalc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigeventInit", (char*) &_func_sigeventInit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigfillset", (char*) &_func_sigfillset, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_signalMmanHook", (char*) &_func_signalMmanHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigprocmask", (char*) &_func_sigprocmask, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_smObjObjShow", (char*) &_func_smObjObjShow, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spy", (char*) &_func_spy, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyClkStart", (char*) &_func_spyClkStart, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyClkStop", (char*) &_func_spyClkStop, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyReport", (char*) &_func_spyReport, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyStop", (char*) &_func_spyStop, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyTask", (char*) &_func_spyTask, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symByValueAndTypeFind", (char*) &_func_symByValueAndTypeFind, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_symByValueFind", (char*) &_func_symByValueFind, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_symEach", (char*) &_func_symEach, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindByName", (char*) &_func_symFindByName, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindByValue", (char*) &_func_symFindByValue, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindByValueAndType", (char*) &_func_symFindByValueAndType, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindSymbol", (char*) &_func_symFindSymbol, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symNameGet", (char*) &_func_symNameGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symRegister", (char*) &_func_symRegister, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symTblShutdown", (char*) &_func_symTblShutdown, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symTypeGet", (char*) &_func_symTypeGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symValueGet", (char*) &_func_symValueGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskCreateHookAdd", (char*) &_func_taskCreateHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskDeleteHookAdd", (char*) &_func_taskDeleteHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskMemCtxSwitch", (char*) &_func_taskMemCtxSwitch, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskPxAttrCreate", (char*) &_func_taskPxAttrCreate, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskPxAttrGet", (char*) &_func_taskPxAttrGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskPxAttrSet", (char*) &_func_taskPxAttrSet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskRegsShowRtn", (char*) &_func_taskRegsShowRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskStackAlloc", (char*) &_func_taskStackAlloc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskStackFree", (char*) &_func_taskStackFree, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tipStart", (char*) &_func_tipStart, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_tmrConnect", (char*) &_func_tmrConnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrDisable", (char*) &_func_tmrDisable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrEnable", (char*) &_func_tmrEnable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrFreq", (char*) &_func_tmrFreq, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrPeriod", (char*) &_func_tmrPeriod, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrStamp", (char*) &_func_tmrStamp, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrStampLock", (char*) &_func_tmrStampLock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_unldByModuleId", (char*) &_func_unldByModuleId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utf16ToCP", (char*) &_func_utf16ToCP, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utf16ToUtf8String", (char*) &_func_utf16ToUtf8String, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utf16ToUtf8StringBOM", (char*) &_func_utf16ToUtf8StringBOM, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utf8ToCP", (char*) &_func_utf8ToCP, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utf8ToUtf16String", (char*) &_func_utf8ToUtf16String, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utf8ToUtf16StringBOM", (char*) &_func_utf8ToUtf16StringBOM, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utflen16", (char*) &_func_utflen16, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_utflen8", (char*) &_func_utflen8, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_valloc", (char*) &_func_valloc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_virtExtraMapInfoGet", (char*) &_func_virtExtraMapInfoGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_virtSegInfoGet", (char*) &_func_virtSegInfoGet, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxMemProbeHook", (char*) &_func_vxMemProbeHook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxbDelayCommon", (char*) &_func_vxbDelayCommon, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxbIntConnect", (char*) &_func_vxbIntConnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDisable", (char*) &_func_vxbIntDisable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDisconnect", (char*) &_func_vxbIntDisconnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaConnect", (char*) &_func_vxbIntDynaConnect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaCtlrInputInit", (char*) &_func_vxbIntDynaCtlrInputInit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaVecAlloc", (char*) &_func_vxbIntDynaVecAlloc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaVecDevMultiProgram", (char*) &_func_vxbIntDynaVecDevMultiProgram, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaVecDisable", (char*) &_func_vxbIntDynaVecDisable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaVecEnable", (char*) &_func_vxbIntDynaVecEnable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaVecOwnerFind", (char*) &_func_vxbIntDynaVecOwnerFind, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntDynaVecProgram", (char*) &_func_vxbIntDynaVecProgram, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbIntEnable", (char*) &_func_vxbIntEnable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbPciAutoConfig", (char*) &_func_vxbPciAutoConfig, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbPciDevCfgRead", (char*) &_func_vxbPciDevCfgRead, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbPciDevCfgWrite", (char*) &_func_vxbPciDevCfgWrite, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxbUserHookDevInit", (char*) &_func_vxbUserHookDevInit, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxdbgBreakpoint", (char*) &_func_vxdbgBreakpoint, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxdbgFuncs", (char*) &_func_vxdbgFuncs, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxdbgRtpCont", (char*) &_func_vxdbgRtpCont, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxdbgRtpIdVerify", (char*) &_func_vxdbgRtpIdVerify, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxdbgRtpStop", (char*) &_func_vxdbgRtpStop, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_vxdbgTrace", (char*) &_func_vxdbgTrace, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_wdbBreakpoint", (char*) &_func_wdbBreakpoint, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_wdbExternEnterHookAdd", (char*) &_func_wdbExternEnterHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbExternExitHookAdd", (char*) &_func_wdbExternExitHookAdd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbExternNotifyHost", (char*) &_func_wdbExternNotifyHost, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbExternRcvHook", (char*) &_func_wdbExternRcvHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbIsNowExternal", (char*) &_func_wdbIsNowExternal, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbResumeSystem", (char*) &_func_wdbResumeSystem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbSuspendSystem", (char*) &_func_wdbSuspendSystem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbTaskBpByIdRemove", (char*) &_func_wdbTaskBpByIdRemove, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wdbTrace", (char*) &_func_wdbTrace, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_windSemRWDelete", (char*) &_func_windSemRWDelete, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_windTickAnnounceHook", (char*) &_func_windTickAnnounceHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_workQDbgTextDump", (char*) &_func_workQDbgTextDump, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_hostAdd", (char*) _hostAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_hostDelete", (char*) _hostDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_hostGetByAddr", (char*) _hostGetByAddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_hostGetByName", (char*) _hostGetByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_hostTblSearchByName2", (char*) _hostTblSearchByName2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ipcom_gethostbyaddr_r", (char*) &_ipcom_gethostbyaddr_r, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_ipcom_gethostbyname_r", (char*) &_ipcom_gethostbyname_r, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_ipdhcpc_callback_hook", (char*) &_ipdhcpc_callback_hook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_linkMemReqClAlign", (char*) &_linkMemReqClAlign, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_linkMemReqMlinkAlign", (char*) &_linkMemReqMlinkAlign, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_muxProtosPerEndInc", (char*) &_muxProtosPerEndInc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_muxProtosPerEndStart", (char*) &_muxProtosPerEndStart, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_netMemReqDefault", (char*) _netMemReqDefault, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_netSysctl", (char*) &_netSysctl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_netSysctlCli", (char*) &_netSysctlCli, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pLinkPoolFuncTbl", (char*) &_pLinkPoolFuncTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pNetBufCollect", (char*) &_pNetBufCollect, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pNetDpool", (char*) &_pNetDpool, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_pNetPoolFuncTbl", (char*) &_pNetPoolFuncTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pNetSysPool", (char*) &_pNetSysPool, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_pSigQueueFreeHead", (char*) &_pSigQueueFreeHead, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_panicHook", (char*) &_panicHook, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_procNumWasSet", (char*) &_procNumWasSet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_setjmpSetup", (char*) _setjmpSetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxLoad", (char*) _sigCtxLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxRtnValSet", (char*) _sigCtxRtnValSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxSave", (char*) _sigCtxSave, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxSetup", (char*) _sigCtxSetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxStackEnd", (char*) _sigCtxStackEnd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigfaulttable", (char*) &_sigfaulttable, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_sysInit", (char*) _sysInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_taskSuspend", (char*) _taskSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vx_offset_COPROC_DESC_ctxAlign", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_DESC_ctxSize", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_DESC_mask", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_DESC_next", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_DESC_pCtxGetRtn", (char*) 0x00000028, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_DESC_pLastEntry", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_TBL_ENTRY_pCtx", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_TBL_ENTRY_pDescriptor", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_TBL_ENTRY_pTask", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_COPROC_TBL_ENTRY_size", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DEV_HDR_drvNum", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DEV_HDR_name", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DL_LIST_head", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DL_NODE_next", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_close", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_create", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_delete", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_inuse", (char*) 0x00000020, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_ioctl", (char*) 0x00000018, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_open", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_read", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_DRV_ENTRY_de_write", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_FD_ENTRY_pDevHdr", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_FD_ENTRY_refCnt", (char*) 0x0000004c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_FD_ENTRY_value", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HANDLE_attributes", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HANDLE_context", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HANDLE_contextType", (char*) 0x0000000b, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HANDLE_magic", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HANDLE_objSize", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HANDLE_type", (char*) 0x0000000a, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HASH_TBL_elements", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_HASH_TBL_pHashTbl", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_KERNEL_RTP_CMN_ctxCnt", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_KERNEL_RTP_CMN_pWdbInfo", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_KERNEL_RTP_CMN_pgMgrId", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_KERNEL_RTP_CMN_sharedDataList", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_KERNEL_RTP_CMN_vmContextId", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_PART_STATS_maxBlockSizeFree", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_PART_STATS_maxBytesAlloc", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_PART_STATS_numBlocksAlloc", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_PART_STATS_numBlocksFree", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_PART_STATS_numBytesAlloc", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_PART_STATS_numBytesFree", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MEM_SECTION_HDR_size", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODLIST_DESC_moduleList", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_commTotalSize", (char*) 0x0000053c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_ctors", (char*) 0x00000534, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_dtors", (char*) 0x00000538, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_flags", (char*) 0x00000518, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_format", (char*) 0x0000052c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_group", (char*) 0x00000530, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_nameWithPath", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_sectionList", (char*) 0x0000051c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_segmentList", (char*) 0x00000524, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_swapNeeded", (char*) 0x00000540, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MODULE_undefSymCount", (char*) 0x00000544, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_NODE_message", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_NODE_msgLength", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_HEAD_count", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_HEAD_list", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_HEAD_pendQ", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_events", (char*) 0x0000008c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_freeQ", (char*) 0x0000005c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_maxMsgLength", (char*) 0x00000080, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_maxMsgs", (char*) 0x0000007c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_msgQ", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_options", (char*) 0x00000078, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_recvTimeouts", (char*) 0x00000088, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_MSG_Q_sendTimeouts", (char*) 0x00000084, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_altClassId", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_createRtn", (char*) 0x00000020, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_destroyRtn", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_handle", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_initRtn", (char*) 0x00000030, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_instRtn", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objClassType", (char*) 0x00000038, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objMemAllocRtn", (char*) 0x00000028, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objMemFreeRtn", (char*) 0x0000002c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objPartId", (char*) 0x00000034, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objPrivList", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objPubList", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_objSize", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_openRtn", (char*) 0x00000024, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_options", (char*) 0x0000003c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_pClassSem", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_OBJ_CLASS_showRtn", (char*) 0x00000018, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PAGE_MGR_OBJ_mmapList", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PAGE_MGR_OBJ_options", (char*) 0x00000018, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PAGE_MGR_OBJ_physPgPoolId", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PAGE_MGR_OBJ_virtPgPoolId", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PAGE_MGR_OBJ_vmContextId", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_avlSize", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_cumBlocksAllocated", (char*) 0x000000ec, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_cumWordsAllocated", (char*) 0x000000f4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_curBlocksAllocated", (char*) 0x000000e4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_curBlocksAllocatedInternal", (char*) 0x00000100, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_curBlocksFreed", (char*) 0x000000dc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_curWordsAllocated", (char*) 0x000000e8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_curWordsAllocatedInternal", (char*) 0x00000104, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_curWordsFreed", (char*) 0x000000e0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_freeSizeNodeNb", (char*) 0x0000004c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_maxWordsAllocated", (char*) 0x000000fc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_options", (char*) 0x000000bc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_sectionHdrLst", (char*) 0x000000c0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_sem", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PARTITION_totalWords", (char*) 0x000000b8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_ATTR_mq_curmsgs", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_ATTR_mq_flags", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_ATTR_mq_maxmsg", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_ATTR_mq_msgsize", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_DES_f_data", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_DES_f_flag", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_msgq_attr", (char*) 0x00000114, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_msgq_cond_data", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_POSIX_MSG_Q_msgq_cond_read", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PSEMAPHORE_objCore", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PSEMAPHORE_pSelf", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_PSEMAPHORE_wSemId", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_Q_FIFO_G_HEAD_pFifoQ", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_buffSize", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_bytesPeak", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_bytesRead", (char*) 0x0000003c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_bytesWritten", (char*) 0x00000038, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_currBuffs", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_dataContent", (char*) 0x00000024, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_emptyBuffs", (char*) 0x00000020, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_maxBuffs", (char*) 0x00000018, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_maxBuffsActual", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_minBuffs", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_options", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_readsSinceReset", (char*) 0x0000002c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_srcPart", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_threshold", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_timesExtended", (char*) 0x00000030, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_timesXThreshold", (char*) 0x00000034, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_INFO_TYPE_writesSinceReset", (char*) 0x00000028, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_TYPE_buffDesc", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_TYPE_buffRead", (char*) 0x000000a0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_TYPE_buffWrite", (char*) 0x000000a4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_TYPE_dataRead", (char*) 0x000000a8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_RBUFF_TYPE_dataWrite", (char*) 0x000000ac, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_REG_SET_pc", (char*) 0x00000024, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_REG_SET_size", (char*) 0x00000028, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_REG_SET_sp", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_address", (char*) 0x00000018, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_checksum", (char*) 0x0000002c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_flags", (char*) 0x00000024, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_name", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_sectionNode", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_size", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SECTION_DESC_type", (char*) 0x00000020, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEGMENT_address", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEGMENT_flags", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEGMENT_segmentNode", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEGMENT_size", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEGMENT_type", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEMAPHORE_count", (char*) 0x00000054, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEMAPHORE_events", (char*) 0x00000058, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEMAPHORE_options", (char*) 0x00000041, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEMAPHORE_qHead", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SEMAPHORE_semType", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SL_LIST_head", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SL_LIST_size", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SL_NODE_next", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_BLOCK_HDR_nWords", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_FREE_BLOCK_node", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_NODE_message", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_NODE_msgLength", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_freeQ", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_freeQSem", (char*) 0x0000002c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_maxMsgLength", (char*) 0x00000058, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_maxMsgs", (char*) 0x00000054, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_msgQ", (char*) 0x00000024, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_msgQSem", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_options", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_recvTimeouts", (char*) 0x00000060, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_MSG_Q_sendTimeouts", (char*) 0x0000005c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_curNumMsgQ", (char*) 0x000001d0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_curNumName", (char*) 0x000001dc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_curNumPart", (char*) 0x000001d8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_curNumSemB", (char*) 0x000001c8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_curNumSemC", (char*) 0x000001cc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_curNumTask", (char*) 0x000001d4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_maxMemParts", (char*) 0x000001c0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_maxMsgQueues", (char*) 0x000001b8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_maxNames", (char*) 0x000001c4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_maxSems", (char*) 0x000001b4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_maxTasks", (char*) 0x000001bc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_nameDtb", (char*) 0x00000184, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_objCpuTbl", (char*) 0x000001b0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_smMsgQPart", (char*) 0x000000b8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_smNamePart", (char*) 0x00000074, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_smPartPart", (char*) 0x000000fc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_smSemPart", (char*) 0x00000030, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_smSysPart", (char*) 0x00000140, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_MEM_HDR_smTcbPart", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_TCB_localTcb", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_TCB_ownerCpu", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_OBJ_objType", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_PARTITION_cumBlocksAllocated", (char*) 0x0000003c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_PARTITION_cumWordsAllocated", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_PARTITION_curBlocksAllocated", (char*) 0x00000034, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_PARTITION_curWordsAllocated", (char*) 0x00000038, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_PARTITION_freeList", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_PARTITION_totalWords", (char*) 0x00000028, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_SEMAPHORE_count", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_SEMAPHORE_flag", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_SEMAPHORE_lock", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_SEMAPHORE_objType", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_SEMAPHORE_smPendQ", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SM_SEMAPHORE_verify", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYMBOL_group", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYMBOL_name", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYMBOL_symRef", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYMBOL_type", (char*) 0x00000012, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYMBOL_value", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYMTAB_nameHashId", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYSCALL_ENTRY_STATE_args", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYSCALL_ENTRY_STATE_pUStack", (char*) 0x0000003c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYSCALL_ENTRY_STATE_pc", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYSCALL_ENTRY_STATE_scn", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_SYSCALL_ENTRY_STATE_size", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_actionArg", (char*) 0x00000074, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_actionDef", (char*) 0x00000078, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_actionFunc", (char*) 0x00000070, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_actionType", (char*) 0x0000006c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_chain", (char*) 0x00000054, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_condEx1", (char*) 0x00000060, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_condEx2", (char*) 0x00000068, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_condOp", (char*) 0x00000064, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_condType", (char*) 0x0000005c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_conditional", (char*) 0x00000058, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_contextId", (char*) 0x0000004c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_contextType", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_disable", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_eventId", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_hitCnt", (char*) 0x0000007c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_initialState", (char*) 0x00000080, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_objCore", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_objId", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_pDataCollector", (char*) 0x00000084, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_TRIGGER_status", (char*) 0x00000042, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_dropped", (char*) 0x00000022, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_hiwatermark", (char*) 0x00000020, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_node", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_pLastExp", (char*) 0x00000018, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_pLastReg", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_pPeerSocket", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_pRecvPacket", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_pSelfSocket", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_selfName", (char*) 0x00000012, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_UNCOMPCB_selfState", (char*) 0x00000010, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc1Task", (char*) 0x01000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc2Task", (char*) 0x02000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc3Task", (char*) 0x04000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc4Task", (char*) 0x08000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc5Task", (char*) 0x10000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc6Task", (char*) 0x20000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc7Task", (char*) 0x40000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_coproc8Task", (char*) 0x80000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_VX_fpTask", (char*) 0x01000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WDOG_deferStartCnt", (char*) 0x00000052, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WDOG_status", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WDOG_timeout", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WDOG_wdParameter", (char*) 0x00000058, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WDOG_wdRoutine", (char*) 0x00000054, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_arg", (char*) 0x0000005c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_count", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_cpuTime", (char*) 0x0000004c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_handlerRtn", (char*) 0x00000058, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_isrTag", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_objCore", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_options", (char*) 0x00000054, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_ISR_serviceCount", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_accessCnt", (char*) 0x0000003e, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_classNode", (char*) 0x0000001c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_handle", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_name", (char*) 0x0000002c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_objHandleList", (char*) 0x00000034, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_ownerId", (char*) 0x00000024, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_ownerList", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_ownerNode", (char*) 0x00000014, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_ownerRtpId", (char*) 0x00000028, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_pObjClass", (char*) 0x00000030, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_OBJ_refCnt", (char*) 0x0000003c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_binaryInfo", (char*) 0x00000088, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_cpuTimeInfo", (char*) 0x00000b60, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_defPath", (char*) 0x000000d4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_defPathLen", (char*) 0x000000d8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_entrAddr", (char*) 0x00000078, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_fdTable", (char*) 0x000000cc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_fdTableSize", (char*) 0x000000d0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_initTaskId", (char*) 0x0000007c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_kernelRtpCmn", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_lockTaskId", (char*) 0x00000b48, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_options", (char*) 0x00000074, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_pArgv", (char*) 0x0000006c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_pEnv", (char*) 0x00000070, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_pPathName", (char*) 0x00000068, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_pSchedInfo", (char*) 0x00000b70, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_pSigQFreeHead", (char*) 0x00000714, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_parentRtpId", (char*) 0x00000728, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_rtpNode", (char*) 0x00000058, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_semId", (char*) 0x00000060, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_sigReturnRtn", (char*) 0x000000e0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_signalInfo", (char*) 0x000000e4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_sigwaitQ", (char*) 0x00000718, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_status", (char*) 0x00000064, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_symTabId", (char*) 0x00000084, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_taskCnt", (char*) 0x000000b4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_RTP_taskExitRtn", (char*) 0x000000dc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_attr", (char*) 0x000000ac, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_clientCount", (char*) 0x000000b4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_objCore", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_options", (char*) 0x000000a8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_physAdrs", (char*) 0x000000b8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_sem", (char*) 0x00000040, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_size", (char*) 0x000000b0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SD_virtAdrs", (char*) 0x000000bc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_fd", (char*) 0x00000044, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_linger", (char*) 0x00000008, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_options", (char*) 0x00000006, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_pcb", (char*) 0x0000000c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_qlen", (char*) 0x00000030, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_qlimit", (char*) 0x00000034, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_state", (char*) 0x0000000a, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_SOCKET_so_type", (char*) 0x00000004, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_cpuTimeInfo", (char*) 0x00000160, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_entry", (char*) 0x000000c0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_errorStatus", (char*) 0x000000d0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_events", (char*) 0x00000124, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_excCnt", (char*) 0x0000006c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_excInfo", (char*) 0x000001b4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_objCore", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_options", (char*) 0x00000098, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pCoprocTbl", (char*) 0x000000f0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pEdrInfo", (char*) 0x000000cc, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pExcRegSet", (char*) 0x00000120, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pExcStackBase", (char*) 0x00000060, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pExcStackEnd", (char*) 0x00000064, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pPendQ", (char*) 0x000000a8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pPriMutex", (char*) 0x0000008c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pPwrMgmtPState", (char*) 0x00000170, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pSchedInfo", (char*) 0x00000174, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pStackBase", (char*) 0x000000c4, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pStackEnd", (char*) 0x000000c8, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pTlsDesc", (char*) 0x00000250, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_pUTcb", (char*) 0x0000009c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_priDrop", (char*) 0x00000088, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_priInheritCnt", (char*) 0x00000084, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_priMutexCnt", (char*) 0x00000080, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_priNormal", (char*) 0x00000078, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_priority", (char*) 0x00000074, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_qNode", (char*) 0x00000050, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_regs", (char*) 0x00000220, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_rtpId", (char*) 0x00000094, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_safeCnt", (char*) 0x000000ac, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_status", (char*) 0x00000070, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_taskTicks", (char*) 0x000000e0, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_timeout", (char*) 0x00000048, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_WIND_TCB_windSmpInfo", (char*) 0x0000017c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_sizeof_FD_ENTRY", (char*) 0x0000005c, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vx_offset_syscallEntryBaseOffset", (char*) 0x00000000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "_vxb_clkConnectRtn", (char*) &_vxb_clkConnectRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_clkDisableRtn", (char*) &_vxb_clkDisableRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_clkEnableRtn", (char*) &_vxb_clkEnableRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_clkRateGetRtn", (char*) &_vxb_clkRateGetRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_clkRateSetRtn", (char*) &_vxb_clkRateSetRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_delayRtn", (char*) &_vxb_delayRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_msDelayRtn", (char*) &_vxb_msDelayRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxb_usDelayRtn", (char*) &_vxb_usDelayRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_vxmux_pNullPoolFuncTbl", (char*) &_vxmux_pNullPoolFuncTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_wdbCtxLoad", (char*) _wdbCtxLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_wdbCtxSave", (char*) _wdbCtxSave, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_zbufDeleteEmpty", (char*) _zbufDeleteEmpty, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_zbufGetSeg", (char*) _zbufGetSeg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_zbufSetSeg", (char*) _zbufSetSeg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "abort", (char*) abort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "abs", (char*) abs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "absSymbols_Bounds", (char*) absSymbols_Bounds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "absSymbols_Common", (char*) absSymbols_Common, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "accept", (char*) accept, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "access", (char*) access, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "acos", (char*) acos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "aimFppLibInit", (char*) aimFppLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "aimMmuBaseLibInit", (char*) aimMmuBaseLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocChunkEndGuardSize", (char*) &allocChunkEndGuardSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "applLoggerInit", (char*) applLoggerInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "applLoggerStop", (char*) applLoggerStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "applUtilInstInit", (char*) applUtilInstInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "applUtilLogSem", (char*) &applUtilLogSem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "asctime", (char*) asctime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "asctime_r", (char*) asctime_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "asin", (char*) asin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "assertlist", (char*) &assertlist, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ata0Resources", (char*) &ata0Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ataResources", (char*) &ataResources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ataTypes", (char*) &ataTypes, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "atan", (char*) atan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atan2", (char*) atan2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atexit", (char*) atexit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atof", (char*) atof, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atoi", (char*) atoi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atol", (char*) atol, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Add", (char*) atomic32Add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32And", (char*) atomic32And, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Cas", (char*) atomic32Cas, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Clear", (char*) atomic32Clear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Dec", (char*) atomic32Dec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Get", (char*) atomic32Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Inc", (char*) atomic32Inc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Nand", (char*) atomic32Nand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Or", (char*) atomic32Or, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Set", (char*) atomic32Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Sub", (char*) atomic32Sub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atomic32Xor", (char*) atomic32Xor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "attrib", (char*) attrib, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "audio_test", (char*) audio_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintDelete", (char*) avlUintDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintInsert", (char*) avlUintInsert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintMaximumGet", (char*) avlUintMaximumGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintMinimumGet", (char*) avlUintMinimumGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintPredecessorGet", (char*) avlUintPredecessorGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintSearch", (char*) avlUintSearch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintSuccessorGet", (char*) avlUintSuccessorGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "avlUintTreeWalk", (char*) avlUintTreeWalk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "b", (char*) b, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "baseExcOSMStack", (char*) &baseExcOSMStack, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bcmp", (char*) bcmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopy", (char*) bcopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopyBytes", (char*) bcopyBytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopyLongs", (char*) bcopyLongs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopyWords", (char*) bcopyWords, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bd", (char*) bd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bdall", (char*) bdall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bfill", (char*) bfill, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bfillBytes", (char*) bfillBytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bfillLongs", (char*) bfillLongs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bfillWords", (char*) bfillWords, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bh", (char*) bh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bind", (char*) bind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bindresvport", (char*) bindresvport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bindresvportCommon", (char*) bindresvportCommon, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bindresvport_af", (char*) bindresvport_af, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "binvert", (char*) binvert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bioInit", (char*) bioInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bio_alloc", (char*) bio_alloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bio_done", (char*) bio_done, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bio_free", (char*) bio_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootApp", (char*) bootApp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootAppBootFileLoadAndGo", (char*) bootAppBootFileLoadAndGo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootAppInit", (char*) bootAppInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootAppPrintHeaderFunc", (char*) &bootAppPrintHeaderFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootAppPrintf", (char*) bootAppPrintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootAppShellFunc", (char*) &bootAppShellFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootAppTask", (char*) bootAppTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootAppTaskId", (char*) &bootAppTaskId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bootBpAnchorExtract", (char*) bootBpAnchorExtract, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootChange", (char*) bootChange, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootCmdNameSkip", (char*) bootCmdNameSkip, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootCommandHandlerAdd", (char*) bootCommandHandlerAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootCommandHelpAdd", (char*) bootCommandHelpAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootDelayedInit", (char*) &bootDelayedInit, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootDevFormatHelpAdd", (char*) bootDevFormatHelpAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootDisableMmuBeforeEntry", (char*) &bootDisableMmuBeforeEntry, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bootFlagHelpAdd", (char*) bootFlagHelpAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootFsFileLoad", (char*) bootFsFileLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootFsLoad", (char*) bootFsLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootFsLoadInit", (char*) bootFsLoadInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootGoOverrideFunc", (char*) &bootGoOverrideFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootLeaseExtract", (char*) bootLeaseExtract, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootLoad", (char*) bootLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootLoadModule", (char*) bootLoadModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootLoadRoutine", (char*) &bootLoadRoutine, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bootLoaderAdd", (char*) bootLoaderAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootMemBase", (char*) &bootMemBase, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootNetDevStopAllFunc", (char*) &bootNetDevStopAllFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootNetSettingsUpdateFunc", (char*) &bootNetSettingsUpdateFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootNetmaskExtract", (char*) bootNetmaskExtract, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamCheck", (char*) bootParamCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamsErrorPrint", (char*) bootParamsErrorPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamsPrompt", (char*) bootParamsPrompt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamsShow", (char*) bootParamsShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootPrintDevsFuncAdd", (char*) bootPrintDevsFuncAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootScanNum", (char*) bootScanNum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootShellAutobootFunc", (char*) &bootShellAutobootFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootShellDevFormatHelpAddFunc", (char*) &bootShellDevFormatHelpAddFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootShellFlagHelpAddFunc", (char*) &bootShellFlagHelpAddFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootShellHelpAddFunc", (char*) &bootShellHelpAddFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootShellPrintDevAddFunc", (char*) &bootShellPrintDevAddFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootShellPrintfFunc", (char*) &bootShellPrintfFunc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bootShellPrompt", (char*) &bootShellPrompt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bootSpaceSkip", (char*) bootSpaceSkip, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootStringToStruct", (char*) bootStringToStruct, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootStringToStructAdd", (char*) bootStringToStructAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootStructToString", (char*) bootStructToString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsearch", (char*) bsearch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bspSerialChanGet", (char*) bspSerialChanGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bswap", (char*) bswap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "busCtlrBaseAddrCvt_desc", (char*) &busCtlrBaseAddrCvt_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "busCtlrCfgInfo_desc", (char*) &busCtlrCfgInfo_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "busCtlrDevCfgRead_desc", (char*) &busCtlrDevCfgRead_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "busCtlrDevCfgWrite_desc", (char*) &busCtlrDevCfgWrite_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "busCtlrDevCtlr_desc", (char*) &busCtlrDevCtlr_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "busCtlrInterruptInfo_desc", (char*) &busCtlrInterruptInfo_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bzero", (char*) bzero, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "c", (char*) c, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchClear", (char*) cacheArchClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchClearEntry", (char*) cacheArchClearEntry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchDisable", (char*) cacheArchDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchDmaFree", (char*) cacheArchDmaFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchDmaMalloc", (char*) cacheArchDmaMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchEnable", (char*) cacheArchEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchFlush", (char*) cacheArchFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchLibInit", (char*) cacheArchLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchLock", (char*) cacheArchLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchUnlock", (char*) cacheArchUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheClear", (char*) cacheClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDataEnabled", (char*) &cacheDataEnabled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDataMode", (char*) &cacheDataMode, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDisable", (char*) cacheDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDmaFree", (char*) cacheDmaFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDmaFreeRtn", (char*) &cacheDmaFreeRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDmaFuncs", (char*) &cacheDmaFuncs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDmaMalloc", (char*) cacheDmaMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDmaMallocRtn", (char*) &cacheDmaMallocRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDrvFlush", (char*) cacheDrvFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDrvInvalidate", (char*) cacheDrvInvalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDrvPhysToVirt", (char*) cacheDrvPhysToVirt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDrvVirtToPhys", (char*) cacheDrvVirtToPhys, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheEnable", (char*) cacheEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheFlush", (char*) cacheFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheFlushBytes", (char*) &cacheFlushBytes, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheForeignClear", (char*) cacheForeignClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheForeignFlush", (char*) cacheForeignFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheForeignInvalidate", (char*) cacheForeignInvalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheFuncsSet", (char*) cacheFuncsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Clear", (char*) cacheI86Clear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Disable", (char*) cacheI86Disable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Enable", (char*) cacheI86Enable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Flush", (char*) cacheI86Flush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Lock", (char*) cacheI86Lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Reset", (char*) cacheI86Reset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheI86Unlock", (char*) cacheI86Unlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheInvalidate", (char*) cacheInvalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheLib", (char*) &cacheLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheLibInit", (char*) cacheLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheLock", (char*) cacheLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheMmuAvailable", (char*) &cacheMmuAvailable, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheNullFuncs", (char*) &cacheNullFuncs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cachePen4Clear", (char*) cachePen4Clear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cachePen4Flush", (char*) cachePen4Flush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cachePipeFlush", (char*) cachePipeFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheTextLocalUpdate", (char*) cacheTextLocalUpdate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheTextUpdate", (char*) cacheTextUpdate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheUnlock", (char*) cacheUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheUserFuncs", (char*) &cacheUserFuncs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "calloc", (char*) calloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "catInfo", (char*) &catInfo, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cbrt", (char*) cbrt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cd", (char*) cd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ceil", (char*) ceil, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cfree", (char*) cfree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "changeFpReg", (char*) changeFpReg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "changeLogLevel", (char*) changeLogLevel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "changeReg", (char*) changeReg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chdir", (char*) chdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "checkStack", (char*) checkStack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "checksum", (char*) checksum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chkdsk", (char*) chkdsk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chmod", (char*) chmod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classCreateConnect", (char*) classCreateConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classDestroyConnect", (char*) classDestroyConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classIdTable", (char*) &classIdTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "classInit", (char*) classInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classLibInit", (char*) classLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classListLibInit", (char*) classListLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classMemPartIdSet", (char*) classMemPartIdSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classOpenConnect", (char*) classOpenConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classShowConnect", (char*) classShowConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clearerr", (char*) clearerr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock", (char*) clock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clockLibInit", (char*) clockLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_getres", (char*) clock_getres, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_gettime", (char*) clock_gettime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_gettime_wd", (char*) clock_gettime_wd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_nanosleep", (char*) clock_nanosleep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_setres", (char*) clock_setres, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_settime", (char*) clock_settime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "close", (char*) close, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "closedir", (char*) closedir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "com_change_baudrate", (char*) com_change_baudrate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "com_read_ex", (char*) com_read_ex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "com_receive", (char*) com_receive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "com_test", (char*) com_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "com_transmit", (char*) com_transmit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "com_write_ex", (char*) com_write_ex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "commit", (char*) commit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "completionPathComplete", (char*) completionPathComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "completionPathListGet", (char*) completionPathListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "completionPathShow", (char*) completionPathShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "completionSymComplete", (char*) completionSymComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "completionSymListGet", (char*) completionSymListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "completionSymShow", (char*) completionSymShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "connect", (char*) connect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "connectWithTimeout", (char*) connectWithTimeout, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "consoleFd", (char*) &consoleFd, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "convertAttrFromArchDepToIndep", (char*) convertAttrFromArchDepToIndep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "convertAttrFromArchIndepToDep", (char*) convertAttrFromArchIndepToDep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocCtxReplicate", (char*) coprocCtxReplicate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocCtxStorageSizeGet", (char*) coprocCtxStorageSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocDescriptorsInit", (char*) coprocDescriptorsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocDisable", (char*) coprocDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocEnable", (char*) coprocEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocLibInit", (char*) coprocLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocMRegs", (char*) coprocMRegs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocRegListShow", (char*) coprocRegListShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocSave", (char*) coprocSave, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocShow", (char*) coprocShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocShowInit", (char*) coprocShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocShowOnDebug", (char*) coprocShowOnDebug, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocTaskCreateHook", (char*) coprocTaskCreateHook, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocTaskDeleteHook", (char*) coprocTaskDeleteHook, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocTaskRegsGet", (char*) coprocTaskRegsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocTaskRegsSet", (char*) coprocTaskRegsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocTaskRegsShow", (char*) coprocTaskRegsShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocTaskSwapHook", (char*) coprocTaskSwapHook, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "coprocsDiscover", (char*) coprocsDiscover, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copy", (char*) copy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copyStreams", (char*) copyStreams, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copyright_wind_river", (char*) &copyright_wind_river, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "copysign", (char*) copysign, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cos", (char*) cos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cosh", (char*) cosh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cp", (char*) cp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCallCtors", (char*) cplusCallCtors, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCallDtors", (char*) cplusCallDtors, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCtors", (char*) cplusCtors, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCtorsLink", (char*) cplusCtorsLink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemangle", (char*) cplusDemangle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemangle2", (char*) cplusDemangle2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemangle2Func", (char*) &cplusDemangle2Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplusDemangleFunc", (char*) &cplusDemangleFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplusDemangleToBuffer", (char*) cplusDemangleToBuffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemangleToBufferFunc", (char*) &cplusDemangleToBufferFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplusDemanglerMode", (char*) &cplusDemanglerMode, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplusDemanglerSet", (char*) cplusDemanglerSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemanglerStyle", (char*) &cplusDemanglerStyle, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "cplusDemanglerStyleInit", (char*) cplusDemanglerStyleInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemanglerStyleSet", (char*) cplusDemanglerStyleSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDtors", (char*) cplusDtors, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDtorsLink", (char*) cplusDtorsLink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusLoadFixup", (char*) cplusLoadFixup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusMangledSymCheck", (char*) cplusMangledSymCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusMangledSymGet", (char*) cplusMangledSymGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusMatchMangled", (char*) cplusMatchMangled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusMatchMangledListGet", (char*) cplusMatchMangledListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusUnloadFixup", (char*) cplusUnloadFixup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusUserAsk", (char*) cplusUserAsk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusXtorGet", (char*) cplusXtorGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusXtorSet", (char*) cplusXtorSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusXtorStrategy", (char*) &cplusXtorStrategy, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cpuPwrArchLibInit", (char*) cpuPwrArchLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrCStateHookSet", (char*) cpuPwrCStateHookSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrCStateSet", (char*) cpuPwrCStateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrCheckHotRtn", (char*) cpuPwrCheckHotRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrEventHandlersSet", (char*) cpuPwrEventHandlersSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrFrameWorkInit", (char*) cpuPwrFrameWorkInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrIntEnter", (char*) cpuPwrIntEnter, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrIntExit", (char*) cpuPwrIntExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrLightMgrInit", (char*) cpuPwrLightMgrInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrMgrEnable", (char*) cpuPwrMgrEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrMgrIsEnabled", (char*) cpuPwrMgrIsEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrPStateGet", (char*) cpuPwrPStateGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrPStateSet", (char*) cpuPwrPStateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrTaskCreateRtn", (char*) cpuPwrTaskCreateRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrTaskPStateGet", (char*) cpuPwrTaskPStateGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrTaskPStateSet", (char*) cpuPwrTaskPStateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrTaskSwapRtn", (char*) cpuPwrTaskSwapRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrTempThreshGet", (char*) cpuPwrTempThreshGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrTempThreshSet", (char*) cpuPwrTempThreshSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrThermIntConnect", (char*) cpuPwrThermIntConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrThermIntHandler", (char*) cpuPwrThermIntHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrUtilPeriodSet", (char*) cpuPwrUtilPeriodSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrWdDownRtn", (char*) cpuPwrWdDownRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpuPwrWdStartFailed", (char*) &cpuPwrWdStartFailed, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cpuPwrWdUpRtn", (char*) cpuPwrWdUpRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "crc16", (char*) crc16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "creat", (char*) creat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "creationDate", (char*) &creationDate, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cret", (char*) cret, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ctime", (char*) ctime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ctime_r", (char*) ctime_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "d", (char*) d, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgBpEpCoreRtn", (char*) dbgBpEpCoreRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgBpListPrint", (char*) dbgBpListPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgCallPrint", (char*) dbgCallPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgDisassemble", (char*) dbgDisassemble, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgDynPrintfCommonRtn", (char*) dbgDynPrintfCommonRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgHelp", (char*) dbgHelp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgInit", (char*) dbgInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgPrintDsp", (char*) &dbgPrintDsp, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgPrintFpp", (char*) &dbgPrintFpp, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgPrintSimd", (char*) &dbgPrintSimd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgStackTrace", (char*) dbgStackTrace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgTaskTraceCoreRtn", (char*) dbgTaskTraceCoreRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "debugIx", (char*) &debugIx, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "debugPwrMgmt", (char*) &debugPwrMgmt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "defaultDrv", (char*) &defaultDrv, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "devAttach", (char*) devAttach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devDetach", (char*) devDetach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devInit", (char*) devInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devMap", (char*) devMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devMapUnsafe", (char*) devMapUnsafe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devName", (char*) devName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devResourceGet", (char*) devResourceGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devResourceIntrGet", (char*) devResourceIntrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devUnmap", (char*) devUnmap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devUnmapUnsafe", (char*) devUnmapUnsafe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devs", (char*) devs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dfltInumTbl", (char*) &dfltInumTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "difftime", (char*) difftime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dirList", (char*) dirList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "diskFormat", (char*) diskFormat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "diskInit", (char*) diskInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "div", (char*) div, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "div_r", (char*) div_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllAdd", (char*) dllAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllCount", (char*) dllCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllEach", (char*) dllEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllGet", (char*) dllGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllInit", (char*) dllInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllInsert", (char*) dllInsert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllRemove", (char*) dllRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllTerminate", (char*) dllTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dma_page_addr", (char*) &dma_page_addr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dma_test", (char*) dma_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosChkDebug", (char*) &dosChkDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosChkDsk", (char*) dosChkDsk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosChkLibInit", (char*) dosChkLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosChkMinDate", (char*) &dosChkMinDate, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosDirHdlrsList", (char*) &dosDirHdlrsList, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosDirOldDebug", (char*) &dosDirOldDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosDirOldLibInit", (char*) dosDirOldLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFatHdlrsList", (char*) &dosFatHdlrsList, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheCreateRtn", (char*) &dosFsCacheCreateRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheDataDirDefaultSize", (char*) &dosFsCacheDataDirDefaultSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheDeleteRtn", (char*) &dosFsCacheDeleteRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheFatDefaultSize", (char*) &dosFsCacheFatDefaultSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheMountRtn", (char*) &dosFsCacheMountRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheShow", (char*) dosFsCacheShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsCacheUnmountRtn", (char*) &dosFsCacheUnmountRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsChkDsk", (char*) dosFsChkDsk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsChkRtn", (char*) &dosFsChkRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsClose", (char*) dosFsClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDebug", (char*) &dosFsDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsDevCreate", (char*) dosFsDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDevDelete", (char*) dosFsDevDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDiskProbe", (char*) dosFsDiskProbe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDrvNum", (char*) &dosFsDrvNum, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsFatInit", (char*) dosFsFatInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsFdFree", (char*) dosFsFdFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsFdGet", (char*) dosFsFdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsFmtLargeWriteSize", (char*) &dosFsFmtLargeWriteSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsFmtLibInit", (char*) dosFsFmtLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsFmtRtn", (char*) &dosFsFmtRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsHdlrInstall", (char*) dosFsHdlrInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsIoctl", (char*) dosFsIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsLastAccessDateEnable", (char*) dosFsLastAccessDateEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsLibInit", (char*) dosFsLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsMonitorDevCreate", (char*) dosFsMonitorDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsMsgLevel", (char*) &dosFsMsgLevel, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsMutexOptions", (char*) &dosFsMutexOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsOpen", (char*) dosFsOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsShow", (char*) dosFsShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsShowInit", (char*) dosFsShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsTCacheShow", (char*) dosFsTCacheShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolDescGet", (char*) dosFsVolDescGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolFormat", (char*) dosFsVolFormat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolFormatFd", (char*) dosFsVolFormatFd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolIsFat12", (char*) dosFsVolIsFat12, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolUnmount", (char*) dosFsVolUnmount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolumeBioBufferSize", (char*) &dosFsVolumeBioBufferSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsVolumeOptionsGet", (char*) dosFsVolumeOptionsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolumeOptionsSet", (char*) dosFsVolumeOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsXbdBlkCopy", (char*) dosFsXbdBlkCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsXbdBlkRead", (char*) dosFsXbdBlkRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsXbdBlkWrite", (char*) dosFsXbdBlkWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsXbdBytesRW", (char*) dosFsXbdBytesRW, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsXbdIoctl", (char*) dosFsXbdIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosPathParse", (char*) dosPathParse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosSetVolCaseSens", (char*) dosSetVolCaseSens, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosVDirDebug", (char*) &dosVDirDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosVDirLibInit", (char*) dosVDirLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosVDirMutexOpt", (char*) &dosVDirMutexOpt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosVDirReaddirPlus", (char*) dosVDirReaddirPlus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosfsDiskFormat", (char*) dosfsDiskFormat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosfsDiskToHost16", (char*) dosfsDiskToHost16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosfsDiskToHost32", (char*) dosfsDiskToHost32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosfsHostToDisk16", (char*) dosfsHostToDisk16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosfsHostToDisk32", (char*) dosfsHostToDisk32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dprintf", (char*) dprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dprintfVerboseLvl", (char*) &dprintfVerboseLvl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "drem", (char*) drem, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "drvTable", (char*) &drvTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dsmAsize", (char*) &dsmAsize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dsmData", (char*) dsmData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dsmDebug", (char*) &dsmDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dsmDsize", (char*) &dsmDsize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dsmInst", (char*) dsmInst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dsmNbytes", (char*) dsmNbytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dtp", (char*) dtp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dtp_debug_onoff", (char*) dtp_debug_onoff, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dtp_exit", (char*) dtp_exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dummyErrno", (char*) &dummyErrno, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dummyGetCpuIndex", (char*) dummyGetCpuIndex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dup", (char*) dup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dup2", (char*) dup2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "e", (char*) e, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eax", (char*) eax, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ebp", (char*) ebp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ebx", (char*) ebx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ecx", (char*) ecx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edi", (char*) edi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrErrorInjectStub", (char*) edrErrorInjectStub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrErrorPolicyHookRemove", (char*) edrErrorPolicyHookRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrFlagsGet", (char*) edrFlagsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrInitFatalPolicyHandler", (char*) edrInitFatalPolicyHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrInterruptFatalPolicyHandler", (char*) edrInterruptFatalPolicyHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrIsDebugMode", (char*) edrIsDebugMode, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrKernelFatalPolicyHandler", (char*) edrKernelFatalPolicyHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrPolicyHandlerHookAdd", (char*) edrPolicyHandlerHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrPolicyHandlerHookGet", (char*) edrPolicyHandlerHookGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrRtpFatalPolicyHandler", (char*) edrRtpFatalPolicyHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrStubInit", (char*) edrStubInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrSysDbgFlag", (char*) &edrSysDbgFlag, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "edrSystemDebugModeGet", (char*) edrSystemDebugModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrSystemDebugModeInit", (char*) edrSystemDebugModeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edrSystemDebugModeSet", (char*) edrSystemDebugModeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "edx", (char*) edx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eflags", (char*) eflags, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "elfArchInitHook", (char*) &elfArchInitHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "elfArchMdlLoadHook", (char*) &elfArchMdlLoadHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "elfArchReloc", (char*) elfArchReloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "elfArchSymProcessHook", (char*) &elfArchSymProcessHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "elfArchVerify", (char*) elfArchVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "emu387Func", (char*) &emu387Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "emuInitFunc", (char*) &emuInitFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "end8023AddressForm", (char*) end8023AddressForm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endDevName", (char*) endDevName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endDevTbl", (char*) &endDevTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "endEtherAddressForm", (char*) endEtherAddressForm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherCrc32BeGet", (char*) endEtherCrc32BeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherCrc32LeGet", (char*) endEtherCrc32LeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherHdrInit", (char*) endEtherHdrInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherPacketAddrGet", (char*) endEtherPacketAddrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherPacketDataGet", (char*) endEtherPacketDataGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFindByName", (char*) endFindByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFirstUnitFind", (char*) endFirstUnitFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFlagsClr", (char*) endFlagsClr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFlagsGet", (char*) endFlagsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFlagsSet", (char*) endFlagsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endLibInit", (char*) endLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endList", (char*) &endList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "endM2Free", (char*) endM2Free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endM2Init", (char*) endM2Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endM2Ioctl", (char*) endM2Ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endM2Packet", (char*) &endM2Packet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "endMibIfInit", (char*) endMibIfInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMultiLstCnt", (char*) endMultiLstCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMultiLstFirst", (char*) endMultiLstFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMultiLstNext", (char*) endMultiLstNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endObjFlagSet", (char*) endObjFlagSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endObjInit", (char*) endObjInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endObjectUnload", (char*) endObjectUnload, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endPollStatsInit", (char*) endPollStatsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endPoolClSize", (char*) &endPoolClSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "endPoolCreate", (char*) endPoolCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endPoolDestroy", (char*) endPoolDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endPoolJumboClSize", (char*) &endPoolJumboClSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "endPoolJumboCreate", (char*) endPoolJumboCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endRcvRtnCall", (char*) endRcvRtnCall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endTxSemGive", (char*) endTxSemGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endTxSemTake", (char*) endTxSemTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envGet", (char*) envGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envLibInit", (char*) envLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envLibSem", (char*) &envLibSem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "envLibSemId", (char*) &envLibSemId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "envPrivateCreate", (char*) envPrivateCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envPrivateDestroy", (char*) envPrivateDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envShow", (char*) envShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfCatDefSem", (char*) &erfCatDefSem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfCatEventQueues", (char*) &erfCatEventQueues, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfCategoriesAvailable", (char*) erfCategoriesAvailable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfCategoryAllocate", (char*) erfCategoryAllocate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfCategoryQueueCreate", (char*) erfCategoryQueueCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfDbCatSem", (char*) &erfDbCatSem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfDefaultEventQueue", (char*) &erfDefaultEventQueue, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfEventQueueSize", (char*) &erfEventQueueSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "erfEventRaise", (char*) erfEventRaise, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfEventTaskOptions", (char*) &erfEventTaskOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "erfEventTaskPriority", (char*) &erfEventTaskPriority, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "erfEventTaskStackSize", (char*) &erfEventTaskStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "erfHandlerDb", (char*) &erfHandlerDb, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfHandlerRegister", (char*) erfHandlerRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfHandlerUnregister", (char*) erfHandlerUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfLibInit", (char*) erfLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfLibInitialized", (char*) &erfLibInitialized, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "erfMaxNumCat", (char*) &erfMaxNumCat, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfMaxNumType", (char*) &erfMaxNumType, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfMaxNumUserCat", (char*) &erfMaxNumUserCat, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfMaxNumUserType", (char*) &erfMaxNumUserType, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfNumUserCatDef", (char*) &erfNumUserCatDef, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfNumUserTypeDef", (char*) &erfNumUserTypeDef, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "erfTypeAllocate", (char*) erfTypeAllocate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erfTypesAvailable", (char*) erfTypesAvailable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errno", (char*) &errno, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "errnoGet", (char*) errnoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errnoOfTaskGet", (char*) errnoOfTaskGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errnoOfTaskSet", (char*) errnoOfTaskSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errnoSet", (char*) errnoSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "esi", (char*) esi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "esp", (char*) esp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eth_test", (char*) eth_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherMultiAdd", (char*) etherMultiAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherMultiDel", (char*) etherMultiDel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherMultiGet", (char*) etherMultiGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherbroadcastaddr", (char*) &etherbroadcastaddr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "eventClear", (char*) eventClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventInit", (char*) eventInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventLibInit", (char*) eventLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventPointStubLibInit", (char*) eventPointStubLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventPointSwHandle", (char*) eventPointSwHandle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventPointSwStubConnect", (char*) eventPointSwStubConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventReceive", (char*) eventReceive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventRsrcSend", (char*) eventRsrcSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventRsrcShow", (char*) eventRsrcShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventSend", (char*) eventSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventStart", (char*) eventStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventTaskShow", (char*) eventTaskShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventTerminate", (char*) eventTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "evtAction", (char*) &evtAction, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excCallTbl", (char*) excCallTbl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excDoBell", (char*) &excDoBell, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excExcHandle", (char*) excExcHandle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excExcepHook", (char*) &excExcepHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "excGetExcCnt", (char*) excGetExcCnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excHookAdd", (char*) excHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excInit", (char*) excInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excIntHandle", (char*) excIntHandle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excIntStub", (char*) excIntStub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excJobAdd", (char*) excJobAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excMcaInfoShow", (char*) &excMcaInfoShow, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excOSMStack", (char*) &excOSMStack, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excOSMStackCurrent", (char*) &excOSMStackCurrent, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "excOSMTss", (char*) &excOSMTss, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excOSMTssCurrent", (char*) &excOSMTssCurrent, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "excOsmInit", (char*) excOsmInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excShowInit", (char*) excShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excStub", (char*) excStub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excVecInit", (char*) excVecInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exit", (char*) exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exp", (char*) exp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exp__E", (char*) exp__E, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "expm1", (char*) expm1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fabs", (char*) fabs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "facos", (char*) facos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fasin", (char*) fasin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fat16ClustValueGet", (char*) fat16ClustValueGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fat16ClustValueSet", (char*) fat16ClustValueSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fat16Debug", (char*) &fat16Debug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fat16VolMount", (char*) fat16VolMount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fatClugFac", (char*) &fatClugFac, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fatan", (char*) fatan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fatan2", (char*) fatan2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fcbrt", (char*) fcbrt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fceil", (char*) fceil, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fchmod", (char*) fchmod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fclose", (char*) fclose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fcntl", (char*) fcntl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fcntl_dup", (char*) fcntl_dup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fcos", (char*) fcos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fcosh", (char*) fcosh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fdClass", (char*) &fdClass, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "fdInvalidDrv", (char*) &fdInvalidDrv, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "fdatasync", (char*) fdatasync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fdopen", (char*) fdopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fdprintf", (char*) fdprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "feof", (char*) feof, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ferror", (char*) ferror, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fexp", (char*) fexp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffabs", (char*) ffabs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffloor", (char*) ffloor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fflush", (char*) fflush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffmod", (char*) ffmod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffsLsb", (char*) ffsLsb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffsMsb", (char*) ffsMsb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fgetc", (char*) fgetc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fgetpos", (char*) fgetpos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fgets", (char*) fgets, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fhypot", (char*) fhypot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fieldSzIncludeSign", (char*) &fieldSzIncludeSign, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "file_test", (char*) file_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fileno", (char*) fileno, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "finfinity", (char*) finfinity, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "finite", (char*) finite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioBaseLibInit", (char*) fioBaseLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioBufPrint", (char*) fioBufPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioBufPut", (char*) fioBufPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioFltInstall", (char*) fioFltInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioFormatV", (char*) fioFormatV, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioLibInit", (char*) fioLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioRdString", (char*) fioRdString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioRead", (char*) fioRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioScanV", (char*) fioScanV, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioSnBufPut", (char*) fioSnBufPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "firint", (char*) firint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "firound", (char*) firound, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "firstCmd", (char*) &firstCmd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "firstLoader", (char*) &firstLoader, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "flNvRam0Resources", (char*) &flNvRam0Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "flNvRam0Segments", (char*) &flNvRam0Segments, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "floatInit", (char*) floatInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flog", (char*) flog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flog10", (char*) flog10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flog2", (char*) flog2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "floor", (char*) floor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fmod", (char*) fmod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fopen", (char*) fopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fpCtlRegName", (char*) &fpCtlRegName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpRegName", (char*) &fpRegName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpTypeGet", (char*) fpTypeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fpXctlRegName", (char*) &fpXctlRegName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpathconf", (char*) fpathconf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fpow", (char*) fpow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppArchInit", (char*) fppArchInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppArchSwitchHook", (char*) fppArchSwitchHook, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppArchSwitchHookEnable", (char*) fppArchSwitchHookEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppArchTaskCreateInit", (char*) fppArchTaskCreateInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppClex", (char*) fppClex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppCtxCreate", (char*) fppCtxCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppCtxDelete", (char*) fppCtxDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppCtxToRegs", (char*) fppCtxToRegs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppCwGet", (char*) fppCwGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppCwSet", (char*) fppCwSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppDisable", (char*) fppDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppDtoDx", (char*) fppDtoDx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppDxtoD", (char*) fppDxtoD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppEnable", (char*) fppEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppFcw", (char*) &fppFcw, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fppFsw", (char*) &fppFsw, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fppNclex", (char*) fppNclex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppProbe", (char*) fppProbe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppProbeSup", (char*) fppProbeSup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppRegsToCtx", (char*) fppRegsToCtx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppRestore", (char*) fppRestore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppSave", (char*) fppSave, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppSwGet", (char*) fppSwGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppTaskRegsGet", (char*) fppTaskRegsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppTaskRegsSet", (char*) fppTaskRegsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppWait", (char*) fppWait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppXctxToRegs", (char*) fppXctxToRegs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppXregsToCtx", (char*) fppXregsToCtx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppXrestore", (char*) fppXrestore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppXsave", (char*) fppXsave, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fprintf", (char*) fprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fputc", (char*) fputc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fputs", (char*) fputs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fread", (char*) fread, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "free", (char*) free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "freopen", (char*) freopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "frexp", (char*) frexp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fround", (char*) fround, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsEventUtilLibInit", (char*) fsEventUtilLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsMonitorInit", (char*) fsMonitorInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsPathAddedEventRaise", (char*) fsPathAddedEventRaise, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsPathAddedEventSetup", (char*) fsPathAddedEventSetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsWaitForPath", (char*) fsWaitForPath, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fscanf", (char*) fscanf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fseek", (char*) fseek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsetpos", (char*) fsetpos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsin", (char*) fsin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsincos", (char*) fsincos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsinh", (char*) fsinh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmGetDriver", (char*) fsmGetDriver, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmGetVolume", (char*) fsmGetVolume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmInitialized", (char*) &fsmInitialized, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fsmNameInstall", (char*) fsmNameInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmNameMap", (char*) fsmNameMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmNameUninstall", (char*) fsmNameUninstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmProbeInstall", (char*) fsmProbeInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmProbeUninstall", (char*) fsmProbeUninstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmUnmountHookAdd", (char*) fsmUnmountHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmUnmountHookDelete", (char*) fsmUnmountHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsmUnmountHookRun", (char*) fsmUnmountHookRun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsqrt", (char*) fsqrt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fstat", (char*) fstat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fstatfs", (char*) fstatfs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fstatfs64", (char*) fstatfs64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsync", (char*) fsync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftan", (char*) ftan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftanh", (char*) ftanh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftell", (char*) ftell, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpCommand", (char*) ftpCommand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpCommandEnhanced", (char*) ftpCommandEnhanced, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpDataConnGet", (char*) ftpDataConnGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpDataConnInit", (char*) ftpDataConnInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpDataConnInitPassiveMode", (char*) ftpDataConnInitPassiveMode, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpHookup", (char*) ftpHookup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLibDebugOptionsSet", (char*) ftpLibDebugOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLibInit", (char*) ftpLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLogin", (char*) ftpLogin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLs", (char*) ftpLs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpReplyGet", (char*) ftpReplyGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpReplyGetEnhanced", (char*) ftpReplyGetEnhanced, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpReplyTimeout", (char*) &ftpReplyTimeout, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpTransientConfigGet", (char*) ftpTransientConfigGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpTransientConfigSet", (char*) ftpTransientConfigSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpTransientFatalInstall", (char*) ftpTransientFatalInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpVerbose", (char*) &ftpVerbose, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpXfer", (char*) ftpXfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftplDebug", (char*) &ftplDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplPasvModeDisable", (char*) &ftplPasvModeDisable, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplTransientMaxRetryCount", (char*) &ftplTransientMaxRetryCount, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplTransientRetryInterval", (char*) &ftplTransientRetryInterval, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftrunc", (char*) ftrunc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fwrite", (char*) fwrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gRHConfigDescriptor", (char*) &gRHConfigDescriptor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "gRHDeviceDescriptor", (char*) &gRHDeviceDescriptor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_AtaName", (char*) &g_AtaName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_BusNum", (char*) &g_BusNum, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_CanMsgID", (char*) &g_CanMsgID, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_ComBauds", (char*) &g_ComBauds, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_ComMsgID", (char*) &g_ComMsgID, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_Compat_NT", (char*) &g_Compat_NT, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_DevNum", (char*) &g_DevNum, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_EHCDControllerCount", (char*) &g_EHCDControllerCount, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_EHCDHandle", (char*) &g_EHCDHandle, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_ExtComAddr", (char*) &g_ExtComAddr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_ExtComName", (char*) &g_ExtComName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_FunNum", (char*) &g_FunNum, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_IoCntMsgID", (char*) &g_IoCntMsgID, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_ListAccessEvent", (char*) &g_ListAccessEvent, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_MassUsbName", (char*) &g_MassUsbName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_MscHaveMountedMsgID", (char*) &g_MscHaveMountedMsgID, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_NativeInfos", (char*) &g_NativeInfos, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_TxBuffer", (char*) &g_TxBuffer, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_USBDRequestFunctions", (char*) &g_USBDRequestFunctions, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_ataBuffer", (char*) &g_ataBuffer, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_can_id", (char*) &g_can_id, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_can_send_states", (char*) &g_can_send_states, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_com_baud", (char*) &g_com_baud, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_devices", (char*) &g_devices, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_dtp_debug", (char*) &g_dtp_debug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_pEHCDData", (char*) &g_pEHCDData, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_pUHCDData", (char*) &g_pUHCDData, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_pcican_debug", (char*) &g_pcican_debug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_received_counts", (char*) &g_received_counts, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_recv_err_counts", (char*) &g_recv_err_counts, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_sja1000s", (char*) &g_sja1000s, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_tran_err_counts", (char*) &g_tran_err_counts, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_transmit_counts", (char*) &g_transmit_counts, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_txBufferCount", (char*) &g_txBufferCount, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_usbHstFunctionList", (char*) &g_usbHstFunctionList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "geiRegister", (char*) geiRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "genPhyDevRegistration", (char*) &genPhyDevRegistration, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "genPhyRegister", (char*) genPhyRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getArg", (char*) getArg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getOptServ", (char*) getOptServ, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSymNames", (char*) getSymNames, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getc", (char*) getc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getchar", (char*) getchar, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getcwd", (char*) getcwd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getenv", (char*) getenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gethostname", (char*) gethostname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getlhostbyaddr", (char*) getlhostbyaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getlhostbyname", (char*) getlhostbyname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getopt", (char*) getopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getoptInit", (char*) getoptInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getopt_r", (char*) getopt_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getpeername", (char*) getpeername, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getpid", (char*) getpid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gets", (char*) gets, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getsockname", (char*) getsockname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getsockopt", (char*) getsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getw", (char*) getw, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getwd", (char*) getwd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "glbMpApicInterruptTable", (char*) &glbMpApicInterruptTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "glbMpApicIoBaseId", (char*) &glbMpApicIoBaseId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "glbMpApicNioint", (char*) &glbMpApicNioint, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "glbMpApicNloint", (char*) &glbMpApicNloint, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "globalBusCtrlID", (char*) &globalBusCtrlID, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "globalIchDrvCtrl", (char*) &globalIchDrvCtrl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "globalNoStackFill", (char*) &globalNoStackFill, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "gmtime", (char*) gmtime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gmtime_r", (char*) gmtime_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "go", (char*) go, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gopherHookAdd", (char*) gopherHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gopherWriteChar", (char*) gopherWriteChar, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gopherWriteScalar", (char*) gopherWriteScalar, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gpGlobalBus", (char*) &gpGlobalBus, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "h", (char*) h, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hHcDriver", (char*) &hHcDriver, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "handleContextGet", (char*) handleContextGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleContextGetBase", (char*) handleContextGetBase, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleContextSet", (char*) handleContextSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleInit", (char*) handleInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleShow", (char*) handleShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleShowConnect", (char*) handleShowConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleTerminate", (char*) handleTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleTypeGet", (char*) handleTypeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "handleVerify", (char*) handleVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hardWareInterFaceBusInit", (char*) hardWareInterFaceBusInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hardWareInterFaceInit", (char*) hardWareInterFaceInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashFuncIterScale", (char*) hashFuncIterScale, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashFuncModulo", (char*) hashFuncModulo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashFuncMultiply", (char*) hashFuncMultiply, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashKeyCmp", (char*) hashKeyCmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashKeyStrCmp", (char*) hashKeyStrCmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashLibInit", (char*) hashLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblCreate", (char*) hashTblCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblDelete", (char*) hashTblDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblDestroy", (char*) hashTblDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblEach", (char*) hashTblEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblFind", (char*) hashTblFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblInit", (char*) hashTblInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblPut", (char*) hashTblPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblRemove", (char*) hashTblRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblTerminate", (char*) hashTblTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hcfDeviceGet", (char*) hcfDeviceGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hcfDeviceList", (char*) &hcfDeviceList, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hcfDeviceNum", (char*) &hcfDeviceNum, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hdprintf", (char*) hdprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "help", (char*) help, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hookAddToHead", (char*) hookAddToHead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hookAddToTail", (char*) hookAddToTail, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hookDelete", (char*) hookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hookFind", (char*) hookFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostAdd", (char*) hostAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostDelete", (char*) hostDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostGetByAddr", (char*) hostGetByAddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostGetByName", (char*) hostGetByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostInitFlag", (char*) &hostInitFlag, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hostList", (char*) &hostList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "hostListSem", (char*) &hostListSem, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hostTblInit", (char*) hostTblInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSearchByAddr", (char*) hostTblSearchByAddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSearchByAddr2", (char*) hostTblSearchByAddr2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSearchByName", (char*) hostTblSearchByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSearchByName2", (char*) hostTblSearchByName2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSetup", (char*) hostTblSetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostentAlloc", (char*) hostentAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostentFree", (char*) hostentFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostnameSetup", (char*) hostnameSetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hrfsDiskFormat", (char*) hrfsDiskFormat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hrfsFmtRtn", (char*) &hrfsFmtRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hwMemAlloc", (char*) hwMemAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hwMemFree", (char*) hwMemFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hwMemLibInit", (char*) hwMemLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hwMemPool", (char*) &hwMemPool, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "hwMemPoolCreate", (char*) hwMemPoolCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hw_node", (char*) &hw_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hypot", (char*) hypot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i", (char*) i, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8042vxbRegister", (char*) i8042vxbRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8253DevResources", (char*) &i8253DevResources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "i8259Init", (char*) i8259Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntBoi", (char*) i8259IntBoi, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntBoiEem", (char*) i8259IntBoiEem, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntBoiSmm", (char*) i8259IntBoiSmm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntEoiMaster", (char*) i8259IntEoiMaster, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntEoiSlave", (char*) i8259IntEoiSlave, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntEoiSlaveNfnm", (char*) i8259IntEoiSlaveNfnm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntEoiSlaveSfnm", (char*) i8259IntEoiSlaveSfnm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i8259IntEoiSmm", (char*) i8259IntEoiSmm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iPciCan", (char*) iPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iPciIo", (char*) iPciIo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iam", (char*) iam, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaBlkRW", (char*) ichAtaBlkRW, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaCmd", (char*) ichAtaCmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaConfig", (char*) ichAtaConfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaConfigInit", (char*) ichAtaConfigInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaCtrlReset", (char*) ichAtaCtrlReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDevCreate", (char*) ichAtaDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDevIdentify", (char*) ichAtaDevIdentify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDmaModeNegotiate", (char*) ichAtaDmaModeNegotiate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDmaModeSet", (char*) ichAtaDmaModeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDmaRW", (char*) ichAtaDmaRW, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDmaToggle", (char*) ichAtaDmaToggle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDrv", (char*) ichAtaDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaDumptest", (char*) ichAtaDumptest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaGetCtrl", (char*) ichAtaGetCtrl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaInit", (char*) ichAtaInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaParamRead", (char*) ichAtaParamRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaPiInit", (char*) ichAtaPiInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaRW", (char*) ichAtaRW, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaRawio", (char*) ichAtaRawio, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaShow", (char*) ichAtaShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaShowInit", (char*) ichAtaShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaStatusChk", (char*) ichAtaStatusChk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaXbdDevCreate", (char*) ichAtaXbdDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtaXbdRawio", (char*) ichAtaXbdRawio, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiBytesPerSectorGet", (char*) ichAtapiBytesPerSectorGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiBytesPerTrackGet", (char*) ichAtapiBytesPerTrackGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCtrlMediumRemoval", (char*) ichAtapiCtrlMediumRemoval, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentCylinderCountGet", (char*) ichAtapiCurrentCylinderCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentHeadCountGet", (char*) ichAtapiCurrentHeadCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentMDmaModeGet", (char*) ichAtapiCurrentMDmaModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentPioModeGet", (char*) ichAtapiCurrentPioModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentRwModeGet", (char*) ichAtapiCurrentRwModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentSDmaModeGet", (char*) ichAtapiCurrentSDmaModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCurrentUDmaModeGet", (char*) ichAtapiCurrentUDmaModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiCylinderCountGet", (char*) ichAtapiCylinderCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiDriveSerialNumberGet", (char*) ichAtapiDriveSerialNumberGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiDriveTypeGet", (char*) ichAtapiDriveTypeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiFeatureEnabledGet", (char*) ichAtapiFeatureEnabledGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiFeatureSupportedGet", (char*) ichAtapiFeatureSupportedGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiFirmwareRevisionGet", (char*) ichAtapiFirmwareRevisionGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiHeadCountGet", (char*) ichAtapiHeadCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiInit", (char*) ichAtapiInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiIoctl", (char*) ichAtapiIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiMaxMDmaModeGet", (char*) ichAtapiMaxMDmaModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiMaxPioModeGet", (char*) ichAtapiMaxPioModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiMaxSDmaModeGet", (char*) ichAtapiMaxSDmaModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiMaxUDmaModeGet", (char*) ichAtapiMaxUDmaModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiModelNumberGet", (char*) ichAtapiModelNumberGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiPktCmd", (char*) ichAtapiPktCmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiPktCmdSend", (char*) ichAtapiPktCmdSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiRead10", (char*) ichAtapiRead10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiReadCapacity", (char*) ichAtapiReadCapacity, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiReadTocPmaAtip", (char*) ichAtapiReadTocPmaAtip, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiRemovMediaStatusNotifyVerGet", (char*) ichAtapiRemovMediaStatusNotifyVerGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiScan", (char*) ichAtapiScan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiSeek", (char*) ichAtapiSeek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiSetCDSpeed", (char*) ichAtapiSetCDSpeed, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiStartStopUnit", (char*) ichAtapiStartStopUnit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiStopPlayScan", (char*) ichAtapiStopPlayScan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiTestUnitRdy", (char*) ichAtapiTestUnitRdy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichAtapiVersionNumberGet", (char*) ichAtapiVersionNumberGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichIdeCtrlReset", (char*) ichIdeCtrlReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichIdeDrvInstalled", (char*) &ichIdeDrvInstalled, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ichInitAtaDmaEngine", (char*) ichInitAtaDmaEngine, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichPciIdeCtrlInit", (char*) ichPciIdeCtrlInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichStartAtaDmaEngine", (char*) ichStartAtaDmaEngine, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ichStopAtaDmaEngine", (char*) ichStopAtaDmaEngine, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrAdd", (char*) ifAddrAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrDelete", (char*) ifAddrDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrGet", (char*) ifAddrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrSet", (char*) ifAddrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAllRoutesDelete", (char*) ifAllRoutesDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifBroadcastGet", (char*) ifBroadcastGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifBroadcastSet", (char*) ifBroadcastSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifDstAddrGet", (char*) ifDstAddrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifDstAddrSet", (char*) ifDstAddrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifFlagChange", (char*) ifFlagChange, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifFlagGet", (char*) ifFlagGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifFlagSet", (char*) ifFlagSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexToIfName", (char*) ifIndexToIfName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifLibInit", (char*) ifLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMaskGet", (char*) ifMaskGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMaskSet", (char*) ifMaskSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMetricGet", (char*) ifMetricGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMetricSet", (char*) ifMetricSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifNameToIfIndex", (char*) ifNameToIfIndex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifProxyArpDisable", (char*) ifProxyArpDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifProxyArpEnable", (char*) ifProxyArpEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifRouteDelete", (char*) ifRouteDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifconfig", (char*) ifconfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_netof", (char*) in_netof, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "index", (char*) index, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_addr", (char*) inet_addr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_aton", (char*) inet_aton, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_lnaof", (char*) inet_lnaof, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_makeaddr", (char*) inet_makeaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_makeaddr_b", (char*) inet_makeaddr_b, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_netof", (char*) inet_netof, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_netof_string", (char*) inet_netof_string, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_network", (char*) inet_network, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_ntoa", (char*) inet_ntoa, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_ntoa_b", (char*) inet_ntoa_b, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_ntop", (char*) inet_ntop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_pton", (char*) inet_pton, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "infinity", (char*) infinity, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initApplLogger", (char*) initApplLogger, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "instParamModify_desc", (char*) &instParamModify_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intArchConnect", (char*) intArchConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intArchDisconnect", (char*) intArchDisconnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intBoiExit", (char*) intBoiExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCnt", (char*) &intCnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intConnect", (char*) intConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intContext", (char*) intContext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCount", (char*) intCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCpuLock", (char*) intCpuLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCpuMicroLock", (char*) intCpuMicroLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCpuMicroUnlock", (char*) intCpuMicroUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCpuUnlock", (char*) intCpuUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intDisable", (char*) intDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intDisconnect", (char*) intDisconnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intEOI", (char*) &intEOI, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intEnable", (char*) intEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intEnt", (char*) intEnt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intEoiGet", (char*) &intEoiGet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intExit", (char*) intExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intHandlerCreate", (char*) intHandlerCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intHandlerCreateI86", (char*) intHandlerCreateI86, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLevelSet", (char*) intLevelSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLock", (char*) intLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLockLevelGet", (char*) intLockLevelGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLockLevelSet", (char*) intLockLevelSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLockMask", (char*) &intLockMask, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intNest", (char*) &intNest, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intRegsLock", (char*) intRegsLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intRegsUnlock", (char*) intRegsUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intRestrict", (char*) intRestrict, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intStackEnable", (char*) intStackEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intUnlock", (char*) intUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVBRSet", (char*) intVBRSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecBaseGet", (char*) intVecBaseGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecBaseSet", (char*) intVecBaseSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecGet", (char*) intVecGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecGet2", (char*) intVecGet2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecSet", (char*) intVecSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecSet2", (char*) intVecSet2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecSetEnt", (char*) &intVecSetEnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intVecSetExit", (char*) &intVecSetExit, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intVecTableWriteProtect", (char*) intVecTableWriteProtect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "int_test", (char*) int_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioApicIntrBaseGet_desc", (char*) &ioApicIntrBaseGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicIntrDrvInitializedCount", (char*) &ioApicIntrDrvInitializedCount, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ioApicIntrIntDisable_desc", (char*) &ioApicIntrIntDisable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicIntrIntEnable_desc", (char*) &ioApicIntrIntEnable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicIntrIntLock_desc", (char*) &ioApicIntrIntLock_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicIntrIntUnlock_desc", (char*) &ioApicIntrIntUnlock_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicIntrVersionGet_desc", (char*) &ioApicIntrVersionGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicNumIoApics", (char*) &ioApicNumIoApics, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ioApicRed0_15", (char*) &ioApicRed0_15, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicRed16_23", (char*) &ioApicRed16_23, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioApicRedNumEntries", (char*) &ioApicRedNumEntries, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ioApicRedNumEntriesGet_desc", (char*) &ioApicRedNumEntriesGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioDefPath", (char*) &ioDefPath, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ioDefPathCat", (char*) ioDefPathCat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefPathGet", (char*) ioDefPathGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefPathSet", (char*) ioDefPathSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefPathSetInternal", (char*) ioDefPathSetInternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioFullFileNameGet", (char*) ioFullFileNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioGlobalStdGet", (char*) ioGlobalStdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioGlobalStdSet", (char*) ioGlobalStdSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioHelp", (char*) ioHelp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioMaxLinkLevels", (char*) &ioMaxLinkLevels, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioPxCreateOrOpen", (char*) ioPxCreateOrOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioTaskStdGet", (char*) ioTaskStdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioTaskStdSet", (char*) ioTaskStdSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioctl", (char*) ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosClose", (char*) iosClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosCreate", (char*) iosCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDelete", (char*) iosDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevAdd", (char*) iosDevAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevCheck", (char*) iosDevCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevDelCallback", (char*) iosDevDelCallback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevDelDrv", (char*) iosDevDelDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevDelete", (char*) iosDevDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevFind", (char*) iosDevFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevMatch", (char*) iosDevMatch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevReplace", (char*) iosDevReplace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevReplaceExt", (char*) iosDevReplaceExt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevResume", (char*) iosDevResume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevShow", (char*) iosDevShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevSuspend", (char*) iosDevSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvInit", (char*) iosDrvInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvInstall", (char*) iosDrvInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvIoctl", (char*) iosDrvIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvIoctlMemValSet", (char*) iosDrvIoctlMemValSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvRemove", (char*) iosDrvRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvShow", (char*) iosDrvShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDvList", (char*) &iosDvList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iosFdDevFind", (char*) iosFdDevFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdDrvValue", (char*) iosFdDrvValue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdEntryGet", (char*) iosFdEntryGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdEntryIoctl", (char*) iosFdEntryIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdEntryPool", (char*) &iosFdEntryPool, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosFdEntryReturn", (char*) iosFdEntryReturn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdEntrySet", (char*) iosFdEntrySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdFree", (char*) iosFdFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdMap", (char*) iosFdMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdMaxFiles", (char*) iosFdMaxFiles, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdNew", (char*) iosFdNew, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdSet", (char*) iosFdSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdShow", (char*) iosFdShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdTable", (char*) &iosFdTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iosFdTableLock", (char*) iosFdTableLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdTableUnlock", (char*) iosFdTableUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdValue", (char*) iosFdValue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosInit", (char*) iosInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosIoctl", (char*) iosIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosIoctlInternal", (char*) iosIoctlInternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosLibInitialized", (char*) &iosLibInitialized, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosLock", (char*) iosLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosMaxDrivers", (char*) &iosMaxDrivers, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iosMaxFiles", (char*) &iosMaxFiles, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iosNextDevGet", (char*) iosNextDevGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosNonRmvFdEntrySet", (char*) iosNonRmvFdEntrySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosOpen", (char*) iosOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosPathFdEntryIoctl", (char*) iosPathFdEntryIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosPathLibInit", (char*) iosPathLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosPse52Mode", (char*) &iosPse52Mode, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosPxLibInit", (char*) iosPxLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosPxLibInitialized", (char*) &iosPxLibInitialized, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosRead", (char*) iosRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRmvFdEntrySet", (char*) iosRmvFdEntrySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRmvLibInit", (char*) iosRmvLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpDefPathGet", (char*) iosRtpDefPathGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpDefPathSet", (char*) iosRtpDefPathSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpDevCloseOrInvalidate", (char*) iosRtpDevCloseOrInvalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdEntryMap", (char*) iosRtpFdEntryMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdInvalid", (char*) iosRtpFdInvalid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdReserve", (char*) iosRtpFdReserve, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdReserveCntrl", (char*) iosRtpFdReserveCntrl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdSetup", (char*) iosRtpFdSetup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdShow", (char*) iosRtpFdShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdTableGet", (char*) iosRtpFdTableGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdTableSizeGet", (char*) iosRtpFdTableSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdTblEntryGet", (char*) iosRtpFdTblEntryGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpFdUnmap2", (char*) iosRtpFdUnmap2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpIoTableSizeGet", (char*) iosRtpIoTableSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpIoTableSizeSet", (char*) iosRtpIoTableSizeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpLibInit", (char*) iosRtpLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRtpTableSizeSet", (char*) iosRtpTableSizeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosShowInit", (char*) iosShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosUnlock", (char*) iosUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosWrite", (char*) iosWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipAttach", (char*) ipAttach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipDetach", (char*) ipDetach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_inaddr_any", (char*) &ip_inaddr_any, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipc_node", (char*) &ipc_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcomNetTask", (char*) ipcomNetTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_accept", (char*) ipcom_accept, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_accept_usr", (char*) ipcom_accept_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_access", (char*) ipcom_access, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_allocate_fw_cache", (char*) ipcom_allocate_fw_cache, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_asctime_r_vxworks", (char*) ipcom_asctime_r_vxworks, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_add", (char*) ipcom_atomic_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_add_and_return", (char*) ipcom_atomic_add_and_return, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_dec", (char*) ipcom_atomic_dec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_get", (char*) ipcom_atomic_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_inc", (char*) ipcom_atomic_inc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_set", (char*) ipcom_atomic_set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_sub", (char*) ipcom_atomic_sub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_atomic_sub_and_return", (char*) ipcom_atomic_sub_and_return, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_chap_login", (char*) ipcom_auth_chap_login, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_default_hash_rtn", (char*) ipcom_auth_default_hash_rtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_hash", (char*) ipcom_auth_hash, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_hash_get", (char*) ipcom_auth_hash_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_hash_rtn_install", (char*) ipcom_auth_hash_rtn_install, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_login", (char*) ipcom_auth_login, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_old_and_unsecure_hash_rtn", (char*) ipcom_auth_old_and_unsecure_hash_rtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_useradd", (char*) ipcom_auth_useradd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_useradd_hash", (char*) ipcom_auth_useradd_hash, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_userdel", (char*) ipcom_auth_userdel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_userget", (char*) ipcom_auth_userget, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_auth_userlist", (char*) ipcom_auth_userlist, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_bind", (char*) ipcom_bind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_bind_usr", (char*) ipcom_bind_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_block_create", (char*) ipcom_block_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_block_delete", (char*) ipcom_block_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_block_post", (char*) ipcom_block_post, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_block_wait", (char*) ipcom_block_wait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cache_line_size", (char*) ipcom_cache_line_size, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_calloc", (char*) ipcom_calloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_chdir", (char*) ipcom_chdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_chmod", (char*) ipcom_chmod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_clearenv", (char*) ipcom_clearenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_closedir", (char*) ipcom_closedir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_closelog", (char*) ipcom_closelog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_cat", (char*) ipcom_cmd_cat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_cd", (char*) ipcom_cmd_cd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_cp", (char*) ipcom_cmd_cp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_date", (char*) ipcom_cmd_date, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_getenv", (char*) ipcom_cmd_getenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_if_caps_to_str", (char*) ipcom_cmd_if_caps_to_str, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_if_flags_to_str", (char*) ipcom_cmd_if_flags_to_str, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_key_to_str", (char*) ipcom_cmd_key_to_str, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_ls", (char*) ipcom_cmd_ls, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_mkdir", (char*) ipcom_cmd_mkdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_mv", (char*) ipcom_cmd_mv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_pwd", (char*) ipcom_cmd_pwd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_rm", (char*) ipcom_cmd_rm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_rmdir", (char*) ipcom_cmd_rmdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_setenv", (char*) ipcom_cmd_setenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_sockaddr_to_str", (char*) ipcom_cmd_sockaddr_to_str, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_str_to_key", (char*) ipcom_cmd_str_to_key, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_str_to_key2", (char*) ipcom_cmd_str_to_key2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_time", (char*) ipcom_cmd_time, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmd_uuencode", (char*) ipcom_cmd_uuencode, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cmsg_nxthdr", (char*) ipcom_cmsg_nxthdr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_conf_max_link_hdr_size", (char*) &ipcom_conf_max_link_hdr_size, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_conf_pkt_pool_buffer_alignment", (char*) &ipcom_conf_pkt_pool_buffer_alignment, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_conf_pkt_pool_buffer_extra_space", (char*) &ipcom_conf_pkt_pool_buffer_extra_space, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_configure", (char*) ipcom_configure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_configure_reserved_cpus", (char*) ipcom_configure_reserved_cpus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_connect", (char*) ipcom_connect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_connect_usr", (char*) ipcom_connect_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cpu_is_online", (char*) ipcom_cpu_is_online, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cpu_reserved_alloc", (char*) ipcom_cpu_reserved_alloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_cpu_reserved_free", (char*) ipcom_cpu_reserved_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_create", (char*) ipcom_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ctime_r_vxworks", (char*) ipcom_ctime_r_vxworks, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_dns", (char*) &ipcom_dns, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_dns_init_ok", (char*) &ipcom_dns_init_ok, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_drv_eth_create", (char*) ipcom_drv_eth_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_drv_eth_exit", (char*) ipcom_drv_eth_exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_drv_eth_init", (char*) ipcom_drv_eth_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_drv_eth_ip_attach", (char*) ipcom_drv_eth_ip_attach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_errno_get", (char*) ipcom_errno_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_errno_set", (char*) ipcom_errno_set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fclose", (char*) ipcom_fclose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fdopen", (char*) ipcom_fdopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_feof", (char*) ipcom_feof, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ferror", (char*) ipcom_ferror, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fflush", (char*) ipcom_fflush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fileclose", (char*) ipcom_fileclose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fileno", (char*) ipcom_fileno, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fileopen", (char*) ipcom_fileopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fileread", (char*) ipcom_fileread, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_filewrite", (char*) ipcom_filewrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fopen", (char*) ipcom_fopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_config_cache_size", (char*) ipcom_forwarder_config_cache_size, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_config_fw_max", (char*) ipcom_forwarder_config_fw_max, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_create_cf", (char*) ipcom_forwarder_create_cf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_current_core", (char*) ipcom_forwarder_current_core, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_fw_per_port", (char*) ipcom_forwarder_fw_per_port, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_get_fwcache_util_level_limit", (char*) ipcom_forwarder_get_fwcache_util_level_limit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_get_key_shift", (char*) ipcom_forwarder_get_key_shift, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_get_nonfw_stats", (char*) ipcom_forwarder_get_nonfw_stats, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_get_ports_for_interface", (char*) ipcom_forwarder_get_ports_for_interface, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_ipsec_sa_cache_size", (char*) &ipcom_forwarder_ipsec_sa_cache_size, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_forwarder_ipsec_single_output_queue", (char*) &ipcom_forwarder_ipsec_single_output_queue, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_forwarder_mtu", (char*) ipcom_forwarder_mtu, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_forwarder_startup_delay", (char*) ipcom_forwarder_startup_delay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fread", (char*) ipcom_fread, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_free", (char*) ipcom_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_freeaddrinfo", (char*) ipcom_freeaddrinfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_freeaddrinfo2", (char*) ipcom_freeaddrinfo2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_freeifaddrs", (char*) ipcom_freeifaddrs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fseek", (char*) ipcom_fseek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fstat", (char*) ipcom_fstat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ftell", (char*) ipcom_ftell, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_fwrite", (char*) ipcom_fwrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_get_cpuid", (char*) ipcom_get_cpuid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_get_ip_if_name", (char*) ipcom_get_ip_if_name, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getaddrinfo", (char*) ipcom_getaddrinfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getaddrinfo2", (char*) ipcom_getaddrinfo2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getcwd", (char*) ipcom_getcwd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getenv", (char*) ipcom_getenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getenv_as_int", (char*) ipcom_getenv_as_int, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getenv_r", (char*) ipcom_getenv_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gethostbyaddr", (char*) ipcom_gethostbyaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gethostbyaddr_r", (char*) ipcom_gethostbyaddr_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gethostbyaddrlocal", (char*) ipcom_gethostbyaddrlocal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gethostbyname", (char*) ipcom_gethostbyname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gethostbyname_r", (char*) ipcom_gethostbyname_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gethostbynamelocal", (char*) ipcom_gethostbynamelocal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getifaddrs", (char*) ipcom_getifaddrs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getlogmask_on", (char*) ipcom_getlogmask_on, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getnameinfo", (char*) ipcom_getnameinfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getnameinfo2", (char*) ipcom_getnameinfo2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getopt", (char*) ipcom_getopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getopt_clear", (char*) ipcom_getopt_clear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getopt_clear_r", (char*) ipcom_getopt_clear_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getopt_data", (char*) &ipcom_getopt_data, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_getopt_r", (char*) ipcom_getopt_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getpeername", (char*) ipcom_getpeername, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getpeername_usr", (char*) ipcom_getpeername_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getpid", (char*) ipcom_getpid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getprotobyname", (char*) ipcom_getprotobyname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getprotobynumber", (char*) ipcom_getprotobynumber, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getservbyname", (char*) ipcom_getservbyname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getservbyport", (char*) ipcom_getservbyport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getsockaddrbyaddr", (char*) ipcom_getsockaddrbyaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getsockaddrbyaddrname", (char*) ipcom_getsockaddrbyaddrname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getsockname", (char*) ipcom_getsockname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getsockname_usr", (char*) ipcom_getsockname_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getsockopt", (char*) ipcom_getsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_getsockopt_usr", (char*) ipcom_getsockopt_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_gettimeofday", (char*) ipcom_gettimeofday, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_h_errno", (char*) &ipcom_h_errno, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_hash_add", (char*) ipcom_hash_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_hash_delete", (char*) ipcom_hash_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_hash_for_each", (char*) ipcom_hash_for_each, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_hash_get", (char*) ipcom_hash_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_hash_new", (char*) ipcom_hash_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_hash_remove", (char*) ipcom_hash_remove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_hash_update", (char*) ipcom_hash_update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_heap_sort", (char*) ipcom_heap_sort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_attach", (char*) ipcom_if_attach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_attach_and_lock", (char*) ipcom_if_attach_and_lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_changelinkaddr", (char*) ipcom_if_changelinkaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_changemtu", (char*) ipcom_if_changemtu, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_changename", (char*) ipcom_if_changename, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_detach", (char*) ipcom_if_detach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_free", (char*) ipcom_if_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_freenameindex", (char*) ipcom_if_freenameindex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_indextoname", (char*) ipcom_if_indextoname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_malloc", (char*) ipcom_if_malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_nameindex", (char*) ipcom_if_nameindex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_nametoindex", (char*) ipcom_if_nametoindex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_if_nametonetif", (char*) ipcom_if_nametonetif, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ima_stack_task", (char*) ipcom_ima_stack_task, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_in_checksum", (char*) ipcom_in_checksum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_in_checksum_finish", (char*) ipcom_in_checksum_finish, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_in_checksum_memcpy", (char*) ipcom_in_checksum_memcpy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_in_checksum_update", (char*) ipcom_in_checksum_update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_inet_addr", (char*) ipcom_inet_addr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_inet_aton", (char*) ipcom_inet_aton, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_inet_ntoa", (char*) ipcom_inet_ntoa, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_inet_ntop", (char*) ipcom_inet_ntop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_inet_pton", (char*) ipcom_inet_pton, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_init_config_vars", (char*) ipcom_init_config_vars, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_initd", (char*) ipcom_initd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_interrupt_disable", (char*) ipcom_interrupt_disable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_interrupt_enable", (char*) ipcom_interrupt_enable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_close", (char*) ipcom_ipc_close, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_free", (char*) ipcom_ipc_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_install", (char*) ipcom_ipc_install, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_isopen", (char*) ipcom_ipc_isopen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_malloc", (char*) ipcom_ipc_malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_open", (char*) ipcom_ipc_open, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_receive", (char*) ipcom_ipc_receive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_send", (char*) ipcom_ipc_send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_size", (char*) ipcom_ipc_size, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipc_uninstall", (char*) ipcom_ipc_uninstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_datamsg", (char*) ipcom_ipd_datamsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_exit", (char*) ipcom_ipd_exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_init", (char*) ipcom_ipd_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_input", (char*) ipcom_ipd_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_input_process", (char*) ipcom_ipd_input_process, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_kill", (char*) ipcom_ipd_kill, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_products", (char*) &ipcom_ipd_products, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_ipd_read", (char*) ipcom_ipd_read, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_reconfigure", (char*) ipcom_ipd_reconfigure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_send", (char*) ipcom_ipd_send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_sendmsg", (char*) ipcom_ipd_sendmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipd_start", (char*) ipcom_ipd_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_ipproto_name", (char*) ipcom_ipproto_name, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_is_pid_valid", (char*) ipcom_is_pid_valid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_is_stack_task", (char*) ipcom_is_stack_task, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_init", (char*) ipcom_job_queue_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_pipe_schedule", (char*) ipcom_job_queue_pipe_schedule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_schedule", (char*) ipcom_job_queue_schedule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_schedule_singleton", (char*) ipcom_job_queue_schedule_singleton, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_schedule_singleton_delayed", (char*) ipcom_job_queue_schedule_singleton_delayed, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_singleton_delete", (char*) ipcom_job_queue_singleton_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_job_queue_singleton_new", (char*) ipcom_job_queue_singleton_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_first", (char*) ipcom_list_first, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_init", (char*) ipcom_list_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_insert_after", (char*) ipcom_list_insert_after, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_insert_before", (char*) ipcom_list_insert_before, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_insert_first", (char*) ipcom_list_insert_first, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_insert_last", (char*) ipcom_list_insert_last, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_last", (char*) ipcom_list_last, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_next", (char*) ipcom_list_next, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_prev", (char*) ipcom_list_prev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_remove", (char*) ipcom_list_remove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_list_unlink_head", (char*) ipcom_list_unlink_head, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_listen", (char*) ipcom_listen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_listen_usr", (char*) ipcom_listen_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_lseek", (char*) ipcom_lseek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_malloc", (char*) ipcom_malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mask_to_prefixlen", (char*) ipcom_mask_to_prefixlen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mb", (char*) ipcom_mb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mcmd_route", (char*) ipcom_mcmd_route, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_memory_pool_new", (char*) ipcom_memory_pool_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_microtime", (char*) ipcom_microtime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_millisleep", (char*) ipcom_millisleep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mkdir", (char*) ipcom_mkdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mutex_create", (char*) ipcom_mutex_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mutex_delete", (char*) ipcom_mutex_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mutex_lock", (char*) ipcom_mutex_lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_mutex_unlock", (char*) ipcom_mutex_unlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_null_pool_create", (char*) &ipcom_null_pool_create, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_num_configured_cpus", (char*) ipcom_num_configured_cpus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_num_online_cpus", (char*) ipcom_num_online_cpus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_once", (char*) ipcom_once, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_once_mutex", (char*) &ipcom_once_mutex, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_opendir", (char*) ipcom_opendir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_openlog", (char*) ipcom_openlog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_parse_argstr", (char*) ipcom_parse_argstr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_attr_init", (char*) ipcom_pipe_attr_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_free", (char*) ipcom_pipe_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_generic_create", (char*) ipcom_pipe_generic_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_job_queue_create", (char*) ipcom_pipe_job_queue_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_lockless_create", (char*) ipcom_pipe_lockless_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_new", (char*) ipcom_pipe_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_register_type", (char*) ipcom_pipe_register_type, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pipe_tv_zero", (char*) &ipcom_pipe_tv_zero, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_pkt_alloc_info", (char*) ipcom_pkt_alloc_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_copy_info", (char*) ipcom_pkt_copy_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_create", (char*) ipcom_pkt_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_free", (char*) ipcom_pkt_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_get_data", (char*) ipcom_pkt_get_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_get_info", (char*) ipcom_pkt_get_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_get_info_safe", (char*) ipcom_pkt_get_info_safe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_get_length", (char*) ipcom_pkt_get_length, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_hdrspace", (char*) ipcom_pkt_hdrspace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_input", (char*) ipcom_pkt_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_input_queue", (char*) ipcom_pkt_input_queue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_make_linear", (char*) ipcom_pkt_make_linear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_malloc", (char*) ipcom_pkt_malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_output_done", (char*) ipcom_pkt_output_done, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pkt_set_info", (char*) ipcom_pkt_set_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pktbuf_free", (char*) ipcom_pktbuf_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_port", (char*) &ipcom_port, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_port_pkt_hdr_extra_size", (char*) &ipcom_port_pkt_hdr_extra_size, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_pqueue_delete", (char*) ipcom_pqueue_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_for_each", (char*) ipcom_pqueue_for_each, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_get", (char*) ipcom_pqueue_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_get_next", (char*) ipcom_pqueue_get_next, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_insert", (char*) ipcom_pqueue_insert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_new", (char*) ipcom_pqueue_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_nop_store_index", (char*) ipcom_pqueue_nop_store_index, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_remove", (char*) ipcom_pqueue_remove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_remove_next", (char*) ipcom_pqueue_remove_next, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_pqueue_size", (char*) ipcom_pqueue_size, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_preempt_disable", (char*) ipcom_preempt_disable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_preempt_enable", (char*) ipcom_preempt_enable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_priority_map", (char*) &ipcom_priority_map, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_proc_acreate", (char*) ipcom_proc_acreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_attr_init", (char*) ipcom_proc_attr_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_cpu_affinity_clr", (char*) ipcom_proc_cpu_affinity_clr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_cpu_affinity_get", (char*) ipcom_proc_cpu_affinity_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_cpu_affinity_set", (char*) ipcom_proc_cpu_affinity_set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_cpu_affinity_set_all", (char*) ipcom_proc_cpu_affinity_set_all, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_create", (char*) ipcom_proc_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_exit", (char*) ipcom_proc_exit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_find", (char*) ipcom_proc_find, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_free", (char*) ipcom_proc_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_getprio", (char*) ipcom_proc_getprio, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_init", (char*) ipcom_proc_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_malloc", (char*) ipcom_proc_malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_self", (char*) ipcom_proc_self, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_setprio", (char*) ipcom_proc_setprio, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_vr_get", (char*) ipcom_proc_vr_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_vr_set", (char*) ipcom_proc_vr_set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proc_yield", (char*) ipcom_proc_yield, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_proxy_sys_var", (char*) ipcom_proxy_sys_var, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_rand", (char*) ipcom_rand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_random", (char*) ipcom_random, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_random_init", (char*) ipcom_random_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_random_seed_state", (char*) ipcom_random_seed_state, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_readdir", (char*) ipcom_readdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_realloc", (char*) ipcom_realloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_recv", (char*) ipcom_recv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_recv_usr", (char*) ipcom_recv_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_recvfrom", (char*) ipcom_recvfrom, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_recvfrom_usr", (char*) ipcom_recvfrom_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_recvmsg", (char*) ipcom_recvmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_recvmsg_usr", (char*) ipcom_recvmsg_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_register_dev_name_mapping", (char*) ipcom_register_dev_name_mapping, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_rename", (char*) ipcom_rename, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_reserve_fw_cpu", (char*) ipcom_reserve_fw_cpu, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_rewind", (char*) ipcom_rewind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_rmb", (char*) ipcom_rmb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_rmdir", (char*) ipcom_rmdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_add", (char*) ipcom_route_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_first_entry", (char*) ipcom_route_first_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_free_table", (char*) ipcom_route_free_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_init_subtree_mask", (char*) ipcom_route_init_subtree_mask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_key_cmp", (char*) ipcom_route_key_cmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_lookup", (char*) ipcom_route_lookup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_new_table", (char*) ipcom_route_new_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_next_entry", (char*) ipcom_route_next_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_remove", (char*) ipcom_route_remove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_walk_tree", (char*) ipcom_route_walk_tree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_route_walk_tree_backwards", (char*) ipcom_route_walk_tree_backwards, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_rtp_tcb_index_get_fd", (char*) ipcom_rtp_tcb_index_get_fd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_run_cmd", (char*) ipcom_run_cmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_create", (char*) ipcom_sem_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_delete", (char*) ipcom_sem_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_flush", (char*) ipcom_sem_flush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_getvalue", (char*) ipcom_sem_getvalue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_interrupt_flush", (char*) ipcom_sem_interrupt_flush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_interrupt_post", (char*) ipcom_sem_interrupt_post, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_post", (char*) ipcom_sem_post, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sem_wait", (char*) ipcom_sem_wait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_send", (char*) ipcom_send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_send_usr", (char*) ipcom_send_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sendmsg", (char*) ipcom_sendmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sendmsg_usr", (char*) ipcom_sendmsg_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sendto", (char*) ipcom_sendto, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sendto_usr", (char*) ipcom_sendto_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_add", (char*) ipcom_set_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_clone", (char*) ipcom_set_clone, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_contains", (char*) ipcom_set_contains, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_delete", (char*) ipcom_set_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_equal", (char*) ipcom_set_equal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_for_each", (char*) ipcom_set_for_each, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_intersection", (char*) ipcom_set_intersection, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_new", (char*) ipcom_set_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_remove", (char*) ipcom_set_remove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_remove_all", (char*) ipcom_set_remove_all, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_subtract", (char*) ipcom_set_subtract, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_set_union", (char*) ipcom_set_union, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setenv", (char*) ipcom_setenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setenv_as_int", (char*) ipcom_setenv_as_int, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sethostname", (char*) ipcom_sethostname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setlogfile", (char*) ipcom_setlogfile, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setlogmask_on", (char*) ipcom_setlogmask_on, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setlogudp", (char*) ipcom_setlogudp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setsockopt", (char*) ipcom_setsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_setsockopt_usr", (char*) ipcom_setsockopt_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_settimeofday", (char*) ipcom_settimeofday, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shell_add_cmd", (char*) ipcom_shell_add_cmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shell_cmd_head", (char*) &ipcom_shell_cmd_head, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_shell_find_cmd", (char*) ipcom_shell_find_cmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shell_find_cmd_hook", (char*) &ipcom_shell_find_cmd_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_shell_fread", (char*) ipcom_shell_fread, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shell_fwrite", (char*) ipcom_shell_fwrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shell_remove_cmd", (char*) ipcom_shell_remove_cmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shutdown", (char*) ipcom_shutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_shutdown_usr", (char*) ipcom_shutdown_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_add", (char*) ipcom_slab_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_alloc_from", (char*) ipcom_slab_alloc_from, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_alloc_try", (char*) ipcom_slab_alloc_try, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_free", (char*) ipcom_slab_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_get_objects_per_slab", (char*) ipcom_slab_get_objects_per_slab, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_memory_pool_list", (char*) &ipcom_slab_memory_pool_list, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_slab_new", (char*) ipcom_slab_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_slab_once", (char*) &ipcom_slab_once, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_sleep", (char*) ipcom_sleep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sockaddr_to_prefixlen", (char*) ipcom_sockaddr_to_prefixlen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socket", (char*) ipcom_socket, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socket_usr", (char*) ipcom_socket_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketclose", (char*) ipcom_socketclose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketclose_usr", (char*) ipcom_socketclose_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketioctl", (char*) ipcom_socketioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketioctl_usr", (char*) ipcom_socketioctl_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketread", (char*) ipcom_socketread, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketread_usr", (char*) ipcom_socketread_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketselect", (char*) ipcom_socketselect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketselect_usr", (char*) ipcom_socketselect_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketwrite", (char*) ipcom_socketwrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketwrite_usr", (char*) ipcom_socketwrite_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketwritev", (char*) ipcom_socketwritev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_socketwritev_usr", (char*) ipcom_socketwritev_usr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_spinlock_create", (char*) ipcom_spinlock_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_spinlock_delete", (char*) ipcom_spinlock_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_spinlock_lock", (char*) ipcom_spinlock_lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_spinlock_unlock", (char*) ipcom_spinlock_unlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_srand", (char*) ipcom_srand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_srandom", (char*) ipcom_srandom, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_stackd_init", (char*) ipcom_stackd_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_start", (char*) ipcom_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_stat", (char*) ipcom_stat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_stderr", (char*) ipcom_stderr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_stdin", (char*) ipcom_stdin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_stdout", (char*) ipcom_stdout, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_str_in_list", (char*) ipcom_str_in_list, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_strcasecmp", (char*) ipcom_strcasecmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_strerror", (char*) ipcom_strerror, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_strerror_r", (char*) ipcom_strerror_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_strncasecmp", (char*) ipcom_strncasecmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysctl", (char*) ipcom_sysctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_syslog", (char*) ipcom_syslog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_syslog_facility_names", (char*) &ipcom_syslog_facility_names, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_syslog_priority_names", (char*) &ipcom_syslog_priority_names, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_syslogd_init", (char*) ipcom_syslogd_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_ext_setv", (char*) ipcom_sysvar_ext_setv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_for_each", (char*) ipcom_sysvar_for_each, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_get", (char*) ipcom_sysvar_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_get0", (char*) ipcom_sysvar_get0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_get_as_int", (char*) ipcom_sysvar_get_as_int, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_get_as_int0", (char*) ipcom_sysvar_get_as_int0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_get_descriptive_int0", (char*) ipcom_sysvar_get_descriptive_int0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_getvr", (char*) ipcom_sysvar_getvr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_set", (char*) ipcom_sysvar_set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_set0", (char*) ipcom_sysvar_set0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_set_tree", (char*) ipcom_sysvar_set_tree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_setv", (char*) ipcom_sysvar_setv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_sysvar_unset", (char*) ipcom_sysvar_unset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_tmo_cancel", (char*) ipcom_tmo_cancel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_tmo_get", (char*) ipcom_tmo_get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_tmo_request", (char*) ipcom_tmo_request, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_tmo_reset", (char*) ipcom_tmo_reset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_umask", (char*) ipcom_umask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_unlink", (char*) ipcom_unlink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_unsetenv", (char*) ipcom_unsetenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_usr_create", (char*) ipcom_usr_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_version", (char*) &ipcom_version, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipcom_vsyslog", (char*) ipcom_vsyslog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_vxshell_add_cmd", (char*) ipcom_vxshell_add_cmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_vxshell_add_cmd_hook", (char*) &ipcom_vxshell_add_cmd_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipcom_vxworks_pkt_pool_hdr_ctor", (char*) ipcom_vxworks_pkt_pool_hdr_ctor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_vxworks_proc_free", (char*) ipcom_vxworks_proc_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_vxworks_rtp_del_hook_add", (char*) ipcom_vxworks_rtp_del_hook_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_vxworks_task_del_hook", (char*) ipcom_vxworks_task_del_hook, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wait_queue_add_current_proc", (char*) ipcom_wait_queue_add_current_proc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wait_queue_init", (char*) ipcom_wait_queue_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wait_queue_is_empty", (char*) ipcom_wait_queue_is_empty, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wait_queue_wakeup_all_procs", (char*) ipcom_wait_queue_wakeup_all_procs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wait_queue_wakeup_one_proc", (char*) ipcom_wait_queue_wakeup_one_proc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_windnet_socketwritev", (char*) ipcom_windnet_socketwritev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_windnet_socklib_init", (char*) ipcom_windnet_socklib_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_windnet_socklib_init_cb", (char*) ipcom_windnet_socklib_init_cb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_windnet_socklib_sock_size", (char*) ipcom_windnet_socklib_sock_size, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_windnet_socklib_socket_free", (char*) ipcom_windnet_socklib_socket_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_windnet_socklib_socket_init", (char*) ipcom_windnet_socklib_socket_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wmb", (char*) ipcom_wmb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wv_event_2", (char*) ipcom_wv_event_2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wv_marker_1", (char*) ipcom_wv_marker_1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipcom_wv_marker_2", (char*) ipcom_wv_marker_2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_authenticate", (char*) ipftps_authenticate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_conf_sysvar", (char*) &ipftps_conf_sysvar, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipftps_configure", (char*) ipftps_configure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_create", (char*) ipftps_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_main", (char*) ipftps_main, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_session", (char*) ipftps_session, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_start", (char*) ipftps_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipftps_version", (char*) ipftps_version, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipmcrypto_MD5_Final", (char*) ipmcrypto_MD5_Final, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipmcrypto_MD5_Init", (char*) ipmcrypto_MD5_Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipmcrypto_MD5_Update", (char*) ipmcrypto_MD5_Update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipmcrypto_md5_calculate", (char*) ipmcrypto_md5_calculate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet", (char*) &ipnet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_arp_ioctl", (char*) ipnet_arp_ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_arp_request", (char*) ipnet_arp_request, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_arp_set_state", (char*) ipnet_arp_set_state, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_bit_array_clr", (char*) ipnet_bit_array_clr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_bit_array_test_and_set", (char*) ipnet_bit_array_test_and_set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_bool_map", (char*) &ipnet_bool_map, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_boot_config", (char*) ipnet_boot_config, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_cmd_if_type_to_str", (char*) ipnet_cmd_if_type_to_str, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_cmd_ifconfig", (char*) ipnet_cmd_ifconfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_cmd_ifconfig_hook", (char*) &ipnet_cmd_ifconfig_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipnet_cmd_init_addrs", (char*) ipnet_cmd_init_addrs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_cmd_msec_since", (char*) ipnet_cmd_msec_since, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_cmd_qc_hook", (char*) &ipnet_cmd_qc_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipnet_cmd_route_hook", (char*) &ipnet_cmd_route_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipnet_cmd_rt_flags_to_str", (char*) ipnet_cmd_rt_flags_to_str, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_cmd_rt_flags_to_str_short", (char*) ipnet_cmd_rt_flags_to_str_short, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_conf_boot_cmd", (char*) &ipnet_conf_boot_cmd, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_cache_bufsiz", (char*) &ipnet_conf_cache_bufsiz, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipnet_conf_inq_max", (char*) &ipnet_conf_inq_max, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_interfaces", (char*) &ipnet_conf_interfaces, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_ip4_min_mtu", (char*) &ipnet_conf_ip4_min_mtu, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_link_layer", (char*) &ipnet_conf_link_layer, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_max_dgram_frag_list_len", (char*) &ipnet_conf_max_dgram_frag_list_len, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_max_reassembly_list_len", (char*) &ipnet_conf_max_reassembly_list_len, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_max_sockets", (char*) &ipnet_conf_max_sockets, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_memory_limit", (char*) &ipnet_conf_memory_limit, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_reassembly_timeout", (char*) &ipnet_conf_reassembly_timeout, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_conf_sysvar_ext", (char*) &ipnet_conf_sysvar_ext, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_configure", (char*) ipnet_configure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_create", (char*) ipnet_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_create_reassembled_packet", (char*) ipnet_create_reassembled_packet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ctrl", (char*) ipnet_ctrl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ctrl_sig", (char*) ipnet_ctrl_sig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_do_close", (char*) ipnet_do_close, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_eth_add_hdr", (char*) ipnet_eth_add_hdr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_eth_if_init", (char*) ipnet_eth_if_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_eth_update_mib2_lastchange", (char*) ipnet_eth_update_mib2_lastchange, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_finish_transport_checksum", (char*) ipnet_finish_transport_checksum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_flags", (char*) &ipnet_flags, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_fragment_packet", (char*) ipnet_fragment_packet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_get_sock", (char*) ipnet_get_sock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_has_priv", (char*) ipnet_has_priv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_icmp4_dst_create_rt", (char*) ipnet_icmp4_dst_create_rt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_icmp4_param_init", (char*) ipnet_icmp4_param_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_icmp4_send", (char*) ipnet_icmp4_send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_can_detach", (char*) ipnet_if_can_detach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_clean", (char*) ipnet_if_clean, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_clean_ppp_peer", (char*) ipnet_if_clean_ppp_peer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_clean_snd_queue", (char*) ipnet_if_clean_snd_queue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_detach", (char*) ipnet_if_detach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_drv_ioctl", (char*) ipnet_if_drv_ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_drv_output", (char*) ipnet_if_drv_output, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_free", (char*) ipnet_if_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_get_index_array", (char*) ipnet_if_get_index_array, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_indextonetif", (char*) ipnet_if_indextonetif, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_init", (char*) ipnet_if_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_init_ppp_peer", (char*) ipnet_if_init_ppp_peer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_link_ioctl", (char*) ipnet_if_link_ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_nametonetif", (char*) ipnet_if_nametonetif, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_output", (char*) ipnet_if_output, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_set_ipv4_ppp_peer", (char*) ipnet_if_set_ipv4_ppp_peer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_if_to_sockaddr_dl", (char*) ipnet_if_to_sockaddr_dl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ifconfig_if_change_state", (char*) ipnet_ifconfig_if_change_state, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_igmpv3_report_change", (char*) ipnet_igmpv3_report_change, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_increase_hdr_space", (char*) ipnet_increase_hdr_space, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ioctl_move_if_rt_to_vr", (char*) ipnet_ioctl_move_if_rt_to_vr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_add_addr", (char*) ipnet_ip4_add_addr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_add_addr2", (char*) ipnet_ip4_add_addr2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_add_route_table", (char*) ipnet_ip4_add_route_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_addr_to_sockaddr", (char*) ipnet_ip4_addr_to_sockaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_change_addr_mask", (char*) ipnet_ip4_change_addr_mask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_configure_route_table", (char*) ipnet_ip4_configure_route_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_get_addr_entry", (char*) ipnet_ip4_get_addr_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_get_addr_type", (char*) ipnet_ip4_get_addr_type, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_get_addr_type2", (char*) ipnet_ip4_get_addr_type2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_get_mss", (char*) ipnet_ip4_get_mss, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_get_src_addr", (char*) ipnet_ip4_get_src_addr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_init", (char*) ipnet_ip4_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_input", (char*) ipnet_ip4_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_insert_addr_cache", (char*) ipnet_ip4_insert_addr_cache, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_is_part_of_same_pkt", (char*) ipnet_ip4_is_part_of_same_pkt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_kioevent", (char*) ipnet_ip4_kioevent, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_lladdr_conflict", (char*) ipnet_ip4_lladdr_conflict, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_netif_get_subbrd", (char*) ipnet_ip4_netif_get_subbrd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_output", (char*) ipnet_ip4_output, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_remove_addr", (char*) ipnet_ip4_remove_addr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_remove_addr_cache", (char*) ipnet_ip4_remove_addr_cache, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_rfc1256_mode_update", (char*) ipnet_ip4_rfc1256_mode_update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_schedule_host_unreachable", (char*) ipnet_ip4_schedule_host_unreachable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ip4_sendto", (char*) ipnet_ip4_sendto, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_is_loopback", (char*) ipnet_is_loopback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_is_sock_exceptional", (char*) ipnet_is_sock_exceptional, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_is_sock_readable", (char*) ipnet_is_sock_readable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_is_sock_writable", (char*) ipnet_is_sock_writable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_is_stack_task", (char*) ipnet_is_stack_task, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_kioevent", (char*) ipnet_kioevent, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_loopback_attach", (char*) ipnet_loopback_attach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_loopback_get_netif", (char*) ipnet_loopback_get_netif, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_loopback_if_init", (char*) ipnet_loopback_if_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_build_if_filter", (char*) ipnet_mcast_build_if_filter, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_build_source_change_report", (char*) ipnet_mcast_build_source_change_report, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_clear", (char*) ipnet_mcast_clear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_free", (char*) ipnet_mcast_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_init", (char*) ipnet_mcast_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_report_finish", (char*) ipnet_mcast_report_finish, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_schedule_membership_report", (char*) ipnet_mcast_schedule_membership_report, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_mcast_time_to_msec", (char*) ipnet_mcast_time_to_msec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_msec_now", (char*) ipnet_msec_now, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_neigh_free_all_pending", (char*) ipnet_neigh_free_all_pending, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_neigh_init", (char*) ipnet_neigh_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_neigh_queue_until_resolved", (char*) ipnet_neigh_queue_until_resolved, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_neigh_send_all_pending", (char*) ipnet_neigh_send_all_pending, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_neigh_set_state", (char*) ipnet_neigh_set_state, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_neigh_timeout", (char*) ipnet_neigh_timeout, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_netif_change_flags", (char*) ipnet_netif_change_flags, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_next_ephemeral_port", (char*) ipnet_next_ephemeral_port, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_packet_getsockopt", (char*) ipnet_packet_getsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_packet_input", (char*) ipnet_packet_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_packet_setsockopt", (char*) ipnet_packet_setsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pcap_ioctl", (char*) ipnet_pcap_ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ping_stat_init", (char*) ipnet_ping_stat_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ping_stat_receive", (char*) ipnet_ping_stat_receive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ping_stat_report", (char*) ipnet_ping_stat_report, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ping_stat_transmit", (char*) ipnet_ping_stat_transmit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pipe_create", (char*) ipnet_pipe_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_clone", (char*) ipnet_pkt_clone, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_input", (char*) ipnet_pkt_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_pool_hdr_count_hint", (char*) ipnet_pkt_pool_hdr_count_hint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_pool_hdr_ctor_func", (char*) &ipnet_pkt_pool_hdr_ctor_func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_pkt_pool_init", (char*) ipnet_pkt_pool_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_pool_slab_desc", (char*) &ipnet_pkt_pool_slab_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipnet_pkt_queue_delete", (char*) ipnet_pkt_queue_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_queue_fifo_template", (char*) ipnet_pkt_queue_fifo_template, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_queue_init", (char*) ipnet_pkt_queue_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_pkt_queue_new", (char*) ipnet_pkt_queue_new, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_ppp_if_init", (char*) ipnet_ppp_if_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_qc_unif_config_hook", (char*) &ipnet_qc_unif_config_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipnet_queue_received_packet", (char*) ipnet_queue_received_packet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_raw_input", (char*) ipnet_raw_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_reassembly", (char*) ipnet_reassembly, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_release_sock", (char*) ipnet_release_sock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_resume_stack", (char*) ipnet_resume_stack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_add", (char*) ipnet_route_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_add_cloned_rt", (char*) ipnet_route_add_cloned_rt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_add_table", (char*) ipnet_route_add_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_apply_mask", (char*) ipnet_route_apply_mask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_cache_invalidate", (char*) ipnet_route_cache_invalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_create_llinfo_entry", (char*) ipnet_route_create_llinfo_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_create_mask", (char*) ipnet_route_create_mask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_delete", (char*) ipnet_route_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_delete2", (char*) ipnet_route_delete2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_delete_name", (char*) ipnet_route_delete_name, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_delete_table", (char*) ipnet_route_delete_table, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_delete_vr", (char*) ipnet_route_delete_vr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_first_entry", (char*) ipnet_route_first_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_for_each_data_init", (char*) ipnet_route_for_each_data_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_get_name", (char*) ipnet_route_get_name, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_get_rtab", (char*) ipnet_route_get_rtab, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_get_table_ids", (char*) ipnet_route_get_table_ids, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_has_changed", (char*) ipnet_route_has_changed, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_has_expired", (char*) ipnet_route_has_expired, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_is_virtual_router_valid", (char*) ipnet_route_is_virtual_router_valid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_key_cmp", (char*) ipnet_route_key_cmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_key_to_sockaddr", (char*) ipnet_route_key_to_sockaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_lock", (char*) ipnet_route_lock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_lookup", (char*) ipnet_route_lookup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_lookup_ecmp", (char*) ipnet_route_lookup_ecmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_lookup_ip4_dont_route", (char*) ipnet_route_lookup_ip4_dont_route, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_next_entry", (char*) ipnet_route_next_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_notify_func", (char*) ipnet_route_notify_func, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_policy_get_rule_chain", (char*) ipnet_route_policy_get_rule_chain, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_policy_ioctl", (char*) ipnet_route_policy_ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_raw_lookup", (char*) ipnet_route_raw_lookup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_raw_lookup2", (char*) ipnet_route_raw_lookup2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_remove_all", (char*) ipnet_route_remove_all, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_remove_all_cb_for_each_entry", (char*) ipnet_route_remove_all_cb_for_each_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_rotate_gateways", (char*) ipnet_route_rotate_gateways, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_set_lifetime", (char*) ipnet_route_set_lifetime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_set_name", (char*) ipnet_route_set_name, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_set_rtab", (char*) ipnet_route_set_rtab, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_sockaddr_to_key", (char*) ipnet_route_sockaddr_to_key, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_unlock", (char*) ipnet_route_unlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_vr_and_table_from_name", (char*) ipnet_route_vr_and_table_from_name, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_route_walk_tree", (char*) ipnet_route_walk_tree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_addr_add", (char*) ipnet_routesock_addr_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_addr_delete", (char*) ipnet_routesock_addr_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_if_announce", (char*) ipnet_routesock_if_announce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_if_change", (char*) ipnet_routesock_if_change, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_rt_add", (char*) ipnet_routesock_rt_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_rt_change", (char*) ipnet_routesock_rt_change, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_rt_delete", (char*) ipnet_routesock_rt_delete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_rt_miss", (char*) ipnet_routesock_rt_miss, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_rt_redirect", (char*) ipnet_routesock_rt_redirect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_routesock_rt_resolve", (char*) ipnet_routesock_rt_resolve, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_schedule_pkt_report", (char*) ipnet_schedule_pkt_report, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sec_now", (char*) ipnet_sec_now, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sig_free", (char*) ipnet_sig_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_add_to_rx_cache", (char*) ipnet_sock_add_to_rx_cache, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_alloc_private_data", (char*) ipnet_sock_alloc_private_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_bind", (char*) ipnet_sock_bind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_bind_addr_removed", (char*) ipnet_sock_bind_addr_removed, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_bind_to_port", (char*) ipnet_sock_bind_to_port, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_change_addr_entry", (char*) ipnet_sock_change_addr_entry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_create_lookup_tables", (char*) ipnet_sock_create_lookup_tables, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_data_avail", (char*) ipnet_sock_data_avail, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_drop_all_multicast_memberships", (char*) ipnet_sock_drop_all_multicast_memberships, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_free", (char*) ipnet_sock_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_get_bound_socket_size", (char*) ipnet_sock_get_bound_socket_size, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_get_ops", (char*) ipnet_sock_get_ops, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_get_route", (char*) ipnet_sock_get_route, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_has_waiting_writers", (char*) ipnet_sock_has_waiting_writers, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_ip4_get_mcast_data", (char*) ipnet_sock_ip4_get_mcast_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_ip4_get_ops", (char*) ipnet_sock_ip4_get_ops, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_ip4_lookup", (char*) ipnet_sock_ip4_lookup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_ip4_mcast_delete_data", (char*) ipnet_sock_ip4_mcast_delete_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_ip4_register", (char*) ipnet_sock_ip4_register, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_packet_register", (char*) ipnet_sock_packet_register, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_pkt_drain", (char*) ipnet_sock_pkt_drain, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_register_ops", (char*) ipnet_sock_register_ops, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_route_register", (char*) ipnet_sock_route_register, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_rx_cache_invalidate", (char*) ipnet_sock_rx_cache_invalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_set_reachable", (char*) ipnet_sock_set_reachable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_set_unreachable", (char*) ipnet_sock_set_unreachable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_tcp_register", (char*) ipnet_sock_tcp_register, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_udp_register", (char*) ipnet_sock_udp_register, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_unbind", (char*) ipnet_sock_unbind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_unconnect", (char*) ipnet_sock_unconnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sock_update_reuse", (char*) ipnet_sock_update_reuse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sockopt_ip4_addr_to_netif", (char*) ipnet_sockopt_ip4_addr_to_netif, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_softirq_init", (char*) ipnet_softirq_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_softirq_run", (char*) ipnet_softirq_run, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_softirq_schedule", (char*) ipnet_softirq_schedule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_start", (char*) ipnet_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_stats_tcp_established", (char*) ipnet_stats_tcp_established, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_suspend_stack", (char*) ipnet_suspend_stack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_accept", (char*) ipnet_sys_accept, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_bind", (char*) ipnet_sys_bind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_connect", (char*) ipnet_sys_connect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_get_ancillary_data", (char*) ipnet_sys_get_ancillary_data, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_getname", (char*) ipnet_sys_getname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_getsockopt", (char*) ipnet_sys_getsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_attach", (char*) ipnet_sys_if_attach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_changelinkaddr", (char*) ipnet_sys_if_changelinkaddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_changemtu", (char*) ipnet_sys_if_changemtu, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_changename", (char*) ipnet_sys_if_changename, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_detach", (char*) ipnet_sys_if_detach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_free", (char*) ipnet_sys_if_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_indexname", (char*) ipnet_sys_if_indexname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_malloc", (char*) ipnet_sys_if_malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_if_nametonetif", (char*) ipnet_sys_if_nametonetif, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_listen", (char*) ipnet_sys_listen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_poll", (char*) ipnet_sys_poll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_poll_async", (char*) ipnet_sys_poll_async, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_poll_done", (char*) ipnet_sys_poll_done, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_sendmsg", (char*) ipnet_sys_sendmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_setsockopt", (char*) ipnet_sys_setsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_shutdown", (char*) ipnet_sys_shutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_socket", (char*) ipnet_sys_socket, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_socketclose", (char*) ipnet_sys_socketclose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_socketioctl", (char*) ipnet_sys_socketioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sys_sysctl", (char*) ipnet_sys_sysctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sysctl_create_ifinfo", (char*) ipnet_sysctl_create_ifinfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sysctl_if_add_addrs_one", (char*) ipnet_sysctl_if_add_addrs_one, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sysvar_netif_get_as_int", (char*) ipnet_sysvar_netif_get_as_int, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_sysvar_netif_get_as_int_ex", (char*) ipnet_sysvar_netif_get_as_int_ex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_timeout_cancel", (char*) ipnet_timeout_cancel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_timeout_msec_until", (char*) ipnet_timeout_msec_until, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_timeout_schedule", (char*) ipnet_timeout_schedule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_timeval_to_msec", (char*) ipnet_timeval_to_msec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_udp_input", (char*) ipnet_udp_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_get_ops", (char*) ipnet_usr_sock_get_ops, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_get_pipe", (char*) ipnet_usr_sock_get_pipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_get_response_pipe", (char*) ipnet_usr_sock_get_response_pipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_get_route_cache_id", (char*) ipnet_usr_sock_get_route_cache_id, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_init", (char*) ipnet_usr_sock_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_init_sig", (char*) ipnet_usr_sock_init_sig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_recvmsg", (char*) ipnet_usr_sock_recvmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_usr_sock_wait_until_writable", (char*) ipnet_usr_sock_wait_until_writable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipnet_version", (char*) ipnet_version, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipstack_ifconfig_print_info", (char*) ipstack_ifconfig_print_info, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp", (char*) &iptcp, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iptcp_accept", (char*) iptcp_accept, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_change_state_global", (char*) iptcp_change_state_global, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_close", (char*) iptcp_close, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_conf_default_backlog", (char*) &iptcp_conf_default_backlog, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iptcp_configure", (char*) iptcp_configure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_connect", (char*) iptcp_connect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_create", (char*) iptcp_create, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_drop_connection", (char*) iptcp_drop_connection, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_get_rto", (char*) iptcp_get_rto, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_get_state", (char*) iptcp_get_state, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_getsockopt", (char*) iptcp_getsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_icmp4_report", (char*) iptcp_icmp4_report, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_input", (char*) iptcp_input, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_ioctl", (char*) iptcp_ioctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_listen", (char*) iptcp_listen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_pkt_drain", (char*) iptcp_pkt_drain, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_send", (char*) iptcp_send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_send_reset", (char*) iptcp_send_reset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_setsockopt", (char*) iptcp_setsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_shutdown", (char*) iptcp_shutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_sock_free", (char*) iptcp_sock_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_sock_init", (char*) iptcp_sock_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_start", (char*) iptcp_start, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_usr_recv", (char*) iptcp_usr_recv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_version", (char*) iptcp_version, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptcp_window_update", (char*) iptcp_window_update, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "irint", (char*) irint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iround", (char*) iround, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "irq_isr", (char*) irq_isr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isalnum", (char*) isalnum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isalpha", (char*) isalpha, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isatty", (char*) isatty, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iscntrl", (char*) iscntrl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isdigit", (char*) isdigit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isgraph", (char*) isgraph, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "islower", (char*) islower, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isprint", (char*) isprint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ispunct", (char*) ispunct, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isrDeferIsrReroute", (char*) isrDeferIsrReroute, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isrDeferJobAdd", (char*) isrDeferJobAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isrDeferLibInit", (char*) isrDeferLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isrDeferQueueGet", (char*) isrDeferQueueGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isrIdCurrent", (char*) &isrIdCurrent, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "isrJobPool", (char*) &isrJobPool, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "isspace", (char*) isspace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isupper", (char*) isupper, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isxdigit", (char*) isxdigit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobAdd", (char*) jobAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobExcAdd", (char*) jobExcAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobLibInit", (char*) jobLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobLibTaskInstalled", (char*) &jobLibTaskInstalled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "jobQueueCreate", (char*) jobQueueCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueInit", (char*) jobQueueInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueLibInit", (char*) jobQueueLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueuePost", (char*) jobQueuePost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueuePriorityMask", (char*) jobQueuePriorityMask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueProcess", (char*) jobQueueProcess, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueProcessFunc", (char*) &jobQueueProcessFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "jobQueueStdJobsAlloc", (char*) jobQueueStdJobsAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueStdPoolInit", (char*) jobQueueStdPoolInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueStdPost", (char*) jobQueueStdPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "jobQueueTask", (char*) jobQueueTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kbdConvertCharSet_desc", (char*) &kbdConvertCharSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kbdCurrConSet_desc", (char*) &kbdCurrConSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kbdInit_desc", (char*) &kbdInit_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kbdLedGet_desc", (char*) &kbdLedGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kbdLedSet_desc", (char*) &kbdLedSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kbdModeSet_desc", (char*) &kbdModeSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kbdNumSet_desc", (char*) &kbdNumSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kernSysctlInit", (char*) kernSysctlInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kern_node", (char*) &kern_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kernelBaseInit", (char*) kernelBaseInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelCpuEnable", (char*) kernelCpuEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelId", (char*) &kernelId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kernelIdGet", (char*) kernelIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelInit", (char*) kernelInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelIsCpuIdle", (char*) kernelIsCpuIdle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelIsIdle", (char*) &kernelIsIdle, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "kernelIsSystemIdle", (char*) kernelIsSystemIdle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelModuleListId", (char*) &kernelModuleListId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "kernelObjClassId", (char*) &kernelObjClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "kernelRoundRobinInstall", (char*) kernelRoundRobinInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelState", (char*) &kernelState, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "kernelTimeSlice", (char*) kernelTimeSlice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelVersion", (char*) kernelVersion, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernel_sysctl", (char*) kernel_sysctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kill", (char*) kill, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "l", (char*) l, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "labs", (char*) labs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lastCmd", (char*) &lastCmd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "lastLoader", (char*) &lastLoader, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "lcd_test", (char*) lcd_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ld", (char*) ld, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ldCommonMatchAll", (char*) &ldCommonMatchAll, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ldexp", (char*) ldexp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ldiv", (char*) ldiv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ldiv_r", (char*) ldiv_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledBeep", (char*) ledBeep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledBwdFind", (char*) ledBwdFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledCDelete", (char*) ledCDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledChange", (char*) ledChange, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledClose", (char*) ledClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledComplete", (char*) ledComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledCompletionSet", (char*) ledCompletionSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledControl", (char*) ledControl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledDfltComplete", (char*) ledDfltComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledFwdFind", (char*) ledFwdFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistCurrentNumGet", (char*) ledHistCurrentNumGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistFind", (char*) ledHistFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistNextGet", (char*) ledHistNextGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistNumGet", (char*) ledHistNumGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistPrevGet", (char*) ledHistPrevGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistResize", (char*) ledHistResize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistoryAdd", (char*) ledHistoryAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistoryClone", (char*) ledHistoryClone, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistoryCreate", (char*) ledHistoryCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistoryFree", (char*) ledHistoryFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistoryLineAllocate", (char*) ledHistoryLineAllocate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledHistorySet", (char*) ledHistorySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledInactivityDelaySet", (char*) ledInactivityDelaySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledLibInit", (char*) ledLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledModeDefaultNameGet", (char*) ledModeDefaultNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledModeNameGet", (char*) ledModeNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledModeRegister", (char*) ledModeRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledModeSet", (char*) ledModeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledNWrite", (char*) ledNWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledOpen", (char*) ledOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledPreempt", (char*) ledPreempt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledPreemptSet", (char*) ledPreemptSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledRead", (char*) ledRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledRedraw", (char*) ledRedraw, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledReplace", (char*) ledReplace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledSearch", (char*) ledSearch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "link", (char*) link, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "linkBufPoolInit", (char*) linkBufPoolInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "linkDataSyms", (char*) &linkDataSyms, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "linkSyms", (char*) &linkSyms, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "linkedCtorsInitialized", (char*) &linkedCtorsInitialized, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "listen", (char*) listen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lkAddr", (char*) lkAddr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lkAddrInternal", (char*) lkAddrInternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lkup", (char*) lkup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ll", (char*) ll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "llr", (char*) llr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadCommonSymbolProcess", (char*) loadCommonSymbolProcess, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadDefinedSymbolProcess", (char*) loadDefinedSymbolProcess, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfFileHeaderReadAndCheck", (char*) loadElfFileHeaderReadAndCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfInit", (char*) loadElfInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfProgramHeaderTableReadAndCheck", (char*) loadElfProgramHeaderTableReadAndCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfRelEntryRead", (char*) loadElfRelEntryRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfRelaEntryRead", (char*) loadElfRelaEntryRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfSectionHeaderCheck", (char*) loadElfSectionHeaderCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadFormat", (char*) &loadFormat, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "loadLibInit", (char*) loadLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModule", (char*) loadModule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleAt", (char*) loadModuleAt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleInfoFromFd", (char*) loadModuleInfoFromFd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleInfoFromFilenameClose", (char*) loadModuleInfoFromFilenameClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleInfoFromFilenameOpen", (char*) loadModuleInfoFromFilenameOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleInfoInit", (char*) loadModuleInfoInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleInfoRelease", (char*) loadModuleInfoRelease, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleSeek", (char*) loadModuleSeek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleStringRead", (char*) loadModuleStringRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleTagsCheck", (char*) loadModuleTagsCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleValueRead", (char*) loadModuleValueRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadSectionsInstall", (char*) loadSectionsInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadSegInfoDescAllocate", (char*) loadSegInfoDescAllocate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadSegInfoDescFree", (char*) loadSegInfoDescFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadSegmentsAllocate", (char*) loadSegmentsAllocate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadShareTgtMemAlign", (char*) loadShareTgtMemAlign, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadShareTgtMemFree", (char*) loadShareTgtMemFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadShareTgtMemSet", (char*) loadShareTgtMemSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadSysSymTblLoad", (char*) loadSysSymTblLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadUndefinedSymbolProcess", (char*) loadUndefinedSymbolProcess, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loaderCacheBufferSize", (char*) &loaderCacheBufferSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "localToGlobalOffset", (char*) &localToGlobalOffset, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "localeconv", (char*) localeconv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "localtime", (char*) localtime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "localtime_r", (char*) localtime_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "log", (char*) log, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "log10", (char*) log10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "log2", (char*) log2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logDecorationChange", (char*) logDecorationChange, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logFd", (char*) &logFd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "logFdAdd", (char*) logFdAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logFdDelete", (char*) logFdDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logFdFromRlogin", (char*) &logFdFromRlogin, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logFdSem", (char*) &logFdSem, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "logFdSet", (char*) logFdSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logInfo", (char*) &logInfo, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "logInit", (char*) logInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logLevelChange", (char*) logLevelChange, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logMsg", (char*) logMsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logShow", (char*) logShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logTask", (char*) logTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logTaskId", (char*) &logTaskId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logTaskOptions", (char*) &logTaskOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logTaskPriority", (char*) &logTaskPriority, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logTaskStackSize", (char*) &logTaskStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logb", (char*) logb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loggerInfoShow", (char*) loggerInfoShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginDefaultEncrypt", (char*) loginDefaultEncrypt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginEncryptGet", (char*) loginEncryptGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginEncryptInstall", (char*) loginEncryptInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginHostname", (char*) &loginHostname, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "loginInit", (char*) loginInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginPassword", (char*) &loginPassword, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "loginPrompt", (char*) loginPrompt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginPrompt2", (char*) loginPrompt2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginStringSet", (char*) loginStringSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginTimeOutInSecond", (char*) &loginTimeOutInSecond, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "loginUserAdd", (char*) loginUserAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUserDelete", (char*) loginUserDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUserShow", (char*) loginUserShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUserVerify", (char*) loginUserVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUsername", (char*) &loginUsername, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "loginVerify_node", (char*) &loginVerify_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logout", (char*) logout, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "longjmp", (char*) longjmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lpt_test", (char*) lpt_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ls", (char*) ls, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lseek", (char*) lseek, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lsr", (char*) lsr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstAdd", (char*) lstAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstConcat", (char*) lstConcat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstCount", (char*) lstCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstDelete", (char*) lstDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstExtract", (char*) lstExtract, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFind", (char*) lstFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFirst", (char*) lstFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFree", (char*) lstFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFree2", (char*) lstFree2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstGet", (char*) lstGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstInit", (char*) lstInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstInsert", (char*) lstInsert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstLast", (char*) lstLast, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstLibInit", (char*) lstLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstNStep", (char*) lstNStep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstNext", (char*) lstNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstNth", (char*) lstNth, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstPrevious", (char*) lstPrevious, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m", (char*) m, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m2If64BitCounters", (char*) &m2If64BitCounters, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "m6845vxbRegister", (char*) m6845vxbRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRegs", (char*) mRegs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_prepend", (char*) m_prepend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "malloc", (char*) malloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathAcosFunc", (char*) &mathAcosFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathAsinFunc", (char*) &mathAsinFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathAtan2Func", (char*) &mathAtan2Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathAtanFunc", (char*) &mathAtanFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathCbrtFunc", (char*) &mathCbrtFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathCeilFunc", (char*) &mathCeilFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathCosFunc", (char*) &mathCosFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathCoshFunc", (char*) &mathCoshFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathErrNoInit", (char*) mathErrNoInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathExpFunc", (char*) &mathExpFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFabsFunc", (char*) &mathFabsFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFacosFunc", (char*) &mathFacosFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFasinFunc", (char*) &mathFasinFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFatan2Func", (char*) &mathFatan2Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFatanFunc", (char*) &mathFatanFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFcbrtFunc", (char*) &mathFcbrtFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFceilFunc", (char*) &mathFceilFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFcosFunc", (char*) &mathFcosFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFcoshFunc", (char*) &mathFcoshFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFexpFunc", (char*) &mathFexpFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFfabsFunc", (char*) &mathFfabsFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFfloorFunc", (char*) &mathFfloorFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFfmodFunc", (char*) &mathFfmodFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFhypotFunc", (char*) &mathFhypotFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFinfinityFunc", (char*) &mathFinfinityFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFirintFunc", (char*) &mathFirintFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFiroundFunc", (char*) &mathFiroundFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFlog10Func", (char*) &mathFlog10Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFlog2Func", (char*) &mathFlog2Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFlogFunc", (char*) &mathFlogFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFloorFunc", (char*) &mathFloorFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFmodFunc", (char*) &mathFmodFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFpowFunc", (char*) &mathFpowFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFroundFunc", (char*) &mathFroundFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFsinFunc", (char*) &mathFsinFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFsincosFunc", (char*) &mathFsincosFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFsinhFunc", (char*) &mathFsinhFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFsqrtFunc", (char*) &mathFsqrtFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFtanFunc", (char*) &mathFtanFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFtanhFunc", (char*) &mathFtanhFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathFtruncFunc", (char*) &mathFtruncFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathHardAcos", (char*) mathHardAcos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardAsin", (char*) mathHardAsin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardAtan", (char*) mathHardAtan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardAtan2", (char*) mathHardAtan2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardCeil", (char*) mathHardCeil, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardCos", (char*) mathHardCos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardExp", (char*) mathHardExp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardFabs", (char*) mathHardFabs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardFloor", (char*) mathHardFloor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardFmod", (char*) mathHardFmod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardFmodIeee", (char*) mathHardFmodIeee, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardFuncInit", (char*) mathHardFuncInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardInfinity", (char*) mathHardInfinity, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardIrint", (char*) mathHardIrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardIround", (char*) mathHardIround, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardLog", (char*) mathHardLog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardLog10", (char*) mathHardLog10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardLog2", (char*) mathHardLog2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardPow", (char*) mathHardPow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardRound", (char*) mathHardRound, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardSin", (char*) mathHardSin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardSincos", (char*) mathHardSincos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardSqrt", (char*) mathHardSqrt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardTan", (char*) mathHardTan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHardTrunc", (char*) mathHardTrunc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mathHypotFunc", (char*) &mathHypotFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathInfinityFunc", (char*) &mathInfinityFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathIrintFunc", (char*) &mathIrintFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathIroundFunc", (char*) &mathIroundFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathLog10Func", (char*) &mathLog10Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathLog2Func", (char*) &mathLog2Func, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathLogFunc", (char*) &mathLogFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathPowFunc", (char*) &mathPowFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathRoundFunc", (char*) &mathRoundFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathSinFunc", (char*) &mathSinFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathSincosFunc", (char*) &mathSincosFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathSinhFunc", (char*) &mathSinhFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathSqrtFunc", (char*) &mathSqrtFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathTanFunc", (char*) &mathTanFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathTanhFunc", (char*) &mathTanhFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mathTruncFunc", (char*) &mathTruncFunc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "max_hdr", (char*) &max_hdr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_linkhdr", (char*) &max_linkhdr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_protohdr", (char*) &max_protohdr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mblen", (char*) mblen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mbstowcs", (char*) mbstowcs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mbtowc", (char*) mbtowc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "md5_block_host_order", (char*) md5_block_host_order, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncLibInit", (char*) mdlSymSyncLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncModAdd", (char*) mdlSymSyncModAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncModInfoGet", (char*) mdlSymSyncModInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncModuleRemove", (char*) mdlSymSyncModuleRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncStop", (char*) mdlSymSyncStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncSymListAdd", (char*) mdlSymSyncSymListAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mdlSymSyncSymListGet", (char*) mdlSymSyncSymListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memAddToPool", (char*) memAddToPool, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memBlockSizeGet", (char*) memBlockSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memDefaultAlignment", (char*) &memDefaultAlignment, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memFindMax", (char*) memFindMax, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memInfoGet", (char*) memInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memInfoInit", (char*) memInfoInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memInit", (char*) memInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memMsgBlockError", (char*) &memMsgBlockError, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memMsgBlockTooBig", (char*) &memMsgBlockTooBig, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memOptionsGet", (char*) memOptionsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memOptionsSet", (char*) memOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAddToPool", (char*) memPartAddToPool, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAlignedAlloc", (char*) memPartAlignedAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAlloc", (char*) memPartAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAllocErrorRtn", (char*) &memPartAllocErrorRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartBlockErrorRtn", (char*) &memPartBlockErrorRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartBlockIsValid", (char*) memPartBlockIsValid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartBlockValidate", (char*) memPartBlockValidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartClassId", (char*) &memPartClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartCreate", (char*) memPartCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartCreateHookSet", (char*) memPartCreateHookSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartDelete", (char*) memPartDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartDeleteFree", (char*) memPartDeleteFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartEdrErrorInject", (char*) memPartEdrErrorInject, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartFindMax", (char*) memPartFindMax, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartFree", (char*) memPartFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartFreeListWalk", (char*) memPartFreeListWalk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartHooksInstall", (char*) memPartHooksInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartInfoGet", (char*) memPartInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartInit", (char*) memPartInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartInsertFree", (char*) memPartInsertFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartLibInit", (char*) memPartLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartOptionsDefault", (char*) &memPartOptionsDefault, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartOptionsGet", (char*) memPartOptionsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartOptionsSet", (char*) memPartOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartRealloc", (char*) memPartRealloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartReallocInternal", (char*) memPartReallocInternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartShow", (char*) memPartShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartVerifiedLock", (char*) memPartVerifiedLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPoolEndAdrs", (char*) &memPoolEndAdrs, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "memRom", (char*) &memRom, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "memShow", (char*) memShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memShowInit", (char*) memShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memSysPartId", (char*) &memSysPartId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memTopPhys", (char*) &memTopPhys, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "memalign", (char*) memalign, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memchr", (char*) memchr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memcmp", (char*) memcmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memcpy", (char*) memcpy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memmove", (char*) memmove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memoryDump", (char*) memoryDump, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memoryModify", (char*) memoryModify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memset", (char*) memset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mib2ErrorAdd", (char*) mib2ErrorAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mib2Init", (char*) mib2Init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusCreate", (char*) miiBusCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusDelete", (char*) miiBusDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusGet", (char*) miiBusGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusIdleErrorCheck", (char*) miiBusIdleErrorCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusListAdd", (char*) miiBusListAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusListDel", (char*) miiBusListDel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusMediaAdd", (char*) miiBusMediaAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusMediaDefaultSet", (char*) miiBusMediaDefaultSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusMediaDel", (char*) miiBusMediaDel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusMediaListGet", (char*) miiBusMediaListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusMediaUpdate", (char*) miiBusMediaUpdate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusModeGet", (char*) miiBusModeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusModeSet", (char*) miiBusModeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusRead", (char*) miiBusRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusRegister", (char*) miiBusRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiBusWrite", (char*) miiBusWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "miiMediaUpdate_desc", (char*) &miiMediaUpdate_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "miiModeGet_desc", (char*) &miiModeGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "miiModeSet_desc", (char*) &miiModeSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "miiRead_desc", (char*) &miiRead_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "miiWrite_desc", (char*) &miiWrite_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mkdir", (char*) mkdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mktime", (char*) mktime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArchCopySize", (char*) &mmuArchCopySize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuArchLibAttrs", (char*) &mmuArchLibAttrs, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuArchLibFuncs", (char*) &mmuArchLibFuncs, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuCacheStateTransTbl", (char*) &mmuCacheStateTransTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuInvalidState", (char*) &mmuInvalidState, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuLibFuncs", (char*) &mmuLibFuncs, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuMaskTransTbl", (char*) &mmuMaskTransTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuPhysAddrShift", (char*) &mmuPhysAddrShift, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuPro32Enable", (char*) mmuPro32Enable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32Enabled", (char*) &mmuPro32Enabled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuPro32LibInit", (char*) mmuPro32LibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32Off", (char*) mmuPro32Off, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32On", (char*) mmuPro32On, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32Page0UnMap", (char*) mmuPro32Page0UnMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32Page0UnMapped", (char*) &mmuPro32Page0UnMapped, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuPro32PdbrGet", (char*) mmuPro32PdbrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32PdbrSet", (char*) mmuPro32PdbrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32PhysAddrSet", (char*) mmuPro32PhysAddrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32TLBEntryFlush", (char*) mmuPro32TLBEntryFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPro32TLBFlush", (char*) mmuPro32TLBFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuProtStateTransTbl", (char*) &mmuProtStateTransTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuValidStateTransTbl", (char*) &mmuValidStateTransTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "modf", (char*) modf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "modlist", (char*) &modlist, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "moduleCheck", (char*) moduleCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleCreate", (char*) moduleCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleCreateHookAdd", (char*) moduleCreateHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleCreateHookDelete", (char*) moduleCreateHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleDelete", (char*) moduleDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleDescDestroy", (char*) moduleDescDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleEach", (char*) moduleEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFindByGroup", (char*) moduleFindByGroup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFindByName", (char*) moduleFindByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFindByNameAndPath", (char*) moduleFindByNameAndPath, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFirstSectionGet", (char*) moduleFirstSectionGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFlagsGet", (char*) moduleFlagsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleIdFigure", (char*) moduleIdFigure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleIdListGet", (char*) moduleIdListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleIdVerify", (char*) moduleIdVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleInfoGet", (char*) moduleInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleInit", (char*) moduleInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleLibInit", (char*) moduleLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleNameGet", (char*) moduleNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleNextSectionGet", (char*) moduleNextSectionGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSectionChecksumSet", (char*) moduleSectionChecksumSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSectionDescFree", (char*) moduleSectionDescFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSectionDescGet", (char*) moduleSectionDescGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSectionRegister", (char*) moduleSectionRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegAdd", (char*) moduleSegAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegEach", (char*) moduleSegEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegFirst", (char*) moduleSegFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegGet", (char*) moduleSegGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegInfoGet", (char*) moduleSegInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegNext", (char*) moduleSegNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleShow", (char*) moduleShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleShowInit", (char*) moduleShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleUndefSymAdd", (char*) moduleUndefSymAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mpApicAddrTableGet_desc", (char*) &mpApicAddrTableGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicBusTableGet_desc", (char*) &mpApicBusTableGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicCpuIndexTableGet_desc", (char*) &mpApicCpuIndexTableGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicDataShow_desc", (char*) &mpApicDataShow_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicFpsGet_desc", (char*) &mpApicFpsGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicInterruptTableGet_desc", (char*) &mpApicInterruptTableGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicLoIndexTableGet_desc", (char*) &mpApicLoIndexTableGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicLogicalTableGet_desc", (char*) &mpApicLogicalTableGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicNbusGet_desc", (char*) &mpApicNbusGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicNioApicGet_desc", (char*) &mpApicNioApicGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicNiointGet_desc", (char*) &mpApicNiointGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicNlointGet_desc", (char*) &mpApicNlointGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpApicloBaseGet_desc", (char*) &mpApicloBaseGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mpCpuIndexTable", (char*) &mpCpuIndexTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQClassId", (char*) &msgQClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "msgQCreate", (char*) msgQCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQCreateLibInit", (char*) msgQCreateLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQDelete", (char*) msgQDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQDestroy", (char*) msgQDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQDistInfoGetRtn", (char*) &msgQDistInfoGetRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistNumMsgsRtn", (char*) &msgQDistNumMsgsRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistReceiveRtn", (char*) &msgQDistReceiveRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistSendRtn", (char*) &msgQDistSendRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistShowRtn", (char*) &msgQDistShowRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQEvStart", (char*) msgQEvStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQEvStop", (char*) msgQEvStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQInfoGet", (char*) msgQInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQInit", (char*) msgQInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQInitialize", (char*) msgQInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQLibInit", (char*) msgQLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQLibInstalled", (char*) &msgQLibInstalled, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQNumMsgs", (char*) msgQNumMsgs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQReceive", (char*) msgQReceive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQSend", (char*) msgQSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQSmInfoGetRtn", (char*) &msgQSmInfoGetRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmNumMsgsRtn", (char*) &msgQSmNumMsgsRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmReceiveRtn", (char*) &msgQSmReceiveRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmSendRtn", (char*) &msgQSmSendRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmShowRtn", (char*) &msgQSmShowRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQTerminate", (char*) msgQTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mutexOptionsHostLib", (char*) &mutexOptionsHostLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsIosLib", (char*) &mutexOptionsIosLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsLogLib", (char*) &mutexOptionsLogLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsNetDrv", (char*) &mutexOptionsNetDrv, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsSelectLib", (char*) &mutexOptionsSelectLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsSymLib", (char*) &mutexOptionsSymLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsTyLib", (char*) &mutexOptionsTyLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsVmBaseLib", (char*) &mutexOptionsVmBaseLib, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mux2Bind", (char*) mux2Bind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mux2LibInit", (char*) mux2LibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mux2OverEndInit", (char*) mux2OverEndInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mux2OverEndOutputFilterChainDrops", (char*) &mux2OverEndOutputFilterChainDrops, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mux2PollReceive", (char*) mux2PollReceive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mux2PollSend", (char*) mux2PollSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mux2Send", (char*) mux2Send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxAddressForm", (char*) muxAddressForm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxBind", (char*) muxBind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxBindCommon", (char*) muxBindCommon, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxBindStyles", (char*) &muxBindStyles, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "muxCommonInit", (char*) muxCommonInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDebug", (char*) &muxDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxDevAcquire", (char*) muxDevAcquire, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevConnect_desc", (char*) &muxDevConnect_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxDevExists", (char*) muxDevExists, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevLoad", (char*) muxDevLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevRelease", (char*) muxDevRelease, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStart", (char*) muxDevStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStop", (char*) muxDevStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStopAll", (char*) muxDevStopAll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevUnload", (char*) muxDevUnload, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevUnloadAsync", (char*) muxDevUnloadAsync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxEndJobQDo", (char*) muxEndJobQDo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxEndJobQDoJob", (char*) muxEndJobQDoJob, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxEndListGet", (char*) muxEndListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxEndQnumGet", (char*) muxEndQnumGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxEndRxJobQueue", (char*) muxEndRxJobQueue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxEndStyles", (char*) &muxEndStyles, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "muxError", (char*) muxError, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxErrorPost", (char*) muxErrorPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxErrorSkip", (char*) muxErrorSkip, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxIfTypeGet", (char*) muxIfTypeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxIoctl", (char*) muxIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxIpcomPktFreeMblk", (char*) muxIpcomPktFreeMblk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxIpcomPktToMblkTx", (char*) muxIpcomPktToMblkTx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxL2PortDetachRtn", (char*) &muxL2PortDetachRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxLibInit", (char*) muxLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxLinkDownNotify", (char*) muxLinkDownNotify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxLinkHeaderCreate", (char*) muxLinkHeaderCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxLinkUpNotify", (char*) muxLinkUpNotify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxLock", (char*) &muxLock, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxMCastAddrAdd", (char*) muxMCastAddrAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMCastAddrDel", (char*) muxMCastAddrDel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMCastAddrGet", (char*) muxMCastAddrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMblkFreeIpcomPktOutDone", (char*) muxMblkFreeIpcomPktOutDone, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMblkToIpcomPktMallocDrops", (char*) &muxMblkToIpcomPktMallocDrops, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "muxMblkToIpcomPktTx", (char*) muxMblkToIpcomPktTx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMblkToIpcomPktTxChainDrops", (char*) &muxMblkToIpcomPktTxChainDrops, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "muxPacketAddrGet", (char*) muxPacketAddrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPacketDataGet", (char*) muxPacketDataGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollReceive", (char*) muxPollReceive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollSend", (char*) muxPollSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxProtoInfoGet", (char*) muxProtoInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxProtoListGet", (char*) muxProtoListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxReceive", (char*) muxReceive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxSend", (char*) muxSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxShow", (char*) muxShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkBind", (char*) muxTkBind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkCookieGet", (char*) muxTkCookieGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkDrvCheck", (char*) muxTkDrvCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkLibInit", (char*) muxTkLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkOverEndInit", (char*) muxTkOverEndInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkPollReceive", (char*) muxTkPollReceive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkPollSend", (char*) muxTkPollSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkSend", (char*) muxTkSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTxRestart", (char*) muxTxRestart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxUnbind", (char*) muxUnbind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mv", (char*) mv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "name_node", (char*) &name_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "namelessPrefix", (char*) &namelessPrefix, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nbioAppend", (char*) nbioAppend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioBegin", (char*) nbioBegin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioDrop", (char*) nbioDrop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioEnd", (char*) nbioEnd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioFdPrint", (char*) nbioFdPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioFlush", (char*) nbioFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioFormatV", (char*) nbioFormatV, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLog", (char*) nbioLog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogInfoInit", (char*) nbioLogInfoInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogInfoMsgsAdd", (char*) nbioLogInfoMsgsAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogInfoSync", (char*) nbioLogInfoSync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogInfoTerminate", (char*) nbioLogInfoTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogInit", (char*) nbioLogInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogServerInit", (char*) nbioLogServerInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioLogTaskName", (char*) &nbioLogTaskName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nbioLogTaskOptions", (char*) &nbioLogTaskOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nbioLogTaskPriority", (char*) &nbioLogTaskPriority, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nbioLogTaskStackSize", (char*) &nbioLogTaskStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nbioOutput", (char*) nbioOutput, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nbioPoolSemOptions", (char*) &nbioPoolSemOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nbioSync", (char*) nbioSync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netAttachFlag", (char*) &netAttachFlag, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netBufClOffset", (char*) &netBufClOffset, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netBufLibInit", (char*) netBufLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netBufLibInitialize", (char*) netBufLibInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netBufLock", (char*) &netBufLock, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netBufPoolInit", (char*) netBufPoolInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClBlkFree", (char*) netClBlkFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClBlkGet", (char*) netClBlkGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClBlkJoin", (char*) netClBlkJoin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClFree", (char*) netClFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClPoolIdGet", (char*) netClPoolIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClusterGet", (char*) netClusterGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDaemonQ", (char*) netDaemonQ, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDaemonQnum", (char*) netDaemonQnum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDaemonsCount", (char*) netDaemonsCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDaemonsStart", (char*) netDaemonsStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDevBootFlag", (char*) &netDevBootFlag, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netDevCreate", (char*) netDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDevCreate2", (char*) netDevCreate2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrv", (char*) netDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrvDebugLevelSet", (char*) netDrvDebugLevelSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrvFileDoesNotExist", (char*) netDrvFileDoesNotExist, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrvFileDoesNotExistInstall", (char*) netDrvFileDoesNotExistInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netErrnoSet", (char*) netErrnoSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netHelp", (char*) netHelp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netJobAdd", (char*) netJobAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netJobNum", (char*) &netJobNum, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netJobQueueId", (char*) &netJobQueueId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netLibInitialize", (char*) netLibInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netLsByName", (char*) netLsByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkChainDup", (char*) netMblkChainDup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClChainFree", (char*) netMblkClChainFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClFree", (char*) netMblkClFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClGet", (char*) netMblkClGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClJoin", (char*) netMblkClJoin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkDup", (char*) netMblkDup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkFree", (char*) netMblkFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkFromBufCopy", (char*) netMblkFromBufCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkGet", (char*) netMblkGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkOffsetToBufCopy", (char*) netMblkOffsetToBufCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkToBufCopy", (char*) netMblkToBufCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolCreate", (char*) netPoolCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolCreateValidate", (char*) netPoolCreateValidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolDelete", (char*) netPoolDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolIdGet", (char*) netPoolIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolIdGetWork", (char*) netPoolIdGetWork, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolInit", (char*) netPoolInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolInitWrapper", (char*) netPoolInitWrapper, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolKheapInit", (char*) netPoolKheapInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolNameGet", (char*) netPoolNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolRelPri", (char*) &netPoolRelPri, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netPoolRelease", (char*) netPoolRelease, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTaskId", (char*) &netTaskId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netTaskNamePrefix", (char*) &netTaskNamePrefix, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTaskOptions", (char*) &netTaskOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTaskPriority", (char*) &netTaskPriority, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTaskStackSize", (char*) &netTaskStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTupleFree", (char*) netTupleFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTupleGet", (char*) netTupleGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netVersionString", (char*) &netVersionString, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netmask", (char*) &netmask, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "next_node", (char*) &next_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "noDev", (char*) noDev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "nonVolGet_desc", (char*) &nonVolGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nonVolSet_desc", (char*) &nonVolSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ns16550SioRegister", (char*) ns16550SioRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "numLogFds", (char*) &numLogFds, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "numberOfCmdHandlers", (char*) &numberOfCmdHandlers, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "numberOfLoaders", (char*) &numberOfLoaders, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "nvRamSegDefGet", (char*) nvRamSegDefGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objAlloc", (char*) objAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objAllocExtra", (char*) objAllocExtra, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objArchLibInit", (char*) objArchLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objClassIdGet", (char*) objClassIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objClassTypeGet", (char*) objClassTypeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objContextGet", (char*) objContextGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objContextSet", (char*) objContextSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreInit", (char*) objCoreInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreInvalidate", (char*) objCoreInvalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreReclaim", (char*) objCoreReclaim, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreTerminate", (char*) objCoreTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreUnlink", (char*) objCoreUnlink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objEach", (char*) objEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objFree", (char*) objFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objGenericVerify", (char*) objGenericVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objInfo", (char*) objInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objInfoInit", (char*) objInfoInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objLibInit", (char*) objLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objMemAlloc", (char*) objMemAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objMemFree", (char*) objMemFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objNameGet", (char*) objNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objNameLenGet", (char*) objNameLenGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objNamePtrGet", (char*) objNamePtrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objNamePtrSet", (char*) objNamePtrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objNameSet", (char*) objNameSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objNameToId", (char*) objNameToId, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objOwnerGet", (char*) objOwnerGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objOwnerLibInstalled", (char*) &objOwnerLibInstalled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "objOwnerSet", (char*) objOwnerSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objOwnerSetBase", (char*) objOwnerSetBase, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objShow", (char*) objShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objVerify", (char*) objVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objVerifyError", (char*) objVerifyError, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objVerifyMagicRead", (char*) objVerifyMagicRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objVerifyTypeRead", (char*) objVerifyTypeRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objectShow", (char*) objectShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "oidfmt_node", (char*) &oidfmt_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "oidsInList", (char*) &oidsInList, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "open", (char*) open, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "opendir", (char*) opendir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "oprintf", (char*) oprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "optarg", (char*) &optarg, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "opterr", (char*) &opterr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "optind", (char*) &optind, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "optopt", (char*) &optopt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "optreset", (char*) &optreset, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "osmFatalMsg", (char*) &osmFatalMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "osmGuardPageSize", (char*) &osmGuardPageSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "osmTask", (char*) osmTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossCalloc", (char*) ossCalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossFree", (char*) ossFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossFreeFuncPtr", (char*) &ossFreeFuncPtr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ossInitialize", (char*) ossInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossMalloc", (char*) ossMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossMallocFuncPtr", (char*) &ossMallocFuncPtr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ossMemUsedGet", (char*) ossMemUsedGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossMutexCreate", (char*) ossMutexCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossMutexDestroy", (char*) ossMutexDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossMutexRelease", (char*) ossMutexRelease, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossMutexTake", (char*) ossMutexTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossOldFree", (char*) ossOldFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossOldInstall", (char*) ossOldInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossOldMalloc", (char*) ossOldMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossPartFree", (char*) ossPartFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossPartIdGet", (char*) ossPartIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossPartMalloc", (char*) ossPartMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossPartSizeGet", (char*) ossPartSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossPartSizeSet", (char*) ossPartSizeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossSemCreate", (char*) ossSemCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossSemDestroy", (char*) ossSemDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossSemGive", (char*) ossSemGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossSemTake", (char*) ossSemTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossShutdown", (char*) ossShutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossStatus", (char*) ossStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossThreadCreate", (char*) ossThreadCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossThreadDestroy", (char*) ossThreadDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossThreadSleep", (char*) ossThreadSleep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ossTime", (char*) ossTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pAddrString", (char*) &pAddrString, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pBusHead", (char*) &pBusHead, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pBusListHead", (char*) &pBusListHead, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pClkCookie", (char*) &pClkCookie, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pClkTimer", (char*) &pClkTimer, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pCoprocDescList", (char*) &pCoprocDescList, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pDataCollectorFunctions", (char*) &pDataCollectorFunctions, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pDbgClnt", (char*) &pDbgClnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pDevName", (char*) &pDevName, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pDriverListHead", (char*) &pDriverListHead, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pEndPktDev", (char*) &pEndPktDev, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pHead", (char*) &pHead, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pInPkt", (char*) &pInPkt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pIosDevCloseRtn", (char*) &pIosDevCloseRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pIosFdEntrySetRtn", (char*) &pIosFdEntrySetRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pIosFdInvalidRtn", (char*) &pIosFdInvalidRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pIosRemovableDevDrv", (char*) &pIosRemovableDevDrv, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pIosSuspendedDevDrv", (char*) &pIosSuspendedDevDrv, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pJobPool", (char*) &pJobPool, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pLoadRoutine", (char*) &pLoadRoutine, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pLoaderHooksCall", (char*) &pLoaderHooksCall, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pM2TrapRtn", (char*) &pM2TrapRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pM2TrapRtnArg", (char*) &pM2TrapRtnArg, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pMibRtn", (char*) &pMibRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pMpApicData", (char*) &pMpApicData, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pNetPoolHead", (char*) &pNetPoolHead, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pNullFd", (char*) &pNullFd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pPlbBus", (char*) &pPlbBus, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pPlbDev", (char*) &pPlbDev, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pPlbDevControl", (char*) &pPlbDevControl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pRebootHookTbl", (char*) &pRebootHookTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pRootMemStart", (char*) &pRootMemStart, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pRtpDbgCmdSvc", (char*) &pRtpDbgCmdSvc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pSockIoctlMemVal", (char*) &pSockIoctlMemVal, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pSymRelRtn", (char*) &pSymRelRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pSysClkName", (char*) &pSysClkName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pSysGdt", (char*) &pSysGdt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pSysPlbMethods", (char*) &pSysPlbMethods, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pSysctlCtxList", (char*) &pSysctlCtxList, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTaskLastDspTcb", (char*) &pTaskLastDspTcb, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTaskLastFpTcb", (char*) &pTaskLastFpTcb, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTgtName", (char*) &pTgtName, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pUnixIoctlMemVal", (char*) &pUnixIoctlMemVal, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pUnloaderHooksCall", (char*) &pUnloaderHooksCall, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pUsb2MscDriver", (char*) &pUsb2MscDriver, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pVmBaseFuncsSet", (char*) &pVmBaseFuncsSet, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pVmInvPageMapRtn", (char*) &pVmInvPageMapRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pVxbDelayCookie", (char*) &pVxbDelayCookie, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pVxbDelayTimer", (char*) &pVxbDelayTimer, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pVxbSpinLockGive", (char*) &pVxbSpinLockGive, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pVxbSpinLockTake", (char*) &pVxbSpinLockTake, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pWdbClnt", (char*) &pWdbClnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pWdbCommIf", (char*) &pWdbCommIf, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pWdbCtxBpIf", (char*) &pWdbCtxBpIf, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pWdbExternSystemRegs", (char*) &pWdbExternSystemRegs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pWdbMemRegions", (char*) &pWdbMemRegions, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pWdbRtIf", (char*) &pWdbRtIf, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pWdbXport", (char*) &pWdbXport, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pWvNetEventMap", (char*) &pWvNetEventMap, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "panic", (char*) panic, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "panicSuspend", (char*) &panicSuspend, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "partLibCreate", (char*) partLibCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "partLibCreateSz", (char*) partLibCreateSz, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathBuild", (char*) pathBuild, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathCat", (char*) pathCat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathCondense", (char*) pathCondense, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathLastName", (char*) pathLastName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathLastNamePtr", (char*) pathLastNamePtr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathParse", (char*) pathParse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathSplit", (char*) pathSplit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathconf", (char*) pathconf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pause", (char*) pause, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pc", (char*) pc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pcConBeep_desc", (char*) &pcConBeep_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pcConDevBind", (char*) pcConDevBind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pcConDevCreate", (char*) pcConDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pcConDrv", (char*) pcConDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciBusAnnounceDevices", (char*) pciBusAnnounceDevices, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciCfgInit", (char*) pciCfgInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigEnable", (char*) pciConfigEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigExtCapFind", (char*) pciConfigExtCapFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigForeachFunc", (char*) pciConfigForeachFunc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigInByte", (char*) pciConfigInByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigInLong", (char*) pciConfigInLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigInWord", (char*) pciConfigInWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigModifyByte", (char*) pciConfigModifyByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigModifyLong", (char*) pciConfigModifyLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigModifyWord", (char*) pciConfigModifyWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigOutByte", (char*) pciConfigOutByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigOutLong", (char*) pciConfigOutLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConfigOutWord", (char*) pciConfigOutWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciConnect", (char*) pciConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciDevConfig", (char*) pciDevConfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciDevMatch", (char*) pciDevMatch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciDeviceAnnounce", (char*) pciDeviceAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciFindClass", (char*) pciFindClass, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciFindDevice", (char*) pciFindDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciHcfRecordFind", (char*) pciHcfRecordFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciInit1", (char*) pciInit1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciInit2", (char*) pciInit2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciIntConnect", (char*) pciIntConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciIntDisconnect", (char*) pciIntDisconnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciIntDisconnect2", (char*) pciIntDisconnect2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciIntVectorToIRQ", (char*) pciIntVectorToIRQ, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pciRegister", (char*) pciRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumBtc", (char*) pentiumBtc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumBts", (char*) pentiumBts, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumCr4Get", (char*) pentiumCr4Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumCr4Set", (char*) pentiumCr4Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumM6845VgaResources", (char*) &pentiumM6845VgaResources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMcaEnable", (char*) pentiumMcaEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMsrGet", (char*) pentiumMsrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMsrInit", (char*) pentiumMsrInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMsrP5", (char*) &pentiumMsrP5, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMsrP5NumEnt", (char*) &pentiumMsrP5NumEnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMsrP6", (char*) &pentiumMsrP6, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMsrP6NumEnt", (char*) &pentiumMsrP6NumEnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMsrP7", (char*) &pentiumMsrP7, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMsrP7NumEnt", (char*) &pentiumMsrP7NumEnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumMsrSet", (char*) pentiumMsrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMtrrDisable", (char*) pentiumMtrrDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMtrrEnable", (char*) pentiumMtrrEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMtrrGet", (char*) pentiumMtrrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumMtrrSet", (char*) pentiumMtrrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcGet", (char*) pentiumP5PmcGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcGet0", (char*) pentiumP5PmcGet0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcGet1", (char*) pentiumP5PmcGet1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcReset", (char*) pentiumP5PmcReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcReset0", (char*) pentiumP5PmcReset0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcReset1", (char*) pentiumP5PmcReset1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcStart0", (char*) pentiumP5PmcStart0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcStart1", (char*) pentiumP5PmcStart1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcStop0", (char*) pentiumP5PmcStop0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP5PmcStop1", (char*) pentiumP5PmcStop1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcGet", (char*) pentiumP6PmcGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcGet0", (char*) pentiumP6PmcGet0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcGet1", (char*) pentiumP6PmcGet1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcReset", (char*) pentiumP6PmcReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcReset0", (char*) pentiumP6PmcReset0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcReset1", (char*) pentiumP6PmcReset1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcStart", (char*) pentiumP6PmcStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcStop", (char*) pentiumP6PmcStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumP6PmcStop1", (char*) pentiumP6PmcStop1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPci0Resources", (char*) &pentiumPci0Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumPciBusDevGet", (char*) pentiumPciBusDevGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPciMmuMapAdd", (char*) pentiumPciMmuMapAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPciPhysMemHandle", (char*) pentiumPciPhysMemHandle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPciPhysMemShow", (char*) pentiumPciPhysMemShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPciRegister", (char*) pentiumPciRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcGet", (char*) pentiumPmcGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcGet0", (char*) pentiumPmcGet0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcGet1", (char*) pentiumPmcGet1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcReset", (char*) pentiumPmcReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcReset0", (char*) pentiumPmcReset0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcReset1", (char*) pentiumPmcReset1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcStart", (char*) pentiumPmcStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcStart0", (char*) pentiumPmcStart0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcStart1", (char*) pentiumPmcStart1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcStop", (char*) pentiumPmcStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcStop0", (char*) pentiumPmcStop0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumPmcStop1", (char*) pentiumPmcStop1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumSerialize", (char*) pentiumSerialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumTlbFlush", (char*) pentiumTlbFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumTscGet32", (char*) pentiumTscGet32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumTscGet64", (char*) pentiumTscGet64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumTscReset", (char*) pentiumTscReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pentiumi8042KbdResources", (char*) &pentiumi8042KbdResources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumi8042MseResources", (char*) &pentiumi8042MseResources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumi82501Resources", (char*) &pentiumi82501Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumi82502Resources", (char*) &pentiumi82502Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumi82503Resources", (char*) &pentiumi82503Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pentiumi82504Resources", (char*) &pentiumi82504Resources, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "period", (char*) period, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "periodHost", (char*) periodHost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "periodRun", (char*) periodRun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "perror", (char*) perror, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeDevCreate", (char*) pipeDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeDevDelete", (char*) pipeDevDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeDrv", (char*) pipeDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeMsgQOptions", (char*) &pipeMsgQOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "plbConnect", (char*) plbConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "plbDevMatch", (char*) plbDevMatch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "plbInit1", (char*) plbInit1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "plbInit2", (char*) plbInit2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "plbIntrGet", (char*) plbIntrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "plbIntrSet", (char*) plbIntrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "plbRegister", (char*) plbRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolBlockAdd", (char*) poolBlockAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolCreate", (char*) poolCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolDelete", (char*) poolDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolFreeCount", (char*) poolFreeCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolIdListGet", (char*) poolIdListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolIncrementGet", (char*) poolIncrementGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolIncrementSet", (char*) poolIncrementSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolItemGet", (char*) poolItemGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolItemReturn", (char*) poolItemReturn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolLibInit", (char*) poolLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolListGbl", (char*) &poolListGbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "poolTotalCount", (char*) poolTotalCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "poolUnusedBlocksFree", (char*) poolUnusedBlocksFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pow", (char*) pow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ppGlobalEnviron", (char*) &ppGlobalEnviron, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "print64", (char*) print64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64Fine", (char*) print64Fine, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64Mult", (char*) print64Mult, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64Row", (char*) print64Row, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printBootShellPrompt", (char*) &printBootShellPrompt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "printErr", (char*) printErr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printErrno", (char*) printErrno, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printErrorMessageHere", (char*) printErrorMessageHere, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printExc", (char*) printExc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printLogo", (char*) printLogo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printf", (char*) printf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "priv_targetName", (char*) &priv_targetName, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ptyDevCreate", (char*) ptyDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ptyDevRemove", (char*) ptyDevRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ptyDrv", (char*) ptyDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putc", (char*) putc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putchar", (char*) putchar, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putenv", (char*) putenv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "puts", (char*) puts, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putw", (char*) putw, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pwd", (char*) pwd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qAdvance", (char*) qAdvance, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qCalibrate", (char*) qCalibrate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qEach", (char*) qEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoClass", (char*) &qFifoClass, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qFifoClassId", (char*) &qFifoClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qFifoEach", (char*) qFifoEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoGet", (char*) qFifoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoInfo", (char*) qFifoInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoInit", (char*) qFifoInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoNext", (char*) qFifoNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoPut", (char*) qFifoPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoRemove", (char*) qFifoRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoRestore", (char*) qFifoRestore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFirst", (char*) qFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qGet", (char*) qGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qGetExpired", (char*) qGetExpired, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qInfo", (char*) qInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qInit", (char*) qInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qKey", (char*) qKey, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qNullRtn", (char*) qNullRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapClassId", (char*) &qPriBMapClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriBMapEach", (char*) qPriBMapEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapGet", (char*) qPriBMapGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapInfo", (char*) qPriBMapInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapInit", (char*) qPriBMapInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapKey", (char*) qPriBMapKey, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapNext", (char*) qPriBMapNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapPut", (char*) qPriBMapPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapRemove", (char*) qPriBMapRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapResort", (char*) qPriBMapResort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapRestore", (char*) qPriBMapRestore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapSet", (char*) qPriBMapSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaAdvance", (char*) qPriDeltaAdvance, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaClassId", (char*) &qPriDeltaClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriDeltaEach", (char*) qPriDeltaEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaGet", (char*) qPriDeltaGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaGetExpired", (char*) qPriDeltaGetExpired, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaInfo", (char*) qPriDeltaInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaInit", (char*) qPriDeltaInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaKey", (char*) qPriDeltaKey, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaNext", (char*) qPriDeltaNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaPut", (char*) qPriDeltaPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaRemove", (char*) qPriDeltaRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaResort", (char*) qPriDeltaResort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriDeltaTerminate", (char*) qPriDeltaTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListAdvance", (char*) qPriListAdvance, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListCalibrate", (char*) qPriListCalibrate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListClassId", (char*) &qPriListClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriListEach", (char*) qPriListEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListFromTailClassId", (char*) &qPriListFromTailClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriListGet", (char*) qPriListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListGetExpired", (char*) qPriListGetExpired, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListInfo", (char*) qPriListInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListInit", (char*) qPriListInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListKey", (char*) qPriListKey, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListNext", (char*) qPriListNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListPut", (char*) qPriListPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListPutFromTail", (char*) qPriListPutFromTail, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListRemove", (char*) qPriListRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListResort", (char*) qPriListResort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListTerminate", (char*) qPriListTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPut", (char*) qPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qRemove", (char*) qRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qResort", (char*) qResort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qTerminate", (char*) qTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qTradPriBMapClassId", (char*) &qTradPriBMapClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qTradPriBMapSetCompatible", (char*) qTradPriBMapSetCompatible, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qTradPriListClassId", (char*) &qTradPriListClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qTradPriListSetCompatible", (char*) qTradPriListSetCompatible, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qsort", (char*) qsort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "raise", (char*) raise, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rand", (char*) rand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rawFsDevInit", (char*) rawFsDevInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rawFsDrvNum", (char*) &rawFsDrvNum, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rawFsFdListMutexOptions", (char*) &rawFsFdListMutexOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rawFsFdMutexOptions", (char*) &rawFsFdMutexOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rawFsInit", (char*) rawFsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rawFsVolMutexOptions", (char*) &rawFsVolMutexOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rawFsVolUnmount", (char*) rawFsVolUnmount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rcmd", (char*) rcmd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rcmd_af", (char*) rcmd_af, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read", (char*) read, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readdir", (char*) readdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readdir_r", (char*) readdir_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readv", (char*) readv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readyQBMap", (char*) &readyQBMap, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "readyQHead", (char*) &readyQHead, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "realloc", (char*) realloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "realtime_test", (char*) realtime_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reboot", (char*) reboot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rebootHookAdd", (char*) rebootHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rebootHookTbl", (char*) &rebootHookTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rebootHookTblSize", (char*) &rebootHookTblSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "recv", (char*) recv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "recvfrom", (char*) recvfrom, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "recvmsg", (char*) recvmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "regsShow", (char*) regsShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "regsShowOutput", (char*) regsShowOutput, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reld", (char*) reld, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remCurIdGet", (char*) remCurIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remCurIdSet", (char*) remCurIdSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remLastResvPort", (char*) &remLastResvPort, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remLibInit", (char*) remLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remNumConnRetrials", (char*) &remNumConnRetrials, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remPasswd", (char*) &remPasswd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "remStdErrSetupTimeout", (char*) &remStdErrSetupTimeout, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remUser", (char*) &remUser, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "remove", (char*) remove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rename", (char*) rename, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeat", (char*) repeat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeatHost", (char*) repeatHost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeatRun", (char*) repeatRun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reschedule", (char*) reschedule, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "restartTaskName", (char*) &restartTaskName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskOptions", (char*) &restartTaskOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskPriority", (char*) &restartTaskPriority, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskStackSize", (char*) &restartTaskStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rewind", (char*) rewind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rewinddir", (char*) rewinddir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rindex", (char*) rindex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rm", (char*) rm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rmdir", (char*) rmdir, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngBufGet", (char*) rngBufGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngBufPut", (char*) rngBufPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngCreate", (char*) rngCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngDelete", (char*) rngDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngFlush", (char*) rngFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngFreeBytes", (char*) rngFreeBytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngIsEmpty", (char*) rngIsEmpty, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngIsFull", (char*) rngIsFull, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngMoveAhead", (char*) rngMoveAhead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngNBytes", (char*) rngNBytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngPutAhead", (char*) rngPutAhead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rootMemNBytes", (char*) &rootMemNBytes, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rootTaskId", (char*) &rootTaskId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "round", (char*) round, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "roundRobinHookInstalled", (char*) &roundRobinHookInstalled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "roundRobinOn", (char*) &roundRobinOn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "roundRobinSlice", (char*) &roundRobinSlice, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rresvport", (char*) rresvport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rresvportCommon", (char*) rresvportCommon, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rresvport_af", (char*) rresvport_af, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtpCallHandlerAddr", (char*) &rtpCallHandlerAddr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtpDeleteMsg", (char*) &rtpDeleteMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtpSigDeleteMsg", (char*) &rtpSigDeleteMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtpSigStopMsg", (char*) &rtpSigStopMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtpStopMsg", (char*) &rtpStopMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "runtimeName", (char*) &runtimeName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "runtimeVersion", (char*) &runtimeVersion, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "s", (char*) s, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sStepLibInit", (char*) sStepLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "s_ComName", (char*) &s_ComName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "s_IoCntTid", (char*) &s_IoCntTid, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_MangeCan", (char*) &s_MangeCan, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_TxBuffer", (char*) &s_TxBuffer, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_com_tid", (char*) &s_com_tid, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_net_tid", (char*) &s_net_tid, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_task_over_flag", (char*) &s_task_over_flag, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_ticks", (char*) &s_ticks, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_wdId", (char*) &s_wdId, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "s_wdId2", (char*) &s_wdId2, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "salEvtRtn", (char*) &salEvtRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "scalb", (char*) scalb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scanCharSet", (char*) scanCharSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scanField", (char*) scanField, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scanf", (char*) scanf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selNodeAdd", (char*) selNodeAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selNodeDelete", (char*) selNodeDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selTaskDeleteHookAdd", (char*) selTaskDeleteHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeup", (char*) selWakeup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupAll", (char*) selWakeupAll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupListInit", (char*) selWakeupListInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupListLen", (char*) selWakeupListLen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupListTerm", (char*) selWakeupListTerm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupType", (char*) selWakeupType, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "select", (char*) select, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selectInit", (char*) selectInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBCreate", (char*) semBCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBGive", (char*) semBGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBGiveDefer", (char*) semBGiveDefer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBGiveNoLock", (char*) semBGiveNoLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBGiveScalable", (char*) semBGiveScalable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBInit", (char*) semBInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBInitialize", (char*) semBInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBTake", (char*) semBTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBTakeNoLock", (char*) semBTakeNoLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBTakeScalable", (char*) semBTakeScalable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCCreate", (char*) semCCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCGive", (char*) semCGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCGiveDefer", (char*) semCGiveDefer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCInit", (char*) semCInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCInitialize", (char*) semCInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCTake", (char*) semCTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semClass", (char*) &semClass, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semClassId", (char*) &semClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semCreateTbl", (char*) &semCreateTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semDelete", (char*) semDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semDeleteLibInit", (char*) semDeleteLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semDestroy", (char*) semDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semEvIsFreeTbl", (char*) &semEvIsFreeTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semEvStart", (char*) semEvStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semEvStop", (char*) semEvStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semFlush", (char*) semFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semFlushDefer", (char*) semFlushDefer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semFlushDeferTbl", (char*) &semFlushDeferTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semFlushTbl", (char*) &semFlushTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semGive", (char*) semGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semGiveDefer", (char*) semGiveDefer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semGiveDeferTbl", (char*) &semGiveDeferTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semGiveNoLockTbl", (char*) &semGiveNoLockTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semGiveTbl", (char*) &semGiveTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semInfo", (char*) semInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semInfoGet", (char*) semInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semIntRestrict", (char*) semIntRestrict, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semInvalid", (char*) semInvalid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semLibInit", (char*) semLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semLocalIdVerify", (char*) semLocalIdVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMCreate", (char*) semMCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGive", (char*) semMGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveForce", (char*) semMGiveForce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveKernWork", (char*) semMGiveKernWork, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveNoLock", (char*) semMGiveNoLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveScalable", (char*) semMGiveScalable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMInit", (char*) semMInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMInitialize", (char*) semMInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMPendQPut", (char*) semMPendQPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMTake", (char*) semMTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMTakeByProxy", (char*) semMTakeByProxy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMTakeNoLock", (char*) semMTakeNoLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMTakeScalable", (char*) semMTakeScalable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQFlush", (char*) semQFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQFlushDefer", (char*) semQFlushDefer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQInit", (char*) semQInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semRTake", (char*) semRTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semRWCreate", (char*) semRWCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semRWGive", (char*) semRWGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semRWGiveForce", (char*) semRWGiveForce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semRWInitialize", (char*) semRWInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semRWLibMaxReaders", (char*) &semRWLibMaxReaders, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semSmInfoRtn", (char*) &semSmInfoRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semSmShowRtn", (char*) &semSmShowRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semTake", (char*) semTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semTakeNoLockTbl", (char*) &semTakeNoLockTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semTakeTbl", (char*) &semTakeTbl, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semTerminate", (char*) semTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semWTake", (char*) semWTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sem_test", (char*) sem_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "send", (char*) send, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendmsg", (char*) sendmsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendto", (char*) sendto, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setbuf", (char*) setbuf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setbuffer", (char*) setbuffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sethostname", (char*) sethostname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setjmp", (char*) setjmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setlinebuf", (char*) setlinebuf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setlocale", (char*) setlocale, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setsockopt", (char*) setsockopt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setvbuf", (char*) setvbuf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sfsFmtRtn", (char*) &sfsFmtRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shConfig", (char*) shConfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sha256_block_data_order", (char*) sha256_block_data_order, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sha256_block_host_order", (char*) sha256_block_host_order, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellAbort", (char*) shellAbort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellAbortHandledByShell", (char*) shellAbortHandledByShell, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellBackgroundInit", (char*) shellBackgroundInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellBackgroundRead", (char*) shellBackgroundRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdAdd", (char*) shellCmdAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdAliasAdd", (char*) shellCmdAliasAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdAliasArrayAdd", (char*) shellCmdAliasArrayAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdAliasDelete", (char*) shellCmdAliasDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdAliasShow", (char*) shellCmdAliasShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdArrayAdd", (char*) shellCmdArrayAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdCheck", (char*) shellCmdCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdExec", (char*) shellCmdExec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdInfoArgsStore", (char*) shellCmdInfoArgsStore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdInfoCmdLineStore", (char*) shellCmdInfoCmdLineStore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdInfoFinalNameStore", (char*) shellCmdInfoFinalNameStore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdInfoGet", (char*) shellCmdInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdInfoInitialNameStore", (char*) shellCmdInfoInitialNameStore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdInit", (char*) shellCmdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdMatchingAliasListGet", (char*) shellCmdMatchingAliasListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdMatchingCmdListGet", (char*) shellCmdMatchingCmdListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdMemRegister", (char*) shellCmdMemRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdMemUnregister", (char*) shellCmdMemUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdPreParseAdd", (char*) shellCmdPreParseAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdPreParsedGet", (char*) shellCmdPreParsedGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdStatementExec", (char*) shellCmdStatementExec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdStatementSplit", (char*) shellCmdStatementSplit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdSymTabIdGet", (char*) shellCmdSymTabIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdTaskIdConvert", (char*) shellCmdTaskIdConvert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCmdTopicAdd", (char*) shellCmdTopicAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCompatibleCheck", (char*) shellCompatibleCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCompatibleSet", (char*) shellCompatibleSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellCompletionPathnameGet", (char*) shellCompletionPathnameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigDefaultGet", (char*) shellConfigDefaultGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigDefaultSet", (char*) shellConfigDefaultSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigDefaultValueGet", (char*) shellConfigDefaultValueGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigDefaultValueSet", (char*) shellConfigDefaultValueSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigDefaultValueUnset", (char*) shellConfigDefaultValueUnset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigGet", (char*) shellConfigGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigLibInit", (char*) shellConfigLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigSet", (char*) shellConfigSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigValueGet", (char*) shellConfigValueGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigValueSet", (char*) shellConfigValueSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConfigValueUnset", (char*) shellConfigValueUnset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConsoleInit", (char*) shellConsoleInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellConsoleTaskId", (char*) &shellConsoleTaskId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellContextFinalize", (char*) shellContextFinalize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellContextInit", (char*) shellContextInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellContextListLock", (char*) shellContextListLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellContextListUnlock", (char*) shellContextListUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataAdd", (char*) shellDataAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataAllRemove", (char*) shellDataAllRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataFirst", (char*) shellDataFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataFromNameAdd", (char*) shellDataFromNameAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataFromNameGet", (char*) shellDataFromNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataGet", (char*) shellDataGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataNext", (char*) shellDataNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellDataRemove", (char*) shellDataRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellErrnoGet", (char*) shellErrnoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellErrnoSet", (char*) shellErrnoSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellExec", (char*) shellExec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellExitWrapper", (char*) shellExitWrapper, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellFirst", (char*) shellFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellFromNameGet", (char*) shellFromNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellFromTaskGet", (char*) shellFromTaskGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellFromTaskParentContextGet", (char*) shellFromTaskParentContextGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellGenericInit", (char*) shellGenericInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellHistory", (char*) shellHistory, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellIdVerify", (char*) shellIdVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBgndClose", (char*) shellInOutBgndClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBgndGet", (char*) shellInOutBgndGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBgndIoClose", (char*) shellInOutBgndIoClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBgndOpen", (char*) shellInOutBgndOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBgndRegister", (char*) shellInOutBgndRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingBlock", (char*) shellInOutBlockingBlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingBlockedDataGet", (char*) shellInOutBlockingBlockedDataGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingClose", (char*) shellInOutBlockingClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingDataSet", (char*) shellInOutBlockingDataSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingGet", (char*) shellInOutBlockingGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingOnDataClose", (char*) shellInOutBlockingOnDataClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingOpen", (char*) shellInOutBlockingOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutBlockingUnblock", (char*) shellInOutBlockingUnblock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutGet", (char*) shellInOutGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutInitialGet", (char*) shellInOutInitialGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutInputHookAdd", (char*) shellInOutInputHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutInputHookDelete", (char*) shellInOutInputHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutInputHookSet", (char*) shellInOutInputHookSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutInputHookUnset", (char*) shellInOutInputHookUnset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutInputUniqueCheck", (char*) shellInOutInputUniqueCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutMasterPtyGet", (char*) shellInOutMasterPtyGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutRedirectClose", (char*) shellInOutRedirectClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutRedirectOpen", (char*) shellInOutRedirectOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutRedirectRestore", (char*) shellInOutRedirectRestore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutRedirectScript", (char*) shellInOutRedirectScript, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutRedirectSet", (char*) shellInOutRedirectSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutSet", (char*) shellInOutSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutSlavePtyGet", (char*) shellInOutSlavePtyGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInOutUse", (char*) shellInOutUse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalArgStackAllocate", (char*) shellInternalArgStackAllocate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalArgumentEval", (char*) shellInternalArgumentEval, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalDataSymbolGet", (char*) shellInternalDataSymbolGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalDecValueDisplay", (char*) shellInternalDecValueDisplay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalFuncDoubleArgAdd", (char*) shellInternalFuncDoubleArgAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalFuncFloatArgAdd", (char*) shellInternalFuncFloatArgAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalFuncIntArgAdd", (char*) shellInternalFuncIntArgAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalFuncLLongArgAdd", (char*) shellInternalFuncLLongArgAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalFunctionCall", (char*) shellInternalFunctionCall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalHexValueDisplay", (char*) shellInternalHexValueDisplay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalKernelSymbolCreate", (char*) shellInternalKernelSymbolCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalOptFree", (char*) shellInternalOptFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalOptGet", (char*) shellInternalOptGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrSpaceTokenize", (char*) shellInternalStrSpaceTokenize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrToChar", (char*) shellInternalStrToChar, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrToFloat", (char*) shellInternalStrToFloat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrToInt", (char*) shellInternalStrToInt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrToInt2", (char*) shellInternalStrToInt2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrToInt32", (char*) shellInternalStrToInt32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrTokenize", (char*) shellInternalStrTokenize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalStrUnquote", (char*) shellInternalStrUnquote, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalSymTblFromRtpGet", (char*) shellInternalSymTblFromRtpGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalSymTblFromTaskGet", (char*) shellInternalSymTblFromTaskGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalSymbolDisplay", (char*) shellInternalSymbolDisplay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalSymbolGet", (char*) shellInternalSymbolGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalSymbolsResolve", (char*) shellInternalSymbolsResolve, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalTaskNameMatch", (char*) shellInternalTaskNameMatch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalTextSymbolGet", (char*) shellInternalTextSymbolGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInternalValueDisplay", (char*) shellInternalValueDisplay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpByNameFind", (char*) shellInterpByNameFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCInit", (char*) shellInterpCInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_create_buffer", (char*) shellInterpC_create_buffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_delete_buffer", (char*) shellInterpC_delete_buffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_flush_buffer", (char*) shellInterpC_flush_buffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_init_buffer", (char*) shellInterpC_init_buffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_load_buffer_state", (char*) shellInterpC_load_buffer_state, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_scan_buffer", (char*) shellInterpC_scan_buffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_scan_bytes", (char*) shellInterpC_scan_bytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_scan_string", (char*) shellInterpC_scan_string, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpC_switch_to_buffer", (char*) shellInterpC_switch_to_buffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCin", (char*) &shellInterpCin, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellInterpCleng", (char*) &shellInterpCleng, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "shellInterpClex", (char*) shellInterpClex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCmdLibInit", (char*) shellInterpCmdLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCout", (char*) &shellInterpCout, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellInterpCparse", (char*) shellInterpCparse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCrestart", (char*) shellInterpCrestart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCtext", (char*) &shellInterpCtext, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "shellInterpCtxCreate", (char*) shellInterpCtxCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpCtxGet", (char*) shellInterpCtxGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpDefaultNameGet", (char*) shellInterpDefaultNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpDelete", (char*) shellInterpDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpEvaluate", (char*) shellInterpEvaluate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpLibInit", (char*) shellInterpLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpNameGet", (char*) shellInterpNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpPromptDftSet", (char*) shellInterpPromptDftSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpPromptGet", (char*) shellInterpPromptGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpPromptSet", (char*) shellInterpPromptSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpRegister", (char*) shellInterpRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpRestart", (char*) shellInterpRestart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpSet", (char*) shellInterpSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInterpSwitch", (char*) shellInterpSwitch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLibInit", (char*) shellLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLineLenGet", (char*) shellLineLenGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLock", (char*) shellLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLoginInstall", (char*) shellLoginInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLogout", (char*) shellLogout, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLogout2", (char*) shellLogout2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLogoutInstall", (char*) shellLogoutInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMaxSessionsSet", (char*) shellMaxSessionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemAllRegFree", (char*) shellMemAllRegFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemCalloc", (char*) shellMemCalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemFree", (char*) shellMemFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemLibInit", (char*) shellMemLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemMalloc", (char*) shellMemMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemRealloc", (char*) shellMemRealloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemRegAllFree", (char*) shellMemRegAllFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemRegFree", (char*) shellMemRegFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemRegMalloc", (char*) shellMemRegMalloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemRegister", (char*) shellMemRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemStrdup", (char*) shellMemStrdup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemStringAdd", (char*) shellMemStringAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemStringFree", (char*) shellMemStringFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemStringIsAllocated", (char*) shellMemStringIsAllocated, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemStringShow", (char*) shellMemStringShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellMemUnregister", (char*) shellMemUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellNext", (char*) shellNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellOutputLock", (char*) shellOutputLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellOutputUnlock", (char*) shellOutputUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellParserControl", (char*) shellParserControl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPrint", (char*) shellPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPrintErr", (char*) shellPrintErr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptFmtDftSet", (char*) shellPromptFmtDftSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptFmtSet", (char*) shellPromptFmtSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptFmtStrAdd", (char*) shellPromptFmtStrAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptGet", (char*) shellPromptGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptLibInit", (char*) shellPromptLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptPrint", (char*) shellPromptPrint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptSet", (char*) shellPromptSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellRemoteConfigStr", (char*) &shellRemoteConfigStr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellResourceReleaseHookAdd", (char*) shellResourceReleaseHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellRestart", (char*) shellRestart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellScriptAbort", (char*) shellScriptAbort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellScriptNoAbort", (char*) shellScriptNoAbort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellSecureInit", (char*) shellSecureInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTask", (char*) shellTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultBaseNameGet", (char*) shellTaskDefaultBaseNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultBaseNameSet", (char*) shellTaskDefaultBaseNameSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultOptionsGet", (char*) shellTaskDefaultOptionsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultOptionsSet", (char*) shellTaskDefaultOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultPriorityGet", (char*) shellTaskDefaultPriorityGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultPrioritySet", (char*) shellTaskDefaultPrioritySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultStackSizeGet", (char*) shellTaskDefaultStackSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskDefaultStackSizeSet", (char*) shellTaskDefaultStackSizeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskGet", (char*) shellTaskGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskIdDefault", (char*) shellTaskIdDefault, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTerminate", (char*) shellTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxAttach", (char*) shellWorkingMemCtxAttach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxAttachedShow", (char*) shellWorkingMemCtxAttachedShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxCurrentGet", (char*) shellWorkingMemCtxCurrentGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxCurrentSet", (char*) shellWorkingMemCtxCurrentSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxDetach", (char*) shellWorkingMemCtxDetach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxDuplicate", (char*) shellWorkingMemCtxDuplicate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxGet", (char*) shellWorkingMemCtxGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxIdConvert", (char*) shellWorkingMemCtxIdConvert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxLastGet", (char*) shellWorkingMemCtxLastGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellWorkingMemCtxRtnSet", (char*) shellWorkingMemCtxRtnSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "show", (char*) show, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "showLoggerInfo", (char*) showLoggerInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "showRtnTbl", (char*) &showRtnTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "shutdown", (char*) shutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigEvtRtn", (char*) &sigEvtRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sigFfsMsb", (char*) sigFfsMsb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigInit", (char*) sigInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigPendDestroy", (char*) sigPendDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigPendInit", (char*) sigPendInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigPendKill", (char*) sigPendKill, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigaction", (char*) sigaction, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigaddset", (char*) sigaddset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigblock", (char*) sigblock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigdelset", (char*) sigdelset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigemptyset", (char*) sigemptyset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigfillset", (char*) sigfillset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigismember", (char*) sigismember, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "signal", (char*) signal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigpending", (char*) sigpending, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigprocmask", (char*) sigprocmask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigqueue", (char*) sigqueue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigqueueInit", (char*) sigqueueInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigreturn", (char*) sigreturn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigsetjmp", (char*) sigsetjmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigsetmask", (char*) sigsetmask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigsuspend", (char*) sigsuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigtimedwait", (char*) sigtimedwait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigvec", (char*) sigvec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigwait", (char*) sigwait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigwaitinfo", (char*) sigwaitinfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sin", (char*) sin, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sincos", (char*) sincos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sinh", (char*) sinh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sioChanConnect_desc", (char*) &sioChanConnect_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sioChanGet_desc", (char*) &sioChanGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sioEnable_desc", (char*) &sioEnable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sioIntEnable_desc", (char*) &sioIntEnable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sioNextChannelNumberAssign", (char*) sioNextChannelNumberAssign, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sizeNodesAlloc", (char*) sizeNodesAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllCount", (char*) sllCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllEach", (char*) sllEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllGet", (char*) sllGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllInit", (char*) sllInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllPrevious", (char*) sllPrevious, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllPutAtHead", (char*) sllPutAtHead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllPutAtTail", (char*) sllPutAtTail, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllRemove", (char*) sllRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllTerminate", (char*) sllTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "smMemPartAddToPoolRtn", (char*) &smMemPartAddToPoolRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "smMemPartAllocRtn", (char*) &smMemPartAllocRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "smMemPartFindMaxRtn", (char*) &smMemPartFindMaxRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smMemPartFreeRtn", (char*) &smMemPartFreeRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "smMemPartOptionsSetRtn", (char*) &smMemPartOptionsSetRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smMemPartReallocRtn", (char*) &smMemPartReallocRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smMemPartShowRtn", (char*) &smMemPartShowRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjPoolMinusOne", (char*) &smObjPoolMinusOne, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjTaskDeleteFailRtn", (char*) &smObjTaskDeleteFailRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjTcbFreeFailRtn", (char*) &smObjTcbFreeFailRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjTcbFreeRtn", (char*) &smObjTcbFreeRtn, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "snprintf", (char*) snprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "so", (char*) so, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sockLibAdd", (char*) sockLibAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sockLibInit", (char*) sockLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sockLibMap", (char*) &sockLibMap, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "socket", (char*) socket, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "socketDevHdr", (char*) &socketDevHdr, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "socket_test", (char*) socket_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soft_watchdog_test", (char*) soft_watchdog_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soft_watchdog_test2", (char*) soft_watchdog_test2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sp", (char*) sp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spTaskOptions", (char*) &spTaskOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spTaskPriority", (char*) &spTaskPriority, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spTaskStackSize", (char*) &spTaskStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "speaker_test", (char*) speaker_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockIsrEhcd", (char*) &spinLockIsrEhcd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spinLockIsrGive", (char*) spinLockIsrGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockIsrInit", (char*) spinLockIsrInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockIsrTake", (char*) spinLockIsrTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockRestrict", (char*) spinLockRestrict, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockTaskGive", (char*) spinLockTaskGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockTaskInit", (char*) spinLockTaskInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spinLockTaskTake", (char*) spinLockTaskTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sprintf", (char*) sprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spy", (char*) spy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyClkStart", (char*) spyClkStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyClkStop", (char*) spyClkStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyHelp", (char*) spyHelp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyReport", (char*) spyReport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyStop", (char*) spyStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyTask", (char*) spyTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sqrt", (char*) sqrt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "srand", (char*) srand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sscanf", (char*) sscanf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stat", (char*) stat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "statSymTbl", (char*) &statSymTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "statfs", (char*) statfs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "statfs64", (char*) statfs64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "std_test", (char*) std_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioFp", (char*) stdioFp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioFpCreate", (char*) stdioFpCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioFpDestroy", (char*) stdioFpDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioInit", (char*) stdioInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stopApplLogger", (char*) stopApplLogger, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strFree", (char*) strFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcasecmp", (char*) strcasecmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcat", (char*) strcat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strchr", (char*) strchr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcmp", (char*) strcmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcoll", (char*) strcoll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcpy", (char*) strcpy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcspn", (char*) strcspn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strdup", (char*) strdup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strerror", (char*) strerror, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strerrorIf", (char*) strerrorIf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strerror_r", (char*) strerror_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strftime", (char*) strftime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strlcpy", (char*) strlcpy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strlen", (char*) strlen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncasecmp", (char*) strncasecmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncat", (char*) strncat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncmp", (char*) strncmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncpy", (char*) strncpy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strpbrk", (char*) strpbrk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strrchr", (char*) strrchr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strspn", (char*) strspn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strstr", (char*) strstr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtod", (char*) strtod, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtok", (char*) strtok, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtok_r", (char*) strtok_r, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtol", (char*) strtol, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtoul", (char*) strtoul, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strxfrm", (char*) strxfrm, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "substrcmp", (char*) substrcmp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "swab", (char*) swab, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symAdd", (char*) symAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symByCNameFind", (char*) symByCNameFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symByValueAndTypeFind", (char*) symByValueAndTypeFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symByValueFind", (char*) symByValueFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symEach", (char*) symEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByName", (char*) symFindByName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByNameAndType", (char*) symFindByNameAndType, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByValue", (char*) symFindByValue, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByValueAndType", (char*) symFindByValueAndType, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindSymbol", (char*) symFindSymbol, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFree", (char*) symFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symGroupDefault", (char*) &symGroupDefault, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "symLibInit", (char*) symLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symListGet", (char*) symListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symLkupPgSz", (char*) &symLkupPgSz, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "symName", (char*) symName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symNameGet", (char*) symNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symRegister", (char*) symRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symRemove", (char*) symRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symShow", (char*) symShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symShowInit", (char*) symShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblAdd", (char*) symTblAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblCreate", (char*) symTblCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblDelete", (char*) symTblDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblRemove", (char*) symTblRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblShutdown", (char*) symTblShutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblSymSetRemove", (char*) symTblSymSetRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTypeGet", (char*) symTypeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTypeToStringConvert", (char*) symTypeToStringConvert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symValueGet", (char*) symValueGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "syncLoadRtn", (char*) &syncLoadRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "syncSymAddRtn", (char*) &syncSymAddRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "syncSymRemoveRtn", (char*) &syncSymRemoveRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "syncUnldRtn", (char*) &syncUnldRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysAbsSymPhysMemBottom", (char*) 0x00100000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "sysAbsSymPhysMemSize", (char*) 0x7bf00000, 0, 0, SYM_GLOBAL | SYM_ABS},
        {{NULL}, "sysAdaEnable", (char*) &sysAdaEnable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysAddGdt", (char*) sysAddGdt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBootFile", (char*) &sysBootFile, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysBootHost", (char*) &sysBootHost, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysBootLine", (char*) &sysBootLine, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysBootParams", (char*) &sysBootParams, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysBp", (char*) &sysBp, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysBspDevFilter_desc", (char*) &sysBspDevFilter_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysBspRev", (char*) sysBspRev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBus", (char*) &sysBus, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysBusIntAck", (char*) sysBusIntAck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBusIntGen", (char*) sysBusIntGen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBusTas", (char*) sysBusTas, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBusToLocalAdrs", (char*) sysBusToLocalAdrs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkConnect", (char*) sysClkConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkDevUnitNo", (char*) &sysClkDevUnitNo, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysClkDisable", (char*) sysClkDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkEnable", (char*) sysClkEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkHandleGet", (char*) sysClkHandleGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkInit", (char*) sysClkInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkRateGet", (char*) sysClkRateGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkRateSet", (char*) sysClkRateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkTimerNo", (char*) &sysClkTimerNo, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCoprocessor", (char*) &sysCoprocessor, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysCplusEnable", (char*) &sysCplusEnable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysCpu", (char*) &sysCpu, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCpuId", (char*) &sysCpuId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCpuProbe", (char*) sysCpuProbe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysCr3", (char*) &sysCr3, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCsExc", (char*) &sysCsExc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCsInt", (char*) &sysCsInt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCsSuper", (char*) &sysCsSuper, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysCsUser", (char*) &sysCsUser, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysDelay", (char*) sysDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysDsSuper", (char*) &sysDsSuper, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysDsUser", (char*) &sysDsUser, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysExcMsg", (char*) &sysExcMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysFlags", (char*) &sysFlags, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysGdt", (char*) sysGdt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysGdtr", (char*) sysGdtr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysHwInit", (char*) sysHwInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysHwInit0", (char*) sysHwInit0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysHwInit2", (char*) sysHwInit2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIchAtaGive", (char*) sysIchAtaGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIchAtaInit", (char*) sysIchAtaInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIchAtaInit2", (char*) sysIchAtaInit2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIchAtaWait", (char*) sysIchAtaWait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInByte", (char*) sysInByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInLong", (char*) sysInLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInLongString", (char*) sysInLongString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInWord", (char*) sysInWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInWordString", (char*) sysInWordString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInit", (char*) sysInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInitGDT", (char*) sysInitGDT, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInstParamTable", (char*) &sysInstParamTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysIntDisablePIC", (char*) sysIntDisablePIC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntEnablePIC", (char*) sysIntEnablePIC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntEoiGet", (char*) sysIntEoiGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntIdtType", (char*) &sysIntIdtType, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntInitPIC", (char*) sysIntInitPIC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntLevel", (char*) sysIntLevel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntLock", (char*) sysIntLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntLvlDisableRtn", (char*) &sysIntLvlDisableRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntLvlEnableRtn", (char*) &sysIntLvlEnableRtn, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntUnlock", (char*) sysIntUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInumTbl", (char*) &sysInumTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysInumTblNumEnt", (char*) &sysInumTblNumEnt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysLoadGdt", (char*) sysLoadGdt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysLocalToBusAdrs", (char*) sysLocalToBusAdrs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMailboxConnect", (char*) sysMailboxConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMailboxEnable", (char*) sysMailboxEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMemTop", (char*) sysMemTop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMmuMapAdd", (char*) sysMmuMapAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysModel", (char*) sysModel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysNetMacNVRamAddrGet", (char*) sysNetMacNVRamAddrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysNetPciInit", (char*) sysNetPciInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysNvRamGet", (char*) sysNvRamGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysNvRamSet", (char*) sysNvRamSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOSMGdtScratch", (char*) &sysOSMGdtScratch, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysOSMGdtScratchCurrent", (char*) &sysOSMGdtScratchCurrent, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysOSMLdt", (char*) &sysOSMLdt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysOSMLdtCurrent", (char*) &sysOSMLdtCurrent, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysOSMTaskGateInit", (char*) sysOSMTaskGateInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOutByte", (char*) sysOutByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOutLong", (char*) sysOutLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOutLongString", (char*) sysOutLongString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOutWord", (char*) sysOutWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOutWordString", (char*) sysOutWordString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysPciIvecToIrq", (char*) sysPciIvecToIrq, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysPhysMemDesc", (char*) &sysPhysMemDesc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysPhysMemDescNumEnt", (char*) &sysPhysMemDescNumEnt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysPhysMemTop", (char*) sysPhysMemTop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysProcNum", (char*) &sysProcNum, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysProcNumGet", (char*) sysProcNumGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysProcNumSet", (char*) sysProcNumSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysProcessor", (char*) &sysProcessor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysReboot", (char*) sysReboot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialChanConnect", (char*) sysSerialChanConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialChanGet", (char*) sysSerialChanGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialConnectAll", (char*) sysSerialConnectAll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSsUser", (char*) &sysSsUser, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysStart", (char*) sysStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysStartType", (char*) &sysStartType, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysStrayInt", (char*) sysStrayInt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysStrayIntCount", (char*) &sysStrayIntCount, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysSymPhysMemBottom", (char*) &sysSymPhysMemBottom, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysSymPhysMemSize", (char*) &sysSymPhysMemSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysSymTbl", (char*) &sysSymTbl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysTextProtect", (char*) &sysTextProtect, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysToMonitor", (char*) sysToMonitor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysTss", (char*) &sysTss, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysTssCurrent", (char*) &sysTssCurrent, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysUsDelay", (char*) sysUsDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysVmContext", (char*) &sysVmContext, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysWait", (char*) sysWait, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysWarmAtaCtrl", (char*) &sysWarmAtaCtrl, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysWarmAtaDrive", (char*) &sysWarmAtaDrive, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysWarmFdDrive", (char*) &sysWarmFdDrive, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysWarmFdType", (char*) &sysWarmFdType, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysWarmTffsDrive", (char*) &sysWarmTffsDrive, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysWarmType", (char*) &sysWarmType, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysctl", (char*) sysctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctlCtxList", (char*) &sysctlCtxList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysctlInit", (char*) sysctlInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl__children", (char*) &sysctl__children, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysctl_add_oid", (char*) sysctl_add_oid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_add_oid_internal", (char*) sysctl_add_oid_internal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_ctx_entry_add", (char*) sysctl_ctx_entry_add, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_ctx_entry_find", (char*) sysctl_ctx_entry_find, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_ctx_free", (char*) sysctl_ctx_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_ctx_init", (char*) sysctl_ctx_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_find_oid", (char*) sysctl_find_oid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_handle_int", (char*) sysctl_handle_int, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_handle_long", (char*) sysctl_handle_long, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_handle_opaque", (char*) sysctl_handle_opaque, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_handle_reg", (char*) sysctl_handle_reg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_handle_string", (char*) sysctl_handle_string, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_node", (char*) &sysctl_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysctl_register_oid", (char*) sysctl_register_oid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_remove_oid", (char*) sysctl_remove_oid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_sysctl_debug_dump_node", (char*) sysctl_sysctl_debug_dump_node, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctl_unregister_oid", (char*) sysctl_unregister_oid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctlbyname", (char*) sysctlbyname, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysctlnametomib", (char*) sysctlnametomib, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "system", (char*) system, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tCanReceive2", (char*) tCanReceive2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tCntComSync", (char*) tCntComSync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tComRecv", (char*) tComRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tExcTaskExcStk", (char*) &tExcTaskExcStk, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tExcTaskStk", (char*) &tExcTaskStk, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tExcTaskTcb", (char*) &tExcTaskTcb, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tPciCan", (char*) tPciCan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tPciCan2", (char*) tPciCan2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tPciIo", (char*) tPciIo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tTcpPerformRecv", (char*) tTcpPerformRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tTcpServerRecv", (char*) tTcpServerRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tTestSem", (char*) tTestSem, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tUdpBroadcastRecv", (char*) tUdpBroadcastRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tUdpGroupRecv", (char*) tUdpGroupRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tUdpServerRecv", (char*) tUdpServerRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tagCheckEvaluateAsserts", (char*) tagCheckEvaluateAsserts, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tagCheckModuleAdd", (char*) tagCheckModuleAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tagCheckModuleDel", (char*) tagCheckModuleDel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tagCheckStatementAdd", (char*) tagCheckStatementAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taglist", (char*) &taglist, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tan", (char*) tan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tanh", (char*) tanh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskATenable", (char*) &taskATenable, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskActivate", (char*) taskActivate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskArgsGet", (char*) taskArgsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskArgsSet", (char*) taskArgsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskBpHook", (char*) &taskBpHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskBpHookSet", (char*) taskBpHookSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskClassId", (char*) &taskClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskCont", (char*) taskCont, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCpuAffinityGet", (char*) taskCpuAffinityGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCpuAffinitySet", (char*) taskCpuAffinitySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCpuLock", (char*) taskCpuLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCpuUnlock", (char*) taskCpuUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCpuUnlockNoResched", (char*) taskCpuUnlockNoResched, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreat", (char*) taskCreat, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreate", (char*) taskCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookAdd", (char*) taskCreateHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookDelete", (char*) taskCreateHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookInit", (char*) taskCreateHookInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateLibInit", (char*) taskCreateLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateTable", (char*) &taskCreateTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskCreateWithGuard", (char*) taskCreateWithGuard, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDelay", (char*) taskDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDelete", (char*) taskDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteForce", (char*) taskDeleteForce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteHookAdd", (char*) taskDeleteHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteHookDelete", (char*) taskDeleteHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteTable", (char*) &taskDeleteTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskDestroy", (char*) taskDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskEach", (char*) taskEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdCurrent", (char*) &taskIdCurrent, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskIdDefault", (char*) taskIdDefault, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdFigure", (char*) taskIdFigure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdListGet", (char*) taskIdListGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdListSort", (char*) taskIdListSort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdSelf", (char*) taskIdSelf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdVerify", (char*) taskIdVerify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInfoGet", (char*) taskInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInit", (char*) taskInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInitExcStk", (char*) taskInitExcStk, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInitialize", (char*) taskInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIsDelayed", (char*) taskIsDelayed, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIsPended", (char*) taskIsPended, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIsReady", (char*) taskIsReady, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIsStopped", (char*) taskIsStopped, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIsSuspended", (char*) taskIsSuspended, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskKerExcStackSize", (char*) &taskKerExcStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskKerExcStkOverflowSize", (char*) &taskKerExcStkOverflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskKerExecStkOverflowSize", (char*) &taskKerExecStkOverflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskKerExecStkUnderflowSize", (char*) &taskKerExecStkUnderflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskLibInit", (char*) taskLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskListCount", (char*) taskListCount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskLock", (char*) taskLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskName", (char*) taskName, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskNameToId", (char*) taskNameToId, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsGet", (char*) taskOptionsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsSet", (char*) taskOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsString", (char*) taskOptionsString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPriNormalGet", (char*) taskPriNormalGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPriorityGet", (char*) taskPriorityGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPrioritySet", (char*) taskPrioritySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegName", (char*) &taskRegName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskRegsFmt", (char*) &taskRegsFmt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskRegsGet", (char*) taskRegsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsInit", (char*) taskRegsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsModify", (char*) taskRegsModify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsSet", (char*) taskRegsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsShow", (char*) taskRegsShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskReservedFieldGet", (char*) taskReservedFieldGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskReservedFieldSet", (char*) taskReservedFieldSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskReservedNumAllot", (char*) taskReservedNumAllot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskReset", (char*) taskReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRestart", (char*) taskRestart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskResume", (char*) taskResume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRtnValueSet", (char*) taskRtnValueSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSRSet", (char*) taskSRSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSafe", (char*) taskSafe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSchedInfoGet", (char*) taskSchedInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskShow", (char*) taskShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskShowInit", (char*) taskShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSpareFieldGet", (char*) taskSpareFieldGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSpareFieldSet", (char*) taskSpareFieldSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSpareNumAllot", (char*) taskSpareNumAllot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSpawn", (char*) taskSpawn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStackAllot", (char*) taskStackAllot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStackSizeGet", (char*) taskStackSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStatusString", (char*) taskStatusString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStop", (char*) taskStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStopForce", (char*) taskStopForce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStopMsg", (char*) &taskStopMsg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskSuspend", (char*) taskSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookAdd", (char*) taskSwapHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookAttach", (char*) taskSwapHookAttach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookDelete", (char*) taskSwapHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookDetach", (char*) taskSwapHookDetach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapReference", (char*) &taskSwapReference, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskSwapTable", (char*) &taskSwapTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskSwitchHookAdd", (char*) taskSwitchHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwitchHookDelete", (char*) taskSwitchHookDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwitchTable", (char*) &taskSwitchTable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskTcb", (char*) taskTcb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskTerminate", (char*) taskTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUndelay", (char*) taskUndelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUnlock", (char*) taskUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUnsafe", (char*) taskUnsafe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUsrExcStackSize", (char*) &taskUsrExcStackSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskUsrExcStkOverflowSize", (char*) &taskUsrExcStkOverflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskUsrExecStkOverflowSize", (char*) &taskUsrExecStkOverflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskUsrExecStkUnderflowSize", (char*) &taskUsrExecStkUnderflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskVarAdd", (char*) taskVarAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarDelete", (char*) taskVarDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarGet", (char*) taskVarGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarInfo", (char*) taskVarInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarInit", (char*) taskVarInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarSet", (char*) taskVarSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskWaitShow", (char*) taskWaitShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskWaitShowCoreRtn", (char*) taskWaitShowCoreRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcbReserveBitmap", (char*) &tcbReserveBitmap, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcbSpareBitmap", (char*) &tcbSpareBitmap, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_client", (char*) tcp_client, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_rx_performance", (char*) tcp_rx_performance, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_server", (char*) tcp_server, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_tx_performance", (char*) tcp_tx_performance, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "td", (char*) td, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ti", (char*) ti, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tick64Get", (char*) tick64Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tick64Set", (char*) tick64Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickAnnounce", (char*) tickAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickAnnounceHookAdd", (char*) tickAnnounceHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickGet", (char*) tickGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickQHead", (char*) &tickQHead, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tickSet", (char*) tickSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "time", (char*) time, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timer0_callback", (char*) timer0_callback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timer0_test", (char*) timer0_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timex", (char*) timex, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexClear", (char*) timexClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexFunc", (char*) timexFunc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexHelp", (char*) timexHelp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexInit", (char*) timexInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexN", (char*) timexN, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexPost", (char*) timexPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexPre", (char*) timexPre, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexShow", (char*) timexShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tip", (char*) tip, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tipConfigString", (char*) &tipConfigString, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tipEscapeChar", (char*) &tipEscapeChar, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tipLibInit", (char*) tipLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tipStart", (char*) tipStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tmpfile", (char*) tmpfile, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tmpnam", (char*) tmpnam, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tolower", (char*) tolower, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "toupper", (char*) toupper, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tr", (char*) tr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trcDefaultArgs", (char*) &trcDefaultArgs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "trcLibFuncs", (char*) &trcLibFuncs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "trcStack", (char*) trcStack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trcStackCtxTrace", (char*) trcStackCtxTrace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trcStackTrace", (char*) trcStackTrace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trcSyscallCheck", (char*) trcSyscallCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trunc", (char*) trunc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ts", (char*) ts, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tt", (char*) tt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ttyDevCreate", (char*) ttyDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ttyDrv", (char*) ttyDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tw", (char*) tw, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyAbortFuncGet", (char*) tyAbortFuncGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyAbortFuncSet", (char*) tyAbortFuncSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyAbortGet", (char*) tyAbortGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyAbortSet", (char*) tyAbortSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyBackspaceChar", (char*) &tyBackspaceChar, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tyBackspaceSet", (char*) tyBackspaceSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDeleteLineChar", (char*) &tyDeleteLineChar, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tyDeleteLineSet", (char*) tyDeleteLineSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDevInit", (char*) tyDevInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDevRemove", (char*) tyDevRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDevTerminate", (char*) tyDevTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyEOFGet", (char*) tyEOFGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyEOFSet", (char*) tyEOFSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyEofChar", (char*) &tyEofChar, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tyIRd", (char*) tyIRd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyITx", (char*) tyITx, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyIoctl", (char*) tyIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyLibInit", (char*) tyLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyMonitorTrapSet", (char*) tyMonitorTrapSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyRead", (char*) tyRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyWrite", (char*) tyWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyXoffHookSet", (char*) tyXoffHookSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "uNum", (char*) &uNum, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "udpCommIfInit", (char*) udpCommIfInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udpRcv", (char*) udpRcv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_broadcast", (char*) udp_broadcast, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_client", (char*) udp_client, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_client_2", (char*) udp_client_2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_group", (char*) udp_group, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_server", (char*) udp_server, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_task", (char*) udp_task, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ungetc", (char*) ungetc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unld", (char*) unld, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unldByGroup", (char*) unldByGroup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unldByModuleId", (char*) unldByModuleId, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unldByNameAndPath", (char*) unldByNameAndPath, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unldLibInit", (char*) unldLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unlink", (char*) unlink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unmount", (char*) unmount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDeviceAddCallbackSet", (char*) usb2ClassDeviceAddCallbackSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDeviceCreate", (char*) usb2ClassDeviceCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDeviceDelCallbackSet", (char*) usb2ClassDeviceDelCallbackSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDeviceDelete", (char*) usb2ClassDeviceDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDeviceIsValid", (char*) usb2ClassDeviceIsValid, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDriverCreate", (char*) usb2ClassDriverCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ClassDriverDelete", (char*) usb2ClassDriverDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2DeviceDeleteHelperDeInit", (char*) usb2DeviceDeleteHelperDeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2DeviceDeleteHelperInit", (char*) usb2DeviceDeleteHelperInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2DeviceDeleteMsgPost", (char*) usb2DeviceDeleteMsgPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2DriverIsEmpty", (char*) usb2DriverIsEmpty, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2FindEndpoint", (char*) usb2FindEndpoint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2FindInterface", (char*) usb2FindInterface, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2HlpDebug", (char*) &usb2HlpDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "usb2MscBlkDevCreate", (char*) usb2MscBlkDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBlkDevIoctl", (char*) usb2MscBlkDevIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBlkDevMount", (char*) usb2MscBlkDevMount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBlkDevStatusCheck", (char*) usb2MscBlkDevStatusCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBlkDevUnmount", (char*) usb2MscBlkDevUnmount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkInTransfer", (char*) usb2MscBulkInTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkOnlyGetMaxLun", (char*) usb2MscBulkOnlyGetMaxLun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkOnlyMassStorageReset", (char*) usb2MscBulkOnlyMassStorageReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkOnlyResetEndpoints", (char*) usb2MscBulkOnlyResetEndpoints, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkOnlyResetRecovery", (char*) usb2MscBulkOnlyResetRecovery, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkOnlyTransport", (char*) usb2MscBulkOnlyTransport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkOutTransfer", (char*) usb2MscBulkOutTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscBulkTransfer", (char*) usb2MscBulkTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCBICommandBlockReset", (char*) usb2MscCBICommandBlockReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCBICommandTransfer", (char*) usb2MscCBICommandTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCBIResetRecovery", (char*) usb2MscCBIResetRecovery, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCBIStatusTransfer", (char*) usb2MscCBIStatusTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCBITransport", (char*) usb2MscCBITransport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCheckOptimalInterface", (char*) usb2MscCheckOptimalInterface, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCommandSetTransport", (char*) usb2MscCommandSetTransport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase10Test", (char*) usb2MscComplianceCase10Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase11Test", (char*) usb2MscComplianceCase11Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase12Test", (char*) usb2MscComplianceCase12Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase13Test", (char*) usb2MscComplianceCase13Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase1Test", (char*) usb2MscComplianceCase1Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase2Test", (char*) usb2MscComplianceCase2Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase3Test", (char*) usb2MscComplianceCase3Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase4Test", (char*) usb2MscComplianceCase4Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase5Test", (char*) usb2MscComplianceCase5Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase6Test", (char*) usb2MscComplianceCase6Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase7Test", (char*) usb2MscComplianceCase7Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase8Test", (char*) usb2MscComplianceCase8Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceCase9Test", (char*) usb2MscComplianceCase9Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceClassSpecificRequestTest", (char*) usb2MscComplianceClassSpecificRequestTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceErrorRecoveryTest", (char*) usb2MscComplianceErrorRecoveryTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceInquiryTest", (char*) usb2MscComplianceInquiryTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceInterfaceDescriptorTest", (char*) usb2MscComplianceInterfaceDescriptorTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogCBW", (char*) usb2MscComplianceLogCBW, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogCSW", (char*) usb2MscComplianceLogCSW, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogCurrentStatistics", (char*) usb2MscComplianceLogCurrentStatistics, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogError", (char*) usb2MscComplianceLogError, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogFinalStatistics", (char*) usb2MscComplianceLogFinalStatistics, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogHstStatus", (char*) usb2MscComplianceLogHstStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogInfo", (char*) usb2MscComplianceLogInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogLangId", (char*) usb2MscComplianceLogLangId, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceLogWarning", (char*) usb2MscComplianceLogWarning, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceModeSelect10Test", (char*) usb2MscComplianceModeSelect10Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceModeSelect6Test", (char*) usb2MscComplianceModeSelect6Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceModeSense10Test", (char*) usb2MscComplianceModeSense10Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceModeSense6Test", (char*) usb2MscComplianceModeSense6Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCompliancePowerUpTest", (char*) usb2MscCompliancePowerUpTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCompliancePreliminaryProcedure", (char*) usb2MscCompliancePreliminaryProcedure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCompliancePreventAllowMediumRemovalTest", (char*) usb2MscCompliancePreventAllowMediumRemovalTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceRead10Test", (char*) usb2MscComplianceRead10Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceRead12Test", (char*) usb2MscComplianceRead12Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceReadCapacityTest", (char*) usb2MscComplianceReadCapacityTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceReadTOCTest", (char*) usb2MscComplianceReadTOCTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceRecoveryProcedure", (char*) usb2MscComplianceRecoveryProcedure, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceRequestSense", (char*) usb2MscComplianceRequestSense, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceRequestSenseTest", (char*) usb2MscComplianceRequestSenseTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceSerialNumberTest", (char*) usb2MscComplianceSerialNumberTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceStartStopUnitTest", (char*) usb2MscComplianceStartStopUnitTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceTestDeviceAdd", (char*) usb2MscComplianceTestDeviceAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceTestDeviceRemove", (char*) usb2MscComplianceTestDeviceRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceTestUnitReadyTest", (char*) usb2MscComplianceTestUnitReadyTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceTransport", (char*) usb2MscComplianceTransport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceTransportCommon", (char*) usb2MscComplianceTransportCommon, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceVerify10Test", (char*) usb2MscComplianceVerify10Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceVerifySerialNumber", (char*) usb2MscComplianceVerifySerialNumber, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceWrite10Test", (char*) usb2MscComplianceWrite10Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscComplianceWrite12Test", (char*) usb2MscComplianceWrite12Test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscCompliancebCBLengthTest", (char*) usb2MscCompliancebCBLengthTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDebug", (char*) &usb2MscDebug, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "usb2MscDirectAccessDeviceAdd", (char*) usb2MscDirectAccessDeviceAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDirectAccessDeviceRemove", (char*) usb2MscDirectAccessDeviceRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDirectAccessInit", (char*) usb2MscDirectAccessInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDirectAccessOpen", (char*) usb2MscDirectAccessOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDirectAccessScsiPassThrough", (char*) usb2MscDirectAccessScsiPassThrough, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDirectAccessUnInit", (char*) usb2MscDirectAccessUnInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDrvInit", (char*) usb2MscDrvInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscDrvUnInit", (char*) usb2MscDrvUnInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscFindOptimalInterface", (char*) usb2MscFindOptimalInterface, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscFixupAsciiString", (char*) usb2MscFixupAsciiString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscGetTotalLun", (char*) usb2MscGetTotalLun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscInterruptInTransfer", (char*) usb2MscInterruptInTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscIsEndpointHalted", (char*) usb2MscIsEndpointHalted, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscResetDevice", (char*) usb2MscResetDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscResetEndpoint", (char*) usb2MscResetEndpoint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiCheckReady", (char*) usb2MscScsiCheckReady, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiFormatUnit", (char*) usb2MscScsiFormatUnit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiHandleSenseData", (char*) usb2MscScsiHandleSenseData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiInquiry", (char*) usb2MscScsiInquiry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiModeSense", (char*) usb2MscScsiModeSense, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiModeSense10", (char*) usb2MscScsiModeSense10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiModeSense6", (char*) usb2MscScsiModeSense6, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiRead10", (char*) usb2MscScsiRead10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiRead10Internal", (char*) usb2MscScsiRead10Internal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiReadCapacity10", (char*) usb2MscScsiReadCapacity10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiReadFormatCapacities", (char*) usb2MscScsiReadFormatCapacities, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiRequestSense", (char*) usb2MscScsiRequestSense, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiStartStopUnit", (char*) usb2MscScsiStartStopUnit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiTestUnitReady", (char*) usb2MscScsiTestUnitReady, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiWrite10", (char*) usb2MscScsiWrite10, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscScsiWrite10Internal", (char*) usb2MscScsiWrite10Internal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscStatusCheck", (char*) usb2MscStatusCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscTransport", (char*) usb2MscTransport, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscWriteProtectionCheck", (char*) usb2MscWriteProtectionCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscXbdEject", (char*) usb2MscXbdEject, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscXbdMediaTest", (char*) usb2MscXbdMediaTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscXbdMount", (char*) usb2MscXbdMount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscXbdTest", (char*) usb2MscXbdTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2MscXbdUnmount", (char*) usb2MscXbdUnmount, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ReleaseDevice", (char*) usb2ReleaseDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2ReleaseDriver", (char*) usb2ReleaseDriver, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2TakeDevice", (char*) usb2TakeDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2TakeDriver", (char*) usb2TakeDriver, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2VendorClassSpecific", (char*) usb2VendorClassSpecific, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2WindViewLog", (char*) usb2WindViewLog, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb2WvFilter", (char*) &usb2WvFilter, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "usbConfigCountGet", (char*) usbConfigCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbConfigDescrGet", (char*) usbConfigDescrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbDescrParse", (char*) usbDescrParse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbDescrParseSkip", (char*) usbDescrParseSkip, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAddBandwidth", (char*) usbEhcdAddBandwidth, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAddToFreeITDList", (char*) usbEhcdAddToFreeITDList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAddToFreeQHList", (char*) usbEhcdAddToFreeQHList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAddToFreeQTDList", (char*) usbEhcdAddToFreeQTDList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAddToFreeSITDList", (char*) usbEhcdAddToFreeSITDList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAlign", (char*) usbEhcdAlign, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAsynchScheduleDisable", (char*) usbEhcdAsynchScheduleDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdAsynchScheduleEnable", (char*) usbEhcdAsynchScheduleEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCalculateBusTime", (char*) usbEhcdCalculateBusTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCancelURB", (char*) usbEhcdCancelURB, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCheckBandwidth", (char*) usbEhcdCheckBandwidth, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdClearTTRequestComplete", (char*) usbEhcdClearTTRequestComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCopyRHInterruptData", (char*) usbEhcdCopyRHInterruptData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCreateInterruptTree", (char*) usbEhcdCreateInterruptTree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCreatePipe", (char*) usbEhcdCreatePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdCreateQTDs", (char*) usbEhcdCreateQTDs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdDeletePipe", (char*) usbEhcdDeletePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdDestroyInterruptTree", (char*) usbEhcdDestroyInterruptTree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdDisableHC", (char*) usbEhcdDisableHC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdExit", (char*) usbEhcdExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdFillQTDBuffer", (char*) usbEhcdFillQTDBuffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdFormEmptyQH", (char*) usbEhcdFormEmptyQH, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdFormEmptyQTD", (char*) usbEhcdFormEmptyQTD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdFreeAllLists", (char*) usbEhcdFreeAllLists, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGenerateITDs", (char*) usbEhcdGenerateITDs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGenerateSITDs", (char*) usbEhcdGenerateSITDs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGetFrameNumber", (char*) usbEhcdGetFrameNumber, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGetFreeITD", (char*) usbEhcdGetFreeITD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGetFreeQH", (char*) usbEhcdGetFreeQH, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGetFreeQTD", (char*) usbEhcdGetFreeQTD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdGetFreeSITD", (char*) usbEhcdGetFreeSITD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdISR", (char*) usbEhcdISR, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdInit", (char*) usbEhcdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdInstantiate", (char*) usbEhcdInstantiate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdInterruptHandler", (char*) usbEhcdInterruptHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdIsBandwidthAvailable", (char*) usbEhcdIsBandwidthAvailable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdIsRequestPending", (char*) usbEhcdIsRequestPending, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdLinkITDs", (char*) usbEhcdLinkITDs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdLinkSITDs", (char*) usbEhcdLinkSITDs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdModifyDefaultPipe", (char*) usbEhcdModifyDefaultPipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRHCancelURB", (char*) usbEhcdRHCancelURB, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRHDeletePipe", (char*) usbEhcdRHDeletePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRHSubmitURB", (char*) usbEhcdRHSubmitURB, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdResetTTRequestComplete", (char*) usbEhcdResetTTRequestComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhClearPortFeature", (char*) usbEhcdRhClearPortFeature, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhCreatePipe", (char*) usbEhcdRhCreatePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhGetHubDescriptor", (char*) usbEhcdRhGetHubDescriptor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhGetPortStatus", (char*) usbEhcdRhGetPortStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhProcessClassSpecificRequest", (char*) usbEhcdRhProcessClassSpecificRequest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhProcessControlRequest", (char*) usbEhcdRhProcessControlRequest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhProcessInterruptRequest", (char*) usbEhcdRhProcessInterruptRequest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhProcessStandardRequest", (char*) usbEhcdRhProcessStandardRequest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdRhSetPortFeature", (char*) usbEhcdRhSetPortFeature, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdSetBitRate", (char*) usbEhcdSetBitRate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdSubBandwidth", (char*) usbEhcdSubBandwidth, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdSubDeviceBandwidth", (char*) usbEhcdSubDeviceBandwidth, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdSubmitURB", (char*) usbEhcdSubmitURB, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdUnLinkITD", (char*) usbEhcdUnLinkITD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdUnLinkSITD", (char*) usbEhcdUnLinkSITD, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdUpdateBandwidth", (char*) usbEhcdUpdateBandwidth, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdUpdateITDData", (char*) usbEhcdUpdateITDData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdUpdateNonIsochStatusAndBytes", (char*) usbEhcdUpdateNonIsochStatusAndBytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbEhcdUpdateSITDData", (char*) usbEhcdUpdateSITDData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbExit", (char*) usbExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHidIdleSet", (char*) usbHidIdleSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHidProtocolSet", (char*) usbHidProtocolSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHidReportSet", (char*) usbHidReportSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstBusDeregister", (char*) usbHstBusDeregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstBusRegister", (char*) usbHstBusRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstClearFeature", (char*) usbHstClearFeature, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstCommonCallback", (char*) usbHstCommonCallback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstDriverDeregister", (char*) usbHstDriverDeregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstDriverRegister", (char*) usbHstDriverRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstGetConfiguration", (char*) usbHstGetConfiguration, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstGetDescriptor", (char*) usbHstGetDescriptor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstGetFrameNumber", (char*) usbHstGetFrameNumber, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstGetInterface", (char*) usbHstGetInterface, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstGetStatus", (char*) usbHstGetStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstHCDDeregister", (char*) usbHstHCDDeregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstHCDRegister", (char*) usbHstHCDRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstResetDevice", (char*) usbHstResetDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSelectiveResume", (char*) usbHstSelectiveResume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSelectiveSuspend", (char*) usbHstSelectiveSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSetBitRate", (char*) usbHstSetBitRate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSetConfiguration", (char*) usbHstSetConfiguration, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSetDescriptor", (char*) usbHstSetDescriptor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSetFeature", (char*) usbHstSetFeature, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSetInterface", (char*) usbHstSetInterface, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstSetSynchFrame", (char*) usbHstSetSynchFrame, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstURBCancel", (char*) usbHstURBCancel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstURBSubmit", (char*) usbHstURBSubmit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHstWaitUrbComplete", (char*) usbHstWaitUrbComplete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubExit", (char*) usbHubExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubGetRootHubHandle", (char*) usbHubGetRootHubHandle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubInit", (char*) usbHubInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubNodeIDGet", (char*) usbHubNodeIDGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubPollingIntervalGet", (char*) usbHubPollingIntervalGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubPollingIntervalSet", (char*) usbHubPollingIntervalSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbHubPortCntGet", (char*) usbHubPortCntGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbInit", (char*) usbInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbListFirst", (char*) usbListFirst, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbListLink", (char*) usbListLink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbListLinkProt", (char*) usbListLinkProt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbListNext", (char*) usbListNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbListUnlink", (char*) usbListUnlink, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbListUnlinkProt", (char*) usbListUnlinkProt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbLogMsg", (char*) usbLogMsg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbMemToPci", (char*) usbMemToPci, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbOhcdInit", (char*) usbOhcdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbOhciExit", (char*) usbOhciExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbOhciInstantiate", (char*) usbOhciInstantiate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbOhciPowerOffPorts", (char*) usbOhciPowerOffPorts, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciByteGet", (char*) usbPciByteGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciByteIn", (char*) usbPciByteIn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciByteOut", (char*) usbPciByteOut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciConfigHeaderGet", (char*) usbPciConfigHeaderGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciDwordGet", (char*) usbPciDwordGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciDwordIn", (char*) usbPciDwordIn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciDwordOut", (char*) usbPciDwordOut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciIntConnect", (char*) usbPciIntConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciIntRestore", (char*) usbPciIntRestore, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciMemFlush", (char*) usbPciMemFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciMemInvalidate", (char*) usbPciMemInvalidate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciMemioOffset", (char*) usbPciMemioOffset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciToMem", (char*) usbPciToMem, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciWordGet", (char*) usbPciWordGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciWordIn", (char*) usbPciWordIn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbPciWordOut", (char*) usbPciWordOut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbRecurringTime", (char*) usbRecurringTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbTransferTime", (char*) usbTransferTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCalculateBusTime", (char*) usbUhcdCalculateBusTime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCanIsoBeAccomodated", (char*) usbUhcdCanIsoBeAccomodated, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCancelRhRequest", (char*) usbUhcdCancelRhRequest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCancelUrb", (char*) usbUhcdCancelUrb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdClearPortFeature", (char*) usbUhcdClearPortFeature, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCleartdOnSysError", (char*) usbUhcdCleartdOnSysError, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCompletedTdHandler", (char*) usbUhcdCompletedTdHandler, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCopy", (char*) usbUhcdCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCreateFrameList", (char*) usbUhcdCreateFrameList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdCreatePipe", (char*) usbUhcdCreatePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdDeleteFrameList", (char*) usbUhcdDeleteFrameList, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdDeletePipe", (char*) usbUhcdDeletePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdDeleteQhContext", (char*) usbUhcdDeleteQhContext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdEnterCritical", (char*) usbUhcdEnterCritical, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdExit", (char*) usbUhcdExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFillIsoStatus", (char*) usbUhcdFillIsoStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFillNonisoStatus", (char*) usbUhcdFillNonisoStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFindHcdPipe", (char*) usbUhcdFindHcdPipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFindLinkForQh", (char*) usbUhcdFindLinkForQh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFindPosForIntQh", (char*) usbUhcdFindPosForIntQh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFindQlinkToTree", (char*) usbUhcdFindQlinkToTree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFindTreeBw", (char*) usbUhcdFindTreeBw, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFormEmptyPipe", (char*) usbUhcdFormEmptyPipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFormEmptyQh", (char*) usbUhcdFormEmptyQh, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFormEmptyTd", (char*) usbUhcdFormEmptyTd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdFreeTds", (char*) usbUhcdFreeTds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGdConfigDescriptor", (char*) &usbUhcdGdConfigDescriptor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "usbUhcdGdDeviceDescriptor", (char*) &usbUhcdGdDeviceDescriptor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "usbUhcdGetBit", (char*) usbUhcdGetBit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetBusState", (char*) usbUhcdGetBusState, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetConfiguration", (char*) usbUhcdGetConfiguration, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetCurrentEndpointDetails", (char*) usbUhcdGetCurrentEndpointDetails, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetDescriptor", (char*) usbUhcdGetDescriptor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetDetailsForEndpoints", (char*) usbUhcdGetDetailsForEndpoints, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetFrameNumber", (char*) usbUhcdGetFrameNumber, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetHubDescriptor", (char*) usbUhcdGetHubDescriptor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetHubStatus", (char*) usbUhcdGetHubStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetIsoTransferLength", (char*) usbUhcdGetIsoTransferLength, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetPortStatus", (char*) usbUhcdGetPortStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetStatus", (char*) usbUhcdGetStatus, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdGetTransferLength", (char*) usbUhcdGetTransferLength, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdHcReset", (char*) usbUhcdHcReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdInit", (char*) usbUhcdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdInstantiate", (char*) usbUhcdInstantiate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsBandwidthAvailable", (char*) usbUhcdIsBandwidthAvailable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsBitReset", (char*) usbUhcdIsBitReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsBitSet", (char*) usbUhcdIsBitSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsLinked", (char*) usbUhcdIsLinked, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsRequestPending", (char*) usbUhcdIsRequestPending, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsValidPipe", (char*) usbUhcdIsValidPipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdIsr", (char*) usbUhcdIsr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdLeaveCritical", (char*) usbUhcdLeaveCritical, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdLinkItds", (char*) usbUhcdLinkItds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdLinkQheadBetween", (char*) usbUhcdLinkQheadBetween, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdMakeFrameelementLE", (char*) usbUhcdMakeFrameelementLE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdMakeIsocTds", (char*) usbUhcdMakeIsocTds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdMakeQDLE", (char*) usbUhcdMakeQDLE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdMakeTDLE", (char*) usbUhcdMakeTDLE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdMakeTds", (char*) usbUhcdMakeTds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdMaxIsoBwLinkedTo", (char*) usbUhcdMaxIsoBwLinkedTo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdModifyDefaultPipe", (char*) usbUhcdModifyDefaultPipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdPortClearBit", (char*) usbUhcdPortClearBit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdPortSetBit", (char*) usbUhcdPortSetBit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdProcessCompletedTds", (char*) usbUhcdProcessCompletedTds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdProcessIsocTds", (char*) usbUhcdProcessIsocTds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdProcessRhControlTransfer", (char*) usbUhcdProcessRhControlTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdProcessRhInterruptTransfer", (char*) usbUhcdProcessRhInterruptTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdQueueRhRequest", (char*) usbUhcdQueueRhRequest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdReadReg", (char*) usbUhcdReadReg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdRegxClearBit", (char*) usbUhcdRegxClearBit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdRegxSetBit", (char*) usbUhcdRegxSetBit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdRhCreatePipe", (char*) usbUhcdRhCreatePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdRhDeletePipe", (char*) usbUhcdRhDeletePipe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdSetBitRate", (char*) usbUhcdSetBitRate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdSetConfiguration", (char*) usbUhcdSetConfiguration, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdSetPortFeature", (char*) usbUhcdSetPortFeature, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdSubmitUrb", (char*) usbUhcdSubmitUrb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdUnlinkItds", (char*) usbUhcdUnlinkItds, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhcdWriteReg", (char*) usbUhcdWriteReg, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhciDelay", (char*) usbUhciDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbUhciLog2", (char*) usbUhciLog2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbVxbRootHubAdd", (char*) usbVxbRootHubAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbVxbRootHubRemove", (char*) usbVxbRootHubRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usb_test", (char*) usb_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdAddressGet", (char*) usbdAddressGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdAddressSet", (char*) usbdAddressSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdBusCntGet", (char*) usbdBusCntGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdBusCountGet", (char*) usbdBusCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdBusStateSet", (char*) usbdBusStateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdClientRegister", (char*) usbdClientRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdClientUnregister", (char*) usbdClientUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdConfigurationGet", (char*) usbdConfigurationGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdConfigurationSet", (char*) usbdConfigurationSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdCurrentFrameGet", (char*) usbdCurrentFrameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdDescriptorGet", (char*) usbdDescriptorGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdDescriptorSet", (char*) usbdDescriptorSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdDynamicAttachRegister", (char*) usbdDynamicAttachRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdDynamicAttachUnRegister", (char*) usbdDynamicAttachUnRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdExit", (char*) usbdExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdFeatureClear", (char*) usbdFeatureClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdFeatureSet", (char*) usbdFeatureSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdFrameWindowGet", (char*) usbdFrameWindowGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdHubPortCountGet", (char*) usbdHubPortCountGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdInit", (char*) usbdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdInitialize", (char*) usbdInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdInterfaceGet", (char*) usbdInterfaceGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdInterfaceSet", (char*) usbdInterfaceSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdMngmtCallbackSet", (char*) usbdMngmtCallbackSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdNodeIdGet", (char*) usbdNodeIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdNodeInfoGet", (char*) usbdNodeInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdOsalDbg", (char*) &usbdOsalDbg, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "usbdPipeCreate", (char*) usbdPipeCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdPipeDestroy", (char*) usbdPipeDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdRootNodeIDGet", (char*) usbdRootNodeIDGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdRootNodeIdGet", (char*) usbdRootNodeIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdShutdown", (char*) usbdShutdown, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdStatisticsGet", (char*) usbdStatisticsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdStatusGet", (char*) usbdStatusGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdSynchFrameGet", (char*) usbdSynchFrameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdTransfer", (char*) usbdTransfer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdTransferAbort", (char*) usbdTransferAbort, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdTranslateDeviceHandle", (char*) usbdTranslateDeviceHandle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdTranslationInit", (char*) usbdTranslationInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdVendorSpecific", (char*) usbdVendorSpecific, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbdVersionGet", (char*) usbdVersionGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuClientList", (char*) &usbtuClientList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "usbtuDataUrbCompleteCallback", (char*) usbtuDataUrbCompleteCallback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuDataVendorSpecificCallback", (char*) usbtuDataVendorSpecificCallback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuDevList", (char*) &usbtuDevList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "usbtuInitClientIrpCompleteThreadFn", (char*) usbtuInitClientIrpCompleteThreadFn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitDeviceAdd", (char*) usbtuInitDeviceAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitDeviceRemove", (char*) usbtuInitDeviceRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitDeviceResume", (char*) usbtuInitDeviceResume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitDeviceSuspend", (char*) usbtuInitDeviceSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitFindDriverInfo", (char*) usbtuInitFindDriverInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitHandleClientEvent", (char*) usbtuInitHandleClientEvent, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitHandleDeviceEvent", (char*) usbtuInitHandleDeviceEvent, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usbtuInitWvFilter", (char*) &usbtuInitWvFilter, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "usbtuMutex", (char*) &usbtuMutex, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "userUsb2MscPrintBuffer", (char*) userUsb2MscPrintBuffer, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrAppInit", (char*) usrAppInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineCrack", (char*) usrBootLineCrack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineGet", (char*) usrBootLineGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineInit", (char*) usrBootLineInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineParse", (char*) usrBootLineParse, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBreakpointSet", (char*) usrBreakpointSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrCacheEnable", (char*) usrCacheEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrClock", (char*) usrClock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrDosfsInit", (char*) usrDosfsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrFtpInit", (char*) usrFtpInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrInit", (char*) usrInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrIosCoreInit", (char*) usrIosCoreInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrIosExtraInit", (char*) usrIosExtraInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrIsrDeferInit", (char*) usrIsrDeferInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrKernelCoreInit", (char*) usrKernelCoreInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrKernelExtraInit", (char*) usrKernelExtraInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrKernelInit", (char*) usrKernelInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrLoaderInit", (char*) usrLoaderInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrMmuInit", (char*) usrMmuInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrModuleLoad", (char*) usrModuleLoad, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetAppInit", (char*) usrNetAppInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetApplUtilInit", (char*) usrNetApplUtilInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetBoot", (char*) usrNetBoot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetDaemonInit", (char*) usrNetDaemonInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetDevNameGet", (char*) usrNetDevNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetEndLibInit", (char*) usrNetEndLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetHostInit", (char*) usrNetHostInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetIfconfigInit", (char*) usrNetIfconfigInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetRemoteCreate", (char*) usrNetRemoteCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetRemoteInit", (char*) usrNetRemoteInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetUtilsInit", (char*) usrNetUtilsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetmaskGet", (char*) usrNetmaskGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetworkInit", (char*) usrNetworkInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrPcConsoleInit", (char*) usrPcConsoleInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrRoot", (char*) usrRoot, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrRtpAppInit", (char*) usrRtpAppInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSecurity", (char*) usrSecurity, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSerialInit", (char*) usrSerialInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrShell", (char*) usrShell, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrShellInit", (char*) usrShellInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrShowInit", (char*) usrShowInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrStandaloneInit", (char*) usrStandaloneInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSymTblInit", (char*) usrSymTblInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSysHwInit2", (char*) usrSysHwInit2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSysSymTblInit", (char*) usrSysSymTblInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSysctlInit", (char*) usrSysctlInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrTipInit", (char*) usrTipInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrToolsInit", (char*) usrToolsInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2HelperInit", (char*) usrUsb2HelperInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscCommandTimeoutGet", (char*) usrUsb2MscCommandTimeoutGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscCommandTimeoutSet", (char*) usrUsb2MscCommandTimeoutSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscComplianceEnabled", (char*) usrUsb2MscComplianceEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscComplianceEnabledSet", (char*) usrUsb2MscComplianceEnabledSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscComplianceTestLogFileBaseNameSet", (char*) usrUsb2MscComplianceTestLogFileBaseNameSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscComplianceTestLogFileClose", (char*) usrUsb2MscComplianceTestLogFileClose, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscComplianceTestLogFileOpen", (char*) usrUsb2MscComplianceTestLogFileOpen, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscDefaultMediumChangeCallback", (char*) usrUsb2MscDefaultMediumChangeCallback, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscDirectAccessEnabled", (char*) usrUsb2MscDirectAccessEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscDirectAccessEnabledSet", (char*) usrUsb2MscDirectAccessEnabledSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscDrvNameGet", (char*) usrUsb2MscDrvNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscDumpQuirkyDevices", (char*) usrUsb2MscDumpQuirkyDevices, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscFilesystemInterfaceGet", (char*) usrUsb2MscFilesystemInterfaceGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscFilesystemInterfaceSet", (char*) usrUsb2MscFilesystemInterfaceSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscInit", (char*) usrUsb2MscInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscLookupQuirkyInfo", (char*) usrUsb2MscLookupQuirkyInfo, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscMaxBlocksPerTransferGet", (char*) usrUsb2MscMaxBlocksPerTransferGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscMaxBlocksPerTransferSet", (char*) usrUsb2MscMaxBlocksPerTransferSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscMediumHotplugCheckEabled", (char*) usrUsb2MscMediumHotplugCheckEabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscMediumHotplugCheckEabledSet", (char*) usrUsb2MscMediumHotplugCheckEabledSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscMediumHotplugCheckIntervalGet", (char*) usrUsb2MscMediumHotplugCheckIntervalGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscMediumHotplugCheckIntervalSet", (char*) usrUsb2MscMediumHotplugCheckIntervalSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscNameInstall", (char*) usrUsb2MscNameInstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscNameUninstall", (char*) usrUsb2MscNameUninstall, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscReserveDevice", (char*) usrUsb2MscReserveDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscResetTimeoutGet", (char*) usrUsb2MscResetTimeoutGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscResetTimeoutSet", (char*) usrUsb2MscResetTimeoutSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskNameGet", (char*) usrUsb2MscServiceTaskNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskOptionsGet", (char*) usrUsb2MscServiceTaskOptionsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskOptionsSet", (char*) usrUsb2MscServiceTaskOptionsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskPriorityGet", (char*) usrUsb2MscServiceTaskPriorityGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskPrioritySet", (char*) usrUsb2MscServiceTaskPrioritySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskStackSizeGet", (char*) usrUsb2MscServiceTaskStackSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscServiceTaskStackSizeSet", (char*) usrUsb2MscServiceTaskStackSizeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscStatusCheckEnabled", (char*) usrUsb2MscStatusCheckEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscStatusCheckEnabledSet", (char*) usrUsb2MscStatusCheckEnabledSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscStatusTimeoutGet", (char*) usrUsb2MscStatusTimeoutGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscStatusTimeoutSet", (char*) usrUsb2MscStatusTimeoutSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscTest", (char*) usrUsb2MscTest, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscUninit", (char*) usrUsb2MscUninit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscUnreserveDevice", (char*) usrUsb2MscUnreserveDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscWriteProtectionCheckEnabled", (char*) usrUsb2MscWriteProtectionCheckEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscWriteProtectionCheckEnabledSet", (char*) usrUsb2MscWriteProtectionCheckEnabledSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsb2MscXbdDirectBioEnabled", (char*) usrUsb2MscXbdDirectBioEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsbHubInit", (char*) usrUsbHubInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsbResubmitUrbCheckEnabled", (char*) usrUsbResubmitUrbCheckEnabled, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrUsbWaitTimeOutValueGet", (char*) usrUsbWaitTimeOutValueGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrVxbTimerSysInit", (char*) usrVxbTimerSysInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbBanner", (char*) usrWdbBanner, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbBp", (char*) usrWdbBp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbGopherInit", (char*) usrWdbGopherInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbInit", (char*) usrWdbInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbInitDone", (char*) usrWdbInitDone, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usr_ext_node", (char*) &usr_ext_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "uswab", (char*) uswab, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "utime", (char*) utime, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "valloc", (char*) valloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "version", (char*) version, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vfdprintf", (char*) vfdprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vfprintf", (char*) vfprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vgaCurAttrib_desc", (char*) &vgaCurAttrib_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vgaCursorMove_desc", (char*) &vgaCursorMove_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vgaCursorSet_desc", (char*) &vgaCursorSet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vgaScreenRev_desc", (char*) &vgaScreenRev_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "viLedLibInit", (char*) viLedLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBaseGlobalMapInit", (char*) vmBaseGlobalMapInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBaseLibInit", (char*) vmBaseLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBasePageSizeGet", (char*) vmBasePageSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBaseStateSet", (char*) vmBaseStateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBufferWrite", (char*) vmBufferWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmContextClassId", (char*) &vmContextClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vmContigBlockEach", (char*) vmContigBlockEach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmCurrentGet", (char*) vmCurrentGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmGlobalMapInit", (char*) vmGlobalMapInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmInfoGet", (char*) vmInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmKernelContextIdGet", (char*) vmKernelContextIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmLibInfo", (char*) &vmLibInfo, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vmMap", (char*) vmMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmMaxPhysBitsGet", (char*) vmMaxPhysBitsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPageLock", (char*) vmPageLock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPageMap", (char*) vmPageMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPageOptimize", (char*) vmPageOptimize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPageSizeGet", (char*) vmPageSizeGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPageUnlock", (char*) vmPageUnlock, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPgMap", (char*) vmPgMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmPhysTranslate", (char*) vmPhysTranslate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmStateGet", (char*) vmStateGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmStateSet", (char*) vmStateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmTextProtect", (char*) vmTextProtect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmTranslate", (char*) vmTranslate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vm_node", (char*) &vm_node, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "voprintf", (char*) voprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vprintf", (char*) vprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vsnprintf", (char*) vsnprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vsprintf", (char*) vsprintf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAbsTicks", (char*) &vxAbsTicks, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxAtomicAdd", (char*) vxAtomicAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicAnd", (char*) vxAtomicAnd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicClear", (char*) vxAtomicClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicDec", (char*) vxAtomicDec, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicGet", (char*) vxAtomicGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicInc", (char*) vxAtomicInc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicNand", (char*) vxAtomicNand, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicOr", (char*) vxAtomicOr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicQuadRead", (char*) vxAtomicQuadRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicQuadWrite", (char*) vxAtomicQuadWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicSet", (char*) vxAtomicSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicSub", (char*) vxAtomicSub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAtomicXor", (char*) vxAtomicXor, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxBaseCpuPhysIndex", (char*) &vxBaseCpuPhysIndex, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxC1StateSet", (char*) vxC1StateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCas", (char*) vxCas, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuConfigured", (char*) &vxCpuConfigured, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxCpuConfiguredGet", (char*) vxCpuConfiguredGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuCount", (char*) &vxCpuCount, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxCpuEnabled", (char*) &vxCpuEnabled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxCpuEnabledGet", (char*) vxCpuEnabledGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuIdGet", (char*) vxCpuIdGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuIndexGet", (char*) vxCpuIndexGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuLoApicId", (char*) vxCpuLoApicId, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuReserve", (char*) vxCpuReserve, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuReservedGet", (char*) vxCpuReservedGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCpuSetConfigured", (char*) &vxCpuSetConfigured, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxCpuSetReserved", (char*) &vxCpuSetReserved, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxCpuSetReservedAvail", (char*) &vxCpuSetReservedAvail, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxCpuUnreserve", (char*) vxCpuUnreserve, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr0Get", (char*) vxCr0Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr0Set", (char*) vxCr0Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr2Get", (char*) vxCr2Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr2Set", (char*) vxCr2Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr3Get", (char*) vxCr3Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr3Set", (char*) vxCr3Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr4Get", (char*) vxCr4Get, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCr4Set", (char*) vxCr4Set, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxCsGet", (char*) vxCsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxDrGet", (char*) vxDrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxDrSet", (char*) vxDrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxDsGet", (char*) vxDsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxEflagsGet", (char*) vxEflagsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxEflagsSet", (char*) vxEflagsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxEventPendQ", (char*) &vxEventPendQ, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxGdtrGet", (char*) vxGdtrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxGdtrSet", (char*) vxGdtrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIOProbeSup", (char*) vxIOProbeSup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIOProbeTrap", (char*) vxIOProbeTrap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIdleEntHookRtn", (char*) vxIdleEntHookRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIdleExtHookRtn", (char*) vxIdleExtHookRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIdleNent", (char*) &vxIdleNent, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleNext", (char*) &vxIdleNext, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleTick1st", (char*) &vxIdleTick1st, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleTickBusy", (char*) &vxIdleTickBusy, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleTickEnt", (char*) &vxIdleTickEnt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleTickExt", (char*) &vxIdleTickExt, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleTickIdle", (char*) &vxIdleTickIdle, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIdleTsc1st", (char*) &vxIdleTsc1st, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIdleTscBusy", (char*) &vxIdleTscBusy, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIdleTscEnt", (char*) &vxIdleTscEnt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIdleTscExt", (char*) &vxIdleTscExt, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIdleTscIdle", (char*) &vxIdleTscIdle, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIdleUtilGet", (char*) vxIdleUtilGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIdtrGet", (char*) vxIdtrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxIntStackBase", (char*) &vxIntStackBase, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIntStackEnabled", (char*) &vxIntStackEnabled, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIntStackEnd", (char*) &vxIntStackEnd, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIntStackOverflowSize", (char*) &vxIntStackOverflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIntStackPtr", (char*) &vxIntStackPtr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxIntStackUnderflowSize", (char*) &vxIntStackUnderflowSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxKernelSchedDesc", (char*) &vxKernelSchedDesc, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxLdtrGet", (char*) vxLdtrGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxLdtrSet", (char*) vxLdtrSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemArchProbe", (char*) vxMemArchProbe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemArchProbeInit", (char*) vxMemArchProbeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemCommonProbe", (char*) vxMemCommonProbe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbe", (char*) vxMemProbe, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeByteRead", (char*) vxMemProbeByteRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeByteWrite", (char*) vxMemProbeByteWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeErrorRtn", (char*) vxMemProbeErrorRtn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeInit", (char*) vxMemProbeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeLongRead", (char*) vxMemProbeLongRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeLongWrite", (char*) vxMemProbeLongWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeSup", (char*) vxMemProbeSup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeWordRead", (char*) vxMemProbeWordRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeWordWrite", (char*) vxMemProbeWordWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxRsdpPtr", (char*) &vxRsdpPtr, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxSsGet", (char*) vxSsGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxTas", (char*) vxTas, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxTaskEntry", (char*) vxTaskEntry, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxTssGet", (char*) vxTssGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxTssSet", (char*) vxTssSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxWorksVersion", (char*) &vxWorksVersion, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxWorksVersionMaint", (char*) &vxWorksVersionMaint, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxWorksVersionMajor", (char*) &vxWorksVersionMajor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxWorksVersionMinor", (char*) &vxWorksVersionMinor, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbAccessFree", (char*) vxbAccessFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbBusAnnounce", (char*) vxbBusAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbBusListLock", (char*) &vxbBusListLock, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbBusTypeRegister", (char*) vxbBusTypeRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbBusTypeString", (char*) vxbBusTypeString, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbBusTypeUnregister", (char*) vxbBusTypeUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDelay", (char*) vxbDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDelayLibInit", (char*) vxbDelayLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDelayTimerFreeRunning", (char*) &vxbDelayTimerFreeRunning, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbDevAccessAnnounce", (char*) vxbDevAccessAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevConnect", (char*) vxbDevConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevConnectInternal", (char*) vxbDevConnectInternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevInit", (char*) vxbDevInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevInitInternal", (char*) vxbDevInitInternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevIterate", (char*) vxbDevIterate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevMethodGet", (char*) vxbDevMethodGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevMethodRun", (char*) vxbDevMethodRun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevParent", (char*) vxbDevParent, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevPath", (char*) vxbDevPath, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevRegMap_desc", (char*) &vxbDevRegMap_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbDevRegister", (char*) vxbDevRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevRemovalAnnounce", (char*) vxbDevRemovalAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevStructAlloc", (char*) vxbDevStructAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevStructFree", (char*) vxbDevStructFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDevStructListLock", (char*) &vxbDevStructListLock, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbDeviceAnnounce", (char*) vxbDeviceAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDeviceDriverRelease", (char*) vxbDeviceDriverRelease, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDeviceMethodRun", (char*) vxbDeviceMethodRun, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDriverUnregister", (char*) vxbDriverUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDrvRescan", (char*) vxbDrvRescan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbDrvUnlink_desc", (char*) &vxbDrvUnlink_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbDrvVerCheck", (char*) vxbDrvVerCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbFileNvRamGet", (char*) vxbFileNvRamGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbFileNvRamRegister", (char*) vxbFileNvRamRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbFileNvRamSet", (char*) vxbFileNvRamSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbGlobalListsLock", (char*) &vxbGlobalListsLock, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbI8253TimerDrvRegister", (char*) vxbI8253TimerDrvRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInit", (char*) vxbInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInstByNameFind", (char*) vxbInstByNameFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInstParamByIndexGet", (char*) vxbInstParamByIndexGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInstParamByNameGet", (char*) vxbInstParamByNameGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInstParamSet", (char*) vxbInstParamSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInstUnitGet", (char*) vxbInstUnitGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbInstUnitSet", (char*) vxbInstUnitSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntAcknowledge", (char*) vxbIntAcknowledge, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntConnect", (char*) vxbIntConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntCtlrAck_desc", (char*) &vxbIntCtlrAck_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntCtlrConnect_desc", (char*) &vxbIntCtlrConnect_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntCtlrCpuReroute_desc", (char*) &vxbIntCtlrCpuReroute_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntCtlrDisable_desc", (char*) &vxbIntCtlrDisable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntCtlrDisconnect_desc", (char*) &vxbIntCtlrDisconnect_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntCtlrEnable_desc", (char*) &vxbIntCtlrEnable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntCtlrIntReroute_desc", (char*) &vxbIntCtlrIntReroute_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntDisable", (char*) vxbIntDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntDisconnect", (char*) vxbIntDisconnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntDynaVecDisable_desc", (char*) &vxbIntDynaVecDisable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntDynaVecEnable_desc", (char*) &vxbIntDynaVecEnable_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntDynaVecProgram_desc", (char*) &vxbIntDynaVecProgram_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbIntEnable", (char*) vxbIntEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntVectorGet", (char*) vxbIntVectorGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIntelIchStorageRegister", (char*) vxbIntelIchStorageRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIoApicIntrDrvRegister", (char*) vxbIoApicIntrDrvRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbIoApicIntrShowAll", (char*) vxbIoApicIntrShowAll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbLibError", (char*) vxbLibError, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbLibInit", (char*) vxbLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbLockDelete", (char*) vxbLockDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbLockGive", (char*) vxbLockGive, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbLockInit", (char*) vxbLockInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbLockTake", (char*) vxbLockTake, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbMpApicDataShow", (char*) vxbMpApicDataShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbMpApicDrvRegister", (char*) vxbMpApicDrvRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbMpBiosIoIntMapShow", (char*) vxbMpBiosIoIntMapShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbMpBiosLocalIntMapShow", (char*) vxbMpBiosLocalIntMapShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbMpBiosShow", (char*) vxbMpBiosShow, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbMsDelay", (char*) vxbMsDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbNextUnitGet", (char*) vxbNextUnitGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbNonVolGet", (char*) vxbNonVolGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbNonVolLibInit", (char*) vxbNonVolLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbNonVolSet", (char*) vxbNonVolSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciAccessCookieSet", (char*) vxbPciAccessCookieSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciAccessInit", (char*) vxbPciAccessInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciBusCfgRead", (char*) vxbPciBusCfgRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciBusCfgWrite", (char*) vxbPciBusCfgWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciBusTypeInit", (char*) vxbPciBusTypeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigBdfPack", (char*) vxbPciConfigBdfPack, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigExtCapFind", (char*) vxbPciConfigExtCapFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigForeachFunc", (char*) vxbPciConfigForeachFunc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigInByte", (char*) vxbPciConfigInByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigInLong", (char*) vxbPciConfigInLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigInWord", (char*) vxbPciConfigInWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigLibInit", (char*) vxbPciConfigLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigModifyByte", (char*) vxbPciConfigModifyByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigModifyLong", (char*) vxbPciConfigModifyLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigModifyWord", (char*) vxbPciConfigModifyWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigOutByte", (char*) vxbPciConfigOutByte, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigOutLong", (char*) vxbPciConfigOutLong, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigOutWord", (char*) vxbPciConfigOutWord, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciConfigReset", (char*) vxbPciConfigReset, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciDevCfgRead", (char*) vxbPciDevCfgRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciDevCfgWrite", (char*) vxbPciDevCfgWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciDevConfig", (char*) vxbPciDevConfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciFindClass", (char*) vxbPciFindClass, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciFindDevice", (char*) vxbPciFindDevice, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciInt", (char*) vxbPciInt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciIntConnect", (char*) vxbPciIntConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciIntDisconnect", (char*) vxbPciIntDisconnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciIntDisconnect2", (char*) vxbPciIntDisconnect2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciIntLibInit", (char*) vxbPciIntLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciMSICtl", (char*) vxbPciMSICtl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciMSIDisable", (char*) vxbPciMSIDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciMSIEnable", (char*) vxbPciMSIEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciMSIIsCap", (char*) vxbPciMSIIsCap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciMSIProgram", (char*) vxbPciMSIProgram, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbPciSpecialCycle", (char*) vxbPciSpecialCycle, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbRead16", (char*) vxbRead16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbRead32", (char*) vxbRead32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbRead64", (char*) vxbRead64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbRead8", (char*) vxbRead8, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbRegMap", (char*) vxbRegMap, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbResourceFind", (char*) vxbResourceFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSerialChanGet", (char*) vxbSerialChanGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSubDevAction", (char*) vxbSubDevAction, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSwap16", (char*) vxbSwap16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSwap32", (char*) vxbSwap32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSwap64", (char*) vxbSwap64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSysClkConnect", (char*) vxbSysClkConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSysClkDisable", (char*) vxbSysClkDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSysClkEnable", (char*) vxbSysClkEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSysClkLibInit", (char*) vxbSysClkLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSysClkRateGet", (char*) vxbSysClkRateGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbSysClkRateSet", (char*) vxbSysClkRateSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbTimerAlloc", (char*) vxbTimerAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbTimerFeaturesGet", (char*) vxbTimerFeaturesGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbTimerFuncGet_desc", (char*) &vxbTimerFuncGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbTimerNumberGet_desc", (char*) &vxbTimerNumberGet_desc, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vxbTimerRelease", (char*) vxbTimerRelease, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbUsDelay", (char*) vxbUsDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbUsbEhciRegister", (char*) vxbUsbEhciRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbUsbHcdUhciDevDeregister", (char*) vxbUsbHcdUhciDevDeregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbUsbOhciRegister", (char*) vxbUsbOhciRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbUsbUhciRegister", (char*) vxbUsbUhciRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbWrite16", (char*) vxbWrite16, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbWrite32", (char*) vxbWrite32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbWrite64", (char*) vxbWrite64, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxbWrite8", (char*) vxbWrite8, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpAdd", (char*) vxdbgBpAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpAddrCheck", (char*) vxdbgBpAddrCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpAllDisable", (char*) vxdbgBpAllDisable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpDelete", (char*) vxdbgBpDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpFind", (char*) vxdbgBpFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpList", (char*) &vxdbgBpList, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxdbgBpMsgDrop", (char*) vxdbgBpMsgDrop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpMsgGet", (char*) vxdbgBpMsgGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpMsgPost", (char*) vxdbgBpMsgPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpMsgQCreate", (char*) vxdbgBpMsgQCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgBpMsgQHdlrIsRunning", (char*) vxdbgBpMsgQHdlrIsRunning, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgClntRegister", (char*) vxdbgClntRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgCont", (char*) vxdbgCont, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgEnable", (char*) vxdbgEnable, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgHookAdd", (char*) vxdbgHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgLockUnbreakable", (char*) &vxdbgLockUnbreakable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxdbgMemAccess", (char*) vxdbgMemAccess, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgMemMove", (char*) vxdbgMemMove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgMemRead", (char*) vxdbgMemRead, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgMemScan", (char*) vxdbgMemScan, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgMemWrite", (char*) vxdbgMemWrite, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgSafeUnbreakable", (char*) &vxdbgSafeUnbreakable, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxdbgStep", (char*) vxdbgStep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgStop", (char*) vxdbgStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgTaskCont", (char*) vxdbgTaskCont, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgTaskLibInit", (char*) vxdbgTaskLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgTaskStep", (char*) vxdbgTaskStep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgTaskStop", (char*) vxdbgTaskStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxdbgUnbreakableOld", (char*) &vxdbgUnbreakableOld, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxfs_ramdisk_init_hook", (char*) &vxfs_ramdisk_init_hook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxmux_calculate_transport_checksum", (char*) vxmux_calculate_transport_checksum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxmux_mux_mblk_init", (char*) vxmux_mux_mblk_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxmux_null_buf_init", (char*) vxmux_null_buf_init, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxmux_null_pool", (char*) &vxmux_null_pool, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "w", (char*) w, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "watchdog_test", (char*) watchdog_test, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wcstombs", (char*) wcstombs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wctomb", (char*) wctomb, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdCancel", (char*) wdCancel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdClassId", (char*) &wdClassId, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdCreate", (char*) wdCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdCreateLibInit", (char*) wdCreateLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdDelete", (char*) wdDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdDestroy", (char*) wdDestroy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdInit", (char*) wdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdInitialize", (char*) wdInitialize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdLibInit", (char*) wdLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdStart", (char*) wdStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdTerminate", (char*) wdTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdTick", (char*) wdTick, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbAvailModes", (char*) &wdbAvailModes, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbAvailOptions", (char*) &wdbAvailOptions, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbBpAddHookAdd", (char*) wdbBpAddHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbBpSyncLibInit", (char*) wdbBpSyncLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbBpSysEnterHook", (char*) &wdbBpSysEnterHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbBpSysExitHook", (char*) &wdbBpSysExitHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbCksum", (char*) wdbCksum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCmdLoop", (char*) wdbCmdLoop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCnctModePost", (char*) wdbCnctModePost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCommDevInit", (char*) wdbCommDevInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCommMtu", (char*) &wdbCommMtu, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbCommMtuGet", (char*) wdbCommMtuGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbConfig", (char*) wdbConfig, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbConnectHookAdd", (char*) wdbConnectHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbConnectLibInit", (char*) wdbConnectLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxCreateNotify", (char*) wdbCtxCreateNotify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxCs", (char*) &wdbCtxCs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbCtxDeleteNotify", (char*) wdbCtxDeleteNotify, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxEvtLibInit", (char*) wdbCtxEvtLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxExitEventGet", (char*) wdbCtxExitEventGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxExitLibInit", (char*) wdbCtxExitLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxExitNotifyHook", (char*) wdbCtxExitNotifyHook, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxLibInit", (char*) wdbCtxLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxStartEventGet", (char*) wdbCtxStartEventGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxStartLibInit", (char*) wdbCtxStartLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgArchInit", (char*) wdbDbgArchInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBpStub", (char*) wdbDbgBpStub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBreakpoint", (char*) wdbDbgBreakpoint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgCtxCs", (char*) &wdbDbgCtxCs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbDbgHwAddrCheck", (char*) wdbDbgHwAddrCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgHwBpFind", (char*) wdbDbgHwBpFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgHwBpSet", (char*) wdbDbgHwBpSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgPreBreakpoint", (char*) wdbDbgPreBreakpoint, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgPreTrace", (char*) wdbDbgPreTrace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgRegsClear", (char*) wdbDbgRegsClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgRegsSet", (char*) wdbDbgRegsSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgSysCallCheck", (char*) wdbDbgSysCallCheck, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTrace", (char*) wdbDbgTrace, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTraceModeClear", (char*) wdbDbgTraceModeClear, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTraceModeSet", (char*) wdbDbgTraceModeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTraceStub", (char*) wdbDbgTraceStub, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDirectCallLibInit", (char*) wdbDirectCallLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbE", (char*) wdbE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEndDebug", (char*) &wdbEndDebug, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbEndDeviceAddress", (char*) &wdbEndDeviceAddress, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbEndPktDevInit", (char*) wdbEndPktDevInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventDeq", (char*) wdbEventDeq, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventLibInit", (char*) wdbEventLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventNodeInit", (char*) wdbEventNodeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventPost", (char*) wdbEventPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEvtptClassConnect", (char*) wdbEvtptClassConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEvtptLibInit", (char*) wdbEvtptLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExcLibInit", (char*) wdbExcLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternEnterHookAdd", (char*) wdbExternEnterHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternExitHookAdd", (char*) wdbExternExitHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternInit", (char*) wdbExternInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternLibInit", (char*) wdbExternLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternRegLibInit", (char*) wdbExternRegLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbFuncCallLibInit", (char*) wdbFuncCallLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbGopherLibInit", (char*) wdbGopherLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbInfoGet", (char*) wdbInfoGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbInstallCommIf", (char*) wdbInstallCommIf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbInstallRtIf", (char*) wdbInstallRtIf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbIsInitialized", (char*) &wdbIsInitialized, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbIsNowExternal", (char*) wdbIsNowExternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbIsReady", (char*) &wdbIsReady, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbMbufAlloc", (char*) wdbMbufAlloc, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMbufFree", (char*) wdbMbufFree, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMbufInit", (char*) wdbMbufInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMdlSymSyncLibInit", (char*) wdbMdlSymSyncLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMemCoreLibInit", (char*) wdbMemCoreLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMemLibInit", (char*) wdbMemLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMode", (char*) &wdbMode, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbModeSet", (char*) wdbModeSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbModeSetHookAdd", (char*) wdbModeSetHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbNotifyHost", (char*) wdbNotifyHost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbNumMemRegions", (char*) &wdbNumMemRegions, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbOneShot", (char*) &wdbOneShot, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbPort", (char*) &wdbPort, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbRegsBuffer", (char*) &wdbRegsBuffer, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbRegsBufferSize", (char*) &wdbRegsBufferSize, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbRegsLibInit", (char*) wdbRegsLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcGetArgs", (char*) wdbRpcGetArgs, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcNotifyConnect", (char*) wdbRpcNotifyConnect, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcNotifyHost", (char*) wdbRpcNotifyHost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcRcv", (char*) wdbRpcRcv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcReply", (char*) wdbRpcReply, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcReplyErr", (char*) wdbRpcReplyErr, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcResendReply", (char*) wdbRpcResendReply, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcXportInit", (char*) wdbRpcXportInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRtIf", (char*) &wdbRtIf, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbRtLibInit", (char*) wdbRtLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRunsExternal", (char*) wdbRunsExternal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRunsTasking", (char*) wdbRunsTasking, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSp", (char*) wdbSp, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcAdd", (char*) wdbSvcAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcDispatch", (char*) wdbSvcDispatch, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcHookAdd", (char*) wdbSvcHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcLibInit", (char*) wdbSvcLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSysBpDisableAll", (char*) wdbSysBpDisableAll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSysBpEnableAll", (char*) wdbSysBpEnableAll, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSysBpLibInit", (char*) wdbSysBpLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSysModeInit", (char*) wdbSysModeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSystemSuspend", (char*) wdbSystemSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTargetIsConnected", (char*) wdbTargetIsConnected, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTask", (char*) wdbTask, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskBpAdd", (char*) wdbTaskBpAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskBpLibInit", (char*) wdbTaskBpLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskCont", (char*) wdbTaskCont, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskCreateHookAdd", (char*) wdbTaskCreateHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskDeleteHookAdd", (char*) wdbTaskDeleteHookAdd, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskExtraModules", (char*) &wdbTaskExtraModules, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbTaskHookInit", (char*) wdbTaskHookInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskModeInit", (char*) wdbTaskModeInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskRegLibInit", (char*) wdbTaskRegLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskRestartHook", (char*) &wdbTaskRestartHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskStep", (char*) wdbTaskStep, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskStop", (char*) wdbTaskStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTgtInfoLibInit", (char*) wdbTgtInfoLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbToolName", (char*) &wdbToolName, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbUserEvtLibInit", (char*) wdbUserEvtLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbUserEvtPost", (char*) wdbUserEvtPost, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioChannelRegister", (char*) wdbVioChannelRegister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioChannelUnregister", (char*) wdbVioChannelUnregister, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioDrv", (char*) wdbVioDrv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioLibInit", (char*) wdbVioLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrCreate", (char*) wdbXdrCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrGetVal", (char*) wdbXdrGetVal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrGetpos", (char*) wdbXdrGetpos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrInline", (char*) wdbXdrInline, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrPutVal", (char*) wdbXdrPutVal, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrPutbytes", (char*) wdbXdrPutbytes, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbXdrSetpos", (char*) wdbXdrSetpos, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "whoami", (char*) whoami, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windCont", (char*) windCont, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windDelay", (char*) windDelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windDelete", (char*) windDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windExit", (char*) windExit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windIntStackSet", (char*) windIntStackSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windLoadContext", (char*) windLoadContext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windNullReturn", (char*) windNullReturn, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQFlush", (char*) windPendQFlush, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQGet", (char*) windPendQGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQPut", (char*) windPendQPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQRemove", (char*) windPendQRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQTerminate", (char*) windPendQTerminate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPriNormalSet", (char*) windPriNormalSet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPrioritySet", (char*) windPrioritySet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windReadyQPut", (char*) windReadyQPut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windReadyQRemove", (char*) windReadyQRemove, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windResume", (char*) windResume, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windSemDelete", (char*) windSemDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windSemRWDelete", (char*) windSemRWDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windStop", (char*) windStop, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windSuspend", (char*) windSuspend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windTickAnnounce", (char*) windTickAnnounce, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windTickAnnounceN", (char*) windTickAnnounceN, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windTickWaitGet", (char*) windTickWaitGet, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windUndelay", (char*) windUndelay, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windWdCancel", (char*) windWdCancel, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windWdStart", (char*) windWdStart, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQAdd0", (char*) workQAdd0, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQAdd1", (char*) workQAdd1, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQAdd2", (char*) workQAdd2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQDoWork", (char*) workQDoWork, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQInit", (char*) workQInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQIsEmpty", (char*) &workQIsEmpty, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "workQIx", (char*) &workQIx, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "workQPanic", (char*) workQPanic, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQPanicHook", (char*) &workQPanicHook, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "workQWorkInProgress", (char*) &workQWorkInProgress, 0, 0,  SYM_GLOBAL | SYM_BSS},
        {{NULL}, "write", (char*) write, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "writev", (char*) writev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xattrib", (char*) xattrib, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdAttach", (char*) xbdAttach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdAttachExt", (char*) xbdAttachExt, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdBlkDevCreate", (char*) xbdBlkDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdBlkDevCreateSync", (char*) xbdBlkDevCreateSync, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdBlkDevDelete", (char*) xbdBlkDevDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdBlkDevLibInit", (char*) xbdBlkDevLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdBlkDevServTskPri", (char*) &xbdBlkDevServTskPri, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdBlockSize", (char*) xbdBlockSize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdCreatePartition", (char*) xbdCreatePartition, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdCreatePartitionSz", (char*) xbdCreatePartitionSz, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdDetach", (char*) xbdDetach, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdDump", (char*) xbdDump, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdEventCategory", (char*) &xbdEventCategory, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdEventInstantiated", (char*) &xbdEventInstantiated, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdEventMediaChanged", (char*) &xbdEventMediaChanged, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdEventPrimaryInsert", (char*) &xbdEventPrimaryInsert, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdEventRemove", (char*) &xbdEventRemove, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdEventSecondaryInsert", (char*) &xbdEventSecondaryInsert, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdEventSoftInsert", (char*) &xbdEventSoftInsert, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "xbdGetBioSched", (char*) xbdGetBioSched, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdGetNextBioGeneric", (char*) xbdGetNextBioGeneric, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdInit", (char*) xbdInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdIoctl", (char*) xbdIoctl, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdNBlocks", (char*) xbdNBlocks, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdPartitionDevCreate", (char*) xbdPartitionDevCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdSetBioSched", (char*) xbdSetBioSched, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdSize", (char*) xbdSize, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdSrvTaskGeneric", (char*) xbdSrvTaskGeneric, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdStrategy", (char*) xbdStrategy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xbdStrategyGeneric", (char*) xbdStrategyGeneric, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xcopy", (char*) xcopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdelete", (char*) xdelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdrCksum", (char*) xdrCksum, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_ARRAY", (char*) xdr_ARRAY, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_BOOL", (char*) xdr_BOOL, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_CHECKSUM", (char*) xdr_CHECKSUM, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_ENUM", (char*) xdr_ENUM, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_REFERENCE", (char*) xdr_REFERENCE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_TGT_ADDR_T", (char*) xdr_TGT_ADDR_T, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_TGT_LONG_T", (char*) xdr_TGT_LONG_T, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_UINT32", (char*) xdr_UINT32, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_VOID", (char*) xdr_VOID, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_AGENT_INFO", (char*) xdr_WDB_AGENT_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CALL_RETURN_INFO", (char*) xdr_WDB_CALL_RETURN_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CONNECT_INFO", (char*) xdr_WDB_CONNECT_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CONNECT_PARAMS", (char*) xdr_WDB_CONNECT_PARAMS, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CORE", (char*) xdr_WDB_CORE, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX", (char*) xdr_WDB_CTX, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX_CREATE_DESC", (char*) xdr_WDB_CTX_CREATE_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX_KILL_DESC", (char*) xdr_WDB_CTX_KILL_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX_STEP_DESC", (char*) xdr_WDB_CTX_STEP_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_DIRECT_CALL_RET", (char*) xdr_WDB_DIRECT_CALL_RET, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVTPT_ADD_DESC", (char*) xdr_WDB_EVTPT_ADD_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVTPT_DEL_DESC", (char*) xdr_WDB_EVTPT_DEL_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVT_DATA", (char*) xdr_WDB_EVT_DATA, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVT_INFO", (char*) xdr_WDB_EVT_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MEM_REGION", (char*) xdr_WDB_MEM_REGION, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MEM_SCAN_DESC", (char*) xdr_WDB_MEM_SCAN_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MEM_XFER", (char*) xdr_WDB_MEM_XFER, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MOD_INFO", (char*) xdr_WDB_MOD_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_OPQ_DATA_T", (char*) xdr_WDB_OPQ_DATA_T, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_PARAM_WRAPPER", (char*) xdr_WDB_PARAM_WRAPPER, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_REG_READ_DESC", (char*) xdr_WDB_REG_READ_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_REG_WRITE_DESC", (char*) xdr_WDB_REG_WRITE_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_REPLY_WRAPPER", (char*) xdr_WDB_REPLY_WRAPPER, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_RT_INFO", (char*) xdr_WDB_RT_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SECT_INFO", (char*) xdr_WDB_SECT_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SEG_INFO", (char*) xdr_WDB_SEG_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_STRING_ARRAY", (char*) xdr_WDB_STRING_ARRAY, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_STRING_T", (char*) xdr_WDB_STRING_T, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SYM_ID", (char*) xdr_WDB_SYM_ID, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SYM_ID_LIST", (char*) xdr_WDB_SYM_ID_LIST, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SYM_INFO", (char*) xdr_WDB_SYM_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SYM_LIST", (char*) xdr_WDB_SYM_LIST, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_SYM_MOD_DESC", (char*) xdr_WDB_SYM_MOD_DESC, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_TGT_INFO", (char*) xdr_WDB_TGT_INFO, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_TGT_INFO_2", (char*) xdr_WDB_TGT_INFO_2, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xpFuncs", (char*) &xpFuncs, 0, 0,  SYM_GLOBAL | SYM_DATA},
        {{NULL}, "zbufCreate", (char*) zbufCreate, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufCut", (char*) zbufCut, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufDelete", (char*) zbufDelete, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufDup", (char*) zbufDup, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufExtractCopy", (char*) zbufExtractCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufInsert", (char*) zbufInsert, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufInsertBuf", (char*) zbufInsertBuf, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufInsertCopy", (char*) zbufInsertCopy, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufLength", (char*) zbufLength, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufLibInit", (char*) zbufLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSegData", (char*) zbufSegData, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSegFind", (char*) zbufSegFind, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSegLength", (char*) zbufSegLength, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSegNext", (char*) zbufSegNext, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSegPrev", (char*) zbufSegPrev, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockBufSend", (char*) zbufSockBufSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockBufSendto", (char*) zbufSockBufSendto, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockLibInit", (char*) zbufSockLibInit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockRecv", (char*) zbufSockRecv, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockRecvfrom", (char*) zbufSockRecvfrom, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockSend", (char*) zbufSockSend, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSockSendto", (char*) zbufSockSendto, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbufSplit", (char*) zbufSplit, 0, 0,  SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "zbuf_free", (char*) zbuf_free, 0, 0,  SYM_GLOBAL | SYM_TEXT},
    };


ULONG standTblSize = 6076;
