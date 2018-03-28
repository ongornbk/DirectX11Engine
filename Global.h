#pragma once
#include "Model.h"

class Global
{
public:
	Global(void);
	~Global(void);
	Model * m_lastSelectedModel;
	static Global* GetInstance();

};

