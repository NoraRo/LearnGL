glew = path.getabsolute(".")

function use_glew()
	includedirs "%{glew}/include"
	links "glew"
	filter "system:linux"
		links
		{
			"X11",
			"GL",
			"GLU"
		}

	filter "system:windows"
		links
		{
			"opengl32"
		}

	filter {}
end

project "glew"
	language "C++"
	kind "SharedLib"

	files
	{
		"include/**.h",
		"src/**.c"
	}

	includedirs
	{
		"include"
	}

	defines
	{
		"GLEW_BUILD"
	}

	filter "system:linux"
		links
		{
			"X11",
			"GL",
			"GLU"
		}

	filter "system:windows"
		links
		{
			"opengl32"
		}
