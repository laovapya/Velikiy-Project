#pragma once

#include"VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include"Controller.h"
#include"VertexData.h"



class Shape
{
protected:
	
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::vec3 normalColor = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 selectedColor = glm::vec3(0.0f, 0.3f, 0.65f);


	int id;
	static int idIncrement;
	//VAO vao;
	int vertexCount = 0;

	
public:
	enum Shapes {
		cube,
		cone,
		cylinder,
		sphere
	};

	Shape();


	int GetIndexCount();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	int GetID();

	void Translate(glm::vec3 v);
	void Rotate(glm::vec3 v); 
	void Scale(glm::vec3 v);

	void Translate(float* v);
	void Rotate(float*  v);
	void Scale(float* v);


	



	static glm::mat4 GetObjectMatrix(Shape* object);

	bool isSelected = false;

	glm::vec3 GetColor();

	Shapes GetShape();

	virtual VAO GetVAO() = 0;

protected:
	Shapes shape;
};