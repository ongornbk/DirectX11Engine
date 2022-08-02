#include "SingleSound.h"
#include <iostream>

SingleSound::SingleSound(const class modern_string& name)
{
	m_sound = nullptr;
	m_volume = 100.0f;
	m_isLooping = false;
	m_initialized = Initialize(name);
}


SingleSound::~SingleSound()
{
	if (m_sound)
	{
		delete m_sound;
		m_sound = NULL;
	}
}

modern_Boolean SingleSound::Initialize(const class modern_string& name)
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

modern_Boolean SingleSound::IsInitialized()
{
	return modern_Boolean(m_initialized);
}

sf::SoundSource::Status SingleSound::GetStatus()
{
	return m_sound->getStatus();
}

void SingleSound::Play()
{
	if (!m_initialized) return;
	m_sound->play();
}

void SingleSound::Play(const float volume)
{
	if (!m_initialized) return;
	m_sound->setVolume(volume);
	m_sound->play();
}

class sf::Sound* SingleSound::StartPlaying()
{
	if (!m_initialized) return nullptr;
	SingleSound::SetLooping(true);
	m_sound->play();
	return m_sound;
}

void SingleSound::Stop()
{
	if (!m_initialized) return;
	//	m_sound->pause();
}

void SingleSound::SetLooping(bool looping)
{
	if (!m_initialized) return;
	m_isLooping = looping;
	m_sound->setLoop(looping);
}

void SingleSound::SetVolume(float volume)
{
	if (!m_initialized) return;
	m_volume = volume;
	m_sound->setVolume(volume);
}


float SingleSound::GetVolume()
{
	return m_volume;
}

bool SingleSound::IsLooping()
{
	return m_isLooping;
}

void SingleSound::Update(void)
{
	//for (int32_t i = 0; i < m_instances.size(); ++i)
	//{
	//	if (m_instances[i].getStatus() == sf::Sound::Stopped)
	//	{
	//		m_instances.erase(m_instances.begin() + i);
	//		--i;
	//	}
	//}
	if (!m_initialized) return;
}

const class modern_string_view& SingleSound::GetName()
{
	return *(new modern_string_view(&m_name));
}

sf::Sound* SingleSound::GetSound()
{

	return m_sound;
}
