#pragma once

#include "Core.h"
#include "Render.h"

namespace graphics
{
    DECLARE_SPTR(CCamera);
    DECLARE_SPTR(CMaterial);
    DECLARE_SPTR(CMaterialParameter);

    enum class TextureMap
    {
        Diffuse = 0,
        Bump,
        LightMap,
        Specular,
        
        MAX
    };

    enum class ParameterType
    {
        Float = 0,
        Float2,
        Float3,
        Float4,
        Color,

        MAX
    };
}

//---------------------------------------------------------------------------------------------------------
Begin_Enum_String(graphics::TextureMap)
{
    Enum_String_Id(graphics::TextureMap::Diffuse, "diffuse");
    Enum_String_Id(graphics::TextureMap::Bump, "bump");
    Enum_String_Id(graphics::TextureMap::LightMap, "lightmap");
    Enum_String_Id(graphics::TextureMap::Specular, "specular");
}
End_Enum_String;

//---------------------------------------------------------------------------------------------------------
Begin_Enum_String(graphics::ParameterType)
{
    Enum_String_Id(graphics::ParameterType::Float, "float");
    Enum_String_Id(graphics::ParameterType::Float2, "float2");
    Enum_String_Id(graphics::ParameterType::Float3, "float3");
    Enum_String_Id(graphics::ParameterType::Float4, "float4");
    Enum_String_Id(graphics::ParameterType::Color, "color");
}
End_Enum_String;