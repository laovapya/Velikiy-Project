#pragma once
#include"Shape.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"

#include<vector>
#define maxCount 32
class ObjectManager
{
private:
	int objectCount = 0;
	const int COUNT = maxCount;
	
	std::vector<Shape*> createdObjects;
	//std::vector<Shape*> selectedObjects;

	/*std::vector<Shape> storedObjects;
	int storedCount = 0;
	Shape* start = storedObjects.data();*/
	//Shape storedObjects[maxCount];
public:
	
	ObjectManager();
	~ObjectManager();

	int AddCube();
	int AddCone();
	int AddCylinder();
	int AddSphere();

	void AddObject(Shape* object);


	void RemoveObject(int id);
	void SelectObject(int id);
	void DeselectObject(int id);






	std::vector<Shape*> GetCreatedObjects();


};

