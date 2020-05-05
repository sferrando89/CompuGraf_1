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

	InputHandler* inputHandler = InputHandler::GetInstance();
	GameManager* gameManager = GameManager::GetInstance();
    Settings* settings = Settings::GetInstance();

    LTimer capTimer;

    const int SCREEN_TICKS_PER_FRAME = 1000 / settings->SCREEN_FPS;

    if (!initSDL())
    {
        printf("Unable to initialize SDL \n");
        return 1;
    }

	atexit(SDL_Quit);

    /*
    //Do post window/context creation initialization
    if (!initGL())
    {
        printf("Unable to initialize graphics library!\n");
        return 1;
    }
	
    */
	//bandera que controla el loop principal
    bool quit = false;
    bool skipNextFrame = false;
    
    while (!quit)
    {
        capTimer.restart();
        Player* player = gameManager->getPlayer();

        //cout << getAvgFrames() << endl;
		quit = inputHandler->Handle();

		if (gameManager->CheckWinCondition() ){
			// Gano
			cout << "Partida ganada!";
		}

        if (player->isMoving) {
            player->updatePlayer();
        }
		//Render quad
        if (!skipNextFrame) {
            render();
        }
        skipNextFrame = false;

        int frameTicks = capTimer.getTicks();
        if (frameTicks <= SCREEN_TICKS_PER_FRAME)
        {
            //Wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
        else {
            skipNextFrame = true;
        }
    }

	return 0;
}
