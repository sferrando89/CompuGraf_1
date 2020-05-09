#include "Player.h"

Player* Player::instance = NULL;

Player* Player::GetInstance(Vector3 position, Direction init_direction) {
	if (!instance) {
		instance = new Player(position, init_direction);
	}
	return instance;
}

Player* Player::GetInstance() {
	return instance;
}

Player::Player(Vector3 position, Direction init_direction)
{
	currentPosition = position;
	isMoving = false;
	direction = init_direction;
	settings = Settings::GetInstance();
	//gamemanager= GameManager::GetInstance();
	map = Map::GetInstance();
	percentageTraveled = 0;
}
