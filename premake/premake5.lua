workspace "Helios"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location "../vs2015"
   language "C++"
   debugdir "\$(OutDir)"
   
   filter "configurations:Debug"
      defines { "DEBUG" }
	  rtti ("off")
	  symbols "on"

   filter "configurations:Release"
      defines { "NO_DEBUG" }
      optimize "On"
	
	targetdir "../bin/Helios/%{cfg.buildcfg}"
	
project "HeliosEditor"
	kind "ConsoleApp"
	flags { "ExtraWarnings" }
	files { "../src/HeliosEditor/*.cpp" }
	includedirs { "../src/3rdParty/Mathpp/Mathpp/", "../src/3rdParty/stb/" }
	libdirs { "$(SolutionDir)bin/%{cfg.buildcfg}/$(ConfigurationName)/" }
	links {"Mathpp" }

group "Engine"
project "Core"
    kind "StaticLib"
    files { "../src/Engine/Core/**.h", "../src/Engine/Core/**.cpp", "../src/Engine/Core/**.inl" }
	includedirs { "../src/Engine/Core" }

group "3rdParty"
project "Mathpp"
    kind "StaticLib"
    files { "../src/3rdParty/Mathpp/**.h", "../src/3rdParty/Mathpp/**.cpp", "../src/3rdParty/Mathpp/**.inl" }
	includedirs { "../src/3rdParty/Mathpp/Mathpp" }
	excludes {"../src/3rdParty/Mathpp/main.cpp"}

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