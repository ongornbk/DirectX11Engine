#include "Text.h"



Text::Text()
{
}

Text::Text(const Text &)
{
}


Text::~Text()
{
}

bool Text::Initialize(ID3D11Device *, ID3D11DeviceContext *, HWND, int, int, XMMATRIX)
{
	return false;
}

void Text::Shutdown()
{
}

bool Text::Render(ID3D11DeviceContext *, XMMATRIX, XMMATRIX)
{
	return false;
}

bool Text::InitializeSentence(SentenceType **, int, ID3D11Device *)
{
	return false;
}

bool Text::UpdateSentence(SentenceType *, char *, int, int, float, float, float, ID3D11DeviceContext *)
{
	return false;
}

void Text::ReleaseSentence(SentenceType **)
{
}

bool Text::RenderSentence(ID3D11DeviceContext *, SentenceType *, XMMATRIX, XMMATRIX)
{
	return false;
}
