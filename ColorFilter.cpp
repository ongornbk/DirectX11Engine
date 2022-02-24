#include "ColorFilter.h"

ColorFilter::ColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter) :
	m_colorFilter(redfilter,greenfilter,bluefilter,alphafilter)
{

}

ColorFilter::ColorFilter(const DirectX::XMFLOAT4& color) :
	m_colorFilter(color)
{

}

void ColorFilter::SetColorFilter(const float redfilter, const float greenfilter, const float bluefilter, const float alphafilter) noexcept
{
	if (redfilter >= 0.f)
		m_colorFilter.x = redfilter;
	if (greenfilter >= 0.f)
		m_colorFilter.y = greenfilter;
	if (bluefilter >= 0.f)
		m_colorFilter.z = bluefilter;
	if (alphafilter >= 0.f)
		m_colorFilter.w = alphafilter;
}

void ColorFilter::SetColorFilter(const DirectX::XMFLOAT4& color) noexcept
{
	if (color.x >= 0.f)
		m_colorFilter.x = color.x;
	if (color.y >= 0.f)
		m_colorFilter.y = color.y;
	if (color.z >= 0.f)
		m_colorFilter.z = color.z;
	if (color.w >= 0.f)
		m_colorFilter.w = color.w;
}

void ColorFilter::AddAlpha(const float alpha) noexcept
{
	m_colorFilter.w += alpha;
}
