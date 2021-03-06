#include "OpenGLUtil.h"
#include "GameManager.h"
#include "InputHandler.h"
#include "Settings.h"
#include "OBJLoader.h"
#include <iostream> 
#include <string>
#include <sstream>
#include "SDL_image.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//OpenGL context
SDL_GLContext gContext;

// Background related
SDL_Surface* backgrund;
GLuint backgroundTexture;
float rotationAngle = 0;

// Text related
struct _text {
	const char* texto;
	SDL_Color color;
	TTF_Font* font;
	/*~_text(){
		delete[](texto);
	}*/
};
SDL_Surface* intermediary = NULL;
TTF_Font* font;
TTF_Font* fontBig;
TTF_Font* fontSmall;
SDL_Surface* sFont = NULL;
GLuint textTexture;
GLuint* settingsTextTexturesFixed;
SDL_Surface* sLoose;
GLuint* looseTextTextures;
SDL_Surface* sWin;
GLuint* winTextTextures;


SDL_Surface* sScore;
GLuint scoreTexture;
SDL_Surface* sTime;
GLuint timeTexture;

int actualScore = 0;

GLuint* hudTextTexturesFixed = NULL;
_text* hudDynamicText = NULL;

bool firstdraw = false;
int renderedFrames = 0;

GameManager* gamemanager = GameManager::GetInstance();
Map* map = gamemanager->getGameMap();
Settings* settings = Settings::GetInstance();


GLfloat lightPosition0[] = {0, 0, 10, 1};
GLfloat lightPosition1[] = { 8.0 , 8.0 , 0.0, 0.0 };

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

