#pragma once
#include "Render.h"
#include "Button.h"
#include "GameState.h"
#include "TextureBox.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();
	StateEnum update();
	void draw();

private:
	Button _startButton;
	Button _mapButton;
	Button _quitButton;

	VBORectangle _bg[2];

	GLfloat bgAlphaMod;
};