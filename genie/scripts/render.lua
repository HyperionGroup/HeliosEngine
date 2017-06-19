project "gfx"
	kind "StaticLib"
	
	includedirs {
		path.join(UCRT_DIR,   "include"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
		CORE_DIR,
		GFX_DIR,
	}

	files {
		path.join(GFX_DIR, "**.h"),
		path.join(GFX_DIR, "**.cpp"),
	}
	
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}