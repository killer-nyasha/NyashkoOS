#pragma once
#include "efi_graphics.h"
//#include "../../Vanguard/Vanguard/vectors.h"

//#pragma intrinsic(memcpy)

//
//extern "C" void* memcpy(void* destination, const void* source, size_t num)
//{
//	char* d = (char*)destination;
//	const char* s = (const char*)source;
//	while (num--)
//		*d++ = *s++;
//	return destination;
//}

struct FsiFile
{
	int height;
	int width;

	EFI_GRAPHICS_OUTPUT_BLT_PIXEL& operator()(size_t x, size_t y)
	{
		return ((EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)((char*)this + 8))[y * width + x];
	}

	const EFI_GRAPHICS_OUTPUT_BLT_PIXEL& operator()(size_t x, size_t y) const
	{
		return ((EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)((char*)this + 8))[y * width + x];
	}
};