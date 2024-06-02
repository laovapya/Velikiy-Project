#pragma once

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h" //before glad

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include"Shader.h"



#include"Controller.h"

#define appName "Project"


class Window //object manager should be part of scene class. window init should be moved to window class. move imgui to window class as well 
{
private:

	
	static float width;
	static float height;
	static float aspectRatio;
	static glm::vec2 lowerLeft;
	static glm::vec2 upperRight;
	static float yDownOffset;
	static float XRightOffset;

	glm::vec4 color = glm::vec4(0.4f, 0.4f, 0.4f, 1); //grey 
	
	//float deltaTime = 0;
	//float lastFrame = 0;

	Shader shaderProgram; 
	GLFWwindow* window;
	

	bool shouldClose = 0;

	void InitGLFW();
	void CreateWindow();
	void InitGlad();
	void SetWindowParameters();
	void RegisterEvents();
	void UseShaders();

	void InitImGui();

	
public:

	Window();
	~Window();



	void EarlyUpdate();
	
	void LateUpdate();

	

	GLFWwindow* GetWindow();
	Shader GetShaderProgram();
	bool GetShouldClose();

	float GetWidth();
	float GetHeight();
	static float GetAspectRatio();


	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//void imgui();


	void SetUpDocking();

	ImVec2 GetWidget1Dimensions();
	ImVec2 GetWidget2Dimensions();
	ImVec2 GetWidget3Dimensions();
};


