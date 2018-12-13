#include "LevelStats.h"

LevelStats::LevelStats()
{
	_currentLevel = 1;

	_spawnCD = 500;
	_enemiesTotal = 10;
	_spawnTimer = 0;
	runningLevel = false;
	_enemiesSpawned = 0;
	_spawnOK = false;
}

LevelStats::~LevelStats()
{
}

void LevelStats::update()
{
	if (runningLevel)
	{
		if (!_spawnOK)
		{
			_spawnTimer += gameTimer.getDelta();
			if (_spawnTimer >= _spawnCD)
			{
				_spawnTimer -= _spawnCD;
				_spawnOK = true;
				_enemiesSpawned++;

				if (_enemiesSpawned >= _enemiesTotal)
				{
					stop();
					setLevel(_currentLevel + 1);
				}
			}
		}
	}
}

void LevelStats::draw()
{

}

void LevelStats::setLevel(int l)
{
	_currentLevel = l;
	generate();
}

void LevelStats::generate()
{
	_spawnCD = 500;
	_enemiesTotal = 10;
}

void LevelStats::start()
{
	runningLevel = true;
}

void LevelStats::pause()
{
	runningLevel = false;
}

void LevelStats::stop()
{
	runningLevel = false;
	_enemiesSpawned = 0;
	_spawnTimer = 0;
	_spawnOK = false;
}

bool LevelStats::isSpawnOK()
{
	bool b = _spawnOK;
	_spawnOK = false;

	return b;
}