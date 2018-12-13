#include "FileListElement.h"

FileListElement::FileListElement()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 40;

	selected = false;
	hovering = false;

	_highlight.setWireframe(true);
	_highlight.setRGBA(Color(.6f, .6f, .6f, 1.f));

	_selection.setWireframe(false);
	_selection.setRGBA(Color(.2f, .2f, .2f, 1.f));

	//fileImg.setTexture(textureBox->addIcon);

	prev = nullptr;
	next = nullptr;

	realign();
}

FileListElement::FileListElement(std::string name)
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 64;
	presence.h = 40;

	selected = false;
	hovering = false;

	_highlight.setWireframe(true);
	_highlight.setRGBA(Color(.6f, .6f, .6f, 1.f));

	_selection.setWireframe(false);
	_selection.setRGBA(Color(.2f, .2f, .2f, 1.f));

	fileName.setText(name);

	prev = nullptr;
	next = nullptr;

	realign();
}

FileListElement::~FileListElement()
{
}

void FileListElement::draw()
{
	if (selected)
	{
		_selection.draw();
	}

	fileName.draw();

	if (hovering)
	{
		_highlight.draw();
	}
}

void FileListElement::drawClipped(fRectangle clip)
{
	if (rectCollison(clip, presence))
	{
		clip = rectIntersection(presence, clip);

		if (selected)
		{
			_selection.drawClipped(clip);
		}

		fileName.drawClipped(clip);

		if (hovering)
		{
			_highlight.drawClipped(clip);
		}
	}
}

void FileListElement::realign()
{
	_highlight.setRect(presence);
	_selection.setRect(presence);

	fileName.setPosition(presence.x + 5, presence.y + 5);
}

void FileListElement::setUI(bool b)
{
	isUI = b;

	_highlight.setUI(b);
	_selection.setUI(b);

	fileName.setUI(b);
}