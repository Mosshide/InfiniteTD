#include "Attack.h"

Attack::Attack()
{
	dead = true;
	presence.w = 16;
	presence.h = 16;

	targetID = nullptr;
	stats = nullptr;

	realign();

	_ani.setSpriteSheet(textureBox->arrow, 1, 1);
	_ani.modSpeed(.05f);
	_ani.setUI(false);
	_ani.setSize(presence.w, presence.h);

	_nav.speed = .2f;
}

Attack::~Attack()
{
}

void Attack::update()
{
	if (!dead)
	{
		if (targetID != nullptr)
		{
			if (targetID->dead) targetID = nullptr;
			else
			{
				_nav.target.x = targetID->presence.x;
				_nav.target.y = targetID->presence.y;
			}
		}
		//else printf("Attack has no target.\n");
		_nav.moveTowardTarget(presence);
		_ani.setRotation(_nav.direction - float(M_PI / 2));

		if (_nav.nextNode)
		{
			dead = true;
			if (targetID != nullptr && stats != nullptr)
			{
				targetID->health -= stats->mod[bluntDamageMod];
				targetID = nullptr;
			}
		}

		_ani.setRect(presence);
		_ani.update();
	}
}

void Attack::draw()
{
	if (!dead)
	{
		_ani.draw();
	}
}

void Attack::realign()
{
	_ani.setPosition(presence.x - (presence.w / 2), presence.y - (presence.h / 2));
}