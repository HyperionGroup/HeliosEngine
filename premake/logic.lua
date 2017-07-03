project "logic"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}/$(ConfigurationName)/"
	pchheader "Logic.h"
	pchsource "../src/Engine/Logic/Logic.cpp"
	
    files
	{
		path.join(ENGINE_PATH, "Logic/**.h"),
		path.join(ENGINE_PATH, "Logic/**.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		SOL,
		LUA,
		path.join(ANAX, "include"),
		ENGINE_PATH,
		path.join(ENGINE_PATH, "Logic"),
		path.join(ENGINE_PATH, "Core")
	}