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
	gameMap = Map(6, 6, {	//eje y 
				   /*(0,0)*/{6,5,4,3,2,1}, // e
							{5,4,3,2,1,0}, // j
							{4,3,2,1,0,0}, // e
							{3,2,1,0,0,0}, //
							{2,1,0,0,0,0}, // x
							{6,0,0,0,0,0},

		});


	//Player player(0,0,0,Direction_x::left, Direction_y::down);

	this->player = Player::GetInstance(Vector3(0, 0, 0), Direction::right);

	//Player player(0, 0, 0, Direction::right);

	//cout << player.position_m << "\n";
	//cout << player.position_n << "\n";
	//cout << player.direction << "\n";
	//cout << "----------------" << "\n";
	
	gameMap.PrintWithCharacter(0,0);
}

void GameManager::HandleMovement(SDL_Keycode key) {
	/* Check the SDLKey values and move change the coords */
	if (!player->isMoving) {
		switch (key)
		{
			case SDLK_w:
				player->direction = Direction::up;

				if (player->currentPosition.y < gameMap.size_n - 1)
				{
					int new_x = player->currentPosition.x;
					int new_y = player->currentPosition.y + 1;
					if (gameMap.validMovement(player->currentPosition.x, player->currentPosition.y, new_x, new_y)) {
						Vector3 nuevaPos = Vector3(new_x, new_y, player->currentPosition.z);
						player->startMoving(nuevaPos);
						player->currentPosition = nuevaPos;
						gameMap.PaintCube(player->currentPosition.x, player->currentPosition.y);
					}
				}

				break;

			case SDLK_a:

				player->direction = Direction::left;

				if (player->currentPosition.x > 0)
				{
					int new_x = player->currentPosition.x - 1;
					int new_y = player->currentPosition.y;
					if (gameMap.validMovement(player->currentPosition.x, player->currentPosition.y, new_x, new_y)) {
						Vector3 nuevaPos = Vector3(new_x, new_y, player->currentPosition.z);
						player->startMoving(nuevaPos);
						player->currentPosition = nuevaPos;
						gameMap.PaintCube(player->currentPosition.x, player->currentPosition.y);
					}
				}

				break;

			case SDLK_d:

				player->direction = Direction::right;

				if (player->currentPosition.x < gameMap.size_m - 1)
				{
					int new_x = player->currentPosition.x + 1;
					int new_y = player->currentPosition.y;
					if (gameMap.validMovement(player->currentPosition.x, player->currentPosition.y, new_x, new_y)) {
						Vector3 nuevaPos = Vector3(new_x, new_y, player->currentPosition.z);
						player->startMoving(nuevaPos);
						//player->currentPosition = nuevaPos;
						gameMap.PaintCube(player->currentPosition.x, player->currentPosition.y);
					}
				}

				break;

			case SDLK_s:

				player->direction = Direction::down;

				if (player->currentPosition.y > 0)
				{
					int new_x = player->currentPosition.x;
					int new_y = player->currentPosition.y - 1;
					if (gameMap.validMovement(player->currentPosition.x, player->currentPosition.y, new_x, new_y)) {
						Vector3 nuevaPos = Vector3(new_x, new_y, player->currentPosition.z);
						player->startMoving(nuevaPos);
						player->currentPosition = nuevaPos;
						gameMap.PaintCube(player->currentPosition.x, player->currentPosition.y);
					}
				}

				break;
		}
	}
	//gameMap.PrintWithCharacter(player.position_m, player.position_n);
}

bool GameManager::CheckWinCondition()
{
	return gameMap.AllCubesPainted();
}

Map GameManager::getGameMap()
{
	return this->gameMap;
}

Player* GameManager::getPlayer()
{
	return this->player;
}

void GameManager::switchTimer(){
	if (timer.isPaused())
	{
		timer.unpause();
	}
	else
	{
		timer.pause();
	}
}

bool GameManager::isPaused() {
	return timer.isPaused();
}

Uint32 GameManager::getPlayTime() {
	return timer.getTicks();
}
