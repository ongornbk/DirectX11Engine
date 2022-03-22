#pragma once
#include <Windows.h>


#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <deque>
#pragma comment(lib,"sfml-audio.lib")
using namespace std;

#include "gdef.h"
#include "List.h"

class Sound
{
public:
	Sound(WCHAR* soundFileName);
	~Sound(void);
	bool Initialize(WCHAR* soundFileName);
	bool IsInitialized();
	sf::SoundSource::Status GetStatus();
	void Play();
	class sf::Sound* StartPlaying();
	void Stop();
	void SetLooping(bool looping = true);
	void SetVolume(float volume);
	float GetVolume();
	bool IsLooping();

	void Update(void);

	string GetName();
	sf::Sound* GetSound();
private:
	sf::Sound* m_sound;
	sf::SoundBuffer m_soundBuffer;

	string m_name;
	bool m_initialized;
	bool m_isLooping;
	float m_volume;

	class std::deque<class sf::Sound> m_instances;
};

