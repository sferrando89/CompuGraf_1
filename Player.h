#pragma once
#include "Vector3.h"
#include "Settings.h"

enum class Direction { left, right, up, down };

enum class Direction_x { left, right };
enum class Direction_y { up, down };

class Player
{
	private:
		Settings* settings;

	public:
		Vector3 currentPosition;
		Vector3 oldPosition;

		float percentageTraveled;
		Direction direction;
		bool isMoving;

		void startMoving(Vector3 nuevaPos);
		void updatePlayer();

		Player();
		Player(Vector3 position, Direction init_direction);
		
};
