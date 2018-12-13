#pragma once
#include "UserInput.h"
#include "Physics.h"
#include "AllStates.h"

class PlayGame
{
public:
	PlayGame();
	~PlayGame();
	void runGame();

private:
	StateEnum _stateRequest;
	GameState* _currentState;
	bool _quit;
};

