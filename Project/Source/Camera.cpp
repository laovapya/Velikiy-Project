#include "Camera.h"

Camera::Camera() {

}
glm::mat4 Camera::GetViewMatrix() {
	glm::mat4 id = glm::mat4();
	id = glm::translate(id, GetInstance().position);
	return id;
}

glm::mat4 Camera::GetProjectionMatrix() {
	return GetInstance().projection;
}


void Camera::Translate(glm::vec3 v) {
	GetInstance().position += v;
}