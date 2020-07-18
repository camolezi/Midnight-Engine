	
--Premake5 lua Script
workspace "Midnight"
	configurations{"Debug" , "Release" , "Deploy"}
	location "Build"
	architecture "x86_64"
	startproject "MNCore"


	--GlFW
	include "Midnight/Vendor/Libraries/GLFW"
	include "Midnight/Vendor/Libraries/GLAD"
	include "Midnight/Vendor/Libraries/iamGui"
	
project "MNCore"
	--just for now a console app (dynamic lib after?)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"

	filter {"configurations:Debug"}
		defines {"debug"}
		runtime "Debug"
		symbols "On"

	filter {"configurations:Release"}
		defines {"MNRelease"}
		runtime "Release"
		optimize "On"

	filter {"configurations:Deploy"}
		defines {"deploy"}
		runtime "Release"
		optimize "On"

	filter{"system:linux"}
		--on linux you need xorg-dev and libasound2-dev to build from source
		links{ "X11", "dl", "pthread", "Xrandr", "m", "z", "GL", "Xext", "Xfixes", "dl"}
		links{"GL"}
		defines {"MNLinux"}
	
	filter{"system:windows"}
		links{"opengl32.lib", "dsound.lib"}
		defines {"MNWindows"}

	filter {}

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

	files{"Midnight/Src/**"}

	--External Vendor Files
		files{"Midnight/Vendor/Libraries/STB/**"}
		--Iam gui plataform specific
		files{"Midnight/Vendor/Libraries/iamGui/plataform/**"}
		--Miniaudio
		files{"Midnight/Vendor/Libraries/miniaudio/include/**"}
		--cute_sound
		files{"Midnight/Vendor/Libraries/cute_sound/**"}


	libdirs {"Midnight/Vendor/Libraries/GLFW/Build/Bin/GLFW/Debug"}

	includedirs {"Midnight/Src/**",
				 "Midnight/Src",	 
				 "Midnight/Vendor/Libraries/GLFW/include/",
				 "Midnight/Vendor/Libraries/GLAD/include/**",
				 "Midnight/Vendor/Libraries/STB",
				 "Midnight/Vendor/Libraries/iamGui",
				 "Midnight/Vendor/Libraries/iamGui/plataform",
				 "Midnight/Vendor/Libraries/miniaudio/include",
				 "Midnight/Vendor/Libraries/cute_sound"}

	links{"GLFW","GLAD","iamGui"}

	files{"Midnight/Assets/**"}
	--filter {"files:**.png"}
  	--	buildaction "Copy"

	filter {}





