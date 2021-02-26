#include "SingleSound.h"

SingleSound::SingleSound(WCHAR* soundFileName)
{
	m_sound = NULL;
	m_volume = 100.0f;
	m_isLooping = false;
	m_initialized = Initialize(soundFileName);
}


SingleSound::~SingleSound()
{
	if (m_sound)
	{
		delete m_sound;
		m_sound = NULL;
	}
	m_name.clear();
}

bool SingleSound::Initialize(WCHAR* soundFileName)
{
	std::wstring tmp0 = std::wstring(soundFileName);
	std::string tmp1 = std::string(tmp0.begin(), tmp0.end());
	int32_t pos = (int32_t)tmp1.find_last_of("/");
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

bool SingleSound::IsInitialized()
{
	return m_initialized;
}

sf::SoundSource::Status SingleSound::GetStatus()
{
	return m_sound->getStatus();
}

void SingleSound::Play()
{
	m_sound->play();
}

class sf::Sound* SingleSound::StartPlaying()
{
	SingleSound::SetLooping(true);
	m_sound->play();
	return m_sound;
}

void SingleSound::Stop()
{
	//	m_sound->pause();
}

void SingleSound::SetLooping(bool looping)
{
	m_isLooping = looping;
	m_sound->setLoop(looping);
}

void SingleSound::SetVolume(float volume)
{
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
}

std::string SingleSound::GetName()
{

	return m_name;
}

sf::Sound* SingleSound::GetSound()
{

	return m_sound;
}
