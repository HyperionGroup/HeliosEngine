local qt = premake.extensions.qt

project "editor"
	kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"

	qt.enable()
	qtpath "../src/3rdParty/qt"
	qtprefix "Qt5"
	qtgenerateddir "$(SolutionDir)lib/mocs"
	qtmodules { "core", "gui", "widgets" }

	pchheader "Editor.h"
	pchsource "../src/Engine/Editor/Editor.cpp"
	
    files
	{
		path.join(ENGINE_PATH, "Editor/**.h"),
		path.join(ENGINE_PATH, "Editor/**.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
		SOL,
		LUA,
		ANY,
		TINYFORMAT,
		path.join(ANAX, "include"),
		JSON,
		SIGNALS,
		ENGINE_PATH,
		path.join(ENGINE_PATH, "Editor"),
		path.join(ENGINE_PATH, "Core"),
		path.join(BGFX_DIR, "examples/common/"),
		path.join(BGFX_DIR, "examples/common/entry"),
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
		path.join(BGFX_DIR, "3rdparty"),
	}