#include "IO.h"

#include "Serializable.h"

#include "rapidjson/istreamwrapper.h"

namespace io
{
    namespace serialization
    {
        bool OpenFileAndGetNode(CSerializableNode& _node, const std::string& _filename, const std::string& _nodeTag)
        {
            bool lParsed = false;
            if (!_filename.empty())
            {
                std::ifstream ifs(_filename);
                std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
                rapidjson::Document document;
                document.Parse(content.c_str());
                _node = document[_nodeTag.c_str()];
            }

            return lParsed;
        }
    }

}
