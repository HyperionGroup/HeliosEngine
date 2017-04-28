#include "PixelStage.h"
#include "Device.h"

namespace render
{
    CPixelStage::CPixelStage(const std::string& aShaderCode)
        : CShaderStage(aShaderCode, ShaderStageType::FragmentStage )
        , m_PixelShader(nullptr)
    {
    }

    CPixelStage::~CPixelStage()
    {
        m_PixelShader->Release();
    }

    bool CPixelStage::Load(CDevicePtr _device)
    {
        bool lOk = CShaderStage::Load(_device);
        if (lOk)
        {
            HRESULT lHR = _device->Device()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PixelShader);
            lOk = SUCCEEDED(lHR);
            DXCall(lHR);
        }
        return lOk;
    }

    void CPixelStage::Bind(CDevicePtr _device)
    {
        _device->ImmediateContext()->PSSetShader(m_PixelShader, NULL, 0);
    }

    const char* CPixelStage::GetShaderModel()
    {
        return CDevice::GetInstance().GetVertexStageFeatureLevel();
    }
}