#include "TextureAsset.h"
#include "Logger/Logger.h"

#include <cereal/types/base_class.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace io
{
    CTextureAsset::CTextureAsset( const std::string& _fileName )
        : CAsset(_fileName)
        , mHeight(0)
        , mWidth(0)
    {
    }

    CTextureAsset::~CTextureAsset()
    {

    }

    bool CTextureAsset::Load()
    {
        unsigned char* data = stbi_load(mID.c_str(), &mWidth, &mHeight, &mNumComponents, 4);
        LOG_ERROR_APPLICATION_IF(data == nullptr, "Unable to load texture %s", mID.c_str());
        stbi_image_free(data);
        return false;
    }
}