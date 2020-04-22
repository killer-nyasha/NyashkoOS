#pragma once

typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef wchar_t CHAR16;
typedef int INT32;
typedef unsigned int UINT32;
typedef unsigned long long int UINTN;
typedef unsigned long long int UINT64;
typedef bool BOOLEAN;

typedef UINTN   EFI_TPL;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64  EFI_VIRTUAL_ADDRESS;
typedef UINTN EFI_STATUS;
typedef void* EFI_HANDLE;
typedef void* EFI_EVENT;
typedef void VOID;

#define TPL_APPLICATION    4
#define TPL_CALLBACK       8
#define TPL_NOTIFY         16
#define TPL_HIGH_LEVEL     31

const EFI_STATUS EFIERR = 0x8000000000000000;
const EFI_STATUS EFI_SUCCESS = 0;
const EFI_STATUS EFI_LOAD_ERROR = EFIERR | 1;
const EFI_STATUS EFI_INVALID_PARAMETER = EFIERR | 2;
const EFI_STATUS EFI_UNSUPPORTED = EFIERR | 3;
const EFI_STATUS EFI_BAD_BUFFER_SIZE = EFIERR | 4;
const EFI_STATUS EFI_BUFFER_TOO_SMALL = EFIERR | 5;
const EFI_STATUS EFI_NOT_READY = EFIERR | 6;
const EFI_STATUS EFI_DEVICE_ERROR = EFIERR | 7;
const EFI_STATUS EFI_WRITE_PROTECTED = EFIERR | 8;
const EFI_STATUS EFI_OUT_OF_RESOURCES = EFIERR | 9;
const EFI_STATUS EFI_VOLUME_CORRUPTED = EFIERR | 10;
const EFI_STATUS EFI_VOLUME_FULL = EFIERR | 11;
const EFI_STATUS EFI_NO_MEDIA = EFIERR | 12;
const EFI_STATUS EFI_MEDIA_CHANGED = EFIERR | 13;
const EFI_STATUS EFI_NOT_FOUND = EFIERR | 14;
const EFI_STATUS EFI_ACCESS_DENIED = EFIERR | 15;
const EFI_STATUS EFI_NO_RESPONSE = EFIERR | 16;
const EFI_STATUS EFI_NO_MAPPING = EFIERR | 17;
const EFI_STATUS EFI_TIMEOUT = EFIERR | 18;
const EFI_STATUS EFI_NOT_STARTED = EFIERR | 19;
const EFI_STATUS EFI_ALREADY_STARTED = EFIERR | 20;
const EFI_STATUS EFI_ABORTED = EFIERR | 21;
const EFI_STATUS EFI_ICMP_ERROR = EFIERR | 22;
const EFI_STATUS EFI_TFTP_ERROR = EFIERR | 23;
const EFI_STATUS EFI_PROTOCOL_ERROR = EFIERR | 24;

#define IN
#define OUT
#define EFIAPI
#define OPTIONAL

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct EFI_BOOT_SERVICES;
struct EFI_RUNTIME_SERVICES;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
struct EFI_FILE_PROTOCOL;

typedef struct {
	UINT64  Signature;
	UINT32  Revision;
	UINT32  HeaderSize;
	UINT32  CRC32;
	UINT32  Reserved;
} EFI_TABLE_HEADER;

typedef struct {
	UINT32 Data1;
	UINT16 Data2;
	UINT16 Data3;
	UINT8  Data4[8];
} EFI_GUID;

typedef struct {
	EFI_GUID            VendorGuid;
	VOID               *VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct {
	EFI_TABLE_HEADER          Hdr;
	CHAR16               *FirmwareVendor;
	UINT32               FirmwareRevision;
	EFI_HANDLE             ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *ConIn;
	EFI_HANDLE             ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *ConOut;
	EFI_HANDLE             StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *StdErr;
	EFI_RUNTIME_SERVICES        *RuntimeServices;
	EFI_BOOT_SERVICES          *BootServices;
	UINTN                NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE       *ConfigurationTable;
} EFI_SYSTEM_TABLE;

//============================================================================
//EVENTS
//============================================================================

typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT Event,
	IN VOID    *Context
	);

