#pragma once
#include "ISound.h"
#include <string>

class UnitSounds
{
	ISound* m_sounds[13];

public:

	UnitSounds(void);
	~UnitSounds(void);

	enum UnitSoundType
	{
	ATTACK_1           = 0,
	ATTACK_2           = 1,
	GETHIT             = 2,
	KICK			   = 3,
	NEUTRAL			   = 4,
	RUN				   = 5,
	SPECIALCAST		   = 6,
	SPECIAL_1		   = 7,
	SPECIAL_3		   = 8,
	SPECIAL_4		   = 9,
	TOWNNEUTRAL		   = 10,
	TOWNWALK		   = 11,
	WALK			   = 12
	};

	void Play(const enum UnitSoundType type);
	void LoadSounds(WCHAR* file);
};

