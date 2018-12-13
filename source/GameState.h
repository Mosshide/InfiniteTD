#pragma once
#include "StateEnum.h"

class GameState
{
public:
	GameState();
	virtual ~GameState();
	virtual StateEnum update(){ return quitState; };
	virtual void draw(){};
	
	StateEnum id;
};

