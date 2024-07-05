#include "ShaderProgram.h"
#include <Debug.h>

namespace Square
{
    ShaderProgram::ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
    {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            Square::Log(std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n") + std::string(infoLog));
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            Square::Log(std::string("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n") + std::string(infoLog));
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            Square::Log(std::string("ERROR::SHADER::PROGRAM::LINKING_FAILED\n") + std::string(infoLog));
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(shaderProgram);
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
    }

    void ShaderProgram::Use(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
    {
        glUseProgram(shaderProgram);

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }

    void ShaderProgram::SetLightVariables(glm::vec3 lightPosition, glm::vec3 lightColor, float ambientLight)
    {
        glUseProgram(shaderProgram);

        unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPosition");
        unsigned int lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
        unsigned int ambientLightLoc = glGetUniformLocation(shaderProgram, "ambientLight");

        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPosition));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform1f(ambientLightLoc, ambientLight);
    }

    void ShaderProgram::SetMaterialProperties(glm::vec3 viewPosition, float shininess)
    {
        glUseProgram(shaderProgram);

        unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPosition");
        unsigned int shininessLoc = glGetUniformLocation(shaderProgram, "shininess");

        glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPosition));
        glUniform1f(shininessLoc, shininess);
    }
}
