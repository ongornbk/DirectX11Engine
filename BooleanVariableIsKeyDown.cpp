#include "BooleanVariableIsKeyDown.h"
#include "Engine.h"

BooleanVariableIsKeyDown::BooleanVariableIsKeyDown(const uint32_t __key) : key(__key)
{
}

const bool BooleanVariableIsKeyDown::get()
{
	return Engine::GetEngine()->GetInput()->IsKeyDown(key);
}
