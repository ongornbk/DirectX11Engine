#pragma once
#include "Region.h"

class IRegionAgent
{
public:
	virtual void Initialize(const DirectX::XMFLOAT2 position,class Region* const agent) = 0;
	virtual ~IRegionAgent();

	virtual void PostInitializeText() = 0;
	virtual void SetText(std::string text) = 0;
};

