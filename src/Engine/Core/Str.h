#pragma once

#include <string>
#include <vector>

#include "tinyformat.h"

namespace core
{
    class CStrVector;
    class CStr
    {
    public:
        CStr() = default;
        CStr(const std::string& _str);
        CStr(const char* _str);
        CStr& operator=(const std::string& other);
        bool operator!=(const core::CStr& other) const;
        bool operator==(const core::CStr& other) const;
        bool operator!=(const std::string& other) const;
        bool operator==(const std::string& other) const;
        CStr& operator=(const char* other);
        CStr operator+(const char* other) const;
        CStr operator+(const std::string& other) const;
        bool IsEmpty() const;
        template<typename... Arguments> CStr& Format(Arguments... params)
        {
          mStr = tfm::format(ToCStr(), params...);
          return *this;
        }

        CStrVector Split(char _split_char) const;
        void ToLower();
        CStr& ToUpper();
        const char* ToCStr() const;
    protected:
        std::string mStr;
    };

    class CStrVector : public std::vector< std::string >
    {
    public:
        CStrVector() = default;
        virtual ~CStrVector() = default;
    };
}