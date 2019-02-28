playground = path.getabsolute(".")

function use_playground()
	includedirs "%{playground}/include"
	links "playground"
end

project "playground"
	language "C++"
	kind "ConsoleApp"

	files
	{
		"include/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"include"
	}

	use_glew()
