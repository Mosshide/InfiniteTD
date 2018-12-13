#pragma once
#include "Inputmouse.h"
#include "Inputkeyboard.h"

class UserInput
{
public:
	UserInput();
	bool getInput();

protected:
	SDL_Event _event;
};

extern InputKeyboard* keyboard;
extern InputMouse* mouse;