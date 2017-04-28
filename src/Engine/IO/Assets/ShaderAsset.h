#ifndef _ShaderAsset_
#define _ShaderAsset_

#pragma once

#include "Asset.h"
#include "Serializable.h"
#include "Core.h"

namespace io
{
    class CShaderAsset : public CAsset
    {
        SERIALIZABLE
    private:
        std::vector< std::string > mFlags;
        std::string mVertexStage;
        std::string mPixelStage;
    public:
        CShaderAsset();
        virtual ~CShaderAsset();
        virtual bool Load();
    };

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CShaderAsset)
    {
        TO_ARCHIVE(Flags);
        TO_ARCHIVE(VertexStage);
        TO_ARCHIVE(PixelStage);
    }

    SERIALIZABLE_LOAD_DECLARATION(CShaderAsset)
    {
        FROM_ARCHIVE(Flags);
        FROM_ARCHIVE(VertexStage);
        FROM_ARCHIVE(PixelStage);
        Load();
    }
#pragma endregion Serialization

}
#endif