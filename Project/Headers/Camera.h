#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	const float WIDTH = 800;
	const float HEIGHT = 800; //put somewhere else


	Camera();
	glm::vec3 position = glm::vec3(0,0,-20);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);

	//glm::vec3 rotation = glm::vec3(0, 0, 0);
	//view angle
	//far near planes
	//frustum
	
public:
	Camera(const Camera&) = delete;
	static Camera& GetInstance() {
		static Camera instance;
		return instance;
	}
	static glm::mat4 GetViewMatrix();
	static glm::mat4 GetProjectionMatrix();
	static void Translate(glm::vec3);
};



