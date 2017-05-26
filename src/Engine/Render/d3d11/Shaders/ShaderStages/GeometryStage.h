#pragma once

#include "ShaderStage.h"

namespace render
{
    class CGeometryStage : public CShaderStage
    {
    public:
        CGeometryStage() = default;
        virtual ~CGeometryStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device);
        virtual void ShutDown();
        virtual void Bind(ID3D11DeviceContextPtr _device);
        virtual void Unbind(ID3D11DeviceContextPtr _device);

    protected:
        virtual const char* GetShaderModel();
    private:
        ID3D11GeometryShader *m_GeometryShader;
    };
}