#include "Canals.h"
#include <mutex>

namespace
{
	static Canals* m_instance = NULL;
	static Sound* a_sound = NULL;

}

Canals::Canals()
{
	m_instance = this;
	for (int i = 0; i < NUMBER_OF_CANALS; i++)
	{
		m_canals[i] = new Sound_Canal(CanalType(i), 100.0f);
	}
}


Canals::~Canals()
{
	for (int i = 0; i < NUMBER_OF_CANALS; i++)
	{
		delete m_canals[i];
		m_canals[i] = NULL;
	}
}

Canals * Canals::GetInstance()
{
	if (m_instance)
	{
		return m_instance;
	}
	else
	{
		return (m_instance = new Canals());
	}
}

Sound* Canals::__GetSound(string sound)
{	

	for (int i = 0; i < NUMBER_OF_CANALS; i++)
	{
		m_canals[i]->GetSound(sound);
	}

	return a_sound;
}

void Canals::__AddSound(CanalType type, string name, Sound * sound)
{

	m_canals[type]->AddSound(sound, name);

}

Sound_Canal::Sound_Canal(CanalType type, float volume)
{
}

Sound_Canal::~Sound_Canal()
{
	m_sounds.clear();
}

void Sound_Canal::AddSound(Sound * sound, string name)
{

	m_sounds[name] = sound;

}

void Sound_Canal::GetSound(string name)
{
	Sound* tmp = m_sounds[name];
	if (tmp)
	{
		a_sound = tmp;
	}

}
