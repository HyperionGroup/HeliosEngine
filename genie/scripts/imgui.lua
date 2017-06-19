project "imgui"
	kind "StaticLib"
	
	includedirs {
		IMGUI_DIR,
		IM3D_DIR,
	}

	files {
		path.join(UCRT_DIR,   "include"),
		path.join(IMGUI_DIR, "**.h"),
		path.join(IMGUI_DIR, "**.cpp"),
		path.join(IM3D_DIR, "**.h"),
		path.join(IM3D_DIR, "**.cpp"),
	}
	
	excludes
	{
		path.join(IMGUI_DIR, "examples/**.h"),
		path.join(IMGUI_DIR, "examples/**.cpp"),
		path.join(IM3D_DIR, "examples/**.h"),
		path.join(IM3D_DIR, "examples/**.cpp"),
	}

	configuration { "linux-*" }
		buildoptions {
			"-fPIC",
		}