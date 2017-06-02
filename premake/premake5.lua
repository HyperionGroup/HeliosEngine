workspace "Helios"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location "../vs"
   language "C++"
   
   targetdir "$(SolutionDir)bin/%{cfg.buildcfg}"
   
   filter "configurations:Debug"
      defines { "DEBUG", "DX_LOG_CALLS" }
	  rtti ("off")
	  characterset ("MBCS")
	  symbols "on"

   filter "configurations:Release"
      defines { "NO_DEBUG" }
	  characterset ("MBCS")
	  rtti ("off")
      optimize "On"
	
project "HeliosEditor"
	kind "WindowedApp"
	flags { "ExtraWarnings" }
	files { "../src/HeliosEditor/*.cpp", "../src/HeliosEditor/*.h" }
	includedirs { "../src/Engine/Engine", "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11/", "../src/Engine/Graphics" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/sol2", "../src/3rdParty/luajit-2.0/src" }
	libdirs { "$(SolutionDir)bin/%{cfg.buildcfg}/$(ConfigurationName)/" }
	libdirs { "$(DXSDK_DIR)lib/x86/" }
	libdirs { "$(SolutionDir)../bin/luajit/" }
	links { "d3d11", "d3dcompiler", "Render", "Core", "imgui", "Engine", "lua51", "Logic" }
	pchheader "HeliosEditor.h"
	pchsource "../src/HeliosEditor/main.cpp"
	postbuildcommands { 'echo F | xcopy "$(SolutionDir)..\\bin\\luajit\\lua51.dll" "$(TargetDir)lua51.dll" /Y' }
	
group "Engine"
project "Core"
    kind "StaticLib"
    files { "../src/Engine/Core/**.h", "../src/Engine/Core/**.cpp", "../src/Engine/Core/**.inl" }
	includedirs { "../src/Engine/Core" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d" }
	pchheader "Core.h"
	pchsource "../src/Engine/Core/Core.cpp"

project "Engine"
    kind "StaticLib"
    files { "../src/Engine/Engine/**.h", "../src/Engine/Engine/**.cpp", "../src/Engine/Engine/**.inl" }
	includedirs { "../src/Engine/Engine", "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Logic", "../src/Engine/Render/d3d11/", "../src/Engine/Graphics" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d" }
	includedirs { "../src/3rdParty/sol2", "../src/3rdParty/luajit-2.0/src" }
	pchheader "Engine.h"
	pchsource "../src/Engine/Engine/Engine.cpp"

project "Graphics"
    kind "StaticLib"
    files { "../src/Engine/Graphics/**.h", "../src/Engine/Graphics/**.cpp", "../src/Engine/GraphicsGraphics/**.inl" }
	includedirs { "../src/Engine/Engine", "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11/", "../src/Engine/Graphics" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d" }
	pchheader "Graphics.h"
	pchsource "../src/Engine/Graphics/Graphics.cpp"
	
project "Logic"
    kind "StaticLib"
    files { "../src/Engine/Logic/**.h", "../src/Engine/Logic/**.cpp", "../src/Engine/GraphicsGraphics/**.inl" }
	includedirs { "../src/Engine/Engine", "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11/", "../src/Engine/Graphics", "../src/Engine/Logic" }
	includedirs { "../src/3rdParty/sol2", "../src/3rdParty/luajit-2.0/src" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d" }
	pchheader "Logic.h"
	pchsource "../src/Engine/Logic/Logic.cpp"

project "Render"
    kind "StaticLib"
    files { "../src/Engine/Render/**.h", "../src/Engine/Render/**.cpp", "../src/Engine/Render/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11" , "../src/Engine/Engine", "../src/Engine/Graphics" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/" }
	pchheader "Render.h"
	pchsource "../src/Engine/Render/Render.cpp"
	buildoptions { "-Zm150" }

group "3rdParty"
project "imgui"
    kind "StaticLib"
    files { "../src/3rdParty/imgui/**.h", "../src/3rdParty/imgui/**.cpp" }
	files { "../src/3rdParty/im3d/**.h", "../src/3rdParty/im3d/**.cpp" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d"}
	excludes {"../src/3rdParty/imgui/examples/**.cpp", "../src/3rdParty/imgui/examples/**.h"}
	excludes {"../src/3rdParty/im3d/examples/**.cpp", "../src/3rdParty/im3d/examples/**.h"}