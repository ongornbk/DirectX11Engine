#include "Sound.h"
#include "GlobalUtilities.h"


Sound::Sound(WCHAR* soundFileName)
{
	m_sound = NULL;
	m_volume = 100.0f;
	m_isLooping = false;
	m_initialized = Initialize(soundFileName);
}


Sound::~Sound()
{
	if (m_sound)
	{
		delete m_sound;
		m_sound = NULL;
	}
	m_name.clear();
}

bool Sound::Initialize(WCHAR* soundFileName)
{
	wstring tmp0 = wstring(soundFileName);
	string tmp1 = string(tmp0.begin(), tmp0.end());
	int32 pos = (int32)tmp1.find_last_of("/");
	if (pos >= 0)
	{
		m_name = tmp1.substr(pos + 1, tmp1.length());
	}
	m_name = m_name.substr(0, m_name.find("."));

	
	if (!m_soundBuffer.loadFromFile(tmp1))
	{
		
		return false;
	}

	m_sound = new sf::Sound();
	m_sound->setBuffer(m_soundBuffer);
	return true;
}

bool Sound::IsInitialized()
{

	return m_initialized;
}

sf::SoundSource::Status Sound::GetStatus()
{
	return m_sound->getStatus();
}

void Sound::Play()
{
	m_instances.push_back(sf::Sound(m_soundBuffer));
	m_instances.back().play();
}

class sf::Sound * Sound::StartPlaying()
{
	Sound::SetLooping(true);
	sf::Sound sound(m_soundBuffer);
	m_instances.push_back(sound);
	m_instances.back().play();
	return &sound;
}

void Sound::Stop()
{
//	m_sound->pause();
}

void Sound::SetLooping(bool looping)
{
	m_isLooping = looping;
	m_sound->setLoop(looping);
}

void Sound::SetVolume(float volume)
{
	m_volume = volume;
	m_sound->setVolume(volume);
}


float Sound::GetVolume()
{
	return m_volume;
}

bool Sound::IsLooping()
{
	return m_isLooping;
}

void Sound::Update(void)
{
	for (int32 i = 0; i < m_instances.size(); ++i)
	{
		if (m_instances[i].getStatus() == sf::Sound::Stopped)
		{
			m_instances.erase(m_instances.begin() + i);
			--i;
		}
	}
}

string Sound::GetName()
{

	return m_name;
}

sf::Sound * Sound::GetSound()
{
	
	return m_sound;
}
