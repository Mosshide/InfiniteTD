#pragma once
#include "Entity.h"

class VBOTriangle : public Entity
{
public:
	VBOTriangle();
	VBOTriangle(const VBOTriangle& v);
	VBOTriangle& operator=(const VBOTriangle& v);
	~VBOTriangle();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setRGBA(Color c);
	void setWireframe(bool b);
	void setUI(bool b);
	void initVBO();
	void freeVBO();
	void setTriangle(Vertex a, Vertex b, Vertex c);

	VertexData2D vertices[3];

protected:
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
	bool _isUI;
};

