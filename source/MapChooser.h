#pragma once
#include "ListContainer.h"
#include <Windows.h>
#include "TextEntryBox.h"
#include "FileListElement.h"

class MapChooser
{
public:
	MapChooser();
	~MapChooser();
	void update();
	void draw();
	void refresh();
	void enable();
	void disable();
	
	bool cancel;
	std::string mapName;

private:
	bool _enabled;
	std::vector<std::string> _fileNames;
	ListContainer _mapList;
	TextEntryBox _newMapText;
	Button _chooseBtn;
	Button _cancelBtn;
	Button _createBtn;
	Button _deleteBtn;
};

