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
        _archive.Begin();
        _archive.Add( "task_type", core::CStr("begin_frame") );
        Serialize<::gfx::CRenderTask>(_archive, _object);
        _archive.End();
    }

    template<> void Serialize<::gfx::CEndFrame>(OutputArchive& _archive, const ::gfx::CEndFrame& _object)
    {
        _archive.Begin();
        _archive.Add("task_type", core::CStr("end_frame"));
        Serialize<::gfx::CRenderTask>(_archive, _object);
        _archive.End();
    }

    template<> void Serialize<::gfx::CRenderDebugText>(OutputArchive& _archive, const ::gfx::CRenderDebugText& _object)
    {
        _archive.Begin();
        _archive.Add("task_type", core::CStr("render_debug_text"));
        Serialize<::gfx::CRenderTask>(_archive, _object);
        _archive.Add("text", _object.mText);
        _archive.Add("x", _object.mX, 0u);
        _archive.Add("y", _object.mY, 0u);
        _archive.End();
    }

    template<> void Deserialize<::gfx::CRenderTask>(InputArchiveNode& _node, ::gfx::CRenderTask& _object)
    {
        Deserialize<core::CName>(_node, _object);
        Deserialize<core::CEnabled>(_node, _object);
    }

    template<> void Deserialize<::gfx::CRenderDebugText>(InputArchiveNode& _node, ::gfx::CRenderDebugText& _object)
    {
        Deserialize<::gfx::CRenderTask>(_node, _object);
        _object.mText = Get<core::CStr>( _node, "text" );
        _object.mX = Get(_node, "x", 0u);
        _object.mY = Get(_node, "y", 0u);
        LOG_INFO_APPLICATION("gfx::CRenderDebugText");
    }

    template<> void Deserialize<::gfx::CBeginFrame>(InputArchiveNode& _node, ::gfx::CBeginFrame& _object)
    {
        Deserialize<::gfx::CRenderTask>(_node, _object);
        LOG_INFO_APPLICATION("gfx::CBeginFrame");
    }

    template<> void Deserialize<::gfx::CEndFrame>(InputArchiveNode& _node, ::gfx::CEndFrame& _object)
    {
        Deserialize<::gfx::CRenderTask>(_node, _object);
        LOG_INFO_APPLICATION("gfx::CEndFrame");
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