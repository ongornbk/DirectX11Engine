#pragma once
#include "IBidirectionalElement.h"

template<class T>
class IBidirectionalStruct
{
public:
	virtual int32                    size()  const = 0;
	virtual bool                      empty() const = 0;

	virtual class IBidirectionalElement<T>* front() const = 0;
	virtual class IBidirectionalElement<T>* end()   const = 0;

	virtual T&                        get_front()   const = 0;
	virtual T&                        get_back()   const = 0;
	virtual void                      pop_front() = 0;
	virtual void                      push_front(const T element) = 0;
	virtual void                      pop_back() = 0;
	virtual void                      push_back(const T element) = 0;


};