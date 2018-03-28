#include <algorithm>
#include <iterator>

using std::iterator;

template <class Type> class DynamicArray
{
	unsigned int   m_size;
	unsigned int   m_elements;
	Type* m_array;

	Type* m_lastPointer;
public:
	DynamicArray()
	{
		m_size = 1;
		m_elements = 0;
		m_array = new Type();
	}
	~DynamicArray()
	{
		free(m_array);
	}

	void clear()
	{
		m_size = 1;
		m_elements = 0;
		free(m_array);
	}

	int size()
	{
		return m_size;
	}
	int elements()
	{
		return m_elements;
	}
	Type at(unsigned long index)
	{
		if (index >= 0 && index<m_elements)
		{
			return m_array[index];
		}
		else
		{

			return Type();
		}
	}
	// constexpr iterator<std::output_iterator_tag,Type*,> begin()
	//{
	//	return std::begin(m_array);
	//}

	 //constexpr iterator<Type*> end()
	//{
	//	return std::end(m_array);
	//}

	void push_back(Type element)
	{
		m_elements++;
		if (m_elements >= m_size) alloc();
		m_array[m_elements - 1] = element;

	}

	void reserve(int size)
	{
		m_size = size;
		this->m_array = (Type*)calloc(m_size, sizeof(Type));
	}
private:
	void alloc()
	{
		m_size *= 2;
		Type* m_lastPointer = m_array;
		this->m_array = (Type*)calloc(m_size, sizeof(Type));
		memcpy(m_array, m_lastPointer, sizeof(Type)*(m_size / 2));
		free(m_lastPointer);

	}
};

