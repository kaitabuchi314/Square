#include "Camera.h"

void Square::UpdateCamera(Camera* cam, bool orbit)
{
	glm::mat4 model;

	if (orbit)
	{
		model = glm::translate(glm::mat4(1.0f), cam->position);
		model = glm::rotate(model, cam->rotation.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, cam->rotation.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, cam->rotation.z, glm::vec3(0, 0, 1));
	}
	else
	{
		model = glm::rotate(glm::mat4(1.0f), cam->rotation.x, glm::vec3(1, 0, 0));
		model = glm::rotate(model, cam->rotation.y, glm::vec3(0, 1, 0));
		model = glm::rotate(model, cam->rotation.z, glm::vec3(0, 0, 1));
		model = glm::translate(model, cam->position);
	}

	cam->view = model;
}