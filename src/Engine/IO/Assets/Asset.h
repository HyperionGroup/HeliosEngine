#ifndef _IO_ASSET_
#define _IO_ASSET_

#pragma once

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
}

#endif