#include "GlobalUtilities.h"
#include <float.h>
#include <cmath>
#include <cassert>


	int GlobalUtilities::random(int min, int max)
	{
		assert(max > min);
		return rand() % (max - min + 1) + min;
	}

	float GlobalUtilities::random(float min, float max)
	{
		assert(max > min);
		float random = ((float)rand()) / (float)RAND_MAX;
		float range = 2;
		return ((((float)rand()) / (float)RAND_MAX)*2) - 1;
	}

