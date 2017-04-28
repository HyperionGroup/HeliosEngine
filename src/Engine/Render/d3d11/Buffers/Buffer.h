#pragma once

#ifndef __BUFFER__HH__
#define __BUFFER__HH__

#include "Render.h"

namespace render
{
    class CBuffer
    {
    public:
        CBuffer()
            : mBuffer(nullptr)
            , mInitialized(false)
        {}
        virtual ~CBuffer() {}
        virtual void Initialize(CDevicePtr _device) = 0;
        virtual void Bind(CDevicePtr _device) = 0;
        ID3D11BufferPtr Buffer() const { return mBuffer; }
    protected:
        ID3D11BufferPtr mBuffer;
        bool mInitialized;
    };
}

#endif // !__BUFFER__HH__
