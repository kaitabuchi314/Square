#pragma once
#include <glad/glad.h>
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Square
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

		void Use(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
		void SetLightVariables(glm::vec3 lightPosition, glm::vec3 lightColor, float ambientLight);
	public:
		unsigned int shaderProgram;
	};
}