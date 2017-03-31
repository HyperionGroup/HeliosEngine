#pragma once

#include "Render.h"

namespace render
{
    static const uint32 sBitsPerPixel[PixelDesc::PixelBitsCount] =
    {
        0,   //Unknown
        32,  //R32F
        64,  //RG32F
        96,  //RGB32F
        128, //RGBA32f
        16,  //R16F
        32,  //RG16F
        48,  //RGB16F
        64,  //RGBA16f
    };

    uint16 BytesPerPixel(PixelDesc _pixelDesc)
    {
        return sBitsPerPixel[_pixelDesc];
    }
}