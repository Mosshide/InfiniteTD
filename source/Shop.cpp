#include "Shop.h"

Shop::Shop()
{
	presence.x = 800;
	presence.y = 100;
	presence.w = 400;
	presence.h = 600;

	_titleBarBtn.setText("Shop");

	_dialogue.setStyle(boxScroll);
	_dialogue.setText("This is maybe a description of the shop.");

	active = false;

	_openBtn.setPosition(render->getScreenWidth() - 48, render->getScreenHeight() - 48);
	_openBtn.setSize(32, 32);
	_openBtn.setImage(textureBox->shirtIcon);

	_closeBtn.setSize(render->getFontSize(0), render->getFontSize(0));
	_closeBtn.setImage(textureBox->cancelIcon);

	_portrait.setTexture(textureBox->shopPortrait);

	inventory.generateItems(10, 1.5f);

	realign();
}

Shop::~Shop()
{
	
}

void Shop::update()
{
	_openBtn.update();
	if (!active)
	{
		if (_openBtn.getClick(leftClick) == clickUp)
		{
			active = true;
		}
	}
	else
	{
		_dialogue.update();
		inventory.update();

		_closeBtn.update();
		if (_closeBtn.getClick(leftClick) == clickUp || _openBtn.getClick(leftClick) == clickUp)
		{
			active = false;
		}

		_titleBarBtn.update();
		if (_titleBarBtn.getClick(leftClick) == clickHold)
		{
			offsetPosition(mouse->dX, mouse->dY);
		}

		if (pointInRect(mouse->p, presence))
		{
			mouse->lockClick("shop", leftClick);
			mouse->lockClick("shop", rightClick);
			mouse->lockClick("shop", middleClick);
		}
	}
}

void Shop::draw()
{
	_openBtn.draw();

	if (active)
	{
		_bg.draw();

		_dialogue.draw();
		_portrait.draw();

		inventory.draw();

		_titleBarBtn.draw();
		_closeBtn.draw();
	}
}

void Shop::realign()
{
	_portrait.setPosition(presence.x + 5, presence.y + 50);
	_portrait.setSize(400 * ((presence.h / 3) - 55) / 450, (presence.h / 3) - 55);
	_dialogue.setPosition(_portrait.presence.x + _portrait.presence.w + 5, presence.y + 50);
	_dialogue.setSize(presence.w - _portrait.presence.w - 15, _portrait.presence.h);

	inventory.setPosition(presence.x + 5, _portrait.presence.y + _portrait.presence.h + 10);
	inventory.setSize(presence.w - 10, presence.h - _portrait.presence.h - 65);

	_titleBarBtn.setPosition(presence.x, presence.y);
	_titleBarBtn.setSize(presence.w - render->getFontSize(0), render->getFontSize(0));

	_closeBtn.setPosition(presence.x + presence.w - render->getFontSize(0), presence.y);

	_bg.setPosition(presence.x, presence.y);
	_bg.setSize(presence.w, presence.h);
}