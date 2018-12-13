#include "Character.h"

Character::Character()
{
	presence.x = FLT_MAX;
	presence.y = FLT_MAX;
	presence.w = TILE_WIDTH * 2.f;
	presence.h = TILE_HEIGHT * 2.f;

	name = gameNames.grabName();

	inv.visible = false;
	inv.generateItems(1, 1.f);
	updateStats();

	_details.setUI(false);

	_btn.visible = false;
	_btn.name = "character";
	_btn.setUI(false);
	
	_animation.setSpriteSheet(textureBox->aelWalkForward);
	_animation.setUI(false);

	_selection.setWireframe(true);
	_selection.setUI(false);

	_rangeIndicator.setUI(false);

	active = false;
	visible = true;
	selected = true;
	readyToAttack = false;
	isEmbarrassed = false;

	_attackCD = stats.mod[speedMod];

	_attack.stats = &stats;
	_attack.dead = false;

	placeable.push_back(trnStone);

	level = nullptr;

	realign();
}

Character::~Character()
{

}

void Character::update()
{
	inv.visible = false;

	if (active)
	{
		update_attackCD();

		inv.update();

		_btn.update();
		if (_btn.getClick(leftClick) == clickUp)
		{
			selected = true;
		}
		else if (mouse->clicked[leftClick] == "none" ||
			mouse->clicked[leftClick] == "gamemap" ||
			mouse->clicked[leftClick] == "character")
		{
			selected = false;
		}
	}

	_animation.update();
}

void Character::draw()
{
	if (visible)
	{
		if (isEmbarrassed) _animation.setRGBA(Color(1.f, 0.f, 0.f, .3f));
		else if (!active) _animation.setRGBA(Color(1.f, 1.f, 1.f, .3f));
		else _animation.setRGBA(Color(1.f, 1.f, 1.f, 1.f));

		if (selected)
		{
			_selection.setRGBA(Color(1.f, 1.f, 1.f, 1.f));
			_rangeIndicator.setRGBA(Color(.1f, .1f, .8f, .15f));
			_details.visible = true;
		}
		else if (_btn.hovering)
		{
			_selection.setRGBA(Color(1.f, 1.f, 1.f, .5f));
			_rangeIndicator.setRGBA(Color(.1f, .1f, .8f, .1f));
			_details.visible = true;
		}
		else
		{
			_selection.setRGBA(Color(1.f, 1.f, 1.f, 0.f));
			_rangeIndicator.setRGBA(Color(.1f, .1f, .8f, 0.f));
			_details.visible = false;
		}

		_rangeIndicator.draw();
		_selection.draw();
		_animation.draw();
		
	}
}

void Character::drawUI()
{
	if (selected || _btn.hovering) _details.visible = true;
	else _details.visible = false;

	_details.draw();
	inv.draw();
}

ClickState Character::getClick(MouseClick mc)
{
	return _btn.getClick(mc);
}

void Character::update_attackCD()
{
	if (_attackCD > 0)
	{
		_attackCD -= gameTimer.getDelta();
		if (_attackCD <= 0) readyToAttack = true;
	}
	else  _attackCD = 0;

	if (readyToAttack)
	{
		if (level != nullptr)
		{
			_attack.targetID = level->getClosestEnemy(presence.getVertex(0), stats.mod[rangeMod]);
			if (_attack.targetID != nullptr)
			{
				_attackCD = 1000 - stats.mod[speedMod];

				readyToAttack = false;

				level->receiveAttacks(&_attack);
			}
		}
		else printf("Character has no reference to level\n");
	}
}

void Character::realign()
{
	_animation.setRect(fRectangle(presence.x - (presence.w / 2), presence.y - presence.h, presence.w, presence.h));
	_btn.setRect(fRectangle(presence.x - (TILE_WIDTH / 2), presence.y - (TILE_HEIGHT / 2), (GLfloat)TILE_WIDTH, (GLfloat)TILE_HEIGHT));
	_selection.setRect(fRectangle(presence.x - (TILE_WIDTH / 2), presence.y - (TILE_HEIGHT / 2), (GLfloat)TILE_WIDTH, (GLfloat)TILE_HEIGHT));
	_attack.setPosition(presence.x, presence.y - (presence.h / 2));
	_rangeIndicator.setCircle(presence.x, presence.y, (GLfloat)stats.mod[rangeMod]);
	_details.setPosition(presence.x - 10.f, presence.y + 5.f);
}

void Character::toggleInventory()
{
	inv.visible = true;
}

void Character::updateStats()
{
	stats.reset();
	stats = inv.getStats();
	stats.mod[rangeMod] += 100;
	_details.setText(stats.mod[bluntDamageMod]);
}