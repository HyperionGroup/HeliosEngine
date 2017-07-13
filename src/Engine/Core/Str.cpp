#include "Core.h"

#include "Str.h"

namespace core
{
  void Split(const CStr& _str, char _split_char, CStrVector& elems)
  {
    std::stringstream ss(_str);
    CStr item;
    while (std::getline(ss, item, _split_char))
      elems.push_back(item.c_str());
  }
  /*
    

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

    const char* CStr::c_str() const
    {
        return mStr.c_str();
    }
    */
}