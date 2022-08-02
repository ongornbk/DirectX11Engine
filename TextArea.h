#pragma once

class TextArea
{
public:

	enum TextAreaStance
	{
		OPEN,
		CLOSED
	};

	TextArea();
	~TextArea();

	void Open() modern_except_state;
	void Close() modern_except_state;

	void Update() modern_except_state;
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4  worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) modern_except_state;

private:
	Text* m_text;
	TextAreaStance m_stance;
};

