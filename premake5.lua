

--Premake5 lua Script

workspace "Midnight"
	configurations{"Debug" , "Release"}
	platforms { "Linux", "Win"}
	location "Build"
	architecture "x86_64"
	language "C++"


	filter {"configurations:Debug"}
		defines {"debug"}
		symbols "On"

	filter {"configurations:Release"}
		optimize "On"

	filter {}

	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

project "MNCore"
	--just for now a console app (dynamic lib after?)
	kind "ConsoleApp"
	files{"Midnight/Headers/**" , "Midnight/Sources/**" }
	includedirs {"Midnight/Headers"}
	includedirs {"Midnight/Headers/**"}



