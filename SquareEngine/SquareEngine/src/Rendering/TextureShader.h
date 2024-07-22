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
layout (location = 3) in vec3 normal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoord = aTexCoord;
}
)";

inline const char* fragmentShaderSource = // fragment shader
R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float ambientLight;
uniform vec3 viewPosition;
uniform float shininess;

void main()
{
    // Ambient
    vec3 ambient = ambientLight * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * vec3(texture(ourTexture, TexCoord));
    FragColor = vec4(result, 1.0);
}
)";

    }
}