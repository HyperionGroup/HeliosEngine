#pragma once

#include "Name.h"
#include "Core/Utils/Containers.h"

namespace core
{
  class CAttribute : public CName
  {
  public:
    CAttribute(const char* _name, void* _value, bool _editable)
      : CName(_name)
      , mValue(_value)
      , mEditable(_editable)
    {
    }
    virtual ~CAttribute() = default;
    virtual uint32_t      GetSize()	const = 0;
    virtual const size_t  Hash()    const = 0;
    bool IsEditable() { return mEditable; }
    template < typename U >
    bool Is() const { return mHash == typeid(U).hash_code(); }
    template < typename U >
    U* As() { return static_cast<U*>(mValue); }

  protected:
    void* mValue;
    bool  mEditable;
  };

  template<typename T>
  class CTemplatedAttribute : public CAttribute
  {
  public:
    CTemplatedAttribute(const char* _name, T* _value, bool _editable)
      : CAttribute(_name,(void*)_value, _editable)
    {
    }
    virtual ~CTemplatedAttribute() = default;
    virtual uint32 GetSize() const { return sizeof(T); };
    virtual const size_t Hash() const { return typeid(T).hash_code(); }
  };

  class CAttributesTable : public CStringArrayMap< CAttribute >
  {
  public:
    CAttributesTable() = default;
    virtual ~CAttributesTable() = default;
    template< typename T >
    void AddAttribute(const char* _name, T& _value, bool _editable = true)
    {
      Add(_name, std::make_shared< CTemplatedAttribute< T > >(_name, &_value, _editable));
    }
  };
}