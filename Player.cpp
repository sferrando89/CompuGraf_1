#include "Player.h"
#include <iostream>
using namespace std;

Player* Player::instance = NULL;

Player* Player::GetInstance(Vector3 position, Direction init_direction) {
	if (!instance) {
		instance = new Player(position, init_direction);
	}
	return instance;
}

Player* Player::GetInstance() {
	return instance;
}

Player::Player(Vector3 position, Direction init_direction)
{
	currentPosition = position;
	isMoving = false;
	direction = init_direction;
	settings = Settings::GetInstance();
	//gamemanager= GameManager::GetInstance();
	map = Map::GetInstance();
	percentageTraveled = 0;

	//carga el modelo:
	model.mesh_body = loadOBJ("models/Cuerpo.obj");
	model.mesh_nose = loadOBJ("models/Nariz.obj");
	model.mesh_left_eye = loadOBJ("models/Ojo_Izquierdo.obj");
	model.mesh_right_eye = loadOBJ("models/Ojo_Derecho.obj");
	model.mesh_left_foot = loadOBJ("models/Pie_Izquierdo.obj");
	model.mesh_right_foot = loadOBJ("models/Pie_Derecho.obj");
}
