#pragma once
#include <Windows.h>
#include <string>

struct ModelPaths
{

	ModelPaths();
	ModelPaths(WCHAR* file);

	union
	{
		struct
		{
			WCHAR* ATTACK_1;
			WCHAR* ATTACK_2;
			WCHAR* GETHIT;
			WCHAR* KICK;
			WCHAR* NEUTRAL;
			WCHAR* RUN;
			WCHAR* SPECIALCAST;
			WCHAR* SPECIAL_1;
			WCHAR* SPECIAL_3;
			WCHAR* SPECIAL_4;
			WCHAR* TOWNNEUTRAL;
			WCHAR* TOWNWALK;
			WCHAR* WALK;
			WCHAR* DEATH;
			WCHAR* DEAD;
		};

		WCHAR* m_modelPath[15];
	};

	int32_t m_rotations;
	int32_t m_frames[15];

};

namespace S_ModelPaths
{

	using std::string;

	 ModelPaths* GetModelPaths(string paths);
	 void        AddModelPaths(string name, WCHAR* file);


};


