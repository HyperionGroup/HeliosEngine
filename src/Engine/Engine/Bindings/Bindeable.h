#pragma once

#include <imgui.h>

#define BINDEABLE \
public: \
virtual void Bind();

namespace io
{
    class CBindeableEntity
    {
    public:
        CBindeableEntity() = default;
        virtual ~CBindeableEntity() = default;
        virtual void Bind() = 0;
    };
}
