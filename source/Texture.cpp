#include "Texture.h"

Texture::Texture()
{
	txr = nullptr;
}

Texture::Texture(const Texture &obj)
{
	_x = obj._x;
	txr = nullptr;
}

Texture& Texture::operator=(const Texture& rhs)
{
	return *this;
}

Texture::~Texture()
{
	SDL_DestroyTexture(txr);
}

void Texture::loadTexture(std::string path)
{
	//The final texture
	//SDL_Texture *newTexture = nullptr;
	SDL_DestroyTexture(txr);

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		txr = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (txr == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_BLEND);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}
