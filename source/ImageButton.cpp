#include "ImageButton.h"

ImageButton::ImageButton()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;

	setBackgroundRGBA(Color(.4f, .4f, .4f, 1.f));

	visible = true;
	background = true;

	for (int i = 0; i < 3; i++)
	{
		_clickState[i] = clickNone;
	}
	hovering = false;
	hasBeenPressed = false;
	timesPressed = 0;

	visible = true;
	active = true;
	greedy = true;
	background = true;
	setUI(true);
	name = "image button";

	realign();
}

ImageButton::~ImageButton()
{
}

void ImageButton::update()
{
	mouse->sendInfo(isUI, greedy, &presence, active, &name, hovering, _clickState);

	if (_clickState[leftClick] == clickUp)
	{
		hasBeenPressed = true;
		timesPressed++;
	}
}

void ImageButton::draw()
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
				else if (hovering) _bg.setRGBA(Color(_bgColor.r + .07f, _bgColor.g + .07f, _bgColor.b + .07f, _bgColor.a));
				else _bg.setRGBA(_bgColor);

				_bg.draw();
			}

			_pic.setRGBA(Color(_color.r, _color.g, _color.b, _color.a));
			_pic.draw();
		}
		else
		{
			if (background)
			{
				_bg.setRGBA(Color(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a / 2));
				_bg.draw();
			}

			_pic.setRGBA(Color(_color.r, _color.g, _color.b, _color.a / 2));
			_pic.draw();
		}
	}
}

void ImageButton::drawClipped(fRectangle clip)
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

				_pic.setRGBA(Color(_color.r, _color.g, _color.b, _color.a));
				_pic.drawClipped(clip);
			}
			else
			{
				if (background)
				{
					_bg.setRGBA(Color(_bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a / 2));
					_bg.drawClipped(clip);
				}

				_pic.setRGBA(Color(_color.r, _color.g, _color.b, _color.a / 2));
				_pic.drawClipped(clip);
			}
		}
	}
}

ClickState ImageButton::getClick(MouseClick mc)
{
	return _clickState[mc];
}

void ImageButton::setRGBA(Color c)
{
	_color = c;
}

void ImageButton::setBackgroundRGBA(Color c)
{
	_bgColor = c;
}

void ImageButton::setImage(GLuint txr)
{
	_pic.setTexture(txr);
}

void ImageButton::setClip(fRectangle *clip)
{
	_pic.setClip(clip);
}

void ImageButton::setUI(bool b)
{
	isUI = b;

	_pic.setUI(b);
	_bg.setUI(b);
}

void ImageButton::realign()
{
	_pic.setPosition(presence.x, presence.y);
	_pic.setSize(presence.w, presence.h);

	_bg.setPosition(presence.x, presence.y);
	_bg.setSize(presence.w, presence.h);
}