#include "Shader.h"
#include "ShaderStages/ShaderStage.h"

namespace render
{
    CShader::CShader()
    {
        mShaders.resize(ShaderStageType::StagesCount, nullptr);
    }

    CShader::~CShader()
    {
    }

    void CShader::SetStage(ShaderStageType _stage, CShaderStagePtr _shaderstage)
    {
        HELIOSASSERT( mShaders[static_cast<int>(_stage)] == nullptr );
        mShaders[static_cast<int>(_stage)] = _shaderstage;
    }

    void CShader::Bind(CDevicePtr _device)
    {
        for( CShaderStagePtr lShader : mShaders )
        {
            if (lShader) lShader->Bind(_device);
        }
    }
}