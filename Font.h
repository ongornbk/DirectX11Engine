#pragma once
#include <string>

class Font
{
public:
	


	struct Font_FLOAT4
	{
		float m_left;
		float m_top;
		float m_right;
		float m_bottom;
	};

~Font();

static void LoadFontFromFile(std::string name,float width,float height);
static void ReleaseFonts();

private:

	Font(float width,float height,Font_FLOAT4 coords);

	float m_width;
	float m_height;
	Font_FLOAT4 m_char[255u];
};

