#pragma once
#include"Scene.h"

#include"iostream"

#define maxObjectCount 32


struct ListedObject {

public:
	bool isSelected;
	int id;
	std::string name;
	ListedObject() {
		isSelected = false;
		id = -1;
		name = "null";
	}
	ListedObject(bool isSelected, int ID, std::string name) {
		this->isSelected = isSelected;
		this->id = ID;
		this->name = name;
	}
};



class UI
{
private:
	Scene* scene;

	//std::string items[maxObjectCount];

	ListedObject items[maxObjectCount];


	int currentCount = 0;

	int cubeCount = 0;
	int coneCount = 0;
	int cylinderCount = 0;
	int sphereCount = 0;

	float positionBuffer[3] = { 0, 0, 0 };
	float rotationBuffer[3] = { 0, 0, 0 };
	float scaleBuffer[3] = { 0, 0, 0 };

	void AddItem(ListedObject object);
	void ReInitItems();
public:
	UI(Scene* scene);

	void DrawObjectMenu();
	
	void DrawObjectList();

	void DrawTransformMenu();



};





