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


std::string GetFileContents(const char* fileName);

class Shader {
public:
	GLuint ID; //change to int
	int matrixLoc;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
	void SetMatrix(glm::mat4 matrix);
};



