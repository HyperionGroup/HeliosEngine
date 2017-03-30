#ifndef _RENDER_SAMPLER_
#define _RENDER_SAMPLER_

#pragma once

#include "Render.h"

namespace render
{
    class CTexture
    {
        SERIALIZABLE
        private:
            CSamplerPtr mSampler;
            uint32      mHeight;
            uint32      mWidht;
            uint8*      mData;
        public:
            CTexture();
            virtual ~CTexture();
    };

    SERIALIZABLE_SAVE_DECLARATION(CTexture)
    {
    }

    SERIALIZABLE_LOAD_DECLARATION(CTexture)
    {
    }
}

#endif