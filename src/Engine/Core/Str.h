#pragma once

#include <string>
#include <vector>

namespace core
{
    class CStrVector : public std::vector< std::string >
    {
    public:
        CStrVector() = default;
        virtual ~CStrVector() = default;
    };

    class CStr
    {
    public:
        CStr() = default;
        CStr(const std::string& _str);
        CStr(const char* _str);
        CStr& operator=(const std::string& other);
        CStr& operator=(const char* other);
        template<typename... Arguments> void Format(Arguments... params);
        CStrVector Split(char _split_char) const;
        void ToLower();
        CStr& ToUpper();
        const char* ToCStr() const;
    protected:
        std::string mStr;
    };
}