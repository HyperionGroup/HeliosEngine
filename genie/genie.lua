newoption {
	trigger = "with-amalgamated",
	description = "Enable amalgamated build.",
}

newoption {
	trigger = "with-ovr",
	description = "Enable OculusVR integration.",
}

newoption {
	trigger = "with-sdl",
	description = "Enable SDL entry.",
}

newoption {
	trigger = "with-glfw",
	description = "Enable GLFW entry.",
}

newoption {
	trigger = "with-profiler",
	description = "Enable build with intrusive profiler.",
}

newoption {
	trigger = "with-scintilla",
	description = "Enable building with Scintilla editor.",
}

newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

newoption {
	trigger = "with-examples",
	description = "Enable building examples.",
}

solution "helios"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION == "xcode4" then
		platforms {
			"Universal",
		}
	else
		platforms {
			"x64",
--			"Xbox360",
			"Native", -- for targets where bitness is not specified
		}
	end

	language "C++"
	startproject "editor"

MODULE_DIR = path.getabsolute("../")
HELIOS_DIR   = path.getabsolute("..")

UCRT_DIR =  path.join(HELIOS_DIR, "bin/ucrt")
ENGINE_DIR   = path.join(HELIOS_DIR, path.join("src", "Engine"))
CORE_DIR   = path.join(ENGINE_DIR, "Core")
GFX_DIR   = path.join(ENGINE_DIR, "Gfx")

local HELIOS_BUILD_DIR = path.join(HELIOS_DIR, ".build")
local GENIE_SCRIPTS_DIR = path.join(HELIOS_DIR, "genie/scripts")
local HELIOS_THIRD_PARTY_DIR = path.join(HELIOS_DIR, "src/3rdparty")
if not BX_DIR then
	BX_DIR = path.getabsolute(path.join(HELIOS_DIR, "../bx"))
end

ANAX_DIR  = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "anax"))
IMGUI_DIR  = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "imgui"))
IM3D_DIR  = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "im3d"))
BGFX_DIR   = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bgfx"))
SOL2_DIR   = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "sol2"))
LUA_DIR   = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "luajit-2.0/src"))

WORKING_DIR = path.join(BGFX_DIR, "examples/runtime")

BIMG_DIR   = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bimg"))
BX_DIR      = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bx"))
BX_DIR      = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bx"))

BX_DIR      = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bx"))
BX_DIR      = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bx"))
BX_DIR      = path.getabsolute(path.join(HELIOS_THIRD_PARTY_DIR, "bx"))

dofile (path.join(BX_DIR, "scripts/toolchain.lua"))
if not toolchain(HELIOS_BUILD_DIR, HELIOS_THIRD_PARTY_DIR) then
	return -- no action specified
end

function copyLib()
end

