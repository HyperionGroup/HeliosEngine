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
		path.join(ENGINE_PATH, "Engine"),
	}