bool initTextTexture() {

	//Initialize font library and font texture
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		return false;
	}
	font = TTF_OpenFont("fonts/pixeldroidBoticRegular.ttf", 40);
	fontSmall = TTF_OpenFont("fonts/pixeldroidBoticRegular.ttf", 20);
	fontBig = TTF_OpenFont("fonts/pixeldroidBoticRegular.ttf", 80);
	std::cout << TTF_GetError() << std::endl;

	SDL_Color color;
	SDL_Surface* intermediary;

	color = { 255, 0, 0 };
	sFont = TTF_RenderText_Solid(font, "Q*ALBER7_", color);
	//SDL_SaveBMP(sFont, "blended.png");

	intermediary = SDL_CreateRGBSurface(0, sFont->w, sFont->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(sFont, 0, intermediary, 0);

	glGenTextures(1, &textTexture);

	// Bindeo la textura para poder usarla en el draw
	// "Paso" la surface con la textura de texto a la de opengl
	glBindTexture(GL_TEXTURE_2D, textTexture);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Error en el bindtexture dentro del render del texto\n");
		//printf((const char*)error);
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);


	error = glGetError();
	if (error != GL_NO_ERROR) {
		// ESTO DE ACA ABAJO ME ROMPIA EL NSIGHT ANDA A SABER POR QUE
		//printf("Error en el TexImage dentro del initTextTexture \n");
		//printf((const char*)error);
		//return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Genero las texturas para los textos fijos
	// Las texturas que se guardan en la estructura son:
	// settingsTextTexturesFixed[0] = Titulo
	// settingsTextTexturesFixed[1] = "Game speed:" No seleccionado
	// settingsTextTexturesFixed[2] = "Game speed:" Seleccionado
	// settingsTextTexturesFixed[3] = "Wireframe: " No seleccionado
	// settingsTextTexturesFixed[4] = "Wireframe: " Seleccionado
	// settingsTextTexturesFixed[5] = "Texturas: " No seleccionado
	// settingsTextTexturesFixed[6] = "Texturas: " Seleccionado
	// settingsTextTexturesFixed[7] = "Interpolado: " No seleccionado
	// settingsTextTexturesFixed[8] = "Interpolado: " Seleccionado
	// settingsTextTexturesFixed[9] = "On" Prendido
	// settingsTextTexturesFixed[10] = "On" Apagado
	// settingsTextTexturesFixed[11] = "Off" Prendido
	// settingsTextTexturesFixed[12] = "Off" Apagado
	// settingsTextTexturesFixed[13] = "Lento" Prendido
	// settingsTextTexturesFixed[14] = "Lento" Apagado
	// settingsTextTexturesFixed[15] = "Rapido" Prendido
	// settingsTextTexturesFixed[16] = "Rapido" Apagado
	// settingsTextTexturesFixed[17] = "Tiempo" 
	// settingsTextTexturesFixed[18] = "Puntaje" 

	int n = 17;
	settingsTextTexturesFixed = new GLuint[n];
	glGenTextures(n, settingsTextTexturesFixed);

	_text* textos = new _text[n];
	textos[0] = { "SETTINGS",		{255,0,0} ,font};
	textos[1] = { "Game speed:",	{0,0,255} ,font };
	textos[2] = { "Game speed:",	{0,255,255} ,font };
	textos[3] = { "Wireframe:",	{0,0,255} ,font };
	textos[4] = { "Wireframe:",	{0,255,255} ,font };
	textos[5] = { "Texturas:",	{0,0,255} ,font };
	textos[6] = { "Texturas:",	{0,255,255} ,font };
	textos[7] = { "Interpolado:",	{0,0,255} ,font };
	textos[8] = { "Interpolado:",	{0,255,255} ,font };
	textos[9] = { "ON",			{255, 255,255} ,font };
	textos[10] = { "ON",			{125, 125,125} ,font };
	textos[11] = { "OFF",			{255, 255,255} ,font };
	textos[12] = { "OFF",			{125, 125,125} ,font };
	textos[13] = { "Lento",		{255, 255,255} ,font };
	textos[14] = { "Lento",		{125, 125,125} ,font };
	textos[15] = { "Rapido",		{255, 255,255} ,font };
	textos[16] = { "Rapido",		{125, 125,125} ,font };

	for (int i = 0; i < n; i++)
	{
		sFont = TTF_RenderText_Solid(textos[i].font, textos[i].texto, textos[i].color);
		intermediary = SDL_CreateRGBSurface(0, sFont->w, sFont->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_BlitSurface(sFont, 0, intermediary, 0);

		glBindTexture(GL_TEXTURE_2D, settingsTextTexturesFixed[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, NULL); // Desbindeo
	}
	
	//Textura del puntaje

	color = { 255, 179, 0};
	std::stringstream temp_str;
	temp_str << (ScoreKeeper::GetInstance()->getScore());
	std::string str = temp_str.str();
	const char* cstr2 = str.c_str();
	sScore = TTF_RenderText_Solid(font, cstr2, color);

	intermediary = SDL_CreateRGBSurface(0, sScore->w, sScore->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(sScore, 0, intermediary, 0);

	glGenTextures(1, &scoreTexture);
	glBindTexture(GL_TEXTURE_2D, scoreTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);
	SDL_FreeSurface(intermediary);

	// "Desbindeo" 
	//glBindTexture(GL_TEXTURE_2D, NULL);

	// Textura del tiempo
	color = { 179, 255, 0 };
	temp_str << (GameManager::GetInstance()->getPlayTime());
	str = temp_str.str();
	cstr2 = str.c_str();
	sTime = TTF_RenderText_Solid(font, cstr2, color);

	intermediary = SDL_CreateRGBSurface(0, sTime->w, sTime->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(sTime, 0, intermediary, 0);

	glGenTextures(1, &timeTexture);
	glBindTexture(GL_TEXTURE_2D, timeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);

	// Texturas de la escena de perdida
	// Las texturas que se guardan en la estructura son:
	// looseTextTextures[0] = "Que paso Q*ALBERT?"
	// looseTextTextures[1] = "Perdiste!!"
	// looseTExtTexture[2] = "Tu puntaje fue"
	// looseTExtTexture[3] = "Para salir presiona"
	// looseTextTexture[4] = "Q"
	// looseTextTexture[5] = "Para volver al menu principal presiona"
	// looseTextTexture[6] = "M"

	SDL_Surface* sLoose;

	n = 7;
	looseTextTextures = new GLuint[n];
	glGenTextures(n, looseTextTextures);

	textos = new _text[n];
	textos[0] = { "Que paso Q*ALBERT?",		{255,230,0} ,font};
	textos[1] = { "PERDISTE!",	{255,0,128} ,fontBig};
	textos[2] = { "Tu puntaje fue ",	{255,255,255} ,font};
	textos[3] = { "Para salir presiona",	{128,128,128} ,fontSmall};
	textos[4] = { "Q",	{255,230,0} ,fontSmall};
	textos[5] = { "Para volver al menu principal presiona",	{128,128,128},fontSmall };
	textos[6] = { "M",	{255,230,0}, fontSmall };

	for (int i = 0; i < n; i++)
	{
		sLoose = TTF_RenderText_Solid(textos[i].font, textos[i].texto, textos[i].color);
		intermediary = SDL_CreateRGBSurface(0, sLoose->w, sLoose->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_BlitSurface(sLoose, 0, intermediary, 0);

		glBindTexture(GL_TEXTURE_2D, looseTextTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, NULL); // Desbindeo
	}

	// Texturas de la escena de perdida
	// Las texturas que se guardan en la estructura son:
	// winTextTextures[0] = "Buena Q*ALBERT"
	// winTextTextures[1] = "GANASTE"
	// winTextTextures[2] = "Para salir presiona"
	// winTextTextures[3] = "Q"
	// winTextTextures[4] = "Para volver al menu principal presiona"
	// winTextTextures[5] = "M"

	SDL_Surface* swIN;

	n = 6;
	winTextTextures = new GLuint[n];
	glGenTextures(n, winTextTextures);

	textos = new _text[n];
	textos[0] = { "Buena Q*ALBERT",		{255,230,0} ,font };
	textos[1] = { "GANASTE",	{255,0,128} ,fontBig };
	textos[2] = { "Para salir presiona",	{128,128,128} ,fontSmall };
	textos[3] = { "Q",	{255,230,0} ,fontSmall };
	textos[4] = { "Para volver al menu principal presiona",	{128,128,128},fontSmall };
	textos[5] = { "M",	{255,230,0}, fontSmall };

	for (int i = 0; i < n; i++)
	{
		sWin = TTF_RenderText_Solid(textos[i].font, textos[i].texto, textos[i].color);
		intermediary = SDL_CreateRGBSurface(0, sWin->w, sWin->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_BlitSurface(sWin, 0, intermediary, 0);

		glBindTexture(GL_TEXTURE_2D, winTextTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, NULL); // Desbindeo
	}

	SDL_FreeSurface(intermediary);

	return true;
}

bool initBackgroundTexture()
{
	SDL_Surface* loadedSurface = IMG_Load("textures/background.png");
	if (loadedSurface == NULL)
	{
		cout << "no cargo la textura\n";
	}

	intermediary = SDL_CreateRGBSurface(0, loadedSurface->w, loadedSurface->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(loadedSurface, 0, intermediary, 0);

	glGenTextures(1, &backgroundTexture);

	// Bindeo la textura para poder usarla en el draw
	// "Paso" la surface con la textura de texto a la de opengl
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		//printf("Error en el bindtexture dentro del init del fondo\n");
		//printf((const char*)error);
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);


	error = glGetError();
	if (error != GL_NO_ERROR) {
		// ESTO DE ACA ABAJO ME ROMPIA EL NSIGHT ANDA A SABER POR QUE
		//printf("Error en el TexImage dentro del initTextTexture \n");
		//printf((const char*)error);
		//return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(intermediary);
	SDL_FreeSurface(loadedSurface);
	glBindTexture(GL_TEXTURE_2D, NULL);

	return true;
}

bool initGL() {
	//Initialize Projection Matrix

	Ficha* player = GameManager::GetInstance()->getPlayer();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(800, SCREEN_WIDTH / SCREEN_HEIGHT, 0.8, 100); // Es necesario hacer esto?

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize Clear Color
	glClearColor(0.f, 0.f, 0.f, 0.f);

	//Add ambient light
	GLfloat ambientColor[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	//glEnable(GL_DEPTH_TEST);

	//Add positioned light
	GLfloat lightColor0[] = { 1.0, 0.6, 0.6, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	//Add directed light
	GLfloat lightColor1[] = { 0.01, 0.01, 0.01, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	//Check For Error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		//printf("Error initializing OpenGL! %s\n");
		return false;
	}

	return true;
}

bool initSDL()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return(false);
	}

	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create window
	gWindow = SDL_CreateWindow("Q*ALBERT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return(false);
	}

	//Create context
	gContext = SDL_GL_CreateContext(gWindow);
	if (gContext == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return(false);
	}

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	//Initialize OpenGL
	if (!initGL())
	{
		printf("Unable to initialize OpenGL!\n");
		return(false);
	}

	if (!initTextTexture())
	{
		printf("Unable to initialize TextTexture!\n");
		return(false);
	}
	
	if (!initBackgroundTexture())
	{
		printf("Unable to initialize BAckgroundTExture!\n");
		return(false);
	}
	
	return true;
}

void updateCamera3d()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (Settings::GetInstance()->cameraMode == CameraModes::isometric)
	{
		float size = GameManager::GetInstance()->getGameMap()->isometricSize;;
		glOrtho(-SCREEN_WIDTH / size,
			SCREEN_WIDTH / size,
			-SCREEN_HEIGHT / size,
			SCREEN_HEIGHT / size,
			-100, 100);
		
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);

	}
	else
	{
		gluPerspective(800, SCREEN_WIDTH / SCREEN_HEIGHT, 0.8, 100);

		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (InputHandler::GetInstance()->mousePressed 
		&& Settings::GetInstance()->cameraMode == CameraModes::free)
	{
		Camera::GetInstance()->Rotate(InputHandler::GetInstance()->dir_t,
			InputHandler::GetInstance()->dir_p);

		// feo feo, pero arregla el bug de que se quede
		// girando a pesar de que el mouse se quedo quieto
		InputHandler::GetInstance()->dir_t = 0;
		InputHandler::GetInstance()->dir_p = 0;

	}
	Camera::GetInstance()->apply();

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);

}

void renderMap()
{
	map = GameManager::GetInstance()->getGameMap();

	for (int i = 0; i < map->size_m; i++)
	{
		for (int j = 0; j < map->size_n; j++)
		{
			if (map->GetCubeHeight(j, i) != 0) {
				// varValues[1] = wireframe mode on
				if (!settings->varValues[1]) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glBegin(GL_QUADS);

					if (map->isCubePainted(j, i))
						glColor3f(0, 0, 1);
					else
						glColor3f(0, 1, 1);

					//UP
					glNormal3f(j, i, map->GetCubeHeight(j, i));
					glVertex3f(j, i, map->GetCubeHeight(j, i));
					glNormal3f(j + 1, i, map->GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map->GetCubeHeight(j, i));
					glNormal3f(j + 1, i + 1, map->GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i));
					glNormal3f(j, i + 1, map->GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map->GetCubeHeight(j, i));

					//FRONT
					glColor3f(0, 0, 0);
					glNormal3f(j, i, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j, i, map->GetCubeHeight(j, i) - 1);
					glNormal3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
					glColor3f(1, 0, 0);
					glNormal3f(j + 1, i, map->GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map->GetCubeHeight(j, i));
					glNormal3f(j, i, map->GetCubeHeight(j, i));
					glVertex3f(j, i, map->GetCubeHeight(j, i));

					//RIGHT
					glColor3f(0, 0, 0);
					glNormal3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
					glNormal3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
					glColor3f(1, 0, 0);
					glNormal3f(j + 1, i + 1, map->GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i));
					glNormal3f(j + 1, i, map->GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map->GetCubeHeight(j, i));					

					//DOWN
					glColor3f(0, 0, 1);
					glNormal3f(j, i, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j, i, map->GetCubeHeight(j, i) - 1);
					glColor3f(1, 0, 0);
					glNormal3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
					glColor3f(0, 0, 1);
					glNormal3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
					glColor3f(1, 0, 0);
					glNormal3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map->GetCubeHeight(j, i) - 1);

					//LEFT
					glColor3f(0, 0, 0);
					glNormal3f(j, i, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j, i, map->GetCubeHeight(j, i) - 1);
					glColor3f(1, 0, 0);
					glNormal3f(j, i, map->GetCubeHeight(j, i));
					glVertex3f(j, i, map->GetCubeHeight(j, i));					
					glNormal3f(j, i + 1, map->GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map->GetCubeHeight(j, i));
					glColor3f(0, 0, 0);
					glNormal3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map->GetCubeHeight(j, i) - 1);

					//BACK
					glColor3f(0, 0, 0);
					glNormal3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
					glColor3f(1, 0, 0);
					glNormal3f(j, i + 1, map->GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map->GetCubeHeight(j, i));
					glNormal3f(j + 1, i + 1, map->GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i));
					glColor3f(0, 0, 0);
					glNormal3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);

					glEnd();
				}
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBegin(GL_QUADS);

				if (!settings->varValues[1]) {
					glColor3f(0, 0, 0);
				}
				else {
					if (map->isCubePainted(j, i)) {
						glColor3f(0, 0, 1);
					}
					else {
						glColor3f(1, 1, 1);
						
					}
				}

				//FRONT
				glVertex3f(j, i, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i, map->GetCubeHeight(j, i));
				glVertex3f(j, i, map->GetCubeHeight(j, i));

				//RIGHT
				glVertex3f(j + 1, i, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i));
				glVertex3f(j + 1, i, map->GetCubeHeight(j, i));

				//UP
				glVertex3f(j, i, map->GetCubeHeight(j, i));
				glVertex3f(j + 1, i, map->GetCubeHeight(j, i));
				glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i));
				glVertex3f(j, i + 1, map->GetCubeHeight(j, i));

				//DOWN
				glVertex3f(j, i, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i, map->GetCubeHeight(j, i) - 1);

				//LEFT
				glVertex3f(j, i, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j, i, map->GetCubeHeight(j, i));
				glVertex3f(j, i + 1, map->GetCubeHeight(j, i));
				glVertex3f(j, i + 1, map->GetCubeHeight(j, i) - 1);

				//BACK
				glVertex3f(j, i + 1, map->GetCubeHeight(j, i) - 1);
				glVertex3f(j, i + 1, map->GetCubeHeight(j, i));
				glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i));
				glVertex3f(j + 1, i + 1, map->GetCubeHeight(j, i) - 1);

				glEnd();
			}

		}
	}

}

