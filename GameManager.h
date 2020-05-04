#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "Map.h"
#include "Player.h"
#include "LTimer.h"

// GameManager es singleton

class GameManager
{
    private:
        static GameManager* instance;
        // Private constructor so that no objects can be created.
        GameManager();
		Map gameMap;
		Player player;
        LTimer timer;
    public:
        static GameManager* GetInstance();
		void HandleMovement(SDL_Keycode key);
		bool CheckWinCondition();
        Map getGameMap();
        Player getPlayer();
        void switchTimer();
        bool isPaused();
        Uint32 getPlayTime();
        Uint32 getAvgFrames(int countedFrames);
};