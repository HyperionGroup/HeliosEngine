project "core"
	kind "StaticLib"

	includedirs {
		IMGUI_DIR,
		IM3D_DIR,
		CORE_DIR,
	}

	files {
		path.join(CORE_DIR, "**.h"),
		path.join(CORE_DIR, "**.cpp"),
	}

	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}
		
	CORE_PCH  =  path.join(CORE_DIR, "Core.h")
	print("CORE_PCH\n" .. CORE_PCH)