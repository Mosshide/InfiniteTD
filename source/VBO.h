#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include "Color.h"
#include <cstdio>
#include "Render.h"
#include <cmath>

class VBO
{
public:
	VBO();
	VBO(const VBO& v);
	VBO& operator=(const VBO& rhs);
	~VBO();
	void draw();
	void drawClipped(fRectangle clip);
	void setNumVertices(int n);
	void setRGBA(Color c);
	void setTexture(GLuint t);
	void setWireframe(bool b);
	void setUI(bool b);
	void initVBO();
	void freeVBO();
	bool updateVBO();

	VertexData2D *vertices;
	
protected:
	Shader *_shader;
	Color _color;
	GLuint _vbo;
	GLuint _ibo;
	int _numVertices;

	GLuint _txr;
	bool _wf;
	bool _isUI;
	GLenum drawType;

	GLenum error;
};

