#pragma once
#include "Party.h"
#include "TextBox.h"

class Story
{
public:
	Story();
	~Story();
	void update();
	void advance();
	void draw();

	bool visible;

private:
	std::string _text;
	TextBox _tb;

	bool _start;
	int _day;
};

