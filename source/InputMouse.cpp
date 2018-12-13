 #include "Inputmouse.h"

InputMouse::InputMouse()
{
	wheel = 0;
	p = { 0, 0 };
	x = 0;
	y = 0;
	worldP = { 0, 0 };
	worldX = 0;
	worldY = 0;
	dX = 0;
	dY = 0;
	
	for (int i = 0; i < 3; i++)
	{
		_click[i] = clickNone;
		clicked[i] = "no click";
		_lockclick[i] = false;
	}
}

InputMouse::~InputMouse()
{
}

void InputMouse::update()
{
	for (int i = 0; i < 3; i++)
	{
		clicked[i] = "no click";
		_lockclick[i] = false;
	}
	wheel = 0;

	for (int i = 0; i < 3; i++)
	{
		if (_click[i] == clickDown)
		{
			_click[i] = clickHold;
			clicked[i] = "none";
		}
		if (_click[i] == clickHold)
		{
			clicked[i] = "none";
		}
		if (_click[i] == clickUp)
		{
			_click[i] = clickNone;
		}
	}

	/*if (render->getFullscreen())
	{
		SDL_GetMouseState(&dX, &dY);
		dX = int(dX*render->getWidthRatio());
		dY = int(dY*render->getHeightRatio());

		dX = dX - x;
		dY = dY - y;
		SDL_GetMouseState(&x, &y);
		x = int(x*render->getWidthRatio());
		y = int(y*render->getHeightRatio());
	}
	else
	{*/
		SDL_GetMouseState(&dX, &dY);
		dX = dX - x;
		dY = dY - y;
		SDL_GetMouseState(&x, &y);
	//}
	worldX = int(x - gameCamera.x);
	worldY = int(y - gameCamera.y);

	p = { (GLfloat)x, (GLfloat)y };
	worldP = { (GLfloat)worldX, (GLfloat)worldY };
}

void InputMouse::receiveInput(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		_click[e.button.button - 1] = clickDown;
		clicked[e.button.button - 1] = "none";
	}
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		_click[e.button.button - 1] = clickUp;
		clicked[e.button.button - 1] = "none";
	}
	if (e.type == SDL_MOUSEWHEEL)
	{
		wheel = e.wheel.y;
	}
}

ClickState InputMouse::getClick(MouseClick mc)
{
	if (_lockclick[mc])
	{
		return clickNone;
	}
	else
	{
		return _click[mc];
	}
}

void InputMouse::lockClick(std::string *object, MouseClick mc)
{
	if (!_lockclick[mc])
	{
		_lockclick[mc] = true;
		clicked[mc] = *object;
	}
}

void InputMouse::sendInfo(bool ui, bool greedy, fRectangle *pres, bool active, std::string *name, bool &h, ClickState *cs)
{
	h = false;
	Vertex pos = p;
	if (!ui) pos = worldP;

	if (active)
	{
		if (pointInRect(pos, pres))
		{
			h = true;

			for (int i = 0; i < 3; i++)
			{
				if (getClick((MouseClick)i) == clickDown)
				{
					cs[i] = clickDown;
					if (greedy) lockClick(name, (MouseClick)i);
				}
				else if (getClick((MouseClick)i) == clickUp)
				{
					if (cs[i] == clickDown || cs[i] == clickHold)
					{
						cs[i] = clickUp;
						if (greedy) lockClick(name, (MouseClick)i);
					}
				}
				else if (cs[i] == clickDown)
				{
					cs[i] = clickHold;
					if (greedy) lockClick(name, (MouseClick)i);
				}
				else if (cs[i] == clickUp)
				{
					cs[i] = clickNone;
				}
				else if (cs[i] == clickHold)
				{
					if (greedy) lockClick(name, (MouseClick)i);
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				if (cs[i] != clickHold) cs[i] = clickNone;
				else if (getClick((MouseClick)i) == clickUp)
				{
					cs[i] = clickNone;
					if (greedy) lockClick(name, (MouseClick)i);
				}
				else if (getClick((MouseClick)i) == clickNone ||
					getClick((MouseClick)i) == clickDown) cs[i] = clickNone;
				else
				{
					if (greedy) lockClick(name, (MouseClick)i);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			cs[i] = clickNone;
		}

		if (greedy && pointInRect(pos, pres))
		{
			for (int i = 0; i < 3; i++)
			{
				lockClick(name, (MouseClick)i);
			}
		}
	}
}