void renderPlayer()
{
	Player* player = GameManager::GetInstance()->getPlayer();
	Map* map = GameManager::GetInstance()->getGameMap();

	int currX = player->currentPosition.x;
	int currY = player->currentPosition.y;

	int oldX = player->oldPosition.x;
	int oldY = player->oldPosition.y;

	if (!GameManager::GetInstance()->looseCondition && !GameManager::GetInstance()->winCondition)
	{
		if (player->isMoving) {


			float distanceDone = player->percentageTraveled;

			float traveledY = ((currY - oldY) * distanceDone);
			float traveledX = ((currX - oldX) * distanceDone);
			float traveledZ;

			if (map->GetCubeHeight(currX, currY) == map->GetCubeHeight(oldX, oldY))
				traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone);
			else if (map->GetCubeHeight(currX, currY) > map->GetCubeHeight(oldX, oldY))
				traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone) - 1;
			else
				traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone) + 1;

			if (!settings->varValues[1])
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


			glPushMatrix();

			glTranslatef(oldX + traveledX + 0.5, oldY + traveledY + 0.5, traveledZ);

			if (player->direction == Direction::up)
				glRotatef(90, 0, 0, 1);

			if (player->direction == Direction::down)
				glRotatef(-90, 0, 0, 1);

			if (player->direction == Direction::left)
				glRotatef(180, 0, 0, 1);

			glTranslatef(-0.5, -0.5, 0);

			player->draw();

			glPopMatrix();

			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);

		}
		else {

			if (!settings->varValues[1])
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glPushMatrix();

			glTranslatef(currX + 0.5, currY + 0.5, 0);

			if (player->direction == Direction::up)
				glRotatef(90, 0, 0, 1);

			if (player->direction == Direction::down)
				glRotatef(-90, 0, 0, 1);

			if (player->direction == Direction::left)
				glRotatef(180, 0, 0, 1);

			glTranslatef(-0.5, -0.5, 0);

			player->draw();

			glPopMatrix();

		}
	}
	else
	{
		if (!settings->varValues[1])
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glPushMatrix();

		glTranslatef(currX + 0.5, currY + 0.5, 0);

		glRotatef(45, 0, 0, 1);

		glTranslatef(-0.5, -0.5, 0);

		player->draw();
		if (GameManager::GetInstance()->looseCondition)
		{
			glRotatef(90, 0, 0, 1);
			glTranslatef(0.5, -1, 0.5);
			player->drawBalloon();
		}
		
		glPopMatrix();


		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);


	}
	
}

