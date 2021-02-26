#pragma once
#include "MultiSound.h"
#include "SingleSound.h"
#include "SoundType.h"

class ResourceSound
{
public:
	ResourceSound();
	~ResourceSound();

	bool Load(WCHAR* soundFileName,const enum class SoundType type);
	ISound* GetSound();
	std::string GetName();
private:
	ISound* m_sound;
};

