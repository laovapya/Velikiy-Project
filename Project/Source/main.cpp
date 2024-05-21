#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Shader.h"

#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"

#include"ObjectManager.h"
#include"Controller.h"
#include"Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void DisplayKeys();


const float WIDTH = 800;
const float HEIGHT = 800;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    Controller::RegisterEvents(window); //after window is created
    DisplayKeys();
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // --------------------------------------------
    
    Shader shaderProgram("default.vert", "default.frag");
    shaderProgram.Activate();

    // ------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST); //to prevent rendering back vertices
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // -----------

    Cube cube;
    Cone cone;
    Cylinder cyl;

    ObjectManager::GetInstance().AddObject(&cube);
    //ObjectManager::GetInstance().AddObject(&cone);
    ObjectManager::GetInstance().AddObject(&cyl);

    //ObjectManager::GetInstance().SelectObject(cube.GetID());
    //ObjectManager::GetInstance().SelectObject(cone.GetID());
    ObjectManager::GetInstance().SelectObject(cyl.GetID());


    while (!glfwWindowShouldClose(window))
    {
        Controller::MoveCamera(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::vec3 v = Controller::GetTransformVector();

        for (Shape* object : ObjectManager::GetSelectedObjects()) {
            if (Controller::GetTranslating())
                object->Move(v);
            if (Controller::GetScaling())
                object->Scale(v);
            if (Controller::GetRotating())
                object->Rotate(v);
        }
        for (Shape* object : ObjectManager::GetCreatedObjects()) {
            shaderProgram.SetMatrix(Camera::GetProjectionMatrix() * Camera::GetViewMatrix() * Shape::GetObjectMatrix(object)); // projection * view * local * vector; 
            object->Bind();
            glDrawElements(GL_TRIANGLES, object->GetVertexCount(), GL_UNSIGNED_INT, 0);
        }
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // -------------------------------------
    shaderProgram.Delete();
    /*vao.Delete();
    vbo.Delete(); //replace this
    ebo.Delete();*/


    glfwTerminate();
    return 0;
}





// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



void DisplayKeys() {
    std::cout << " Translate G" << std::endl;
    std::cout << " Rotate R" << std::endl;
    std::cout << " Scale S" << std::endl;
    std::cout << " X Axis - X" << std::endl;
    std::cout << " Y Axis - Y" << std::endl;
    std::cout << " Z Axis - Z" << std::endl;
    std::cout << " UP 9 " << std::endl;
    std::cout << " DOWN 0 " << std::endl;
    std::cout << " RESET 1" << std::endl;
    std::cout << " Camera movement - WASD" << std::endl;
    std::cout << " Zoom + -" << std::endl;
}

