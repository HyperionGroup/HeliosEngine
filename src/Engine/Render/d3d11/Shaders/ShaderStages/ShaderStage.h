#pragma once

namespace render
{
    class CShaderStage
    {
    public:
        CShaderStage() = default;
        virtual ~CShaderStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device, const std::string& _src, const std::string& _preprocessor );
        virtual void ShutDown();
        virtual void Bind(ID3D11DeviceContextPtr _device) = 0;
        virtual void Unbind(ID3D11DeviceContextPtr _device) = 0;

    protected:
        ID3DBlob        *m_Blob;
        std::string     mSource;
        bool            mInitialized;
        
        virtual const char* GetShaderModel() = 0;
    };
}