#pragma once
#include <glew.h>

struct Vertex
{
	GLfloat x;
	GLfloat y;
};

struct TexCoord
{
	GLfloat s;
	GLfloat t;
};

struct VertexData2D
{
	Vertex position;
	TexCoord texCoord;
};