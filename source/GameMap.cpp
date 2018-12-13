#include "GameMap.h"

GameMap::GameMap()
{
	presence.x = 0;
	presence.y = 0;
	presence.w = 0;
	presence.h = 0;
	_enabled = false;
	wTiled = 0;
	hTiled = 0;
	_fileName = "*.*";
	_editing = false;
	_startEnd[0] = 0;
	_startEnd[1] = 0;
	_centered.x = 0;
	_centered.y = 0;

	_endMarker.setRect(fRectangle(200, 400, 32, 32));
	_endMarker.setTexture(textureBox->marker);
	_endMarker.setRGBA(Color(blue, .1f));
	_endMarker.setUI(false);
	_spawnMarker.setRect(fRectangle(600, 100, 32, 32));
	_spawnMarker.setTexture(textureBox->marker);
	_spawnMarker.setRGBA(Color(red, .1f));
	_spawnMarker.setUI(false);

	_tiles = nullptr;
	setTiles(15, 15);

	_highlight.setWireframe(true);
	_highlight.setRect(fRectangle(0, 0, TILE_WIDTH, TILE_HEIGHT));
	_highlight.setUI(false);

	_map.setTexture(textureBox->tileSet);
}

GameMap::~GameMap()
{
	if (_tiles != nullptr)
	{
		delete[] _tiles;
	}
}

void GameMap::update()
{
	if (_enabled)
	{
		for (int i = 0; i < 5; i++)
		{
			_flies[i].update();
		}

		if (_editing)
		{
			if (keyboard->getKey('d') == keyUp) setTiles(70, 55);
			if (keyboard->getKey('s') == keyUp) save();
			if (keyboard->getKey('c') == keyUp) _centered = gameCamera;

			_tc.update();

			_highlightedTile = -1;
			if (pointInRect(mouse->worldP, presence))
			{
				_highlightedTile = (wTiled * (int(mouse->worldY) / TILE_HEIGHT)) +
					(int(mouse->worldX) / TILE_WIDTH);

				_highlight.setPosition(float((_highlightedTile % wTiled) * TILE_WIDTH), 
										float((_highlightedTile / wTiled) * TILE_HEIGHT));

				if (mouse->getClick(leftClick) == clickHold)
				{
					_tiles[_highlightedTile] = _tc.getTile();
					mouse->lockClick("edit tile", leftClick);
				}

				if (keyboard->getKey('o') == keyUp)
				{
					_startEnd[0] = _highlightedTile;
					_nav.setStartEnd(_startEnd[0], _startEnd[1]);
					Vertex sp = _nav.getStartPoint();
					_spawnMarker.setPosition(sp.x, sp.y);
				}
				if (keyboard->getKey('p') == keyUp)
				{
					_startEnd[1] = _highlightedTile;
					_nav.setStartEnd(_startEnd[0], _startEnd[1]);
					Vertex ep = _nav.getEndPoint();
					_endMarker.setPosition(ep.x, ep.y);
				}
			}
		}
		else
		{
			_theGoal.update();
		}
	}
}

void GameMap::draw()
{
	if (_enabled)
	{
		fRectangle *clip;
		//custom vbo
		for (int i = 0; i < wTiled * hTiled * 6; i += 6)
		{
			clip = _tc.getTileClip(_tiles[i / 6]);
			_map.vertices[i].texCoord.s = clip->x;
			_map.vertices[i].texCoord.t = clip->y;
			_map.vertices[i + 1].texCoord.s = clip->x + clip->w;
			_map.vertices[i + 1].texCoord.t = clip->y;
			_map.vertices[i + 2].texCoord.s = clip->x + clip->w;
			_map.vertices[i + 2].texCoord.t = clip->y + clip->h;

			_map.vertices[i + 3].texCoord.s = clip->x;
			_map.vertices[i + 3].texCoord.t = clip->y;
			_map.vertices[i + 4].texCoord.s = clip->x + clip->w;
			_map.vertices[i + 4].texCoord.t = clip->y + clip->h;
			_map.vertices[i + 5].texCoord.s = clip->x;
			_map.vertices[i + 5].texCoord.t = clip->y + clip->h;

			GLfloat x = (i / 6) % wTiled * TILE_WIDTH + gameCamera.x;
			GLfloat y = (i / 6) / wTiled * TILE_HEIGHT + gameCamera.y;
			_map.vertices[i].position.x = x;
			_map.vertices[i].position.y = y;
			_map.vertices[i + 1].position.x = x + TILE_WIDTH;
			_map.vertices[i + 1].position.y = y;
			_map.vertices[i + 2].position.x = x + TILE_WIDTH;
			_map.vertices[i + 2].position.y = y + TILE_HEIGHT;

			_map.vertices[i + 3].position.x = x;
			_map.vertices[i + 3].position.y = y;
			_map.vertices[i + 4].position.x = x + TILE_WIDTH;
			_map.vertices[i + 4].position.y = y + TILE_HEIGHT;
			_map.vertices[i + 5].position.x = x;
			_map.vertices[i + 5].position.y = y + TILE_HEIGHT;
		}
		_map.draw();

		_endMarker.draw();
		_spawnMarker.draw();

		for (int i = 0; i < 5; i++)
		{
			_flies[i].draw();
		}

		if (_editing)
		{
			if (_highlightedTile > -1 && _highlightedTile < wTiled * hTiled)
			{
				_highlight.draw();
			}

			_tc.draw();
		}
		else
		{
			_theGoal.draw();
		}

		_nav.draw();
	}
}

