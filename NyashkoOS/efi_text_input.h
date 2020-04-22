#pragma once
#include "efi.h"

//============================================================================
//INPUT
//============================================================================

typedef UINT8	EFI_KEY_TOGGLE_STATE;
#define EFI_TOGGLE_STATE_VALID	0x80
#define EFI_KEY_STATE_EXPOSED	0x40
#define EFI_SCROLL_LOCK_ACTIVE	0x01
#define EFI_NUM_LOCK_ACTIVE		0x02
#define EFI_CAPS_LOCK_ACTIVE	0x04

typedef struct EFI_KEY_STATE {
	UINT32                KeyShiftState;
	EFI_KEY_TOGGLE_STATE  KeyToggleState;
} EFI_KEY_STATE;

typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct {
	EFI_INPUT_KEY    Key;
	EFI_KEY_STATE    KeyState;
} EFI_KEY_DATA;

typedef
EFI_STATUS
(EFIAPI* EFI_INPUT_RESET_EX) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN BOOLEAN                           ExtendedVerification);

typedef
EFI_STATUS
(EFIAPI* EFI_INPUT_READ_KEY_EX) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	OUT EFI_KEY_DATA* KeyData
	);

typedef EFI_STATUS
(EFIAPI* EFI_SET_STATE) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN EFI_KEY_TOGGLE_STATE* KeyToggleState);

typedef
EFI_STATUS
(EFIAPI* EFI_KEY_NOTIFY_FUNCTION) (
	IN EFI_KEY_DATA* KeyData
	);

typedef
EFI_STATUS
(EFIAPI* EFI_REGISTER_KEYSTROKE_NOTIFY) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN EFI_KEY_DATA* KeyData,
	IN EFI_KEY_NOTIFY_FUNCTION            KeyNotificationFunction,
	OUT VOID** NotifyHandle);

typedef
EFI_STATUS
(EFIAPI* EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
	IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* This,
	IN VOID* NotificationHandle);

typedef struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
	EFI_INPUT_RESET_EX	Reset;
	EFI_INPUT_READ_KEY_EX	ReadKeyStrokeEx;
	EFI_EVENT	WaitForKeyEx;
	EFI_SET_STATE	SetState;
	EFI_REGISTER_KEYSTROKE_NOTIFY	RegisterKeyNotify;
	EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
} EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI* EFI_INPUT_RESET) (
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
	IN BOOLEAN                         ExtendedVerification);

typedef
EFI_STATUS
(EFIAPI* EFI_INPUT_READ_KEY) (
	IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL* This,
	OUT EFI_INPUT_KEY* Key
	);

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET     Reset;
	EFI_INPUT_READ_KEY  ReadKeyStroke;
	EFI_EVENT           WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
