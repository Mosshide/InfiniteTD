#pragma once
#include <string>
#include <vector>

class NameGrabber
{
public:
	NameGrabber();
	~NameGrabber();
	std::string grabName();
	std::string grabWeaponName();

private:
	std::vector<std::string> _names;
	std::vector<std::string> _weaponNames;
};

extern NameGrabber gameNames;