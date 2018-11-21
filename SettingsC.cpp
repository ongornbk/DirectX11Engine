#include "SettingsC.h"

namespace 
{
	static int32_t SETTINGS_RESOLUTION_X = 0;
	static int32_t SETTINGS_RESOLUTION_Y = 0;
	static int32_t SETTINGS_SCREEN_RESOLUTION_X = 0;
	static int32_t SETTINGS_SCREEN_RESOLUTION_Y = 0;
	static int32_t SETTINGS_NUMBER_OF_THREADS = 1;
}

float Settings::GetAspectRatio()
{
	if (SETTINGS_RESOLUTION_Y == 0)
		return 0.f;
	return (((float)(SETTINGS_RESOLUTION_X)) / ((float)(SETTINGS_RESOLUTION_Y)));
}

int32_t Settings::GetScreenResolutionX()
{
	return SETTINGS_SCREEN_RESOLUTION_X;
}

int32_t Settings::GetScreenResolutionY()
{
	return SETTINGS_SCREEN_RESOLUTION_Y;
}

int32_t Settings::GetResolutionX()
{
	return SETTINGS_RESOLUTION_X;
}

int32_t Settings::GetResolutionY()
{
	return SETTINGS_RESOLUTION_Y;
}

int32_t Settings::GetNumberOfThreads()
{
	return SETTINGS_NUMBER_OF_THREADS;
}

void Settings::Initialize(int32_t resX, int32_t resY, int32_t scrX, int32_t scrY, int32_t threads)
{
	SETTINGS_RESOLUTION_X = resX;
	SETTINGS_RESOLUTION_Y = resY;
	SETTINGS_SCREEN_RESOLUTION_X = scrX;
	SETTINGS_SCREEN_RESOLUTION_Y = scrY;
	SETTINGS_NUMBER_OF_THREADS = threads;
}
