#pragma once
#include "modern/modern.h"
class UnitTemplate
{
	UnitTemplate();

	modern_string m_name;

public:

	~UnitTemplate();

	static class UnitTemplate* LoadFromFile(class modern_string path);
};

