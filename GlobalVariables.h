#pragma once
#include "GameChat.h"

namespace gv
{
	static ID3D11Device*        g_device     = nullptr;
	static ID3D11DeviceContext* g_context    = nullptr;
	static Shader*              g_textShader = nullptr;
	static GameChat*            g_gameChat   = nullptr;
}
