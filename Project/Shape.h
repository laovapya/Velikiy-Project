#pragma once

#include"VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"Controller.h"

class Shape
{
protected:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	//float colorX;
	//float colorY;
	//float colorZ;

	int id;
	static int idIncrement;
public:
	Shape();
	//static VAO vao;
	virtual void Bind() = 0;
	virtual int GetVertexCount() = 0;

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	int GetID();

	void Move(glm::vec3 v);
	void Rotate(glm::vec3 v); 
	//void Rotate(glm::vec3 v, float angle) //do this 
	void Scale(glm::vec3 v);

	static glm::mat4 GetObjectMatrix(Shape* object);

};