#pragma once

#include "ShaderStage.h"

namespace render
{
    class CPixelStage : public CShaderStage
    {
    public:
        CPixelStage() = default;
        virtual ~CPixelStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device);
        virtual void ShutDown();
        virtual void Bind(ID3D11DeviceContextPtr _device);
        virtual void Unbind(ID3D11DeviceContextPtr _device);

    protected:
        virtual const char* GetShaderModel();
    private:
        ID3D11PixelShader *m_PixelShader;
    };
}