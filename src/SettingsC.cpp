#include "SettingsC.h"

extern "C"
{

	namespace
	{
		static SettingsC m_settings;
	}

}

SettingsC::SettingsC()
{

}

SettingsC::~SettingsC()
{
	if (NUMBER_OF_UNITS)
	{
		delete NUMBER_OF_UNITS;
		NUMBER_OF_UNITS = 0;
	}
	if (RESOLUTION_X)
	{
		delete RESOLUTION_X;
		RESOLUTION_X = 0;
	}
	if (RESOLUTION_Y)
	{
		delete RESOLUTION_Y;
		RESOLUTION_Y = 0;
	}
	if (COLLISSION_RADIUS)
	{
		delete COLLISSION_RADIUS;
		COLLISSION_RADIUS = 0;
	}
	if (REALRESOLUTION_X)
	{
		delete REALRESOLUTION_X;
		REALRESOLUTION_X = 0;
	}
	if (REALRESOLUTION_Y)
	{
		delete REALRESOLUTION_Y;
		REALRESOLUTION_Y = 0;
	}
	if (NUMBER_OF_THREADS)
	{
		delete NUMBER_OF_THREADS;
		NUMBER_OF_THREADS = 0;
	}
}

SettingsC* Settings::get()
{
	return &m_settings;
}

