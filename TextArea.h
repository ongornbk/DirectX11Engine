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

	void Open() noexcept;
	void Close() noexcept;

	void Update() noexcept;
	void Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4  worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix) noexcept;

private:
	Text* m_text;
	TextAreaStance m_stance;
};

