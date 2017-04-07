#pragma once

#include "EnumToString.h"
#include <Mathpp.h>
#include <memory>
#include "Serializable.h"

#pragma warning( disable  : 4005 )  

#ifdef OGL_RENDERER
#define RENDER_API ogl

#else
#define RENDER_API d3d11

#include <d3d11_1.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#define D3D_ERROR_CASE(HR_ERROR) case HR_ERROR: lMsg = #HR_ERROR; break;
#define CHECK_PRINT_HR(HR) \
std::string lMsg; \
if( FAILED( HR ) ) \
{ \
  switch (HR) \
  { \
    D3D_ERROR_CASE(D3D11_ERROR_FILE_NOT_FOUND) \
    D3D_ERROR_CASE(D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS) \
    D3D_ERROR_CASE(D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS) \
    D3D_ERROR_CASE(D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD) \
    D3D_ERROR_CASE(DXGI_ERROR_INVALID_CALL) \
    D3D_ERROR_CASE(DXGI_ERROR_WAS_STILL_DRAWING) \
    D3D_ERROR_CASE(E_FAIL) \
    D3D_ERROR_CASE(E_INVALIDARG) \
    D3D_ERROR_CASE(E_OUTOFMEMORY) \
    D3D_ERROR_CASE(E_NOTIMPL) \
    D3D_ERROR_CASE(S_FALSE) \
  default: \
    break; \
  }\
    LOG_ERROR_APPLICATION("Error calling render function %s", lMsg.c_str()) \
}

#define CHECKED_RELEASE(d3d11handle) \
if( d3d11handle)\
{\
    d3d11handle->Release();\
    d3d11handle = nullptr;\
}

#endif

namespace render
{
    class CSampler;
    typedef std::shared_ptr< CSampler > CSamplerPtr;

    enum Filter
    {
        PointFilter = 0,
        LinearFilter,
        AnisotropicFilter
    };

    enum AddressMode
    {
        WrapMode = 0,
        MirrorMode,
        ClampMode,
        BorderMode,
        MirrorOnceMode
    };

    enum ComparisonFunc
    {
        NeverFunc = 0,
        LessFunc,
        EqualFunc,
        LessEqualFunc,
        NotEqualFunc,
        GreaterEqualFunc,
        AlwaysFunc,
    };

    enum TextureType
    {
        OneDimension = 1,
        TwoDimensions,
        ThreeDimensions,
    };

    enum PixelDesc
    {
        Unknown = 0,
        R32F,
        RG32F,
        RGB32F,
        RGBA32F,
        R16F,
        RG16F,
        RGB16F,
        RGBA16F,
        PixelBitsCount
    };

    uint16 BytesPerPixel(PixelDesc _pixelDesc);

    enum ShaderStage
    {
        VertexStage   = 0,
        FragmentStage,
        GeometryStage,
    };

    enum BlendEquation
    {
        BlendAdd,
        BlendSubtract,
        BlendReverseSubtract
    };

    enum BlendFunc
    {
        Zero = 0,
        One,
        SrcColor,
        DstColor,
        SrcAlpha,
        DstAlpha,
        ConstantAlpha,
        ConstantColor,
        OneMinusSrcColor,
        OneMinusDstColor,
        OneMinusSrcAlpha,
        OneMinusDstAlpha,
        OneMinusConstantColor,
        OneMinusConstantAlpha,
        SrcAlphaSaturate,
    };
}

//---------------------------------------------------------------------------------------------------------
Begin_Enum_String(render::ShaderStage)
{
    Enum_String_Id(render::VertexStage, "VertexStage");
    Enum_String_Id(render::FragmentStage, "FragmentStage");
    Enum_String_Id(render::GeometryStage, "GeometryStage");
}
End_Enum_String;

Begin_Enum_String(render::Filter)
{
    Enum_String_Id(render::PointFilter, "Point");
    Enum_String_Id(render::LinearFilter, "Linear");
    Enum_String_Id(render::AnisotropicFilter, "Anisotropic");
}
End_Enum_String;

Begin_Enum_String(render::AddressMode)
{
    Enum_String_Id(render::WrapMode, "Wrap");
    Enum_String_Id(render::MirrorMode, "Mirror");
    Enum_String_Id(render::ClampMode, "Clamp");
    Enum_String_Id(render::BorderMode, "Border");
    Enum_String_Id(render::MirrorOnceMode, "MirrorOnce");
}
End_Enum_String;

Begin_Enum_String(render::ComparisonFunc)
{
    Enum_String_Id(render::NeverFunc, "Never");
    Enum_String_Id(render::LessFunc, "Less");
    Enum_String_Id(render::EqualFunc, "Equal");
    Enum_String_Id(render::LessEqualFunc, "LessEqual");
    Enum_String_Id(render::NotEqualFunc, "NotEqual");
    Enum_String_Id(render::GreaterEqualFunc, "GreaterEqual");
    Enum_String_Id(render::AlwaysFunc, "Always");
}
End_Enum_String;

Begin_Enum_String(render::TextureType)
{
    Enum_String_Id(render::OneDimension, "1D");
    Enum_String_Id(render::TwoDimensions, "2D");
    Enum_String_Id(render::ThreeDimensions, "3D");
}
End_Enum_String;

Begin_Enum_String(render::BlendFunc)
{
    Enum_String_Id(render::Zero, "Zero");
    Enum_String_Id(render::One, "One");
    Enum_String_Id(render::SrcColor, "SrcColor");
    Enum_String_Id(render::DstColor, "DstColor");
    Enum_String_Id(render::SrcAlpha, "SrcAlpha");
    Enum_String_Id(render::DstAlpha, "DstAlpha");
    Enum_String_Id(render::ConstantAlpha, "ConstantAlpha");
    Enum_String_Id(render::ConstantColor, "ConstantColor");
    Enum_String_Id(render::OneMinusSrcColor, "OneMinusSrcColor");
    Enum_String_Id(render::OneMinusDstColor, "OneMinusDstColor");
    Enum_String_Id(render::OneMinusSrcAlpha, "OneMinusSrcAlpha");
    Enum_String_Id(render::OneMinusDstAlpha, "OneMinusDstAlpha");
    Enum_String_Id(render::OneMinusConstantColor, "OneMinusConstantColor");
    Enum_String_Id(render::OneMinusConstantAlpha, "OneMinusConstantAlpha");
    Enum_String_Id(render::SrcAlphaSaturate, "SrcAlphaSaturate");
}
End_Enum_String;

Begin_Enum_String(render::PixelDesc)
{
    Enum_String_Id(render::R32F, "R32F");
    Enum_String_Id(render::RG32F, "RG32F");
    Enum_String_Id(render::RGB32F, "RGB32F");
    Enum_String_Id(render::RGBA32F, "RGBA32F");
    Enum_String_Id(render::R16F, "R16F");
    Enum_String_Id(render::RG16F, "RG16F");
    Enum_String_Id(render::RGB16F, "RGB16F");
    Enum_String_Id(render::RGBA16F, "RGBA16F");
}
End_Enum_String;