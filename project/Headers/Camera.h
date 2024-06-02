#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Scene's camera class
class Camera
{
private:
	//up orientation
	const glm::vec3 worldUp = glm::vec3(0, 1, 0);

	//base transform fields
	glm::vec3 position;
	glm::vec3 target;
	
	//view matrix is a transformation matrix applied to all objects. 
	//it is created based on camera's position and orientation.
	//multiplying each vertex in the scene by it creates the illusion of camera movement. 
	glm::mat4 view;

	float panSpeed = 10;
	float orbitSpeed = 10;

	//camera's coordinate system
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
public:
	Camera();
	

	glm::mat4 GetViewMatrix();

	//functionality to move the camera along its XY plane
	void Pan(glm::vec3);
	//functionality to orbit the camera around its target (starts at 0,0,0) 
	void Orbit(glm::vec3 angle);

	

	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetForward();
};



