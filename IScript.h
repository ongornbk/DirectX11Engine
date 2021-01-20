#pragma once
class IScript
{
public:
	virtual void Load(const char* const filename) = 0;
	virtual void Execute() = 0;
};

