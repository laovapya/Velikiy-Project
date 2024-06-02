#pragma once
#include"Shape.h"
class Sphere : public Shape
{
	using Shape::Shape;
private:


public:
	virtual void Bind();
	virtual int GetVertexCount();
	Sphere();

};