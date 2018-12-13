#include "DesiredObject.h"

DesiredObject::DesiredObject()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 32;
	presence.h = 32;

	selected = false;
	held = false;

	placeable.push_back(trnStone);

	_animation.setSpriteSheet(textureBox->money, 1, 1);
	_animation.setUI(false);

	_btn.setUI(false);
	_rangeIndicator.setUI(false);

	realign();
}

DesiredObject::~DesiredObject()
{
}

void DesiredObject::update()
{
	_btn.update();
	if (_btn.getClick(leftClick) == clickDown)
	{
		selected = true;
	}
	if (_btn.getClick(leftClick) == clickUp)
	{
		selected = false;
	}

	if (selected)
	{
		presence.x += (float)mouse->dX;
		presence.y += (float)mouse->dY;
		realign();
	}

	_animation.update();
}

void DesiredObject::draw()
{
	if (selected) _rangeIndicator.draw();
	_animation.draw();
}

void DesiredObject::realign()
{
	_animation.setRect(fRectangle(presence.x - (presence.w / 2), presence.y - (presence.h / 2), presence.w, presence.h));
	_btn.setRect(fRectangle(presence.x - (presence.w / 2), presence.y - (presence.h / 2), presence.w, presence.h));
	_rangeIndicator.setCircle(presence.x, presence.y, 500.f);
}