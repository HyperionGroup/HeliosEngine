#pragma once

#include <string>

namespace core
{
    class CName
    {
    public:
        CName() : mName("") {}
        CName(const std::string& _name) : mName(_name) {}
        virtual ~CName() {}
        const std::string& GetName() const { return mName;  }
        void SetName(const std::string& _name) { mName = _name; }
    protected:
        std::string mName;
    };
}