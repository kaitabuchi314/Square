#include "EditorLayer.h"


EditorLayer::EditorLayer() :
    window(1296, 864, "Square Editor", true),
    camera(glm::vec3(0, 0, -5), glm::vec3(0)),
    renderer(window.width, window.height),
    box(positions, texCoords, normals, indices, sizeof(positions), sizeof(texCoords), sizeof(normals), sizeof(indices)),
    texture(Square::loadTexture("../Assets/concrete.jpg")),
    position(),
    rotation(),
    scale(1),
    light( { glm::vec3(-500, 500, 500), glm::vec3(1.5f), 0.15f } )
{
	Square::SetMainCamera(&camera);

    renderer.SetLight(light);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    regular = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Regular.ttf", 15);
    bold = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 15);

    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);

    ImGui_ImplOpenGL3_Init("#version 130");

    SetImGuiColors();
}

EditorLayer::~EditorLayer()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    box.Flush();
    window.Flush();
}

void EditorLayer::Run(int argc, char** argv)
{
    while (window)
    {
        MoveCamera();

        Square::UpdateCamera(&camera, true);

        renderer.SetLight(light);
        renderer.BeginFrame(skyColorR*255, skyColorG*255, skyColorB*255);

        renderer.RenderMesh(box, shine, texture, position, rotation, scale);
        
        ImGuiFrame();

        renderer.Resize(window.width, window.height);
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
}

void EditorLayer::DrawImGui()
{
    ImGui::Begin("Settings");

    InputVector("Position: ", "###positioninput", &position);
    InputVector("Rotation: ", "###rotationinput", &rotation);
    InputVector("Scale: ", "###scaleinput", &scale);

    ImGui::Separator();

    ImGui::Text("Shine: ");
    ImGui::SameLine();
    ImGui::SliderFloat("###inputshine", &shine, 0.1f, 10);

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
        ImGui::InputFloat("###fontsize", &fontSize, 0.01f);

        ImGui::End();
    }


    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                window.Close();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Editor"))
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
    style.PopupRounding = 4.0f;
    style.PopupBorderSize = 1.0f;
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
