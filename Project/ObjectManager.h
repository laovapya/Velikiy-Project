#pragma once
#include"Shape.h"
#include<vector>
class ObjectManager 
{
private:
	int objectCount = 0;
	const int COUNT = 32;
	std::vector<Shape*> createdObjects;
	std::vector<Shape*> selectedObjects;
	ObjectManager();
public:
	ObjectManager(const ObjectManager&) = delete;
	static ObjectManager& GetInstance() {
		static ObjectManager instance;
		return instance;
	}


	void AddObject(Shape* object); //make these statics?
	void RemoveObject(int id);
	void SelectObject(int id);
	void DeselectObject(int id);

	static std::vector<Shape*> GetCreatedObjects();
	static std::vector<Shape*> GetSelectedObjects();

};

