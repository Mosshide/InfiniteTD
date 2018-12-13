#include "MapChooser.h"

MapChooser::MapChooser()
{
	_enabled = false;
	cancel = false;
	mapName = "";

	_mapList.setPosition(render->getScreenWidth() / 4, 50);
	_mapList.setSize(render->getScreenWidth() / 2, render->getScreenHeight() / 2);

	_chooseBtn.setText("Okay");
	_cancelBtn.setText("Cancel");

	_cancelBtn.setPosition((3 * render->getScreenWidth() / 4) - _cancelBtn.presence.w, (render->getScreenHeight() / 2) + 100.f);
	_chooseBtn.setPosition(_cancelBtn.presence.x - _chooseBtn.presence.w - 10, (render->getScreenHeight() / 2) + 100.f);

	_newMapText.setPosition(render->getScreenWidth() / 4, (render->getScreenHeight() / 2) + 150);
	_newMapText.setSize(render->getScreenWidth() / 2.f, (float)render->getFontSize(0));

	_createBtn.setText("Create New Map");
	_createBtn.setPosition((3 * render->getScreenWidth() / 4) - _createBtn.presence.w, (render->getScreenHeight() / 2) + 200.f);

	_deleteBtn.setText("Delete Map");
	_deleteBtn.setPosition((3 * render->getScreenWidth() / 4) - _deleteBtn.presence.w, (render->getScreenHeight() / 2) + 250.f);

	_chooseBtn.active = false;
	_deleteBtn.active = false;
}

MapChooser::~MapChooser()
{
}

void MapChooser::update()
{
	if (_enabled)
	{
		if (_mapList.itemSelected > -1)
		{
			_chooseBtn.active = true;
			_deleteBtn.active = true;
		}
		else
		{
			_chooseBtn.active = false;
			_deleteBtn.active = false;
		}
		if (_newMapText.text != "")
		{
			bool ok = true;
			for (int i = 0; i < (int)_fileNames.size(); i++)
			{
				if (_newMapText.text + ".nm" == _fileNames[i])
				{
					ok = false;
					break;
				}
			}
			if (ok) _createBtn.active = true;
			else _createBtn.active = false;
		}
		else _createBtn.active = false;

		_mapList.update();
		_chooseBtn.update();
		_cancelBtn.update();
		_newMapText.update();
		_createBtn.update();
		_deleteBtn.update();

		if (_chooseBtn.getClick(leftClick) == clickUp)
		{
			if (_mapList.itemSelected > -1) mapName = _fileNames[_mapList.itemSelected];
		}

		if (_cancelBtn.getClick(leftClick) == clickUp)
		{
			cancel = true;
		}

		if (_createBtn.getClick(leftClick) == clickUp)
		{
			SDL_RWops *saveFile = SDL_RWFromFile(("maps/" + _newMapText.text + ".nm").c_str(), "w+b");
			if (saveFile != nullptr)
			{
				int data[4] = { 2, 2, 0, 0 };
				Vertex _centered = { 0, 0 };
				//save data
				SDL_RWwrite(saveFile, &data[0], sizeof(int), 1);
				SDL_RWwrite(saveFile, &data[1], sizeof(int), 1);
				SDL_RWwrite(saveFile, &data[2], sizeof(int), 1);
				SDL_RWwrite(saveFile, &data[3], sizeof(int), 1);
				SDL_RWwrite(saveFile, &_centered, sizeof(Vertex), 1);

				TerrainType *tiles = new TerrainType[data[1] * data[0]];
				for (int i = 0; i < data[1] * data[0]; i++)
				{
					tiles[i] = trnGrass;
					SDL_RWwrite(saveFile, &tiles[i], sizeof(TerrainType), 1);
				}

				//Close file handler
				SDL_RWclose(saveFile);

				_fileNames.push_back(_newMapText.text + ".nm");
				_mapList.addElement(new FileListElement(_newMapText.text + ".nm"));
			}
			else printf("Could not create map: %s\n", SDL_GetError());
		}

		if (_deleteBtn.getClick(leftClick) == clickUp)
		{
			if (std::remove(("maps/" + _fileNames[_mapList.itemSelected]).c_str()) == 0)
			{
				_fileNames.erase(_fileNames.begin() + _mapList.itemSelected);
				_mapList.removeElement(_mapList.itemSelected);
			}
			else printf("Couldn't delete the file!");
		}
	}
}

void MapChooser::draw()
{
	if (_enabled)
	{
		_mapList.draw();
		_chooseBtn.draw();
		_cancelBtn.draw();
		_newMapText.draw();
		_createBtn.draw();
		_deleteBtn.draw();
	}
}

void MapChooser::refresh()
{
	_fileNames.clear();
	_mapList.clear();

	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile("maps/*", &fileData)) == INVALID_HANDLE_VALUE)) 
	{
		FindNextFile(hFind, &fileData);
		while (FindNextFile(hFind, &fileData)) 
		{
			_fileNames.push_back(fileData.cFileName);
			_mapList.addElement(new FileListElement(fileData.cFileName));
		}
	}

	FindClose(hFind);
}

void MapChooser::enable()
{
	_enabled = true;
	refresh();
}

void MapChooser::disable()
{
	_enabled = false;
	mapName = "";
}