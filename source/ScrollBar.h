#pragma once
#include "ImageButton.h"
#include "Navigator.h"
#include "Entity.h"

class ScrollBar : public Entity
{
public:
	ScrollBar();
	~ScrollBar();
	void update();
	void updateWheel();
	void updateClick();
	void draw();
	void fitArea(float x, float y, float h, float scrollLimit);
	void realign();

	fRectangle activeArea;
	float scrollAmount;
	bool active;
	bool changed;

private:
	ImageButton _btn;
	Navigator _nav;
	float _percent;
	float _scrollLimit;
	float _minY;
	float _maxY;
};

