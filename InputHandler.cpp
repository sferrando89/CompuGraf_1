#include "InputHandler.h"

InputHandler::InputHandler()
{
	//GameManager* gameManager = GameManager::GetInstance();
	//Camera* camera = Camera::GetInstance();
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
			int dir_t = 0;
			int dir_p = 0;
			int x, y;

			SDL_GetMouseState(&x, &y);
			
			if (x < previous_x) {
				dir_t = -1;
			}
			else if (x > dir_t) {
				dir_t = 1;
			}

			if (y < previous_y) {
				dir_p = -1;
			}
			else if (y > previous_y) {
				dir_p = 1;
			}
			previous_x = x;
			previous_y = y;
			Camera::GetInstance()->Rotate(dir_t, dir_p);
		}

		return false;
	}
}