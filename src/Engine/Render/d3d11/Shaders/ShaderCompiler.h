#ifndef __ShaderCompiler_HH__
#define __ShaderCompiler_HH__

#include "Render.h"
#include "Shader.h"

namespace render
{
    class CShaderCompiler : public core::CSingleton< CShaderCompiler >
    {
    public:
        CShaderCompiler();
        virtual ~CShaderCompiler();
        CShader* LoadShader(const std::vector< std::string >& _flags, const std::string& _vs, const std::string& _ps );
        std::string GetVertexStructures(const std::vector< std::string >& _flags);
    protected:
    };
}

#endif