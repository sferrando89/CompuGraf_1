#include "InputHandler.h"

InputHandler* InputHandler::instance = 0;

InputHandler* InputHandler::GetInstance() {
	if (!instance) {
		instance = new InputHandler;
	}
	return instance;
}

InputHandler::InputHandler()
{

}

bool InputHandler::Handle() {

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return true;
		}

		if (event.type == SDL_KEYDOWN)
		{

			if (event.key.keysym.sym == SDLK_q) {
				return true;
			}

			else if (event.key.keysym.sym == SDLK_c)
			{
				settingsOn = !settingsOn;
			}
			
			GameManager::GetInstance()->HandleMovement(event.key.keysym.sym);
			
		}
		if (event.type == SDL_KEYUP)
		{

		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			mousePressed = true;
			SDL_GetMouseState(&previous_x, &previous_y);
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			mousePressed = false;
		}
		if (mousePressed)
		{
			dir_t = 0;
			dir_p = 0;
			int x, y;

			SDL_GetMouseState(&x, &y);

			if (x < previous_x) {
				dir_t = -1;
			}
			else if (x > previous_x) {
				dir_t = 1;
			}
			else
			{
				dir_t = 0;
			}

			if (y < previous_y) {
				dir_p = -1;
			}
			else if (y > previous_y) {
				dir_p = 1;
			}
			else
			{
				dir_p = 0;
			}

			previous_x = x;
			previous_y = y;
		}

		return false;
	}
}