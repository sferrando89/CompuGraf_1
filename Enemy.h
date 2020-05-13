#pragma once
#include "Vector3.h"
#include "Settings.h"
#include "Ficha.h"
#include "OpenGLUtil.h"
#include "OBJLoader.h"

struct badGuy {
	std::vector<Vector3> mesh_body = loadOBJ("models/Vil_Body.obj");
	std::vector<Vector3> mesh_left_eye = loadOBJ("models/Vil_Left_Eye.obj");
	std::vector<Vector3> mesh_right_eye = loadOBJ("models/Vil_Right_Eye.obj");	
	std::vector<Vector3> mesh_cap = loadOBJ("models/Vil_Cap.obj");
	std::vector<Vector3> mesh_death = loadOBJ("models/Vil_death.obj");
};

class Enemy : public Ficha
{
	private:
		badGuy model;
	public:
		Enemy(Vector3 position, Direction init_direction);
		void draw();
		void drawDeath();
};
