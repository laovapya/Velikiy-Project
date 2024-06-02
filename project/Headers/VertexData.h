#pragma once
#include"VAO.h"


#define cubeVertexCount 36
#define coneVertexCount 3 * 2 + 3 * 360 / 10 //polygonAmount max = 1 => min angle = 10
#define cylinderVertexCount 3 * 2 + 2 * 3 * 360 / 10

#define max_grid_size 2 * 3 * 2 * 250


#define coneIndexCount (360 / 10) * 3 * 2 //polygonAmount max = 1 => min angle = 10
#define cylinderIndexCount 4 * (360 / 10) * 3 //polygonAmount max = 1 => min angle = 10




class VertexData //remake this as a namespace? 
{
private:
	VertexData();
	int polygonAmount = 10; //1 to 10
	VAO cubeVAO;
	VAO coneVAO;
	VAO cylinderVAO; 
	VAO sphereVAO;


	float gridSpacing = 1;
	VAO grid;
	VAO axisX;
	VAO axisZ;
	
	void SetCubeVAO();
	void SetConeVAO(); 
	void SetCylinderVAO();
	void SetSphereVAO();

	void SetGridVAO();

public:
	static float degToRad;
	VertexData(const VertexData&) = delete;
	static VertexData& GetInstance() {
		static VertexData instance;
		return instance;
	}

	static VAO GetCubeVAO();
	static VAO GetConeVAO(); 
	static VAO GetCylinderVAO();
	static VAO GetSphereVAO();
	static VAO GetXVAO();
	static VAO GetZVAO();
	static VAO GetGridVAO();

	static int GetGridVertexCount();
	static int GetCubeIndexCount();
	static int GetConeIndexCount();
	static int GetCylinderIndexCount();
	static int GetSphereIndexCount();

};





