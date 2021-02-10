workspace "Aether"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include Directories Struct (table)
IncludeDir = {}
IncludeDir["GLFW"] = "Aether/vendor/GLFW/include"
IncludeDir["Glad"] = "Aether/vendor/Glad/include"
IncludeDir["ImGui"] = "Aether/vendor/imgui"
IncludeDir["glm"] = "Aether/vendor/glm"

include "Aether/vendor/GLFW"
include "Aether/vendor/Glad"
include "Aether/vendor/imgui"

project "Aether"
	location "Aether"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "atpch.h"
	pchsource "Aether/src/atpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AT_PLATFORM_WINDOWS",
			"AT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "AT_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "AT_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "AT_DIST"
		buildoptions "/MD"
		optimize "on"

		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Aether/vendor/spdlog/include",
		"Aether/src",
		"Aether/vendor",
		"%{IncludeDir.glm}",
	}

	links
	{
		"Aether"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AT_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "AT_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "AT_DIST"
		buildoptions "/MD"
		optimize "on"