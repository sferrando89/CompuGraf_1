#pragma once
#include "Vector3.h"
#include "Settings.h"
#include "Ficha.h"

class Enemy : public Ficha
{
	public:
		Enemy(Vector3 position, Direction init_direction);
};
