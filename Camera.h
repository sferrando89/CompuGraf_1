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
		float x = S_RADIO;
		float y = 0;
		float z = 0;
	public:
		static Camera* GetInstance();

		// Para las transformaciones de la camara, primero se aplica la transformacion
		// y a lo ultimo se aplican esas transformaciones con apply

		// dir_x = -1 -> izquierda
		// dir_x = 1 -> derecha
		// dir_y = -1 -> abajo
		// dir_y = 1 --> arriba
		// dir_x, dir_y = 0 -> no hay giro en esa direccion
		void Rotate(float dir_x, float dir_y);

		void apply();
};

