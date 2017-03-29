#ifndef _RENDER_SAMPLER_
#define _RENDER_SAMPLER_

#pragma once

#include "Render.h"
#include "Serializable.h"
#include <Mathpp.h>

namespace render
{
    class CSampler
    {
        public:
            CSampler();
            virtual ~CSampler();

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
    };

    template <class Archive> void CSampler::save(Archive & ar) const
    {
        ar(cereal::make_nvp("Filter", EnumString< Filter >::ToStr(mFilter)));
        ar(cereal::make_nvp("AddressMode", EnumString< AddressMode >::ToStr(mAddressMode)));
        ar(cereal::make_nvp("ComparisonFunc", EnumString< ComparisonFunc >::ToStr(mComparisonFunc)));
        ar(cereal::make_nvp("MinLOD", mMinLOD));
        ar(cereal::make_nvp("MaxLOD", mMaxLOD));
        ar(cereal::make_nvp("BorderColor", mBorderColor));
        ar(cereal::make_nvp("MipLODBias", mMipLODBias));
        ar(cereal::make_nvp("MaxAnisotropy", mMaxAnisotropy));
    }

    template <class Archive> void CSampler::load(Archive & ar)
    {
        std::string lFilterStr, lAddressModeStr, lComparisonStr;
        ar(cereal::make_nvp("Filter", lFilterStr));
        ar(cereal::make_nvp("AddressMode", lAddressModeStr));
        ar(cereal::make_nvp("ComparisonFunc", lComparisonStr));
        EnumString< Filter >::ToEnum(mFilter, lFilterStr);
        EnumString< ComparisonFunc >::ToEnum(mComparisonFunc, lComparisonStr);
        EnumString< AddressMode >::ToEnum(mAddressMode, lAddressModeStr);
        ar(cereal::make_nvp("MinLOD", mMinLOD));
        ar(cereal::make_nvp("MaxLOD", mMaxLOD));
        ar(cereal::make_nvp("BorderColor", mBorderColor));
        ar(cereal::make_nvp("MipLODBias", mMipLODBias));
        ar(cereal::make_nvp("MaxAnisotropy", mMaxAnisotropy));
    }
}

#endif