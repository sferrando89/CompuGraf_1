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
	theeta = M_PI / 4;
	phi = M_PI / 4;
	r = S_RADIO;
	delta = M_PI / 135;

	x = r * cos(theeta) * sin(phi);
	y = r * sin(theeta) * sin(phi);
	z = r * cos(phi);
}



void Camera::Rotate(float dir_x, float dir_y)
{

	theeta += dir_x * delta;
	float phi_n = phi + dir_y * delta;


	if (phi_n > (3/2) * M_PI)
		phi = phi;

	else if (phi_n < 0 ) 
		phi = phi;
	
	else
		phi = phi_n;

	x = r * cos(theeta) * sin(phi);
	y = r * sin(theeta) * sin(phi);
	z = r * cos(phi);

	cout << r << " - " << phi << " - " << x << ", " << y << ", " << z << ", " <<  "\n";

}

void Camera::apply()
{
	Player player = GameManager::GetInstance()->getPlayer();
	glLoadIdentity();
	
	gluLookAt(x, y, z, player.position_x, player.position_y, player.position_z, 0, 0, 1);

}
