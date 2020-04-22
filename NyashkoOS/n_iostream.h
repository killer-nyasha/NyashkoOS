#pragma once
#include "efi.h"
#include "n_util.h"
#include "core_globals.h"

class OutStream
{
public:
	OutStream& operator <<(const wchar_t* str)
	{
		ConOut->OutputString(ConOut, str);
		return *this;
	}

	OutStream& operator <<(const UINTN i)
	{
		ConOut->OutputString(ConOut, uintToTempString(i));
		return *this;
	}
}; 
extern OutStream rcout;

class InStream
{
public:
	EFI_INPUT_KEY key;

	InStream& operator >>(CHAR16& ch)
	{
		while ((ConIn->ReadKeyStroke(ConIn, &key) != EFI_SUCCESS));
		ch = key.UnicodeChar;
		return *this;
	}

	InStream& operator >>(CHAR16*& str)
	{
		//TODO
		return *this;
	}

	InStream& operator >>(UINTN& i)
	{
		//TODO
		return *this;
	}
}; 
extern InStream rcin;

inline void pink_screen_of_death(int code)
{
	ConOut->SetMode(ConOut, 0);
	ConOut->SetAttribute(ConOut, EFI_BRIGHT | EFI_WHITE | EFI_BACKGROUND_MAGENTA);
	rcout << L"oh, fuck :(\r\nNyashkoOS met a critical error\r\n";
	rcout << L"error code: " << code;
	while (true) { }
}

inline void pink_screen_of_death() { pink_screen_of_death(0); }