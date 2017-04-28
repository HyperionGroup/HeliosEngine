#ifndef _IO_ASSET_
#define _IO_ASSET_

#pragma once

#include "Render.h"
#include "Serializable.h"
#include <string>

namespace io
{
    class CAsset
    {
        SERIALIZABLE
        public:
            CAsset();
            virtual ~CAsset();
            virtual bool Load() = 0;
    };

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CAsset)
    {
    }

    SERIALIZABLE_LOAD_DECLARATION(CAsset)
    {

    }
#pragma endregion Serialization
}

#endif