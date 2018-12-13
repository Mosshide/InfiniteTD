#include "CharacterEdit.h"

CharacterEdit::CharacterEdit()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 300;
	presence.h = 300;

	realign();
	setCharacter(nullptr);
}

CharacterEdit::~CharacterEdit()
{
}

void CharacterEdit::update()
{
	_nameEditor.update();
	_t->name = _nameEditor.text;
}

void CharacterEdit::draw()
{
	_nameEditor.draw();
}


//override
void CharacterEdit::setPosition(float x, float y)
{
	presence.x = x;
	presence.y = y;
	realign();
}

void CharacterEdit::setCharacter(Character *t)
{
	_t = t;
	if (_t == nullptr)
	{
		_nameEditor.active = false;
		_nameEditor.setText("No Tower");
	}
	else
	{
		_nameEditor.active = true;
		_nameEditor.setText(_t->name);
	}
	
}

void CharacterEdit::setSize(float w, float h)
{
	if (presence.w > -1) presence.w = w;
	if (presence.h > -1) presence.h = h;
	realign();
}

void CharacterEdit::realign()
{
	//to edit char name
	_nameEditor.setPosition(presence.x + 10, presence.y + 10);
	_nameEditor.setSize(200, -1);
}
