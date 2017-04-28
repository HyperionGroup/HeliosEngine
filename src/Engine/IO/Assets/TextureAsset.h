#ifndef _IO_TEXTURE_ASSET_
#define _IO_TEXTURE_ASSET_

#pragma once

#include "Asset.h"
#include "Serializable.h"
#include "IO.h"

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

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CTextureAsset)
    {
        CAsset::save(ar);
        TO_ARCHIVE(Filename);
    }

    SERIALIZABLE_LOAD_DECLARATION(CTextureAsset)
    {

    }
#pragma endregion Serialization

}
#endif