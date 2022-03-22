
struct modern_element
{
	modern_element*          next;
	void*                    data;

	constexpr modern_element(struct modern_element* const __next, void* __data)
		: next(__next),data(__data)
	{

	}
};