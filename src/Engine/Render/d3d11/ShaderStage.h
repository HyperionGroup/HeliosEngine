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

    template< typename TVertexType >
    class CVertexStage : public CShaderStage
    {
    public:
        CVertexStage() = default;
        virtual ~CVertexStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device)
        {
            CShaderStage::Initialize(_device);
            DXCall(_device->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VertexShader->GetInterfacePtr()));
            TVertexType::CreateInputLayout(_device, m_Blob, &m_VertexLayout);
        }

        virtual void ShutDown()
        {
            if (mInitialized)
            {
                DXCheckedRelease(m_VertexShader);
                DXCheckedRelease(m_VertexLayout);
                mInitialized = false;
            }
        }

        virtual void Bind(ID3D11DeviceContextPtr _device)
        {
            // Configure how the CPU will send the vertexes to the GPU( COORDS | NORMALS | COLOR | UV ... )
            _device->IASetInputLayout(m_VertexLayout);

            // Bind the vertex shader and its uniform data across all the vertexes
            _device->VSSetShader(m_VertexShader->GetInterfacePtr(), nullptr, 0);
        }
        virtual void Unbind(ID3D11DeviceContextPtr _device)
        {
            _device->VSSetShader(nullptr, nullptr, 0);
        }

    private:
        ID3D11VertexShaderPtr *m_VertexShader;
        ID3D11InputLayoutPtr m_VertexLayout;

        virtual const char* GetShaderModel()
        {
            return helios::CEngine::GetInstance().GetDevice().GetVertexStageFeatureLevel();
        }
    };

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