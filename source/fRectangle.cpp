#include "fRectangle.h"

fRectangle::fRectangle()
{
	x = 0.f;
	y = 0.f;
	w = 1.f;
	h = 1.f;
}

fRectangle::fRectangle(GLfloat ex, GLfloat why, GLfloat width, GLfloat height)
{
	x = ex;
	y = why;
	w = width;
	h = height;
}

fRectangle::fRectangle(Vertex a, Vertex b)
{
	x = a.x;
	y = a.y;
	w = b.x;
	h = b.y;
}

fRectangle::fRectangle(int ex, int why, int width, int height)
{
	x = (float)ex;
	y = (float)why;
	w = (float)width;
	h = (float)height;
}

fRectangle::~fRectangle()
{
}

void fRectangle::set(GLfloat ex, GLfloat why, GLfloat width, GLfloat height)
{
	x = ex;
	y = why;
	w = width;
	h = height;
}

Vertex fRectangle::getVertex(int v)
{
	Vertex r;
	r.x = x;
	r.y = y;
	if (v == 1 || v == 2) r.x += w;
	if (v == 2 || v == 3) r.y += h;
	
	return r;
}