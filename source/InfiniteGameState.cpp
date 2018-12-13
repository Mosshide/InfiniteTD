#include "InfiniteGameState.h"

InfiniteGameState::InfiniteGameState()
{
	id = infiniteGameState;

	_paused = false;

	gameCamera = { 0, 0 };

	_map.load("meme.nm");
	_map.play();
	
	_level.setNav(_map.getNav());
	_level.generateEnemyPath();

	_party.setLevel(&_level);
	_party.setNav(_map.getNav());
}

InfiniteGameState::~InfiniteGameState()
{
	
}

StateEnum InfiniteGameState::update()
{
	if (!_escMenu.active)
	{
		_shop.update();

		_level.update();

		_party.chargeMoney(-_level.getBounty());

		_party.updateGame();

		_map.update();

		if (_shop.inventory.sellAttempt)
		{
			if (_party.openInventory())
			{
				if (_party.chargeMoney(_shop.inventory.getHighlightedPrice()))
				{
					_shop.inventory.addGold(_shop.inventory.getHighlightedPrice());
					_party.receiveItem(_shop.inventory.grabHighlightedItem());
				}
			}
		}

		//maybe move the map around
		if (mouse->getClick(rightClick) == clickHold)
		{
			gameCamera.x += (float)mouse->dX;
			gameCamera.y += (float)mouse->dY;
			mouse->lockClick("move camera", rightClick);

			if (gameCamera.x < -_map.presence.w + render->getScreenWidth()) gameCamera.x = -_map.presence.w + render->getScreenWidth();
			if (gameCamera.y < -_map.presence.h + render->getScreenHeight()) gameCamera.y = -_map.presence.h + render->getScreenHeight();
			if (gameCamera.x > 0) gameCamera.x = 0;
			if (gameCamera.y > 0) gameCamera.y = 0;
		}
	}

	//state changing
	if (_party.health <= 0) return mainMenuState;
	else return _escMenu.update();
}

void InfiniteGameState::draw()
{
	_map.draw();

	_level.draw();

	_party.draw();

	_level.drawUI();

	_party.drawUI();

	_shop.draw();

	_escMenu.draw();
}