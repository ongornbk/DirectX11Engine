#pragma once
class Direct2DCallback
{
protected:
	static void(*m_renderCallback)(void);
	static void(*m_updateCallback)(void);
};

