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

bool ResourceSound::Load(WCHAR* soundFileName)
{
	m_sound = new Sound(soundFileName);
	if (!m_sound->IsInitialized())
	{
		delete m_sound;
		m_sound = NULL;
		return false;
	}
	return true;
}

Sound * ResourceSound::GetSound()
{
	return m_sound;
}

string ResourceSound::GetName()
{
	if (m_sound)return m_sound->GetName();
	return "Uninitialized Sound";
}
