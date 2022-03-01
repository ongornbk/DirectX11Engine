#pragma once
#include <DirectXMath.h>

class ColorFilter
{
protected:
	struct DirectX::XMFLOAT4     m_colorFilter;
	ColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter);
	ColorFilter(const struct DirectX::XMFLOAT4& color);
public:
	void SetColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter) noexcept;
	void SetColorFilter(const struct DirectX::XMFLOAT4& color) noexcept;
	void SetColorFilter(const float filter) noexcept;

	void AddAlpha(const float alpha) noexcept;
};

