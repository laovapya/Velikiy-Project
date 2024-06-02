#pragma once
#include"Scene.h"

#include"iostream"

#define maxObjectCount 32






class UI
{
private:
	struct ListedObject {

	public:
		bool isSelected;
		int id;
		std::string name;
		Shape::Shapes shape;
		ListedObject() {
			isSelected = false;
			id = -1;
			name = "null";
			shape = Shape::Shapes::cube;
		}
		ListedObject(bool isSelected, int ID, std::string name, Shape::Shapes shape) {
			this->isSelected = isSelected;
			this->id = ID;
			this->name = name;
			this->shape = shape;
		}
	};


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

	int objectListMenuHeight = maxObjectCount;

	void AddItem(ListedObject& item);
	void ReInitItems();

	void DeleteItems();
public:
	UI(Scene* scene);

	void DrawObjectMenu();
	
	void DrawObjectList();

	void DrawTransformMenu();



};





