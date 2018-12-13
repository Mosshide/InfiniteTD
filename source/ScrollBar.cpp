#include "ScrollBar.h"

ScrollBar::ScrollBar()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;

	activeArea = presence;

	_btn.setRGBA(Color(0.f, 0.f, 0.f, 0.f));

	active = true;

	_nav.speed = .5f;
	_percent = 0;
	scrollAmount = 0;

	changed = false;

	realign();
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::update()
{
	updateWheel();
	updateClick();
}

void ScrollBar::updateWheel()
{
	if (active)
	{
		if (_btn.getClick(leftClick) != clickHold && pointInRect(mouse->p, activeArea))
		{
			if (mouse->wheel != 0.f)
			{
				_nav.target.y += mouse->wheel * -40.f;

				if (_nav.target.y < _minY)
				{
					_nav.target.y = _minY;
				}
				else if (_nav.target.y > _maxY)
				{
					_nav.target.y = _maxY;
				}
			}

			_nav.moveTowardTarget(presence);
			if (_nav.moved) changed = true;
			realign();
		}

		_percent = (presence.y - _minY) / (_maxY - _minY);
		scrollAmount = _percent * _scrollLimit;
	}
}

void ScrollBar::updateClick()
{
	changed = false;

	if (active)
	{
		_btn.update();

		if (_btn.getClick(leftClick) == clickHold)
		{
			if (mouse->dY != 0)
			{
				changed = true;

				presence.y += mouse->dY;

				if (presence.y < _minY)
				{
					presence.y = _minY;
				}
				else if (presence.y > _maxY)
				{
					presence.y = _maxY;
				}
				_nav.target.x = presence.x;
				_nav.target.y = presence.y;
			}

			_btn.hovering = true;
		}

		_percent = (presence.y - _minY) / (_maxY - _minY);
		scrollAmount = _percent * _scrollLimit;

		realign();
	}
}

void ScrollBar::draw()
{
	if (active)
	{
		_btn.draw();
	}
}

void ScrollBar::fitArea(float x, float y, float h, float scrollLimit)
{
	setSize(5, 10);
	_scrollLimit = scrollLimit;
	if (h - (scrollLimit / 2) > presence.h) setSize(5.f, h - (scrollLimit / 2));

	_minY = y;
	_maxY = y + h - presence.h;
	setPosition(x, _minY + (_percent * (_maxY - _minY)));

	if (_scrollLimit > 0) active = true;
	else
	{
		active = false;
	}

	realign();
	_nav.target.x = presence.x;
	_nav.target.y = presence.y;
}

void ScrollBar::realign()
{
	_btn.setRect(presence);
}