#include "Render.h"

#include "GeometryStage.h"
#include "Device.h"

namespace render
{
    void CGeometryStage::Initialize(ID3D11DevicePtr _device, const std::string& aShaderCode)
    {
        m_EntryPoint = "mainGS";
        m_Type = ShaderStageType::GeometryStage;
        CShaderStage::Initialize(_device, aShaderCode);
    }

    void CGeometryStage::ShutDown()
    {

    }

    void CGeometryStage::Bind(ID3D11DeviceContextPtr _device)
    {
        _device->GSSetShader(nullptr, nullptr, 0);
    }

    void CGeometryStage::Unbind(ID3D11DeviceContextPtr _device)
    {
        _device->GSSetShader(nullptr, nullptr, 0);
    }

    const char* CGeometryStage::GetShaderModel()
    {
        return CDevice::GetInstance().GetGeometryStageFeatureLevel();
    }
}