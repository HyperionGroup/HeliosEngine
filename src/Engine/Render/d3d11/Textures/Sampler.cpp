#include "Sampler.h"

namespace render
{
    CSampler::CSampler() 
        : mFilter( PointFilter )
        , mAddressMode( WrapMode )
        , mComparisonFunc( NeverFunc )
        , mMinLOD( 0.0f )
        , mMaxLOD( FLT_MAX )
        , mBorderColor(1.0f)
        , mMipLODBias(0.0f)
        , mMaxAnisotropy(1)
    {

    }

    CSampler::~CSampler()
    {

    }
}