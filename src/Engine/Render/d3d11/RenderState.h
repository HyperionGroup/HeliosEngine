#ifndef _RENDER_STATE_
#define _RENDER_STATE_

#pragma once

#include "Render.h"
#include "Singleton.h"

namespace render
{
    class CRenderState : public core::CSingleton<CRenderState>
    {
    private:
    public:
        CRenderState();
        virtual ~CRenderState();
    };
}

#endif