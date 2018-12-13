#pragma once
#include <glew.h>
#include "Vertex.h"

class fRectangle
{
public:
	fRectangle();
	fRectangle(GLfloat ex, GLfloat why, GLfloat width, GLfloat height);
	fRectangle(Vertex a, Vertex b);
	fRectangle(int ex, int why, int width, int height);
	~fRectangle();
	void set(GLfloat ex, GLfloat why, GLfloat width, GLfloat height);
	Vertex getVertex(int v);
	GLfloat x;
	GLfloat y;
	GLfloat w;
	GLfloat h;
};

