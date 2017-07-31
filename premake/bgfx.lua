--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--
local qt = premake.extensions.qt

project "bgfx"
	kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"
	qt.enable()
	qtmodules { "core", "gui", "widgets" }
	qtpath "../src/3rdParty/qt"
	qtprefix "Qt5"

	includedirs {
		UCRT,
		path.join(ENGINE_PATH, "Core/nodejs"),
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
		path.join(BGFX_DIR, "3rdparty/khronos"),
		path.join(BGFX_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
		path.join(BGFX_DIR, "3rdparty/glslang"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/include"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/src/glsl"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/src"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/src/mesa"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/src/getopt"),
	}

	files {
		path.join(BGFX_DIR, "include/**.h"),
		path.join(BGFX_DIR, "src/**.cpp"),
		path.join(BGFX_DIR, "src/**.h"),
		path.join(BGFX_DIR, "examples/common/**.cpp"),
		path.join(BGFX_DIR, "examples/common/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/**.h"),
	}

	removefiles {
		path.join(BGFX_DIR, "src/**.bin.h"),
		path.join(BGFX_DIR, "examples/common/entry/**_windows.**"),
	}

	excludes
	{
		path.join(BGFX_DIR, "src/amalgamated.**"),
		path.join(BGFX_DIR, "3rdparty/scintilla/**.**"),
		path.join(BGFX_DIR, "3rdparty/glslang/**.**"),
		path.join(BGFX_DIR, "3rdparty/glsl-optimizer/**.**"),
	}
