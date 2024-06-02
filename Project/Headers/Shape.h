#pragma once

#include"VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Glm.h>
#include"Controller.h"

class Shape
{
protected:

	vec3 position = vec3(0, 0, 0);
	vec3 rotation = vec3(0, 0, 0);
	vec3 scale = vec3(1, 1, 1);

	//float colorX;
	//float colorY;
	//float colorZ;

	int id;
	static int idIncrement;
public:
	Shape();
	static VAO vao;
	virtual void Bind() = 0;
	virtual int GetVertexCount() = 0;

	vec3 GetPosition();
	vec3 GetRotation();
	vec3 GetScale();

	int GetID();

	void Move(vec3 v);
	void Rotate(vec3 v); 
	//void Rotate(vec3 v, float angle) //do this 
	void Scale(vec3 v);

	static mat4 GetObjectMatrix(Shape* object);

};
