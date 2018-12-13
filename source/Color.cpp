#include "Color.h"

Color::Color()
{
	r = 1.f;
	g = 1.f;
	b = 1.f;
	a = 1.f;
}

Color::Color(GLfloat rd, GLfloat gr, GLfloat bl, GLfloat al)
{
	r = rd;
	g = gr;
	b = bl;
	a = al;
}

Color::Color(ColorEnum c, GLfloat sat)
{
	r = 0.f;
	g = 0.f;
	b = 0.f;
	a = 1.f;

	switch (c)
	{
	case white:
		r = 1.f;
		g = 1.f;
		b = 1.f;
		break;
	case red:
		r = 1.f;
		break;
	case green:
		g = 1.f;
		break;
	case blue:
		b = 1.f;
		break;
	case yellow:
		r = 1.f;
		g = 1.f;
		break;
	case magenta:
		r = 1.f;
		b = 1.f;
		break;
	case teal:
		g = 1.f;
		b = 1.f;
		break;
	}

	GLfloat avg = (r + g + b) / 3;
	sat = 1.f - sat;

	r = r - (sat * (r - avg));
	g = g - (sat * (g - avg));
	b = b - (sat * (b - avg));
}

Color::~Color()
{
}

ColorStruct Color::get()
{
	ColorStruct s;
	s.r = r;
	s.g = g;
	s.b = b;
	s.a = a;

	return s;
}