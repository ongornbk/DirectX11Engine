#pragma once
#include <string>
#include <functional>
#include <map>
#include <stack>
#include "IAction.h"
#include "PointerParameter.h"

#include "BasicParameter.h"

class ActionMap
{
	ActionMap();
	std::map< std::string, std::function<class IAction*(class ActionMap*)>> m_fooMap;
	std::stack<IParameter*> m_stack;

public:

	~ActionMap();

	static class ActionMap* GetInstance();

	void AddAction(std::function<class IAction*(class ActionMap*)> foo, std::string name);

	std::function<class IAction* (class ActionMap*)> const GetAction(std::string);

	void* PopPointer();
	BasicParameter::BasicParameterValue PopBasic();

	void PushPointer(void* const ptr);
	void PushBasic(const float __float__type);
	void PushBasic(const double __double__type);
	void PushBasic(const int8 __int8__type);
	void PushBasic(const int16 __int16__type);
	void PushBasic(const int32 __int32__type);
	void PushBasic(const int64 __int64__type);
	void PushBasic(const uint8 __uint8__type);
	void PushBasic(const uint16 __uint16__type);
	void PushBasic(const uint32 __uint32__type);
	void PushBasic(const uint64 __uint64__type);
};					 

