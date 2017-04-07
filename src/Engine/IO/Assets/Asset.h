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
        protected:
            std::string mID;
        public:
            CAsset( const std::string& _fileName );
            virtual ~CAsset();
            virtual bool Load() { return false;  }
    };

#pragma region Serialization
    SERIALIZABLE_SAVE_DECLARATION(CAsset)
    {
        TO_ARCHIVE(ID);
    }

    SERIALIZABLE_LOAD_DECLARATION(CAsset)
    {

    }
#pragma endregion Serialization
}

#endif