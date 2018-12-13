#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	id = mainMenuState;

	_startButton.setText("Start");
	_startButton.setPosition(100, 100);
	_mapButton.setText("Edit Map");
	_mapButton.setPosition(100, 150);
	_quitButton.setText("Quit");
	_quitButton.setPosition(100, 200);

	_bg[0].setSize(render->getScreenWidth(), render->getScreenHeight());
	_bg[0].setTexture(textureBox->abbeyInsideUnlit);
	_bg[1].setSize(render->getScreenWidth(), render->getScreenHeight());
	_bg[1].setTexture(textureBox->abbeyInsideLighting);

	bgAlphaMod = 0;
}

MainMenuState::~MainMenuState()
{
}

StateEnum MainMenuState::update()
{
	_startButton.update();
	_mapButton.update();
	_quitButton.update();

	//bg flicker
	for (int i = 0; i < 2; i++)
	{
		if (bgAlphaMod < .95f) {
			bgAlphaMod += ((rand() % 10) - 4) / 256.f;
		}
		else {
			if (rand() % 256 < 4) bgAlphaMod = 1.f - ((rand() % 150) / 256.f);
			else bgAlphaMod = 1.f - ((rand() % 15) / 256.f);
		}
		if (bgAlphaMod < 0.f) bgAlphaMod = 0.f;
		if (bgAlphaMod > 1.f) bgAlphaMod = 1.f;
	}
	

	if (_startButton.getClick(leftClick) == clickUp) return infiniteGameState;
	else if (_mapButton.getClick(leftClick) == clickUp) return mapMakingState;
	else if (_quitButton.getClick(leftClick) == clickUp) return quitState;
	else return mainMenuState;
}

void MainMenuState::draw()
{
	_bg[0].draw();

	_bg[1].setRGBA(Color(1.f, 1.f, 1.f, bgAlphaMod));
	_bg[1].draw();

	_startButton.draw();
	_mapButton.draw();
	_quitButton.draw();
}
