#ifndef H_GEOMETRY_SHADER
#define H_GEOMETRY_SHADER

#include "ShaderStage.h"

namespace render
{
    class CGeometryStage : public CShaderStage
    {
    public:
        CGeometryStage(const std::string& aShaderCode);
        virtual ~CGeometryStage();
        virtual void Bind(CDevicePtr _device) {};

    protected:
        virtual const char* GetShaderModel();
    };
}

#endif //H_GEOMETRY_SHADER