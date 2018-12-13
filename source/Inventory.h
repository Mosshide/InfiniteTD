#pragma once
#include "Item.h"
#include "ListContainer.h"
#include "ItemTooltip.h"

class Inventory : public Entity
{
public:
	Inventory();
	~Inventory();
	void update();
	void draw();
	void generateItems(int n, float mod);
	Item grabHighlightedItem();
	int getHighlightedPrice();
	void addItem(Item itemToAdd);
	void setGold(int g);
	bool addGold(int g);
	void realign();
	CombatStats getStats();

	bool sellAttempt;
	bool visible;
	bool active;

protected:
	void refreshItemList();

	ListContainer _list;
	std::vector<Item> _items;
	ItemTooltip _itt;
	int _toolTipper;
	std::string _name;
	int _gold;
	
	TextBox _title;
	TextBox _txtWealth;
};