#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Square
{
	struct Camera
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::mat4 view;

		inline Camera(glm::vec3 p, glm::vec3 r) : position(p), rotation(r), view(1) {};
	};

	void UpdateCamera(Camera* cam, bool orbit);

	inline Camera* mainCamera;
	inline void SetMainCamera(Camera* cam) { mainCamera = cam; };
	inline Camera* GetMainCamera() { return mainCamera; };
}