#pragma once
#include "TextureBox.h"
#include "Navigation.h"
#include "UserInput.h"
#include "TileChooser.h"
#include "VBO.h"
#include "Firefly.h"
#include <iostream>
#include <fstream>
#include "DesiredObject.h"

class GameMap : public Entity
{
public:
	GameMap();
	~GameMap();
	void update();
	void draw();
	void enable();
	void disable();
	void load(std::string file);
	void save();
	void edit();
	void play();
	void setTiles(int w, int h);
	Navigation *getNav() { return &_nav; }

	int wTiled;
	int hTiled;

private:
	bool _enabled;
	std::string _fileName;
	bool _editing;

	Firefly _flies[5];

	VBO _map;
	TileChooser _tc;
	TerrainType *_tiles;
	VBORectangle _highlight;
	int _highlightedTile;

	Navigation _nav;
	int _startEnd[2];
	Vertex _centered;
	VBORectangle _endMarker;
	VBORectangle _spawnMarker;

	DesiredObject _theGoal;
};

