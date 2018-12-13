#pragma once
#include "Button.h"
#include "Item.h"
#include "TextureBox.h"
#include "Entity.h"

class CharacterInventory : public Entity
{
public:
	CharacterInventory();
	~CharacterInventory();
	void update();
	void draw();
	void generateItems(int n);
	void clear();
	Item grabHighlightedItem();
	Item addItem(Item itemToAdd);
	void realign();

	bool visible;
	bool withdrawAttempt;
	int higlighted;

private:
	std::vector<Item> _items;

	Button _titleBar;
	ImageButton _closeBtn;
};

