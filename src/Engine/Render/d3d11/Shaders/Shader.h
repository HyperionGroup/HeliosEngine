#pragma once

namespace render
{
    class CShader
    {
    public:
        CShader();
        virtual ~CShader();
        void SetStage(ShaderStageType _stage, CShaderStagePtr _shaderstage);
        void Bind(ID3D11DeviceContextPtr _device);
        void Unbind(ID3D11DeviceContextPtr _device);

    private:
        std::vector< CShaderStagePtr > mShaders;
        uint32 mFlags;
    };
}