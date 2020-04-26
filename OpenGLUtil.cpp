#include "OpenGLUtil.h"
#include "GameManager.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//OpenGL context
SDL_GLContext gContext;

bool firstdraw = false;

Player player = GameManager::GetInstance()->getPlayer();
Map map = GameManager::GetInstance()->getGameMap();

bool initGL() {
	//Initialize Projection Matrix

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(800, SCREEN_WIDTH / SCREEN_HEIGHT, 0.8, 100);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize Clear Color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	gluLookAt(S_RADIO, 0, 0, player.position_m, player.position_n, player.position_o, 0, 0, 1);

	//Check For Error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Error initializing OpenGL! %s\n");
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
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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

	return true;
}

void update()
{

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < map.size_m; i++) 
	{
		for (int j = 0; j < map.size_n; j++) 
		{
			if (map.GetCubeHeight(j, i) != 0)
			{
				glBegin(GL_QUADS);
				glColor3f(0, 0, 1); // AZUL
				glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
				glVertex3f(j, i, map.GetCubeHeight(j, i));
				glColor3f(0, 1, 0); //VERDE
				glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
				glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
				glColor3f(0, 1, 1); //CELESTE
				glVertex3f(j, i, map.GetCubeHeight(j, i));
				glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
				glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
				glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
				glColor3f(1, 0, 0); //ROJO
				glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
				glColor3f(1, 0, 1); //VIOLETA
				glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
				glVertex3f(j, i, map.GetCubeHeight(j, i));
				glColor3f(1, 1, 0); //MARRON
				glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
				glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
				glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
				glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
				glEnd();
			}			
			
		}
	}
	//Update screen
	SDL_GL_SwapWindow(gWindow);

}