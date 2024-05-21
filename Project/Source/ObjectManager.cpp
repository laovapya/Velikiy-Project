#include"ObjectManager.h"
ObjectManager::ObjectManager() {

}


void ObjectManager::AddObject(Shape* object) {
	if (objectCount > COUNT - 1) {
		//throw error
		return;
	}
	createdObjects.push_back(object);
	objectCount++;
}
void ObjectManager::RemoveObject(int id) {
	auto it = createdObjects.begin();
	for (Shape* object : createdObjects) {
		it++;
		if (object->GetID() == id) {
			//delete object here if nesessary
			createdObjects.erase(it);
			return;
		}
	}
	//throw error couldnt find object to erase
}
void ObjectManager::SelectObject(int id) {
	for (Shape* object : createdObjects) {
		if (object->GetID() == id) {
			selectedObjects.push_back(object);
			return;
		}
	}
	//throw error couldnt find object to push back
}

void ObjectManager::DeselectObject(int id) {
	auto it = selectedObjects.begin();
	for (Shape* object : selectedObjects) {
		it++;
		if (object->GetID() == id) {
			selectedObjects.erase(it);
			return;
		}
	}
	//throw error couldnt find object to erase
}

std::vector<Shape*> ObjectManager::GetCreatedObjects() {
	return GetInstance().createdObjects;
}
std::vector<Shape*> ObjectManager::GetSelectedObjects() {
	return GetInstance().selectedObjects;
}

