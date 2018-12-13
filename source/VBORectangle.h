#pragma once
//#include "Entity.h"
#include "TextureBox.h"

class VBORectangle : public Entity
{
public:
	VBORectangle();
	VBORectangle(const VBORectangle& v);
	VBORectangle& operator=(const VBORectangle& v);
	~VBORectangle();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setPosition(GLfloat x, GLfloat y);
	void offsetPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat w, GLfloat h);
	void setRect(fRectangle r);
	void setClip(fRectangle *clip);
	void setClip(fRectangle clip) { setClip(&clip); };
	void setRGBA(Color c);
	void setRotation(float r);
	void setTexture(GLuint t);
	void setWireframe(bool b);
	void setUI(bool b);
	void initVBO();
	void freeVBO();

	VertexData2D vertices[4];

protected:
	Shader *_shader;
	Color _color;
	float _rotation;
	fRectangle _clip;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
	bool _isUI;
};