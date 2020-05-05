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
	percentageTraveled = 0;
}

void Player::startMoving(Vector3 nuevaPos) {
	isMoving = true;
	percentageTraveled = 0;
	oldPosition = currentPosition;
	currentPosition = nuevaPos;
}

void Player::updatePlayer() {
	int fps=settings->SCREEN_FPS;
	float speed = settings->gameSpeed;
	float porcentajeParticion = speed / fps;
	percentageTraveled = percentageTraveled + porcentajeParticion;
	if (percentageTraveled>1) {
		percentageTraveled = 1;
		isMoving = false;
	}
	/*distanceTraveled.x = distanceTraveled.x + ((oldPosition.x - currentPosition.x) / settings->gameSpeed * settings->SCREEN_FPS);
	distanceTraveled.y = distanceTraveled.y + ((oldPosition.y - currentPosition.y) / settings->gameSpeed * settings->SCREEN_FPS);
	distanceTraveled.z = distanceTraveled.z + ((oldPosition.z - currentPosition.z) / settings->gameSpeed * settings->SCREEN_FPS);
	if (distanceTraveled.x > 0.9 || distanceTraveled.y > 0.9 || distanceTraveled.z > 0.9) {
		distanceTraveled.x = 1;
		distanceTraveled.y = 1;
		distanceTraveled.z = 1;
		isMoving = false;
	}*/
}