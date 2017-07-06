#include "Gfx.h"

#include "Pipeline.h"

#include "RenderableWorld.h"

namespace gfx
{
    namespace 
    {
        inline uint8_t FloatToByte(float fValue)
        {
            int i = static_cast<int>(0xff * fValue);
            if (i < 0)
                i = 0;
            else if (i > 0xff)
                i = 0xff;
            return static_cast<uint8_t>(i);
        }

        inline uint32_t GetUint32Argb( float r, float g, float b, float a)
        {
            return  (uint32_t)(FloatToByte(r) << 24) + (FloatToByte(g) << 16) + (FloatToByte(b) << 8) + FloatToByte(a);
        }
    }

    void CBeginFrame::Execute()
    {

    }

    void CEndFrame::Execute()
    {

    }

    void CRenderDebugText::Execute()
    {

    }
}