#pragma once
#include "ListElement.h"

class ItemListElement : public ListElement
{
public:
	ItemListElement();
	~ItemListElement();
	void draw();
	void drawClipped(fRectangle clip);
	void realign();
	void setUI(bool b);

	VBORectangle itemImg;
	VBOText itemName;
	VBOText itemDes;
	VBOText itemCost;
};

