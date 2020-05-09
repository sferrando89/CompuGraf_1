#include "Ficha.h"
#include "Player.h"

Ficha::~Ficha() {}

void Ficha::startMoving(Vector3 nuevaPos) {
	isMoving = true;
	percentageTraveled = 0;
	oldPosition = currentPosition;
	currentPosition = nuevaPos;
}

void Ficha::updateTokenLogicalPosition() {
	if (this->isMoving) {
		int fps = settings->SCREEN_FPS;
		float speed = settings->gameSpeed;
		float porcentajeParticion = speed / fps;
		percentageTraveled = percentageTraveled + porcentajeParticion;
		if (percentageTraveled > 1) {
			percentageTraveled = 1;
			isMoving = false;
			//gamemanager->getGameMap().PaintCube(this->currentPosition.x,this->currentPosition.y);
			//int a= dynamic_cast<Player*>(this);
			if (!(dynamic_cast<Player*>(this)==0)) {
				//NO SE CASTEO a PLAYER
				map->PaintCube(this->currentPosition.x, this->currentPosition.y);
			}
		}
	}
}