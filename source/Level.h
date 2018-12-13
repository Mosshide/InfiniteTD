#pragma once
#include <string>
#include "Enemy.h"
#include "LevelStats.h"
#include "Navigation.h"
#include "Attack.h"
#include "ImageButton.h"

enum LevelStage
{
	levelCreate,
	levelSpawning,
	levelWait
};

class Level
{
public:
	Level();
	~Level();
	void update();
	void draw();
	void drawUI();
	Enemy* getClosestEnemy(Vertex v, int range);
	void receiveAttacks(Attack *a);
	void generateEnemyPath();
	void generateLevel(int l);
	int getBounty();
	void setNav(Navigation *n) { _nav = n; }

	int damage;

private:
	Navigation *_nav;
	Enemy *_enemies;
	VBOText _enemyDet;
	Button _startLvl;

	Attack *_attacks;

	LevelStage _levelStage;
	int _currentLevel;
	int _spawnCD;
	int _spawnTime;
	int _spawnAmount;
	int _spawned;
	int _enemyHealth;

	int _bounty;

	std::vector<Vertex> _cachePath;
};

