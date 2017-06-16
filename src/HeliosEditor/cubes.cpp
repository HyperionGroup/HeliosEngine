/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"

#include "RenderableWorld.h"

#include "Logic/Logic.h"

#include "Vertex.h"

#include "Core/Logger\Logger.h"

#include "sol.hpp"
#include "Pipeline.h"

class ExampleCubes : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		// Create vertex stream declaration.
		gfx::CPositionColorVertex::init();

        mCube = std::make_shared< gfx::CRenderablePrimitive >();
        
		m_timeOffset = bx::getHPCounter();

        logic::sol_example();
	}

	virtual int shutdown() BX_OVERRIDE
	{
        mCube.reset();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			frameTime = now - last;
			last = now;
			freq = double(bx::getHPFrequency() );
			toMs = 1000.0/freq;

			time = (float)( (now-m_timeOffset)/double(bx::getHPFrequency() ) );
            render();
			return true;
		}

		return false;
	}

    bool render()
    {
        gfx::pipeline::BeginRender();
        gfx::pipeline::ClearView(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        gfx::pipeline::SetViewProjection();

        // Use debug font to print information about this example.
        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/01-cube");
        bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering simple static mesh.");
        bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

        // Submit 11x11 cubes.
        for (uint32_t yy = 0; yy < 11; ++yy)
        {
            for (uint32_t xx = 0; xx < 11; ++xx)
            {
                bx::mtxRotateXY(mCube->mtx, time + xx*0.21f, time + yy*0.37f);
                mCube->mtx[12] = -15.0f + float(xx)*3.0f;
                mCube->mtx[13] = -15.0f + float(yy)*3.0f;
                mCube->mtx[14] = 0.0f;

                // Set render states.
                bgfx::setState(0
                    | BGFX_STATE_DEFAULT
                    | BGFX_STATE_PT_TRISTRIP
                );

                // Set model matrix for rendering.
                mCube->Render();
            }
        }

        gfx::pipeline::EndRender();
        return true;
    }

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
    float time;
    int64_t frameTime;
    double freq;
    double toMs;

    std::shared_ptr< gfx::CRenderablePrimitive > mCube;
	int64_t m_timeOffset;
};

ENTRY_IMPLEMENT_MAIN(ExampleCubes);
