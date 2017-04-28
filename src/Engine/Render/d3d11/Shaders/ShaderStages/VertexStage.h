#ifndef H_VERTEX_SHADER
#define H_VERTEX_SHADER

#include "ShaderStage.h"

namespace render
{
    class CVertexShader : public CShaderStage
    {
    public:
        CVertexShader(const std::string& aShaderCode, uint32 aVertexFlags);
        virtual ~CVertexShader();
        virtual bool Load(CDevicePtr _device);
        virtual void Bind(CDevicePtr _device);
    private:
        uint32  m_VertexFlags;
        ID3D11VertexShader *m_VertexShader;
        ID3D11InputLayout *m_VertexLayout;

        virtual const char* GetShaderModel();
    };
}

#endif //H_VERTEX_SHADER