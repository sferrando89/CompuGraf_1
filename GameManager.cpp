#include "GameManager.h"

GameManager* GameManager::instance = NULL;


GameManager* GameManager::GetInstance() {
	if (!instance) {
		instance = new GameManager;
	}
	return instance;

}

GameManager::GameManager()
{
	//HARDCODEADO EL MAPA PRINCIPAL
	gameMap = Map(4, 4, { {1,2,3,4},
						  {1,2,3,4},
		                  {1,2,3,4},
		                  {1,2,3,4} });

	Player player(0,0,0,Direction_x::left, Direction_y::down);
	cout << player.position_n << "\n";

	gameMap.PrintWithCharacter(0,0);
}

void GameManager::HandleMovement(SDL_Keycode key) {
	/* Check the SDLKey values and move change the coords */
	switch (key) {
		case SDLK_LEFT:
			player.direction_x = Direction_x::left;
			break;
		case SDLK_RIGHT:
			player.direction_x = Direction_x::right;
			break;
		case SDLK_UP:
			player.direction_y = Direction_y::up;
			if (player.position_m > 0) //No esta en el borde superior del mapa
			{ 

				if(player.direction_x == Direction_x::left
					&& player.position_n > 0 // No esta en el borde izquierdo del mapa
					&& gameMap.GetCubeHeight(player.position_m - 1, player.position_n - 1) > 0) // Hay un bloque en la direccion a saltar
				{
					gameMap.PaintCube(player.position_m, player.position_n); // Pinto el bloque actual
					player.position_m = player.position_m - 1; // Muevo el personaje
					player.position_n = player.position_n - 1;
				}
				else if (player.direction_x == Direction_x::right
					&& player.position_n < gameMap.size_n - 1 // No esta en el borde derecho del mapa
					&& gameMap.GetCubeHeight(player.position_m - 1, player.position_n) > 0) // Hay un bloque en la direccion a saltar
				{	
					gameMap.PaintCube(player.position_m, player.position_n); // Pinto el bloque actual
					player.position_m = player.position_m - 1; // Muevo el personaje
				}
			}
			break;
		case SDLK_DOWN:
			player.direction_y = Direction_y::down;
			if (player.position_m < gameMap.size_n - 1) //No esta en el borde inferior del mapa
			{
				
				if (player.direction_x == Direction_x::left
					//&& player.position_n > 0 // No esta en el borde izquierdo del mapa
					&& gameMap.GetCubeHeight(player.position_m + 1, player.position_n) > 0) // Hay un bloque en la direccion a saltar
				{
					gameMap.PaintCube(player.position_m, player.position_n); // Pinto el bloque actual
					player.position_m = player.position_m + 1; // Muevo el personaje
				}
				else if (player.direction_x == Direction_x::right
					&& player.position_n < gameMap.size_n - 1 // No esta en el borde derecho del mapa
					&& gameMap.GetCubeHeight(player.position_m + 1, player.position_n + 1) > 0) // Hay un bloque en la direccion a saltar
				{
					gameMap.PaintCube(player.position_m, player.position_n); //Pinto el bloque actual
					player.position_m = player.position_m + 1; // Muevo el personaje
					player.position_n = player.position_n + 1; 
				}
			}
			break;
	}

	gameMap.PrintWithCharacter(player.position_m, player.position_n);

}

bool GameManager::CheckWinCondition()
{
	return gameMap.AllCubesPainted();
}

Map GameManager::getGameMap()
{
	return this->gameMap;
}

Player GameManager::getPlayer()
{
	return this->player;
}
