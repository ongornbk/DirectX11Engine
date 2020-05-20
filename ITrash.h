#pragma once
class ITrash
{
public:
	void* m_data;
	ITrash() = delete;
	ITrash(void* const data);
	virtual ~ITrash();
private:

};

