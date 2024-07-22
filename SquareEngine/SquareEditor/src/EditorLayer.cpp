#include "EditorLayer.h"

EditorLayer::EditorLayer() :
    window(1296, 864, "Square Editor", true),
    camera(glm::vec3(0, 0, -5), glm::vec3(0)),
    renderer(window.width, window.height),
    light({ glm::vec3(-500, 500, 500), glm::vec3(1.5f), 0.15f }),
    renderTimer(&window),
    computeTimer(&window),
    meshIcon(Square::loadTexture("Resources/meshicon.png")),
    scene()
{
	Square::SetMainCamera(&camera);
    Square::SetActiveRenderer(&renderer);

    renderer.SetLight(light);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    regular = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 15);
    bold = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 15);
    boldXL = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 20);

    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);

    ImGui_ImplOpenGL3_Init("#version 130");

    SetImGuiColors();
}

EditorLayer::~EditorLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.Flush();
}

void EditorLayer::Run(int argc, char** argv)
{
    while (window)
    {
        computeTimer.Start();

        scene.Update();

        MoveCamera();

        Square::UpdateCamera(&camera, true);

        computeTimer.Stop();

        renderTimer.Start();

        renderer.SetLight(light);

        renderer.BeginFrame(skyColorR*255, skyColorG*255, skyColorB*255);

        scene.Render();

        ImGuiFrame();

        renderer.Resize(window.width, window.height);

        renderTimer.Stop();

        renderTimerTime = renderTimer;
        computeTimerTime = computeTimer;

        window.EndFrame();
    }
}

void EditorLayer::MoveCamera()
{
    if (Square::IsMouseDown(0))
    {
        if (Square::GetMousePosition().x > window.width / 2.5f && !ImGui::GetIO().WantCaptureMouse)
            camera.rotation.y -= 0.00075f;
        if (Square::GetMousePosition().x < window.width / 1.5f && !ImGui::GetIO().WantCaptureMouse)
            camera.rotation.y += 0.00075f;
        if (Square::GetMousePosition().y > window.height / 2.5f && !ImGui::GetIO().WantCaptureMouse)
            camera.rotation.x -= 0.00075f;
        if (Square::GetMousePosition().y < window.height / 1.5f && !ImGui::GetIO().WantCaptureMouse)
            camera.rotation.x += 0.00075f;
    }

    if (Square::GetMouseScroll() != 0)
    {
        if (!ImGui::GetIO().WantCaptureMouse)
        {
            camera.position.z += Square::GetMouseScroll();
        }
        Square::ReceivedScroll();
    }
}

void EditorLayer::ImGuiFrame()
{
    regular->Scale = fontSize;
    bold->Scale = fontSize;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    DrawImGui();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::EndFrame();
}

