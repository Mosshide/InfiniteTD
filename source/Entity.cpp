#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::setPosition(GLfloat x, GLfloat y)
{
	presence.x = x;
	presence.y = y;

	realign();
}

void Entity::offsetPosition(GLfloat x, GLfloat y)
{
	presence.x += x;
	presence.y += y;

	realign();
}

void Entity::setSize(GLfloat w, GLfloat h)
{
	presence.w = w;
	presence.h = h;

	realign();
}

void Entity::setRect(fRectangle r)
{
	presence.x = r.x;
	presence.y = r.y;
	presence.w = r.w;
	presence.h = r.h;

	realign();
}