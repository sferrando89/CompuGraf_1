#include "OpenGLUtil.h"
#include "GameManager.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//OpenGL context
SDL_GLContext gContext;

bool firstdraw = false;

Map map = GameManager::GetInstance()->getGameMap();

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

bool initGL() {
	//Initialize Projection Matrix

	Player player = GameManager::GetInstance()->getPlayer();

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

void renderMap()
{
	for (int i = 0; i < map.size_m; i++) 
	{
		for (int j = 0; j < map.size_n; j++) 
		{
			if (map.GetCubeHeight(j, i) != 0)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_QUADS);
					glColor3f(1, 0, 0); // AZUL
					//FRONT
					glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
					glVertex3f(j, i, map.GetCubeHeight(j, i));

					//RIGHT
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i));

					if (map.isCubePainted(j,i))
						glColor3f(0, 0, 1);
					else
						glColor3f(0, 1, 1);
					
					//UP
					glVertex3f(j, i, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
					
					//DOWN
					glColor3f(0, 1, 0); 
					glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
					
					glColor3f(1, 0, 0); 
					
					//LEFT
					glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j, i, map.GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
					
					//BACK
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);

				glEnd();
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glBegin(GL_QUADS);
					
					glColor3f(0, 0, 0);
					
					//FRONT
					glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
					glVertex3f(j, i, map.GetCubeHeight(j, i));

					//RIGHT
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i));

					//UP
					glVertex3f(j, i, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i));

					//DOWN
					glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j + 1, i, map.GetCubeHeight(j, i) - 1);

					//LEFT
					glVertex3f(j, i, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j, i, map.GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);

					//BACK
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i) - 1);
					glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
					glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) - 1);

				glEnd();
			}			
			
		}
	}

}


void renderPlayer()
{
	Player player = GameManager::GetInstance()->getPlayer();

	cout << player.position_m << "\n";
	cout << player.position_n << "\n";
	cout << player.direction << "\n";
	cout << "----------------" << "\n";

	int j = player.position_m;
	int i = player.position_n;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);

		//UP
		glVertex3f(j, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i) + 1);

		//DOWN
		glVertex3f(j, i, map.GetCubeHeight(j, i));
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i));

		if (player.direction == Direction::up)
			glColor3f(0, 1, 0);

		//FRONT
		glVertex3f(j, i, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i, map.GetCubeHeight(j, i) + 1);

		glColor3f(1, 1, 1);

		if (player.direction == Direction::right)
			glColor3f(0, 1, 0);
			
		
		//LEFT
		glVertex3f(j, i, map.GetCubeHeight(j, i));
		glVertex3f(j, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i));

		glColor3f(1, 1, 1);

		if (player.direction == Direction::left)
			glColor3f(0, 1, 0);
		
		//RIGHT
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i) + 1);

		glColor3f(1, 1, 1);

		if (player.direction == Direction::down)
			glColor3f(0, 1, 0);
			
		//BACK
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));

	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);

		glColor3f(0, 0, 0);

		//UP
		glVertex3f(j, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i) + 1);

		//DOWN
		glVertex3f(j, i, map.GetCubeHeight(j, i));
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i));

		//FRONT
		glVertex3f(j, i, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i, map.GetCubeHeight(j, i) + 1);

		//LEFT
		glVertex3f(j, i, map.GetCubeHeight(j, i));
		glVertex3f(j, i, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i));

		//RIGHT
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i, map.GetCubeHeight(j, i) + 1);

		//BACK
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i));
		glVertex3f(j, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i) + 1);
		glVertex3f(j + 1, i + 1, map.GetCubeHeight(j, i));

	glEnd();
}

void renderEnemy()
{
}


void render()
{
	//Clean Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderMap();
	renderPlayer();
	renderEnemy();

	//Update screen
	SDL_GL_SwapWindow(gWindow);
}