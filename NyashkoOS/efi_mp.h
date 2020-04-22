#pragma once
#include "efi.h"

typedef struct { UINT32  Package;  UINT32  Core;  UINT32  Thread; } EFI_CPU_PHYSICAL_LOCATION;

#define PROCESSOR_AS_BSP_BIT         0x00000001 
#define PROCESSOR_ENABLED_BIT        0x00000002 
#define PROCESSOR_HEALTH_STATUS_BIT  0x00000004 

struct EFI_MP_SERVICES_PROTOCOL;

typedef struct {
	UINT64                     ProcessorId;
	UINT32                    StatusFlag;  
	EFI_CPU_PHYSICAL_LOCATION Location;
} EFI_PROCESSOR_INFORMATION;

typedef EFI_STATUS(EFIAPI* EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS) (
	IN  EFI_MP_SERVICES_PROTOCOL* This, 
	OUT UINTN* NumberOfProcessors, 
	OUT UINTN* NumberOfEnabledProcessors
	);

typedef EFI_STATUS(EFIAPI* EFI_MP_SERVICES_GET_PROCESSOR_INFO) (
	IN  EFI_MP_SERVICES_PROTOCOL* This, 
	IN  UINTN                       ProcessorNumber, 
	OUT EFI_PROCESSOR_INFORMATION* ProcessorInfoBuffer
	);

#define END_OF_CPU_LIST    0xffffffff 
typedef VOID (EFIAPI *EFI_AP_PROCEDURE) (  IN VOID  *ProcedureArgument );

typedef EFI_STATUS(EFIAPI* EFI_MP_SERVICES_STARTUP_ALL_APS) (
	IN  EFI_MP_SERVICES_PROTOCOL* This, 
	IN  EFI_AP_PROCEDURE         Procedure, 
	IN  BOOLEAN                  SingleThread, 
	IN  EFI_EVENT                WaitEvent               OPTIONAL, 
	IN  UINTN                    TimeoutInMicroSeconds, 
	IN  VOID* ProcedureArgument      OPTIONAL, 
	OUT UINTN** FailedCpuList         OPTIONAL
	);

typedef EFI_STATUS(EFIAPI* EFI_MP_SERVICES_STARTUP_THIS_AP) (
	IN  EFI_MP_SERVICES_PROTOCOL* This, 
	IN  EFI_AP_PROCEDURE        Procedure, 
	IN  UINTN                   ProcessorNumber, 
	IN  EFI_EVENT               WaitEvent               OPTIONAL, 
	IN  UINTN                   TimeoutInMicroseconds, 
	IN  VOID* ProcedureArgument      OPTIONAL, 
	OUT BOOLEAN* Finished               OPTIONAL
	);

typedef struct EFI_MP_SERVICES_PROTOCOL { 
	EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS GetNumberOfProcessors; 
	EFI_MP_SERVICES_GET_PROCESSOR_INFO       GetProcessorInfo; 
	EFI_MP_SERVICES_STARTUP_ALL_APS          StartupAllAPs; 
	EFI_MP_SERVICES_STARTUP_THIS_AP          StartupThisAP; 
	//EFI_MP_SERVICES_SWITCH_BSP               SwitchBSP; 
	//EFI_MP_SERVICES_ENABLEDISABLEAP          EnableDisableAP; 
	//EFI_MP_SERVICES_WHOAMI                   WhoAmI; 
} EFI_MP_SERVICES_PROTOCOL;