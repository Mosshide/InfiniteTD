#pragma once
#include "Entity.h"
#include "Render.h"

class VBOText : public Entity
{
public:
	VBOText();
	VBOText(const VBOText& v);
	VBOText& operator=(const VBOText& v);
	~VBOText();
	void update() {};
	void draw();
	void drawClipped(fRectangle clip);
	void setPosition(GLfloat x, GLfloat y);
	void offsetPosition(GLfloat x, GLfloat y);
	void setSize(GLfloat w, GLfloat h);
	void setRect(fRectangle r);
	void setClip(fRectangle t);
	void setRGBA(Color c);
	void setRotation(float r);
	void setWireframe(bool b);
	void setUI(bool b);
	void initVBO();
	void freeVBO();
	void setText(std::string t);
	void setText(int n) { setText(std::to_string(n)); }

	VertexData2D vertices[4];
	std::string text;

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