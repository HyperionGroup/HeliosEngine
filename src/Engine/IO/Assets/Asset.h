#ifndef _IO_ASSET_
#define _IO_ASSET_

#pragma once

#include "Render.h"
#include "Serializable.h"
#include <string>

namespace io
{
    class CAsset : public std::string
    {
        SERIALIZABLE
        private:
        public:
            CAsset( const std::string& _fileName );
            virtual ~CAsset();
            virtual bool Load() { return false;  }
    };

    SERIALIZABLE_SAVE_DECLARATION(CAsset)
    {
        ar(cereal::make_nvp("id", c_str()));
    }

    SERIALIZABLE_LOAD_DECLARATION(CAsset)
    {

    }
}

#endif