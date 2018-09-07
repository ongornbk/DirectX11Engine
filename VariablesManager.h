#pragma once
#include <map>
#include <string>
#include "Unit.h"


class VariablePoint
{
protected:
	VariablePoint();
	~VariablePoint();
public:
	XMFLOAT3 GetPoint(std::string name);
	bool   PushPoint(std::string name, XMFLOAT3 i);
	bool   ErasePoint(std::string name);

protected:
	std::map<std::string, XMFLOAT3> m_points;
};

class VariableBoolean
{
protected:
	VariableBoolean();
	~VariableBoolean();
public:
	int8_t GetBoolean(std::string name);
	bool   PushBoolean(std::string name,bool i);
	bool   EraseBoolean(std::string name);
	bool   NegateBoolean(std::string name);

protected:
	std::map<std::string, bool> m_bools;
};

class VariableUnit
{
protected:
	VariableUnit();
	~VariableUnit();
public:
	Unit* GetUnit(std::string name);
	bool  PushUnit(std::string name,Unit* i);
	bool  EraseUnit(std::string name);

protected:
	std::map<std::string, Unit*> m_units;
};

class VariableReal
{
protected:
	VariableReal();
	~VariableReal();
public:
	float GetReal(std::string name);
	bool PushReal(std::string name, float i);
	bool IncReal(std::string name);
	bool DecReal(std::string name);
	bool AddReal(std::string name, float i);
	bool SubReal(std::string name, float i);
	bool MulReal(std::string name, float i);
	bool DivReal(std::string name, float i);

protected:
	std::map<std::string, float> m_reals;
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

class VariablesManager : public VariableInteger, public VariableString,public VariableUnit,public VariableBoolean,
	public VariablePoint,public VariableReal
{
public:
	VariablesManager();
	~VariablesManager();

	


};

