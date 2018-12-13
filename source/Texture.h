#pragma once
#include "Render.h"

class Texture
{
public:
	Texture();
	Texture(const Texture &obj);
	Texture& operator=(const Texture& rhs);
	~Texture();

	void loadTexture(std::string path);

	SDL_Texture* txr;
};

