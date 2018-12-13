#pragma once
#include "ListContainer.h"
#include "Inventory.h"
#include "TextureBox.h"
#include "ImageButton.h"
#include "Background.h"
#include "Entity.h"

class Shop : public Entity
{
public:
	Shop();
	~Shop();
	void update();
	void draw();
	void realign();

	bool active;
	
	Inventory inventory;

private:
	Background _bg;
	TextBox _dialogue;
	VBORectangle _portrait;

	Button _titleBarBtn;
	ImageButton _openBtn;
	ImageButton _closeBtn;
};