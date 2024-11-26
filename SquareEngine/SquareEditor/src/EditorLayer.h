#pragma once
#include <Square.h>
#define IMGUI_ENABLE_DOCKING

#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <filesystem>


#ifdef WINDOWS
#include <windows.h>
#include <commdlg.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#endif

class EditorLayer : public Square::GameLayer
{
public:
	EditorLayer(int arc, char** arv);
	virtual ~EditorLayer() override;
	virtual void Run() override;
private:
    void MoveCamera();
    void ImGuiFrame();
    void DrawImGui();
    void SetImGuiColors();
    void InputVector(const char* title, const char* id, glm::vec3* vector);
    void InputVectorSlider(const char* title, const char* id, glm::vec3* vector, float min, float max);
    void DrawMeshComponentUI();
    void DrawScriptComponentUI();

    std::string FileOpen(int idx);
    std::string GetRelativePath(const std::string& absolutePath, const std::string& basePath);
private:
	Square::Window window;
	Square::Camera camera;
	Square::Renderer renderer;

    Square::Light light;

    Square::Timer renderTimer;
    Square::Timer computeTimer;

    Square::Texture2D meshIcon;
    Square::Texture2D menuIcon;
    Square::Texture2D x;
    Square::Texture2D playButton;
    Square::Texture2D stopButton;
    Square::Texture2D reloadIcon;
    Square::Texture2D folderIcon;
    Square::Texture2D meshFileIcon;

    Square::Texture2D fileIcon;

    Square::Scene scene;

    Square::Entity curSelectedEntity;
private:
    float skyColorR = 35 / 255;
    float skyColorG = 164 / 255;
    float skyColorB = 234 / 255;
private:
    float fontSize = 1;

    ImFont* regular;
    ImFont* bold;
    ImFont* boldXL;
private:
    bool selectedEntity = false;
private:
    int argc;
    char** argv;

    bool paused = false;

    std::string currentProject = "Projects/Test/";
};
namespace math {
    template <typename T>
    T lerp(T start, T end, float t) {
        return start + t * (end - start);
    }
}