void renderEnemy()
{
	list<Ficha*>* enemy = GameManager::GetInstance()->getEnemies();
	list<Ficha*>::iterator iterEnemy;

	for (iterEnemy = enemy->begin(); iterEnemy != enemy->end(); ++iterEnemy) 
	{
		int currX = (*iterEnemy)->currentPosition.x;
		int currY = (*iterEnemy)->currentPosition.y;

		int oldX = (*iterEnemy)->oldPosition.x;
		int oldY = (*iterEnemy)->oldPosition.y;
		if (!GameManager::GetInstance()->looseCondition && !GameManager::GetInstance()->winCondition)
		{
			if ((*iterEnemy)->isMoving) {

				float distanceDone = (*iterEnemy)->percentageTraveled;

				float traveledY = ((currY - oldY) * distanceDone);
				float traveledX = ((currX - oldX) * distanceDone);
				float traveledZ;

				if (map->GetCubeHeight(currX, currY) == map->GetCubeHeight(oldX, oldY))
					traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone);
				else if (map->GetCubeHeight(currX, currY) > map->GetCubeHeight(oldX, oldY))
					traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone) - 1;
				else
					traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone) + 1;

				if (!settings->varValues[1])
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				glPushMatrix();

				glTranslatef(oldX + traveledX + 0.5, oldY + traveledY + 0.5, traveledZ);

				if ((*iterEnemy)->direction == Direction::up)
					glRotatef(90, 0, 0, 1);

				if ((*iterEnemy)->direction == Direction::down)
					glRotatef(-90, 0, 0, 1);

				if ((*iterEnemy)->direction == Direction::left)
					glRotatef(180, 0, 0, 1);

				glTranslatef(-0.5, -0.5, 0);

				dynamic_cast<Enemy*>(*iterEnemy)->draw();

				glPopMatrix();

			}
			else
			{

				if (!settings->varValues[1])
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				glPushMatrix();

				glTranslatef(currX + 0.5, currY + 0.5, 0);

				if ((*iterEnemy)->direction == Direction::up)
					glRotatef(90, 0, 0, 1);

				if ((*iterEnemy)->direction == Direction::down)
					glRotatef(-90, 0, 0, 1);

				if ((*iterEnemy)->direction == Direction::left)
					glRotatef(180, 0, 0, 1);

				glTranslatef(-0.5, -0.5, 0);

				dynamic_cast<Enemy*>(*iterEnemy)->draw();

				glPopMatrix();


				glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
				glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);


			}

		}
		else
		{
			float distanceDone = (*iterEnemy)->percentageTraveled;

			float traveledY = ((currY - oldY) * distanceDone);
			float traveledX = ((currX - oldX) * distanceDone);
			float traveledZ;

			if (map->GetCubeHeight(currX, currY) == map->GetCubeHeight(oldX, oldY))
				traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone);
			else if (map->GetCubeHeight(currX, currY) > map->GetCubeHeight(oldX, oldY))
				traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone) - 1;
			else
				traveledZ = ((map->GetCubeHeight(currX, currY) - map->GetCubeHeight(oldX, oldY)) * distanceDone) + 1;

			if (!settings->varValues[1])
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glPushMatrix();

			glTranslatef(oldX + traveledX + 0.6 , oldY + traveledY +0.6, traveledZ + 0.5);

			glTranslatef(-0.5, -0.5, 0);

			dynamic_cast<Enemy*>(*iterEnemy)->drawDeath();

			glPopMatrix();

			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
		}
		
	}
}

