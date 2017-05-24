#ifndef _RENDER_TEXTURE_
#define _RENDER_TEXTURE_

#pragma once

namespace render
{
    class CTexture
    {
        private:
            render::PixelDesc   mColorFormat;
            uint8*              mData;
        public:
            CTexture();
            virtual ~CTexture();
    };
}

#endif