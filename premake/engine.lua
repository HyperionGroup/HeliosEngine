project "engine"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}/$(ConfigurationName)/"
	pchheader "Engine.h"
	pchsource "../src/Engine/Engine/Engine.cpp"
	
    files
	{
		path.join(ENGINE_PATH, "Engine/**.h"),
		path.join(ENGINE_PATH, "Engine/**.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		ENGINE_PATH,
		TINYFORMAT,
		path.join(ENGINE_PATH, "Engine"),
		path.join(ENGINE_PATH, "Core"),
		path.join(BX_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
		SOL,
		LUA
	}