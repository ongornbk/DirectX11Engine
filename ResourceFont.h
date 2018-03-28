#pragma once
#include "Font.h"

class ResourceFont
{
public:
	ResourceFont();
	~ResourceFont();
	bool Load(ID3D11Device* device, WCHAR* fontFileName);

	Font* GetFont();
	string GetName();
private:
	Font* m_font;
};

