project "editor"
		kind "WindowedApp"

	configuration {}
	
	debugdir (WORKING_DIR)
	
	includedirs {
		path.join(UCRT_DIR,   "include"),
		SOL2_DIR,
		ANAX_DIR,
		ENGINE_DIR,
	}

	files {
		path.join(HELIOS_DIR, "src/HeliosEditor","cubes.cpp"),
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
		"anax",
		"lua51",
		"core",
		"gfx",
		"script",
	}

	configuration { "vs*", "x64" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}
		
	configuration { "x64" }
		targetdir (path.join(HELIOS_BUILD_DIR, _ACTION, "Win64", "bin"))
		objdir (path.join(HELIOS_BUILD_DIR, _ACTION, "Win64", "obj"))
		os.copyfile(path.join(HELIOS_DIR, "bin/luajit", "lua51.dll"), path.join(HELIOS_BUILD_DIR,  _ACTION, "Win64", "bin", "lua51.dll"))
