#include "Render.h"
#include "Shader.h"
#include "ShaderStages\VertexStage.h"
#include "ShaderStages\PixelStage.h"
#include "ShaderStages\GeometryStage.h"
#include "Device.h"
#include "Geometry/Vertex.h"

namespace render
{
    CShader::CShader()
    {
        mShaders.resize(static_cast<int>(ShaderStageType::MAX), nullptr);
    }

    void CShader::Bind(ID3D11DeviceContextPtr _device)
    {
        for (auto& lShader : mShaders)
            if (lShader) lShader->Bind(_device);
    }

    void CShader::Unbind(ID3D11DeviceContextPtr _device)
    {
        for (auto& lShader : mShaders)
            if (lShader) lShader->Unbind(_device);
    }

    void CShader::Deserialize(const io::CSerializableNode& _node)
    {
        CSerializable::Deserialize(_node);

        render::CDevice& lDevice = render::CDevice::GetInstance();
        ID3D11Device* d3d = lDevice.Device();

        const io::CSerializableNode& lStagesNode = _node["stages"];
        HELIOSASSERT(lStagesNode.IsArray());
        for (io::ArraySize i = 0; i < lStagesNode.Size(); ++i)
        {
            render::ShaderStageType lType;
            if (EnumString<render::ShaderStageType>::ToEnum(lType, lStagesNode[i]["type"].GetString() ))
            {
                render::CShaderStage* lShaderStage = nullptr;
                switch (lType)
                {
                case render::ShaderStageType::VertexStage:
                {
                    lShaderStage = new CVertexStage<render::CIm3dVertex>();
                }
                break;
                case render::ShaderStageType::PixelStage:
                {
                    lShaderStage = new CPixelStage();
                }
                break;
                case render::ShaderStageType::GeometryStage:
                {
                    lShaderStage = new CGeometryStage();
                }
                break;
                }
                HELIOSASSERT(lShaderStage != nullptr);
                lShaderStage->Initialize(d3d, lStagesNode[i]["src"].GetString(), lStagesNode[i]["macros"].GetString() );
                //mShader->SetStage(lType, lShaderStage);
            }
        }
    }

    void CShader::Serialize(io::CSerializableNode& _node) const
    {

    }
}