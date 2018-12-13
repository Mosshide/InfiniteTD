#pragma once
#include "VBORectangle.h"
#include "Navigator.h"

class Firefly : public Entity
{
public:
	Firefly();
	~Firefly();
	void update();
	void draw();
	void realign();

private:
	Navigator _nav;
	VBORectangle _fly;
	GLfloat _alpha;
};

