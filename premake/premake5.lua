require "qt" 
local qt = premake.extensions.qt

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
	  qtsuffix "d"

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
	includedirs { "../src/3rdParty/Mathpp/Mathpp/", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/", "../src/3rdParty/glad/include/" }
	libdirs { "$(SolutionDir)bin/%{cfg.buildcfg}/$(ConfigurationName)/" }
	libdirs { "$(DXSDK_DIR)lib/x86/" }
	links { "d3d11", "d3dcompiler", "Mathpp", "Render", "IO", "Core", "User"}
	qt.enable()
	qtpath "C:/Qt/Qt5.6.0/5.6/msvc2015_64"
	qtmodules { "core", "gui", "widgets", "opengl" }
	qtprefix "Qt5"
	configuration { "Debug" }
		qtsuffix "d"

group "Engine"
project "Core"
    kind "StaticLib"
    files { "../src/Engine/Core/**.h", "../src/Engine/Core/**.cpp", "../src/Engine/Core/**.inl" }
	includedirs { "../src/Engine/Core" }
	includedirs { "../src/3rdParty/Mathpp/Mathpp/",  "../src/3rdParty/cereal/include/" }

project "Render"
    kind "StaticLib"
    files { "../src/Engine/Render/**.h", "../src/Engine/Render/**.cpp", "../src/Engine/Render/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" }
	includedirs { "../src/3rdParty/Mathpp/Mathpp/", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	
project "IO"
    kind "StaticLib"
    files { "../src/Engine/IO/**.h", "../src/Engine/IO/**.cpp", "../src/Engine/IO/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" , "../src/Engine/IO"  }
	includedirs { "../src/3rdParty/Mathpp/Mathpp/", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	
project "User"
    kind "StaticLib"
    files { "../src/Engine/User/**.h", "../src/Engine/User/**.cpp", "../src/Engine/User/**.inl" }
	includedirs { "../src/Engine/Core", "../src/Engine/Render" , "../src/Engine/Render"  }
	includedirs { "../src/3rdParty/Mathpp/Mathpp/", "../src/3rdParty/stb/", "../src/3rdParty/cereal/include/" }
	qt.enable()
	qtpath "C:/Qt/Qt5.6.0/5.6/msvc2015_64"
	qtmodules { "core", "gui", "widgets", "opengl" }
	qtprefix "Qt5"
	configuration { "Debug" }
		qtsuffix "d"

group "3rdParty"
project "Mathpp"
    kind "StaticLib"
    files { "../src/3rdParty/Mathpp/**.h", "../src/3rdParty/Mathpp/**.cpp", "../src/3rdParty/Mathpp/**.inl" }
	includedirs { "../src/3rdParty/Mathpp/Mathpp" }
	excludes {"../src/3rdParty/Mathpp/main.cpp"}
	
project "glad"
    kind "StaticLib"
    files { "../src/3rdParty/glad/**.h", "../src/3rdParty/glad/**.cpp", "../src/3rdParty/glad/**.inl" }
	includedirs { "../src/3rdParty/glad" }

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