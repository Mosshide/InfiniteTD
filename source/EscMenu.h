#pragma once
#include "Button.h"
#include "StateEnum.h"

class EscMenu
{
public:
	EscMenu();
	~EscMenu();
	StateEnum update();
	void draw();

	bool active;
	StateEnum state;

private:
	VBORectangle _shade;
	VBOText _title;
	Button _mainMenu;
	Button _exitGame;
};

