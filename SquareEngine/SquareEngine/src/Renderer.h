#pragma once
#include <glad/glad.h>
#include <ShaderProgram.h>
#include <Mesh.h>
#include <Texture2D.h>
#include <Camera.h>

namespace Square
{
	class Renderer
	{
	public:
		Renderer(int width, int height);

		void BeginFrame(float r, float g, float b);

		void RenderMesh(Mesh mesh, Texture2D texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	
		void SetLight(glm::vec3 lightPosition, glm::vec3 lightColor, float ambientLight);
	private:
		ShaderProgram program;

		glm::mat4 projection;
	};
}