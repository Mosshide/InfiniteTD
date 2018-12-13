#include "TextBox.h"

TextBox::TextBox()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 64;
	text = "Textboiiii";
	visible = true;
	_style = boxDynamicWidth;
	background = true;

	setUI(true);

	_scrollAmount = 0;
	_scrollTotal = 0;
}

TextBox::~TextBox()
{
}

void TextBox::update()
{
	//scroll
	if (_scrollTotal > 0)
	{
		/*_scrollAmount -= mouse->wheel * 10;
		if (_scrollAmount < 0) _scrollAmount = 0;
		else if (_scrollAmount > (render->getFontSize(0) + 5) * (int)_lines.size() - _presence.h + 6)
			_scrollAmount = (render->getFontSize(0) + 5) * (int)_lines.size() - _presence.h + 6;*/
	}
	else
	{
		_scrollAmount = 0;
	}
}

void TextBox::draw()
{
	if (visible)
	{
		if (background) _bg.draw();

		for (int i = 0; i < (int)_lines.size(); i++)
		{
			_lines[i].draw();
		}
	}
}

void TextBox::drawClipped(fRectangle clip)
{
	if (visible)
	{
		if (rectCollison(clip, presence))
		{
			if (background) _bg.drawClipped(clip);

			for (int i = 0; i < (int)_lines.size(); i++)
			{
				_lines[i].drawClipped(clip);
			}
		}
	}
}

void TextBox::setRGBA(Color c)
{
	_color = c;
	for (int i = 0; i < (int)_lines.size(); i++)
	{
		_lines[i].setRGBA(_color);
	}
}

void TextBox::setBackgroundRGBA(Color c)
{
	_bgColor = c;
	_bg.setRGBA(_bgColor);
}

void TextBox::setText(std::string txt)
{
	_lines.clear();

	text = txt;

	if (text != "")
	{
		if (_style == boxDynamicWidth)
		{
			_lines.push_back(VBOText());
			_lines.back().setText(text);
			_lines.back().setUI(_isUI);
			presence.w = render->getTextWidth(text, 0);
			presence.h = render->getFontSize(0);
		}
		else
		{
			std::string line;
			std::string wrap;
			int lastEnd = -1;

			for (int i = 0; i < (int)text.size(); i++)
			{
				wrap += text[i];

				if ((text[i] == ' ') || (text[i] == ',') || (text[i] == '.') || (i == text.size() - 1))
				{
					GLfloat checkW = render->getTextWidth(line + wrap, 0);

					if (checkW >= presence.w)
					{
						if (line == "")
						{
							lastEnd = i;

							line = wrap;
							_lines.push_back(VBOText());
							_lines.back().setText(line);
							_lines.back().setUI(_isUI);

							wrap = "";
							line = "";
						}
						else
						{
							lastEnd = i - wrap.size();

							_lines.push_back(VBOText());
							_lines.back().setText(line);
							_lines.back().setUI(_isUI);
							line = "";

							GLfloat checkkW = render->getTextWidth(wrap, 0);

							if (checkkW >= presence.w)
							{
								_lines.push_back(VBOText());
								_lines.back().setText(wrap);
								_lines.back().setUI(_isUI);
							}
							else
							{
								line += wrap;
								wrap = "";
							}
						}
					}
					else
					{
						line += wrap;
						wrap = "";
					}
				}
			}
			_lines.push_back(VBOText());
			_lines.back().setText(line);
			_lines.back().setUI(_isUI);

			if (_style == boxDynamicHeight)
			{
				presence.h = (render->getFontSize(0) + 5) * (int)_lines.size() + 1.f;
				_scrollAmount = 0;
				_scrollTotal = 0;
			}
			else
			{
				if ((render->getFontSize(0) + 5) * (int)_lines.size() > presence.h - 6)
				{
					_scrollAmount = 0;
					_scrollTotal = (render->getFontSize(0) + 5) * (int)_lines.size() - (presence.h - 6);
				}
				else
				{
					_scrollAmount = 0;
					_scrollTotal = 0;
				}
			}
		}
	}

	realign();
}

void TextBox::setStyle(BoxStyle s)
{
	_style = s;
}

void TextBox::setSize(GLfloat w, GLfloat h)
{
	if (_style == boxDynamicHeight)
	{
		if (presence.w != w)
		{
			presence.w = w;
			setText(text);
		}
	}
	if (_style == boxScroll)
	{
		if (presence.w != w)
		{
			presence.w = w;
			setText(text);
		}
		presence.h = h;
		if ((render->getFontSize(0) + 5) * (int)_lines.size() > presence.h - 6)
		{
			_scrollAmount = 0;
			_scrollTotal = (render->getFontSize(0) + 5) * (int)_lines.size() - (presence.h - 6);
		}
		else
		{
			_scrollAmount = 0;
			_scrollTotal = 0;
		}
	}
	_bg.setSize(presence.w, presence.h);
}

void TextBox::setUI(bool b)
{
	for (int i = 0; i < (int)_lines.size(); i++)
	{
		_lines[i].setUI(b);
	}

	_bg.setUI(b);

	_isUI = b;

	realign();
}

void TextBox::realign()
{
	for (int i = 0; i < (int)_lines.size(); i++)
	{
		_lines[i].setPosition(presence.x, presence.y + (render->getFontSize(0) + 5) * i);
	}

	_bg.setPosition(presence.x, presence.y);
	_bg.setSize(presence.w, presence.h);
}