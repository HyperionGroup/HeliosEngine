project "core"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"
	
	pchheader "Core.h"
	pchsource "../src/Engine/Core/Core.cpp"
	
    files
	{
		path.join(ENGINE_PATH, "Core/**.h"),
		path.join(ENGINE_PATH, "Core/**.cpp"),
		path.join(ENGINE_PATH, "Core/**.hpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		path.join(ANAX, "include"),
		ENGINE_PATH,
		path.join(ENGINE_PATH, "Core"),
		path.join(BX_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
	}
	
	