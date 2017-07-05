project "imgui"
    kind "StaticLib"
	targetdir "$(SolutionDir)lib/%{cfg.buildcfg}"
	
    files
	{
		path.join(IMGUI, "**.h"),
		path.join(IMGUI, "**.cpp"),
		path.join(IM3D, "**.h"),
		path.join(IM3D, "**.cpp"),
	}
	
	excludes
	{
		path.join(IMGUI, "examples/**.h"),
		path.join(IMGUI, "examples/**.cpp"),
		path.join(IM3D, "examples/**.h"),
		path.join(IM3D, "examples/**.cpp"),
	}
	
	files
	{
		path.join(IMGUI, "examples/directx11_example/imgui_impl_dx11.h"),
		path.join(IMGUI, "examples/directx11_example/imgui_impl_dx11.cpp"),
	}
	
	includedirs
	{ 
		UCRT,
		IMGUI,
		IM3D,
	}