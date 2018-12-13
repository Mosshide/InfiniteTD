#include "Enemy.h"

Enemy::Enemy()
{
	presence.w = 32;
	presence.h = 32;

	_sprite.setRGBA(Color(red, .1f));
	_sprite.setUI(false);
	_sprite.setSize(presence.w, presence.h);

	_nav.pathable.push_back(trnGrass);
	_nav.pathable.push_back(trnEntrance);
	_nav.pathable.push_back(trnBuilding);
	_nav.pathable.push_back(trnBed);

	_origin.setRGBA(Color(red));
	_origin.setUI(false);
	_origin.setSize(5, 5);

	reset();

	realign();
}

Enemy::~Enemy()
{
}

void Enemy::reset()
{
	dead = true;
	ascended = false;
	_nav.reachedTarget = false;
	health = 200;
	_sprite.setTexture(textureBox->kernIdle);
	setPosition(0.f, FLT_MAX);
}

void Enemy::update()
{
	if (!dead)
	{
		_nav.moveAlongPath(presence);
		realign();

		if (_nav.reachedTarget)
		{
			dead = true;
			ascended = true;
		}
		if (health <= 0)
		{
			reset();
		}
	}
}

void Enemy::draw()
{
	if (!dead)
	{
		_sprite.draw();
		//_origin.draw();
	}
}

void Enemy::realign()
{
	_sprite.setPosition(presence.x - (presence.w / 2), presence.y - (presence.h / 2));
	_origin.setPosition(presence.x - 2, presence.y - 2);
}

void Enemy::setPath(std::vector<Vertex> p)
{
	_nav.setPath(p);
}