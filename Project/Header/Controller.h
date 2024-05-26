#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include"Camera.h"
class Controller
{
private:
	bool isScaling = false;
	bool isRotating = false;
	bool isTranslating = false;



	bool isXaxisEnabled = false;
	bool isYaxisEnabled = false;
	bool isZaxisEnabled = false;

	

	bool isTransformingUp = false;
	bool isTransformingDown = false;

	float speed = 10;


	float mouseLastX = 400;
	float mouseLastY = 300;
	float mouseXoffset;
	float mouseYoffset; 
	float mouseYaw = 0;
	float mousePitch = 0;

	const float mouseSensitivity = 0.1f;



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
	static glm::vec3 GetTransformVector();


	

	static void MoveCamera(GLFWwindow* window);
	static void SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

};

