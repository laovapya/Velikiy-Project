#include "Camera.h"
#include"DeltaTime.h"
#include <Glm.h>
Camera::Camera() {

	position = vec3(10, 8, -15);
	target = vec3(0, 0, 0);


	projection = perspective(radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);
	view = lookAt(position, target, vec3(0,1,0));

	//cameraRight = glm::vec3(1, 0, 0);
}
mat4 Camera::GetViewMatrix() {
	return GetInstance().view;
}

mat4 Camera::GetProjectionMatrix() {
	return GetInstance().projection;
}

void Camera::Pan(vec3 v) {
	vec3 cameraForward = normalize(GetInstance().target - GetInstance().position);
	vec3 cameraRight = normalize(cross(GetInstance().worldUp, cameraForward));
	vec3 cameraUp = normalize(cross(cameraRight, cameraForward));
	float speed = GetInstance().panSpeed * abs(GetInstance().position.z) * GetInstance().zoomPanCoefficient;
	GetInstance().position += (cameraRight * v.x + cameraUp * v.y + cameraForward * v.z) * speed;
	GetInstance().target += (cameraRight * v.x + cameraUp * v.y) * speed;

	GetInstance().view = glm::lookAt(GetInstance().position, GetInstance().target, GetInstance().worldUp);
}

void Camera::Orbit(vec3 angle) { //target here should be set to mouse projected on XZ plane 
	angle *= orbitSpeed;
	vec4 v1 = vec4(position.x, position.y, position.z, 1);
	mat4 rotateWorldUp = rotate(mat4(1), angle.y, worldUp);
	
	v1 = rotateWorldUp * v1;

	//glm::vec3 temp = target - position;
	vec3 cameraForward = target - position; 
	vec3 cameraRight = glm::cross(worldUp, cameraForward);
	mat4 rotateCameraRight = glm::rotate(glm::mat4(1), angle.x, cameraRight);
	vec4 temp = rotateCameraRight * v1;
	if (abs(normalize(temp).y) < 0.99)
		v1 = temp;
	
	

	position.x = v1.x;
	position.y = v1.y;
	position.z = v1.z;

	view = lookAt(position, target, worldUp);
}
