project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
    debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Aether/src"
    }

    libdirs
    {
        "%{wks.location}/bin/" .. outputdir .. "/Aether"
    }

    links
    {
        "Aether"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "AT_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "AT_RELEASE"
        runtime "Release"
        optimize "on"