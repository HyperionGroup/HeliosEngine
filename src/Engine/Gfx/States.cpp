#include "Gfx.h"
#include "States.h"

namespace render
{
    /*
    void BlendStates::Initialize(ID3D11Device* device)
    {
        DXCall(device->CreateBlendState(&BlendDisabledDesc(), &blendDisabled));
        DXCall(device->CreateBlendState(&AdditiveBlendDesc(), &additiveBlend));
        DXCall(device->CreateBlendState(&AlphaBlendDesc(), &alphaBlend));
        DXCall(device->CreateBlendState(&PreMultipliedAlphaBlendDesc(), &pmAlphaBlend));
        DXCall(device->CreateBlendState(&ColorWriteDisabledDesc(), &noColor));
        DXCall(device->CreateBlendState(&AlphaToCoverageDesc(), &alphaToCoverage));
        DXCall(device->CreateBlendState(&OpacityBlendDesc(), &opacityBlend));
        DXCall(device->CreateBlendState(&Im3dBlendDesc(), &im3dBlend));
    }

    void BlendStates::ShutDown()
    {
    }

    void BlendStates::Apply(ID3D11DeviceContext* _context, BlendState _state, float* _blendFactor)
    {
        if (_state != mState)
        {
            switch (_state)
            {
            case BlendState::BlendDisabled:
                _context->OMSetBlendState(blendDisabled, _blendFactor, 0xFFFFFFFF);
            case BlendState::AdditiveBlend:
                _context->OMSetBlendState(additiveBlend, _blendFactor, 0xFFFFFFFF);
            case BlendState::AlphaBlend:
                _context->OMSetBlendState(alphaBlend, _blendFactor, 0xFFFFFFFF);
            case BlendState::PreMultipliedAlphaBlend:
                _context->OMSetBlendState(pmAlphaBlend, _blendFactor, 0xFFFFFFFF);
            case BlendState::NoColorBlend:
                _context->OMSetBlendState(noColor, _blendFactor, 0xFFFFFFFF);
            case BlendState::AlphaToCoverageBlend:
                _context->OMSetBlendState(opacityBlend, _blendFactor, 0xFFFFFFFF);
            case BlendState::Im3dBlend:
                _context->OMSetBlendState(im3dBlend, _blendFactor, 0xFFFFFFFF);
            default:
                HELIOSASSERT(false);
                break;
            }
        }
    }

    D3D11_BLEND_DESC BlendStates::Im3dBlendDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = true;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        }

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::BlendDisabledDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = false;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::AdditiveBlendDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = true;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::AlphaBlendDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = true;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = true;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        blendDesc.RenderTarget[0].BlendEnable = true;

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::PreMultipliedAlphaBlendDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = false;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::ColorWriteDisabledDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = false;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = 0;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::AlphaToCoverageDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = true;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = false;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        return blendDesc;
    }

    D3D11_BLEND_DESC BlendStates::OpacityBlendDesc()
    {
        D3D11_BLEND_DESC blendDesc;
        blendDesc.AlphaToCoverageEnable = false;
        blendDesc.IndependentBlendEnable = false;
        for (UINT i = 0; i < 8; ++i)
        {
            blendDesc.RenderTarget[i].BlendEnable = true;
            blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC1_COLOR;
            blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
            blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
            blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        }

        return blendDesc;
    }

    void RasterizerStates::Initialize(ID3D11Device* device)
    {
        DXCall(device->CreateRasterizerState(&NoCullDesc(), &noCull));
        DXCall(device->CreateRasterizerState(&FrontFaceCullDesc(), &cullFrontFaces));
        DXCall(device->CreateRasterizerState(&FrontFaceCullScissorDesc(), &cullFrontFacesScissor));
        DXCall(device->CreateRasterizerState(&BackFaceCullDesc(), &cullBackFaces));
        DXCall(device->CreateRasterizerState(&BackFaceCullScissorDesc(), &cullBackFacesScissor));
        DXCall(device->CreateRasterizerState(&NoCullNoMSDesc(), &noCullNoMS));
        DXCall(device->CreateRasterizerState(&NoCullScissorDesc(), &noCullScissor));
        DXCall(device->CreateRasterizerState(&WireframeDesc(), &wireframe));
    }

    void RasterizerStates::ShutDown()
    {

    }

    void RasterizerStates::Apply(ID3D11DeviceContext* _context, RasterizerState _state )
    {
        if (_state != mState)
        {
            switch (_state)
            {
            case RasterizerState::NoCull:
                _context->RSSetState(noCull);
            case RasterizerState::CullFrontFaces:
                _context->RSSetState(cullFrontFaces);
            case RasterizerState::CullBackFacesScissor:
                _context->RSSetState(cullBackFacesScissor);
            case RasterizerState::CullBackFaces:
                _context->RSSetState(cullBackFaces);
            case RasterizerState::CullFrontFacesScissor:
                _context->RSSetState(cullFrontFacesScissor);
            case RasterizerState::NoCullNoMs:
                _context->RSSetState(noCullNoMS);
            case RasterizerState::NoCullScissor:
                _context->RSSetState(noCullScissor);
            case RasterizerState::WireFrame:
                _context->RSSetState(wireframe);
            default:
                HELIOSASSERT(false);
                break;
            }
        }
    }

    D3D11_RASTERIZER_DESC RasterizerStates::NoCullDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = false;
        rastDesc.MultisampleEnable = true;
        rastDesc.ScissorEnable = false;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::FrontFaceCullDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_FRONT;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = false;
        rastDesc.MultisampleEnable = true;
        rastDesc.ScissorEnable = false;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::FrontFaceCullScissorDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_FRONT;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = TRUE;
        rastDesc.MultisampleEnable = TRUE;
        rastDesc.ScissorEnable = TRUE;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::BackFaceCullDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_BACK;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = false;
        rastDesc.MultisampleEnable = true;
        rastDesc.ScissorEnable = false;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::BackFaceCullScissorDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_BACK;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = FALSE;
        rastDesc.MultisampleEnable = TRUE;
        rastDesc.ScissorEnable = TRUE;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::NoCullNoMSDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = false;
        rastDesc.MultisampleEnable = false;
        rastDesc.ScissorEnable = false;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::NoCullScissorDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_SOLID;
        rastDesc.FrontCounterClockwise = false;
        rastDesc.MultisampleEnable = true;
        rastDesc.ScissorEnable = true;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    D3D11_RASTERIZER_DESC RasterizerStates::WireframeDesc()
    {
        D3D11_RASTERIZER_DESC rastDesc;

        rastDesc.AntialiasedLineEnable = FALSE;
        rastDesc.CullMode = D3D11_CULL_NONE;
        rastDesc.DepthBias = 0;
        rastDesc.DepthBiasClamp = 0.0f;
        rastDesc.DepthClipEnable = TRUE;
        rastDesc.FillMode = D3D11_FILL_WIREFRAME;
        rastDesc.FrontCounterClockwise = false;
        rastDesc.MultisampleEnable = true;
        rastDesc.ScissorEnable = false;
        rastDesc.SlopeScaledDepthBias = 0;

        return rastDesc;
    }

    void DepthStencilStates::Initialize(ID3D11Device* device)
    {
        DXCall(device->CreateDepthStencilState(&DepthDisabledDesc(), &depthDisabled));
        DXCall(device->CreateDepthStencilState(&DepthEnabledDesc(), &depthEnabled));
        DXCall(device->CreateDepthStencilState(&ReverseDepthEnabledDesc(), &revDepthEnabled));
        DXCall(device->CreateDepthStencilState(&DepthWriteEnabledDesc(), &depthWriteEnabled));
        DXCall(device->CreateDepthStencilState(&ReverseDepthWriteEnabledDesc(), &revDepthWriteEnabled));
        DXCall(device->CreateDepthStencilState(&DepthStencilWriteEnabledDesc(), &depthStencilWriteEnabled));
        DXCall(device->CreateDepthStencilState(&StencilEnabledDesc(), &stencilEnabled));
    }

    void DepthStencilStates::ShutDown()
    {

    }

    void DepthStencilStates::Apply(ID3D11DeviceContext* _context, DepthStencilState _state)
    {
        if (_state != mState)
        {
            switch (_state)
            {
            case DepthStencilState::DepthDisabled:
                _context->OMSetDepthStencilState(depthDisabled, 0);
            case DepthStencilState::DepthEnabled:
                _context->OMSetDepthStencilState(depthEnabled, 0);
            case DepthStencilState::ReverseDepthEnabled:
                _context->OMSetDepthStencilState(revDepthEnabled, 0);
            case DepthStencilState::DepthWriteEnabled:
                _context->OMSetDepthStencilState(depthWriteEnabled, 0);
            case DepthStencilState::ReverseDepthWriteEnabled:
                _context->OMSetDepthStencilState(revDepthWriteEnabled, 0);
            case DepthStencilState::DepthStencilWriteEnabled:
                _context->OMSetDepthStencilState(depthStencilWriteEnabled, 0);
            case DepthStencilState::StencilEnabled:
                _context->OMSetDepthStencilState(stencilEnabled, 0);
            default:
                HELIOSASSERT(false);
                break;
            }
        }
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthDisabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = false;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        dsDesc.StencilEnable = false;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthEnabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        dsDesc.StencilEnable = false;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::ReverseDepthEnabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
        dsDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
        dsDesc.StencilEnable = false;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthWriteEnabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        dsDesc.StencilEnable = false;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::ReverseDepthWriteEnabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
        dsDesc.StencilEnable = false;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::DepthStencilWriteEnabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        dsDesc.StencilEnable = true;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    D3D11_DEPTH_STENCIL_DESC DepthStencilStates::StencilEnabledDesc()
    {
        D3D11_DEPTH_STENCIL_DESC dsDesc;
        dsDesc.DepthEnable = true;
        dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        dsDesc.StencilEnable = true;
        dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        dsDesc.StencilWriteMask = 0;
        dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
        dsDesc.BackFace = dsDesc.FrontFace;

        return dsDesc;
    }

    void SamplerStates::ShutDown()
    {

    }

    void SamplerStates::Apply(ID3D11DeviceContext* _context, SamplerStates _state)
    {
        /*
        enum class SamplerType
        {
            Linear = 0,
            LinearClamp,
            LinearBorder,
            Point,
            Anisotropic,
            ShadowMap,
            ShadowMapPCF,

            MAX
        };
    }


    void SamplerStates::Initialize(ID3D11Device* device)
    {
        DXCall(device->CreateSamplerState(&LinearDesc(), &linear));
        DXCall(device->CreateSamplerState(&LinearClampDesc(), &linearClamp));
        DXCall(device->CreateSamplerState(&LinearBorderDesc(), &linearBorder));
        DXCall(device->CreateSamplerState(&PointDesc(), &point));
        DXCall(device->CreateSamplerState(&AnisotropicDesc(), &anisotropic));
        DXCall(device->CreateSamplerState(&ShadowMapDesc(), &shadowMap));
        DXCall(device->CreateSamplerState(&ShadowMapPCFDesc(), &shadowMapPCF));
    }

    D3D11_SAMPLER_DESC SamplerStates::LinearDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 1;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }

    D3D11_SAMPLER_DESC SamplerStates::LinearClampDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 1;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }

    D3D11_SAMPLER_DESC SamplerStates::LinearBorderDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 1;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }

    D3D11_SAMPLER_DESC SamplerStates::PointDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 1;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }

    D3D11_SAMPLER_DESC SamplerStates::AnisotropicDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 16;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }

    D3D11_SAMPLER_DESC SamplerStates::ShadowMapDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 1;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }

    D3D11_SAMPLER_DESC SamplerStates::ShadowMapPCFDesc()
    {
        D3D11_SAMPLER_DESC sampDesc;

        sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
        sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampDesc.MipLODBias = 0.0f;
        sampDesc.MaxAnisotropy = 1;
        sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
        sampDesc.BorderColor[0] = sampDesc.BorderColor[1] = sampDesc.BorderColor[2] = sampDesc.BorderColor[3] = 0;
        sampDesc.MinLOD = 0;
        sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

        return sampDesc;
    }
    */
}