project "anax"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"
	
    files
	{
		path.join(ANAX, "include/**.h"),
		path.join(ANAX, "src/**.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		path.join(ANAX, "include"),
		path.join(ENGINE_PATH, "Core"),
		SOL
	}