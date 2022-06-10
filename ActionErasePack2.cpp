#include "ActionErasePack2.h"
#include "Global.h"

ActionErasePack2::ActionErasePack2(modern_pack2& refpack)
{
	m_pack = refpack;
}

ActionErasePack2::~ActionErasePack2()
{
}

void ActionErasePack2::execute()
{
	//Global::GetInstance()->m_bmap2.erase(m_pack);
}

const ActionBehavior ActionErasePack2::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
