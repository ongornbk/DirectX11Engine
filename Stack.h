#pragma once
#include <cstdint>

namespace Whoops
{
	class Stack
	{
		struct StackElement
		{
			StackElement()
			{
				next = nullptr;
			}
			~StackElement()
			{
				if (next)
					delete next;
			}
			void* data;
			StackElement* next;
		};

	public:
		Stack();
		~Stack();

		void* top();
		void pop();
		bool empty();
		void push(void* element);
		void clear();

		uint32_t size();

	private:
		StackElement*    m_top;
		uint32_t         m_size;
	};

}
