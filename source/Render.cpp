#include "Render.h" 

Render::Render()
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	//initialize the screen variable
	FULLSCREEN = false;
	SDL_GetDisplayBounds(0, &rctDisplay);
	if (FULLSCREEN)
	{
		SCREEN_WIDTH = rctDisplay.w;
		SCREEN_HEIGHT = rctDisplay.h;
	}
	else
	{
		SCREEN_WIDTH = 1600;//1366
		SCREEN_HEIGHT = 900;//768
	}
	SCREEN_BPP = 32;
	//initialize the sdl goodies
	window = nullptr;
	windowIcon = nullptr;

	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	 //Set up the screen
    if (!FULLSCREEN) window = SDL_CreateWindow("KernQuest",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	else window = SDL_CreateWindow("KernQuest",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

	//Create context
	gContext = SDL_GL_CreateContext(window);
	
	glewExperimental = GL_TRUE;
	glewInit();
	SDL_GL_SetSwapInterval(0);
	initGL();

	//Get window dimensions
	WIDTH_RATIO = (float)SCREEN_WIDTH/(float)rctDisplay.w;
	HEIGHT_RATIO = (float)SCREEN_HEIGHT/(float)rctDisplay.h;

	srand(int(time(nullptr)));

	windowIcon = IMG_Load("img/ael icon.png");
	SDL_SetWindowIcon(window, windowIcon);

	//Open the font
    font[0] = TTF_OpenFont("AozoraMinchoRegular.ttf", 18);
	font[1] = TTF_OpenFont("AozoraMinchoRegular.ttf", 12);
	font[2] = TTF_OpenFont("AozoraMinchoRegular.ttf", 50);
	TTF_SizeText(font[0], "0", nullptr, &fontSize[0]);
	TTF_SizeText(font[1], "1", nullptr, &fontSize[1]);
	TTF_SizeText(font[2], "2", nullptr, &fontSize[2]);

	BASE_FRAME_TIME = 250;

	_showFPS = true;
	_frame = 0;
	_time = 0;

	//SDL_SetRelativeMouseMode(SDL_TRUE);

	//_v = new VertexData2D[1000000];
}

Render::~Render()
{
	//delete[] _v;

	stopGL();

	 //Free the surface
	SDL_DestroyWindow(window);
	SDL_FreeSurface(windowIcon);

	//Close the font
    TTF_CloseFont(font[0]);
	TTF_CloseFont(font[1]);
	TTF_CloseFont(font[2]);
}

bool Render::initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Initialize clear color
	glClearColor(.1f, .1f, .1f, 1.f);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//previously in vbo draw
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		success = false;
	}

	//Load basic shader program
	if (!_shader.loadProgram())
	{
		printf("Unable to load basic shader!\n");
		return false;
	}

	//Bind basic shader program
	_shader.bind();

	//Initialize projection
	_shader.setProjection(glm::ortho<GLfloat>(0.0, (GLfloat)SCREEN_WIDTH, (GLfloat)SCREEN_HEIGHT, 0.0, 1.0, -1.0));
	_shader.updateProjection();

	//Initialize modelview
	_shader.setModelView(glm::mat4());
	_shader.updateModelView();

	_shader.setTextureUnit(0);

	_shader.enableVertexPointer();
	_shader.enableTexCoordPointer();

	return success;
}

void Render::stopGL()
{
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	_shader.disableVertexPointer();
	_shader.disableTexCoordPointer();

	_shader.unbind();
	_shader.disableVertexPointer();
	_shader.disableTexCoordPointer();
}

SDL_Surface* Render::_surfRender_text(std::string textureText, SDL_Color textColor, TTF_Font* ft)
{
	//cout << textureText << endl;
	//SDL_Texture* tempT;

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(ft, textureText.c_str(), textColor);
	if( textSurface == nullptr )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	//Create texture from surface pixels
    /*tempT = SDL_CreateTextureFromSurface(renderer, textSurface);
	if(tempT == nullptr)
	{
		printf("Unable to create texture from rendered text! SDL Error: \n");
	}
	else
	{
		SDL_SetTextureBlendMode(tempT, SDL_BLENDMODE_BLEND);
	}*/

	//Get rid of old surface
	//SDL_FreeSurface(textSurface);
	
	//Return success
	return textSurface;
}

