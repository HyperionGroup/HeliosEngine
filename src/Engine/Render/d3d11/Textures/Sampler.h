#ifndef _RENDER_SAMPLER_
#define _RENDER_SAMPLER_

#pragma once

#include "Render.h"
#include "Serializable.h"

namespace render
{
    class CSampler
    {
        SERIALIZABLE
        private:
            Filter                     mFilter;
            AddressMode                mAddressMode;
            ComparisonFunc             mComparisonFunc;
            float                      mMinLOD;
            float                      mMaxLOD;
            Float4                     mBorderColor;
            float                      mMipLODBias;
            uint32                     mMaxAnisotropy;
        public:
            CSampler();
            virtual ~CSampler();
    };

    SERIALIZABLE_SAVE_DECLARATION(CSampler)
    {
        TO_ARCHIVE_ENUM(Filter);
        TO_ARCHIVE_ENUM(AddressMode);
        TO_ARCHIVE_ENUM(ComparisonFunc);
        TO_ARCHIVE(MinLOD);
        TO_ARCHIVE(MaxLOD);
        TO_ARCHIVE(BorderColor);
        TO_ARCHIVE(MipLODBias);
        TO_ARCHIVE(MaxAnisotropy);
    }

    SERIALIZABLE_LOAD_DECLARATION(CSampler)
    {
        FROM_ARCHIVE_ENUM(Filter);
        FROM_ARCHIVE_ENUM(AddressMode);
        FROM_ARCHIVE_ENUM(ComparisonFunc);
        FROM_ARCHIVE(MinLOD);
        FROM_ARCHIVE(MaxLOD);
        FROM_ARCHIVE(BorderColor);
        FROM_ARCHIVE(MipLODBias);
        FROM_ARCHIVE(MaxAnisotropy);
    }
}

#endif