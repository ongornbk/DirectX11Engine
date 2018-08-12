#include "Font.h"
#include "Onion.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>

#define FONTPATH "../../content/Textures/font/"

using Onion::Console;

namespace
{
	static std::vector<Font*> m_fonts;
}

Font::Font(float width, float height, Font_FLOAT4 coords)
{

}


Font::~Font()
{

}

void Font::LoadFontFromFile(std::string filename,float width,float height)
{
	Font_FLOAT4 coords;
	memset(&coords, 0.0f, sizeof(float) * (size_t)255);

#pragma warning(disable : 4996)
#pragma region
	using std::ifstream;
	using std::getline;
	using std::istreambuf_iterator;
	using std::istringstream;
	using std::string;
#pragma endregion

	ifstream stream(FONTPATH+filename);
	if (!stream.good())
	{
		Console::SetTextColor(Onion::RED);
		Console::Println("Bad stream : " + filename);
	}
	string BUFFER((istreambuf_iterator<char>(stream)), istreambuf_iterator<char>());
	istringstream ss(BUFFER);
	std::vector<float> coordinates;
	string token,token2;

	

	while (getline(ss, token, '\n'))
	{
		std::cout << token << std::endl;
		//while (getline(istringstream(token), token2, ' '))
		//{
		//	std::cout <<"gleba" << std::endl;
		//	coordinates.push_back((float)atoi(token2.c_str()));
		//}
	}

	while (!coordinates.empty())
	{
		std::cout << coordinates.back() << std::endl;
		coordinates.pop_back();
	}
}

void Font::ReleaseFonts()
{

}