void Render::renderGame()
{
	//queue fps counter
	if (_showFPS)
	{
		_time += gameTimer.getDelta();
		_frame++;
		if (_time >= 1000)
		{
			_fps = int((float)_frame / (_time / 1000.f));
			_time = 0;
			_frame = 0;
			printf("%d\n", _fps);
		}
	}


	////Enable vertex and texture coordinate arrays
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	//glTexCoordPointer(2, GL_FLOAT, sizeof(VertexDataColor2D), (GLvoid*)offsetof(VertexDataColor2D, texCoord));
	//glVertexPointer(2, GL_FLOAT, sizeof(VertexDataColor2D), (GLvoid*)offsetof(VertexDataColor2D, position));
	//glColorPointer(4, GL_FLOAT, sizeof(VertexDataColor2D), (GLvoid*)offsetof(VertexDataColor2D, color));

	////Bind vertex buffer
	//glUseProgram(_shaderProgram);
	//glEnableVertexAttribArray(gVertexPos2DLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, mVBOID);
	//glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBOID);

	////Update vertex buffer data
	//glBufferSubData(GL_ARRAY_BUFFER, 0, _currentVertex * sizeof(VertexDataColor2D), _vData);

	////Draw quad using vertex data and index data
	//glDrawElements(GL_QUADS, _currentVertex, GL_UNSIGNED_INT, NULL);

	////opengl
	////delete _vData;
	////_vData = new VertexDataColor2D[MAX_VERTEX];
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glDisableVertexAttribArray(gVertexPos2DLocation);
	//glUseProgram(NULL);

	////Disable vertex and texture coordinate arrays
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT);
	//_shader.setModelView(glm::mat4());
	//_shader.updateModelView();

	//_currentVertex = 0;
}


//
void Render::newTxtTxr(GLuint *txr, std::string text, SDL_Color textColor, int f)
{
	if ((int)text.size() > 0)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = TTF_RenderText_Blended(font[f], text.c_str(), textColor);
		if (loadedSurface == nullptr)
		{
			printf("Unable to create text %s! SDL_image Error: %s\n", text.c_str(), IMG_GetError());
		}
		else
		{
			/*newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if( newTexture == nullptr )
			{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
			}
			else SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);*/

			glGenTextures(1, txr);
			glBindTexture(GL_TEXTURE_2D, *txr);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Unbind texture
			glBindTexture(GL_TEXTURE_2D, NULL);

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
	}
}

void Render::newUniTxtTxr(GLuint *txr, Uint16 textureText, SDL_Color textColor, int f)
{
	//The final texture
	//SDL_Texture *newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = TTF_RenderGlyph_Blended(font[f], textureText, textColor);
	if (loadedSurface == nullptr)
	{
		printf("Unable to create text %s! SDL_image Error: %s\n", "UNICODE", IMG_GetError());
	}
	else
	{
		/*newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == nullptr )
		{
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);*/

		glGenTextures(1, txr);
		glBindTexture(GL_TEXTURE_2D, *txr);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Unbind texture
		glBindTexture(GL_TEXTURE_2D, NULL);

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
}

void Render::newTxtTxr(GLuint *txr)
{
	glGenTextures(1, txr);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, *txr);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 768, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Render::loadTxr(GLuint *txr, std::string path, bool filter)
{
	//The final texture
	//SDL_Texture *newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		glGenTextures(1, txr);
		glBindTexture(GL_TEXTURE_2D, *txr);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h,
					0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexImage2D! %s\n", gluErrorString(error));
		}

		if (filter)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexParameteri %s\n", gluErrorString(error));
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			printf("Error glTexParameteri 2! %s\n", gluErrorString(error));
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
}

void Render::clearTexture(GLuint txr)
{
	/*SDL_SetRenderTarget(renderer, txr);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_NONE);
	SDL_RenderClear(renderer);
	SDL_SetTextureBlendMode(txr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, nullptr);*/
}

void Render::setScreenSize(int w, int h)
{
	if (w < 0) w = SCREEN_WIDTH;
	if (h < 0) h = SCREEN_HEIGHT;
	
	SDL_SetWindowSize(window, w, h);
}

