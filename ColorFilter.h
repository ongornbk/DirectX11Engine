#pragma once
#include <DirectXMath.h>

#include <modern__.h>

class ColorFilter
{
protected:
	struct DirectX::XMFLOAT4     m_colorFilter;
	ColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter);
	ColorFilter(const struct DirectX::XMFLOAT4& color);
public:
	void SetColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter) modern_except_state;
	void SetColorFilter(const struct DirectX::XMFLOAT4& color) modern_except_state;
	void SetColorFilter(const float filter) modern_except_state;

	void AddAlpha(const float alpha) modern_except_state;
};

