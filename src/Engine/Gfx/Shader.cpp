#include "Gfx.h"
#include "Shader.h"

#include "common.h"
#include "bgfx_utils.h"

namespace gfx
{
    void CShader::Initialize(const char* _vs, const char* _fs)
    {
        // Create program from shaders.
        m_program = loadProgram(_vs, _fs);
    }

    CShader::~CShader()
    {
        bgfx::destroyProgram(m_program);
    }

    void CShader::Bind()
    {
        // Submit primitive for rendering to view 0.
        bgfx::submit(0, m_program);
    }

}