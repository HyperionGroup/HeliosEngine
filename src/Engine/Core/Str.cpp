#include "Core.h"

#include "Str.h"

namespace core
{
    CStr::CStr(const std::string& _str)
    {
        mStr = _str;
    }

    CStr::CStr(const char* _str)
    {
        mStr = _str;
    }

    CStr& CStr::operator=(const std::string& other)
    {
        mStr = other;
        return *this;
    }

    CStr CStr::operator+(const std::string& other) const
    {
        return mStr + other;
    }

    CStr CStr::operator+(const char* other) const
    {
        return mStr + other;
    }

    CStr& CStr::operator=(const char* other)
    {
        return *this;
    }

    bool CStr::operator!=(const core::CStr& other) const
    {
        return mStr != other.mStr;
    }
     
    bool CStr::operator==(const core::CStr& other) const
    {
        return mStr == other.mStr;
    }

    bool CStr::operator!=(const std::string& other) const
    {
        return mStr != other;
    }

    bool CStr::operator==(const std::string& other) const
    {
        return mStr == other;
    }

    bool CStr::IsEmpty() const
    {
        return mStr.empty();
    }

    CStrVector CStr::Split(char _split_char) const
    {
        std::stringstream ss(mStr);
        std::string item;

        CStrVector elems;
        while (std::getline(ss, item, _split_char))
            elems.push_back(item);

        return elems;
    }

    void CStr::ToLower()
    {
        for (size_t i = 0; i < mStr.length(); i++)
            mStr[i] = tolower(mStr[i]);
    }

    CStr& CStr::ToUpper()
    {
        for (size_t i = 0; i < mStr.length(); i++)
            mStr[i] = toupper(mStr[i]);

        return *this;
    }

    const char* CStr::ToCStr() const
    {
        return mStr.c_str();
    }
}