void EditorLayer::DrawImGui()
{
    ImGui::Begin("Scene");

    for (Square::Entity e : scene.AllEntities())
    {
        std::string eTag = scene.GetEntityTag(e);

        if (ImGui::Button((eTag + " ").c_str()))
        {
            curSelectedEntity = e;

            selectedEntity = true;
        }
    }

    ImGui::End();
    
    static bool preferencesWindowOpen = false;

    ImGui::Begin("Settings");

    if (selectedEntity)
    {
        Square::TransformComponent& tc = scene.GetComponent<Square::TransformComponent>(curSelectedEntity);
        
        Square::TagComponent& tagC = scene.GetComponent<Square::TagComponent>(curSelectedEntity);

        ImGui::InputText("###selectedEntityName", &tagC.tag);

        ImGui::SameLine();

        if (ImGui::Button("+"))
        {
            ImGui::OpenPopup("addcomponentmenu");
        }

        if (ImGui::BeginPopup("addcomponentmenu"))
        {
            if (ImGui::MenuItem("Mesh Component"))
            {
                scene.AddComponent<Square::MeshComponent>(curSelectedEntity, "");
                scene.ReloadMesh(curSelectedEntity);
                scene.GetComponent<Square::MeshComponent>(curSelectedEntity).mesh->mat.texture = Square::loadTexture("Resources/grid.png");
            }

            ImGui::EndPopup();
        }

        ImGui::Separator();

        InputVector("Position: ", "###positioninput", &tc.position);
        InputVector("Rotation: ", "###rotationinput", &tc.rotation);
        InputVector("Scale: ", "###scaleinput", &tc.scale);

        if (scene.HasComponent<Square::MeshComponent>(curSelectedEntity))
        {
            ImGui::PushFont(bold);

            ImGui::Text("Mesh Component: ");

            ImGui::PopFont();

            DrawMeshComponentUI();
        }
    }
    
    ImGui::End();

    ImGui::Begin("Material Editor");

    if (selectedEntity && scene.HasComponent<Square::MeshComponent>(curSelectedEntity))
    {
        if (ImGui::ImageButton((void*)scene.GetComponent<Square::MeshComponent>(curSelectedEntity).mesh->mat.texture, ImVec2(30, 30)))
        {
            std::string fn = FileOpen(1);
            if (fn != "")
            {
                scene.GetComponent<Square::MeshComponent>(curSelectedEntity).mesh->mat.texture = Square::loadTexture(fn.c_str());
            }
        }

        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        {
            ImGui::SetTooltip("Material Base Color");
        }

        ImGui::SliderFloat("###inputshine", &scene.GetComponent<Square::MeshComponent>(curSelectedEntity).mesh->mat.shine, 1, 128);

        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        {
            ImGui::SetTooltip("Material Specular");
        }
    }
    
    ImGui::End();

    ImGui::Begin("Environment");

    float skyColor[3] = {skyColorR, skyColorG, skyColorB};

    ImGui::Text("Sky Color: ");
    ImGui::SameLine();

    if (ImGui::ColorEdit3("###colorsky", skyColor))
    {
        skyColorR = skyColor[0];
        skyColorG = skyColor[1];
        skyColorB = skyColor[2];
    }

    ImGui::PushFont(bold);

    ImGui::SeparatorText("Light");

    ImGui::PopFont();

    InputVector("Position: ", "###lightpositioninput", &light.lightPosition);
    InputVectorSlider("Color: ", "###lightcolorinput", &light.lightColor, 0, 100);

    ImGui::Text("Ambient: ");
    ImGui::SameLine();
    ImGui::SliderFloat("###inputambient", &light.ambientLight, 0, 1);

    ImGui::End();

    if (preferencesWindowOpen && ImGui::Begin("Preferences", &preferencesWindowOpen))
    {
        ImGui::Text("Font Size: ");
        ImGui::SameLine();
        ImGui::SliderFloat("###fontsize", &fontSize, 1, 5);

        ImGui::End();
    }
    
    ImGui::Begin("Performance");

    ImGui::Text("Compute Time: %fms.", computeTimerTime);
    ImGui::Text("Render Time: %fms.", renderTimerTime);

    ImGui::End();
    
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                window.Close();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Reset Camera"))
            {
                camera.position = glm::vec3(0, 0, -5);
                camera.rotation = glm::vec3(0, 0, 0);
            }

            if (ImGui::MenuItem("Preferences"))
            {
                preferencesWindowOpen = true;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Entity"))
        {
            if (ImGui::MenuItem("Create"))
            {
                scene.AddEntityDefaultTemplate("New Entity");
            }

            if (ImGui::MenuItem("Delete"))
            {
                selectedEntity = false;
                scene.DeleteEntity(curSelectedEntity);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void EditorLayer::SetImGuiColors()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.6000000238418579f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.WindowRounding = 7.0f;
    style.WindowBorderSize = 1.0f;
    style.WindowMinSize = ImVec2(32.0f, 32.0f);
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 4.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupRounding = 0.0f;
    style.PopupBorderSize = 0.5f;
    style.FramePadding = ImVec2(5.0f, 2.0f);
    style.FrameRounding = 3.0f;
    style.FrameBorderSize = 1.0f;
    style.ItemSpacing = ImVec2(6.0f, 6.0f);
    style.ItemInnerSpacing = ImVec2(6.0f, 6.0f);
    style.CellPadding = ImVec2(6.0f, 6.0f);
    style.IndentSpacing = 25.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 3.0f;
    style.TabRounding = 4.0f;
    style.TabBorderSize = 1.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.9200000166893005f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.2899999916553497f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.239999994635582f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05882352963089943f, 0.05882352963089943f, 0.05882352963089943f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f, 0.4000000059604645f, 0.5400000214576721f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.3372549116611481f, 0.3372549116611481f, 0.3372549116611481f, 0.5400000214576721f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5568627715110779f, 0.5568627715110779f, 0.5568627715110779f, 0.5400000214576721f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.0470588244497776f, 0.0470588244497776f, 0.0470588244497776f, 0.5400000214576721f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.1882352977991104f, 0.5400000214576721f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.3600000143051147f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 0.3300000131130219f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.2899999916553497f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4000000059604645f, 0.4392156898975372f, 0.4666666686534882f, 1.0f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2000000029802322f, 0.3600000143051147f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0f, 0.0f, 0.0f, 0.5199999809265137f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2784313857555389f, 0.2784313857555389f, 0.2784313857555389f, 0.2899999916553497f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2000000029802322f, 0.2196078449487686f, 0.2274509817361832f, 1.0f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.3294117748737335f, 0.6666666865348816f, 0.8588235378265381f, 1.0f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 0.0f, 0.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.0f, 0.0f, 0.0f, 0.3499999940395355f);
}

void EditorLayer::InputVector(const char* title, const char* id, glm::vec3* vector)
{
    float position[3] = { vector->x, vector->y, vector->z };

    ImGui::Text(title);
    ImGui::SameLine();
    ImGui::InputFloat3(id, position);

    vector->x = position[0];
    vector->y = position[1];
    vector->z = position[2];
}

void EditorLayer::InputVectorSlider(const char* title, const char* id, glm::vec3* vector, float min, float max)
{
    float position[3] = { vector->x, vector->y, vector->z };

    ImGui::Text(title);
    ImGui::SameLine();
    ImGui::SliderFloat3(id, position, min, max);

    vector->x = position[0];
    vector->y = position[1];
    vector->z = position[2];
}

void EditorLayer::DrawMeshComponentUI()
{
    if (ImGui::ImageButton((void*)meshIcon, ImVec2(30, 30)))
    {
        std::string fn = FileOpen(2);
        if (fn != "")
        {
            Square::MeshComponent& msh = scene.GetComponent<Square::MeshComponent>(curSelectedEntity);

            bool meshExists = msh.mesh;

            Square::Material mp;

            if (meshExists)
                mp = msh.mesh->mat;
    
            msh.meshPath = fn;
    
            scene.ReloadMesh(curSelectedEntity);
            
            if (meshExists)
                scene.GetComponent<Square::MeshComponent>(curSelectedEntity).mesh->mat = mp;
        }
    }
    
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
    {
        ImGui::SetTooltip("Load Mesh");
    }
}

std::string EditorLayer::FileOpen(int idx)
{
#ifdef WINDOWS
    // Save the current working directory
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Windows-specific file open dialog using Windows API (Unicode)
    OPENFILENAMEW ofn;
    wchar_t szFile[260] = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
    wchar_t filter[] = L"Image Files\0*.png;*.jpg\0Mesh Files\0*.obj;*.fbx;*.glb\0All Files\0*.*\0";
    ofn.lpstrFilter = filter;    ofn.nFilterIndex = idx;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    std::string result;

    if (GetOpenFileNameW(&ofn) == TRUE)
    {
        // Convert wide string to std::string
        char filePath[260];
        wcstombs(filePath, szFile, 260);

        // Find the current working directory again (in case it changed)
        std::string basePath = currentPath.string();

        // Convert to relative path
        result = GetRelativePath(std::string(filePath), basePath);
    }

    // Restore the original working directory
    std::filesystem::current_path(currentPath);

    return result;
#else
    // Not implemented for other platforms
    throw std::runtime_error("FileOpen not implemented for this platform.");
#endif
}

std::string EditorLayer::GetRelativePath(const std::string& absolutePath, const std::string& basePath)
{
    std::filesystem::path absPath(absolutePath);
    std::filesystem::path base(basePath);
    std::filesystem::path relativePath = std::filesystem::relative(absPath, base);
    return relativePath.string();
}
