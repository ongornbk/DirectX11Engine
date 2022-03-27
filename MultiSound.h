#pragma once
#include "ISound.h"
class MultiSound :
	public ISound
{
public:
	MultiSound(WCHAR* soundFileName);
	~MultiSound(void);
	bool Initialize(WCHAR* soundFileName) override;
	bool IsInitialized() override;
	sf::SoundSource::Status GetStatus() override;
	void Play() override;
	void Play(const float volume) override;
	class sf::Sound* StartPlaying() override;
	void Stop() override;
	void SetLooping(bool looping = true) override;
	void SetVolume(float volume) override;
	float GetVolume() override;
	bool IsLooping() override;

	void Update(void) override;

	std::string GetName() override;
	sf::Sound* GetSound() override;
private:
	sf::Sound* m_sound;
	sf::SoundBuffer m_soundBuffer;

	std::string m_name;
	bool m_initialized;
	bool m_isLooping;
	float m_volume;

	class std::deque<class sf::Sound> m_instances;
};

