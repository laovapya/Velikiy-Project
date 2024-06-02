#include "Cone.h"
#include"VertexData.h"
Cone::Cone() : Shape() {
	
	vertexCount = VertexData::GetConeIndexCount();
	shape = cone;
}


VAO Cone::GetVAO() {
	return VertexData::GetConeVAO();
}

