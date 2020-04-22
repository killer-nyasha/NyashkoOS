#pragma once
#include "efi.h"

#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000

typedef
EFI_STATUS
(EFIAPI* EFI_FILE_OPEN) (
	IN EFI_FILE_PROTOCOL* This,
	OUT EFI_FILE_PROTOCOL** NewHandle,
	IN CHAR16* FileName,
	IN UINT64 OpenMode,
	IN UINT64 Attributes
	);

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x0000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

typedef
EFI_STATUS
(EFIAPI* EFI_FILE_CLOSE) (
	IN EFI_FILE_PROTOCOL* This
	);

typedef
EFI_STATUS
(EFIAPI* EFI_FILE_DELETE) (
	IN EFI_FILE_PROTOCOL* This
	);

typedef
EFI_STATUS
(EFIAPI* EFI_FILE_READ) (
	IN EFI_FILE_PROTOCOL* This,
	IN OUT UINTN* BufferSize,
	OUT VOID* BUFFER
	);

typedef
EFI_STATUS
(EFIAPI* EFI_FILE_WRITE) (
	IN EFI_FILE_PROTOCOL* This,
	IN OUT UINTN* BufferSize,
	OUT VOID* BUFFER
	);

typedef struct EFI_FILE_PROTOCOL {
	UINT64 Revision;
	EFI_FILE_OPEN Open;
	EFI_FILE_CLOSE Close;
	EFI_FILE_DELETE Delete;
	EFI_FILE_READ Read;
	EFI_FILE_WRITE Write;
	//EFI_FILE_GET_POSITION GetPosition;
	//FILE_FILE_SET_POSITION SetPosition;
	//EFI_FILE_GET_INFO GetInfo;
	//EFI_FILE_SET_INFO SetInfo;
	//EFI_FILE_FLUSH Flush;

	////revision 2	
	//EFI_FILE_OPEN_EX OpenEx;
	//EFI_FILE_READ_EX ReadEx;
	//EFI_FILE_WRITE_EX WriteEx;
	//EFI_FILE_FLUSH_EX FlushEx;
} EFI_FILE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI* EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME) (
	IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* This,
	OUT EFI_FILE_PROTOCOL** Root
	);

typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	UINT64 Revision;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;