function engineLibrary(_name)

	project ("example-" .. _name)
		uuid (os.uuid("example-" .. _name))
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
	}

	files {
		path.join(BGFX_DIR, "examples", _name, "**.c"),
		path.join(BGFX_DIR, "examples", _name, "**.cpp"),
		path.join(BGFX_DIR, "examples", _name, "**.h"),
	}

	removefiles {
		path.join(HELIOS_DIR, "examples", _name, "**.bin.h"),
	}

	flags {
		"FatalWarnings",
	}
	
	links {
		"example-common",
		"bgfx",
		"bimg_decode",
		"bimg",
		"bx",
	}
	
	libdirs
	{
		"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/ucrt/x64"
	}

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

		configuration { "osx" }
			libdirs { "$(SDL2_DIR)/lib" }

		configuration {}
	end

	if _OPTIONS["with-glfw"] then
		defines { "ENTRY_CONFIG_USE_GLFW=1" }
		links   { "glfw3" }

		configuration { "linux or freebsd" }
			links {
				"Xrandr",
				"Xinerama",
				"Xi",
				"Xxf86vm",
				"Xcursor",
			}

		configuration { "osx" }
			linkoptions {
				"-framework CoreVideo",
				"-framework IOKit",
			}

		configuration {}
	end

	if _OPTIONS["with-ovr"] then
		configuration { "x64" }
			libdirs { path.join("$(OVR_DIR)/LibOVR/Lib/Windows/x64/Release", _ACTION) }

		configuration { "x64" }
			links { "libovr" }

		configuration {}
	end

	configuration { "vs*", "x64" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

	configuration { "vs201*", "x64" }
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

	configuration { "vs20*", "x64" }
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

	-- WinRT targets need their own output directories or build files stomp over each other
	configuration { "x64", "winphone8* or winstore8*" }
		targetdir (path.join(HELIOS_BUILD_DIR, "win64_" .. _ACTION, "bin", _name ))
		objdir (path.join(HELIOS_BUILD_DIR, "win64_" .. _ACTION, "obj", _name))

	configuration { "ARM", "winphone8* or winstore8*" }
		targetdir (path.join(HELIOS_BUILD_DIR, "arm_" .. _ACTION, "bin", _name))
		objdir (path.join(HELIOS_BUILD_DIR, "arm_" .. _ACTION, "obj", _name))

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
end

dofile(path.join(BGFX_DIR,   "scripts/bgfx.lua"))

group "3rdparty"
bgfxProject("", "StaticLib", {})

dofile(path.join(GENIE_SCRIPTS_DIR,   "imgui.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))
dofile(path.join(BX_DIR,   "scripts/bx.lua"))
--dofile(path.join(GENIE_SCRIPTS_DIR,   "luajit.lua"))

group "Engine"
dofile(path.join(GENIE_SCRIPTS_DIR,   "core.lua"))
dofile(path.join(GENIE_SCRIPTS_DIR,   "render.lua"))
dofile(path.join(GENIE_SCRIPTS_DIR,   "script.lua"))

group "Apps"
dofile(path.join(GENIE_SCRIPTS_DIR,   "editor.lua"))



if _OPTIONS["with-tools"] then
	dofile(path.join(BIMG_DIR, "scripts/bimg_encode.lua"))
end

if _OPTIONS["with-examples"] or _OPTIONS["with-tools"] then
	group "examples"
	dofile(path.join(BGFX_DIR, "scripts/example-common.lua"))
end

if _OPTIONS["with-examples"] then
	group "examples"
	engineLibrary("00-helloworld")
	engineLibrary("01-cubes")
	engineLibrary("02-metaballs")
	engineLibrary("03-raymarch")
	engineLibrary("04-mesh")
	engineLibrary("05-instancing")
	engineLibrary("06-bump")
	engineLibrary("07-callback")
	engineLibrary("08-update")
	engineLibrary("09-hdr")
	engineLibrary("10-font")
	engineLibrary("11-fontsdf")
	engineLibrary("12-lod")
	engineLibrary("13-stencil")
	engineLibrary("14-shadowvolumes")
	engineLibrary("15-shadowmaps-simple")
	engineLibrary("16-shadowmaps")
	engineLibrary("17-drawstress")
	engineLibrary("18-ibl")
	engineLibrary("19-oit")
	engineLibrary("20-nanovg")
	engineLibrary("21-deferred")
	engineLibrary("22-windows")
	engineLibrary("23-vectordisplay")
	engineLibrary("24-nbody")
	engineLibrary("26-occlusion")
	engineLibrary("27-terrain")
	engineLibrary("28-wireframe")
	engineLibrary("29-debugdraw")
	engineLibrary("30-picking")
	engineLibrary("31-rsm")
	engineLibrary("32-particles")
	engineLibrary("33-pom")

	-- C99 source doesn't compile under WinRT settings
	if not premake.vstudio.iswinrt() then
		engineLibrary("25-c99")
	end
end

if _OPTIONS["with-shared-lib"] then
	group "libs"
	bgfxProject("-shared-lib", "SharedLib", {})
end

if _OPTIONS["with-tools"] then
	group "tools"
	dofile "shaderc.lua"
	dofile "texturec.lua"
	dofile "texturev.lua"
	dofile "geometryc.lua"
end
