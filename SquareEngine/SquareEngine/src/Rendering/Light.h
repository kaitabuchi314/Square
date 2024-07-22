#pragma once
#include <glm/glm.hpp>

namespace Square
{
	struct Light
	{
		glm::vec3 lightPosition;
		glm::vec3 lightColor;
		float ambientLight;
	};
}