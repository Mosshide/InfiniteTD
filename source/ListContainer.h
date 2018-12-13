#pragma once
#include "ListElement.h"
#include "TextureBox.h"
#include "ScrollBar.h"
#include "Background.h"
#include "UserInput.h"
#include "Entity.h"

class ListContainer : public Entity
{
public:
	ListContainer();
	~ListContainer();
	void update();
	void draw();
	void adjustPosition(ListElement *it);
	void adjustPositions();
	void updateScrollLimit();
	void addElement(ListElement *le);
	void removeElement(int n = 0);
	void clear();
	void realign();

	ListElement *elements;
	bool click[3];
	bool noScroll;
	int itemHighlighted;
	int itemSelected;

protected:
	Background _bg;
	ScrollBar _scrollBar;

	ListElement *it;
};