#pragma once
#include "VBORectangle.h"

class Animation : public Entity
{
public:
	Animation();
	~Animation();
	void update();
	void draw();
	void setSpriteSheet(GLuint ss, int total = 4, int w = 4);
	void setRGBA(Color c);
	void setRotation(float r);
	void modSpeed(float m);
	void setUI(bool b);
	void realign();

private:
	VBORectangle _sprite;
	fRectangle _clip;
	int _numSprites;
	int _numSpritesW;

	int _frameTime;
	int _remainingFrameTime;
	int _frame;
};

