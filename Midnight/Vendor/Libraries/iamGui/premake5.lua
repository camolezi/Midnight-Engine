project "iamGui"

    kind "StaticLib"
    language "C++"
    
    targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
    objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

    files{
		"imconfig.h",
		"imgui.h",
		"imgui.cpp",
		"imgui_draw.cpp",
		"imgui_internal.h",
		"imgui_widgets.cpp",
		"imstb_rectpack.h",
		"imstb_textedit.h",
		"imstb_truetype.h",
        "imgui_demo.cpp"
    }
    
    --plataform
    systemversion "latest"
	cppdialect "C++17"
	staticruntime "On"
    
    filter {"configurations:Debug"}
        runtime "Debug"
        symbols "on"

    filter {"configurations:Release"}
        runtime "Release"
        optimize "on"

    filter{}