#define EVT_RUNTIME 40000000

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32             Type,
	IN EFI_TPL            NotifyTpl,
	IN EFI_EVENT_NOTIFY   NotifyFunction, OPTIONAL
	IN VOID               *NotifyContext, OPTIONAL
	OUT EFI_EVENT         *Event
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
	IN EFI_EVENT Event
	);

typedef EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
	IN EFI_EVENT Event
	);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN       NumberOfEvents,
	IN EFI_EVENT   *Event,
	OUT UINTN      *Index
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
	IN EFI_EVENT Event
	);

typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT           Event,
	IN EFI_TIMER_DELAY     Type,
	IN UINT64              TriggerTime
	);

typedef EFI_TPL
(EFIAPI *EFI_RAISE_TPL) (
	IN EFI_TPL NewTpl
	);

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL) (
	IN EFI_TPL OldTpl
	);

//============================================================================
//MALLOC
//============================================================================

typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES) (IN EFI_ALLOCATE_TYPE        Type,
	IN EFI_MEMORY_TYPE          MemoryType,
	IN UINTN                    Pages,
	IN OUT EFI_PHYSICAL_ADDRESS *Memory
	);

typedef EFI_STATUS
(EFIAPI *EFI_FREE_PAGES) (
	IN EFI_PHYSICAL_ADDRESS	Memory,
	IN UINTN
	);

#define EFI_MEMORY_UC            0x0000000000000001
#define EFI_MEMORY_WC            0x0000000000000002
#define EFI_MEMORY_WT            0x0000000000000004
#define EFI_MEMORY_WB            0x0000000000000008
#define EFI_MEMORY_UCE           0x0000000000000010
#define EFI_MEMORY_WP            0x0000000000001000
#define EFI_MEMORY_RP            0x0000000000002000
#define EFI_MEMORY_XP            0x0000000000004000
#define EFI_MEMORY_NV            0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO            0x0000000000020000
#define EFI_MEMORY_RUNTIME       0x8000000000000000

typedef struct {
	UINT32        Type;
	EFI_PHYSICAL_ADDRESS   PhysicalStart;
	EFI_VIRTUAL_ADDRESS    VirtualStart;
	UINT64                 NumberOfPages;
	UINT64                 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP) (
	IN OUT UINTN                 *MemoryMapSize,
	IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
	OUT UINTN                    *MapKey,
	OUT UINTN                    *DescriptorSize,
	OUT UINT32                   *DescriptorVersion);

typedef EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL) (
	IN EFI_MEMORY_TYPE   PoolType,
	IN UINTN	      Size,
	OUT VOID             **Buffer
	);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL) (
	IN VOID   *Buffer
	);

//============================================================================
//PROTOCOLS
//============================================================================

typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
	IN OUT EFI_HANDLE     *Handle,
	IN EFI_GUID           *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType,
	IN VOID               *Interface
	); 

typedef EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE    Handle,
	IN EFI_GUID      *Protocol,
	IN VOID          *Interface
	);

typedef EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID   *Protocol,
	IN VOID       *OldInterface,
	IN VOID       *NewInterface
	);

typedef EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
	IN EFI_GUID  *Protocol,
	IN EFI_EVENT Event,
	OUT VOID   **Registration
	);

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
	IN EFI_LOCATE_SEARCH_TYPE  SearchType,
	IN EFI_GUID                *Protocol OPTIONAL,
	IN VOID                    *SearchKey OPTIONAL,
	IN OUT UINTN               *BufferSize,
	OUT EFI_HANDLE             *Buffer
	);

typedef EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
	IN EFI_HANDLE    Handle,
	IN EFI_GUID      *Protocol,
	OUT VOID         **Interface
	);

#define EFI_DEVICE_PATH_PROTOCOL void*

typedef EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
	IN EFI_GUID                      *Protocol,
	IN OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
	OUT EFI_HANDLE                   *Device);

typedef EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
	IN EFI_HANDLE      Handle,
	IN EFI_GUID        *Protocol,
	OUT VOID           **Interface OPTIONAL,
	IN EFI_HANDLE      AgentHandle,
	IN EFI_HANDLE      ControllerHandle,
	IN UINT32          Attributes
	);

