#include "Line.h"
#include"VertexData.h"

Line::Line() {

}

void Line::Bind() {
	VertexData::GetLineVAO().Bind();
}

int Line::GetVertexCount() {
	return 3 * 2;
}