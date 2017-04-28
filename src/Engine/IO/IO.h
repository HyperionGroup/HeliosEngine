#pragma once

#include "Core.h"

namespace io
{
    class CAsset;
    typedef std::shared_ptr< CAsset > CAssetPtr;

    enum AssetType
    {
        Texture = 0,
        Mesh,
    };
}

Begin_Enum_String(io::AssetType)
{
    Enum_String_Id(io::Texture, "Texture");
    Enum_String_Id(io::Mesh, "Mesh");
}
End_Enum_String;