#pragma once
#include"VAO.h"

class VertexData //remake this as a namespace? 
{
private:
	VertexData();
	int polygonAmount = 10; //1 to 10
	VAO cubeVAO;
	VAO coneVAO;
	VAO cylinderVAO; 
	VAO sphereVAO;
	
	void SetCubeVAO();
	void SetConeVAO(); 
	void SetCylinderVAO();
	void SetSphereVAO();

public:
	VertexData(const VertexData&) = delete;
	static VertexData& GetInstance() {
		static VertexData instance;
		return instance;
	}
	//static void Init(); //once on start
	///*float* GetCubeVertices();
	//float* GetCubeIndices();*/
	static VAO GetCubeVAO();
	static VAO GetConeVAO(); 
	static VAO GetCylinderVAO();
	static VAO GetSphereVAO();
};


