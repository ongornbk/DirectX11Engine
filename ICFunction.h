#pragma once

class ICFunction
{

	ICFunction() = delete;
protected:
	void* m_f;

	ICFunction(void* const foo) : m_f(foo) {}
public:
	virtual void execute() = 0;
};