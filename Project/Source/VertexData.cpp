#include "VertexData.h"
#include"VBO.h"
#include"EBO.h"
#include"math.h"

const double pi = 3.14159265358979323846;
float DegToRad(float angle) {
	return angle * pi / 180;
}
//float  VertexData::cubeVertices[36];
//float  VertexData::cubeIndices[12];
//VAO  VertexData::cubeVAO;
//const int VertexData::CUBE_VERTEX_COUNT = 36;
//const int VertexData::CUBE_INDEX_COUNT = 12;
VertexData::VertexData() {
	if (polygonAmount < 5) polygonAmount = 5;
	if (polygonAmount > 40) polygonAmount = 40;
	SetCubeVAO();
	SetConeVAO();
	SetCylinderVAO();
	SetSphereVAO();
	SetGridVAO();
}
VAO VertexData::GetCubeVAO() {
	return GetInstance().cubeVAO;
}
VAO VertexData::GetConeVAO() {
	return GetInstance().coneVAO;
}
VAO VertexData::GetCylinderVAO() {
	return GetInstance().cylinderVAO;
}
VAO VertexData::GetSphereVAO() {
	return GetInstance().sphereVAO;
}
void VertexData::SetCubeVAO() {
	float vertices[] = {
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
	};
	int indices[] = {
		0, 1, 2,
		1, 3, 4,
		5, 6, 3,
		7, 3, 6,
		2, 4, 7,
		0, 7, 6,
		0, 5, 1,
		1, 5, 3,
		5, 0, 6,
		7, 4, 3,
		2, 1, 4,
		0, 2, 7
	};

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	cubeVAO.Link(VBO1, EBO1);
}

void VertexData::SetConeVAO() {
	int angle = (int)(360 / (360 / (100 / polygonAmount))); 
	float vertices[3 * 2 + 3 * 360 / 10]; //polygonAmount max = 1 => min angle = 10
	int triangleCount = 360 / angle;
	vertices[0] = 0;
	vertices[1] = 0.5f;
	vertices[2] = 0;
	vertices[3] = 0;
	vertices[4] = -0.5f;
	vertices[5] = 0;
	for (int i = 0, j = 6; i < 360; i += angle, j += 3) {
		vertices[j] = 0.5f * cos(DegToRad(i));
		vertices[j + 1] = -0.5f;
		vertices[j + 2] = 0.5f * sin(DegToRad(i));
	}
	int indices[(360 / 10) * 3 * 2]; //polygonAmount max = 1 => min angle = 10
	int size = triangleCount * 3 * 2;
	for (int i = 0, j = 2; i < size / 2; ++i) {
		if (i % 3 == 0) {
			indices[i] = 0;
			indices[i + size / 2] = 1;
			--j;
			continue;
		}
		++j;
		if (i == size / 2 - 1) j = 2;
		indices[i] = j;
		indices[i + size / 2] = j;
	}

	VBO VBO2(vertices, sizeof(vertices));
	EBO EBO2(indices, sizeof(indices));
	coneVAO.Link(VBO2, EBO2);
}

void VertexData::SetCylinderVAO() {
	int angle = (int)(360 / (360 / (100 / polygonAmount))); 
	float vertices[3 * 2 + 2 * 3 * 360 / 10]; //polygonAmount max = 1 => min angle = 10
	int planeTriangleCount = 360 / angle;
	vertices[0] = 0;
	vertices[1] = -0.5f;
	vertices[2] = 0;
	vertices[3] = 0;
	vertices[4] = 0.5f;
	vertices[5] = 0;
	for (int i = 0, j = 6; i < 360; i += angle, j += 3) {
		vertices[j] = 0.5f * cos(DegToRad(i));
		vertices[j + 1] = -0.5f;
		vertices[j + 2] = 0.5f * sin(DegToRad(i));
		vertices[j +	 planeTriangleCount * 3] = vertices[j];
		vertices[j + 1 + planeTriangleCount * 3] = 0.5f;
		vertices[j + 2 + planeTriangleCount * 3] = vertices[j + 2];
	}

	//planes
	int indices[4 * (360 / 10) * 3]; //polygonAmount max = 1 => min angle = 10
	int size = planeTriangleCount * 3 * 2;
	for (int i = 0, j = 2; i < size / 2; ++i) {
		if (i % 3 == 0) {
			indices[i] = 0;
			indices[i + size / 2] = 1;
			--j;
			continue;
		}
		++j;
		if (i == size / 2 - 1) j = 2;
		indices[i] = j ;
		indices[i + size / 2] = j + planeTriangleCount;
	}
	
	//sides 
	for (int i = size, j = 2; i < size * 1.5; i+=3, ++j) {
		indices[i] = j;
		indices[i + 1] = j + 1;
		indices[i + 2] = j + planeTriangleCount;
	}
	for (int i = size * 1.5, j = 2 + planeTriangleCount; i < size * 2 - 3; i += 3, ++j) {
		indices[i] = j;
		indices[i + 1] = j + 1;
		indices[i + 2] = j - planeTriangleCount + 1;
	}


	VBO VBO2(vertices, sizeof(vertices));
	EBO EBO2(indices, sizeof(indices));
	cylinderVAO.Link(VBO2, EBO2);
}


void VertexData::SetSphereVAO()
{

}

#define max_grid_size 2 * 3 * 2 * 250

void VertexData::SetGridVAO() { //move to another class
	const float length = 9999;
	float vertices1[] = {
		-length, 0, 0,
		length, 0, 0
	};
	VBO vbo1(vertices1, sizeof(vertices1));
	axisX.Link(vbo1);

	float vertices2[] = {
		0, 0, -length,
		0, 0, length
	};
	VBO vbo2(vertices2, sizeof(vertices2));
	axisZ.Link(vbo2);

	float spacing = gridSpacing;
	float amount = max_grid_size;

	if (amount > max_grid_size)
		amount = max_grid_size;

	float vertices3[max_grid_size]; //max amount 
	for (int i = 0; i < amount / 2; i += 6) {
		vertices3[i] = -length;
		vertices3[i + 1] = 0;
		vertices3[i + 2] = spacing * (i / 6 - 125);

		vertices3[i + 3] = length;
		vertices3[i + 4] = 0;
		vertices3[i + 5] = spacing * (i / 6 - 125);
	}
	for (int i = amount / 2; i < amount; i += 6) {
		vertices3[i] = spacing * ((i - amount / 2) / 6 - 125);
		vertices3[i + 1] = 0;
		vertices3[i + 2] = -length;

		vertices3[i + 3] = spacing * ((i - amount / 2) / 6 - 125);
		vertices3[i + 4] = 0;
		vertices3[i + 5] = length;
	}
	VBO vbo3(vertices3, sizeof(vertices3));
	grid.Link(vbo3);
}

VAO VertexData::GetXVAO() {
	return GetInstance().axisX;
}
VAO VertexData::GetZVAO() {
	return GetInstance().axisZ;
}
VAO VertexData::GetGridVAO() {
	return GetInstance().grid;
}
int VertexData::GetGridSize() {
	return max_grid_size;
}