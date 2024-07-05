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
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main()
{
    vec4 worldPosition = model * vec4(aPos, 1.0);
    gl_Position = projection * view * worldPosition;
    TexCoord = aTexCoord;
    
    surfaceNormal = mat3(transpose(inverse(model))) * normal;
    fragPos = vec3(worldPosition);
    toLightVector = lightPosition - fragPos;
}
)";

inline const char* fragmentShaderSource = // fragment shader
R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 surfaceNormal;
in vec3 toLightVector;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform float ambientLight;

void main()
{
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);
    
    float nDotL = max(dot(unitNormal, unitLightVector), 0.0);
    float brightness = max(nDotL, ambientLight);
    vec3 diffuse = brightness * lightColor;
    vec4 texColor = texture(ourTexture, TexCoord);
    FragColor = vec4(diffuse, 1.0) * texColor;
}
)";

    }
}