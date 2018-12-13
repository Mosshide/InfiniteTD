#pragma once
#include "ListElement.h"

class FileListElement : public ListElement
{
public:
	FileListElement();
	FileListElement(std::string name);
	~FileListElement();
	void draw();
	void drawClipped(fRectangle clip);
	void realign();
	void setUI(bool b);

	VBOText fileName;
};

