
include "Dependencies.lua"

startPrj = "Sandbox"

workspace "Aether-Engine"
    architecture "x86_64"
    startproject "%{startPrj}"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


group ""
include "Aether"
include "Sandbox"