#include "Core.h"

#include "Serialization.h"

#include "Str.h"

namespace serialization
{
    template<> void OutputArchive::Add<core::CStr>(const char* _name, const core::CStr& _value, const core::CStr& _defValue )
    {
        if (_value != _defValue)
        {
            Key(_name);
            String(_value.ToCStr());
        }
    }

    template<> void OutputArchive::Add<bool>(const char* _name, const bool& _value, const bool& _defValue )
    {
        if (_value != _defValue)
        {
            Key(_name);
            Bool(_value);
        }
    }

    template<> void OutputArchive::Add<uint32_t>(const char* _name, const uint32_t& _value, const uint32_t& _defValue)
    {
        if (_value != _defValue)
        {
            Key(_name);
            Uint(_value);
        }
    }

    template<> core::CStr Get<core::CStr>(InputArchiveNode& _node, const char* _name, const core::CStr& _defValue)
    {
        InputArchiveNode::MemberIterator lIt = _node.FindMember(_name);
        return (lIt != _node.MemberEnd()) ? lIt->value.GetString() : _defValue;
    }

    template<> uint32_t Get<uint32_t>(InputArchiveNode& _node, const char* _name, const uint32_t& _defValue)
    {
        InputArchiveNode::MemberIterator lIt = _node.FindMember(_name);
        return (lIt != _node.MemberEnd()) ? lIt->value.GetUint() : _defValue;
    }

    template<> bool Get<bool>(InputArchiveNode& _node, const char* _name, const bool& _defValue)
    {
        InputArchiveNode::MemberIterator lIt = _node.FindMember(_name);
        return (lIt != _node.MemberEnd()) ? lIt->value.GetBool() : _defValue;
    }
}
