#pragma once
#include "gdef.h"
#include "RegionPointObject.h"

class Region
{


	class RegionPointObject* m_pointNorthWest;
	class RegionPointObject* m_pointNorthEast;
	class RegionPointObject* m_pointSouthEast;
	class RegionPointObject* m_pointSouthWest;

public:

	Region() = delete;
	explicit Region(struct DirectX::XMFLOAT4 borders);

	int32 GetNumberOfObjectsX();
	int32 GetNumberOfObjectY();


	
};

