#pragma once
#include "UserInput.h"
#include "ImageButton.h"
#include "Entity.h"

class Slider : public Entity
{
public:
	Slider();
	~Slider();
	void update();
	void draw();
	void setRGBA(Color c);
	void realign();
	
	bool active;
	float percent;

protected:
	ImageButton _btn;
};

