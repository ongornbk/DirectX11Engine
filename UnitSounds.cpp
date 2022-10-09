#include "UnitSounds.h"
#include "IPP.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <streambuf>
#include <map>

UnitSounds::UnitSounds(void)
{
	for (int32_t i = 0; i < 13; i++)
		m_sounds[i] = 0;
}

UnitSounds::~UnitSounds(void)
{
}

void UnitSounds::Play(const enum UnitSoundType type)
{
	if (m_sounds[type])
		m_sounds[type]->Play();
}



void UnitSounds::LoadSounds(WCHAR* file)
{
#pragma warning(disable : 4996)
#pragma region
	using std::ifstream;
	using std::getline;
	using std::istreambuf_iterator;
	using std::istringstream;
#pragma endregion
	ifstream stream(file);
	if (!stream.good())
	{
		ipp::Console::SetTextColor(MODERN_CONSOLE_TEXT_COLOR::RED);
		ipp::Console::Println("Bad stream : ");
	}
	std::string BUFFER((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	std::vector<WCHAR*> sounds;
	std::string token;
	while (getline(ss, token, '\n'))
	{
		wchar_t* wide_string = new wchar_t[token.length() + 1];
		wstring ws = std::wstring(token.begin(), token.end()).c_str();
		wcscpy(wide_string, ws.c_str());
		if (wcscmp(wide_string, L"NULL"))
		{
			sounds.push_back(wide_string);
		}
		else
		{
			sounds.push_back(NULL);
		}
	}

	class ResourceManager* const rm = ResourceManager::GetInstance();

	for(int32_t i = 0;i < 13;i++)
	m_sounds[i] = rm->GetSoundByName(sounds.at(i));

}
