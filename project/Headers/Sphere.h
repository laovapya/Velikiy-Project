#pragma once
#include"Shape.h"
class Sphere : public Shape
{
	//using Shape::Shape;
private:


public:
	//virtual void Bind();
	
	Sphere();
	VAO GetVAO() override;
};