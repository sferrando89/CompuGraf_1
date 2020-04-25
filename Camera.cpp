#include "Camera.h"
#include <iostream>

Camera* Camera::instance = 0;

Camera* Camera::GetInstance(){
	if (!instance) {
		instance = new Camera;
	}
	return instance;
}

Camera::Camera()
{
	theeta = M_PI / 4;
	phi = M_PI / 4;
	r = S_RADIO;
	delta = M_PI / 90;
}

void Camera::Rotate(float dir_x, float dir_y)
{
	theeta += dir_x * delta;
	phi += dir_y * delta;
	
	if (theeta >= 2 * M_PI)
		theeta = 0;
	if (phi > M_PI)
		phi = 0;

	float x = r * sin(theeta) * sin(phi);
	float y = r * cos(phi);
	float z = r * cos(theeta) * sin(phi);
	
	glLoadIdentity();
	gluLookAt(x, y, z, 0, -10, 0, 0, 1, 0);
	
}

