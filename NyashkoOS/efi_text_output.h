#pragma once
#include "efi.h"

//============================================================================
//OUTPUT
//============================================================================

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_RESET) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN BOOLEAN                         ExtendedVerification);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN const CHAR16* String
	);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_TEST_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN const CHAR16* String
	);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_QUERY_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN UINTN              ModeNumber,
	OUT UINTN* Columns,
	OUT UINTN* Rows
	);

typedef
EFI_STATUS
(*EFIAPI EFI_TEXT_SET_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN UINTN                           ModeNumber
	);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_SET_ATTRIBUTE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN UINTN                           Attribute
	);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_CLEAR_SCREEN) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This
	);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_SET_CURSOR_POSITION) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN UINTN                           Column,
	IN UINTN                           Row
	);

typedef
EFI_STATUS
(EFIAPI* EFI_TEXT_ENABLE_CURSOR) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* This,
	IN BOOLEAN                         Visible
	);

typedef struct {
	INT32               MaxMode;
	// current settings 
	INT32               Mode;
	INT32               Attribute;
	INT32               CursorColumn;
	INT32               CursorRow;
	BOOLEAN             CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET               Reset;
	EFI_TEXT_STRING              OutputString;
	EFI_TEXT_TEST_STRING         TestString;
	EFI_TEXT_QUERY_MODE          QueryMode;
	EFI_TEXT_SET_MODE            SetMode;
	EFI_TEXT_SET_ATTRIBUTE       SetAttribute;
	EFI_TEXT_CLEAR_SCREEN        ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR       EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE* Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
