#pragma once
#include "ImageButton.h"
#include "TerrainType.h"
#include "TextureBox.h"

class TileChooser
{
public:
	TileChooser();
	~TileChooser();
	void update();
	void draw();
	fRectangle *getTileClip(TerrainType t);
	TerrainType getTile();

private:
	void initClips();

	TerrainType _currentType;

	ImageButton _chooseButton;

	fRectangle _clips[8];
};

