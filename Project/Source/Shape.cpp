#include "Shape.h"
glm::vec3 Shape::GetPosition() {
	return position;
}
glm::vec3 Shape::GetRotation() {
	return rotation;
}
glm::vec3 Shape::GetScale() {
	return scale;
}

Shape::Shape() {
	id = idIncrement++;
}
int Shape::GetID() {
	return id;
}
int Shape::idIncrement = 0;

void Shape::Move(glm::vec3 v) {
	position += v;
}
void Shape::Rotate(glm::vec3 v) {
	rotation += v;
}
//void Shape::Rotate(glm::vec3 v, float angle) { // do this
//	//
//}
void Shape::Scale(glm::vec3 v) {
	scale += v;
}

glm::mat4 Shape::GetObjectMatrix(Shape* object) { //move to Shape
	glm::mat4 id = glm::mat4(1.0f);

	id = glm::translate(id, object->GetPosition());

	id = glm::rotate(id, object->GetRotation().x, glm::vec3(1, 0, 0)); //! change to quaternion 
	id = glm::rotate(id, object->GetRotation().y, glm::vec3(0, 1, 0)); 
	id = glm::rotate(id, object->GetRotation().z, glm::vec3(0, 0, 1)); 

	id = glm::scale(id, object->GetScale());
	return id;
}

//translate * rotate * scale * vector 