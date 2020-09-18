#include "UnitTemplate.h"
#include <fstream>
#include <string>
#include <sstream>

UnitTemplate::~UnitTemplate()
{
}

UnitTemplate* UnitTemplate::LoadFromFile(modern_string path)
{
	std::ifstream stream(path.c_wstr());
	if (!stream.good())
	{
		return nullptr;
	}

	{
		std::wstring buffer((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

		std::wistringstream ss(buffer);
		std::wstring token;
		while (getline(ss, token, L'\n'))
		{
			modern_pair<modern_string, modern_string> pair = modern_string::SplitString(token.c_str(), L' ');
		}

		stream.close();
	}
	return 0;
}
