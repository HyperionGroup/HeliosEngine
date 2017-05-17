#ifndef _RENDER_TEXTURE_
#define _RENDER_TEXTURE_

#pragma once

namespace render
{
    class CTexture
    {
        SERIALIZABLE
        private:
            render::PixelDesc   mColorFormat;
            uint8*              mData;
        public:
            CTexture();
            virtual ~CTexture();
    };
}

#endif