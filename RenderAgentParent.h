#pragma once
#include "RenderLayerType.h"
#include <combaseapi.h>
#include "modern/modern_def.h"

interface RenderAgentParent
{
	virtual const enum class RenderLayerType GetRenderLayer() const modern_except_state = 0;
};

