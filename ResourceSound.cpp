#include "ResourceSound.h"



ResourceSound::ResourceSound()
{
	m_sound = NULL;
}


ResourceSound::~ResourceSound()
{
	if (m_sound)
	{
		delete m_sound;
		m_sound = NULL;
	}
}

modern_Boolean ResourceSound::Load(const class modern_string& name, const enum class SoundType type)
{
	switch (type)
	{
	case SoundType::SOUND_TYPE_SINGLE:
		m_sound = new SingleSound(name);
		break;
	case SoundType::SOUND_TYPE_MULTI:
		m_sound = new MultiSound(name);
		break;
	default:
		return modern_false;
	}
	
	if (!m_sound->IsInitialized())
	{
		delete m_sound;
		m_sound = nullptr;
		return modern_false;
	}
	return modern_true;
}

ISound * ResourceSound::GetSound()
{
	return m_sound;
}

const modern_string_view& ResourceSound::GetName()
{
	if (m_sound)
	{
		return m_sound->GetName();
	}
	return modern_string_view(L"UNINITIALIZED RESOURCE SOUND");
}
