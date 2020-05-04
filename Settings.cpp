#include "Settings.h"

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
}

void Settings::HandleMovement(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_w:
		if (settingSelected > 1)
		{
			settingSelected--;
		}
		break;
	case SDLK_s:

		if (settingSelected < 4)
		{
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
}