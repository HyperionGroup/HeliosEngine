#include "Render.h"

#include "GeometryStage.h"
#include "Device.h"
#include "Engine.h"

namespace render
{
    void CGeometryStage::Initialize(ID3D11DevicePtr _device)
    {
        CShaderStage::Initialize(_device);
        DXCall(_device->CreateGeometryShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_GeometryShader));
        mInitialized = true;
    }

    void CGeometryStage::ShutDown()
    {
        if (mInitialized)
        {
            DXCheckedRelease(m_GeometryShader);
            mInitialized = false;
        }
    }

    void CGeometryStage::Bind(ID3D11DeviceContextPtr _device)
    {
        _device->GSSetShader(m_GeometryShader, nullptr, 0);
    }

    void CGeometryStage::Unbind(ID3D11DeviceContextPtr _device)
    {
        _device->GSSetShader(nullptr, nullptr, 0);
    }

    const char* CGeometryStage::GetShaderModel()
    {
        return helios::CEngine::GetInstance().GetDevice().GetGeometryStageFeatureLevel();
    }
}