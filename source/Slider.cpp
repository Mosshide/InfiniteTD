#include "Slider.h"

Slider::Slider()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;

	percent = .5f;
	active = true;
}

Slider::~Slider()
{
}

void Slider::update()
{
	if (active)
	{
		_btn.update();
		if (_btn.getClick(leftClick) == clickHold)
		{
			percent = (mouse->x - presence.x) / presence.w;

			if (percent < 0.f) percent = 0.f;
			if (percent > 1.f) percent = 1.f;
		}
	}
}

void Slider::draw()
{
	_btn.draw();
}

void Slider::setRGBA(Color c)
{
	_btn.setRGBA(c);
}

void Slider::realign()
{
	_btn.setRect(presence);
}