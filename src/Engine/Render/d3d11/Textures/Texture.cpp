#include "Texture.h"
#include "Sampler.h"

namespace render
{
    CTexture::CTexture()
        : mSampler(std::make_shared<CSampler>())
        , mData(nullptr)
        , mColorFormat(render::RGBA32F)
    {

    }

    CTexture::~CTexture()
    {

    }
}