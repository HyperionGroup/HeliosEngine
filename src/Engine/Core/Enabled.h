#pragma once

#include "Str.h"

namespace core
{
    class CEnabled
    {
      SERIALIZABLE_OBJECT
    public:
        CEnabled() : mEnabled(true) {}
        virtual ~CEnabled() {}
        bool IsEnabled() const { return mEnabled;  }
        void SetEnabled(const bool _enabled) { mEnabled = _enabled; }
    protected:
        bool mEnabled;
    };
}