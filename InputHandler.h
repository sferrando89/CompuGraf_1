#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "GameManager.h"
#include "Camera.h"

class InputHandler
{
	private:
		SDL_Event event;
		GameManager* gameManager;
		Camera* camera;
		// Variables para el control del mouse
		bool mousePressed = false;
		int previous_x, previous_y;
	public:
		InputHandler();
		void Handle();
};

