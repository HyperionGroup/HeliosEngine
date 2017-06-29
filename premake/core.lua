project "core"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}/$(ConfigurationName)/"
	
	pchheader "Core.h"
	pchsource "../src/Engine/Core/Core.cpp"
	
    files
	{
		path.join(ENGINE_PATH, "Core/**.h"),
		path.join(ENGINE_PATH, "Core/**.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		path.join(ANAX, "include"),
		ENGINE_PATH,
		path.join(ENGINE_PATH, "Core"),
	}
	
	