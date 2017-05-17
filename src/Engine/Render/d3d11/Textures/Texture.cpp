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

    SERIALIZABLE_SAVE_DECLARATION(CTexture)
    {
        TO_ARCHIVE_SPTR(Sampler);
        TO_ARCHIVE(Height);
        TO_ARCHIVE(Width);
        TO_ARCHIVE_ENUM(ColorFormat);
        TO_ARCHIVE_BINARY("Data", mData, )
    }

    SERIALIZABLE_LOAD_DECLARATION(CTexture)
    {
    }
}