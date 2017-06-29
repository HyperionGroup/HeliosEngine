#pragma once
#include "Core/Core.h"

namespace gfx
{
    class CStaticMesh;
    typedef std::shared_ptr< CStaticMesh > CStaticMeshSptr;

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
Begin_Enum_String(gfx::ShaderStageType)
{
    Enum_String_Id(gfx::ShaderStageType::VertexStage, "vs");
    Enum_String_Id(gfx::ShaderStageType::PixelStage, "ps");
    Enum_String_Id(gfx::ShaderStageType::GeometryStage, "gs");
}
End_Enum_String;

Begin_Enum_String(gfx::TextureType)
{
    Enum_String_Id(gfx::TextureType::OneDimension, "1D");
    Enum_String_Id(gfx::TextureType::TwoDimensions, "2D");
    Enum_String_Id(gfx::TextureType::ThreeDimensions, "3D");
}
End_Enum_String;

Begin_Enum_String(gfx::PixelDesc)
{
    Enum_String_Id(gfx::PixelDesc::R32F, "r32f");
    Enum_String_Id(gfx::PixelDesc::RG32F, "rg32f");
    Enum_String_Id(gfx::PixelDesc::RGB32F, "rgb32f");
    Enum_String_Id(gfx::PixelDesc::RGBA32F, "rgba32f");
    Enum_String_Id(gfx::PixelDesc::R16F, "r16f");
    Enum_String_Id(gfx::PixelDesc::RG16F, "rg16f");
    Enum_String_Id(gfx::PixelDesc::RGB16F, "rgb16f");
    Enum_String_Id(gfx::PixelDesc::RGBA16F, "rgba16f");
}
End_Enum_String;

Begin_Enum_String(gfx::VertexFlags)
{
    Enum_String_Id(gfx::VertexFlags::Position, "position");
    Enum_String_Id(gfx::VertexFlags::Normal, "normal");
    Enum_String_Id(gfx::VertexFlags::Tangent, "tangent");
    Enum_String_Id(gfx::VertexFlags::Binormal, "binormal");
    Enum_String_Id(gfx::VertexFlags::Uv, "uv");
    Enum_String_Id(gfx::VertexFlags::Uv2, "uv2");
    Enum_String_Id(gfx::VertexFlags::Color, "color");
    Enum_String_Id(gfx::VertexFlags::Position4, "position4");
    Enum_String_Id(gfx::VertexFlags::Bump, "bump");
    Enum_String_Id(gfx::VertexFlags::Weight, "weight");
    Enum_String_Id(gfx::VertexFlags::Indices, "indices");
}
End_Enum_String;

Begin_Enum_String(gfx::SamplerType)
{
    Enum_String_Id(gfx::SamplerType::Linear, "Linear");
    Enum_String_Id(gfx::SamplerType::LinearClamp, "LinearClamp");
    Enum_String_Id(gfx::SamplerType::LinearBorder, "LinearBorder");
    Enum_String_Id(gfx::SamplerType::Anisotropic, "Anisotropic");
    Enum_String_Id(gfx::SamplerType::Point, "Point");
    Enum_String_Id(gfx::SamplerType::ShadowMap, "ShadowMap");
    Enum_String_Id(gfx::SamplerType::ShadowMapPCF, "ShadowMapPCF");
}
End_Enum_String;