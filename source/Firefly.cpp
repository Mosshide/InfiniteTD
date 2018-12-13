#include "Firefly.h"

Firefly::Firefly()
{
	presence = fRectangle(rand() % render->getScreenWidth(), rand() % render->getScreenHeight(), 16, 16);

	_alpha = 1.f;
	_fly.setRGBA(Color(1.f, 1.f, .3f, 1.f));
	_fly.setSize(presence.w, presence.h);
	_fly.setTexture(textureBox->particle);

	_nav.acc = 0.f;
	_nav.speed = 0.f;

	realign();
}

Firefly::~Firefly()
{
}

void Firefly::update()
{
	_nav.acc += ((rand() % 3) - 1) / 10000.f;
	if (_nav.acc > .003f) _nav.acc = .003f;
	if (_nav.acc < -.003f) _nav.acc = -.003f;
	if (_nav.speed > .1f) _nav.speed = .1f;
	if (_nav.speed < .05f) _nav.speed = .05f;
	_nav.turn(((rand() % 30) - 15) / 100.f);

	_nav.move(presence);
	

	if (presence.x > render->getScreenWidth())
	{
		_nav.setDirection(M_PI - _nav.direction);
		presence.x -= 2 * (presence.x - render->getScreenWidth());
	}
	if (presence.x < 0)
	{
		_nav.setDirection(M_PI - _nav.direction);
		presence.x -= 2 * presence.x;
	}
	if (presence.y > render->getScreenHeight())
	{
		_nav.setDirection((2 * M_PI) - _nav.direction);
		presence.y -= 2 * (presence.y - render->getScreenHeight());
	}
	if (presence.y < 0)
	{
		_nav.setDirection((2 * M_PI) - _nav.direction);
		presence.y -= 2 * presence.y;
	}

	_alpha += ((rand() % 3) - 1) / 100.f;
	if (_alpha > 1.f) _alpha = 1.f;
	if (_alpha < 0.f) _alpha = 0.f;
	_fly.setRGBA(Color(1.f, 1.f, .3f, _alpha));

	realign();
}

void Firefly::draw()
{
	_fly.draw();
}

void Firefly::realign()
{
	_fly.setPosition(presence.x - (presence.w / 2), presence.y - (presence.h / 2));
}