#pragma once
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include "Color.h"
#include <cstdio>
#include "Camera.h"
#include <cmath>
#include <string>
#include "Physics.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void drawClipped(fRectangle clip) {};
	virtual void realign() {};

	virtual void setPosition(GLfloat x, GLfloat y);
	virtual void setPosition(Vertex v) { setPosition(v.x, v.y); }
	virtual void setPosition(int x, int y) { setPosition((GLfloat)x, (GLfloat)y); }

	virtual void offsetPosition(GLfloat x, GLfloat y);
	virtual void offsetPosition(Vertex v) { offsetPosition(v.x, v.y); }
	virtual void offsetPosition(int x, int y) { offsetPosition((GLfloat)x, (GLfloat)y); }

	virtual void setSize(GLfloat w, GLfloat h);
	virtual void setSize(Vertex v) { setSize(v.x, v.y); }
	virtual void setSize(int w, int h) { setSize((GLfloat)w, (GLfloat)h); }

	virtual void setRect(fRectangle r);

	fRectangle presence;
};

