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
		//GameManager* gamemanager;

	public:
		Vector3 currentPosition;
		Vector3 oldPosition;

		float percentageTraveled;
		Direction direction;
		bool isMoving;

		void startMoving(Vector3 nuevaPos);
		void updateTokenLogicalPosition();
};
