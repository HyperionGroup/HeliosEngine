project "anax"
	kind "StaticLib"
	
	includedirs {
		path.join(ANAX_DIR, "include"),
	}

	files {
		path.join(ANAX_DIR, "include", "**.hpp"),
		path.join(ANAX_DIR, "include", "**.inl"),
		path.join(ANAX_DIR, "src", "**.cpp"),
	}