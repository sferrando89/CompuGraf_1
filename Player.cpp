#include "Player.h"

Player::Player() 
{

}

//Player::Player(int init_m, int init_n, int init_o, Direction_x init_direction_x, Direction_y init_direction_y) 
Player::Player(Vector3 position, Direction init_direction)
{
	currentPosition = position;
	isMoving = false;
	distanceTraveled = 0;
	direction = init_direction;
}

void Player::updatePosition(Vector3 nuevaPos) {
	oldPosition = currentPosition;
	currentPosition = nuevaPos;
}