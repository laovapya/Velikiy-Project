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

	Camera();
	glm::vec3 position;
	glm::vec3 target;
	

	glm::mat4 projection;
	glm::mat4 view;

	//glm::vec3 cameraRight;

	//glm::vec3 rotation = glm::vec3(0, 0, 0);
	//view angle
	//far near planes
	//frustum
	float panSpeed = 10;
	float orbitSpeed = 10;

	const float zoomPanCoefficient = 0.125f;
	
public:
	Camera(const Camera&) = delete;
	static Camera& GetInstance() {
		static Camera instance;
		return instance;
	}
	static glm::mat4 GetViewMatrix();
	static glm::mat4 GetProjectionMatrix();
	static void Pan(glm::vec3);

	void Orbit(glm::vec3 angle);

};



