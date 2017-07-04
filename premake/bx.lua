--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bx#license-bsd-2-clause
--

project "bx"
	kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"

	includedirs
	{
		UCRT,
		path.join(BX_DIR, "include"),
		path.join(BX_DIR, "include/compat/msvc"),
	}

	files {
		path.join(BX_DIR, "include/**.h"),
		path.join(BX_DIR, "include/**.inl"),
		path.join(BX_DIR, "src/**.cpp"),
	}

	excludes {
		path.join(BX_DIR, "src/amalgamated.**"),
	}
