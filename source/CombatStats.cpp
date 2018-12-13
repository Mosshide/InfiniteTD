#include "CombatStats.h"

CombatStats::CombatStats()
{
	reset();
}

CombatStats::~CombatStats()
{
}

CombatStats CombatStats::operator+(const CombatStats&  other)
{
	for (int i = 0; i < 12; i++)
	{
		mod[i] += other.mod[i];
	}
	return *this;
}

void CombatStats::reset()
{
	mod[bluntDamageMod] = 0;
	mod[slashDamageMod] = 0;
	mod[pierceDamageMod] = 0;
	mod[arcaneDamageMod] = 0;
	mod[fireDamageMod] = 0;
	mod[waterDamageMod] = 0;
	mod[voidDamageMod] = 0;
	mod[speedMod] = 0;
	mod[healthMod] = 0;
	mod[rangeMod] = 0;
	mod[slowMod] = 0;
	mod[stunMod] = 0;
}