void GameMap::enable()
{
	_enabled = true;
}

void GameMap::disable()
{
	_enabled = false;
	_editing = false;
}

void GameMap::load(std::string file)
{
	setTiles(0, 0);

	_fileName = file;

	SDL_RWops *saveFile = SDL_RWFromFile(("maps/" + _fileName).c_str(), "r+b");

	if (saveFile != NULL)
	{
		//retrieve data
		int w, h = 0;
		SDL_RWread(saveFile, &w, sizeof(int), 1);
		SDL_RWread(saveFile, &h, sizeof(int), 1);
		SDL_RWread(saveFile, &_startEnd[0], sizeof(int), 1);
		SDL_RWread(saveFile, &_startEnd[1], sizeof(int), 1);
		SDL_RWread(saveFile, &_centered, sizeof(Vertex), 1);
		gameCamera = _centered;
		_theGoal.setPosition(-gameCamera.x + render->getScreenWidth() / 2, -gameCamera.y + render->getScreenHeight() / 2);
		setTiles(w, h);
		//wTiled = w;
		//hTiled = h;
		//presence.w = (float)wTiled * TILE_WIDTH;
		//presence.h = (float)hTiled * TILE_HEIGHT;
		for (int i = 0; i < hTiled * wTiled; i++)
		{
			//_tiles.push_back(TerrainType(0));
			SDL_RWread(saveFile, &_tiles[i], sizeof(TerrainType), 1);
		}

		//Close file handler
		SDL_RWclose(saveFile);

		Vertex sp = _nav.getStartPoint();
		_spawnMarker.setPosition(sp.x, sp.y);
		Vertex ep = _nav.getEndPoint();
		_endMarker.setPosition(ep.x, ep.y);
		
	}
	else printf("Could not load: %s\n", SDL_GetError());
}

void GameMap::save()
{
	SDL_RWops *saveFile = SDL_RWFromFile(("maps/" + _fileName).c_str(), "w+b");
	if (saveFile != nullptr)
	{
		//save data
		SDL_RWwrite(saveFile, &wTiled, sizeof(int), 1);
		SDL_RWwrite(saveFile, &hTiled, sizeof(int), 1);
		SDL_RWwrite(saveFile, &_startEnd[0], sizeof(int), 1);
		SDL_RWwrite(saveFile, &_startEnd[1], sizeof(int), 1);
		SDL_RWwrite(saveFile, &_centered, sizeof(Vertex), 1);

		for (int i = 0; i < hTiled * wTiled; i++)
		{
			SDL_RWwrite(saveFile, &_tiles[i], sizeof(TerrainType), 1);
		}

		//Close file handler
		SDL_RWclose(saveFile);
	}
	else printf("Could not save: %s\n", SDL_GetError());
}

void GameMap::edit()
{
	_editing = true;
	_enabled = true;
}

void GameMap::play()
{
	_editing = false;
	_enabled = true;
	for (int i = 0; i < hTiled; i++)
	{
		for (int ii = 0; ii < wTiled; ii++)
		{
			_nav.setTerrain(ii, i, _tiles[ii + i * wTiled]);
		}
	}
}

void GameMap::setTiles(int w, int h)
{
	if (_tiles != nullptr)
	{
		TerrainType *temp = new TerrainType[w * h];
		for (int i = 0; i < h; i++)
		{
			for (int ii = 0; ii < w; ii++)
			{
				if (i < hTiled && ii < wTiled) temp[ii + i * w] = _tiles[ii + i * wTiled];
				else temp[ii + i * w] = trnGrass;
			}
		}

		delete[] _tiles;
		_tiles = temp;
	}
	else
	{
		_tiles = new TerrainType[w * h];
		for (int i = 0; i < h; i++)
		{
			for (int ii = 0; ii < w; ii++)
			{
				_tiles[ii + i * wTiled] = trnGrass;
			}
		}
	}
	
	wTiled = w;
	hTiled = h;
	presence.w = (float)wTiled * TILE_WIDTH;
	presence.h = (float)hTiled * TILE_HEIGHT;

	_map.setNumVertices(wTiled * hTiled * 6);

	_nav.setNodes(wTiled, hTiled);
	
	if (_startEnd[0] >= wTiled * hTiled) _startEnd[0] = 0;
	if (_startEnd[1] >= wTiled * hTiled) _startEnd[1] = 0;
	_nav.setStartEnd(_startEnd[0], _startEnd[1]);
	Vertex sp = _nav.getStartPoint();
	_spawnMarker.setPosition(sp.x, sp.y);
	Vertex ep = _nav.getEndPoint();
	_endMarker.setPosition(ep.x, ep.y);
}