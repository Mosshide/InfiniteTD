#pragma once
#include "SDL.h"
#include <string>

enum KeyState
{
	keyNone,
	keyDown,
	keyHold,
	keyUp
};

class InputKeyboard
{
public:
	InputKeyboard();
	~InputKeyboard();
	void update();
	void receiveInput(SDL_Event e);
	KeyState getKey(char k);

	std::string inputText;
	KeyState key[256];
};

