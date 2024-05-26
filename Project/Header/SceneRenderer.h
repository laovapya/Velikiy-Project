#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include"Shader.h"

#include"ObjectManager.h"
#include"Controller.h"
#include"Camera.h"
class Scene
{
private:

	

	//float deltaTime = 0;
	//float lastFrame = 0;

	Shader shaderProgram; 
	GLFWwindow* window;
	

	const float WIDTH = 800;
	const float HEIGHT = 800;

	bool shouldClose = 0;

	void InitGLFW();
	void CreateWindow();
	void InitGlad();
	void SetWindowParameters();
	void RegisterEvents();
	void UseShaders();




public:

	Scene();
	//~Scene();

	void Update();
	void DrawGrid();
	
	//void SetDeltaTime();
	//float GetDeltaTime();
	GLFWwindow* GetWindow();
	Shader GetShaderProgram();
	bool GetShouldClose();
	

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};


