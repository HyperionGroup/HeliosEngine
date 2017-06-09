#pragma once
#include "Core.h"

namespace render
{
    enum class BlendState
    {
        BlendDisabled = 0,
        AdditiveBlend,
        AlphaBlend,
        PreMultipliedAlphaBlend,
        NoColorBlend,
        AlphaToCoverageBlend,
        Opacity,
        Im3dBlend,

        MAX
    };

    enum class RasterizerState
    {
        NoCull = 0,
        CullBackFaces,
        CullBackFacesScissor,
        CullFrontFaces,
        CullFrontFacesScissor,
        NoCullNoMs,
        NoCullScissor,
        WireFrame,
        
        MAX
    };

    enum class DepthStencilState
    {
        DepthDisabled = 0,
        DepthEnabled,
        ReverseDepthEnabled,
        DepthWriteEnabled,
        ReverseDepthWriteEnabled,
        DepthStencilWriteEnabled,
        StencilEnabled,

        MAX
    };

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

    enum VertexFlags
    {
        Position = 0x0001,
        Normal = 0x0002,
        Tangent = 0x0004,
        Binormal = 0x0008,
        Uv = 0x0010,
        Uv2 = 0x0020,
        Color = 0x0040,
        Position4 = 0x0080,
        Bump = Normal | Tangent | Binormal,
        Weight = 0x0100,
        Indices = 0x0200,
    };

    enum class TextureType
    {
        OneDimension = 1,
        TwoDimensions,
        ThreeDimensions,
    };

    enum class PixelDesc
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

    enum class ShaderStageType
    {
        VertexStage   = 0,
        PixelStage,
        GeometryStage,
        MAX
    };

    enum class PrimitiveTopology
    {
        LineList = 2,
        TriangleList = 4,
        TriangleStrip = 5
    };
}

//---------------------------------------------------------------------------------------------------------
Begin_Enum_String(render::ShaderStageType)
{
    Enum_String_Id(render::ShaderStageType::VertexStage, "vs");
    Enum_String_Id(render::ShaderStageType::PixelStage, "ps");
    Enum_String_Id(render::ShaderStageType::GeometryStage, "gs");
}
End_Enum_String;

Begin_Enum_String(render::TextureType)
{
    Enum_String_Id(render::TextureType::OneDimension, "1D");
    Enum_String_Id(render::TextureType::TwoDimensions, "2D");
    Enum_String_Id(render::TextureType::ThreeDimensions, "3D");
}
End_Enum_String;

Begin_Enum_String(render::PixelDesc)
{
    Enum_String_Id(render::PixelDesc::R32F, "r32f");
    Enum_String_Id(render::PixelDesc::RG32F, "rg32f");
    Enum_String_Id(render::PixelDesc::RGB32F, "rgb32f");
    Enum_String_Id(render::PixelDesc::RGBA32F, "rgba32f");
    Enum_String_Id(render::PixelDesc::R16F, "r16f");
    Enum_String_Id(render::PixelDesc::RG16F, "rg16f");
    Enum_String_Id(render::PixelDesc::RGB16F, "rgb16f");
    Enum_String_Id(render::PixelDesc::RGBA16F, "rgba16f");
}
End_Enum_String;

Begin_Enum_String(render::VertexFlags)
{
    Enum_String_Id(render::VertexFlags::Position, "position");
    Enum_String_Id(render::VertexFlags::Normal, "normal");
    Enum_String_Id(render::VertexFlags::Tangent, "tangent");
    Enum_String_Id(render::VertexFlags::Binormal, "binormal");
    Enum_String_Id(render::VertexFlags::Uv, "uv");
    Enum_String_Id(render::VertexFlags::Uv2, "uv2");
    Enum_String_Id(render::VertexFlags::Color, "color");
    Enum_String_Id(render::VertexFlags::Position4, "position4");
    Enum_String_Id(render::VertexFlags::Bump, "bump");
    Enum_String_Id(render::VertexFlags::Weight, "weight");
    Enum_String_Id(render::VertexFlags::Indices, "indices");
}
End_Enum_String;

Begin_Enum_String(render::SamplerType)
{
    Enum_String_Id(render::SamplerType::Linear, "Linear");
    Enum_String_Id(render::SamplerType::LinearClamp, "LinearClamp");
    Enum_String_Id(render::SamplerType::LinearBorder, "LinearBorder");
    Enum_String_Id(render::SamplerType::Anisotropic, "Anisotropic");
    Enum_String_Id(render::SamplerType::Point, "Point");
    Enum_String_Id(render::SamplerType::ShadowMap, "ShadowMap");
    Enum_String_Id(render::SamplerType::ShadowMapPCF, "ShadowMapPCF");
}
End_Enum_String;