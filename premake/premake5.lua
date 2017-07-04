workspace "Helios"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   location "../vs"
   language "C++"
   
   targetdir "$(SolutionDir)bin/%{cfg.buildcfg}"
   debugdir "../data"
   
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

PREMAKE_PATH = "../premake/"
ENGINE_PATH = "../src/Engine/"
THIRD_PARTY = "../src/3rdParty/"
ANAX = path.join(THIRD_PARTY, "anax")
BX_DIR = path.join(THIRD_PARTY, "bx")
BIMG_DIR = path.join(THIRD_PARTY, "bimg")
BGFX_DIR = path.join(THIRD_PARTY, "bgfx")
IMGUI = path.join(THIRD_PARTY, "imgui")
IM3D = path.join(THIRD_PARTY, "im3d")
LUA = path.join(THIRD_PARTY, "luajit-2.0/src")
SOL = path.join(THIRD_PARTY, "sol2")
UCRT = path.join(THIRD_PARTY, "ucrt")
	
project "HeliosEditor"
	kind "WindowedApp"
	
	flags
	{
		"ExtraWarnings",
		--"FatalWarnings",
	}
	
	files { "../src/HeliosEditor/*.cpp", "../src/HeliosEditor/*.h" }

	defines
	{
		"ENTRY_CONFIG_IMPLEMENT_MAIN=1",
	}
	
	includedirs
	{
		UCRT,
		ENGINE_PATH,
		IMGUI,
		ANAX,
		IM3D,
		SOL,
		LUA,
		IMGUI,
		path.join(BGFX_DIR, "examples/common/"),
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/include"),
	}
	
	libdirs
	{
		"$(SolutionDir)lib/%{cfg.buildcfg}/$(ConfigurationName)/",
		"$(DXSDK_DIR)lib/x86/",
		"../bin/luajit/",
		"../bin/assimp/",
		"../bin/ucrt/",
	}
	
	links
	{
		"gfx",
		"core",
		"imgui",
		"engine",
		"lua51",
		"logic",
		"assimp",
		"bx",
		"bgfx",
		"bimg",
	}
	
	postbuildcommands
	{
		'echo F | xcopy "$(SolutionDir)..\\bin\\luajit\\lua51.dll" "$(TargetDir)lua51.dll" /Y',
		'echo F | xcopy "$(SolutionDir)..\\bin\\assimp\\assimp.dll" "$(TargetDir)assimp.dll" /Y'
	}

group "premake"	
project "vs2017"
	kind "ConsoleApp"
	
	files
	{
		path.join(PREMAKE_PATH, "**.lua"),
	}

	postbuildcommands
	{
		'echo F | $(SolutionDir)..\\sln\\BuildSolutionVS2017.bat'
	}
	
group "engine"
dofile("core.lua")
dofile("gfx.lua")
dofile("engine.lua")
dofile("logic.lua")

group "thridparty"
dofile ("imgui.lua")
dofile ("anax.lua")
dofile ("bx.lua")
dofile ("bimg.lua")
dofile ("bgfx.lua")