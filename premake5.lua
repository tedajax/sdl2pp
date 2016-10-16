workspace "SDL2PP"
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x86", "platforms:x64" }
        system "windows"

    filter "platforms:x86"
        architecture "x32"

    filter "platforms:x64"
        architecture "x64"

    libdirs "external/lib/%{cfg.platform}/%{cfg.buildcfg}"

project "SDL2PP"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs { "external/include", "include/sdl2pp" }
    files { "include/sdl2pp/**.h", "src/**.cc" }
    excludes { "src/tests/*" }
    links { "SDL2", "SDL2PP" }

project "SDL2PP_Tests"
    language "C++"
    targetdir "bin/tests/%{cfg.buildcfg}"

    files { "src/tests/**.cc" }
    includedirs { "external/include", "include" }
    links { "SDL2", "SDL2main", "SDL2PP" }

    filter "configurations:Debug"
        kind "ConsoleApp"

    filter "configurations:Release"
        kind "WindowedApp"

    filter "system:windows"
        links { "ole32", "oleaut32", "imm32", "winmm", "version" }
