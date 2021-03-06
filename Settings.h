#pragma once
#include <SDL.h>

enum class CameraModes {isometric, free, firstPerson};
enum class lightColors {red, green, blue, normal};

CameraModes operator++(CameraModes& d, int);

class Settings
{
	private:
		static Settings* instance;
		Settings();

	public:
		const int SCREEN_FPS = 60;
		static Settings* GetInstance();
		// varValues[0] = velocidad lenta
		// varValues[1] = wireframe mode on
		// varValues[2] = texturas
		// varValues[3] = interpolado/facetado
		bool varValues[4];
		float gameSpeed = 1;

		CameraModes cameraMode; 

		lightColors lightColor;
		int lightDirection;

		int settingSelected;
		void HandleMovement(SDL_Keycode key);
		void changeLightColor();
		void changeLightDirection();
};

