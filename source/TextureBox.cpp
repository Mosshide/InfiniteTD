#include "TextureBox.h"

TextureBox::TextureBox()
{
	render->loadTxr(&blank, "img/blank.png");
	render->loadTxr(&particle, "img/particles/particle.png");

	//render->loadTxr(&heart, "img/ui/heart.png");
	render->loadTxr(&money, "img/ui/money.png");

	render->loadTxr(&marker, "img/marker.png");
	render->loadTxr(&enemy, "img/not in use/old ktq art/enemy_al.png");

	render->loadTxr(&abbeyInsideUnlit, "img/splash/Abbey altar no light.png");
	render->loadTxr(&abbeyInsideLighting, "img/splash/Abbey altar light.png");
	//render->loadTxr(&mapTemplate, "img/maps/map.png");

	//render->loadTxr(&floor, "img/floor.png");
	render->loadTxr(&tileSet, "img/tiles/tiles.png");

	render->loadTxr(&aelWalkForward, "img/ani/ael/ael walk forward.png");
	render->loadTxr(&aelWalkBackward, "img/ani/ael/ael walk backward.png");
	render->loadTxr(&aelWalkLeft, "img/ani/ael/ael walk left.png");
	render->loadTxr(&aelWalkRight, "img/ani/ael/ael walk right.png");
	render->loadTxr(&aelIdle, "img/ani/ael/ael idle.png");

	render->loadTxr(&kernIdle, "img/ani/kern/kern idle.png");

	//render->loadTxr(&fxLightning, "img/ani/fx/lightning.png");
	render->loadTxr(&arrow, "img/particles/arrow.png");

	//ui
	render->loadTxr(&aelCharIcon, "img/ael icon.png");
	render->loadTxr(&shirtIcon, "img/ui/do.png");
	render->loadTxr(&cancelIcon, "img/ui/cancel.png");
	//render->loadTxr(&acceptIcon, "img/ui/accept.png");
	//render->loadTxr(&addIcon, "img/ui/add.png");

	render->loadTxr(&headArmorIcon, "img/ui/items/head armor.png");
	render->loadTxr(&backArmorIcon, "img/ui/items/back armor.png");
	render->loadTxr(&trinketIcon, "img/ui/items/trinket.png");
	render->loadTxr(&chestArmorIcon, "img/ui/items/chest armor.png");
	render->loadTxr(&handArmorIcon, "img/ui/items/hand armor.png");
	render->loadTxr(&ringIcon, "img/ui/items/ring.png");
	render->loadTxr(&weaponIcon, "img/ui/items/weapon.png");
	render->loadTxr(&legArmorIcon, "img/ui/items/leg armor.png");
	render->loadTxr(&footArmorIcon, "img/ui/items/foot armor.png");

	//ui art
	render->loadTxr(&shopPortrait, "img/char art/ael pose 1.png");
}

TextureBox::~TextureBox()
{
	glDeleteTextures(1, &blank);
	glDeleteTextures(1, &particle);

	//glDeleteTextures(1, &heart);
	glDeleteTextures(1, &money);

	glDeleteTextures(1, &marker);
	glDeleteTextures(1, &enemy);

	glDeleteTextures(1, &abbeyInsideUnlit);
	glDeleteTextures(1, &abbeyInsideLighting);
	//glDeleteTextures(1, &mapTemplate);

	//glDeleteTextures(1, &floor);
	glDeleteTextures(1, &tileSet);

	glDeleteTextures(1, &aelWalkForward);
	glDeleteTextures(1, &aelWalkBackward);
	glDeleteTextures(1, &aelWalkLeft);
	glDeleteTextures(1, &aelWalkRight);
	glDeleteTextures(1, &aelIdle);

	glDeleteTextures(1, &kernIdle);

	//glDeleteTextures(1, &fxLightning);
	glDeleteTextures(1, &arrow);

	//ui
	glDeleteTextures(1, &aelCharIcon);
	glDeleteTextures(1, &shirtIcon);
	glDeleteTextures(1, &cancelIcon);
	//glDeleteTextures(1, &acceptIcon);
	//glDeleteTextures(1, &addIcon);

	glDeleteTextures(1, &headArmorIcon);
	glDeleteTextures(1, &backArmorIcon);
	glDeleteTextures(1, &trinketIcon);
	glDeleteTextures(1, &chestArmorIcon);
	glDeleteTextures(1, &handArmorIcon);
	glDeleteTextures(1, &ringIcon);
	glDeleteTextures(1, &weaponIcon);
	glDeleteTextures(1, &legArmorIcon);
	glDeleteTextures(1, &footArmorIcon);

	//ui art
	glDeleteTextures(1, &shopPortrait);
}

TextureBox *textureBox;