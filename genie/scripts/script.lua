project "script"
	kind "StaticLib"
	
	includedirs {
		path.join(ANAX_DIR, "include"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
		SOL2_DIR,
		LUA_DIR,
		ENGINE_DIR,
		CORE_DIR,
		GFX_DIR,
	}

	files {
		path.join(ENGINE_DIR, "Logic/**.h"),
		path.join(ENGINE_DIR, "Logic/**.cpp"),
	}
	
	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}