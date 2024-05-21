#include "Cylinder.h"
int Cylinder::GetVertexCount() {
	return 4 * (360 / 10) * 3;
}

void Cylinder::Bind() {
	VertexData::GetCylinderVAO().Bind();
}