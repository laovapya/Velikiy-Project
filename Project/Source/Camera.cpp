#include "Camera.h"
#include"DeltaTime.h"

Camera::Camera() {

	position = glm::vec3(10, 8, -15);
	target = glm::vec3(0, 0, 0);


	projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);
	view = glm::lookAt(position, target, glm::vec3(0,1,0));

	//cameraRight = glm::vec3(1, 0, 0);
}
glm::mat4 Camera::GetViewMatrix() {
	return GetInstance().view;
}

glm::mat4 Camera::GetProjectionMatrix() {
	return GetInstance().projection;
}

void Camera::Pan(glm::vec3 v) {
	glm::vec3 cameraForward = glm::normalize(GetInstance().target - GetInstance().position);
	glm::vec3 cameraRight = glm::normalize(glm::cross(GetInstance().worldUp, cameraForward));
	glm::vec3 cameraUp = glm::normalize(glm::cross(cameraRight, cameraForward));
	float speed = GetInstance().panSpeed * abs(GetInstance().position.z) * GetInstance().zoomPanCoefficient;
	GetInstance().position += (cameraRight * v.x + cameraUp * v.y + cameraForward * v.z) * speed;
	GetInstance().target += (cameraRight * v.x + cameraUp * v.y) * speed;

	GetInstance().view = glm::lookAt(GetInstance().position, GetInstance().target, GetInstance().worldUp);
}

void Camera::Orbit(glm::vec3 angle) { //target here should be set to mouse projected on XZ plane 
	angle *= orbitSpeed;
	glm::vec4 v1 = glm::vec4(position.x, position.y, position.z, 1);
	glm::mat4 rotateWorldUp = glm::rotate(glm::mat4(1), angle.y, worldUp);
	
	v1 = rotateWorldUp * v1;

	//glm::vec3 temp = target - position;
	glm::vec3 cameraForward = target - position; 
	glm::vec3 cameraRight = glm::cross(worldUp, cameraForward);
	glm::mat4 rotateCameraRight = glm::rotate(glm::mat4(1), angle.x, cameraRight);
	glm::vec4 temp = rotateCameraRight * v1;
	if (abs(glm::normalize(temp).y) < 0.99)
		v1 = temp;
	
	

	position.x = v1.x;
	position.y = v1.y;
	position.z = v1.z;

	view = glm::lookAt(position, target, worldUp);
}