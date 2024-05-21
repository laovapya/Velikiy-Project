#pragma once
#include"Shape.h"
#include"VertexData.h"
class Cylinder : public Shape
{
	using Shape::Shape;
public:

	int GetVertexCount();
	virtual void Bind();
};

