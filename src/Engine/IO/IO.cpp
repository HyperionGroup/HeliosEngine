#include "IO.h"

#include "StringUtils.h"

namespace io
{
    std::string GetTag(const std::string& _filename)
    {
        std::string fName(_filename);
        size_t pos = fName.rfind(".");
        if (pos == std::string::npos)  //No extension.
            return fName;

        if (pos == 0)    //. is at the front. Not an extension.
            return fName;

        std::string lPathWithoutExtension = fName.substr(0, pos);
        return core::Split(lPathWithoutExtension, '/').back();
    }
}