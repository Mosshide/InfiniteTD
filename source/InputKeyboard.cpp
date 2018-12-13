#include "Inputkeyboard.h"

InputKeyboard::InputKeyboard()
{
	for (int i = 0; i < 256; i++)
	{
		key[i] = keyNone;
	}
}

InputKeyboard::~InputKeyboard()
{
}

void InputKeyboard::update()
{
	inputText = "";
	for (int i = 0; i < 256; i++)
	{
		if (key[i] == keyDown) key[i] = keyHold;
		if (key[i] == keyUp) key[i] = keyNone;
	}
}

void InputKeyboard::receiveInput(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (SDL_IsTextInputActive() == SDL_TRUE)
		{
			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE)
			{
				//lop off character
				inputText = "{b}";
			}
			//Handle copy
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				inputText = "{c}";
				//SDL_SetClipboardText(inputText.c_str());
			}
			//Handle paste
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				inputText = SDL_GetClipboardText();
			}
		}
		else
		{
			key[e.key.keysym.sym] = keyDown;
		}
	}
	//Special text input event
	if (e.type == SDL_TEXTINPUT && SDL_IsTextInputActive() == SDL_TRUE)
	{
		//Not copy or pasting
		if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C' ||
			e.text.text[0] == 'v' || e.text.text[0] == 'V') &&
			SDL_GetModState() & KMOD_CTRL))
		{
			//Append character
			inputText = e.text.text;
		}
	}
	if (e.type == SDL_KEYUP)
	{
		key[e.key.keysym.sym] = keyUp;
		//printf("%d", e.key.keysym.sym);
	}
}

KeyState InputKeyboard::getKey(char k)
{
	return key[(int)k];
}