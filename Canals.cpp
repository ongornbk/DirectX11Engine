#include "Canals.h"
#include <mutex>

namespace
{
	static Canals* m_instance = NULL;
	static ISound* a_sound = NULL;

}

Canals::Canals()
{
	m_instance = this;
	for ( int32 i = 0; i < NUMBER_OF_CANALS; i++)
	{
		m_canals[i] = new Sound_Canal(CanalType(i), 100.0f);
	}
}


Canals::~Canals()
{
	for ( int32 i = 0; i < NUMBER_OF_CANALS; i++)
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

ISound* Canals::__GetSound(string sound)
{	

	for ( int32 i = 0; i < NUMBER_OF_CANALS; i++)
	{
		m_canals[i]->GetSound(sound);
	}

	return a_sound;
}

ISound* Canals::__GetSound(modern_string& sound)
{
	for (int32 i = 0; i < NUMBER_OF_CANALS; i++)
	{
		m_canals[i]->GetSound(sound);
	}

	return a_sound;
}

void Canals::__AddSound(CanalType type, string name, ISound * sound)
{

	m_canals[type]->AddSound(sound, name);

}

void Canals::Play(WCHAR * sound)
{
	
	
	
	
	
	
	
}

void Canals::Stop()
{
	for (int32 i = 0; i < NUMBER_OF_CANALS; ++i)
	{
		m_canals[i]->Stop();
	}
}

void Canals::Update()
{
	for (int32 i = 0; i < NUMBER_OF_CANALS; ++i)
	{
		m_canals[i]->Update();
	}
}

Sound_Canal::Sound_Canal(CanalType type, float volume)
{
}

Sound_Canal::~Sound_Canal()
{
	m_sounds.clear();
}

void Sound_Canal::Update(void)
{
	for (auto && sound : m_sounds)
	{
		if (sound.second)
		{
			sound.second->Update();
		}
	}
}

void Sound_Canal::AddSound(class ISound * const sound, string name)
{
	m_sounds[name] = sound;
}

void Sound_Canal::GetSound(string name)
{
	ISound* tmp = m_sounds[name];
	if (tmp)
	{
		a_sound = tmp;
	}
}

void Sound_Canal::GetSound(modern_string& name)
{
	this->GetSound(string(name.c_str()));
}

void Sound_Canal::Stop()
{
	for (auto&& sound : m_sounds)
	{
		if (sound.second)
		{
			sound.second->Stop();
		//	delete sound.second;
		}
	}
//	m_sounds.clear();

	//delete m_instance;
	//m_instance = new class Canals();
}
