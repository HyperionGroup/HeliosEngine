#include "GeometryStage.h"
#include "d3d11\Device.h"

namespace render
{
    CGeometryStage::CGeometryStage(const std::string& aShaderCode)
        : CShaderStage(aShaderCode, ShaderStageType::GeometryStage)
    {
    }

    CGeometryStage::~CGeometryStage()
    {
    }

    const char* CGeometryStage::GetShaderModel()
    {
        return CDevice::GetInstance().GetGeometryStageFeatureLevel();
    }
}