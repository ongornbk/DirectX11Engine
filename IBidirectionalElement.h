#pragma once
#include "gdef.h"

template <class T>
class IBidirectionalElement
{
public:

	IBidirectionalElement(class IBidirectionalElement<T>& ele) : data(ele->data), next(ele->next), previous(ele->previous) {}

	T                          data;
	class IBidirectionalElement<T>*  next;
	class IBidirectionalElement<T>*  previous;

	static void SwapElements(IBidirectionalElement<T>* A, IBidirectionalElement<T>* B)
	{
		//todo
	}
};