#include "Cube.h"
#include"VertexData.h"

Cube::Cube() {
	
}

void Cube::Bind() {
	VertexData::GetCubeVAO().Bind();
}

int Cube::GetVertexCount() {
	return 36;
}