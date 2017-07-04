--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bx#license-bsd-2-clause
--

project "bimg"
	kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"

	includedirs {
		UCRT,
		path.join(BX_DIR, "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BIMG_DIR, "3rdParty"),
		path.join(BIMG_DIR, "3rdparty/iqa/include"),
		path.join(BX_DIR, "include/compat/msvc"),
	}

	files {
		path.join(BIMG_DIR, "include/**"),
		path.join(BIMG_DIR, "src/**.**"),
	}
