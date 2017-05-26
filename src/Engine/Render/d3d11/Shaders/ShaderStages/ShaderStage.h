#pragma once

#include "Serialization\Serializable.h"

#include "Device.h"

namespace render
{
    class CShaderStage : public io::CSerializableEntity
    {
        SERIALIZABLE
    public:
        CShaderStage() = default;
        virtual ~CShaderStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device);
        virtual void ShutDown();
        virtual void Bind(ID3D11DeviceContextPtr _device) = 0;
        virtual void Unbind(ID3D11DeviceContextPtr _device) = 0;

    protected:
        ID3DBlob        *m_Blob;
        std::string     mSource;
        std::string     mMacros;
        bool            mInitialized;
        
        virtual const char* GetShaderModel() = 0;
    };
}