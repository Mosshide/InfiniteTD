#pragma once
#include <queue>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* timeeeeeeee */
#include "Vertex.h"
#include "fRectangle.h"
//#include "UserInput.h"

class Timer
{
public:
	Timer();
	~Timer();
	void update();
	Uint32 getTotal();
	Uint32 getDelta();

protected:
	Uint32 _totalTime;
	Uint32 _deltaTime;
	char _buffer[32];
}; 

extern Timer gameTimer;

/////////////
bool pointInRect(Vertex v, fRectangle *r);

bool pointInRect(Vertex v, fRectangle r);

bool rectCollison(fRectangle a, fRectangle b);

fRectangle rectIntersection(fRectangle a, fRectangle b);

float distance(Vertex a, Vertex b);

float distance(SDL_Point a, SDL_Point b);

void getDirectedVelocity(Vertex a, Vertex b, GLfloat speed, Vertex &vel);

float getDirection(Vertex a, Vertex b);

void rotate(Vertex pivot, GLfloat angle, Vertex &point);