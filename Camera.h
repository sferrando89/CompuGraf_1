#pragma once
#include "OpenGLUtil.h"
#include <cmath>

class Camera
{
	private:
		static Camera* instance;
		Camera();
		float theeta;
		float phi;
		float r;
		float delta;
	public:
		static Camera* GetInstance();

		// dir_x = -1 -> izquierda
		// dir_x = 1 -> derecha
		// dir_y = -1 -> abajo
		// dir_y = 1 --> arriba
		// dir_x, dir_y = 0 -> no hay giro en esa direccion
		void Rotate(float dir_x, float dir_y);
};

