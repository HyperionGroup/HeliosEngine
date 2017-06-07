#pragma once

#include "ShaderStage.h"
#include "Serialization/Serializable.h"
#include "ImmediateGui/ImmediateGui.h"
#include "Name.h"

namespace render
{
    class CShaderStage;
    class CShader : public io::CSerializableEntity, public core::CName, public gui::CImmediateGui
    {
        SERIALIZABLE
    public:
        CShader();
        virtual ~CShader() = default;
        void Bind(ID3D11DeviceContextPtr _device);
        void Unbind(ID3D11DeviceContextPtr _device);
        virtual void OnGui();

    private:
        std::vector< std::shared_ptr<CShaderStage> > mShaders;
    };
}