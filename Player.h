#pragma once
#include "Vector3.h"
#include "Settings.h"
#include "Ficha.h"

class Player : public Ficha
{
	private:
		static Player* instance;
		Player(Vector3 position, Direction init_direction);

	public:
		static Player* GetInstance();
		static Player* GetInstance(Vector3 position, Direction init_direction);
};
