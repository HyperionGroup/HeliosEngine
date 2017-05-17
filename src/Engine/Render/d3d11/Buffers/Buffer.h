#pragma once

#ifndef __BUFFER__HH__
#define __BUFFER__HH__

namespace render
{
    class CBuffer
    {
    public:
        CBuffer()
            : mBuffer(nullptr)
            , mInitialized(false)
            , mUsage(D3D11_USAGE_DEFAULT)
        {}
        virtual ~CBuffer() {}
        virtual void ShutDown()
        {
            HELIOSASSERT(mInitialized);
            if( mInitialized )
            {
                if (mBuffer)
                {
                    mBuffer->Release();
                    mBuffer = nullptr;
                }
                mInitialized = false;
            }
        }
        virtual void Bind(ID3D11DeviceContextPtr _device) = 0;
        ID3D11BufferPtr Buffer() const { return mBuffer; }

        bool IsInitizalized() const { return mInitialized; }
    protected:
        D3D11_USAGE mUsage;
        ID3D11BufferPtr mBuffer;
        bool mInitialized;
    };
}

#endif // !__BUFFER__HH__
