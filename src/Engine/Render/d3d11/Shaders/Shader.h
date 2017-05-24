#pragma once

#include "ShaderStages\ShaderStage.h"

namespace render
{
    class CShaderStage;
    class CShader
    {
    public:
        CShader()
        {
            mShaders.resize(static_cast<int>(ShaderStageType::MAX), nullptr);
        }

        virtual ~CShader()
        {
            for (CShaderStage* stage : mShaders)
            {
                CHECKED_DELETE( stage );
            }
        }
        
        void SetStage(ShaderStageType _stagetype, CShaderStage* _shaderstage)
        {
            mShaders[static_cast<int>(_stagetype)] = _shaderstage;
        }

        void Bind(ID3D11DeviceContextPtr _device)
        {
            for (CShaderStage* lShader : mShaders)
                if (lShader) lShader->Bind(_device);
        }

        void Unbind(ID3D11DeviceContextPtr _device)
        {
            for (CShaderStage* lShader : mShaders)
                if (lShader) lShader->Unbind(_device);
        }

    private:
        std::vector< CShaderStage* > mShaders;
        uint32 mFlags;
    };
}