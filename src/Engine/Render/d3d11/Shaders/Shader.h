#pragma once

namespace render
{
    class CShaderStage;
    class CShader
    {
    public:
        CShader();
        virtual ~CShader();
        void SetStage(render::ShaderStageType _stage, CShaderStage* _shaderstage);
        void Bind(ID3D11DeviceContextPtr _device);
        void Unbind(ID3D11DeviceContextPtr _device);

    private:
        std::vector< CShaderStage* > mShaders;
        uint32 mFlags;
    };
}