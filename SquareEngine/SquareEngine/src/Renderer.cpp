#include "Renderer.h"
#include <TextureShader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Light.h>

namespace Square
{
	Renderer::Renderer(int width, int height) :
		program(TextureShader::vertexShaderSource, TextureShader::fragmentShaderSource)
	{
		glViewport(0, 0, width, height);
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::BeginFrame(float r, float g, float b)
	{
		glClearColor(r / 255, g / 255, b / 255, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::RenderMesh(Mesh mesh, Texture2D texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
		model = glm::scale(model, scale);

		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		program.Use(model, GetMainCamera()->view, projection);

		BindTexture(texture, 0);

		mesh.Bind();
		
		glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);

		mesh.Unbind();

		UnbindTexture(texture);
	}

	void Renderer::SetLight(Light light)
	{
		program.SetLightVariables(light.lightPosition, light.lightColor, light.ambientLight);
	}
}