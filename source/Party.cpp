#include "Party.h"

Party::Party()
{
	health = 10;
	_healthTxt.setText("Health: " + std::to_string(health));
	_healthTxt.setPosition(16.f, render->getScreenHeight() - 115.f);

	_level = nullptr;

	_placing = false;

	_addChar.setPosition(16, render->getScreenHeight() - 48);
	_addChar.setText("Buy Character");

	_latestCharacter = -1;
	_characterSort = new Character*[MAX_CHARACTERS];

	_characterCost = 10;
	_money = 20;
	_moneyTxt.setText("Money: " + std::to_string(_money));
	_moneyTxt.setPosition(16.f, render->getScreenHeight() - 80.f);

	_toggleInventory.setText("Inventory");
	_toggleInventory.setPosition(160, render->getScreenHeight() - 48);
	_toggleInventory.active = false;
	_openInv = false;
	_holdItem = nullptr;
}

Party::~Party()
{
	for (int i = 0; i < _latestCharacter + 1; i++)
	{
		delete _characterSort[i];
	}
	delete[] _characterSort;
}

void Party::updateGame()
{
	_addChar.update();
	_toggleInventory.update();

	if (_placing)
	{
		_toggleInventory.active = false;

		if (keyboard->getKey('\b') == keyUp)
		{
			_placing = false;
			delete _characterSort[_latestCharacter];
			_latestCharacter--;
			chargeMoney(-_characterCost);
		}
		else
		{
			SDL_Point tile = _nav->getClosestTile(mouse->worldX, mouse->worldY);

			_characterSort[_latestCharacter]->setPosition((tile.x * TILE_WIDTH) + (TILE_WIDTH / 2),
				(tile.y * TILE_HEIGHT) + (TILE_HEIGHT / 2));

			TerrainType type = _nav->getTerrain(tile);
			bool okTile = _nav->checkterrainOK(type, _characterSort[_latestCharacter]->placeable);
			bool occ = _nav->getOccupied(tile);

			if (okTile && !occ) _characterSort[_latestCharacter]->isEmbarrassed = false;
			else _characterSort[_latestCharacter]->isEmbarrassed = true;
			if (mouse->getClick(leftClick) == clickUp)
			{
				if (!_characterSort[_latestCharacter]->isEmbarrassed)
				{
					(*_characterSort[_latestCharacter]).active = true;
					_placing = false;

					_nav->setOccupied(tile, true);
				}

				mouse->lockClick("lock in character", leftClick);
			}
		}
	}
	else
	{
		std::sort(_characterSort, _characterSort + _latestCharacter + 1, [](const Character *a, const Character *b)
		{
			return a->presence.y < b->presence.y;
		});

		if (_addChar.getClick(leftClick) == clickUp || keyboard->getKey('n') == keyHold)
		{
			if (chargeMoney(_characterCost))
			{
				if (!createCharacter()) chargeMoney(-_characterCost);
			}
		}

		if (_toggleInventory.getClick(leftClick) == clickUp || keyboard->getKey('i') == keyUp)
		{
			_openInv = !_openInv;
		}
	}

	_toggleInventory.active = false;
	for (int i = 0; i < _latestCharacter + 1; i++)
	{
		_characterSort[i]->update();
		if (_characterSort[i]->selected)
		{
			_toggleInventory.active = true;
			if (_openInv) _characterSort[i]->toggleInventory();
			if (_holdItem != nullptr)
			{
				_characterSort[i]->inv.addItem(*_holdItem);
				_characterSort[i]->updateStats();
				delete _holdItem;
				_holdItem = nullptr;
			}
		}
	}

	if (_level->damage != 0)
	{
		health -= _level->damage;
		_healthTxt.setText("Health: " + std::to_string(health));
	}
}

void Party::draw()
{
	for (int i = 0; i < _latestCharacter + 1; i++)
	{
		_characterSort[i]->draw();
	}
}

void Party::drawUI()
{
	_addChar.draw();
	_toggleInventory.draw();
	_moneyTxt.draw();
	_healthTxt.draw();

	for (int i = 0; i < _latestCharacter + 1; i++)
	{
		_characterSort[i]->drawUI();
	}
}

void Party::setLevel(Level *l)
{
	_level = l;
}

bool Party::createCharacter()
{
	if (_latestCharacter < MAX_CHARACTERS - 1)
	{
		_latestCharacter++;
		_characterSort[_latestCharacter] = new Character();
		_placing = true;
		_characterSort[_latestCharacter]->setPosition(mouse->worldX, mouse->worldY);
		_characterSort[_latestCharacter]->level = _level;
		return true;
	}
	else return false;
}

bool Party::chargeMoney(int amount)
{
	if (_money >= amount)
	{
		_money -= amount;
		if (amount != 0) _moneyTxt.setText("Money: " + std::to_string(_money));
		return true;
	}
	else return false;
}

bool Party::openInventory()
{
	return _openInv;
}

void Party::receiveItem(Item i)
{
	_holdItem = new Item(i);
}