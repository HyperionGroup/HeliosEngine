#include "Engine.h"
#include "Serializable.h"

#include "rapidjson/istreamwrapper.h"

namespace io
{
    namespace utils
    {
        io::CSerializableDocument OpenDocument(const std::string& _filename)
        {
            std::ifstream ifs(_filename);
            std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
            io::CSerializableDocument document;
            document.Parse(content.c_str());
            return document;
        }
    }
}
