#pragma once
#include<glad/glad.h>
#include<string>
#include<fstream>>
#include<sstream>
#include<iostream>
#include<cerrno>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Shader {
public:
	GLuint ID; //change to int
	int matrixLoc;
	int colorLoc;
	int alphaLoc;
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
	void SetMatrix(glm::mat4 matrix);
	void SetColor(glm::vec3 color);
	void SetAlpha(float alpha);
};



