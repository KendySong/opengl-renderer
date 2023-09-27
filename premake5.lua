workspace "opengl-renderer"
    architecture "x64"
    location "build"
    configurations { "Release", "Debug" }

project "opengl-renderer"
    kind "ConsoleApp"
    language "C++"
    location "build"

    files { 
        "src/**.cpp", 
        "src/**.hpp", 
        "src/**.h", 

        "libraries/include/ImGui/**.cpp", 
        "shaders/**", 
        "libraries/lib/glad.c",
        "libraries/include/stb/stb_image.cpp",
    }

    includedirs "libraries/*"
    libdirs "libraries/lib"
    links { "opengl32", "glfw3", "gdi32" }

    filter "configurations:Release"
        optimize "Full"
        defines "RELEASE"

    filter "configurations:Debug"
        defines "DEBUG"