#include "Asset.h"

namespace io
{
    CAsset::CAsset(const std::string& _fileName)
        : mID(_fileName)
    {
    }

    CAsset::~CAsset()
    {

    }
}