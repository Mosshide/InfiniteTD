#pragma once
#include "TextBox.h"
#include "Button.h"
#include "Entity.h"

class TextEntryBox : public Entity
{
public:
	TextEntryBox();
	~TextEntryBox();
	void update();
	void draw();
	void setText(std::string t);
	void setText(int n) { setText(std::to_string(n)); }
	void realign();

	bool active;
	bool visible;
	std::string text;

protected:
	Button _btn;
	TextBox _tb;
	bool _editing;
	bool _untouched;
};