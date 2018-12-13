#include "Animation.h"

Animation::Animation()
{
	_frameTime = render->getBaseFrameTime();
	_remainingFrameTime = render->getBaseFrameTime();
	_frame = -1;
}

Animation::~Animation()
{
	
}

void Animation::update()
{
	if (_frame > -1)
	{
		int timeUse = gameTimer.getDelta();

		while (timeUse > 0)
		{
			if (_remainingFrameTime - timeUse <= 0)
			{
				_frame++;
				if (_frame >= _numSprites) _frame = 0;
				
				timeUse -= _remainingFrameTime;
				_remainingFrameTime = _frameTime;
			}
			else
			{
				_remainingFrameTime -= timeUse;
				timeUse = 0;
			}
		}

		_clip.x = (_frame % _numSpritesW) * _clip.w;
		_clip.y = (_frame / _numSpritesW) * _clip.h;
		_sprite.setClip(_clip);
	}
}

void Animation::draw()
{
	_sprite.draw();
}

void Animation::setSpriteSheet(GLuint ss, int total, int w)
{
	_sprite.setTexture(ss);

	_numSprites = total;
	_numSpritesW = w;

	_clip.x = 0.f;
	_clip.y = 0.f;
	_clip.w = 1.f / _numSpritesW;
	_clip.h = 1.f / (_numSprites / _numSpritesW);

	_sprite.setClip(_clip);

	_frame = 0;
	_remainingFrameTime = _frameTime;
}

void Animation::setRGBA(Color c)
{
	_sprite.setRGBA(c);
}

void Animation::setRotation(float r)
{
	_sprite.setRotation(r);
}

void Animation::modSpeed(float m)
{
	_frameTime = int(render->getBaseFrameTime() * m);
	_remainingFrameTime = _frameTime;
}

void Animation::setUI(bool b)
{
	_sprite.setUI(b);
}

void Animation::realign()
{
	_sprite.setRect(presence);
}