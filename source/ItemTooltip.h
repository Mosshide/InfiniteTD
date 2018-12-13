#pragma once
#include "Textbox.h"
#include "Item.h"

class ItemTooltip : public Entity
{
public:
	ItemTooltip();
	~ItemTooltip();
	void update();
	void draw();
	void setItem(Item *it);
	void sustain();
	void realign();

	bool visible;

private:
	Background _bg;
	VBOText _name;
	VBOText _desc;
	VBOText _mod[12];
};

