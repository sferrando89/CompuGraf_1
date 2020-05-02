#include "Player.h"

Player::Player() 
{

}

//Player::Player(int init_m, int init_n, int init_o, Direction_x init_direction_x, Direction_y init_direction_y) 
Player::Player(int init_m, int init_n, int init_o, Direction init_direction)
{
	position_x = init_m;
	position_y = init_n;
	position_z = init_o;

	direction = init_direction;
	/*
	direction_x = init_direction_x;
	direction_y = init_direction_y;
	*/
}
