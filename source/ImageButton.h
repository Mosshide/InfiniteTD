#pragma once
#include "Button.h"
#include "VBORectangle.h"

class ImageButton : public Entity
{
public:
	ImageButton();
	~ImageButton();
	void update();
	void draw();
	void drawClipped(fRectangle clip);
	ClickState getClick(MouseClick mc);
	void setRGBA(Color c);
	void setBackgroundRGBA(Color c);
	void setImage(GLuint txr);
	void setClip(fRectangle *clip);
	void setClip(fRectangle clip) { setClip(&clip); };
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
	VBORectangle _pic;
};