typedef EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
	IN EFI_HANDLE      Handle,
	IN EFI_GUID        *Protocol,
	IN EFI_HANDLE      AgentHandle,
	IN EFI_HANDLE      ControllerHandle
	);

typedef struct {
	EFI_HANDLE       AgentHandle;
	EFI_HANDLE       ControllerHandle;
	UINT32           Attributes;
	UINT32           OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
	IN EFI_HANDLE                            Handle,
	IN EFI_GUID                              *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY  **EntryBuffer, 
	OUT UINTN                                *EntryCount
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
	IN EFI_HANDLE                ControllerHandle,
	IN EFI_HANDLE                *DriverImageHandle  OPTIONAL,
	IN EFI_DEVICE_PATH_PROTOCOL  *RemainingDevicePath OPTIONAL,
	IN BOOLEAN                   Recursive
	);

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE DriverImageHandle OPTIONAL,
	IN EFI_HANDLE ChildHandle    OPTIONAL
	);

typedef  EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
	IN EFI_HANDLE Handle,
	OUT EFI_GUID  ***ProtocolBuffer,
	OUT UINTN     *ProtocolBufferCount
	);

typedef EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
	IN EFI_LOCATE_SEARCH_TYPE  SearchType,
	IN EFI_GUID                *Protocol  OPTIONAL, 
	IN VOID                    *SearchKey OPTIONAL,
	IN OUT UINTN               *NoHandles,
	OUT EFI_HANDLE             **Buffer
	);

typedef
EFI_STATUS
(EFIAPI* EFI_EXIT_BOOT_SERVICES) (
	IN EFI_HANDLE ImageHandle,
	IN UINTN MapKey
	);

#define EFI_INSTALL_CONFIGURATION_TABLE void*
#define EFI_IMAGE_LOAD void*
#define EFI_IMAGE_START void*
#define EFI_GET_NEXT_MONOTONIC_COUNT void*
#define EFI_STALL void*
#define EFI_SET_WATCHDOG_TIMER void*
#define EFI_EXIT void*
#define EFI_IMAGE_UNLOAD void*

