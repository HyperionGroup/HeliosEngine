#pragma once

#include "Str.h"

#include "Serialization.h"

namespace core
{
    class CName
    {
      SERIALIZABLE_OBJECT
    public:
        CName() : mName("") {}
        CName(const CStr& _name) : mName(_name) {}
        virtual ~CName() {}
        const CStr& GetName() const { return mName;  }
        void SetName(const CStr& _name) { mName = _name; }
    protected:
        CStr mName;
    };
}