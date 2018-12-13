#include "ItemTooltip.h"

ItemTooltip::ItemTooltip()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 150;
	presence.h = 200;

	realign();
}

ItemTooltip::~ItemTooltip()
{

}

void ItemTooltip::update()
{
	setPosition(mouse->p.x + 10.f, mouse->p.y + 10.f);
}

void ItemTooltip::draw()
{
	if (visible)
	{
		_bg.draw();
		_name.draw();
		_desc.draw();
		for (int i = 0; i < 12; i++)
		{
			_mod[i].draw();
		}
	}

	visible = false;
}

void ItemTooltip::setItem(Item *it)
{
	visible = true;

	_name.setText(it->name);
	_desc.setText(it->description);
	for (int i = 0; i < 12; i++)
	{
		_mod[i].setText(it->stats.mod[i]);
	}
}

void ItemTooltip::sustain()
{
	visible = true;
}

void ItemTooltip::realign()
{
	_bg.setRect(presence);
	_name.setPosition(presence.x, presence.y);
	_desc.setPosition(presence.x, presence.y + 25.f);
	for (int i = 0; i < 12; i++)
	{
		_mod[i].setPosition(presence.x + 50.f * (i / 6), presence.y + 50.f + 25.f * (i % 6));
	}
}