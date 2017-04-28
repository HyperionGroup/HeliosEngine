#include "TextureAsset.h"
#include "Logger/Logger.h"

#include <cereal/types/base_class.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace io
{
    CTextureAsset::CTextureAsset()
        : CAsset()
    {
    }

    CTextureAsset::~CTextureAsset()
    { 

    }

    bool CTextureAsset::Load()
    {
        unsigned char* data = stbi_load(mFilename.c_str(), &mWidth, &mHeight, &mNumComponents, 4);
        LOG_ERROR_APPLICATION_IF(data == nullptr, "Unable to load texture %s", mFilename.c_str());
        stbi_image_free(data);
        return false;
    }
}