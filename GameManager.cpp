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
	// Piramide
	
	gameMap = Map::GetInstance(8, 8, {
		{8,7,6,5,4,3,2,1,0},
		{7,6,5,4,3,2,1,0,0},
		{6,5,4,3,2,1,0,0,0},
		{5,4,3,2,1,0,0,0,0},
		{4,3,2,1,0,0,0,0,0},
		{3,2,1,0,0,0,0,0,0},
		{2,1,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0}},
		90,
		5.5,
		5);

	

	// Plano
	/*
	gameMap = Map::GetInstance(8, 8, {
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1} },
		90,
		1,
		5);
		*/
	

	//Player player(0,0,0,Direction_x::left, Direction_y::down);

	this->player = Player::GetInstance(Vector3(2, 3, 0), Direction::right);
	this->enemies = new list<Ficha*>;
	this->enemies->push_front(new Enemy(Vector3(0, 0, 0), Direction::right));

	//Player player(0, 0, 0, Direction::right);

	//cout << player.position_m << "\n";
	//cout << player.position_n << "\n";
	//cout << player.direction << "\n";
	//cout << "----------------" << "\n";

	gameMap->PrintWithCharacter(0, 0);
}

void GameManager::HandleMovement(SDL_Keycode key) {
	/* Check the SDLKey values and move change the coords */
	int new_x=NULL;
	int new_y=NULL;
	int old_x = player->currentPosition.x;
	int old_y = player->currentPosition.y;
	int old_z = player->currentPosition.z;

	Direction newDir;

	if (Settings::GetInstance()->cameraMode == CameraModes::firstPerson){
		if (!player->isMoving) {
			switch (key){
				case SDLK_w:
					//player->direction = Direction::up;
					switch (player->direction){
						case Direction::up:
							newDir = Direction::up;
							new_x = old_x;
							new_y = old_y + 1;
							break;

						case Direction::left:
							newDir = Direction::left;
							new_x = old_x - 1;
							new_y = old_y;
							break;

						case Direction::down:
							newDir = Direction::down;
							new_x = old_x;
							new_y = old_y - 1;
							break;

						case Direction::right:
							newDir = Direction::right;
							new_x = old_x + 1;
							new_y = old_y;
							break;
					}
					if (gameMap->validMovement(newDir, old_x, old_y, new_x, new_y)) {
						Vector3 nuevaPos = Vector3(new_x, new_y, old_z);
						player->startMoving(nuevaPos,newDir);
					}
					break;

				case SDLK_a:
					player->direction--;
					break;

				case SDLK_d:
					player->direction++;
					break;

				case SDLK_s:
					switch (player->direction){
						case Direction::up:
							player->direction = Direction::down;
							break;
						case Direction::left:
							player->direction = Direction::right;
							break;
						case Direction::down:
							player->direction = Direction::up;
							break;
						case Direction::right:
								player->direction = Direction::left;
								break;
					}
					break;
				}
		}
	}
	else{
		if (!player->isMoving) {
			bool sigo = false;
			switch (key) {
				case SDLK_w:
					newDir = Direction::up;
					new_x = old_x;
					new_y = old_y + 1;
					sigo = true;
					break;

				case SDLK_a:
					newDir = Direction::left;
					new_x = old_x - 1;
					new_y = old_y;
					sigo = true;
					break;

				case SDLK_s:
					newDir = Direction::down;
					new_x = old_x;
					new_y = old_y - 1;
					sigo = true;
					break;

				case SDLK_d:
					newDir = Direction::right;
					new_x = old_x + 1;
					new_y = old_y;
					sigo = true;
					break;
			}
			if (sigo) {
				if (gameMap->validMovement(newDir, old_x, old_y, new_x, new_y)) {
					Vector3 nuevaPos = Vector3(new_x, new_y, old_z);
					player->startMoving(nuevaPos,newDir);
				}
			}	
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
	Direction newDir;

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
				int ran = rand() % 4;//de 0 a 3
				switch (possibleDirections[ran]) {
					case Direction::up:
						newDir = Direction::up;
						new_x = old_x;
						new_y = old_y + 1;
						break;
					case Direction::left:
						newDir = Direction::left;
						new_x = old_x - 1;
						new_y = old_y;
						break;
					case Direction::right:
						newDir = Direction::right;
						new_x = old_x + 1;
						new_y = old_y;
						break;
					case Direction::down:
						newDir = Direction::down;
						new_x = old_x;
						new_y = old_y - 1;
						break;
				}
				if (gameMap->validMovement(newDir, old_x, old_y, new_x, new_y)) {
					Vector3 nuevaPos = Vector3(new_x, new_y, old_z);
					(*iterEnemy)->startMoving(nuevaPos,newDir);
					foundValidDirection = true;
				}
			}
		}
	}
}

bool GameManager::detectColision() {
	list<Ficha*>::iterator iterEnemy;
	for (iterEnemy = enemies->begin(); iterEnemy != enemies->end(); ++iterEnemy) {
		if ((*iterEnemy)->currentPosition == player->currentPosition) {
			if ((*iterEnemy)->isMoving && !player->isMoving) {
				if ((*iterEnemy)->percentageTraveled > 0.50) {
					cout << "DEAD 1" << endl;
					return true;
				}
			}
			else if (!(*iterEnemy)->isMoving && player->isMoving) {
				if (player->percentageTraveled > 0.50) {
					cout << "DEAD 2" << endl;
					return true;
				}
			}
			else if ((*iterEnemy)->isMoving && player->isMoving) {
				if ((*iterEnemy)->percentageTraveled > 0.50 && player->percentageTraveled > 0.50) {
					cout << "DEAD 3" << endl;
					return true;
				}
			}
			else {
				//INSTA DEAD
				cout << "DEAD 4" << endl;
				return true;
			}
		}
	}
	return false;
}
