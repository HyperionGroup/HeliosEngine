#include "IO.h"

#include "TextureAsset.h"

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