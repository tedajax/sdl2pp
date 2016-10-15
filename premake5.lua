workspace "SDL2PP"
    configurations { "Debug", "Release" }
    platforms { "Win32", "Win64" }

project "SDL2PP"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { "external/include", "include" }
    files { "include/sdl2pp/**.h", "src/**.cc" }
    excludes { "src/tests/*" }

    links { "SDL2", "SDL2main" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:Win32", "platforms:Win64" }
        system "Windows"

    filter "platforms:Win32"
        libdirs { "external/lib/x86" }
        architecture "x32"

    filter "platforms:Win64"
        libdirs { "external/lib/x64" }
        architecture "x64"

project "SDL2PP_Tests"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/tests/%{cfg.buildcfg}"

    files { "src/tests/**.cc" }

    links { "SDL2PP" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:Win32", "platforms:Win64" }
        system "Windows"

    filter "platforms:Win32"
        architecture "x32"

    filter "platforms:Win64"
        architecture "x64"