void Render::setFullscreen(bool f)
{
	if (f) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else SDL_SetWindowFullscreen(window, 0);
}

int Render::getScreenWidth()
{
	return SCREEN_WIDTH;
}

int Render::getScreenHeight()
{
	return SCREEN_HEIGHT;
}

fRectangle Render::getScreen()
{
	return fRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

float Render::getWidthRatio()
{
	return WIDTH_RATIO;
}

float Render::getHeightRatio()
{
	return HEIGHT_RATIO;
}

bool Render::getFullscreen()
{
	return FULLSCREEN;
}

void Render::setBaseFrameTime(int t)
{
	BASE_FRAME_TIME = t;
}

int Render::getBaseFrameTime()
{
	return BASE_FRAME_TIME;
}

GLfloat Render::getFontSize(int f)
{
	return (GLfloat)fontSize[f];
}

GLfloat Render::getTextWidth(std::string t, int f)
{
	int tw = 0;
	TTF_SizeText(font[f], t.c_str(), &tw, nullptr);
	return (GLfloat)tw;
}

Shader* Render::getShader()
{
	return &_shader;
}

//void Render::initWorldVBO()
//{
//	//If VBO does not already exist
//	if (_worldVbo == 0)
//	{
//		//Vertex data
//		VertexData2D *vData = new VertexData2D[_numWorldVertices];
//		GLuint *iData = new GLuint[_numWorldVertices];
//
//		//Set rendering indices
//		iData[0] = 0;
//		iData[1] = 1;
//		iData[2] = 2;
//		iData[3] = 3;
//
//		//Create VBO
//		glGenBuffers(1, &_worldVbo);
//		glBindBuffer(GL_ARRAY_BUFFER, _worldVbo);
//		glBufferData(GL_ARRAY_BUFFER, _numWorldVertices * sizeof(VertexData2D), vData, GL_DYNAMIC_DRAW);
//
//		//Create IBO
//		glGenBuffers(1, &_worldIbo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _worldIbo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numWorldVertices * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);
//
//		//Unbind buffers
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//		delete[] vData;
//		delete[] iData;
//	}
//}
//
//void Render::freeWorldVBO()
//{
//	//Free VBO and IBO
//	if (_worldVbo != 0)
//	{
//		glDeleteBuffers(1, &_worldVbo);
//		glDeleteBuffers(1, &_worldIbo);
//		_worldVbo = 0;
//		_worldIbo = 0;
//	}
//}
//
//void Render::initUIVBO()
//{
//	//If VBO does not already exist
//	if (_UIVbo == 0)
//	{
//		//Vertex data
//		VertexData2D *vData = new VertexData2D[_numUIVertices];
//		GLuint *iData = new GLuint[_numUIVertices];
//
//		//Set rendering indices
//		iData[0] = 0;
//		iData[1] = 1;
//		iData[2] = 2;
//		iData[3] = 3;
//
//		//Create VBO
//		glGenBuffers(1, &_UIVbo);
//		glBindBuffer(GL_ARRAY_BUFFER, _UIVbo);
//		glBufferData(GL_ARRAY_BUFFER, _numUIVertices * sizeof(VertexData2D), vData, GL_DYNAMIC_DRAW);
//
//		//Create IBO
//		glGenBuffers(1, &_UIIbo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _UIIbo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numUIVertices * sizeof(GLuint), iData, GL_DYNAMIC_DRAW);
//
//		//Unbind buffers
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//		delete[] vData;
//		delete[] iData;
//	}
//}
//
//void Render::freeUIVBO()
//{
//	//Free VBO and IBO
//	if (_UIVbo != 0)
//	{
//		glDeleteBuffers(1, &_UIVbo);
//		glDeleteBuffers(1, &_UIIbo);
//		_UIVbo = 0;
//		_UIIbo = 0;
//	}
//}

Render *render;

char _buffer[33];
int TILE_WIDTH = 32;
int TILE_HEIGHT = 32;
const int MAX_CHARACTERS = 100;
const int MAX_ENEMIES = 20;
const int MAX_ATTACKS = 1000;
const int TOOLTIP_DELAY = 1000;