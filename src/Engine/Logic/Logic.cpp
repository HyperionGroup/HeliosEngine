#include "Logic.h"

#include "Core/Logger\Logger.h"

#include "Gfx\StaticMesh.h"

#include <sol.hpp>

#include <string>
#include <iostream>

#include <anax/anax.hpp>
#include <anax/Component.hpp>

namespace logic
{
  extern void bind_gfx_lib( sol::state& _state );
  extern void bind_core_lib( sol::state& _state );

  struct RenderableLayerComponent: anax::Component
  {
    std::string mName;
  };

  struct OpaqueLayer: public RenderableLayerComponent
  {
    OpaqueLayer()
      : RenderableLayerComponent()
    {
      mName = "Opaque";
    }
  };

  struct TransparentLayer : public RenderableLayerComponent
  {
    TransparentLayer()
      : RenderableLayerComponent()
    {
      mName = "Transparent";
    }
  };

  template < typename TRenderableLayer, class RequireList, class ExcludeList = anax::Excludes<>>
  struct RenderingSystem : anax::System<RequireList, ExcludeList>
  {
      std::string mName;
      /// Construct a SpriteRenderingSystem with no render target
      RenderingSystem()
      {
      }
  };
}