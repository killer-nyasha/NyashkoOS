#pragma once
#include "efi.h"
#include "../../Vanguard/Vanguard/vectors.h"
#include "fsi.h"
#include "core_globals.h"

struct RasterFont
{
	Pixel rfont[256][25][14];

	szvect2 charSize = ivect2(14, 24);
	size_t charIndex_from = 30;
	size_t charIndex_to = 256;
	size_t charsInLine = 83;
	szvect2 offset = ivect2(1, 4);

	RasterFont(const FsiFile& font)
	{
		for (int i = charIndex_from; i < charIndex_to; i++)
		{
			int x = offset.x;
			int y = offset.y;

			x += charSize.x * (i - charIndex_from);

			while (x >= charsInLine * charSize.x)
				x -= charsInLine * charSize.x, y += charSize.y;

			for (int y1 = 0; y1 < charSize.y; y1++)
				for (int x1 = 0; x1 < charSize.x; x1++)
				{
					int nx = x + x1;
					int ny = y + y1;

					rfont[i][y1][x1] = font(nx, ny);

					rfont[i][y1][x1].Reserved = (rfont[i][y1][x1].Red + rfont[i][y1][x1].Green + rfont[i][y1][x1].Blue) / 3;

				}
		}
	}

	void applyAlpha(const Pixel& src, Pixel& dst)
	{
		float factor = src.Reserved / 255.0f;
		dst.Red =
			(int)(dst.Red * (1.0f - factor)
				+ factor * src.Red);
		dst.Green =
			(int)(dst.Green * (1.0f - factor)
				+ factor * src.Green);
		dst.Blue =
			(int)(dst.Blue * (1.0f - factor)
				+ factor * src.Blue);
	}

	void print(Image& img, ivect2 minCoord, ivect2 maxCoord, ivect2& coord, const wchar_t* string)
	{
		int i = 0;

		while (string[i] != 0)
		{
			if (coord.y + charSize.y >= maxCoord.y)
				break;

			for (size_t y = 0; y < charSize.y; y++)
				for (size_t x = 0; x < charSize.x; x++)
				{
					applyAlpha(rfont[string[i]][y][x], img(coord.x + x, coord.y + y));
				}

			//Gop->Blt(Gop, (Pixel*)rfont[string[i]], EfiBltBufferToVideo, 0, 0, coord.x, coord.y, charSize.x, charSize.y, 0);

			coord.x += charSize.x;
			if (string[i] == '\n' || coord.x + charSize.x >= maxCoord.x)
			{
				coord.y += charSize.y;
				coord.x = minCoord.x;
			}
			i++;
		}
	}
};
