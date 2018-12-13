#include "ItemListElement.h"

ItemListElement::ItemListElement()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;

	selected = false;
	hovering = false;

	_highlight.setWireframe(true);
	_highlight.setRGBA(Color(.6f, .6f, .6f, 1.f));

	_selection.setWireframe(false);
	_selection.setRGBA(Color(.2f, .2f, .2f, 1.f));

	prev = nullptr;
	next = nullptr;

	realign();
}

ItemListElement::~ItemListElement()
{
	
}

void ItemListElement::draw()
{
	if (selected)
	{
		_selection.draw();
	}

	itemImg.draw();
	itemName.draw();
	itemDes.draw();
	itemCost.draw();

	if (hovering)
	{
		_highlight.draw();
	}
}

void ItemListElement::drawClipped(fRectangle clip)
{
	if (rectCollison(clip, presence))
	{
		clip = rectIntersection(presence, clip);

		if (selected)
		{
			_selection.drawClipped(clip);
		}

		itemImg.drawClipped(clip);
		itemName.drawClipped(clip);
		itemDes.drawClipped(clip);
		itemCost.drawClipped(clip);

		if (hovering)
		{
			_highlight.drawClipped(clip);
		}
	}
}

void ItemListElement::realign()
{
	_highlight.setRect(presence);
	_selection.setRect(presence);

	itemImg.setRect(fRectangle(presence.x + 5.f, presence.y + 10.f, 30.f, 30.f));
	itemName.setPosition(presence.x + 40, presence.y + 5);
	itemDes.setPosition(presence.x + 40, presence.y + 35);
	itemCost.setPosition(presence.x + presence.w - 50, presence.y + 5);
}

void ItemListElement::setUI(bool b)
{
	isUI = b;

	_highlight.setUI(b);
	_selection.setUI(b);

	itemImg.setUI(b);
	itemName.setUI(b);
	itemDes.setUI(b);
	itemCost.setUI(b);
}