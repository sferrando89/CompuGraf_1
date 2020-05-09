#include "Enemy.h"

Enemy::Enemy(Vector3 position, Direction init_direction)
{
	currentPosition = position;
	isMoving = false;
	direction = init_direction;
	settings = Settings::GetInstance();
	//gamemanager = GameManager::GetInstance();
	map = Map::GetInstance();
	percentageTraveled = 0;
}