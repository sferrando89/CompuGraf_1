#include "InputHandler.h"

InputHandler::InputHandler()
{
	//GameManager* gameManager = GameManager::GetInstance();
	//Camera* camera = Camera::GetInstance();
}

void InputHandler::Handle() {
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//quit = true;
			break;
		}

		if (event.type == SDL_KEYDOWN)
		{
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
			int delta_x = 0;
			int delta_y = 0;
			int x, y;
			SDL_GetMouseState(&x, &y);
			cout << x;
			if (x < previous_x) {
				delta_x = -1;
			}
			else if (x > delta_x) {
				delta_x = 1;
			}

			if (y < previous_y) {
				delta_y = -1;
			}
			else if (y > previous_y) {
				delta_y = 1;
			}
			previous_x = x;
			previous_y = y;
			Camera::GetInstance()->Rotate(delta_x, delta_y);
		}

	}
}