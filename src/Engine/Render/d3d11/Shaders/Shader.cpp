#include "Render.h"
#include "Shader.h"
#include "ShaderStages\VertexStage.h"
#include "ShaderStages\PixelStage.h"
#include "ShaderStages\GeometryStage.h"
#include "Device.h"
#include "Vertex.h"
#include "Engine.h"

namespace render
{
    CShader::CShader()
        : CSerializableEntity()
        , CName("")
    {
    }

    void CShader::Bind(ID3D11DeviceContextPtr _device)
    {
        for (auto& lShader : mShaders) lShader->Bind(_device);
    }

    void CShader::Unbind(ID3D11DeviceContextPtr _device)
    {
        for (auto& lShader : mShaders) lShader->Unbind(_device);
    }

    void CShader::Deserialize(const io::CSerializableNode& _node)
    {
        HELIOSASSERT(_node.IsObject());

        SetName( _node["name"].GetString() );

        helios::CEngine& lEngine = helios::CEngine::GetInstance();

        const io::CSerializableEntityConstructor& lEntityCntr = lEngine.GetSerializableEntityConstructor();
        
        mShaders.clear();
        
        const io::CSerializableNode& lStagesNode = _node["stages"];
        HELIOSASSERT(lStagesNode.IsArray());
        for(const io::CSerializableNode& m : lStagesNode.GetArray())
        {
            std::shared_ptr< io::CSerializableEntity > lShaderStage
                = lEntityCntr.Create( m["type"].GetString() );
            lShaderStage->Deserialize(m);
            mShaders.push_back(std::static_pointer_cast
                <CShaderStage>(lShaderStage));
        }
    }

    void CShader::Serialize(io::CSerializableNode& _node) const
    {

    }
}