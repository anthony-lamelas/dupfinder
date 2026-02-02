workspace "dupfinder"
    configurations { "Debug", "Release" }
    location "build"

project "dupfinder"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "bin/%{cfg.buildcfg}"

    files {
        "src/**.cpp",
        "src/**.c",
        "include/**.hpp"
    }

    includedirs { "include" }

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        optimize "Speed"
