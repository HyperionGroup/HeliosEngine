#ifndef _IO_TEXTURE_ASSET_
#define _IO_TEXTURE_ASSET_

#pragma once

#include "Asset.h"
#include "Serializable.h"
#include "Core.h"

namespace io
{
    class CTextureAsset : public CAsset
    {
        SERIALIZABLE
        private:
            int32              mHeight;
            int32              mWidth;
            int32              mNumComponents;
        public:
            CTextureAsset( const std::string& _fileName );
            virtual ~CTextureAsset();
            virtual bool Load();
    };

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CTextureAsset)
    {
        CAsset::save(ar);
        ar(mHeight);
    }

    SERIALIZABLE_LOAD_DECLARATION(CTextureAsset)
    {

    }
#pragma endregion Serialization

}
#endif