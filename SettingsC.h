#pragma once
#include <cstdint>
#include "modern/modern_cstring.h"




	namespace Settings
	{
		float   GetAspectRatio();
		int32_t GetScreenResolutionX();
		int32_t GetScreenResolutionY();
		int32_t GetResolutionX();
		int32_t GetResolutionY();
		int32_t GetNumberOfThreads();
		bool GetFullscreen();
		bool GetVsync();

		class modern_cstring& GetDatabasePort();

		void Initialize(
			const int32_t resX,
			const int32_t resY,
			const int32_t scrX,
			const int32_t scrY,
			const int32_t threads,
			const bool    fullscreen,
			const bool    vsync,
			const char*   db_port
		);

	}


