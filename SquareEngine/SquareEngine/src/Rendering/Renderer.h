#pragma once
#include <glad/glad.h>
#include <ShaderProgram.h>
#include <Mesh.h>
#include <Texture2D.h>
#include <Camera.h>
#include <Light.h>

namespace Square
{
	class Renderer
	{
	public:
		Renderer(int width, int height);

		void BeginFrame(float r, float g, float b);

		void Resize(int width, int height);

		void RenderMesh(Mesh* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	
		void SetLight(Light light);
	private:
		ShaderProgram program;

		glm::mat4 projection;
	};

	inline Renderer* activeRenderer;
	inline Renderer* GetActiveRenderer() { return activeRenderer; };
	inline void SetActiveRenderer(Renderer* renderer) { activeRenderer = renderer; };
}