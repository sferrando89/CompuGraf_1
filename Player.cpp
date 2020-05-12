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
	oldDirection = init_direction;
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
	model.mesh_right_foot = loadOBJ("models/Globo.obj");
}

void Player::draw()
{
	//Dibujo al personaje
	glBegin(GL_TRIANGLES);
	//Dibujo cuerpo
	glColor3f(1.0f, 0.9f, 0.0f);
	for (int j = 0; j < model.mesh_body.size(); j++)
	{
		glVertex3f(model.mesh_body[j].getX(), model.mesh_body[j].getY(), model.mesh_body[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Nariz
	glColor3f(0.4f, 0.0f, 0.7f);
	for (int j = 0; j < model.mesh_nose.size(); j++)
	{
		glVertex3f(model.mesh_nose[j].getX(), model.mesh_nose[j].getY(), model.mesh_nose[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Ojo Izquierdo
	glColor3f(0.0f, 0.5f, 1.0f);
	for (int j = 0; j < model.mesh_left_eye.size(); j++)
	{
		glVertex3f(model.mesh_left_eye[j].getX(), model.mesh_left_eye[j].getY(), model.mesh_left_eye[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Ojo Derecho
	glColor3f(0.0f, 0.5f, 1.0f);
	for (int j = 0; j < model.mesh_right_eye.size(); j++)
	{
		glVertex3f(model.mesh_right_eye[j].getX(), model.mesh_right_eye[j].getY(), model.mesh_right_eye[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Pie Izquierdo
	glColor3f(1.0f, 0.5f, 0.0f);
	for (int j = 0; j < model.mesh_left_foot.size(); j++)
	{
		glVertex3f(model.mesh_left_foot[j].getX(), model.mesh_left_foot[j].getY(), model.mesh_left_foot[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibjo Pie Derecho
	glColor3f(1.0f, 0.5f, 0.0f);
	for (int j = 0; j < model.mesh_right_foot.size(); j++)
	{
		glVertex3f(model.mesh_right_foot[j].getX(), model.mesh_right_foot[j].getY(), model.mesh_right_foot[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}

	//Dibujo globo
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int j = 0; j < model.mesh_baloon.size(); j++)
	{
		glVertex3f(model.mesh_baloon[j].getX(), model.mesh_baloon[j].getY(), model.mesh_baloon[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	glEnd();
}