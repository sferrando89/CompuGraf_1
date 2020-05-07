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
	mapCenter = GameManager::GetInstance()->getGameMap().getMapCenter();

	//theeta = M_PI / 4;
	//phi = 0;
	r = S_RADIO;
	delta = M_PI / 50;


	//x = r * cos(theeta) * sin(phi);
	//y = r * sin(theeta) * sin(phi);
	//z = r * cos(phi);

	x = r/sqrt(3);
	y = r/sqrt(3);
	z = sqrt( r*r -pow(x-mapCenter.getX(),2) - pow(y-mapCenter.getY(),2) + mapCenter.getZ());


	theeta = atan(sqrt(x*x + y*y)/z);
	phi = atan(y / x);

	
	x = r *cos(phi);
	y = r* sin(phi);

	//x = r * sin(theeta) * cos(phi);
	//y = r * sin(theeta) * sin(phi);
	//z = r * cos(theeta);

	
}



void Camera::Rotate(float dir_x, float dir_y)
{
	//Player* player = GameManager::GetInstance()->getPlayer();


	//theeta += -dir_y * delta;
	//float phi_n = phi + dir_y * delta;
	phi += -dir_x * delta;
	/*
	if (phi_n > (3/2) * M_PI)
		phi = phi;

	else if (phi_n < 0 ) 
		phi = phi;
	
	else
		phi = phi_n;
		*/
	//x = r * sin(theeta) * cos(phi);
	//y = r * sin(theeta) * sin(phi);
	//z = r * cos(theeta);

	x = r *cos(phi);
	y = r* sin(phi);

	//cout << r << " - " << phi << " - " << x << ", " << y << ", " << z << ", " <<  "\n";

}

void Camera::apply()
{
	Player* player = GameManager::GetInstance()->getPlayer();
	glLoadIdentity();
	
	gluLookAt(x,y,z,mapCenter.getX(), mapCenter.getY(), mapCenter.getZ(), 0, 0, 1);

}
