#include"VAO.h"
#include"EBO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}


void VAO::Link(VBO& VBO, EBO& EBO)
{
	Bind();
	VBO.Bind();
	EBO.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	VBO.Unbind();
	Unbind();
	EBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}