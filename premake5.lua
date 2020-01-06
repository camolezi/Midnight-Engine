
--Premake5 lua Script
workspace "Midnight"
	configurations{"Debug" , "Release" , "Deploy"}
	location "Build"
	architecture "x86_64"
	startproject "MNCore"


	--GlFW
	include "Midnight/Vendor/Libraries/GLFW"
	include "Midnight/Vendor/Libraries/GLAD"

project "MNCore"
	--just for now a console app (dynamic lib after?)
	kind "ConsoleApp"
	language "C++"
	systemversion "latest"

	filter {"configurations:Debug"}
		defines {"debug"}
		symbols "On"

	filter {"configurations:Release"}
		defines {"release"}
		optimize "On"

	filter {"configurations:Deploy"}
		defines {"deploy"}
		optimize "On"

	filter{"system:linux"}
		links{ "X11", "dl", "pthread", "Xrandr", "m", "z", "GL", "Xext", "Xfixes"}
		--buildoptions { "-lX11" }

	filter {}

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

	files{"Midnight/Headers/**" , "Midnight/Sources/**" }

	libdirs "Midnight/Vendor/Libraries/GLFW/Build/Bin/GLFW/Debug/linux"

	includedirs {"Midnight/Headers/**",
				 "Midnight/Headers",	 
				 "Midnight/Vendor/Libraries/GLFW/include",
				 "Midnight/Vendor/Libraries/GLAD/include/**"}

	links{"GLFW","GLAD", "GL"}
	





