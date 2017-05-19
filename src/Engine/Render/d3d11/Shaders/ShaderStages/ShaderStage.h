#pragma once

namespace render
{
    class CShaderStage
    {
    public:
        CShaderStage() = default;
        virtual ~CShaderStage() = default;
        virtual void Initialize(ID3D11DevicePtr _device, const std::string& aShaderCode);
        virtual void ShutDown();
        virtual void Bind(ID3D11DeviceContextPtr _device) = 0;
        virtual void Unbind(ID3D11DeviceContextPtr _device) = 0;
        void SetPreprocessor( const std::string& _preprocessor );

    protected:
        ShaderStageType m_Type;
        std::string  m_EntryPoint;
        std::string  m_ShaderCode;
        D3D_SHADER_MACRO *m_ShaderMacros;
        std::vector<std::string> m_PreprocessorMacros;
        ID3DBlob     *m_Blob;
        bool          mInitialized;
        
        virtual const char* GetShaderModel() = 0;
    };
}