#pragma once
#include"Shape.h"
class Cone : public Shape
{
	using Shape::Shape;
private:


public:
	virtual void Bind();
	virtual int GetVertexCount();
	Cone();

};

