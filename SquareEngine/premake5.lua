workspace "SquareEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SquareEditor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "SquareEngine/premake5.lua"
include "SquareEditor/premake5.lua"