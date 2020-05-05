#pragma once
#include "Vector3.h"

enum class Direction { left, right, up, down };

enum class Direction_x { left, right };
enum class Direction_y { up, down };

class Player
{
	public:
		Vector3 currentPosition;
		Vector3 oldPosition;

		float distanceTraveled;
		Direction direction;
		bool isMoving;

		void updatePosition(Vector3 nuevaPos);

		Player();
		Player(Vector3 position, Direction init_direction);
		
};
