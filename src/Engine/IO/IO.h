#include "Core.h"

#pragma once

namespace io
{
    class CAsset;
    typedef std::shared_ptr< CAsset > CAssetPtr;

    enum AssetType
    {
        Texture = 0,
        Mesh,
        Material,
        Shader,
    };

    std::string GetTag(const std::string& _filename);
}

Begin_Enum_String(io::AssetType)
{
    Enum_String_Id(io::Texture, "texture");
    Enum_String_Id(io::Mesh, "mesh");
    Enum_String_Id(io::Material, "material");
    Enum_String_Id(io::Shader, "shader");
}
End_Enum_String;