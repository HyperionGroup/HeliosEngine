workspace "Helios"
   configurations { "Debug", "Release" }
   platforms { "x32", "x64" }
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
	
	targetdir "../bin/%{cfg.buildcfg}"
	
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