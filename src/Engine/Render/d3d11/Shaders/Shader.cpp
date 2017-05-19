#include "Render.h"
#include "Shader.h"
#include "ShaderStages/ShaderStage.h"

namespace render
{
    CShader::CShader()
    {
        mShaders.resize( static_cast<uint32>( ShaderStageType::MAX ), nullptr);
    }

    CShader::~CShader()
    {
        for (CShaderStage* stage : mShaders)
        {
            delete stage;
            stage = nullptr;
        }
    }

    void CShader::SetStage(ShaderStageType _stage, CShaderStage* _shaderstage)
    {
        HELIOSASSERT( mShaders[static_cast<int>(_stage)] == nullptr );
        mShaders[static_cast<int>(_stage)] = _shaderstage;
    }

    void CShader::Bind(ID3D11DeviceContextPtr _device)
    {
        for(CShaderStage* lShader : mShaders )
            if (lShader) lShader->Bind(_device);
    }

    void CShader::Unbind(ID3D11DeviceContextPtr _device)
    {
        for (CShaderStage* lShader : mShaders)
            if (lShader) lShader->Unbind(_device);
    }

}