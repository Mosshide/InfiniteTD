#pragma once
#include "ListContainer.h"
#include "Inventory.h"

class StorePage : public Entity
{
public:
	StorePage();
	~StorePage();
	void draw();
	void update();

	//override
	void setPosition(float x, float y);
	void setSize(int w, int h);

private:
	void realign();


	TextBox _dialogue;

	Inventory _playerInventory;
	Inventory _storeInventory;
};