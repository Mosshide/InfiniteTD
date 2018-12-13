#include "Background.h"

Background::Background()
{
	_back.setRGBA(Color(.2f, .2f, .2f, 1.f));
	_front.setRGBA(Color(.4f, .4f, .4f, 1.f));

	_border = 2;

	setUI(true);
}

Background::~Background()
{
}

void Background::update()
{
}

void Background::draw()
{
	_back.draw();
	_front.draw();
}

void Background::drawClipped(fRectangle clip)
{
	_back.drawClipped(clip);
	_front.drawClipped(clip);
}

void Background::setPosition(GLfloat x, GLfloat y)
{
	presence.x = x;
	presence.y = y;
	_back.setPosition(x - (2 + _border), y - (2 + _border));
	_front.setPosition(x - 2, y - 2);
}

void Background::setSize(GLfloat w, GLfloat h)
{
	presence.w = w;
	presence.h = h;
	_back.setSize(w + ((2 + _border) * 2), h + ((2 + _border) * 2));
	_front.setSize(w + 4, h + 4);
}

void Background::setRGBA(Color c)
{
	_front.setRGBA(c);
	_back.setRGBA(Color(.2f, .2f, .2f, c.a));
}

void Background::setBorder(int b)
{
	_border = b;

	realign();
}

void Background::setUI(bool b)
{
	_back.setUI(b);
	_front.setUI(b);
}

void Background::realign()
{
	_back.setPosition(presence.x - (2 + _border), presence.y - (2 + _border));
	_front.setPosition(presence.x - 2, presence.y - 2);
	_back.setSize(presence.w + ((2 + _border) * 2), presence.h + ((2 + _border) * 2));
	_front.setSize(presence.w + 4, presence.h + 4);
}