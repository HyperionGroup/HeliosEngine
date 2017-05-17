#include "IO.h"

#include "Asset.h"

namespace io
{
    CAsset::CAsset()
    {
    }

    CAsset::~CAsset()
    {

    }

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CAsset)
    {
    }

    SERIALIZABLE_LOAD_DECLARATION(CAsset)
    {

    }
#pragma endregion Serialization
}