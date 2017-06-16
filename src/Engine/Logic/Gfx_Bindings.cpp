#include "Logic/Logic.h"

#include "Core/Logger\Logger.h"

#include <sol.hpp>
#include <Gfx/Shader.h>
#include <Gfx/Pipeline.h>
#include <Gfx/RenderableWorld.h>

#include "Containers.h"

namespace logic
{
    void create_shader(const char* name, const char* _vs, const char* _fs )
    {
    }

    std::shared_ptr< gfx::CRenderableObject > create_cube(const char* _name, float _x, float _y, float _z)
    {
        std::shared_ptr< gfx::CRenderablePrimitive > lCube = std::make_shared< gfx::CRenderablePrimitive >();
        lCube->SetName(_name);
        lCube->SetPosition(Float3(_x, _y, _z));
        return lCube;
    }

    std::shared_ptr< gfx::CLayer > create_layer(const char* _scene, const char* _layer)
    {
        gfx::CRenderableWorld& lWorld = gfx::CRenderableWorld::GetInstance();
        std::shared_ptr< gfx::CScene > lScene = lWorld.Get(_scene);
        if (!lScene)
        {
            lScene = std::make_shared< gfx::CScene >();
            lScene->SetName(_scene);
            gfx::CRenderableWorld::GetInstance().Add(_scene, lScene);
        }

        std::shared_ptr< gfx::CLayer > lLayer;
        lLayer = lScene->Get(_layer);
        if (!lLayer)
        {
            lLayer = std::make_shared< gfx::CLayer >();
            lLayer->SetName(_layer);
            lScene->Add(_layer, lLayer);
        }

        return lLayer;
    }

    void bind_shader(sol::state& _state)
    {
        _state.new_simple_usertype<gfx::CShader>("gfxShader",
            "Initialize", &gfx::CShader::Initialize,
                sol::base_classes, sol::bases<core::CName>()
            );

        _state.set_function("CreateGfxShader", create_shader);
    }

    void bind_renderable_world(sol::state& _state)
    {
        _state.new_simple_usertype<gfx::CRenderableObject>("gfxRenderableObject",
            sol::base_classes, sol::bases<core::CName>()
            );

        _state.new_simple_usertype<gfx::CLayer>("gfxLayer",
            "Add", &core::CStringArrayMap<gfx::CRenderableObject>::Add,
            "Get", &core::CStringArrayMap<gfx::CRenderableObject>::Get,
            "GetByIdx", &core::CStringArrayMap<gfx::CRenderableObject>::GetByIdx,
            sol::base_classes, sol::bases<core::CName>()
            );

        _state.new_simple_usertype<gfx::CScene>("gfxScene",
            "Add", &core::CStringArrayMap<gfx::CLayer>::Add,
            "Get", &core::CStringArrayMap<gfx::CLayer>::Get,
            "GetByIdx", &core::CStringArrayMap<gfx::CLayer>::GetByIdx,
            sol::base_classes, sol::bases<core::CName>()
            );

        _state.new_simple_usertype<gfx::CRenderableWorld>("gfxRenderableWorld",
            "Add", &core::CStringArrayMap<gfx::CScene>::Add,
            "Get", &core::CStringArrayMap<gfx::CScene>::Get,
            "GetByIdx", &core::CStringArrayMap<gfx::CScene>::GetByIdx,
            "GetInstance", &core::CSingleton< gfx::CRenderableWorld >::GetInstance
            );

        _state.new_simple_usertype<gfx::CRenderableMesh>("gfxRenderableMesh",
            sol::base_classes, sol::bases<gfx::CRenderableObject>()
            );

        _state.set_function("CreateGfxCube", create_cube);
        _state.set_function("CreateGfxLayer", create_layer);
    }

    void bind_pipeline(sol::state& _state)
    {
        _state.set_function("clear_view", gfx::pipeline::ClearView);
        _state.set_function("set_view_projection", gfx::pipeline::SetViewProjection);
        _state.set_function("begin_render", gfx::pipeline::BeginRender);
        _state.set_function("render_layer", gfx::pipeline::RenderWorldLayer);
        _state.set_function("render_debug_text", gfx::pipeline::RenderDebugText);
        _state.set_function("end_render", gfx::pipeline::EndRender);
    }

    void bind_gfx_lib(sol::state& _state)
    {
        bind_shader(_state);
        bind_renderable_world(_state);
    }
}