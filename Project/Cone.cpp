#include "Cone.h"
#include"VertexData.h"
Cone::Cone() {

}



void Cone::Bind() {
	VertexData::GetConeVAO().Bind();
}

int Cone::GetVertexCount() {
	return (360 / 10) * 3 * 2;
}