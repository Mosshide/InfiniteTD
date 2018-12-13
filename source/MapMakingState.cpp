#include "MapMakingState.h"

MapMakingState::MapMakingState()
{
	id = mapMakingState;
	_mc.enable();
	_escMenu.state = mapMakingState;

	_widthBox.setPosition(300.f, 400.f);
	_heightBox.setPosition(300.f, 450.f);
	_submitSize.setText("Set Size");
	_submitSize.setPosition(400.f, 350.f);
}

MapMakingState::~MapMakingState()
{
}

StateEnum MapMakingState::update()
{
	if (!_escMenu.active)
	{
		_mc.update();
		if (_mc.mapName != "")
		{
			_map.load(_mc.mapName);
			_mc.disable();
			_map.edit();
		}

		//move the map around
		if (mouse->getClick(rightClick) == clickHold)
		{
			gameCamera.x += (float)mouse->dX;
			gameCamera.y += (float)mouse->dY;
			mouse->lockClick("move camera", rightClick);
		}

		_map.update();
	}
	else
	{
		_widthBox.update();
		_heightBox.update();
		_submitSize.update();

		if (_submitSize.getClick(leftClick) == clickUp)
		{
			_map.setTiles(_widthBox.value, _heightBox.value);
		}
	}

	if (_mc.cancel) return mainMenuState;
	else return _escMenu.update();
}

void MapMakingState::draw()
{
	_map.draw();
	_mc.draw();
	_escMenu.draw();

	if (_escMenu.active)
	{
		_widthBox.draw();
		_heightBox.draw();
		_submitSize.draw();
	}
}