#include "StorePage.h"

StorePage::StorePage()
{
	_x = 0;
	_y = 0;
	_w = 800;
	_h = 600;

	realign();
	_storeInventory.generateItems(7);
	_dialogue.set_text("This is maybe a description of the shop.");
}

StorePage::~StorePage()
{
}

void StorePage::draw()
{
	//bg
	queueRect((int)_x, (int)_y, _w, _h, filled, 64, 64, 64);
	queueRect((int)_x + 2, (int)_y + 2, _w - 4, _h - 4, filled, 32, 32, 32);

	_dialogue.draw();
	//_playerInventory.draw();
	_storeInventory.draw();

	queueText((int)_x + 25, (int)_y + 15, "Shop", 2);

	queueRect((int)_x + 25, (int)_y + 60, (_h / 2) - 100, (_h / 2) - 100, filled);

	queueText((int)_x + 5, (int)_y + (_h / 2) - 30, "Inventory", 0);
	queueText((int)_x + (_w / 2) + 5, (int)_y + (_h / 2) - 30, "Buy Items", 0);
}

void StorePage::update()
{
	_dialogue.update();
	_playerInventory.update();
	_storeInventory.update();

	if (_playerInventory.sellAttempt)
	{
		//_storeInventory.addItem(_playerInventory.grabHighlightedItem());
	}
	if (_storeInventory.sellAttempt)
	{
		//_playerInventory.addItem(_storeInventory.grabHighlightedItem());
		_storeInventory.grabHighlightedItem();
	}
}

void StorePage::realign()
{
	_dialogue.setPosition(_x + (_h / 2) - 70, _y + 60);
	_dialogue.setSize(_w - (25 + (_h / 2) - 100) - 30, (_h / 2) - 100);

	_playerInventory.setPosition(_x + 5, _y + (_h / 2) + 5);
	_playerInventory.setSize((_w / 2) - 10, (_h / 2) - 10);

	_storeInventory.setPosition(_x + (_w / 2) + 5, _y + (_h / 2) + 5);
	_storeInventory.setSize((_w / 2) - 10, (_h / 2) - 10);
}

//override
void StorePage::setPosition(float x, float y)
{
	_x = x;
	_y = y;
	realign();
}

void StorePage::setSize(int w, int h)
{
	if (_w > -1) _w = w;
	if (_h > -1) _h = h;
	realign();
}