#pragma once
#include "UserInput.h"
#include "TextBox.h"

class Button : public Entity
{
public:
	Button();
	~Button();
	void update();
	void draw();
	void drawClipped(fRectangle clip);
	ClickState getClick(MouseClick mc);
	void setRGBA(Color c);
	void setBackgroundRGBA(Color c);
	void setText(std::string text);
	void setText(int text) { setText(std::to_string(text)); }
	void setUI(bool b);
	void realign();

	bool visible;
	bool background;
	bool isUI;

	bool active;
	bool greedy;
	std::string name;

	bool hovering;
	bool hasBeenPressed;
	int timesPressed;

protected:
	Color _color;
	Color _bgColor;
	ClickState _clickState[3];
	Background _bg;
	VBOText _text;
};

