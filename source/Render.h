#pragma once
#include <fstream>
#include "Entity.h"
#include "Shader.h"
//#include <glm/gtx/transform.hpp>

enum RenderType{
	imageRndr,
	textRndr,
	uniTextRndr,
	rectRndr,
	lineRndr
};

enum PositionType {
	uiPosition,
	worldPosition
};

enum RectType{
	filled,
	outlined
};

class Render
{
public:
	Render();
	~Render();
	void renderGame();

	//textures
	void newTxtTxr(GLuint *txr, std::string textureText, SDL_Color textColor, int f);
	void newUniTxtTxr(GLuint *txr, Uint16 textureText, SDL_Color textColor, int f);
	void newTxtTxr(GLuint *txr);
	void loadTxr(GLuint *txr, std::string path, bool filter = false);
	void clearTexture(GLuint txr);
	
	//screen
	void setScreenSize(int w, int h);
	void setFullscreen(bool f);
	int getScreenWidth();
	int getScreenHeight();
	fRectangle getScreen();
	float getWidthRatio();
	float getHeightRatio();
	bool getFullscreen();

	//animation
	void setBaseFrameTime(int t);
	int getBaseFrameTime();

	//font
	GLfloat getFontSize(int f);
	GLfloat getTextWidth(std::string t, int f);

	Shader *getShader();

	//exp batching
	/*void initWorldVBO();
	void freeWorldVBO();
	void initUIVBO();
	void freeUIVBO();*/
	
protected:
	bool initGL();
	void stopGL();
	SDL_Surface *_surfRender_text(std::string textureText, SDL_Color textColor, TTF_Font* ft);
	
	//fps
	bool _showFPS;
	int _frame;
	int _time;
	int _fps;

	//screen values
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_BPP;
	float WIDTH_RATIO;
	float HEIGHT_RATIO;
	bool FULLSCREEN;

	//OpenGL context
	SDL_GLContext gContext;
	Shader _shader;

	//sdl stuff
	SDL_Window *window;
	SDL_Rect rctDisplay;
	SDL_Surface *windowIcon;

	//fonts
	TTF_Font *font[3];
	int fontSize[3];
	char buffer[32];

	//exp batching
	/*Entity **_worldSort;
	GLuint _worldVbo;
	GLuint _worldIbo;
	int _numWorldVertices;
	Entity **_UISort;
	GLuint _UIVbo;
	GLuint _UIIbo;
	int _numUIVertices;*/

	int BASE_FRAME_TIME;
};
extern Render *render;

extern char _buffer[33];
extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern const int MAX_CHARACTERS;
extern const int MAX_ENEMIES;
extern const int MAX_ATTACKS;
extern const int TOOLTIP_DELAY;


