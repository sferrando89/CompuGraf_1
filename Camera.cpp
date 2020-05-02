#include "Camera.h"
#include "GameManager.h"
#include <iostream>

/*
^ (z)   (o)
|       
|      
|     
|    
|    ^  (y) (n) 
|   /
|  /
| /
---------------------------------> (x) (m)
*/
Camera* Camera::instance = 0;

Camera* Camera::GetInstance(){
	if (!instance) {
		instance = new Camera;
	}
	return instance;
}

Camera::Camera()
{
	theeta = 0;
	phi = M_PI / 2;
	r = S_RADIO;
	delta = M_PI / 90;
	x = S_RADIO;
	y = 0;
	z = 0;
}



void Camera::Rotate(float dir_x, float dir_y)
{
	Player player = GameManager::GetInstance()->getPlayer();

	theeta += dir_x * delta;
	phi += dir_y * delta;
	
	float z_up = 1;

	if (theeta >= 2 * M_PI)
		theeta = 0;
	/*
	if (phi > M_PI) {
		phi = 0;
		//z_up = -1;
	}
	*/
	
	x = r * cos(theeta) * sin(phi);
	y = r * sin(theeta) * sin(phi);
	z = r * cos(phi);

	/*
	if (z < 0) {
		z_up = -1;
	}
	*/

	//glLoadIdentity();
	//gluLookAt(x, y, z, player.position_m, player.position_n, player.position_o, 0, 0, z_up);
	
}

void Camera::apply()
{
	Player player = GameManager::GetInstance()->getPlayer();
	glLoadIdentity();
	float z_up = 1;
	gluLookAt(x, y, z, player.position_x, player.position_y, player.position_z, 0, 0, z_up);
}
