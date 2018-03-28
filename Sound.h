#pragma once
#include <Windows.h>


#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#pragma comment(lib,"sfml-audio.lib")
using namespace std;

class Sound
{
public:
	Sound(WCHAR* soundFileName);
	~Sound(void);
	bool Initialize(WCHAR* soundFileName);
	bool IsInitialized();
	sf::SoundSource::Status GetStatus();
	void Play();
	void Play(float volume);
	void Play(bool isLooping);
	void Play(bool isLooping, float volume);
	void SetLooping(bool looping = true);
	void SetVolume(float volume);
	float GetVolume();
	bool IsLooping();

	string GetName();
	sf::Sound* GetSound();
private:
	sf::Sound* m_sound;
	sf::SoundBuffer m_soundBuffer;

	string m_name;
	bool m_initialized;
	bool m_isLooping;
	float m_volume;
};

