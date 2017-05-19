#include "IO.h"

#include "Render.h"

#include "ShaderAsset.h"
#include "Shaders\Shader.h"
#include "Shaders\ShaderStages\VertexStage.h"
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
        std::ifstream ifs("shaders/" + mSource);
        std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

        render::CDevice& lDevice = render::CDevice::GetInstance();
        ID3D11Device* d3d = lDevice.Device();

        mShader = new render::CShader();
        render::CShaderStage* lVS = new render::CVertexStage<render::CIm3dVertex>();
        lVS->SetPreprocessor(mPreprocessorVS);
        lVS->Initialize(d3d, content);
        mShader->SetStage(render::ShaderStageType::VertexStage, lVS);

        render::CShaderStage* lPS = new render::CVertexStage<render::CIm3dVertex>();
        lPS->SetPreprocessor(mPreprocessorPS);
        lPS->Initialize(d3d, content);
        mShader->SetStage(render::ShaderStageType::PixelStage, lPS);

        render::CShaderStage* lGS = new render::CVertexStage<render::CIm3dVertex>();
        lVS->SetPreprocessor(mPreprocessorVS);
        lVS->Initialize(d3d, content);
        mShader->SetStage(render::ShaderStageType::VertexStage, lGS);

        //mShader->SetStage(render::ShaderStageType::VertexStage, lVS);
        return false;
    }
}