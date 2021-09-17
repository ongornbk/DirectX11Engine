#include "PTaskRender.h"

PTaskRender::PTaskRender(Engine* const engine) : m_engine(engine)
{
}

void PTaskRender::execute()
{
	m_engine->PRender();
}
