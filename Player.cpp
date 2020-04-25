#include "Player.h"

Player::Player() 
{

}

Player::Player(int init_m, int init_n, Direction_x init_direction_x, Direction_y init_direction_y) 
{
	position_m = init_m;
	position_n = init_n;

	direction_x = init_direction_x;
	direction_y = init_direction_y;
}
