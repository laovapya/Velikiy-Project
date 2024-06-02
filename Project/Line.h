#pragma once
#include"Shape.h"
class Line : public Shape
{
	using Shape::Shape;
private:


public:
	virtual void Bind();
	virtual int GetVertexCount();
	Line();

};