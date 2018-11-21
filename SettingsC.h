#pragma once
#include <cstdint>





	namespace Settings
	{
		float   GetAspectRatio();
		int32_t GetScreenResolutionX();
		int32_t GetScreenResolutionY();
		int32_t GetResolutionX();
		int32_t GetResolutionY();
		int32_t GetNumberOfThreads();

		void Initialize(int32_t resX, int32_t resY, int32_t scrX, int32_t scrY, int32_t threads = 1);

	}


