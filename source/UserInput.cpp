#include "UserInput.h"

UserInput::UserInput()
{
	SDL_StopTextInput();

	keyboard = new InputKeyboard;
	mouse = new InputMouse;
}

bool UserInput::getInput()
{
	keyboard->update();
	mouse->update();

	//Handle events on queue
    while (SDL_PollEvent(&_event) != 0)
    {
        //User requests quit
        if (_event.type == SDL_QUIT) return true;
		
		keyboard->receiveInput(_event);
		mouse->receiveInput(_event);
    }

	return false;
}

InputKeyboard* keyboard;
InputMouse* mouse;