#include "Core.h"

#include "Serialization.h"

#include "Str.h"

#include <bx\string.h>

namespace serialization
{
  template<> void OutputArchive::Add<Float2>(const char* _name, const Float2& _value, const Float2& _defValue)
  {
    if (_value != _defValue)
    {
      Key(_name);
      String(tfm::format("%f %f", _value.x, _value.y ).c_str());
    }
  }

  template<> void OutputArchive::Add<Float3>(const char* _name, const Float3& _value, const Float3& _defValue)
  {
    if (_value != _defValue)
    {
      Key(_name);
      String(tfm::format("%f %f %f", _value.x, _value.y, _value.z).c_str());
    }
  }

  template<> void OutputArchive::Add<Float4>(const char* _name, const Float4& _value, const Float4& _defValue)
  {
    if (_value != _defValue)
    {
      Key(_name);
      String(tfm::format("%f %f %f %f", _value.x, _value.y, _value.z, _value.w).c_str());
    }
  }

  template<> void OutputArchive::Add<CColor>(const char* _name, const CColor& _value, const CColor& _defValue)
  {
    if (_value != _defValue)
    {
      Key(_name);
      String(tfm::format("%f %f %f %f", _value.r, _value.g, _value.b, _value.r).c_str());
    }
  }

  template<> void OutputArchive::Add<core::CStr>(const char* _name, const core::CStr& _value, const core::CStr& _defValue)
  {
    if (_value != _defValue)
    {
      Key(_name);
      String(_value.c_str());
    }
  }

  template<> void OutputArchive::Add<bool>(const char* _name, const bool& _value, const bool& _defValue)
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

  template<> CColor Get<CColor>(InputArchiveNode& _node, const char* _name, const CColor& _defValue)
  {
    InputArchiveNode::MemberIterator lIt = _node.FindMember(_name);
    const char* lValue = (lIt != _node.MemberEnd()) ? lIt->value.GetString() : nullptr;
    if (lValue)
    {
      core::CStrVector elems;
      core::Split(lValue, ' ', elems );
      HELIOSASSERT(elems.size() == 4);
      float r = std::stof(elems[0]);
      float g = std::stof(elems[1]);
      float b = std::stof(elems[2]);
      float a = std::stof(elems[3]);
      return CColor(r,g,b,a);
    }
    return _defValue;
  }
}
