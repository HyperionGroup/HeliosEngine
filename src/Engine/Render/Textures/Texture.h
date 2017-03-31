#ifndef _RENDER_TEXTURE_
#define _RENDER_TEXTURE_

#pragma once

#include "Render.h"

namespace render
{
    class CTexture
    {
        SERIALIZABLE
        private:
            CSamplerPtr         mSampler;
            render::PixelDesc   mColorFormat;
            uint8*              mData;
        public:
            CTexture();
            virtual ~CTexture();
    };

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

#endif