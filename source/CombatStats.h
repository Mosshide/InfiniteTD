#pragma once

enum StatMod
{
	bluntDamageMod,
	slashDamageMod,
	pierceDamageMod,
	arcaneDamageMod,
	fireDamageMod,
	waterDamageMod,
	voidDamageMod,
	speedMod,
	healthMod,
	slowMod,
	stunMod,
	rangeMod
};

class CombatStats
{
public:
	CombatStats();
	~CombatStats();
	CombatStats operator+(const CombatStats& other);
	void reset();

	int mod[12];
};