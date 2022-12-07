#pragma once
#include <Windows.h>


#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <deque>
#pragma comment(lib,"sfml-audio.lib")

#include <modern__.h>

class ISound
{
public:

	virtual modern_Boolean Initialize(const class modern_string& name) = 0;
	virtual modern_Boolean IsInitialized() = 0;
	virtual sf::SoundSource::Status GetStatus() = 0;
	virtual void Play() = 0;
	virtual void Play(const float volume) = 0;
	virtual class sf::Sound* StartPlaying() = 0;
	virtual void Stop() = 0;
	virtual void SetLooping(bool looping = true) = 0;
	virtual void SetVolume(float volume) = 0;
	virtual float GetVolume() = 0;
	virtual bool IsLooping() = 0;

	virtual void Update(void) = 0;

	virtual const modern_string_view& GetName() = 0;
	virtual sf::Sound* GetSound() = 0;
};

