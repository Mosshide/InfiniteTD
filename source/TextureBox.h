#pragma once
#include "Render.h"

class TextureBox
{
public:
	TextureBox();
	~TextureBox();

	GLuint blank;
	GLuint particle;

	//GLuint heart;
	GLuint money;

	//textures
	GLuint marker;
	GLuint enemy;

	GLuint abbeyInsideUnlit;
	GLuint abbeyInsideLighting;
	//GLuint mapTemplate;

	//GLuint floor;
	GLuint tileSet;

	GLuint aelWalkForward;
	GLuint aelWalkBackward;
	GLuint aelWalkLeft;
	GLuint aelWalkRight;
	GLuint aelIdle;

	GLuint kernIdle;

	//GLuint fxLightning;
	GLuint arrow;

	//ui
	GLuint aelCharIcon;
	GLuint shirtIcon;
	GLuint cancelIcon;
	//GLuint acceptIcon;
	//GLuint addIcon;

	GLuint headArmorIcon;
	GLuint backArmorIcon;
	GLuint trinketIcon;
	GLuint chestArmorIcon;
	GLuint handArmorIcon;
	GLuint ringIcon;
	GLuint weaponIcon;
	GLuint legArmorIcon;
	GLuint footArmorIcon;

	//ui art
	GLuint shopPortrait;
};

extern TextureBox *textureBox;
