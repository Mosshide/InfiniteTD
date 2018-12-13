#pragma once
#include "CombatStats.h"
#include "NameGrabber.h"
#include "Render.h"
#include "ItemListElement.h"
#include "TextureBox.h"
#include "ImageButton.h"
#include "Entity.h"

enum ItemType {
	itemTypeHead,
	itemTypeBack,
	itemTypeHand,
	itemTypeChest,
	itemTypeLegs,
	itemTypeFoot,
	itemTypeWeapon,
	itemTypeRing,
	itemTypeTrinket
};

class Item
{
public:
	Item();
	~Item();
	void reset();
	void generate(int l, ItemType i = itemTypeWeapon);
	void modPrice(float m);
	ListElement* getListElement();

	std::string name;
	std::string description;
	ItemType type;
	int level;
	CombatStats stats;
	int price;

private:
	GLuint _txr;
	int _basePrice;
};