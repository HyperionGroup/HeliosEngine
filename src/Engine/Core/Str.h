#pragma once

#include <string>
#include <vector>

#include "tinyformat.h"

namespace core
{
    typedef std::string CStr;
    typedef std::vector< std::string > CStrVector;
    void Split(const CStr& _str, char _split_char, CStrVector& elems);
    

    /*
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
          mStr = tfm::format(c_str(), params...);
          return *this;
        }

        CStrVector Split(char _split_char) const;
        void ToLower();
        CStr& ToUpper();
        const char* c_str() const;
    protected:
        std::string mStr;
    };
    */
}