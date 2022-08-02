#pragma once
#include "Texture.h"
#include "LetterSprite.h"
#include "modern/modern_array.h"
#include <string>
#include "modern/modern_vector.h"



struct FLOATX6
{
	float __f32[6];
};

class TextFont
{
public:
	


	struct Coords
	{
		float m_left;
		float m_top;
		float m_right;
		float m_bottom;
	} m_char[256u];

~TextFont();

void Initialize(ID3D11Device* device, ID3D11DeviceContext* context, Shader* shader);

static void LoadFontFromFile(std::string name,float width,float height);
static TextFont* GetFontByName(std::string name);
static void ReleaseFonts();

std::string GetName();
FLOATX6 GetCoordsOfLetter(char letter);
float GetLeftOfLetter(char letter);
float GetWidthOfLetter(char letter);

class LetterSprite* const GetSprite(class Text* const text,const char ch);
class Shader* const GetShader() modern_except_state;

void InitializeCoordinates(class modern_vector<float>& coords);

private:

	bool m_initialized;

	TextFont(float width,float height,std::string filename,bool upper = true);
	

	float m_width;
	float m_height;

	bool m_flag;

	std::string m_name;

	modern_array<class LetterSprite*> m_letters;

	class Shader* m_shader;

	friend class LetterSprite;
};

