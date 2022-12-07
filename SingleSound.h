#pragma once
#include "ISound.h"

class SingleSound :
	public ISound
{
public:
	SingleSound(const class modern_string& name);
	~SingleSound(void);
	modern_Boolean Initialize(const class modern_string& name) override;
	modern_Boolean IsInitialized() override;
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

	const class modern_string_view& GetName() override;
	sf::Sound* GetSound() override;
private:
	sf::Sound* m_sound;
	sf::SoundBuffer m_soundBuffer;

	modern_string m_name;
	bool m_initialized = false;
	bool m_isLooping;
	float m_volume;
};

