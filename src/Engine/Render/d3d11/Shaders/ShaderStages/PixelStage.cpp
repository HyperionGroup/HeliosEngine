#include "Render.h"
#include "PixelStage.h"
#include "Device.h"

namespace render
{
    void CPixelStage::Initialize(ID3D11DevicePtr _device, const std::string& _src, const std::string& _preprocessor)
    {
        CShaderStage::Initialize(_device, _src, _preprocessor);
        DXCall(_device->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PixelShader));
        mInitialized = false;
    }

    void CPixelStage::ShutDown()
    {
        if (mInitialized)
        {
            DXCheckedRelease(m_PixelShader);
            mInitialized = false;
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
        return CDevice::GetInstance().GetPixelStageFeatureLevel();
    }
}