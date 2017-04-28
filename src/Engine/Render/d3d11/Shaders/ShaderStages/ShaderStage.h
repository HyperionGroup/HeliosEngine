#ifndef __H_SHADER__
#define __H_SHADER__

#include "Render.h"

namespace render
{
    class CShaderStage
    {
    public:
        CShaderStage(const std::string& aShaderCode, ShaderStageType aType);
        virtual ~CShaderStage();
        bool Load( CDevicePtr _device );
        virtual void Bind(CDevicePtr _device) = 0;
    protected:
        ShaderStageType m_Type;
        std::string  m_Preprocessor;
        std::string  m_EntryPoint;
        std::string  m_ShaderCode;
        D3D_SHADER_MACRO *m_ShaderMacros;
        std::vector<std::string> m_PreprocessorMacros;
        ID3DBlob     *m_Blob;
        void CreateShaderMacro();
        virtual const char* GetShaderModel() = 0;
    };
}
#endif //__H_SHADER__