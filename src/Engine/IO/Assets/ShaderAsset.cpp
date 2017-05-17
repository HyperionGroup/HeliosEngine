#include "IO.h"

#include "ShaderAsset.h"
#include "Shaders\ShaderCompiler.h"

namespace io
{
    CShaderAsset::CShaderAsset()
        : CAsset()
    {
        
    }

    CShaderAsset::~CShaderAsset()
    {

    }

    bool CShaderAsset::Load()
    {
        render::CShaderCompiler& lShaderCompiler = render::CShaderCompiler::GetInstance();
        render::CShader* lShader = lShaderCompiler.LoadShader(mFlags, mVertexStage, mPixelStage);
        return false;
    }

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