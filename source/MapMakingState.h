#pragma once
#include "GameState.h"
#include "MapChooser.h"
#include "GameMap.h"
#include "EscMenu.h"
#include "NumEntryBox.h"

class MapMakingState : public GameState
{
public:
	MapMakingState();
	~MapMakingState();
	StateEnum update();
	void draw();

private:
	MapChooser _mc;
	GameMap _map;
	EscMenu _escMenu;

	NumEntryBox _widthBox;
	NumEntryBox _heightBox;
	Button _submitSize;
};

