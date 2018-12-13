#pragma once
#include "Entity.h"
#include "TerrainType.h"
#include "Level.h"
#include "VBOCircle.h"

class DesiredObject : public Entity
{
public:
	DesiredObject();
	~DesiredObject();
	void update();
	void draw();
	void realign();

	bool selected;
	bool held;

	std::vector<TerrainType> placeable;

	Level *level;

private:
	Animation _animation;
	VBOCircle _rangeIndicator;
	Button _btn;
};

