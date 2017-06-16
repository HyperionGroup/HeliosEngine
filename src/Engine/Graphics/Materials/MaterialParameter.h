#pragma once

#include "Serialization\Serializable.h"
#include "Name.h"

namespace graphics
{
    class CMaterialParameter : public core::CName
    {
    public:
        CMaterialParameter() = default;
        virtual ~CMaterialParameter() = default;
        virtual uint32 GetSize() const = 0;
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
}