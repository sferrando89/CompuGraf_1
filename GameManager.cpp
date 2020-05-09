#include "GameManager.h"
#include <iostream> 

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
	gameMap = Map::GetInstance(7, 7, {	//eje y 
		/*(0,0)*/{1,1,1,1,1,1,1}, // e
				 {3,3,3,2,3,3,3}, // j
				 {4,5,6,7,6,5,4}, // e
				 {3,3,3,2,3,3,3}, //
				 {1,1,1,1,1,1,1}, // x
				 {1,0,0,0,0,0,0},
				 {2,3,4,5,6,7,8}

		});

	//Player player(0,0,0,Direction_x::left, Direction_y::down);

	this->player = Player::GetInstance(Vector3(2, 3, 0), Direction::right);
	this->enemies = new list<Ficha*>;
	this->enemies->push_front(new Enemy(Vector3(3, 3, 0), Direction::right));

	//Player player(0, 0, 0, Direction::right);

	//cout << player.position_m << "\n";
	//cout << player.position_n << "\n";
	//cout << player.direction << "\n";
	//cout << "----------------" << "\n";

	gameMap->PrintWithCharacter(0, 0);
}

void GameManager::HandleMovement(SDL_Keycode key) {
	/* Check the SDLKey values and move change the coords */
	if (!player->isMoving) {
		int new_x;
		int new_y;
		int old_x = player->currentPosition.x;
		int old_y = player->currentPosition.y;
		int old_z = player->currentPosition.z;
		switch (key){
			case SDLK_w:
				player->direction = Direction::up;
				new_x = old_x;
				new_y = old_y + 1;
				break;

			case SDLK_a:
				player->direction = Direction::left;
				new_x = old_x - 1;
				new_y = old_y;
				break;

			case SDLK_d:
				player->direction = Direction::right;
				new_x = old_x + 1;
				new_y = old_y;
				break;

			case SDLK_s:
				player->direction = Direction::down;
				new_x = old_x;
				new_y = old_y - 1;
				break;
		}
		if (gameMap->validMovement(player->direction, old_x, old_y, new_x, new_y)) {
			Vector3 nuevaPos = Vector3(new_x, new_y, old_z);
			player->startMoving(nuevaPos);
		}
	}
	//gameMap->PrintWithCharacter(player.position_m, player.position_n);
}

bool GameManager::CheckWinCondition()
{
	return gameMap->AllCubesPainted();
}

Map* GameManager::getGameMap()
{
	return this->gameMap;
}

Player* GameManager::getPlayer()
{
	return (Player*)this->player;
}

void GameManager::switchTimer() {
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

list<Ficha*>* GameManager::getEnemies() {
	return enemies;
}

void GameManager::moveEnemies() {
	list<Ficha*>* enemies = this->getEnemies();
	list<Ficha*>::iterator iterEnemy;
	for (iterEnemy = enemies->begin(); iterEnemy != enemies->end(); ++iterEnemy) {
		if (!(*iterEnemy)->isMoving) {
			int new_x;
			int new_y;
			int old_x = (*iterEnemy)->currentPosition.x;
			int old_y = (*iterEnemy)->currentPosition.y;
			int old_z = (*iterEnemy)->currentPosition.z;
			Direction possibleDirections[4] = { Direction::up, Direction::left, Direction::right, Direction::down };
			bool foundValidDirection = false;
			while (!foundValidDirection) {
				int ran = rand() % 3;//de 0 a 3
				cout << ran << endl;
				switch (possibleDirections[ran]) {
					case Direction::up:
						(*iterEnemy)->direction = Direction::up;
						new_x = old_x;
						new_y = old_y + 1;
						break;
					case Direction::left:
						(*iterEnemy)->direction = Direction::left;
						new_x = old_x - 1;
						new_y = old_y;
						break;
					case Direction::right:
						(*iterEnemy)->direction = Direction::right;
						new_x = old_x + 1;
						new_y = old_y;
						break;
					case Direction::down:
						(*iterEnemy)->direction = Direction::down;
						new_x = old_x;
						new_y = old_y-1;
						break;
				}
				if (gameMap->validMovement((*iterEnemy)->direction, old_x, old_y, new_x, new_y)) {
					Vector3 nuevaPos = Vector3(new_x, new_y, old_z);
					(*iterEnemy)->startMoving(nuevaPos);
					foundValidDirection = true;
				}
			}
		}
	}
}
