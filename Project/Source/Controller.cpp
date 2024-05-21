#include "Controller.h"
#include<iostream>; //remove this 

Controller::Controller() {

}

void Controller::SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods) {

    Controller& instance = Controller::GetInstance();
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        instance.isXaxisEnabled = !instance.isXaxisEnabled;
    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        instance.isYaxisEnabled = !instance.isYaxisEnabled;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        instance.isZaxisEnabled = !instance.isZaxisEnabled;

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        instance.isScaling = !instance.isScaling;
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        instance.isRotating = !instance.isRotating;
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
        instance.isTranslating = !instance.isTranslating;

    //-------------

    if (key == GLFW_KEY_9 && action == GLFW_PRESS)
        instance.isTransformingUp = true;
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        instance.isTransformingDown = true;

    if (key == GLFW_KEY_9 && action == GLFW_RELEASE)
        instance.isTransformingUp = false;
    if (key == GLFW_KEY_0 && action == GLFW_RELEASE)
        instance.isTransformingDown = false;

    //--------

    if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        std::cout << " X " << instance.isXaxisEnabled << " Y " << instance.isYaxisEnabled << " Z " << instance.isZaxisEnabled << std::endl;
        std::cout << " Translation " << instance.isTranslating << " Rotation " << instance.isRotating << " Scaling " << instance.isScaling << std::endl;
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        instance.isXaxisEnabled = false;
        instance.isYaxisEnabled = false;
        instance.isZaxisEnabled = false;

        instance.isTranslating = false;
        instance.isScaling = false;
        instance.isRotating = false;
    }

    //--------------------

    
}





bool Controller::GetX() {
	return GetInstance().isXaxisEnabled;
}
bool Controller::GetY() {
	return GetInstance().isYaxisEnabled;
}
bool Controller::GetZ() {
	return GetInstance().isZaxisEnabled;
}
bool Controller::GetScaling() {
	return GetInstance().isScaling;
}
bool Controller::GetRotating() {
	return GetInstance().isRotating;
}
bool Controller::GetTranslating() {
	return GetInstance().isTranslating;
}
bool Controller::GetUp() {
	return GetInstance().isTransformingUp;
}
bool Controller::GetDown() {
	return GetInstance().isTransformingDown;
}

glm::vec3 Controller::GetTransformVector() {
    int multiplier = 1;
    glm::vec3 v(0, 0, 0);

    if (GetInstance().isTransformingUp)
        ;
    else if (GetInstance().isTransformingDown)
        multiplier = -1;
    else
        return v;
  
    if (GetInstance().isXaxisEnabled)
        v += glm::vec3(1, 0, 0);
    if (GetInstance().isYaxisEnabled)
        v += glm::vec3(0, 1, 0);
    if (GetInstance().isZaxisEnabled)
        v += glm::vec3(0, 0, 1);
    v *= multiplier;

    return v * GetInstance().delta;
}

void Controller::MoveCamera(GLFWwindow* window) {
    Controller& instance = GetInstance();
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        Camera::Translate(glm::vec3(-1, 0, 0) * instance.delta);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        Camera::Translate(glm::vec3(1, 0, 0) * instance.delta);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        Camera::Translate(glm::vec3(0, 1, 0) * instance.delta);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        Camera::Translate(glm::vec3(0, -1, 0) * instance.delta);
    }
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        Camera::Translate(glm::vec3(0, 0, 1) * instance.delta);
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        Camera::Translate(glm::vec3(0, 0, -1) * instance.delta);
    }
}

