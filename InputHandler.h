#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "GameManager.h"
#include "Camera.h"

class InputHandler
{
	private:
		static InputHandler* instance;
		InputHandler();
		SDL_Event event;
		GameManager* gameManager;
		Camera* camera;
		// Variables para el control del mouse
		int previous_x, previous_y;

	public:
		static InputHandler* GetInstance();

		//Para el control del mouse
		bool mousePressed = false;
		int dir_t, dir_p;

		bool settingsOn = false;
		
		bool Handle();
};

