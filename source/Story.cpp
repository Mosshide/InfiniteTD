#include "Story.h"
#include "TextBox.h"

Story::Story()
{
	_presence.x = 0;
	_presence.y = 0;
	_presence.w = render->getScreenWidth();
	_presence.h = render->getScreenHeight();

	visible = false;

	_start = true;

	_day = 0;

	_tb.setSize(400, 200);
	_tb.set_leftPosition(200, 200);
	_tb.set_rgba(32, 32, 32, 0);
}

Story::~Story()
{
}

void Story::update()
{
	_tb.update();

	if (visible)
	{
		/*if (mouseLUp)
		{
			visible = false;
			mouseLUp = false;
		}*/
	}
}

void Story::advance()
{
	_day++;

	_text = "Where everyone at?";

	_tb.set_text(_text);
}

void Story::draw()
{
	if (visible)
	{
		//bg
		render->background(_presence.x, _presence.y, _presence.w, _presence.h);
		_tb.draw();
	}
}