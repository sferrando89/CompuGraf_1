#pragma once
#include "Vector3.h"
#include "Settings.h"
#include "Ficha.h"
#include "OBJLoader.h"

struct qbert {
	std::vector<Vector3> mesh_body = loadOBJ("models/Cuerpo.obj");
	std::vector<Vector3> mesh_nose = loadOBJ("models/Nariz.obj");
	std::vector<Vector3> mesh_left_eye = loadOBJ("models/Ojo_Izquierdo.obj");
	std::vector<Vector3> mesh_right_eye = loadOBJ("models/Ojo_Derecho.obj");
	std::vector<Vector3> mesh_left_foot = loadOBJ("models/Pie_Izquierdo.obj");
	std::vector<Vector3> mesh_right_foot = loadOBJ("models/Pie_Derecho.obj");
};

struct balloon {
	std::vector<Vector3> mesh_balloon = loadOBJ("models/Globo.obj");
	std::vector<Vector3> mesh_balloon_text = loadOBJ("models/Texto_globo.obj");
};

class Player : public Ficha
{
	private:
		static Player* instance;
		qbert model;
		balloon balloonModel;
		Player(Vector3 position, Direction init_direction);

	public:
		static Player* GetInstance();
		static Player* GetInstance(Vector3 position, Direction init_direction);		
		void draw();
		void drawBalloon();
};
