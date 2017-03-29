#ifndef _RENDER_SAMPLER_
#define _RENDER_SAMPLER_

#pragma once

#include "Render.h"
#include <Mathpp.h>

namespace render
{
    class CSampler
    {
        public:
            CSampler();
            virtual ~CSampler();

            template <class Archive>
            void save(Archive & ar) const
            {
                ar(cereal::make_nvp("min_lod", mMinLOD));
                ar(cereal::make_nvp("max_lod", mMaxLOD));
                ar(cereal::make_nvp("mip_lod_bias", mMipLODBias));
            }

            template <class Archive>
            void load(Archive & ar)
            {
                static int32_t idGen = 0;
                id = idGen++;
                //ar();
            }

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
}

#endif