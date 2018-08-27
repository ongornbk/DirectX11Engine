#pragma once
#include <Windows.h>
#include <string>

struct ModelPaths
{

	ModelPaths();
	ModelPaths(WCHAR* file);

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

};

namespace S_ModelPaths
{

	using std::string;

	 ModelPaths* GetModelPaths(string paths);
	 void        AddModelPaths(string name, WCHAR* file);


};


