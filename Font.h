#pragma once
#include "Texture.h"
#include <string>
#include <vector>

struct FLOATX6
{
	float __f32[6];
};

class Font
{
public:
	


	struct Coords
	{
		float m_left;
		float m_top;
		float m_right;
		float m_bottom;
	} m_char[256u];

~Font();

static void LoadFontFromFile(std::string name,float width,float height);
static Font* GetFontByName(std::string name);
static void ReleaseFonts();

std::string GetName();
FLOATX6 GetCoordsOfLetter(char letter);
float GetLeftOfLetter(char letter);
float GetWidthOfLetter(char letter);

void InitializeCoordinates(std::vector<float> coords);

private:

	Font(float width,float height,std::string filename,bool upper = true);

	float m_width;
	float m_height;

	bool m_flag;

	std::string m_name;

	friend class LetterSprite;
};

