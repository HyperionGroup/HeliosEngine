#include "IO.h"

#include "Render.h"

#include "ShaderAsset.h"
#include "Shaders\Shader.h"
#include "Shaders\ShaderStages\VertexStage.h"
#include "Shaders\ShaderStages\PixelStage.h"
#include "Shaders\ShaderStages\GeometryStage.h"
#include "Geometry/Vertex.h"

#include "Device.h"

namespace io
{
    bool CShaderAsset::Unload()
    {
        CHECKED_DELETE(mShader);
        return true;
    }

    bool CShaderAsset::Load()
    {
        render::CDevice& lDevice = render::CDevice::GetInstance();
        ID3D11Device* d3d = lDevice.Device();

        mShader = new render::CShader();
        
        for (StageDesc desc : mStagesDescriptors)
        {
            render::ShaderStageType lType;
            if (EnumString<render::ShaderStageType>::ToEnum(lType, desc.type))
            {
                render::CShaderStage* lShaderStage = nullptr;
                switch (lType)
                {
                case render::ShaderStageType::VertexStage:
                {
                    lShaderStage = new render::CVertexStage<render::CIm3dVertex>();
                }
                break;
                case render::ShaderStageType::PixelStage:
                {
                    lShaderStage = new render::CPixelStage();
                }
                break;
                case render::ShaderStageType::GeometryStage:
                {
                    lShaderStage = new render::CGeometryStage();
                }
                break;
                }
                HELIOSASSERT(lShaderStage != nullptr);
                lShaderStage->Initialize(d3d, desc.file, desc.macros);
                mShader->SetStage(lType, lShaderStage);
            }
        }
        return true;
    }
}