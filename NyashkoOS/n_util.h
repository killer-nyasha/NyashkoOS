#pragma once
#include "efi.h"

inline wchar_t* uintToTempString(UINTN u)
{
	static wchar_t buffer[32];
	buffer[31] = 0;
	UINTN i = 30;
	do {
		UINTN r = u % 10;
		u /= 10;
		buffer[i--] = L'0' + r;
	} while (u != 0);
	return &buffer[i + 1];
}

//íå ñîîáùàåò îá îøèáêàõ
inline UINTN stringToUint(wchar_t* str, wchar_t** end)
{
	UINTN i = 0;
	UINTN r = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r *= 10; r += str[i] - '0';
		i++;
	};
	if (end != nullptr) *end = &str[i];
	return r;
}