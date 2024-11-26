workspace "Test"
    configurations { "Debug", "Release" }

    targetdir "Binaries"

-- this needs to be relative to the coral dir instead of ../
include "../../Coral.Managed/premake5.lua"

include "premake5.lua"
