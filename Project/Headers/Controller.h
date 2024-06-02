#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Glm.h>
#include"Camera.h"
class Controller
{
private:
	bool isScaling = false;
	bool isRotating = false;
	bool isTranslating = false;

	static void SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods);


	bool isXaxisEnabled = false;
	bool isYaxisEnabled = false;
	bool isZaxisEnabled = false;

	

	bool isTransformingUp = false;
	bool isTransformingDown = false;

	float delta = 0.02f;

	Controller();
public:
	Controller(const Controller&) = delete;
	static Controller& GetInstance() {
		static Controller instance;
		return instance;
	}

	static bool GetX();
	static bool GetY();
	static bool GetZ();
	static bool GetScaling();
	static bool GetRotating();
	static bool GetTranslating();
	static bool GetUp();
	static bool GetDown();
	static vec3 GetTransformVector();


	static void RegisterEvents(GLFWwindow* window) {
		glfwSetKeyCallback(window, SwitchState);
	}

	static void MoveCamera(GLFWwindow* window);
};

