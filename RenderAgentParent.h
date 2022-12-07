#pragma once
#include "RenderLayerType.h"
#include <combaseapi.h>

#include <modern__.h>

interface RenderAgentParent
{
	virtual const enum class RenderLayerType GetRenderLayer() const modern_except_state = 0;
};

