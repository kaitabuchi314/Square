-- this needs to be relative to the coral dir instead of ../
include "../../Premake/CSExtensions.lua"

project "TestProject"
    language "C#"
    dotnetframework "net8.0"
    kind "SharedLib"
    clr "Unsafe"
    
    -- Don't specify architecture here. (see https://github.com/premake/premake-core/issues/1758)

    propertytags {
        { "AppendTargetFrameworkToOutputPath", "false" },
        { "Nullable", "enable" }
    }

    files {
        "Source/**.cs",
-- this needs to be relative to the coral dir instead of ../

        "../../SquareEngine/Glue/Glue.cs"
    }
    
    links { "Coral.Managed" }
