#pragma once
#include "CombatStats.h"
#include "Animation.h"
#include "Enemy.h"
#include "Navigator.h"
#include "Entity.h"

class Attack : public Entity
{
public:
	Attack();
	~Attack();
	void update();
	void draw();
	void realign();

	Enemy *targetID;
	bool dead;

	CombatStats *stats;

private:
	Animation _ani;
	Navigator _nav;
};

