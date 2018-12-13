#pragma once
#include "Slider.h"
#include "TextEntryBox.h"
#include "Character.h"

class CharacterEdit
{
public:
	CharacterEdit();
	~CharacterEdit();
	void update();
	void draw();
	void setCharacter(Character *t);

	//override
	void setPosition(float x, float y);
	void setSize(float w, float h);

	fRectangle presence;

private:
	void realign();

	Character *_t;

	TextEntryBox _nameEditor;
};

