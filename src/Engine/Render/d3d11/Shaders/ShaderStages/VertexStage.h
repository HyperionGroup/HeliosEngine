#pragma once
#include "ShaderStage.h"

namespace render
{
    template< typename TVertexType >
    class CVertexStage : public CShaderStage
    {
    public:
        CVertexStage() = default;
        virtual ~CVertexStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device, const std::string& aShaderCode )
        {
            m_Type = ShaderStageType::VertexStage;
            m_EntryPoint = "mainVS";
            CShaderStage::Initialize(_device, aShaderCode);
            DXCall(_device->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VertexShader->GetInterfacePtr()));
            TVertexType::CreateInputLayout(_device, m_Blob, &m_VertexLayout);
        }

        virtual void ShutDown()
        {
            DXCheckedRelease(m_VertexShader);
            DXCheckedRelease(m_VertexLayout);
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
            return CDevice::GetInstance().GetVertexStageFeatureLevel();
        }
    };
}