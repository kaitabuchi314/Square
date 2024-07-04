#include <glm/glm.hpp>
#include <Square.h>

float positions[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f
};

float texCoords[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

unsigned int indices[] =
{
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
};

int main()
{
    Square::Window window = Square::Window(1296, 864, "Square Editor", true);

    Square::Camera camera = Square::Camera(glm::vec3(0, 0, -5), glm::vec3(0));
    Square::SetMainCamera(&camera);

    Square::Renderer renderer = Square::Renderer(window.width, window.height);

    Square::Mesh box = Square::Mesh(positions, texCoords, indices, sizeof(positions), sizeof(texCoords), sizeof(indices));

    Square::Texture2D boxTexture = Square::loadTexture("../Assets/box.png");
    Square::Texture2D concreteTexture = Square::loadTexture("../Assets/concrete.jpg");

    while (window)
    {
        if (Square::IsKeyDown(S_KEY_Q))
            camera.position.z += 0.001f;
        if (Square::IsKeyDown(S_KEY_E))
            camera.position.z -= 0.001f;
        if (Square::IsKeyDown(S_KEY_W))
            camera.rotation.x += 0.0005f;
        if (Square::IsKeyDown(S_KEY_S))
            camera.rotation.x -= 0.0005f;
        if (Square::IsKeyDown(S_KEY_A))
            camera.rotation.y += 0.0005f;
        if (Square::IsKeyDown(S_KEY_D))
            camera.rotation.y -= 0.0005f;

        Square::UpdateCamera(&camera, true);

        renderer.BeginFrame(35, 164, 234);

        renderer.RenderMesh(box, boxTexture, glm::vec3(0, 0.5f, 0), glm::vec3(window.GetTime()), glm::vec3(1));
        renderer.RenderMesh(box, boxTexture, glm::vec3(2, 2, 0), glm::vec3(window.GetTime()/2), glm::vec3(1));
        renderer.RenderMesh(box, boxTexture, glm::vec3(-3, 1, 1.5f), glm::vec3(window.GetTime()*1.5f), glm::vec3(1));

        renderer.RenderMesh(box, boxTexture, glm::vec3(3, 0, 1), glm::vec3(0), glm::vec3(1));
        renderer.RenderMesh(box, boxTexture, glm::vec3(-3.5f, 0, -2), glm::vec3(0), glm::vec3(1));

        renderer.RenderMesh(box, concreteTexture, glm::vec3(0, -1, 0), glm::vec3(0), glm::vec3(10, 1, 10));

        window.EndFrame();
    }
    
    box.Flush();
    window.Flush();

    return 0;
}
