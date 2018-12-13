#pragma once
#include "Inventory.h"
#include "Attack.h"
#include "TextureBox.h"
#include "VBOCircle.h"
#include "Level.h"

class Character : public Entity
{
public:
	Character();
	~Character();
	void update();
	void draw();
	void drawUI();
	ClickState getClick(MouseClick mc);
	void realign();
	void toggleInventory();
	void updateStats();

	bool active;
	bool visible;
	bool selected;
	bool readyToAttack;
	bool isEmbarrassed;
	Inventory inv;

	std::string name;
	CombatStats stats;

	std::vector<TerrainType> placeable;
	
	Level *level;

private:
	void update_attackCD();

	TextBox _details;

	Animation _animation;
	VBORectangle _selection;
	VBOCircle _rangeIndicator;

	Attack _attack;
	
	Button _btn;

	int _attackCD;
};

