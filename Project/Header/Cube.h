#pragma once
#include"Shape.h"
class Cube : public Shape
{
	using Shape::Shape;
private:
	

public:
	virtual void Bind();
	virtual int GetVertexCount();
	Cube();
	
};
