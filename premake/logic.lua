project "logic"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"
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
		TINYFORMAT,
		path.join(ANAX, "include"),
		JSON,
		SIGNALS,
		ENGINE_PATH,
		path.join(ENGINE_PATH, "Logic"),
		path.join(ENGINE_PATH, "Core"),
		path.join(BGFX_DIR, "examples/common/"),
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
		path.join(BGFX_DIR, "3rdparty"),
	}