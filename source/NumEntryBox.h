#pragma once
#include "TextBox.h"
#include "Button.h"
#include "Entity.h"

class NumEntryBox : public Entity
{
public:
	NumEntryBox();
	~NumEntryBox();
	void update();
	void draw();
	void setValue(int n);
	void realign();

	bool active;
	bool visible;
	int value;

protected:
	Button _btn;
	TextBox _tb;
	bool _editing;
};