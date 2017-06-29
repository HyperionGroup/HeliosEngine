#pragma once

#include "Str.h"

namespace core
{
    class CName
    {
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