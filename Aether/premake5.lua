project "Aether"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

    pchheader "atpch.h"
    pchsource "src/atpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "src",
        "%{IncludeDir.VulkanSDK}"
    }

    libdirs
    {
        "%{LibraryDir.VulkanSDK}"
    }

    links
    {
        "%{Library.Vulkan}",
        "%{Library.ShaderC}"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
        }

        prebuildcommands
        {
            "rmdir %{wks.location}bin\\" .. outputdir .. "\\%{startPrj}\\assets\\ /q /s"
        }

        postbuildcommands
        {
            " xcopy %{wks.location}%{prj.name}\\assets\\ %{wks.location}bin\\" .. outputdir .. "\\%{startPrj}\\assets\\ /E /H /C /I"
        }

    filter "configurations:Debug"
        defines "AT_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "AT_RELEASE"
        runtime "Release"
        optimize "on"