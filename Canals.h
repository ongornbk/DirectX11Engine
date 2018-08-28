#pragma once
#include "Sound.h"
#include <map>
#include <string>
#pragma region
using std::string;
using std::map;
#pragma endregion

#define NUMBER_OF_CANALS 8

enum CanalType
{
	AMBIENT = 0,
	COMBAT = 1,
	SPEECH = 2,
	INTERFACE = 3,
	MUSIC = 4,
	SPELLS = 5,
	WARNINGS = 6,
	FOOTSTEPS = 7
};

struct Sound_Canal
{
public:



	Sound_Canal(CanalType type,float volume);
	~Sound_Canal();



	map<string,Sound*> m_sounds;
	CanalType m_type;

	void AddSound(Sound* sound, string name);
    void GetSound(string name);

};

class Canals
{
public:
	Canals();
	~Canals();

	static Canals* GetInstance();

	Sound* __GetSound(string sound);
	void __AddSound(CanalType type, string name, Sound* sound);

protected:
	Sound_Canal * m_canals[NUMBER_OF_CANALS];
private:

};

