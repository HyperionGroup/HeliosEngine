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
		JSON,
		SOL,
		LUA,
		SIGNALS,
		path.join(ANAX, "include"),
		ENGINE_PATH,
		path.join(ENGINE_PATH, "Core"),
		path.join(ENGINE_PATH, "Logic"),
		path.join(BX_DIR, "include/compat/msvc"),
		TINYFORMAT,
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common/"),
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/include"),
		path.join(BGFX_DIR, "3rdparty"),
	}
	
	