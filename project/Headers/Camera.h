#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	const float WIDTH = 800;
	const float HEIGHT = 800; //put somewhere else
	const glm::vec3 worldUp = glm::vec3(0, 1, 0);


	glm::vec3 position;
	glm::vec3 target;
	

	//glm::mat4 projection;
	glm::mat4 view;


	float panSpeed = 10;
	float orbitSpeed = 10;

	
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
public:
	Camera();
	glm::mat4 GetViewMatrix();
	//glm::mat4 GetProjectionMatrix();
	void Pan(glm::vec3);

	void Orbit(glm::vec3 angle);

	//void SetProjectionMatrix();


	glm::vec3 GetRight();
	glm::vec3 GetUp();
	glm::vec3 GetForward();
};



