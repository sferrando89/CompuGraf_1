#include "Settings.h"
#include <iostream>

CameraModes operator++(CameraModes& d, int)
{
	switch (d)
	{
	case CameraModes::isometric:
		d = CameraModes::free;
		break;
	case CameraModes::free:
		d = CameraModes::firstPerson;
		break;
	case CameraModes::firstPerson:
		d = CameraModes::isometric;
		break;
	}
	return d;
}

Settings* Settings::instance = NULL;

Settings* Settings::GetInstance()
{
	if (!instance) {
		instance = new Settings;
	}
	return instance;
}

Settings::Settings()
{

	varValues[0] = true;
	varValues[1] = false;
	varValues[2] = true;
	varValues[3] = true;
	settingSelected = 1;

	cameraMode = CameraModes::isometric;

	lightColor = lightColors::normal;
	lightDirection = 0;
}

void Settings::HandleMovement(SDL_Keycode key)
{
	switch (key){
		case SDLK_w:
			if (settingSelected > 1){
				settingSelected--;
			}
			break;
		case SDLK_s:

			if (settingSelected < 4){
				settingSelected++;
			}
			break;
		case SDLK_d:
			varValues[settingSelected - 1] = false;
			break;
		case SDLK_a:
			varValues[settingSelected - 1] = true;
			break;
		}
	for (int i = 0; i < std::size(varValues); i++) {
		switch (i) {
			case 0:
				// varValues[0] = velocidad lenta
				if (varValues[i]) {
					gameSpeed = 1;
				}
				else {
					gameSpeed = 2;
				}
				break;
			case 1:
				// varValues[1] = wireframe mode on
		
				break;
			case 2:
				// varValues[2] = texturas
		
				break;
			case 3:
				// varValues[3] = interpolado/facetado
				break;
		}
	}
		
}

void Settings::changeLightColor()
{
	if (lightColor == lightColors::normal)
		lightColor = lightColors::red;
	else if (lightColor == lightColors::red)
		lightColor = lightColors::blue;
	else if (lightColor == lightColors::blue)
		lightColor = lightColors::green;
	else if (lightColor == lightColors::green)
		lightColor = lightColors::normal;
}

void Settings::changeLightDirection()
{
	if (lightDirection == 0)
		lightDirection = 1;
	else
		lightDirection = 0;
}
