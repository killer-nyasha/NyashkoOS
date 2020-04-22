#include "efi.h"
#include "efi_text_input.h"
#include "efi_text_output.h"
#include "efi_graphics.h"
#include "efi_filesystem.h"

#pragma once

//глобальные переменные ядра
extern UINTN handleCount;
extern EFI_HANDLE* handleBuffer;

extern EFI_HANDLE EfiHandle;
extern EFI_SYSTEM_TABLE* EfiTable;
extern EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* ConOut;
extern EFI_SIMPLE_TEXT_INPUT_PROTOCOL* ConIn;
extern EFI_BOOT_SERVICES* BootServices;
extern EFI_GRAPHICS_OUTPUT_PROTOCOL* Gop;
extern EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;

extern EFI_MEMORY_DESCRIPTOR* MemoryMap;

//guid протоколов
extern EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
extern EFI_GUID EFI_FILE_SYSTEM_PROTOCOL_GUID;

