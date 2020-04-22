#include "core_globals.h"

//глобальные переменные ядра
EFI_HANDLE EfiHandle;
EFI_SYSTEM_TABLE* EfiTable;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
EFI_BOOT_SERVICES* BootServices;
EFI_GRAPHICS_OUTPUT_PROTOCOL* Gop;
EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;

EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID =
{ 0x9042a9de,0x23dc,0x4a38,{ 0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a } };
EFI_GUID EFI_FILE_SYSTEM_PROTOCOL_GUID =
{ 0x964e5b22,0x6459,0x11d2,{ 0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b } };

extern "C" int _fltused = 0;

EFI_MEMORY_DESCRIPTOR* MemoryMap = nullptr;

UINTN handleCount;
EFI_HANDLE* handleBuffer = nullptr;