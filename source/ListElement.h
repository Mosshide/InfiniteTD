#pragma once
#include "ImageButton.h"
#include "TextBox.h"
#include "Entity.h"

class ListElement : public Entity
{
public:
	ListElement();
	virtual ~ListElement();
	void update();
	void updateClipped(fRectangle clip);
	virtual void draw();
	virtual void drawClipped(fRectangle clip);
	virtual void realign();
	ClickState getClick(MouseClick mc);
	void setWidth(GLfloat w);
	virtual void setUI(bool b);

	bool selected;
	bool hovering;
	bool active;
	bool greedy;
	bool isUI;
	std::string name;

	fRectangle *_clip;
	ListElement *prev;
	ListElement *next;

protected:
	VBORectangle _highlight;
	VBORectangle _selection;
	ClickState _clickState[3];
};