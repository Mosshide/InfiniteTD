#include "CharacterInventory.h"

CharacterInventory::CharacterInventory()
{
	visible = true;
	
	_titleBar.setText("Character Inventory");
	_closeBtn.setImage(textureBox->cancelIcon);
	_closeBtn.setSize(32, 32);
	realign();

	for (int i = 0; i < 13; i++)
	{
		_items.push_back(Item());
	}
	_items[0].type = itemTypeHead;
	_items[1].type = itemTypeBack;
	_items[2].type = itemTypeTrinket;
	_items[3].type = itemTypeChest;
	_items[4].type = itemTypeHand;
	_items[5].type = itemTypeHand;
	_items[6].type = itemTypeRing;
	_items[7].type = itemTypeRing;
	_items[8].type = itemTypeWeapon;
	_items[9].type = itemTypeWeapon;
	_items[10].type = itemTypeLegs;
	_items[11].type = itemTypeFoot;
	_items[12].type = itemTypeFoot;
	clear();
}

CharacterInventory::~CharacterInventory()
{
}

void CharacterInventory::update()
{
	if (visible)
	{
		withdrawAttempt = false;

		higlighted = -1;

		_titleBar.update();
		if (_titleBar.getClick(leftClick) == clickHold)
		{
			presence.x += mouse->dX;
			presence.y += mouse->dY;
			realign();
		}

		_closeBtn.update();
		if (_closeBtn.getClick(leftClick) == clickUp) visible = false;
	}
}

void CharacterInventory::draw()
{
	if (visible)
	{
		_titleBar.draw();

		_closeBtn.draw();
	}
}

void CharacterInventory::generateItems(int n)
{
	for (int i = 0; i < n; i++)
	{
		Item g;
		g.generate(1, itemTypeWeapon);
		_items.push_back(g);
	}
}

void CharacterInventory::clear()
{
	for (int i = 0; i < (int)_items.size(); i++)
	{
		_items[i].reset();
	}
	withdrawAttempt = false;
	higlighted = -1;
}

Item CharacterInventory::grabHighlightedItem()
{
	Item grab = _items[higlighted];
	_items[higlighted].reset();

	return grab;
}

Item CharacterInventory::addItem(Item itemToAdd)
{
	Item switchItem;
	

	return switchItem;
}

void CharacterInventory::realign()
{
	_titleBar.setPosition(presence.x + 2, presence.y);
	_titleBar.setSize(presence.w - 34, 25.f);
	_closeBtn.setPosition(presence.x + presence.w - 32, presence.y);
}