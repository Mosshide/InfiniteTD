#include "Level.h"

Level::Level()
{
	_enemies = new Enemy[MAX_ENEMIES];
	_attacks = new Attack[MAX_ATTACKS];

	_currentLevel = 1;
	generateLevel(_currentLevel);
	_bounty = 0;

	_enemyDet.setPosition((render->getScreenWidth() / 2) - (_enemyDet.presence.w / 2), render->getScreenHeight() - 80.f);

	_startLvl.setText("Start Level");
	_startLvl.setPosition((render->getScreenWidth() / 2) - (_startLvl.presence.w / 2), render->getScreenHeight() - 40.f);
}

Level::~Level()
{
	delete[] _enemies;
	delete[] _attacks;
}

void Level::update()
{
	damage = 0;
	
	for (int i = 0; i < MAX_ATTACKS; i++)
	{
		_attacks[i].update();
	}

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemies[i].update();
		if (_enemies[i].ascended)
		{
			damage++;
			_enemies[i].reset();
		}
	}

	_startLvl.update();
	if (_levelStage == levelCreate)
	{
		if (_startLvl.getClick(leftClick) == clickUp)
		{
			_levelStage = levelSpawning;
			_startLvl.active = false;
		}
	}
	else if (_levelStage == levelSpawning)
	{
		_spawnCD -= gameTimer.getDelta();
		if (_spawnCD <= 0)
		{
			if (_spawned < _spawnAmount)
			{
				_spawnCD += _spawnTime;

				for (int i = 0; i < MAX_ENEMIES; i++)
				{
					if (_enemies[i].dead)
					{
						_enemies[i].dead = false;
						Vertex sp = _nav->getStartPoint();
						_enemies[i].setPosition(sp.x + _enemies[i].presence.w / 2, sp.y + _enemies[i].presence.h / 2);
						_enemies[i].setPath(_cachePath);
						_enemies[i].health = _enemyHealth;
						break;
					}
				}

				_spawned++;
			}
			else
			{
				_levelStage = levelWait;
			}
		}
	}
	else if (_levelStage == levelWait)
	{
		bool nextLevel = true;

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (!_enemies[i].dead)
			{
				nextLevel = false;
				break;
			}
		}

		if (nextLevel) generateLevel(_currentLevel + 1);
	}
}

void Level::draw()
{
	for (int i = 0; i < MAX_ATTACKS; i++)
	{
		_attacks[i].draw();
	}

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		_enemies[i].draw();
	}
}

void Level::drawUI()
{
	_enemyDet.draw();
	_startLvl.draw();
}

Enemy* Level::getClosestEnemy(Vertex v, int range)
{
	int closest = -1;
	float d = FLT_MAX;

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!_enemies[i].dead)
		{
			float newD = distance(v, _enemies[i].presence.getVertex(0));

			if (newD <= range && newD < d)
			{
				closest = i;
				d = newD;
			}
		}
	}

	if (closest >= 0) return &_enemies[closest];
	else return nullptr;
}

void Level::receiveAttacks(Attack *a)
{
	for (int i = 0; i < MAX_ATTACKS; i++)
	{
		if (_attacks[i].dead)
		{
			_attacks[i] = *a;
			break;
		}
	}
}

void Level::generateEnemyPath()
{
	_cachePath = _nav->getStartEndPath(_enemies[0].getPathable());
}

void Level::generateLevel(int l)
{
	_levelStage = levelCreate;
	_currentLevel = l;

	_spawnTime = 500;
	_spawnCD = _spawnTime;
	_spawnAmount = 10;
	_spawned = 0;
	_enemyHealth = 1 + (l * 5);

	_bounty = 10;

	_enemyDet.setText("Enemy Health: " + std::to_string(_enemyHealth));
	_startLvl.active = true;
}

int Level::getBounty()
{
	int b = _bounty;
	_bounty = 0;
	return b;
}