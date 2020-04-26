#pragma once

enum class Direction_x { left, right };
enum class Direction_y { up, down };

class Player
{
	public:
		
		int position_m;
		int position_n;
		int position_o;
		Direction_x direction_x;
		Direction_y direction_y;

		Player();
		Player(int init_m, int init_n, int init_o, const Direction_x init_direction_x = Direction_x::left, const Direction_y init_direction_y = Direction_y::down);
		
};
