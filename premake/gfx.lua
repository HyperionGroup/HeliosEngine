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
		SOL,
		LUA,
		ENGINE_PATH,
		BGFX_DIR,
		TINYFORMAT,
		path.join(THIRD_PARTY, "assimp"),
		path.join(ANAX, "include"),
		path.join(ENGINE_PATH, "gfx"),
		path.join(ENGINE_PATH, "Core"),
		path.join(BGFX_DIR, "examples/common/"),
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
	}