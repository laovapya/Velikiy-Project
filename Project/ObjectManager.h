#pragma once
#include"Shape.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"
#include<vector>

//defining max amount of objects in the scene
#define maxCount 32

//this class manages the container with all created objects.
//it has functionality to add, remove, select, deselect objects.
class ObjectManager
{
private:
	//current object amount
	int objectCount = 0;

	const int COUNT = maxCount;
	//The scene's objects container
	//This is a pointers container. The objects themselves are stored in the heap and deleted in destructor and RemoveObject()
	std::vector<Shape*> createdObjects;

public:
	ObjectManager();
	~ObjectManager();

	//Adding new objects
	int AddCube();
	int AddCone();
	int AddCylinder();
	int AddSphere();

	void AddObject(Shape* object);
	void RemoveObject(int id);

	//Selecting objects 
	void SelectObject(int id);
	void DeselectObject(int id);

	std::vector<Shape*> GetCreatedObjects();
};

