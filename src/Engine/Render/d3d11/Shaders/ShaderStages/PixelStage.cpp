#include "Render.h"
#include "PixelStage.h"
#include "Device.h"

namespace render
{
    void CPixelStage::Initialize(ID3D11DevicePtr _device, const std::string& aShaderCode)
    {
        m_EntryPoint = "mainPS";
        m_Type = ShaderStageType::PixelStage;
        CShaderStage::Initialize(_device, aShaderCode);
        DXCall(_device->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PixelShader));
    }

    void CPixelStage::ShutDown()
    {
        if (mInitialized)
        {
            m_PixelShader->Release();
            m_PixelShader = nullptr;
        }
    }

    void CPixelStage::Bind(ID3D11DeviceContextPtr _device)
    {
        _device->PSSetShader(m_PixelShader, nullptr, 0);
    }

    void CPixelStage::Unbind(ID3D11DeviceContextPtr _device)
    {
        _device->PSSetShader(nullptr, nullptr, 0);
    }

    const char* CPixelStage::GetShaderModel()
    {
        return CDevice::GetInstance().GetVertexStageFeatureLevel();
    }
}