#include "GameManager.h"

GameManager* GameManager::instance = NULL;

int points = 0;

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

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
						  {0,1,2,2},
		                  {1,7,3,4},
		                  {1,2,1,5} });

	//Player player(0,0,0,Direction_x::left, Direction_y::down);

	this->player = Player(0, 0, 0, Direction::right);
	//Player player(0, 0, 0, Direction::right);

	//cout << player.position_m << "\n";
	//cout << player.position_n << "\n";
	//cout << player.direction << "\n";
	//cout << "----------------" << "\n";

	gameMap.PrintWithCharacter(0,0);
}

void GameManager::HandleMovement(SDL_Keycode key) {
	/* Check the SDLKey values and move change the coords */
	switch (key) 
	{
		case SDLK_w:
			if (player.direction == Direction::up) 
			{
				if (player.position_n < gameMap.size_n -1) 
				{
					gameMap.PaintCube(player.position_m, player.position_n);
					player.position_n += 1;
				}
			}
			else
			{
				player.direction = Direction::up;
			}
			break;
		case SDLK_a:
			if (player.direction == Direction::left) 
			{
				if (player.position_m > 0)
				{
					gameMap.PaintCube(player.position_m, player.position_n);
					player.position_m -= 1;
				}
			}
			else
			{
				player.direction = Direction::left;
			}
			break;
		case SDLK_d:
			if (player.direction == Direction::right) 
			{
				if (player.position_m < gameMap.size_m -1) 
				{
					gameMap.PaintCube(player.position_m, player.position_n);
					player.position_m += 1;
				}
			}
			else
			{
				player.direction = Direction::right;
			}
			break;
		case SDLK_s:
			if (player.direction == Direction::down)
			{
				if (player.position_n > 0)
				{
					gameMap.PaintCube(player.position_m, player.position_n);
					player.position_n -= 1;
				}
			}
			else
			{
				player.direction = Direction::down;
			}
			break;
	}
	/*
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
					if (gameMap.PaintCube(player.position_m, player.position_n)) {
						points++;
					}; // Pinto el bloque actual y gano puntos
					player.position_m = player.position_m - 1; // Muevo el personaje
					player.position_n = player.position_n - 1;
				}
				else if (player.direction_x == Direction_x::right
					&& player.position_n < gameMap.size_n - 1 // No esta en el borde derecho del mapa
					&& gameMap.GetCubeHeight(player.position_m - 1, player.position_n) > 0) // Hay un bloque en la direccion a saltar
				{	
					if (gameMap.PaintCube(player.position_m, player.position_n)) {
						points++;
					}; // Pinto el bloque actual y gano puntos
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
	*/
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
