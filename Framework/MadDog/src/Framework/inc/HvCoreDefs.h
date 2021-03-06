/* 
 * Copyright holder: Invisible Things Lab
 * 
 * This software is protected by domestic and International
 * copyright laws. Any use (including publishing and
 * distribution) of this software requires a valid license
 * from the copyright holder.
 *
 * This software is provided for the educational use only
 * during the Black Hat training. This software should not
 * be used on production systems.
 *
 */
 
 /* Copyright (C) 2010 Trusted Computing Lab in Shanghai Jiaotong University
 * 
 * 09/10/11	Miao Yu <superymkfounder@hotmail.com>
 */
#pragma once
#include <ntddk.h>

#ifdef _X86_
#define ULONG ULONG32
#else

#if defined(_AMD64_)|| defined(_IA64_)
#define ULONG ULONG64
#endif

#endif

//+++++++++++++++++++++Global Definitions+++++++++++++++++++++++++++
#define LAB_TAG 'VSL' 	//Define the tag. This value will be used in allocate pool memory. 
			// 'VSL'- Virtualization Security Lab
//CURRENT_STATE_HYPERVISOR & CURRENT_STATE_GUEST are used for bCurrentMachineState
#define CURRENT_STATE_HYPERVISOR 	0
#define CURRENT_STATE_GUEST 		1

//++++++++++++++Cpu Related Structs(Common Structs)++++++++++++++++
typedef struct _CPU *PCPU;
typedef struct _GUEST_REGS *PGUEST_REGS;

//+++++++++++++++++++++Traps Definitions+++++++++++++++++++++++++++

#define NUM_VMEXITS 	256
#define TRAP_PRIORITY   ULONG
typedef struct _NBP_TRAP *PNBP_TRAP;

// returns FALSE if the adjustment of guest RIP is not needed
typedef BOOLEAN (
  NTAPI * NBP_TRAP_CALLBACK
) (
  PCPU Cpu,
  PGUEST_REGS GuestRegs,
  PNBP_TRAP Trap,
  BOOLEAN WillBeAlsoHandledByGuestHv,
  ... //Pass in arguments
);

//+++++++++++++++++++++Other Definitions+++++++++++++++++++++++++++
typedef NTSTATUS (NTAPI * PCALLBACK_PROC) (PVOID Param);

//+++++++++++++Hypervisor Status+++++++++++
#define HVSTATUS 	ULONG64

#define HVSTATUS_UNSUPPORTED_FEATURE 	0x1
#define HVSTATUS_INVALID_PARAMETERS     STATUS_INVALID_PARAMETER
#define HVSTATUS_SUCCESS				0x0
#define HVSTATUS_NTSTATUS(x) (x==HVSTATUS_SUCCESS?STATUS_SUCCESS:STATUS_UNSUCCESSFUL)

