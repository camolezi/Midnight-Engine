project "GLAD"

	kind "StaticLib"
	language "C"

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

	files{
		"include/**",
		"src/**"
	}

	includedirs{"include/**"}

	systemversion "latest"
	staticruntime "On"


	filter {"system:linux"}
		--pic "On
--		links{ "lX11", "x11", "X11" , "lx11"}

	filter {"system:windows"}

	filter {"configurations:Debug"}
		runtime "Debug"
		symbols "on"

	filter {"configurations:Release"}
		runtime "Release"
		optimize "on"

	filter {}
