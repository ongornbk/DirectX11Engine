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
	int pos = (int)tmp1.find_last_of("/");
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
	if (GetStatus() != sf::SoundSource::Playing)
	{
		m_sound->play();
	}

}

void Sound::Play(float volume)
{
	m_volume = volume;
	if (GetStatus() != sf::SoundSource::Playing)
	{
		m_sound->setVolume(volume);
		m_sound->play();
	}
}

void Sound::Play(bool isLooping)
{
	m_isLooping = isLooping;
	if (GetStatus() != sf::SoundSource::Playing)
	{
		m_sound->setLoop(isLooping);
		m_sound->play();
	}
}

void Sound::Play(bool isLooping, float volume)
{
	m_isLooping = isLooping;
	m_volume = volume;
	if (GetStatus() != sf::SoundSource::Playing)
	{
		m_sound->setLoop(isLooping);
		m_sound->setVolume(volume);
		m_sound->play();
	}
	else
		
		{
		m_sound->stop();
		//m_sound->
			m_sound->setLoop(isLooping);
			m_sound->setVolume(volume);
			m_sound->play();
		}

	
}

void Sound::Stop()
{
	m_sound->stop();
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

string Sound::GetName()
{

	return m_name;
}

sf::Sound * Sound::GetSound()
{
	
	return m_sound;
}
