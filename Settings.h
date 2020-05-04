#pragma once
#include <SDL.h>

class Settings
{
	private:
		static Settings* instance;
		Settings();



	public:
		static Settings* GetInstance();


		// varValues[0] = velocidad lenta
		// varValues[1] = wireframe mode on
		// varValues[2] = texturas
		// varValues[3] = interpolado/facetado
		bool varValues[4];

		int settingSelected;
		void HandleMovement(SDL_Keycode key);
};

