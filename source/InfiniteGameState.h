#pragma once
#include "GameState.h"
#include "Render.h"
#include "UserInput.h"
#include "EscMenu.h"
#include "Navigation.h"
#include "Party.h"
#include "ListContainer.h"
#include "Shop.h"
#include "GameMap.h"

class InfiniteGameState : public GameState
{
public:
	InfiniteGameState();
	~InfiniteGameState();
	StateEnum update();
	void draw();

private:
	bool _paused;

	EscMenu _escMenu;
	GameMap _map;
	Level _level;
	Party _party;
	Shop _shop;
};