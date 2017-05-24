#include "Render.h"

#include "Texture.h"

namespace render
{
    CTexture::CTexture()
        : mData(nullptr)
        , mColorFormat(render::PixelDesc::RGBA32F)
    {

    }

    CTexture::~CTexture()
    {

    }
}