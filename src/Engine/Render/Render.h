#pragma once

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
