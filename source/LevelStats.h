#pragma once
#include <cstdlib>
#include "Physics.h"

class LevelStats
{
public:
	LevelStats();
	~LevelStats();
	void update();
	void draw();
	void setLevel(int l);
	void generate();
	void start();
	void pause();
	void stop();
	bool isSpawnOK();

	bool runningLevel;

private:
	int _currentLevel;

	int _enemiesTotal;
	int _spawnCD;
	bool _spawnOK;
	int _enemiesSpawned;
	int _spawnTimer;
	
};

