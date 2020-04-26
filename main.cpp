#include "OpenGLUtil.h"
#include "GameManager.h"
#include "InputHandler.h"
#include <iostream>
#include <cmath>

#ifdef main
#undef main
#endif


using namespace std;

int main(int argc[], char* args[]) {

	InputHandler inputHandler = InputHandler();
	GameManager* gameManager = GameManager::GetInstance();

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
	
	//bandera que controla el loop principal
    bool quit = false;

    while (!quit)
    {

		quit = inputHandler.Handle();

		if (gameManager->CheckWinCondition() ){
			// Gano
			cout << "Partida ganada!";
		}

		//Render quad
		render();
		
    }

	return 0;
}