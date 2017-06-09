#pragma once

#include "Name.h"

namespace render
{
    class CShader : public core::CName
    {
    public:
        CShader();
        virtual ~CShader() = default;
    };
}