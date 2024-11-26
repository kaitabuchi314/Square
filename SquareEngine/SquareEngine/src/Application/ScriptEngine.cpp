#include "ScriptEngine.h"
#include "Glue.h"
#include "Window.h"
#include "Random.h"
#include <filesystem>

namespace Square
{
    void MoveFilesToTemp(const std::filesystem::path& sourceDir, std::string tempStringName)
    {
        std::filesystem::path parentDir = sourceDir.parent_path();
        std::filesystem::path tempDir = parentDir / tempStringName;

        std::filesystem::create_directory(tempDir);

        for (const auto& entry : std::filesystem::directory_iterator(sourceDir))
        {
            if (entry.is_regular_file())
            {
                std::filesystem::path destPath = tempDir / entry.path().filename();
                std::filesystem::copy_file(entry.path(), destPath, std::filesystem::copy_options::overwrite_existing);
            }
        }
    }

    Coral::ManagedAssembly LoadAssemblies(Coral::HostInstance hostInstance, std::filesystem::path tempDir, std::filesystem::path filePath)
    {
        auto contextName = std::to_string(RandomEntityUUID()) + "Context";
        auto loadContext = hostInstance.CreateAssemblyLoadContext(contextName);

        auto assemblyPath = tempDir / filePath.filename();
        auto& assembly = loadContext.LoadAssembly(assemblyPath.string());

        assembly.AddInternalCall("SquareEngine.Entity", "SQ_LOGInternal", reinterpret_cast<void*>(&LSQ_LOG));
        assembly.AddInternalCall("SquareEngine.Entity", "RandVectorInternal", reinterpret_cast<void*>(&RandVector));
        assembly.AddInternalCall("SquareEngine.Entity", "UpdateTransform", reinterpret_cast<void*>(&UpdateTransform));
        assembly.AddInternalCall("SquareEngine.Entity", "GetTransform", reinterpret_cast<void*>(&GetTransform));
        assembly.AddInternalCall("SquareEngine.Entity", "IsKeyDownInternal", reinterpret_cast<void*>(&Square::IsKeyDown));
        assembly.AddInternalCall("SquareEngine.Entity", "IsKeyUpInternal", reinterpret_cast<void*>(&Square::IsKeyUp));
        assembly.AddInternalCall("SquareEngine.Entity", "IsMousePressedInternal", reinterpret_cast<void*>(&Square::IsMouseDown));

        assembly.UploadInternalCalls();

        return assembly;
    }

    Assembly LoadAssembly(int argc, char** argv, const std::string& assemblyDLL)
    {
        std::filesystem::path filePath{ assemblyDLL.c_str() };
        std::filesystem::path parentPath = filePath.parent_path();

        MoveFilesToTemp(parentPath, "Temp");

        auto tempDir = parentPath.parent_path() / "Temp";
        auto coralDir = tempDir.string();

        Coral::HostSettings settings =
        {
            .CoralDirectory = coralDir,
            .ExceptionCallback = ExceptionCallback
        };

        Coral::HostInstance hostInstance;
        hostInstance.Initialize(settings);

        Coral::AssemblyLoadContext loadContext = hostInstance.CreateAssemblyLoadContext(std::to_string(RandomEntityUUID()) + "Context");

        auto assembly = LoadAssemblies(hostInstance, tempDir, filePath);

        Assembly a = Assembly(assembly, assemblyDLL, loadContext, hostInstance);

        return a;
    }

    Square::Assembly LoadAssembly(int argc, char** argv, const std::string& assemblyDLL, Coral::AssemblyLoadContext& context, Coral::HostInstance& host)
    {
        std::filesystem::path filePath{ assemblyDLL.c_str() };
        std::filesystem::path parentPath = filePath.parent_path();

        host.Shutdown();

        std::string tempFolderName = std::to_string(RandomEntityUUID());

        MoveFilesToTemp(parentPath, tempFolderName);

        auto tempDir = parentPath.parent_path() / tempFolderName;
        auto coralDir = tempDir.string();

        Coral::HostSettings settings =
        {
            .CoralDirectory = coralDir,
            .ExceptionCallback = ExceptionCallback
        };

        Coral::HostInstance hostInstance;
        hostInstance.Initialize(settings);

        Coral::AssemblyLoadContext loadContext = hostInstance.CreateAssemblyLoadContext(std::to_string(RandomEntityUUID()) + "Context");

        auto assembly = LoadAssemblies(hostInstance, tempDir, filePath);

        Assembly a = Assembly(assembly, assemblyDLL, loadContext, hostInstance);

        return a;
    }
}
