#pragma once
#include "RasterFont.h"

class OutGStream
{
public:
	ivect2 minCoord = ivect2(10, 10);
	ivect2 maxCoord = ivect2(10 + 1000, 10 + 800);
	ivect2 coord = ivect2(10, 10);

	Image* img = nullptr;
	RasterFont* defaultFont = nullptr;

	OutGStream() { }

	OutGStream(Image& img, RasterFont& defaultFont) : img(&img), defaultFont(&defaultFont)
	{

	}

	OutGStream& operator<<(const wchar_t* text)
	{
		defaultFont->print(*img, minCoord, maxCoord, coord, text);
		return *this;
	}

	OutGStream& operator<<(const wchar_t ch)
	{
		wchar_t buffer[2];
		buffer[0] = ch;
		buffer[1] = 0;
		defaultFont->print(*img, minCoord, maxCoord, coord, buffer);
		return *this;
	}

	OutGStream& operator <<(const UINTN i)
	{
		return *this << uintToTempString(i);
	}

	OutGStream& operator <<(const UINT32 i)
	{
		return *this << uintToTempString(i);
	}

};
