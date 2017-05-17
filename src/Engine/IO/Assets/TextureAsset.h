#ifndef _IO_TEXTURE_ASSET_
#define _IO_TEXTURE_ASSET_

#pragma once

#include "Asset.h"

namespace io
{
    class CTextureAsset : public CAsset
    {
        SERIALIZABLE
    private:
        int32              mHeight;
        int32              mWidth;
        int32              mNumComponents;
        std::string        mFilename;
    public:
        CTextureAsset();
        virtual ~CTextureAsset();
        virtual bool Load();
    };
}
#endif