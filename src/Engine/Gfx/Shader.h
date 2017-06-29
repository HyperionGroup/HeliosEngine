#pragma once

#include "Core/Name.h"

namespace gfx
{
    class CShader : public core::CName
    {
    public:
        CShader() = default;
        virtual ~CShader();
        void Initialize(const char* _vs, const char* _fs);
        void Bind();
    protected:
    };
}