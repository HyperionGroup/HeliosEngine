workspace "Helios"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location "../vs2015"
   language "C++"
   debugdir "\$(OutDir)"
   
   
   filter "configurations:Debug"
      defines { "DEBUG" }
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
	kind "ConsoleApp"
	flags { "ExtraWarnings" }
	files { "../src/HeliosEditor/*.cpp", "../src/HeliosEditor/*.h" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render", "../src/Engine/IO",  "../src/Engine/User" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	libdirs { "$(SolutionDir)bin/%{cfg.buildcfg}/$(ConfigurationName)/" }
	libdirs { "$(DXSDK_DIR)lib/x86/" }
	links { "d3d11", "d3dcompiler", "Render", "IO", "Core", "User", "imgui"}
	
group "Engine"
project "Core"
    kind "StaticLib"
    files { "../src/Engine/Core/**.h", "../src/Engine/Core/**.cpp", "../src/Engine/Core/**.inl" }
	includedirs { "../src/Engine/Core" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }

project "Render"
    kind "StaticLib"
    files { "../src/Engine/Render/**.h", "../src/Engine/Render/**.cpp", "../src/Engine/Render/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	
project "IO"
    kind "StaticLib"
    files { "../src/Engine/IO/**.h", "../src/Engine/IO/**.cpp", "../src/Engine/IO/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" , "../src/Engine/IO"  }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	
project "User"
    kind "StaticLib"
    files { "../src/Engine/User/**.h", "../src/Engine/User/**.cpp", "../src/Engine/User/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" , "../src/Engine/Render"  }
	includedirs { "../src/3rdParty/imgui", "../src/3rdParty/im3d", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }

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