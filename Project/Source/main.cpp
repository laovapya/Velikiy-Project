#include <iostream>

#include"Shape.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"

#include"ObjectManager.h"
#include"SceneRenderer.h"
#include"DeltaTime.h"

void DisplayKeys();


int main()
{
	DisplayKeys();
    Cube cube;
    Cone cone;
    Cylinder cyl;

    ObjectManager::GetInstance().AddObject(&cube);
    ObjectManager::GetInstance().AddObject(&cone);
    ObjectManager::GetInstance().AddObject(&cyl);

    cone.Move(glm::vec3(3, -2, 1));
    cyl.Move(glm::vec3(-6, 1, 4));

    ObjectManager::GetInstance().SelectObject(cube.GetID());
    //ObjectManager::GetInstance().SelectObject(cone.GetID());
    //ObjectManager::GetInstance().SelectObject(cyl.GetID());

    Scene scene;
    while (true) { //main loop
        DeltaTime::SetDeltaTime(glfwGetTime());
        scene.Update();
        if (scene.GetShouldClose())
            break;
    }
    return 0;
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
    std::cout << " Camera movement - Arrow keys" << std::endl;
    std::cout << " Zoom + -" << std::endl;
    std::cout << " Pan P + Mouse" << std::endl;
    std::cout << " Orbit O + Mouse" << std::endl;
}





