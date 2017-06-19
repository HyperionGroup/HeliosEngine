project "editor"
		kind "WindowedApp"

	configuration {}
	
	debugdir (WORKING_DIR)
	
	includedirs {
		path.join(UCRT_DIR,   "include"),
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
		SOL2_DIR,
		LUA_DIR,
		CORE_DIR,
		GFX_DIR,
		ENGINE_DIR,
	}

	files {
		--path.join(HELIOS_DIR, "src/HeliosEditor", "**.c"),
		path.join(HELIOS_DIR, "src/HeliosEditor","cubes.cpp"),
		--path.join(HELIOS_DIR, "src/HeliosEditor","**.h"),
	}

	--flags {
		--"FatalWarnings",
	--}
	
	libdirs
	{
		path.join(HELIOS_DIR, "bin/luajit" ),
		path.join(UCRT_DIR,   "x64"),
	}
	
	links
	{
		"lua51",
		"example-common",
		"bgfx",
		"bimg_decode",
		"bimg",
		"bx",
		"core",
		"gfx",
		"script",
	}

	configuration { "vs*", "x32 or x64" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

	configuration { "vs201*", "x32 or x64" }
		linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
			"/DELAYLOAD:\"libEGL.dll\"",
			"/DELAYLOAD:\"libGLESv2.dll\"",
		}

	configuration { "mingw*" }
		targetextension ".exe"
		links {
			"gdi32",
			"psapi",
		}

	configuration { "vs20*", "x32 or x64" }
		links {
			"gdi32",
			"psapi",
		}

	configuration { "durango" }
		links {
			"d3d11_x",
			"d3d12_x",
			"combase",
			"kernelx",
		}

	configuration { "winphone8* or winstore8*" }
		removelinks {
			"DelayImp",
			"gdi32",
			"psapi"
		}
		links {
			"d3d11",
			"dxgi"
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

	configuration { "x64", "winphone8* or winstore8*" }
		targetdir (path.join(HELIOS_BUILD_DIR, "win64_" .. _ACTION, "bin"))
		objdir (path.join(HELIOS_BUILD_DIR, "win64_" .. _ACTION, "obj"))
		os.copyfile(path.join(HELIOS_DIR, "bin/luajit", "lua51.dll"), path.join(HELIOS_DIR, ".build",  "win64_" .. _ACTION, "bin", "lua51.dll"))

	configuration { "ARM", "winphone8* or winstore8*" }
		targetdir (path.join(HELIOS_BUILD_DIR, "arm_" .. _ACTION, "bin"))
		objdir (path.join(HELIOS_BUILD_DIR, "arm_" .. _ACTION, "obj"))

	configuration { "mingw-clang" }
		kind "ConsoleApp"

	configuration { "android*" }
		kind "ConsoleApp"
		targetextension ".so"
		linkoptions {
			"-shared",
		}
		links {
			"EGL",
			"GLESv2",
		}

	configuration { "nacl*" }
		kind "ConsoleApp"
		targetextension ".nexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "pnacl" }
		kind "ConsoleApp"
		targetextension ".pexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"

	configuration { "linux-* or freebsd", "not linux-steamlink" }
		links {
			"X11",
			"GL",
			"pthread",
		}

	configuration { "linux-steamlink" }
		links {
			"EGL",
			"GLESv2",
			"SDL2",
			"pthread",
		}

	configuration { "rpi" }
		links {
			"X11",
			"GLESv2",
			"EGL",
			"bcm_host",
			"vcos",
			"vchiq_arm",
			"pthread",
		}

	configuration { "osx" }
		linkoptions {
			"-framework Cocoa",
			"-framework QuartzCore",
			"-framework OpenGL",
			"-weak_framework Metal",
		}

	configuration { "ios* or tvos*" }
		kind "ConsoleApp"
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
			"-weak_framework Metal",
		}

	configuration { "xcode4", "ios" }
		kind "WindowedApp"
		files {
			path.join(HELIOS_DIR, "examples/runtime/iOS-Info.plist"),
		}

	configuration { "xcode4", "tvos" }
		kind "WindowedApp"
		files {
			path.join(HELIOS_DIR, "examples/runtime/tvOS-Info.plist"),
		}

	configuration { "qnx*" }
		targetextension ""
		links {
			"EGL",
			"GLESv2",
		}

	configuration {}

	strip()