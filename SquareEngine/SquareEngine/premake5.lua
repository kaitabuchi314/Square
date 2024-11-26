project "SquareEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "src/**.inl", "Glue/Glue.cs", "vendor/glad/**.c", "vendor/TinyXML/tinyxml2.cpp" }

   includedirs
   {
	"src",
    "src/Rendering",
    "src/Application",
    "src/Tools",
    "vendor/include-glfw",
    "vendor/include-glad",
    "vendor/include",
    "../Coral.Native/Include"
   }

   links
   {
    "vendor/glfw3.lib", "vendor/glfw3_mt.lib", "vendor/glfw3dll.lib", "vendor/assimp-vc143-mt.lib", "Coral.Native"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"