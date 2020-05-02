#include "OpenGLUtil.h"
#include "GameManager.h"
#include "InputHandler.h"


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//OpenGL context
SDL_GLContext gContext;

// Text related
TTF_Font* font;
SDL_Surface* sFont;
GLuint textTexture;


bool firstdraw = false;

Map map = GameManager::GetInstance()->getGameMap();

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
	std::cout << TTF_GetError() << std::endl;

	SDL_Color color = { 255, 0, 0};
	sFont = TTF_RenderText_Solid(font, "Q*ALBER7_", color);
	//SDL_SaveBMP(sFont, "blended.png");

	SDL_Surface* intermediary = SDL_CreateRGBSurface(0, sFont->w, sFont->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(sFont, 0, intermediary, 0);
	// Genero la textura para el texto
	glGenTextures(1, &textTexture);

	// Set the texture's stretching properties



	// Bindeo la textura para poder usarla en el draw
	// "Paso" la surface con la textura de texto a la de opengl
	GLint  nbOfColors;
	GLenum texture_format = 0;
	nbOfColors = sFont->format->BytesPerPixel;

	switch (nbOfColors) {
	case 1:
		texture_format = GL_ALPHA;
		break;
	case 3:     // no alpha channel
		if (sFont->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
		break;
	case 4:     // contains an alpha channel
		if (sFont->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
		break;
	default:
		cout << "Warning: the image is not truecolor...";
		break;
	}

	glBindTexture(GL_TEXTURE_2D, textTexture);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("Error en el bindtexture dentro del render del texto\n");
		printf((const char*)error);
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

	// "Desbindeo" 
	glBindTexture(GL_TEXTURE_2D, NULL);
	
	return true;
}

bool initGL() {
	//Initialize Projection Matrix

	Player player = GameManager::GetInstance()->getPlayer();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(800, SCREEN_WIDTH / SCREEN_HEIGHT, 0.8, 100); // Es necesario hacer esto?

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize Clear Color
	glClearColor(0.f, 0.f, 0.f, 0.f);

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

	if (!initTextTexture())
	{
		printf("Unable to initialize TextTexture!\n");
		return(false);
	}

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
	map = GameManager::GetInstance()->getGameMap();

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

int next_pow2(int num) {
	int p2 = 1;
	while (p2 < num) p2 <<= 1;
	return p2;
}

void renderTextTexture(GLuint texture)
{
	int x = 0;
	int y = 0;
	int z = 0;

	glEnable(GL_BLEND);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	z = 0;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(0, 0, z);
		glTexCoord2f(1, 0); glVertex3f(100, 0, z);
		glTexCoord2f(1, 1); glVertex3f(100, 50, z);
		glTexCoord2f(0, 1); glVertex3f(0, 50, z);
	glEnd();

	// "Desbindeo"
	glBindTexture(GL_TEXTURE_2D, NULL);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

}

void renderHud()
{

	float z = 0.5;

	glColor3f(1.0f, 0.0f, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	
	glVertex3f(10.0, 10.0,z);
	glVertex3f(10.0, 100.0,z);
	glVertex3f(100.0, 100.0,z);
	glVertex3f(100.0, 10.0,z);
	
	
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
		renderTextTexture(textTexture);
	}
	else
	{
		renderHud();
	}


	glEnable(GL_DEPTH_TEST);
	//Update screen
	SDL_GL_SwapWindow(gWindow);
}