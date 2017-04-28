#ifndef __Shader_HH__
#define __Shader_HH__

#include "Render.h"

namespace render
{
    class CShader
    {
    public:
        CShader();
        virtual ~CShader();
        void SetStage(ShaderStageType _stage, CShaderStagePtr _shaderstage);
        void Bind(CDevicePtr _device);
    private:
        std::vector< CShaderStagePtr > mShaders;
        uint32 mFlags;
    };
}

#endif