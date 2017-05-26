workspace "Helios"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location "../vs2015"
   language "C++"
   debugdir "\$(OutDir)"
   
   
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
	
	targetdir "../bin/Helios/%{cfg.buildcfg}"
	
project "HeliosEditor"
	kind "WindowedApp"
	flags { "ExtraWarnings" }
	files { "../src/HeliosEditor/*.cpp", "../src/HeliosEditor/*.h" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11/", "../src/Engine/User", "../src/Engine/Engine" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/" }
	libdirs { "$(SolutionDir)bin/%{cfg.buildcfg}/$(ConfigurationName)/" }
	libdirs { "$(DXSDK_DIR)lib/x86/" }
	links { "d3d11", "d3dcompiler", "Render", "Core", "User", "imgui", "Engine"}
	pchheader "HeliosEditor.h"
	pchsource "../src/HeliosEditor/main.cpp"
	
group "Engine"
project "Core"
    kind "StaticLib"
    files { "../src/Engine/Core/**.h", "../src/Engine/Core/**.cpp", "../src/Engine/Core/**.inl" }
	includedirs { "../src/Engine/Core" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/" }
	pchheader "Core.h"
	pchsource "../src/Engine/Core/Core.cpp"

project "Engine"
    kind "StaticLib"
    files { "../src/Engine/Engine/**.h", "../src/Engine/Engine/**.cpp", "../src/Engine/Engine/**.inl" }
	includedirs { "../src/Engine/Engine", "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11/", "../src/Engine/User" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	pchheader "Engine.h"
	pchsource "../src/Engine/Engine/Engine.cpp"

project "Render"
    kind "StaticLib"
    files { "../src/Engine/Render/**.h", "../src/Engine/Render/**.cpp", "../src/Engine/Render/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/Render/d3d11" , "../src/Engine/Engine", "../src/Engine/User" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/" }
	pchheader "Render.h"
	pchsource "../src/Engine/Render/Render.cpp"
	buildoptions { "-Zm150" }
	
project "User"
    kind "StaticLib"
    files { "../src/Engine/User/**.h", "../src/Engine/User/**.cpp", "../src/Engine/User/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" , "../src/Engine/Render" , "../src/Engine/Engine" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/" }
	pchheader "User.h"
	pchsource "../src/Engine/User/User.cpp"

group "3rdParty"
project "imgui"
    kind "StaticLib"
    files { "../src/3rdParty/imgui/**.h", "../src/3rdParty/imgui/**.cpp" }
	files { "../src/3rdParty/im3d/**.h", "../src/3rdParty/im3d/**.cpp" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d"}
	excludes {"../src/3rdParty/imgui/examples/**.cpp", "../src/3rdParty/imgui/examples/**.h"}
	excludes {"../src/3rdParty/im3d/examples/**.cpp", "../src/3rdParty/im3d/examples/**.h"}

local CPPSHARP_DIR = "../lib/CppSharp/Release_x32/"
	
workspace "HeliosBinder"
   configurations { "Release" }
   platforms { "x32" }
   location "../vs2015"
   language "C#"
   debugdir "\$(OutDir)"
	
	targetdir "../bin/HeliosBinder/%{cfg.buildcfg}"
	
project "HeliosBinder"
	kind  "ConsoleApp"
    language "C#"
    dotnetframework "4.6"
	
	files { "../src/HeliosBinder/*.cs" }
	libdirs { CPPSHARP_DIR }
	links
    {
      path.join(CPPSHARP_DIR, "CppSharp"),
      path.join(CPPSHARP_DIR, "CppSharp.AST"),
      path.join(CPPSHARP_DIR, "CppSharp.Generator")
    }