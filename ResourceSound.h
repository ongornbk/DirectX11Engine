#pragma once
#include "Sound.h"

class ResourceSound
{
public:
	ResourceSound();
	~ResourceSound();

	bool Load(WCHAR* soundFileName);
	Sound* GetSound();
	string GetName();
private:
	Sound* m_sound;
};

