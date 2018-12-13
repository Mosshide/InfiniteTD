#pragma once
#include <glew.h>

enum ColorEnum
{
	black,
	white,
	red,
	green,
	blue,
	yellow,
	magenta,
	teal
};

struct ColorStruct
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

class Color
{
public:
	Color();
	Color(GLfloat rd, GLfloat gr, GLfloat bl, GLfloat al);
	Color(ColorEnum c, GLfloat sat = 1.f);
	~Color();
	ColorStruct get();

	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

