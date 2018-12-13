#include "TileChooser.h"

TileChooser::TileChooser()
{
	initClips();

	_currentType = trnGrass;

	_chooseButton.setPosition(50.f, render->getScreenHeight() - 64.f);
	_chooseButton.setSize(64, 64);
	_chooseButton.setImage(textureBox->tileSet);
	_chooseButton.setClip(getTileClip(_currentType));
}

TileChooser::~TileChooser()
{
}

void TileChooser::update()
{
	_chooseButton.update();
	if (mouse->wheel != 0)
	{
		if (mouse->wheel > 0)
		{
			if (_currentType == TerrainType(TERRAIN_TYPE_SIZE - 1)) _currentType = TerrainType(0);
			else _currentType = TerrainType(_currentType + 1);
		}
		else
		{
			if (_currentType == TerrainType(0)) _currentType = TerrainType(TERRAIN_TYPE_SIZE - 1);
			else _currentType = TerrainType((int)_currentType - 1);
		}
		_chooseButton.setClip(getTileClip(_currentType));
	}
}

void TileChooser::draw()
{
	_chooseButton.draw();
}

fRectangle* TileChooser::getTileClip(TerrainType t)
{
	return &_clips[t];
}

TerrainType TileChooser::getTile()
{
	return _currentType;
}

void TileChooser::initClips()
{
	_clips[trnGrass].x = 0.f;
	_clips[trnGrass].y = 0.f;
	_clips[trnGrass].w = .125f;
	_clips[trnGrass].h = 1.f;

	_clips[trnCobble].x = .125f;
	_clips[trnCobble].y = 0.f;
	_clips[trnCobble].w = .125f;
	_clips[trnCobble].h = 1.f;

	_clips[trnDarkGrass].x = .25f;
	_clips[trnDarkGrass].y = 0.f;
	_clips[trnDarkGrass].w = .125f;
	_clips[trnDarkGrass].h = 1.f;

	_clips[trnStone].x = .375f;
	_clips[trnStone].y = 0.f;
	_clips[trnStone].w = .125f;
	_clips[trnStone].h = 1.f;

	_clips[trnEntrance].x = .5f;
	_clips[trnEntrance].y = 0.f;
	_clips[trnEntrance].w = .125f;
	_clips[trnEntrance].h = 1.f;

	_clips[trnBuilding].x = .625f;
	_clips[trnBuilding].y = 0.f;
	_clips[trnBuilding].w = .125f;
	_clips[trnBuilding].h = 1.f;

	_clips[trnBed].x = .75f;
	_clips[trnBed].y = 0.f;
	_clips[trnBed].w = .125f;
	_clips[trnBed].h = 1.f;

	_clips[trnWater].x = .875f;
	_clips[trnWater].y = 0.f;
	_clips[trnWater].w = .125f;
	_clips[trnWater].h = 1.f;
}