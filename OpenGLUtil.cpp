#include "OpenGLUtil.h"
#include "GameManager.h"
#include "InputHandler.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//OpenGL context
SDL_GLContext gContext;

TTF_Font* font;

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
	gluLookAt(S_RADIO, 0, 0, player.position_x, player.position_y, player.position_z, 0, 0, 1);

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

	//Initialize font library
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		return false;
	}
	font = TTF_OpenFont("fonts/pixeldroidBoticRegular.ttf", 16);
	std::cout << TTF_GetError() << std::endl;

	return true;
}

void update()
{

}

void updateCamera2d()
{
}

void updateCamera3d()
{
	if (InputHandler::GetInstance()->mousePressed)
	{
		Camera::GetInstance()->Rotate(InputHandler::GetInstance()->dir_t, 
										InputHandler::GetInstance()->dir_p);

	}
	Camera::GetInstance()->apply();
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

	//cout << player.position_m << "\n";
	//cout << player.position_n << "\n";
	//cout << player.direction << "\n";
	//cout << "----------------" << "\n";

	int j = player.position_x;
	int i = player.position_y;
	
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

void renderText()
{

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SDL_Color color = { 255, 0, 0};

	SDL_Surface* sFont = TTF_RenderText_Blended(font, "holaaaaaa", color);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

	int x = 0;
	int y = 0;

	glBegin(GL_QUADS);
	
		glTexCoord2f(0, 0); glVertex2f(0.0, 0.0);
		glTexCoord2f(1, 0); glVertex2f(100.0, 0.0);
		glTexCoord2f(1, 1); glVertex2f(100.0, 50.0);
		glTexCoord2f(0, 1); glVertex2f(0.0, 50.0);
	
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 0.0);
	glVertex2f(100.0, 50.0);
	glVertex2f(0.0, 50.0);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);


}

void renderHud()
{
	
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(100.0, 0.0);
	glVertex2f(100.0, 50.0);
	glVertex2f(0.0, 50.0);
	glEnd();

}

void render()
{
	//Clean Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Dibujado de objetos 3D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(800, SCREEN_WIDTH / SCREEN_HEIGHT, 0.8, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCamera3d();

	renderMap();
	renderPlayer();
	renderEnemy();

	//Dibujado de objetos 2D (HUD)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Desactivo el depth_test para que el hud se dibuje por delante
	glDisable(GL_DEPTH_TEST);

	if (InputHandler::GetInstance()->settingsOn)
	{
		renderText();
	}
	else
	{
		renderHud();
	}

	glEnable(GL_DEPTH_TEST);
	//Update screen
	SDL_GL_SwapWindow(gWindow);
}