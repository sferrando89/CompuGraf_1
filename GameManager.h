#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "Map.h"
#include "Player.h"

// GameManager es singleton

class GameManager
{
    private:
        static GameManager* instance;
        // Private constructor so that no objects can be created.
        GameManager();
		Map gameMap;
		Player player;
    public:
        static GameManager* GetInstance();
		void HandleMovement(SDL_Keycode key);
		bool CheckWinCondition();
};