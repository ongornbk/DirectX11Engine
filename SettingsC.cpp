#include "SettingsC.h"

namespace 
{
	static int32_t SETTINGS_RESOLUTION_X = 0;
	static int32_t SETTINGS_RESOLUTION_Y = 0;
	static int32_t SETTINGS_SCREEN_RESOLUTION_X = 0;
	static int32_t SETTINGS_SCREEN_RESOLUTION_Y = 0;
	static int32_t SETTINGS_NUMBER_OF_THREADS = 1;
	static bool    SETTINGS_FULL_SCREEN = true;
    static bool    SETTINGS_VSYNC = true;
	static modern_cstring SETTINGS_DB_PORT = "0";
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

bool Settings::GetFullscreen()
{
	return SETTINGS_FULL_SCREEN;
}

bool Settings::GetVsync()
{
	return SETTINGS_VSYNC;
}

modern_cstring& Settings::GetDatabasePort()
{
	return SETTINGS_DB_PORT;
}

void Settings::Initialize(
	const int32_t resX,
	const int32_t resY,
	const int32_t scrX,
	const int32_t scrY,
	const int32_t threads,
	const bool    fullscreen,
	const bool    vsync,
	const char*   port
)
{
	SETTINGS_RESOLUTION_X        = resX;
	SETTINGS_RESOLUTION_Y        = resY;
	SETTINGS_SCREEN_RESOLUTION_X = scrX;
	SETTINGS_SCREEN_RESOLUTION_Y = scrY;
	SETTINGS_NUMBER_OF_THREADS   = threads;
	SETTINGS_FULL_SCREEN         = fullscreen;
	SETTINGS_VSYNC               = vsync;
	SETTINGS_DB_PORT             = port;
}
