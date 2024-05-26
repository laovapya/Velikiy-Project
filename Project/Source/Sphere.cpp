#include "Sphere.h"
#include"VertexData.h"

Sphere::Sphere() {

}

void Sphere::Bind() {
	VertexData::GetSphereVAO().Bind();
}

int Sphere::GetVertexCount() {
	return 3 * 2 + (360 / 10) * 3 * 360 / 10;
}