#pragma once
#include<glad/glad.h>
#include"VBO.h"
#include"EBO.h"

class VAO
{
public:

	GLuint ID;

	VAO();


	void Link(VBO& VBO, EBO& EBO);

	void Link(VBO& VBO);

	void Bind();

	void Unbind();

	void Delete();
};

