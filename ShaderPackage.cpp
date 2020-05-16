#include "ShaderPackage.h"

namespace
{
	std::mutex m_lock;
}

void ShaderPackage::BeginShadow() const
{
if (current)
	current->End(m_context);
shadow->Begin(m_context);
current = shadow;	
}

void ShaderPackage::BeginStandard() const
{
if (current)
	current->End(m_context);
standard->Begin(m_context);
current = standard;	
}

void ShaderPackage::BeginSelect() const
{
if (current)
	current->End(m_context);
select->Begin(m_context);
current = select;

}

void ShaderPackage::lock() const
{
	m_lock.lock();
}

void ShaderPackage::unlock() const
{
	m_lock.unlock();
}

void ShaderPackage::End() const
{
if(current)
	current->End(m_context);
current = nullptr;
}
