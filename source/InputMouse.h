#pragma once
#include "Entity.h"
#include "Render.h"

enum ClickState
{
	clickNone,
	clickDown,
	clickHold,
	clickUp
};

enum MouseClick
{
	leftClick,
	middleClick,
	rightClick
};

class InputMouse
{
public:
	InputMouse();
	~InputMouse();
	void update();
	void receiveInput(SDL_Event e);
	ClickState getClick(MouseClick mc);
	void lockClick(std::string *object, MouseClick mc);
	void lockClick(std::string object, MouseClick mc) { lockClick(&object, mc); };
	void sendInfo(bool ui, bool greedy, fRectangle *pres, bool active,
					std::string *name, bool &h, ClickState *cs);

	int wheel;
	Vertex p;
	int x;
	int y;
	Vertex worldP;
	int worldX;
	int worldY;
	int dX;
	int dY;
	std::string clicked[3];

private:
	bool _lockclick[3];
	ClickState _click[3];
};