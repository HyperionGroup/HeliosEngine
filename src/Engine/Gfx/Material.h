#pragma once

#include "Core.h"
#include "Name.h"

namespace gfx
{
    class CTexture;
    class CShader;
    class CMaterialParameter : public core::CName
    {
    public:
        CMaterialParameter() = default;
        virtual ~CMaterialParameter() = default;
        virtual uint32_t GetSize() const = 0;
        virtual void * GetAddr(int index = 0) const = 0;
    protected:
        std::string m_Description;
    };

    template<typename T>
    class CTemplatedMaterialParameter : public CMaterialParameter
    {
    public:
        CTemplatedMaterialParameter()
            : CMaterialParameter()
            , mValue()
        {}
        virtual ~CTemplatedMaterialParameter() {}
        virtual uint32 GetSize() const { return sizeof(T); };
        void * GetAddr(int index = 0) const;
        const T& GetValue() const { return mValue; }
        void SetValue(const T& _value) { mValue = _value; }
    private:
        T mValue;
    };

    template<typename T>
    void* CTemplatedMaterialParameter<T>::GetAddr(int index = 0) const
    {
        return (void*)((float*)&mValue + index);
    }

    class CMaterial : public core::CName
    {
    public:
        CMaterial();
        virtual ~CMaterial() = default;
        void Render();
        //std::shared_ptr<gfx::CTexture> GetTexture(TextureMap _map) const { return mTextures[static_cast<int>(_map)]; }

        uint32_t GetParametersCount() const { return static_cast<uint32>(mParameters.size());  }
        std::shared_ptr< CMaterialParameter > GetParameter( uint32 _idx ) const { return mParameters[_idx]; }

    private:
        std::vector< std::shared_ptr< gfx::CTexture> >   mTextures;
        std::vector< std::shared_ptr< CMaterialParameter > > mParameters;
        std::shared_ptr< CShader > mShader;
    };
}