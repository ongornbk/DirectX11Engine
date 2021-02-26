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

bool ResourceSound::Load(WCHAR* soundFileName, const enum class SoundType type)
{
	switch (type)
	{
	case SoundType::SOUND_TYPE_SINGLE:
		m_sound = new SingleSound(soundFileName);
		break;
	case SoundType::SOUND_TYPE_MULTI:
		m_sound = new MultiSound(soundFileName);
		break;
	default:
		return false;
	}
	
	if (!m_sound->IsInitialized())
	{
		delete m_sound;
		m_sound = NULL;
		return false;
	}
	return true;
}

ISound * ResourceSound::GetSound()
{
	return m_sound;
}

std::string ResourceSound::GetName()
{
	if (m_sound)return m_sound->GetName();
	return "Uninitialized Sound";
}
