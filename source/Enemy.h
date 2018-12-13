#pragma once
#include "Animation.h"
#include "CombatStats.h"
#include "Navigator.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	void reset();
	void update();
	void draw();
	void realign();
	void setPath(std::vector<Vertex> p);
	std::vector<TerrainType> getPathable() { return _nav.pathable; }
	
	bool dead;
	bool ascended;

	int health;

private:
	VBORectangle _sprite;
	VBORectangle _origin;
	Navigator _nav;
};

