#include "EscMenu.h"

EscMenu::EscMenu()
{
	active = false;

	_title.setText("Paused");
	_title.setPosition(100.f, 300.f);

	_mainMenu.setText("Main Menu");
	_mainMenu.setPosition(100.f, 400.f);

	_exitGame.setText("Exit Game");
	_exitGame.setPosition(100.f, 450.f);

	_shade.setRGBA(Color(0.f, 0.f, 0.f, .4f));
	_shade.setSize(render->getScreenWidth(), render->getScreenHeight());

	state = infiniteGameState;
}

EscMenu::~EscMenu()
{
}

StateEnum EscMenu::update()
{
	if (keyboard->getKey((char)27) == keyUp)
	{
		active = !active;
	}

	if (active)
	{
		_mainMenu.update();
		_exitGame.update();

		if (_mainMenu.getClick(leftClick) == clickUp)
		{
			return mainMenuState;
		}

		if (_exitGame.getClick(leftClick) == clickUp)
		{
			return quitState;
		}

		return state;
	}
	else return state;
}

void EscMenu::draw()
{
	if (active)
	{
		_shade.draw();
		_title.draw();
		_mainMenu.draw();
		_exitGame.draw();
	}
}