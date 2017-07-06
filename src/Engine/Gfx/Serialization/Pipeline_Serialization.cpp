#include "Gfx.h"

#include "Pipeline.h"

#include "Serialization.h"

namespace serialization
{
    template<> void Serialize<::gfx::CRenderTask>(OutputArchive& _archive, const ::gfx::CRenderTask& _object)
    {
        Serialize<core::CName>(_archive, _object);
        Serialize<core::CEnabled>(_archive, _object);
    }

    template<> void Serialize<::gfx::CBeginFrame>(OutputArchive& _archive, const ::gfx::CBeginFrame& _object)
    {
        _archive->StartObject();
        _archive->Key("task_type");
        _archive->String("begin_frame");
        Serialize<::gfx::CRenderTask>(_archive, _object);
        _archive->EndObject();
    }

    template<> void Serialize<::gfx::CEndFrame>(OutputArchive& _archive, const ::gfx::CEndFrame& _object)
    {
        _archive->StartObject();
        _archive->Key("task_type");
        _archive->String("end_frame");
        Serialize<::gfx::CRenderTask>(_archive, _object);
        _archive->EndObject();
    }

    template<> void Serialize<::gfx::CRenderDebugText>(OutputArchive& _archive, const ::gfx::CRenderDebugText& _object)
    {
        _archive->StartObject();
        _archive->Key("task_type");
        _archive->String("render_debug_text");
        _archive->Key("text");
        _archive->String(_object.mText);
        _archive->Key("x");
        _archive->Uint(_object.mX);
        _archive->Key("y");
        _archive->Uint(_object.mY);
        Serialize<::gfx::CRenderTask>(_archive, _object);
        _archive->EndObject();
    }

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

            inline uint32_t GetUint32Argb(float r, float g, float b, float a)
            {
                return  (uint32_t)(FloatToByte(r) << 24) + (FloatToByte(g) << 16) + (FloatToByte(b) << 8) + FloatToByte(a);
            }
        }
    }
    
    
}