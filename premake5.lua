-- binaries and project paths
bin_path 			= path.getabsolute("bin")
build_path 			= path.getabsolute("build")

workspace "OPEN"
	configurations { "debug", "release" }
	platforms {"x86", "x64"}
	location "build"
	targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}/"
	startproject "playground"
	defaultplatform "x64"

	--language configuration
	warnings "Extra"
	cppdialect "c++17"
	systemversion "latest"

	filter "system:windows"
		defines { "OS_WINDOWS" }

	filter { "system:windows", "configurations:debug" }
		links {"dbghelp"}

	--os agnostic configuration
	filter "configurations:debug"
		defines {"DEBUG"}
		symbols "On"

	filter { "configurations:debug", "kind:SharedLib or StaticLib" }
		targetsuffix "d"

	filter "configurations:release"
		defines {"NDEBUG"}
		optimize "On"

	filter "platforms:x86"
		architecture "x32"

	filter "platforms:x64"
		architecture "x64"

	pic "On"
	filter {}

	-- Groups
	group "Graphics"
		include "glew"
		include "playground"
