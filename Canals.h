#pragma once
#include "gdef.h"
#include "ISound.h"
#include <map>
#include <string>
#include <queue>
#include "modern/modern_string.h"
#pragma region
using std::string;
using std::map;
#pragma endregion

#define NUMBER_OF_CANALS 8

enum CanalType
{
	CTAMBIENT = 0,
	CTCOMBAT = 1,
	CTSPEECH = 2,
	CTINTERFACE = 3,
	CTMUSIC = 4,
	CTSPELLS = 5,
	CTWARNINGS = 6,
	CTFOOTSTEPS = 7
};

struct Sound_Canal
{
public:



	Sound_Canal(CanalType type,float volume);
	~Sound_Canal();

	void Update(void);


	map<string,ISound*> m_sounds;
	CanalType m_type;

	void AddSound(class ISound* const sound, string name);
    void GetSound(string name);
	void GetSound(class modern_string& name);
	void Stop();

};

class Canals
{
public:
	Canals();
	~Canals();

	static Canals* GetInstance();

	ISound* __GetSound(string sound);
	ISound* __GetSound(class modern_string& sound);
	void __AddSound(CanalType type, string name, ISound* sound);

	void Play(WCHAR * sound);
	void Stop();

	void Update();

protected:
	Sound_Canal * m_canals[NUMBER_OF_CANALS];
private:

};

