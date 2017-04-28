#include "VertexStage.h"
#include "Device.h"

namespace render
{
    CVertexShader::CVertexShader(const std::string& aShaderCode, uint32 aVertexFlags)
        : CShaderStage(aShaderCode, ShaderStageType::VertexStage)
        , m_VertexFlags(aVertexFlags)
        , m_VertexLayout(nullptr)
        , m_VertexShader(nullptr)
    {
    }

    CVertexShader::~CVertexShader()
    {
        m_VertexShader->Release();
        m_VertexLayout->Release();
    }

    bool CVertexShader::Load(CDevicePtr _device)
    {
        bool lOk = CShaderStage::Load(_device);
        if (lOk)
        {
            HRESULT lHR = _device->Device()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VertexShader);
            lOk = SUCCEEDED(lHR);
            if (lOk)
            {
                lOk &= m_VertexFlags != 0;
                //lOk &= Vertex::CreateInputLayout(lRenderManager, m_VertexFlags, m_Blob, &m_VertexLayout);
            }
            DXCall(lHR);
        }
        return lOk;
    }

    void CVertexShader::Bind(CDevicePtr _device)
    {
        // Configure how the CPU will send the vertexes to the GPU( COORDS | NORMALS | COLOR | UV ... )
        _device->ImmediateContext()->IASetInputLayout(m_VertexLayout);

        // Bind the vertex shader and its uniform data across all the vertexes
        _device->ImmediateContext()->VSSetShader(m_VertexShader, NULL, 0);
    }

    const char* CVertexShader::GetShaderModel()
    {
        return CDevice::GetInstance().GetVertexStageFeatureLevel();
    }
}
