#include "Inventory.h"

Inventory::Inventory()
{
	setPosition(100.f, 100.f);
	setSize(300.f, 500.f);
	_name = "Inventory";
	_gold = 0;
	sellAttempt = false;
	visible = true;
	active = true;

	_title.setText(_name);
	_title.setPosition(presence.x, presence.y);

	_txtWealth.setText(_gold);
	_txtWealth.setPosition(presence.x + presence.w - _txtWealth.presence.w - 10, presence.y);

	_toolTipper = -1;
}

Inventory::~Inventory()
{
}

void Inventory::update()
{
	if (active)
	{
		sellAttempt = false;

		_itt.update();

		_list.update();

		if (_list.itemHighlighted > -1)
		{
			if (_toolTipper != _list.itemHighlighted)
			{
				_itt.setItem(&_items[_list.itemHighlighted]);
				_toolTipper = _list.itemHighlighted;
			}
			else
			{
				_itt.sustain();
			}
		}
		else _toolTipper = -1;

		if (_list.click[rightClick])
		{
			if (_list.itemHighlighted > -1) sellAttempt = true;
		}

		if (pointInRect(mouse->p, presence))
		{
			mouse->lockClick("inventory", leftClick);
			mouse->lockClick("inventory", rightClick);
			mouse->lockClick("inventory", middleClick);
		}
	}
}

void Inventory::draw()
{
	if (visible)
	{
		_list.draw();

		_title.draw();
		_txtWealth.draw();

		_itt.draw();
	}
}

void Inventory::generateItems(int n, float mod)
{
	for (int i = 0; i < n; i++)
	{
		Item g;
		g.generate(1, itemTypeWeapon);
		g.modPrice(mod);
		_items.push_back(g);
		_list.addElement(g.getListElement());
	}
}

void Inventory::refreshItemList()
{
	_list.clear();

	for (int i = 0; i < (int)_items.size(); i++)
	{
		_list.addElement(_items[i].getListElement());
	}
}

Item Inventory::grabHighlightedItem()
{
	Item grab = _items.at(_list.itemHighlighted);

	grab.modPrice(1.f);

	_items.erase(_items.begin() + _list.itemHighlighted);

	_list.removeElement(_list.itemHighlighted);

	return grab;
}

int Inventory::getHighlightedPrice()
{
	return _items[_list.itemHighlighted].price;
}

void Inventory::addItem(Item itemToAdd)
{
	_items.push_back(itemToAdd);

	_list.addElement(_items.back().getListElement());
}

void Inventory::setGold(int g)
{
	_gold = g;
	_txtWealth.setText(_gold);
	_txtWealth.setPosition(presence.x + presence.w - _txtWealth.presence.w - 10, presence.y);
}

bool Inventory::addGold(int g)
{
	if (_gold + g > -1)
	{
		_gold += g;
		_txtWealth.setText(_gold);
		_txtWealth.setPosition(presence.x + presence.w - _txtWealth.presence.w - 10, presence.y);
		return true;
	}
	else return false;
}

void Inventory::realign()
{
	_title.setPosition(presence.x, presence.y);
	_txtWealth.setPosition(presence.x + presence.w - _txtWealth.presence.w - 10, presence.y);

	_list.setRect(fRectangle(presence.x, presence.y + 30, presence.w, presence.h - 30));
}

CombatStats Inventory::getStats()
{
	CombatStats c;
	for (int i = 0; i < (int)_items.size(); i++)
	{
		c = c + _items[i].stats;
	}

	return c;
}