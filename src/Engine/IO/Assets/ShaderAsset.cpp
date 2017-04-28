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
}