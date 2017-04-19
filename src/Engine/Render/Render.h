#pragma once

#include "Serializable.h"
#include "Core.h"

#pragma warning( disable  : 4005 )  

#ifdef OGL_RENDERER
#define RENDER_API ogl

#else
#include "d3d11/D3DRender.h"
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