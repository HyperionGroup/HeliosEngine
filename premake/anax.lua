project "anax"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}/$(ConfigurationName)/"
	
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
		path.join(ANAX, "include")
	}