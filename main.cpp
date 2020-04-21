#include "OpenGLUtil.h"
#include <iostream>
#include <cmath>

#ifdef main
#undef main
#endif


using namespace std;

int main(int argc[], char* args[]) {

    if (!initSDL())
    {
        printf("Unable to initialize SDL \n");
        return 1;
    }

	atexit(SDL_Quit);

    //Do post window/context creation initialization
    if (!initGL())
    {
        printf("Unable to initialize graphics library!\n");
        return 1;
    }
	
	float delta = M_PI / 90;

	//coordenadas esfericas:
	float x = 0;
	float y = 0;
	float z = 0;

	float r = S_RADIO;
	float phi = M_PI/4;
	float theeta = M_PI/4;

	//bandera que controla el loop principal
    bool quit = false;

    SDL_Event evento;

    while (!quit)
    {

		/* Control de eventos */
        while (SDL_PollEvent(&evento))
        {
			if (evento.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			if (evento.type == SDL_KEYDOWN)
			{
				/* Check the SDLKey values and move change the coords */
				switch (evento.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_LEFT:
						theeta -= delta;
						break;
					case SDLK_RIGHT:
						theeta += delta;
						break;
					case SDLK_UP:
						phi += delta;
						break;
					case SDLK_DOWN:
						phi -= delta;
						break;
					}
					break;
			}
			if (evento.type == SDL_KEYUP)
			{
				switch (evento.key.keysym.sym)
				{
					case SDLK_LEFT:
						break;
					case SDLK_RIGHT:
						break;
					case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
				}
				break;

			}
            
		}

		if (theeta >= 2 * M_PI)
			theeta = 0;
		if (phi > M_PI)
			phi = 0;


		x = r * sin(theeta) * sin(phi);
		y = r * cos(phi);
		z = r * cos(theeta) * sin(phi);

		glLoadIdentity();
		gluLookAt(x, y, z, 0, -10, 0, 0, 1, 0);

		//Render quad
		render();
		
    }


	return 0;
}