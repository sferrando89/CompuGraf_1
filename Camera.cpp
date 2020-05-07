#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
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

	
	//x = r *cos(phi);
	//y = r* sin(phi);

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
	
	glLoadIdentity();
	float offset = 5;
	int offsetX =0;
	int offsetY =0;
	
	float eyePositionX = 0;
	float eyePositionY = 0;
	float eyePositionZ = 0;

	Player* player = GameManager::GetInstance()->getPlayer();

	switch(Settings::GetInstance()->cameraMode){
		case CameraModes::free:
			gluLookAt(	x,
						y,
						z,
						mapCenter.getX(), 
						mapCenter.getY(), 
						mapCenter.getZ(), 
						0, 0, 1);
			break;
		case CameraModes::firstPerson:
			switch(player->direction)
			{
				case Direction::left:
					offsetX = 1;
					break;
				case Direction::right:
					offsetX = -1;
					break;
				case Direction::up:
					offsetY = -1;
					break;
				case Direction::down:
					offsetY = 1;
					break;

			}

			eyePositionX = player->currentPosition.x + offset*offsetX;
			eyePositionY = player->currentPosition.y + offset*offsetY;
			eyePositionZ = player->currentPosition.z + offset;

			gluLookAt( 	eyePositionX,
					   	eyePositionY,
					   	eyePositionZ,
						player->currentPosition.x,
						player->currentPosition.y,
						player->currentPosition.z,
						0, 0, 1);
			break;
		case CameraModes::isometric:
			gluLookAt(	S_RADIO,
						S_RADIO,
						S_RADIO,
						mapCenter.getX(),
						mapCenter.getY(),
						mapCenter.getZ(),
						0, 0, 1);
			break;
	}


}
