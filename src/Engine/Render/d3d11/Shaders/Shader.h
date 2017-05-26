#pragma once

#include "ShaderStages\ShaderStage.h"
#include "Serialization\Serializable.h"
#include "Name.h"

namespace render
{
    class CShaderStage;
    class CShader : public io::CSerializableEntity, public core::CName
    {
        SERIALIZABLE
    public:
        CShader();
        virtual ~CShader() = default;
        void Bind(ID3D11DeviceContextPtr _device);
        void Unbind(ID3D11DeviceContextPtr _device);

    private:
        std::vector< std::shared_ptr<CShaderStage> > mShaders;
    };
}