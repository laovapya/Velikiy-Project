#include "Controller.h"
#include"DeltaTime.h"
#include<iostream>> //remove
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





    //--------

   /* if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        std::cout << " X " << instance.isXaxisEnabled << " Y " << instance.isYaxisEnabled << " Z " << instance.isZaxisEnabled << std::endl;
        std::cout << " Translation " << instance.isTranslating << " Rotation " << instance.isRotating << " Scaling " << instance.isScaling << std::endl;
    }*/
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
void Controller::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    Controller& instance = Controller::GetInstance();
    instance.mouseXoffset = xpos - instance.mouseLastX;
    instance.mouseYoffset = instance.mouseLastY - ypos; // reversed since y-coordinates range from bottom to top
    instance.mouseLastX = xpos;
    instance.mouseLastY = ypos;
    
    instance.mouseXoffset *= instance.mouseSensitivity;
    instance.mouseYoffset *= instance.mouseSensitivity;
   
    //std::cout << "x " << instance.mouseXoffset << " y " << instance.mouseYoffset << std::endl;


   /* GetInstance().mouseYaw += GetInstance().mouseXoffset;
    GetInstance().mousePitch += GetInstance().mouseYoffset;

    if (GetInstance().mousePitch > 89.0f)
        GetInstance().mousePitch = 89.0f;
    if (GetInstance().mousePitch < -89.0f)
        GetInstance().mousePitch = -89.0f;*/
}




//bool Controller::GetX() {
//	return GetInstance().isXaxisEnabled;
//}
//bool Controller::GetY() {
//	return GetInstance().isYaxisEnabled;
//}
//bool Controller::GetZ() {
//	return GetInstance().isZaxisEnabled;
//}
bool Controller::GetScaling() {
	return GetInstance().isScaling;
}
bool Controller::GetRotating() {
	return GetInstance().isRotating;
}
bool Controller::GetTranslating() {
	return GetInstance().isTranslating;
}
//bool Controller::GetUp() {
//	return GetInstance().isTransformingUp;
//}
//bool Controller::GetDown() {
//	return GetInstance().isTransformingDown;
//}

glm::vec3 Controller::GetTransformVector(Camera& camera) {
    glm::vec3 v(0, 0, 0);
    Controller& instance = Controller::GetInstance();

    glm::vec3 mouseVector = camera.GetRight() * instance.mouseXoffset + camera.GetUp() * instance.mouseYoffset;
    if (instance.isXaxisEnabled) 
        v += mouseVector.x * glm::vec3(1, 0, 0);
    
    if (instance.isYaxisEnabled) 
        v += mouseVector.y * glm::vec3(0, 1, 0);
    
    if (instance.isZaxisEnabled) 
        v += mouseVector.z * glm::vec3(0, 0, 1);
    
    return v  * -1.0f * instance.mouseSpeed;
}

void Controller::MoveCamera(GLFWwindow* window, Camera& camera) {
    
    Controller& instance = GetInstance();

    

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        camera.Pan(glm::vec3(GetInstance().mouseXoffset, GetInstance().mouseYoffset, 0) * DeltaTime::GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        camera.Pan(glm::vec3(0, 0, 1) * instance.zoomSpeed * DeltaTime::GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        camera.Pan(glm::vec3(0, 0, -1) * instance.zoomSpeed * DeltaTime::GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        camera.Orbit(-glm::vec3(GetInstance().mouseYoffset, GetInstance().mouseXoffset, 0) * DeltaTime::GetDeltaTime());
    }
}

void Controller::ResetMouse() {
    Controller& instance = GetInstance();

    instance.mouseXoffset = 0;
    instance.mouseYoffset = 0;
}

