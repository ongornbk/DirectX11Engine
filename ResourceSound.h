#pragma once
#include "MultiSound.h"
#include "SingleSound.h"
#include "SoundType.h"

#include "modern/modern_string.h"

class ResourceSound
{
public:
	ResourceSound();
	~ResourceSound();

	modern_Boolean Load(const class modern_string& name,const enum class SoundType type);
	ISound* GetSound();
	const modern_string_view& GetName();
private:
	ISound* m_sound;
};

