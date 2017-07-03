project "gfx"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}/$(ConfigurationName)/"
	pchheader "Gfx.h"
	pchsource "../src/Engine/gfx/Gfx.cpp"
	
    files
	{
		path.join(ENGINE_PATH, "gfx/**.h"),
		path.join(ENGINE_PATH, "gfx/**.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		ENGINE_PATH,
		path.join(ANAX, "include"),
		path.join(ENGINE_PATH, "gfx"),
		path.join(ENGINE_PATH, "Core"),
	}