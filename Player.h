#pragma once
#include "Vector3.h"
#include "Settings.h"

enum class Direction { up, right, down , left}; // Como las agujas del reloj
Direction operator++(Direction& d, int);
Direction operator--(Direction& d, int);

enum class Direction_x { left, right };
enum class Direction_y { up, down };

class Player
{
	private:
		Settings* settings;
		static Player* instance;
		Player(Vector3 position, Direction init_direction);

	public:
		Vector3 currentPosition;
		Vector3 oldPosition;

		float percentageTraveled;
		Direction direction;
		bool isMoving;

		void startMoving(Vector3 nuevaPos);
		void updatePlayer();
		static Player* GetInstance();
		static Player* GetInstance(Vector3 position, Direction init_direction);
};
