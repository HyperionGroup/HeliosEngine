#pragma once

#include "rapidjson/document.h"

#define SERIALIZABLE \
public: \
virtual void Deserialize(const io::CSerializableNode& _node); \
virtual void Serialize(io::CSerializableNode& _node) const;

namespace io
{
    typedef rapidjson::Value CSerializableNode;
    typedef rapidjson::SizeType ArraySize;

    namespace serialization
    {
        bool OpenFileAndGetNode(CSerializableNode& _node, const std::string& _filename, const std::string& _nodeTag);
    }

    class CSerializable
    {
    public:
        CSerializable() = default;
        virtual ~CSerializable() = default;
        virtual void Deserialize(const CSerializableNode& _node)
        {
            mName = _node["name"].GetString();
        }

        virtual void Serialize(CSerializableNode& _node) const = 0;
    protected:
        std::string mName;
    };
}
