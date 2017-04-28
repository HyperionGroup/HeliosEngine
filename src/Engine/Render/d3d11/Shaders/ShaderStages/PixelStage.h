#ifndef H_PIXEL_SHADER
#define H_PIXEL_SHADER

#include "ShaderStage.h"

namespace render
{
    class CPixelStage : public CShaderStage
    {
    public:
        CPixelStage(const std::string& aShaderCode);
        virtual ~CPixelStage();
        virtual bool Load(CDevicePtr _device);
        virtual void Bind(CDevicePtr _device);

    protected:
        virtual const char* GetShaderModel();
    private:
        ID3D11PixelShader *m_PixelShader;
    };
}

#endif //H_PIXEL_SHADER