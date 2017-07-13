#pragma once

#include <functional>

namespace core
{
  template <typename O>
  class CObjectFactory
  {
  protected:
    CObjectFactory() = default;
    ~CObjectFactory() = default;

    template <typename T>
    void Register()
    {
      static_assert(std::is_base_of<O, T>::value, "Invalid registration");
      mCreators[typeid(T).name()] = []() { return std::make_shared<T>(); };
    }

    std::shared_ptr<O> Create(const core::CStr& _type)
    {
      HELIOSASSERT(mCreators.find(_type) != mCreators.end());
      return mCreators[_type]();
    }
  private:
    std::map < const core::CStr, std::function<std::shared_ptr<O>()>> mCreators;
  };
}