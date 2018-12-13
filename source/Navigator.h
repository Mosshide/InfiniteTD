#pragma once
#include "Vertex.h"
#include <vector>
#include "fRectangle.h"
#include "TerrainType.h"
#include "Physics.h"

class Navigator
{
public:
	Navigator();
	~Navigator();
	void moveTowardTarget(fRectangle &pres);
	void moveAlongPath(fRectangle &pres);
	void setPath(std::vector<Vertex> p);
	void move(fRectangle &pres);
	void turn(float t);
	void setDirection(float d);

	bool moved;

	//Vertex vel;
	float speed;
	float acc;
	float dist;
	Vertex target;
	bool reachedTarget;
	bool nextNode;
	std::vector<TerrainType> pathable;
	float direction;
	std::vector<Vertex> path;
};

