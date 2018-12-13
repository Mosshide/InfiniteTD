#include "ListElement.h"

ListElement::ListElement()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;

	selected = false;
	hovering = false;
	active = true;
	greedy = true;
	setUI(true);
	name = "list element";

	_highlight.setWireframe(true);
	_highlight.setRGBA(Color(.6f, .6f, .6f, 1.f));

	_selection.setWireframe(false);
	_selection.setRGBA(Color(.2f, .2f, .2f, 1.f));

	_clip = nullptr;
	prev = nullptr;
	next = nullptr;
}

ListElement::~ListElement()
{
}

void ListElement::update()
{
	mouse->sendInfo(isUI, greedy, &presence, active, &name, hovering, _clickState);

	if (_clickState[leftClick] == clickUp)
	{
		selected = true;
	}
}

void ListElement::updateClipped(fRectangle clip)
{
	if (rectCollison(clip, presence)) mouse->sendInfo(isUI, greedy, &rectIntersection(presence, clip), active, &name, hovering, _clickState);

	if (_clickState[leftClick] == clickUp)
	{
		selected = true;
	}
}

void ListElement::draw()
{
	if (selected)
	{
		_selection.draw();
	}

	if (hovering)
	{
		_highlight.draw();
	}
}

void ListElement::drawClipped(fRectangle clip)
{
	if (rectCollison(clip, presence))
	{
		clip = rectIntersection(presence, clip);

		if (selected)
		{
			_selection.drawClipped(clip);
		}

		if (hovering)
		{
			_highlight.drawClipped(clip);
		}
	}
}

void ListElement::realign()
{
	_highlight.setRect(presence);
	_selection.setRect(presence);
}

ClickState ListElement::getClick(MouseClick mc)
{
	return _clickState[mc];
}

void ListElement::setWidth(GLfloat w)
{
	presence.w = w;
	realign();
}

void ListElement::setUI(bool b)
{
	isUI = b;

	_highlight.setUI(b);
	_selection.setUI(b);
}