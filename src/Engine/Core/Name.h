#pragma once
#ifndef __H_NAME__
#define __H_NAME__

#include <string>

namespace core
{
    class CName
    {
    public:
        CName() : m_Name("") {}
        CName(const std::string& _name) : m_Name(_name) {}
        virtual ~CName() {}
        const std::string& GetName() const { return m_Name;  }
        void SetName(const std::string& _name) { m_Name = _name; }
    protected:
        std::string m_Name;
    };
}

#endif // __H_NAME__