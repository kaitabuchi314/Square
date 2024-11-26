import os
import shutil

def create_project():
    solution_name = input("Enter the solution name: ")
    project_name = input("Enter the project name: ")
    coral_dir = input("Enter the coral directory: ")

    # Create project directory
    os.makedirs(f"{solution_name}/Assets", exist_ok=True)
    os.makedirs(f"{solution_name}/Source", exist_ok=True)
    os.makedirs(f"{solution_name}/Binaries", exist_ok=True)

    # Create premake5-managed.lua file
    premake5_managed_content = f"""workspace "{solution_name}"
    configurations {{ "Debug", "Release" }}

    targetdir "Binaries"

-- this needs to be relative to the coral dir instead of ../
include "{coral_dir}Coral.Managed/premake5.lua"

include "premake5.lua"
"""
    with open(f"{solution_name}/premake5-managed.lua", "w") as file:
        file.write(premake5_managed_content)

    # Create premake5.lua file
    premake5_content = f"""-- this needs to be relative to the coral dir instead of ../
include "{coral_dir}Premake/CSExtensions.lua"

project "{project_name}"
    language "C#"
    dotnetframework "net8.0"
    kind "SharedLib"
    clr "Unsafe"
    
    -- Don't specify architecture here. (see https://github.com/premake/premake-core/issues/1758)

    propertytags {{
        {{ "AppendTargetFrameworkToOutputPath", "false" }},
        {{ "Nullable", "enable" }}
    }}

    files {{
        "Source/**.cs",
-- this needs to be relative to the coral dir instead of ../

        "{coral_dir}SquareEngine/Glue/Glue.cs"
    }}
    
    links {{ "Coral.Managed" }}
"""
    with open(f"{solution_name}/premake5.lua", "w") as file:
        file.write(premake5_content)

    # Copy Coral.Managed.runtimeconfig.json and Rebuild.bat to Assets
    files_to_copy = ["Coral.Managed.runtimeconfig.json"]
    for file_name in files_to_copy:
        if os.path.exists(file_name):
            shutil.copy(file_name, f"{solution_name}/Binaries/")
        else:
            print(f"Warning: {file_name} does not exist and could not be copied.")
    shutil.copy("Rebuild.bat", f"{solution_name}/")

    tpe = input("Please Pick An OS/IDE: ")
    if tpe == "vs":
        os.system("premake5 vs2022 --file="+solution_name+"/premake5-managed.lua")

if __name__ == "__main__":
    create_project()
    input("Press enter to close")
