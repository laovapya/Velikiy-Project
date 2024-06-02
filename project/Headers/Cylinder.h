#pragma once
#include"Shape.h"
#include"VertexData.h"
class Cylinder : public Shape
{
	//using Shape::Shape;
public:
	Cylinder();
	VAO GetVAO() override;
	//virtual void Bind();
};

