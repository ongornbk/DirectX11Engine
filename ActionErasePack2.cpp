#include "ActionErasePack2.h"
#include "Global.h"

ActionErasePack2::ActionErasePack2(struct modern_pack2* const refpack)
{
	m_pack = refpack;
}

ActionErasePack2::~ActionErasePack2()
{
	if (m_pack)
	{
		delete m_pack;
		m_pack = nullptr;
	}
}

void ActionErasePack2::execute()
{
	//auto& mpb = *&Global::GetInstance()->m_binaryMapPack2;
	//auto& mpc = mpb.find(m_pack->m_bits);
	//if (mpc == mpb.end())
	//	return;
	//(*mpc).second.second--;
	//if ((*mpc).second.second <= 0ll)
	{
	//	mpb[m_pack->first].erase(m_pack->second);
	}
}

const ActionBehavior ActionErasePack2::execute_in_array()
{
	this->execute();
	return ActionBehavior::ACTION_BEHAVIOR_FALLTHROUGH;
}
