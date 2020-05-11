#include "Enemy.h"

Enemy::Enemy(Vector3 position, Direction init_direction)
{
	currentPosition = position;
	isMoving = false;
	direction = init_direction;
	settings = Settings::GetInstance();
	//gamemanager = GameManager::GetInstance();
	map = Map::GetInstance();
	percentageTraveled = 0;
}

void Enemy::draw()
{
	//Dibujo al personaje
	glBegin(GL_TRIANGLES);
	//Dibujo cuerpo
	glColor3f(.1, .5, .7);
	for (int j = 0; j < model.mesh_body.size(); j++)
	{
		glVertex3f(model.mesh_body[j].getX(), model.mesh_body[j].getY(), model.mesh_body[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Gorro
	glColor3f(.8, 0, .8);
	for (int j = 0; j < model.mesh_cap.size(); j++)
	{
		glVertex3f(model.mesh_cap[j].getX(), model.mesh_cap[j].getY(), model.mesh_cap[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Ojo Izquierdo
	glColor3f(1, 1, 1);
	for (int j = 0; j < model.mesh_left_eye.size(); j++)
	{
		glVertex3f(model.mesh_left_eye[j].getX(), model.mesh_left_eye[j].getY(), model.mesh_left_eye[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	//Dibujo Ojo Derecho
	glColor3f(1, 1, 1);
	for (int j = 0; j < model.mesh_right_eye.size(); j++)
	{
		glVertex3f(model.mesh_right_eye[j].getX(), model.mesh_right_eye[j].getY(), model.mesh_right_eye[j].getZ() + map->GetCubeHeight(currentPosition.x, currentPosition.y));
	}
	glEnd();
}
