#pragma once

template <class A, class B>
class modern_pair
{
	modern_pair()
	{

	}

public:

	A& first;
	B& second;

	

	constexpr modern_pair(A&& a, B&& b) : first(a), second(b) {}

	~modern_pair()
	{

	}

	bool operator ==(const modern_pair<A, B>& b) const
	{
		return (this->first == b.first) && (this->second == b.second);
	}

	void operator = (const B b)
	{
		second = b;
	}

};