void renderTextTexture(GLuint texture, int x, int y)
{
	int z = 0;
	int w = 0;
	int h = 0;

	glEnable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	z = 0;

	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x, y, z);
	glTexCoord2f(1, 0); glVertex3f(x + w, y, z);
	glTexCoord2f(1, 1); glVertex3f(x + w, y + h, z);
	glTexCoord2f(0, 1); glVertex3f(x, y + h, z);
	glEnd();

	// "Desbindeo"
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void setScoreTexture(int newScore)
{
	SDL_Color color = { 255, 179, 0};

	std::stringstream temp_str;
	temp_str << (newScore);
	std::string str = temp_str.str();
	const char* cstr2 = str.c_str();
	sScore = TTF_RenderText_Solid(font, cstr2, color);

	SDL_Surface* intermediary = SDL_CreateRGBSurface(0, sScore->w, sScore->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(sScore, 0, intermediary, 0);

	glBindTexture(GL_TEXTURE_2D, scoreTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);
	SDL_FreeSurface(intermediary);
}

void setTimeTexture(Uint32 newTime)
{
	SDL_Color color = { 179, 255, 0};

	std::stringstream temp_str;
	temp_str << (newTime);
	std::string str = temp_str.str();
	const char* cstr2 = str.c_str();

	sTime = TTF_RenderText_Solid(font, cstr2, color);

	SDL_Surface* intermediary = SDL_CreateRGBSurface(0, sTime->w, sTime->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(sTime, 0, intermediary, 0);

	glBindTexture(GL_TEXTURE_2D, timeTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, intermediary->w, intermediary->h, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);
	SDL_FreeSurface(intermediary);
	SDL_FreeSurface(sTime);
}

void renderHud()
{
	if (GameManager::GetInstance()->winCondition)
	{
		renderTextTexture(winTextTextures[0], SCREEN_WIDTH / 3, 10);

		renderTextTexture(winTextTextures[1], 30 , 60);
		renderTextTexture(winTextTextures[1], 30, 90);
		renderTextTexture(winTextTextures[1], 30, 120);
		renderTextTexture(winTextTextures[1], 30, 150);

		renderTextTexture(winTextTextures[2], SCREEN_WIDTH / 3, 400);
		renderTextTexture(winTextTextures[3], SCREEN_WIDTH / 1.8, 400);
		//renderTextTexture(looseTextTextures[5], SCREEN_WIDTH / 3, 450);
		//renderTextTexture(looseTextTextures[6], SCREEN_WIDTH / 2 + 300, 450);
	}
	else if (GameManager::GetInstance()->looseCondition)
	{
		// Texturas de la escena de perdida
		// Las texturas que se guardan en la estructura son:
		// looseTextTextures[0] = "Que paso Q*ALBERT?"
		// looseTextTextures[1] = "Perdiste!!"
		// looseTExtTexture[2] = "Tu puntaje fue"
		// looseTExtTexture[3] = "Para salir presiona"
		// looseTextTexture[4] = "Q"
		// looseTextTexture[5] = "Para volver al menu principal presiona"
		// looseTextTexture[6] = "M"
		renderTextTexture(looseTextTextures[0], SCREEN_WIDTH / 3, 10);
		renderTextTexture(looseTextTextures[1], SCREEN_WIDTH / 5, 60);
		renderTextTexture(looseTextTextures[1], SCREEN_WIDTH /2, 50);
		renderTextTexture(looseTextTextures[2], SCREEN_WIDTH / 2, 100);

		renderTextTexture(scoreTexture, SCREEN_WIDTH /2 + 110, 130);

		renderTextTexture(looseTextTextures[3], SCREEN_WIDTH / 3, 400);
		renderTextTexture(looseTextTextures[4], SCREEN_WIDTH / 1.8, 400);
		//renderTextTexture(looseTextTextures[5], SCREEN_WIDTH / 3, 450);
		//renderTextTexture(looseTextTextures[6], SCREEN_WIDTH / 2 + 300, 450);
	}
	else
	{
		float z = 0.5;

		glColor3f(1.0f, 0.0f, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_QUADS);

		glVertex3f(10.0, 10.0, z);
		glVertex3f(10.0, 100.0, z);
		glVertex3f(100.0, 100.0, z);
		glVertex3f(100.0, 10.0, z);


		glEnd();

		if (actualScore != ScoreKeeper::GetInstance()->getScore())
		{
			setScoreTexture(ScoreKeeper::GetInstance()->getScore());
		}

		renderTextTexture(scoreTexture, SCREEN_WIDTH - 40, 10);

		setTimeTexture(max(0, (int)floor(TOTAL_GAME_TIME - (GameManager::GetInstance()->getPlayTime() / 1000))));

		renderTextTexture(timeTexture, SCREEN_WIDTH / 2, 10);
	}
	
}

void renderSettings()
{
	renderTextTexture(settingsTextTexturesFixed[0], 30, 0);

	if (settings->settingSelected == 1) {
		renderTextTexture(settingsTextTexturesFixed[2], 30, 30);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[1], 30, 30);
	}
	// varValues[0] = velocidad lenta
	if (settings->varValues[0]) {
		renderTextTexture(settingsTextTexturesFixed[13], 300, 30);
		renderTextTexture(settingsTextTexturesFixed[16], 420, 30);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[14], 300, 30);
		renderTextTexture(settingsTextTexturesFixed[15], 420, 30);
	}

	if (settings->settingSelected == 2) {
		renderTextTexture(settingsTextTexturesFixed[4], 30, 70);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[3], 30, 70);
	}

	// varValues[1] = wireframe mode on
	if (settings->varValues[1]) {
		renderTextTexture(settingsTextTexturesFixed[9], 300, 70);
		renderTextTexture(settingsTextTexturesFixed[12], 350, 70);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[10], 300, 70);
		renderTextTexture(settingsTextTexturesFixed[11], 350, 70);
	}

	if (settings->settingSelected == 3) {
		renderTextTexture(settingsTextTexturesFixed[6], 30, 110);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[5], 30, 110);
	}

	// varValues[2] = texturas
	if (settings->varValues[2]) {
		renderTextTexture(settingsTextTexturesFixed[9], 300, 110);
		renderTextTexture(settingsTextTexturesFixed[12], 350, 110);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[10], 300, 110);
		renderTextTexture(settingsTextTexturesFixed[11], 350, 110);
	}

	if (settings->settingSelected == 4) {
		renderTextTexture(settingsTextTexturesFixed[8], 30, 150);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[7], 30, 150);
	}

	// varValues[3] = interpolado/facetado
	if (settings->varValues[3]) {
		renderTextTexture(settingsTextTexturesFixed[9], 300, 150);
		renderTextTexture(settingsTextTexturesFixed[12], 350, 150);
	}
	else
	{
		renderTextTexture(settingsTextTexturesFixed[10], 300, 150);
		renderTextTexture(settingsTextTexturesFixed[11], 350, 150);
	}
}

