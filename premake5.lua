
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
	cppdialect "C++17"
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
		links{"GL"}
	
	filter{"system:windows"}
		links{"opengl32.lib"}

	filter {}

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

	files{"Midnight/Headers/**" , "Midnight/Sources/**" }

	--External
	files{"Midnight/Vendor/Libraries/STB/**"}

	libdirs {"Midnight/Vendor/Libraries/GLFW/Build/Bin/GLFW/Debug/linux"}

	includedirs {"Midnight/Headers/**",
				 "Midnight/Headers",	 
				 "Midnight/Vendor/Libraries/GLFW/include",
				 "Midnight/Vendor/Libraries/GLAD/include/**",
				 "Midnight/Vendor/Libraries/STB"}

	links{"GLFW","GLAD"}

	files{"Midnight/Assets/**"}
	--filter {"files:**.png"}
  	--	buildaction "Copy"

	filter {}





