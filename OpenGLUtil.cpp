#include "OpenGLUtil.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//OpenGL context
SDL_GLContext gContext;

bool firstdraw = false;

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
	gluLookAt(0, 0, S_RADIO, 0, -10, 0, 0, 1, 0);

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

	float tamañoCubo = 2;
	float cantidadCubos = 1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render Quad
	for (int j = 0; j < 7; j++)
	{
		cantidadCubos = j + 1;
		for (int i = 0; i < cantidadCubos; i++)
		{
			glBegin(GL_QUADS);
			glColor3f(0, 0, 1); //AZUL
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // top left
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // bottom left
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // bottom right
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // top right 
			glColor3f(0, 1, 0); //VERDE
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, 0 + i * tamañoCubo); // top left
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, 0 + i * tamañoCubo); // bottom left
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// bottom right
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// top right 
			glColor3f(0, 1, 1); //CELESTE
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// top left
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// bottom left
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// bottom right
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// top right 
			glColor3f(1, 0, 0); //ROJO
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// top left
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// bottom left
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // bottom right
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // top right
			glColor3f(1, 0, 1); //VIOLETA
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// top left
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // bottom left
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // bottom right
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, 1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// top right
			glColor3f(1, 1, 0); //VIOLETA
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // top left
			glVertex3f(-1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// bottom left
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, -2.0f + i * tamañoCubo);// bottom right
			glVertex3f(1 + i * tamañoCubo - j * tamañoCubo, -1.0f - j * tamañoCubo, 0.0f + i * tamañoCubo); // top right
			glEnd();
		}
	}

	//Update screen
	SDL_GL_SwapWindow(gWindow);

}