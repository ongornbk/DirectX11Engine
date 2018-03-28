#pragma once


struct SettingsC
{
public:

	const int*          NUMBER_OF_UNITS;
	const int*          RESOLUTION_X;
	const int*          RESOLUTION_Y;
	const int*          REALRESOLUTION_X;
	const int*          REALRESOLUTION_Y;
	const float*        COLLISSION_RADIUS;
	const unsigned int* NUMBER_OF_THREADS;

	SettingsC(void);
	~SettingsC(void);
};

namespace Settings
{
	SettingsC* get();
}

extern "C"
{
	namespace Settings
	{
		inline float GetAspectRatio()
		{
			SettingsC* temp = Settings::get();
			return (((float)*(temp->RESOLUTION_X)) / ((float)*(temp->RESOLUTION_Y)));
		}
	}
}

