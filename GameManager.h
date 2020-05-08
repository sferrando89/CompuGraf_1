#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "Map.h"
#include "Player.h"
#include "LTimer.h"
#include <list>
#include "Enemy.h"
#include "Direction.h"

// GameManager es singleton

class GameManager
{
    private:
        static GameManager* instance;
        // Private constructor so that no objects can be created.
        GameManager();
		Map gameMap;
		Ficha* player;
        LTimer timer;
        list<Ficha*>* enemies;
    public:
        static GameManager* GetInstance();
		void HandleMovement(SDL_Keycode key);
		bool CheckWinCondition();
        Map getGameMap();
        Player* getPlayer();
        list<Ficha*>* getEnemies();
        void switchTimer();
        bool isPaused();
        Uint32 getPlayTime();
        void moveEnemies();
};