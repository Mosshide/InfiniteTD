#include "Button.h"

Button::Button()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;
	setText("Button");

	setBackgroundRGBA(Color(.4f, .4f, .4f, 1.f));

	visible = true;
	background = true;
	isUI = true;

	for (int i = 0; i < 3; i++)
	{
		_clickState[i] = clickNone;
	}
	hovering = false;
	hasBeenPressed = false;
	timesPressed = 0;

	active = true;
	greedy = true;
	name = "button";

	setUI(true);
}

Button::~Button()
{
}

void Button::update()
{
	mouse->sendInfo(isUI, greedy, &presence, active, &name, hovering, _clickState);

	if (_clickState[leftClick] == clickUp)
	{
		hasBeenPressed = true;
		timesPressed++;
	}
}

void Button::draw()
{
	if (visible)
	{
		if (active)
		{
			if (background)
			{
				if (hovering) _bg.setBorder(1);
				else _bg.setBorder(2);

				if (_clickState[0] == clickDown || _clickState[0] == clickHold)
					_bg.setRGBA(Color(_bgColor.r + .05f, _bgColor.g + .05f, _bgColor.b + .15f, _bgColor.a));
				else if (hovering)
				{
					_bg.setRGBA(Color(_bgColor.r + .07f, _bgColor.g + .07f, _bgColor.b + .07f, _bgColor.a));
				}
				else _bg.setRGBA(_bgColor);

				_text.setRGBA(Color(_color.r, _color.g, _color.b, _color.a));
				_bg.draw();
			}

			_text.draw();
		}
		else
		{
			if (background)
			{
				_bg.setRGBA(Color(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a / 3.f));
				_bg.draw();
			}

			_text.setRGBA(Color(_color.r, _color.g, _color.b, _color.a / 3.f));
			_text.draw();
		}
	}
}

void Button::drawClipped(fRectangle clip)
{
	if (visible)
	{
		if (rectCollison(clip, presence))
		{
			fRectangle a = { presence.x, presence.y, presence.w, presence.h };
			clip = rectIntersection(a, clip);

			if (active)
			{
				if (background)
				{
					if (hovering) _bg.setBorder(1);
					else _bg.setBorder(2);

					if (_clickState[0] == clickDown || _clickState[0] == clickHold)
						_bg.setRGBA(Color(_bgColor.r + .05f, _bgColor.g + .05f, _bgColor.b + .15f, _bgColor.a));
					else if (hovering) _bg.setRGBA(Color(_bgColor.r + .07f, _bgColor.g + .07f, _bgColor.b + .07f, _bgColor.a));
					else _bg.setRGBA(_bgColor);

					_bg.drawClipped(clip);
				}

				_text.drawClipped(clip);
			}
			else
			{
				if (background)
				{
					_bg.setRGBA(Color(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a / 2));
					_bg.drawClipped(clip);
				}

				_text.drawClipped(clip);
			}
		}
	}
}

ClickState Button::getClick(MouseClick mc)
{
	return _clickState[mc];
}

void Button::setRGBA(Color c)
{
	_color = c;
}

void Button::setBackgroundRGBA(Color c)
{
	_bgColor = c;
}

void Button::setText(std::string text)
{
	_text.setText(text);
	setSize(_text.presence.w, _text.presence.h);
}

void Button::setUI(bool b)
{
	_text.setUI(b);
	_bg.setUI(b);
	isUI = b;
}

void Button::realign()
{
	_text.setPosition(presence.x, presence.y);

	_bg.setRect(presence);
}