#include "TextEntryBox.h"

TextEntryBox::TextEntryBox()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;
	setText("Enter Text");
	text = "";

	visible = true;
	active = true;

	_untouched = true;
	_editing = false;
}

TextEntryBox::~TextEntryBox()
{
}

void TextEntryBox::update()
{
	_btn.update();

	if (active)
	{
		if (_btn.getClick(leftClick) == clickUp)
		{
			_editing = true;
			if (_untouched)
			{
				setText("");
				_untouched = false;
			}

			//Enable text input
			SDL_StartTextInput();
		}
		else
		{
			if (mouse->getClick(leftClick) == clickDown && _editing)
			{
				_editing = false;

				//stop text input
				SDL_StopTextInput();
			}
		}

		//if focused on this entry box
		if (_editing)
		{
			if (keyboard->inputText == "{b}")
			{
				if (_tb.text.length() > 0)
				{
					_tb.text.pop_back();
					setText(_tb.text);
				}
			}
			else if (keyboard->inputText == "{c}") SDL_SetClipboardText(_tb.text.c_str());
			else
			{
				_tb.text += keyboard->inputText;
				setText(_tb.text);
			}
		}
	}
	else _editing = false;
}

void TextEntryBox::draw()
{
	_tb.draw();
}

void TextEntryBox::setText(std::string t)
{
	text = t;
	_tb.setText(text);
}

void TextEntryBox::realign()
{
	_btn.setRect(presence);
	_tb.setRect(presence);
}