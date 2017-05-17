//=================================================================================================
//
//	MJP's DX11 Sample Framework
//  http://mynameismjp.wordpress.com/
//
//  All code and content licensed under Microsoft Public License (Ms-PL)
//
//=================================================================================================

#pragma once

struct ID3D11BlendState;

namespace render
{

class BlendStates
{
protected:
    BlendStates() = default;
    virtual ~BlendStates() = default;
    void Initialize(ID3D11Device* device);
    void ShutDown();
    void Apply(ID3D11DeviceContext* _context, BlendState _state, float* _blendFactor = nullptr);

    friend CDevice;

    static D3D11_BLEND_DESC BlendDisabledDesc();
    static D3D11_BLEND_DESC AdditiveBlendDesc();
    static D3D11_BLEND_DESC AlphaBlendDesc();
    static D3D11_BLEND_DESC PreMultipliedAlphaBlendDesc();
    static D3D11_BLEND_DESC ColorWriteDisabledDesc();
    static D3D11_BLEND_DESC AlphaToCoverageDesc();
    static D3D11_BLEND_DESC OpacityBlendDesc();
    static D3D11_BLEND_DESC Im3dBlendDesc();

    ID3D11BlendStatePtr blendDisabled;
    ID3D11BlendStatePtr additiveBlend;
    ID3D11BlendStatePtr alphaBlend;
    ID3D11BlendStatePtr pmAlphaBlend;
    ID3D11BlendStatePtr noColor;
    ID3D11BlendStatePtr alphaToCoverage;
    ID3D11BlendStatePtr opacityBlend;
    ID3D11BlendStatePtr im3dBlend;

    BlendState mState;
};


class RasterizerStates
{
protected:
    RasterizerStates() = default;
    virtual ~RasterizerStates() = default;
    void Initialize(ID3D11Device* device);
    void ShutDown();
    void Apply(ID3D11DeviceContext* _context, RasterizerState _state);

    friend CDevice;

protected:

    ID3D11RasterizerStatePtr noCull;
    ID3D11RasterizerStatePtr cullBackFaces;
    ID3D11RasterizerStatePtr cullBackFacesScissor;
    ID3D11RasterizerStatePtr cullFrontFaces;
    ID3D11RasterizerStatePtr cullFrontFacesScissor;
    ID3D11RasterizerStatePtr noCullNoMS;
    ID3D11RasterizerStatePtr noCullScissor;
    ID3D11RasterizerStatePtr wireframe;

    ID3D11RasterizerState* NoCull() { return noCull; };
    ID3D11RasterizerState* BackFaceCull() { return cullBackFaces; };
    ID3D11RasterizerState* BackFaceCullScissor() { return cullBackFacesScissor; };
    ID3D11RasterizerState* FrontFaceCull() { return cullFrontFaces; };
    ID3D11RasterizerState* FrontFaceCullScissor() { return cullFrontFacesScissor; };
    ID3D11RasterizerState* NoCullNoMS() { return noCullNoMS; };
    ID3D11RasterizerState* NoCullScissor() { return noCullScissor; };
    ID3D11RasterizerState* Wireframe() { return wireframe; };

    static D3D11_RASTERIZER_DESC NoCullDesc();
    static D3D11_RASTERIZER_DESC FrontFaceCullDesc();
    static D3D11_RASTERIZER_DESC FrontFaceCullScissorDesc();
    static D3D11_RASTERIZER_DESC BackFaceCullDesc();
    static D3D11_RASTERIZER_DESC BackFaceCullScissorDesc();
    static D3D11_RASTERIZER_DESC NoCullNoMSDesc();
    static D3D11_RASTERIZER_DESC NoCullScissorDesc();
    static D3D11_RASTERIZER_DESC WireframeDesc();

    RasterizerState mState;
};


class DepthStencilStates
{
protected:
    DepthStencilStates() = default;
    virtual ~DepthStencilStates() = default;
    void Initialize(ID3D11Device* device);
    void ShutDown();
    void Apply(ID3D11DeviceContext* _context, DepthStencilState _state);

    friend CDevice;

    ID3D11DepthStencilStatePtr depthDisabled;
    ID3D11DepthStencilStatePtr depthEnabled;
    ID3D11DepthStencilStatePtr revDepthEnabled;
    ID3D11DepthStencilStatePtr depthWriteEnabled;
    ID3D11DepthStencilStatePtr revDepthWriteEnabled;
    ID3D11DepthStencilStatePtr depthStencilWriteEnabled;
    ID3D11DepthStencilStatePtr stencilEnabled;

    ID3D11DepthStencilState* DepthDisabled() { return depthDisabled; };
    ID3D11DepthStencilState* DepthEnabled() { return depthEnabled; };
    ID3D11DepthStencilState* ReverseDepthEnabled() { return revDepthEnabled; };
    ID3D11DepthStencilState* DepthWriteEnabled() { return depthWriteEnabled; };
    ID3D11DepthStencilState* ReverseDepthWriteEnabled() { return revDepthWriteEnabled; };
    ID3D11DepthStencilState* DepthStencilWriteEnabled() { return depthStencilWriteEnabled; };
    ID3D11DepthStencilState* StencilTestEnabled() { return depthStencilWriteEnabled; };

    static D3D11_DEPTH_STENCIL_DESC DepthDisabledDesc();
    static D3D11_DEPTH_STENCIL_DESC DepthEnabledDesc();
    static D3D11_DEPTH_STENCIL_DESC ReverseDepthEnabledDesc();
    static D3D11_DEPTH_STENCIL_DESC DepthWriteEnabledDesc();
    static D3D11_DEPTH_STENCIL_DESC ReverseDepthWriteEnabledDesc();
    static D3D11_DEPTH_STENCIL_DESC DepthStencilWriteEnabledDesc();
    static D3D11_DEPTH_STENCIL_DESC StencilEnabledDesc();
    
    DepthStencilState mState;
};


class SamplerStates
{

    ID3D11SamplerStatePtr linear;
    ID3D11SamplerStatePtr linearClamp;
    ID3D11SamplerStatePtr linearBorder;
    ID3D11SamplerStatePtr point;
    ID3D11SamplerStatePtr anisotropic;
    ID3D11SamplerStatePtr shadowMap;
    ID3D11SamplerStatePtr shadowMapPCF;
public:

    void Initialize(ID3D11Device* device);

    ID3D11SamplerState* Linear() { return linear; };
    ID3D11SamplerState* LinearClamp() { return linearClamp; };
    ID3D11SamplerState* LinearBorder() { return linearBorder; };
    ID3D11SamplerState* Point() { return point; };
    ID3D11SamplerState* Anisotropic() { return anisotropic; };
    ID3D11SamplerState* ShadowMap() { return shadowMap; };
    ID3D11SamplerState* ShadowMapPCF() { return shadowMapPCF; };

    static D3D11_SAMPLER_DESC LinearDesc();
    static D3D11_SAMPLER_DESC LinearClampDesc();
    static D3D11_SAMPLER_DESC LinearBorderDesc();
    static D3D11_SAMPLER_DESC PointDesc();
    static D3D11_SAMPLER_DESC AnisotropicDesc();
    static D3D11_SAMPLER_DESC ShadowMapDesc();
    static D3D11_SAMPLER_DESC ShadowMapPCFDesc();
};

}
