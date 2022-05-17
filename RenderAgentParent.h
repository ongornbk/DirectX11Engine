#pragma once
#include "RenderLayerType.h"
#include <combaseapi.h>

interface RenderAgentParent
{
	virtual const enum class RenderLayerType GetRenderLayer() const noexcept = 0;
};

