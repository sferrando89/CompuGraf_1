#pragma once
#include "Vector3.h"
#include "Settings.h"
#include "Direction.h"
//#include "GameManager.h"
#include "Map.h"

class Ficha
{
	protected:
		Settings* settings;
		Map* map;

	public:
		virtual ~Ficha();
		Vector3 currentPosition;
		Vector3 oldPosition;

		float percentageTraveled;

		Direction direction;
		Direction oldDirection;

		bool isMoving;

		void startMoving(Vector3 nuevaPos, Direction newDirection);
		void updateTokenLogicalPosition();
};
