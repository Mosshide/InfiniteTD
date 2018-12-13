#pragma once
#include "Entity.h"
#include "TextureBox.h"

class VBOCircle : public Entity
{
public:
	VBOCircle();
	VBOCircle(const VBOCircle& v);
	VBOCircle& operator=(const VBOCircle& v);
	~VBOCircle();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setRGBA(Color c);
	void setTexture(GLuint t);
	void setWireframe(bool b);
	void setUI(bool b);
	void initVBO();
	void freeVBO();
	void setCircle(GLfloat x, GLfloat y, GLfloat r);
	void setCircle(Vertex a, GLfloat r) { setCircle(a.x, a.y, r); }

	VertexData2D vertices[41];

protected:
	Shader *_shader;
	Color _color;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
	bool _isUI;
};

