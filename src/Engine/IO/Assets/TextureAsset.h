#ifndef _IO_TEXTURE_ASSET_
#define _IO_TEXTURE_ASSET_

#pragma once

#include "Asset.h"
#include "Serializable.h"
#include <string>

namespace io
{
    class CTextureAsset : public CAsset
    {
        private:
            int32              mHeight;
            int32              mWidth;
            int32              mNumComponents;
        public:
            CTextureAsset( const std::string& _fileName );
            virtual ~CTextureAsset();
            virtual bool Load();
    };
}
#endif