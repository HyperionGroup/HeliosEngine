#include "Texture.h"
#include "Sampler.h"

namespace render
{
    CTexture::CTexture()
        : mSampler(std::make_shared<CSampler>())
        , mHeight(0)
        , mWidht(0)
        , mData(nullptr)
    {

    }

    CTexture::~CTexture()
    {

    }
}