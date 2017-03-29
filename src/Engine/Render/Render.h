#pragma once

#include "EnumToString.h"

namespace render
{
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
        NeverFunc = 1,
        LessFunc,
        EqualFunc,
        LessEqualFunc,
        NotEqualFunc,
        GreaterEqualFunc,
        AlwaysFunc,
    };
}

//---------------------------------------------------------------------------------------------------------
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
