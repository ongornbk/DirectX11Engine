#pragma once
#include <map>
#include <string>
#include "Unit.h"

class VariableUnit
{
protected:
	VariableUnit();
	~VariableUnit();
public:
	Unit* GetUnit(std::string name);
	bool  PushUnit(std::string name,Unit* i);
protected:
	std::map<std::string, Unit*> m_units;
};

class VariableInteger
{
protected:
	VariableInteger();
	~VariableInteger();
public:
	int GetInt(std::string name);
	bool PushInt(std::string name, int i);
	bool IncInt(std::string name);
	bool DecInt(std::string name);
	bool AddInt(std::string name, int i);
	bool SubInt(std::string name, int i);
	bool MulInt(std::string name, int i);
	bool DivInt(std::string name, int i);

protected:
	std::map<std::string, int> m_integers;
};

class VariableString
{
protected:
	VariableString();
	~VariableString();
public:
	std::string GetString(std::string name);
	bool PushString(std::string name, std::string value);
	bool MergeString(std::string name, std::string value);

protected:
	std::map<std::string, std::string> m_strings;
};

class VariablesManager : public VariableInteger, public VariableString,public VariableUnit
{
public:
	VariablesManager();
	~VariablesManager();

	


};

