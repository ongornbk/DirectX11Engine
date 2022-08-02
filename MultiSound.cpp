#include "MultiSound.h"
#include <iostream>

MultiSound::MultiSound(const class modern_string& name)
{
	m_sound = nullptr;
	m_volume = 100.0f;
	m_isLooping = false;
	m_initialized = Initialize(name);
}


MultiSound::~MultiSound()
{
	if (m_sound)
	{
		delete m_sound;
		m_sound = NULL;
	}
}

modern_Boolean MultiSound::Initialize(const class modern_string& name)
{
	std::wstring tmp0 = std::wstring(name.c_wstr());
	std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
	size_t pos = (size_t)tmp0.find_last_of(L"/");
	if (pos >= 0ull)
	{
		tmp0 = tmp0.substr(pos + 1ull, tmp0.length());
	}
	m_name = tmp0.substr(0ull, tmp0.find(L".")).c_str();


	if (!m_soundBuffer.loadFromFile(tmp1))
	{
		return modern_false;
	}

	{
		m_sound = new sf::Sound();
		m_sound->setBuffer(m_soundBuffer);
	}

	return modern_true;
}

modern_Boolean MultiSound::IsInitialized()
{
	return modern_Boolean(m_initialized);
}

sf::SoundSource::Status MultiSound::GetStatus()
{
	return m_sound->getStatus();
}

void MultiSound::Play()
{
	if (m_instances.size() < 10u)
	{
		m_instances.push_back(sf::Sound(m_soundBuffer));
		m_instances.back().play();
	}
}

void MultiSound::Play(const float volume)
{
	if (volume < 10.f)
	{
		return;
	}
	if (m_instances.size() < 10u)
	{
		sf::Sound& sound = sf::Sound(m_soundBuffer);
		sound.setVolume(volume);
		m_instances.push_back(sound);
		m_instances.back().play();
	}
}

class sf::Sound* MultiSound::StartPlaying()
{
	MultiSound::SetLooping(true);
	sf::Sound& sound = *new sf::Sound(m_soundBuffer);
	m_instances.push_back(sound);
	m_instances.back().play();
	return &sound;
}

void MultiSound::Stop()
{
	//	m_sound->pause();
}

void MultiSound::SetLooping(bool looping)
{
	m_isLooping = looping;
	m_sound->setLoop(looping);
}

void MultiSound::SetVolume(float volume)
{
	m_volume = volume;
	m_sound->setVolume(volume);
}


float MultiSound::GetVolume()
{
	return m_volume;
}

bool MultiSound::IsLooping()
{
	return m_isLooping;
}

void MultiSound::Update(void)
{
	for (int32_t i = 0; i < m_instances.size(); ++i)
	{
		if (m_instances[i].getStatus() == sf::Sound::Stopped)
		{
			m_instances.erase(m_instances.begin() + i);
			--i;
		}
	}
}

const class modern_string_view& MultiSound::GetName()
{
	return *(new modern_string_view(&m_name));
}

sf::Sound* MultiSound::GetSound()
{

	return m_sound;
}
