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
//Shape::Shape(const Shape& s) {
//	this->position = s.position;
//	this->rotation = s.rotation;
//	this->scale =	 s.scale;
//
//	this->id = s.id;
//	this->vao = s.vao;
//	this->vertexCount = s.vertexCount;
//
//}
int Shape::GetID() {
	return id;
}
int Shape::idIncrement = 0;

void Shape::Translate(glm::vec3 v) {
	position += v;
}
void Shape::Rotate(glm::vec3 v) {
	rotation += v;
}
void Shape::Scale(glm::vec3 v) {
	float max = v.x;
	
	if (v.y > max)
		max = v.y;
	if (v.z > max)
		max = v.z;

	float min = v.x;
	if (v.y < min)
		min = v.y;
	if (v.z < min)
		min = v.z;
	float val = max;
	if (abs(min) > max)
		val = min;



	if (v.x != 0)
		v.x = val;
	if (v.y != 0)
		v.y = val;
	if (v.z != 0)
		v.z = val;


	scale += v;
	if (scale.x < 0)
		scale.x = 0;
	if (scale.y < 0)
		scale.y = 0;
	if (scale.z < 0)
		scale.z = 0;
}

void Shape::Translate(float* v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
	Translate(v1);
}
void Shape::Rotate(float* v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]) * VertexData::degToRad;
	Rotate(v1);
}
void Shape::Scale(float* v) {
	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
	Scale(v1);
}

//void Shape::SetPosition(glm::vec3 v) {
//	position = v;
//}
//void Shape::SetRotation(glm::vec3 v) {
//	v *= VertexData::degToRad;
//	rotation = v;
//}
//void Shape::SetScale(glm::vec3 v) {
//	scale = v;
//}
//
//void Shape::SetPosition(float* v) {
//	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
//	position = v1;
//}
//void Shape::SetRotation(float* v) {
//	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
//	v1 *= VertexData::degToRad;
//	rotation = v1;
//}
//void Shape::SetScale(float* v) {
//	glm::vec3 v1 = glm::vec3(v[0], v[1], v[2]);
//	scale = v1;
//}


glm::mat4 Shape::GetObjectMatrix(Shape* object) { //move to Shape
	glm::mat4 id = glm::mat4(1.0f);

	id = glm::translate(id, object->GetPosition());

	id = glm::rotate(id, object->GetRotation().x, glm::vec3(1, 0, 0)); //! change to quaternion 
	id = glm::rotate(id, object->GetRotation().y, glm::vec3(0, 1, 0)); 
	id = glm::rotate(id, object->GetRotation().z, glm::vec3(0, 0, 1)); 

	id = glm::scale(id, object->GetScale());
	return id;
}

int Shape::GetIndexCount() {
	return indexCount;
}

glm::vec3 Shape::GetColor() {
	if (isSelected)
		return selectedColor;
	return normalColor;
}
Shape::Shapes Shape::GetShape() {
	return shape;
}

