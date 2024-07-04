#pragma once

namespace Square
{
    namespace TextureShader
    {
        inline const char* vertexShaderSource = // vertex shader
        R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 2) in vec2 aTexCoord;

        out vec2 TexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            TexCoord = aTexCoord;
        }
        )";

        inline const char* fragmentShaderSource = // fragment shader
        R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;

        uniform sampler2D ourTexture;

        void main()
        {
            FragColor = texture(ourTexture, TexCoord);
        }
        )";
    }
}