typedef struct EFI_BOOT_SERVICES {
	EFI_TABLE_HEADER         Hdr;
	//
	// Task Priority Services
	//
	EFI_RAISE_TPL             RaiseTPL;            // EFI 1.0+  
	EFI_RESTORE_TPL           RestoreTPL;          // EFI 1.0+

	//											   //
	//											   // Memory Services
	//											   //
	EFI_ALLOCATE_PAGES              AllocatePages;       // EFI 1.0+   
	EFI_FREE_PAGES                  FreePages;           // EFI 1.0+
	EFI_GET_MEMORY_MAP              GetMemoryMap;        // EFI 1.0+   
	EFI_ALLOCATE_POOL               AllocatePool;        // EFI 1.0+   
	EFI_FREE_POOL                   FreePool;            // EFI 1.0+

	//													 //
	//													 // Event & Timer Services
	//													 //
	EFI_CREATE_EVENT                 CreateEvent;        // EFI 1.0+
	EFI_SET_TIMER                    SetTimer;           // EFI 1.0+
	EFI_WAIT_FOR_EVENT               WaitForEvent;       // EFI 1.0+
	EFI_SIGNAL_EVENT                 SignalEvent;        // EFI 1.0+
	EFI_CLOSE_EVENT                  CloseEvent;         // EFI 1.0+   
	EFI_CHECK_EVENT                  CheckEvent;         // EFI 1.0+

	//													 //
	//													 // Protocol Handler Services
	//													 //
	EFI_INSTALL_PROTOCOL_INTERFACE   InstallProtocolInterface; // EFI 1.0+   
	EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
	EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+ 
	EFI_HANDLE_PROTOCOL              HandleProtocol;   // EFI 1.0+
	VOID*              Reserved; // EFI 1.0+
	EFI_REGISTER_PROTOCOL_NOTIFY     RegisterProtocolNotify;    // EFI 1.0+
	EFI_LOCATE_HANDLE                LocateHandle;     // EFI 1.0+   
	EFI_LOCATE_DEVICE_PATH           LocateDevicePath; // EFI 1.0+
	EFI_INSTALL_CONFIGURATION_TABLE   InstallConfigurationTable; // EFI 1.0+

	//															 //
	//															 // Image Services
	//															 //
	EFI_IMAGE_LOAD                   LoadImage;         // EFI 1.0+
	EFI_IMAGE_START                  StartImage;        // EFI 1.0+   
	EFI_EXIT                         Exit;              // EFI 1.0+   
	EFI_IMAGE_UNLOAD                 UnloadImage;       // EFI 1.0+   
	EFI_EXIT_BOOT_SERVICES           ExitBootServices;  // EFI 1.0+

	//													//
	//													// Miscellaneous Services
	//													//
	EFI_GET_NEXT_MONOTONIC_COUNT    GetNextMonotonicCount; // EFI 1.0+
	EFI_STALL                      Stall;              // EFI 1.0+
	EFI_SET_WATCHDOG_TIMER          SetWatchdogTimer;   // EFI 1.0+

	//													//
	//													// DriverSupport Services
	//													//
	EFI_CONNECT_CONTROLLER          ConnectController;   // EFI 1.1
	EFI_DISCONNECT_CONTROLLER       DisconnectController;// EFI 1.1+

	//													 //
	//													 // Open and Close Protocol Services
	//													 //
	EFI_OPEN_PROTOCOL                OpenProtocol;       // EFI 1.1+
	EFI_CLOSE_PROTOCOL               CloseProtocol;           // EFI 1.1+  
	EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation; // EFI 1.1+

	//														  //
	//														  // Library Services
	//														  //
	EFI_PROTOCOLS_PER_HANDLE         ProtocolsPerHandle;     // EFI 1.1+
	EFI_LOCATE_HANDLE_BUFFER         LocateHandleBuffer;     // EFI 1.1+
	//EFI_LOCATE_PROTOCOL              LocateProtocol;         // EFI 1.1+
	//EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES
	//	InstallMultipleProtocolInterfaces;   // EFI 1.1+
	//EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES
	//	UninstallMultipleProtocolInterfaces; // EFI 1.1+

	//										 //
	//										 // 32-bit CRC Services
	//										 //
	//EFI_CALCULATE_CRC32              CalculateCrc32;           // EFI 1.1+

	//														   //
	//														   // Miscellaneous Services
	//														   //
	//EFI_COPY_MEM                     CopyMem;                  // EFI 1.1+   
	//EFI_SET_MEM                      SetMem;                   // EFI 1.1+
	//EFI_CREATE_EVENT_EX              CreateEventEx;            // UEFI 2.0+  
} EFI_BOOT_SERVICES;

typedef struct EFI_RUNTIME_SERVICES {
	EFI_TABLE_HEADER             Hdr;

	////
	//// Time Services
	////
	//EFI_GET_TIME                   GetTime;
	//EFI_SET_TIME                   SetTime;
	//EFI_GET_WAKEUP_TIME            GetWakeupTime;
	//EFI_SET_WAKEUP_TIME            SetWakeupTime;

	////
	//// Virtual Memory Services
	////
	//EFI_SET_VIRTUAL_ADDRESS_MAP    SetVirtualAddressMap;
	//EFI_CONVERT_POINTER             ConvertPointer;

	////
	//// Variable Services
	////
	//EFI_GET_VARIABLE               GetVariable;                
	//EFI_GET_NEXT_VARIABLE_NAME     GetNextVariableName;
	//EFI_SET_VARIABLE               SetVariable;
	////
	//// Miscellaneous Services
	////
	//EFI_GET_NEXT_HIGH_MONO_COUNT   GetNextHighMonotonicCount;
	//EFI_RESET_SYSTEM               ResetSystem;
	////
	//// UEFI 2.0 Capsule Services
	//// 
	//EFI_UPDATE_CAPSULE              UpdateCapsule;
	//EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;
	////
	//// Miscellaneous UEFI 2.0 Service
	////
	//EFI_QUERY_VARIABLE_INFO         QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

#include "efi-drawing.h"
#include "efi_text_input.h"
#include "efi_text_output.h"
#include "efi_graphics.h"
#include "efi_filesystem.h"
#include "efi_mp.h"