void renderBackground()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 10000);

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Traslado el objeto al 0,0
	glTranslatef(400,
		400,
		0);

	// Lo roto
	rotationAngle += 0.1;
	glRotatef(rotationAngle,
		0,
		0,
		1);

	// Traslado el objeto para que quede centrado en la pantalla
	glTranslatef(-600,
		-600,
		0);

	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glEnable(GL_TEXTURE_2D);
	int z = 1;

	//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
	//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, z);
	glTexCoord2f(1, 0); glVertex3f(1200, 0, z);
	glTexCoord2f(1, 1); glVertex3f(1200, 1200, z);
	glTexCoord2f(0, 1); glVertex3f(0, 1200, z);
	glEnd();

	// "Desbindeo"
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisable(GL_TEXTURE_2D);

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}


int render()
{
	//Prendo o apago el interpolado
	if (settings->varValues[3])
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	//Clean Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Modificaci? del color de la luz ambiente seg?n input
	GLfloat ambientColor[4] = { 0.5, 0.5, 0.5, 1.0 };

	if (settings->lightColor == lightColors::red) {
		ambientColor[0] = 1.0;
		ambientColor[1] = 0.0;
		ambientColor[2] = 0.0;
	}
	else if (settings->lightColor == lightColors::blue)
	{
		ambientColor[0] = 0.0;
		ambientColor[1] = 0.0;
		ambientColor[2] = 1.0;
	}
	else if (settings->lightColor == lightColors::green)
	{
		ambientColor[0] = 0.0;
		ambientColor[1] = 1.0;
		ambientColor[2] = 0.0;
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	if (settings->lightDirection == 1)
	{
		lightPosition1[0] = 0.0;
		lightPosition1[1] = 8.0;
	}
	else
	{
		lightPosition1[1] = 0.0;
		lightPosition1[0] = 8.0;
	}

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	
	// Dibujado de objetos 2d (Background)
	if (Settings::GetInstance()->varValues[2])
	{
		renderBackground();
	}

	//Dibujado de objetos 3D
	updateCamera3d();

	renderMap();

	renderPlayer();

	renderEnemy();

	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	//Dibujado de objetos 2D (HUD)
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 100000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Desactivo el depth_test para que el hud se dibuje por delante
	//glDisable(GL_DEPTH_TEST);

	if (InputHandler::GetInstance()->settingsOn && !GameManager::GetInstance()->looseCondition)
	{
		renderSettings();
	}
	else
	{
		renderHud();
	}

	glEnable(GL_LIGHTING);

	glFlush();
	//Update screen
	SDL_GL_SwapWindow(gWindow);

	renderedFrames++;
	return renderedFrames;
}

Uint32 getAvgFrames() {
	GameManager* gamemanager = GameManager::GetInstance();
	Uint32 avgFPS = renderedFrames / (gamemanager->getPlayTime() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	return avgFPS;
}