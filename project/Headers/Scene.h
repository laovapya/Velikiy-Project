#pragma once
#include"Shape.h"
#include"ObjectManager.h"
#include"Window.h"
class Scene
{
private:
	Window* window;
	ObjectManager manager;
	Camera camera;

	
public:
	Scene(Window* window);
	~Scene();
	void Update();
	void DrawGrid();



	Window* GetWindow();
	ObjectManager* GetObjectManager();

};



