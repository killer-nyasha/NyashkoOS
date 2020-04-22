#pragma once

typedef struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
	UINT8  Blue;
	UINT8  Green;
	UINT8  Red;
	UINT8  Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

#include "../../Vanguard/Vanguard/vectors.h"
#include "../../Vanguard/Vanguard/matrix.h"

using Pixel = EFI_GRAPHICS_OUTPUT_BLT_PIXEL;
using Image = matrix<Pixel>;