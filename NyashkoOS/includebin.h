#pragma once
#include "fsi.h"

extern "C" unsigned char __wallpaper[];
extern "C" unsigned char __font[];

FsiFile& ___wallpaper()
{
	return *(FsiFile*)__wallpaper;
}

FsiFile& ___font()
{
	return *(FsiFile*)__font;
}

#define __WALLPAPER ___wallpaper()
#define __FONT ___font()