#include "Navigator.h"

Navigator::Navigator()
{
	moved = false;
	nextNode = false;
	reachedTarget = false;
	speed = .1f;
	acc = 0.f;
}

Navigator::~Navigator()
{
}

void Navigator::moveTowardTarget(fRectangle &pres)
{
	moved = false;

	float d = speed * gameTimer.getDelta();

	if (d != 0.f) moved = true;

	direction = getDirection(pres.getVertex(0), target);
	while (direction < 0) direction += float(2 * M_PI);
	while (direction > 2 * M_PI) direction -= float(2 * M_PI);

	Vertex origin = { 0, 0 };
	Vertex delta;
	delta.x = d * cos(direction);
	delta.y = d * sin(direction);
	if (distance(origin, delta) > distance(pres.getVertex(0), target))
	{
		pres.x = target.x;
		pres.y = target.y;
		nextNode = true;
	}
	else
	{
		pres.x -= delta.x;
		pres.y -= delta.y;
	}
}

void Navigator::moveAlongPath(fRectangle &pres)
{
	if (!reachedTarget)
	{
		if (!path.empty())
		{
			moveTowardTarget(pres);

			if (nextNode)
			{
				path.pop_back();
				if (path.empty()) reachedTarget = true;
				else
				{
					target.x = path.back().x;
					target.y = path.back().y;
				}
				nextNode = false;
			}
		}
	}
}

void Navigator::setPath(std::vector<Vertex> p)
{
	path = p;
	if ((int)path.size() > 0)
	{
		target.x = path.back().x;
		target.y = path.back().y;
		reachedTarget = false;
	}
}

void Navigator::move(fRectangle &pres)
{
	moved = false;
	dist = 0;

	speed += acc * gameTimer.getDelta();
	dist = speed * gameTimer.getDelta();
	if (dist != 0.f) moved = true;

	Vertex delta;
	delta.x = dist * cos(direction);
	delta.y = dist * sin(direction);

	pres.x -= delta.x;
	pres.y -= delta.y;
}

void Navigator::turn(float t)
{
	direction += t;

	if (direction < 0.f) direction += 2.f * (float)M_PI;
	if (direction > 2.f * (float)M_PI) direction -= 2.f * (float)M_PI;
}

void Navigator::setDirection(float d)
{
	direction = d;

	if (direction < 0.f) direction += 2.f * (float)M_PI;
	if (direction > 2.f * (float)M_PI) direction -= 2.f * (float)M_PI;
}